<?php
/**
 * @name         MPR Email Service
 * @version      1.6
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
// register publicly accessible xajax funtions
array_push($global['xajax_functions'],'mpres_getBusy');
array_push($global['xajax_functions'],'mpres_getData');

function mpres_getBusy(){
	global $global;
	//$d = print_r($global, TRUE); // <br><pre>'.$d.'</pre>
	$global['xajax_res']->addAssign('downloadButton','style.display','none');
	$global['xajax_res']->addAssign('mpresData','innerHTML','<br><br><br><div style="border: 1px solid green; background-color: #E5FFE5; padding: 15px;"><center><span style="color: green; font-weight: bold; font-size: 20px;"><blink>Downloading Emails...</blink></span></center></div>');
	return $global['xajax_res']->getXML();
}


function mpres_downloadEmailData(){


}


function mpres_getData( $download = 1 ){
	global $global;
	$html = "";

/////// DOWNLOAD EMAILS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( $download == 1 ) {

		// get configuration settings
		$q = "select * from mpres_settings where mpres_index = '0'";
		$res = $global['db']->Execute($q);
		$host		= $res->fields['mpres_host'];
		$port		= $res->fields['mpres_port'];
		$popimap	= $res->fields['mpres_popimap'];
		$ssl		= $res->fields['mpres_ssl'];
		$username	= $res->fields['mpres_username'];
		$password 	= $res->fields['mpres_password'];
		$attachments	= $res->fields['mpres_attachments'];
		if ( $ssl ) {
			$sslOption = "/ssl/novalidate-cert";
		} else {
			$sslOption = "";
		}
		if ( $popimap == "POP" ) {
			$protocol = "pop3";
		} elseif ( $popimap == "IMAP" ) {
			$protocol = "imap";
		} else {
			$protocol = "imap";
		}

		$imapServer = "{". $host .":". $port ."/". $protocol . $sslOption ."}";
		$imapUsername 	= $username;
		$imapPassword 	= $password;
		$numberOfAttachments = 3;
		$mbox = imap_open( $imapServer, $imapUsername, $imapPassword );

		if ( $headers = imap_check($mbox) ) {
			//echo "Num Messages " . $hdr->Nmsgs ."\n\n<br><br>";
			$msgCount = $headers->Nmsgs;
		} else {
			$global['xajax_res']->addAssign('mpresData','innerHTML','<br><br><br><div style="border: 1px solid red; background-color: #ffaaaa; padding: 15px;"><center><span style="color: red; font-weight: bold; font-size: 20px;"><blink>Error accessing email account... Please check email settings.</blink></span></center></div>');
			return $global['xajax_res']->getXML();
		}

		$overview = imap_fetch_overview($mbox,"1:$msgCount",0);
		$size = sizeof($overview);

		// loop through each message and retrieve data
		for ( $i = $size-1; $i >= 0; $i-- ) {

			$message	= $overview[$i];
			$msgno		= $message->msgno; // message number
			$date		= $message->date;
			$subject	= $message->subject;
			$seen		= $message->seen;
			$from		= ereg_replace('/"/', '', $message->from);

			list($dayName,$day,$month,$year,$time,$zone) = explode(" ",$date);
			list($hour,$minute,$second) = explode(":",$time);

			// change 3 letter month abbreviation into decimal month
			switch ($month) {
				case "Jan": $month = "01"; break;
				case "Feb": $month = "02"; break;
				case "Mar": $month = "03"; break;
				case "Apr": $month = "04"; break;
				case "May": $month = "05"; break;
				case "Jun": $month = "06"; break;
				case "Jul": $month = "07"; break;
				case "Aug": $month = "08"; break;
				case "Sep": $month = "09"; break;
				case "Oct": $month = "10"; break;
				case "Nov": $month = "11"; break;
				case "Dec": $month = "12"; break;
			}

			$day = str_pad($day, 2, "0", STR_PAD_LEFT);
			$hour = str_pad($hour, 2, "0", STR_PAD_LEFT);
			$minute = str_pad($minute, 2, "0", STR_PAD_LEFT);
			$second = str_pad($second, 2, "0", STR_PAD_LEFT);
			$filename = $year . $month . $day ."_". $hour . $minute . $second;

			include_once($global['approot']."mod/mpres/nameParser.php");
			$name = new nameParser( $subject );

			// MySQL retrieves and displays DATETIME values in 'YYYY-MM-DD HH:MM:SS' format.
			$mpres_person['mpres_person_emailDateTime']	= $year ."-". $month ."-". $day ." ". $hour .":". $minute .":". $second;
			$mpres_person['mpres_person_emailSubject']	= $subject;
			$mpres_person['mpres_person_emailFrom']		= $from;
			$mpres_person['mpres_person_nameFirst']		= $name->getFirstName();
			$mpres_person['mpres_person_nameMiddle']	= $name->getMiddleName();
			$mpres_person['mpres_person_nameLast']		= $name->getLastName();
			$mpres_person['mpres_person_nameTitle']		= $name->getTitle();
			$mpres_person['mpres_person_nameSuffix']	= $name->getSuffix();
			shn_db_insert($mpres_person,'mpres_person',true);

			// get the id of the last inserted item
			$q = "select * from mpres_person order by mpres_person_index DESC limit 1;";
			$res = $global['db']->Execute($q);
			$personIndex = $res->fields['mpres_person_index'];

			// loop through image attachments (up to the maximum number specified) and parse out the image attachments from the email body
			for ( $j = 1; $j <= $numberOfAttachments; $j++ ) {

				// here we are assuming that the attachments are body segments (this may not be always correct but it works in most cases)
				$fileContent = imap_base64( imap_fetchbody($mbox,$i+1,$j+1) );
				if ( $fileContent != NULL ) {

					// save the image and a thumbnail to the www temporary folder so it can be displayed in the module
					$saveDir = $global['approot'].'www/tmp/';
					$saveFile = $saveDir .'original@'. $filename .'+'. $j;
					$thumbFile = $saveDir .'thumb@'. $filename .'+'. $j;
					$handle = fopen( $saveFile, "w" );
					fwrite( $handle, $fileContent );
					fclose( $handle );

					// check the image type
					$info = getimagesize($saveFile);
					if ( !$info ) {
						// something wrong with attachment -- delete it
						unlink( $saveFile );
					} else {
						$mime = $info['mime'];
						$width = $info[0];
						$height = $info[1];
						$widthNew = 100;
						$heightNew = 100;

						if ( $width < $height ) {
							$widthNew = ($heightNew / $height) * $width;
						} else {
							$heightNew = ($widthNew / $width) * $height;
						}

						if ( $mime == "image/jpeg" ) {
							$func = "imagecreatefromjpeg";
							$func2 = "imagejpeg";
							$ext = ".jpg";
							$quality = 90;
						} elseif ( $mime == "image/gif" ) {
							$func = "imagecreatefromgif";
							$func2 = "imagegif";
							$ext = ".gif";
							$quality = 90;
						} elseif ( $mime == "image/png" ) {
							$func = "imagecreatefrompng";
							$func2 = "imagepng";
							$ext = ".png";
							$quality = 9;
						} else {
							// unsupported image type, so delete it
							unlink($saveFile);
							$ext = "";
						}

						// create a thumbnail of the image for modular viewing and insert it into the database
						if ( $ext != "" ) {
							$image = $func( $saveFile );
							$image2 = imagecreatetruecolor($widthNew, $heightNew);
							imagecopyresampled($image2, $image, 0, 0, 0, 0, $widthNew, $heightNew, $width, $height);
							$func2( $image2, $thumbFile, $quality );
							rename( $saveFile, $saveFile.$ext   );
							rename( $thumbFile, $thumbFile.$ext );
							shell_exec( "chmod 744 ".$saveFile  );
							shell_exec( "chmod 744 ".$thumbFile );

							// put original image in database
							$mpres_image['mpres_person_index']	= $personIndex;
							$mpres_image['mpres_image_image']	= $fileContent;
							$mpres_image['mpres_image_type']	= $mime;
							$mpres_image['mpres_image_height']	= $height;
							$mpres_image['mpres_image_width']	= $width;
							$mpres_image['mpres_image_filename']	= $filename."+".$j.$ext;
							shn_db_insert($mpres_image,'mpres_image',true);
						}
					}
				}
			}
		}
		imap_close($mbox);
	}

/////// FORMAT TABLE DATA FOR DISPLAY IN MODULE ////////////////////////////////////////////////////////////////////////////////////////////////////

	// get configuration settings
	$q = "select * from mpres_person order by mpres_person_emailDateTime desc;";
	$res = $global['db']->Execute($q);

	while($row = $res->FetchRow() ){
		$index		= $row['mpres_person_index'];
		$emailDateTime	= $row['mpres_person_emailDateTime'];
		$emailSubject	= $row['mpres_person_emailsubject'];
		$emailFrom	= $row['mpres_person_emailFrom'];
		$nameFirst	= $row['mpres_person_nameFirst'];
		$nameMiddle	= $row['mpres_person_nameMiddle'];
		$nameLast	= $row['mpres_person_nameLast'];
		$nameTitle	= $row['mpres_person_nameTitle'];
		$nameSuffix	= $row['mpres_person_nameSuffix'];

		$html .= '<div style="background-color: #F3F6FF; border: 1px solid #C6D1F5; padding: 15px;">';
		$html .= 'Recieved: <b>'. $emailDateTime .'</b><br>From: <b>'. $emailFrom .'</B><hr style="border: none; background-color: #C6D1F5; height: 1px;">';
		if ( $nameTitle == "NULL" ) $nameTitle = "";
		if ( $nameFirst == "NULL" ) $nameFirst = "";
		if ( $nameMiddle == "NULL" ) $nameMiddle = "";
		if ( $nameLast == "NULL" ) $nameLast = "";
		if ( $nameSuffix == "NULL" ) $nameSuffix = "";
		$html .= "Name: <b>". $nameTitle ." ". $nameFirst ." ". $nameMiddle ." ". $nameLast ." ". $nameSuffix ."</b><br>";

		// get images for this missing person
		$q2 = "select * from mpres_image where mpres_person_index = '". $index ."';";
		$res2 = $global['db']->Execute($q2);

		$count = 1;
		while($row2 = $res2->FetchRow() ){
			$filename = $row2['mpres_image_filename'];
			$width = $row2['mpres_image_width'];
			$height = $row2['mpres_image_height'];
			$html .= "<a onclick=\"window.open('tmp/original@".$filename."','".$nameFirst." ".$nameLast."','width=".($width+20).",height=".($height+20).",scrollbars=no,status=no');return false;\" href=\"#\" title=\"Click to see the original size\">";
			$html .= "<img src=\"tmp/thumb@". $filename ."\" style=\"margin: 5px;\"></a>";
			$count++;
		}
		$html .= "</div><br>";
	}



/*
	$html .= "from: ".$from."\n";
	$html .= "time: ". $hour.":".$minute.":".$second." ".$year.":".$month.":".$day ."\n";

	$html .= "full(". $subject .")\n";
	$html .= "first(". $n->getFirstName() .") middle(". $n->getMiddleName() .") last(". $n->getLastName() .") suffix(". $n->getSuffix() .") title(". $n->getTitle() .")\n";

	$html .= "<img src=\"tmp/thumb@$filename+$j$ext\"><pre>tmp/thumb@$filename+$j$ext\n";

*/
	if ( $html == "" ) $html = "No results!";
	$global['xajax_res']->addAssign('mpresData','innerHTML',$html);
	return $global['xajax_res']->getXML();
}



///////////////////////////////////////////////////////////////////////////////////////

/*
        //check for save handler
        if($conf['mod_mpr_upload_pic_handler'] == 'database'){
            $size = filesize($_FILES['picture']['tmp_name']);
            $pic = fread(fopen($_FILES['picture']['tmp_name'],"r"),$size);
            $_SESSION['mpr']['entry']['image'] = $pic;
            $_SESSION['mpr']['entry']['image_type'] = $ext;
            $_SESSION['mpr']['entry']['image_height'] = $info[1];
            $_SESSION['mpr']['entry']['image_width'] = $info[0];
        }
*/