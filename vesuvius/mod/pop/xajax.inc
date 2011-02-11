<?php
/**
 * POP module's xajax library
 *
 * @package	module
 * @subpackage	pop
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

global $global;
// register publicly accessible xajax funtions
array_push($global['xajax_functions'],'pop_getBusy');
array_push($global['xajax_functions'],'pop_getData');

function pop_getBusy(){
	global $global;
	//$d = print_r($global, TRUE); // <br><pre>'.$d.'</pre>
	$global['xajax_res']->addAssign('downloadButton','style.display','none');
	$global['xajax_res']->addAssign('popData','innerHTML','<br><br><br><div style="border: 1px solid green; background-color: #E5FFE5; padding: 15px;"><center><span style="color: green; font-weight: bold; font-size: 20px;"><blink>Downloading Emails...</blink></span></center></div>');
	return $global['xajax_res']->getXML();
}



function pop_getData( $download = 1 ){
	global $global;
	$html = "";

/////// DOWNLOAD EMAILS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( $download == 1 ) {

		// get configuration settings
		$q = "select * from pop_settings where pop_index = '0'";
		$res = $global['db']->Execute($q);
		$host		= $res->fields['pop_host'];
		$port		= $res->fields['pop_port'];
		$popimap	= $res->fields['pop_popimap'];
		$ssl		= $res->fields['pop_ssl'];
		$username	= $res->fields['pop_username'];
		$password 	= $res->fields['pop_password'];
		$attachments	= $res->fields['pop_attachments'];
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
			$global['xajax_res']->addAssign('popData','innerHTML','<br><br><br><div style="border: 1px solid red; background-color: #ffaaaa; padding: 15px;"><center><span style="color: red; font-weight: bold; font-size: 20px;"><blink>Error accessing email account... Please check email settings.</blink></span></center></div>');
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

			include_once($global['approot']."mod/pop/nameParser.php");
			$name = new nameParser( $subject );

			// MySQL retrieves and displays DATETIME values in 'YYYY-MM-DD HH:MM:SS' format.
			$pop_person['pop_person_emailDateTime']	= $year ."-". $month ."-". $day ." ". $hour .":". $minute .":". $second;
			$pop_person['pop_person_emailSubject']	= $subject;
			$pop_person['pop_person_emailFrom']		= $from;
			$pop_person['pop_person_nameFirst']		= $name->getFirstName();
			$pop_person['pop_person_nameMiddle']	= $name->getMiddleName();
			$pop_person['pop_person_nameLast']		= $name->getLastName();
			$pop_person['pop_person_nameTitle']		= $name->getTitle();
			$pop_person['pop_person_nameSuffix']	= $name->getSuffix();
			shn_db_insert($pop_person,'pop_person',true);

			// get the id of the last inserted item
			$q = "select * from pop_person order by pop_person_index DESC limit 1;";
			$res = $global['db']->Execute($q);
			$personIndex = $res->fields['pop_person_index'];

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
							$pop_image['pop_person_index']	= $personIndex;
							$pop_image['pop_image_image']	= $fileContent;
							$pop_image['pop_image_type']	= $mime;
							$pop_image['pop_image_height']	= $height;
							$pop_image['pop_image_width']	= $width;
							$pop_image['pop_image_filename']	= $filename."+".$j.$ext;
							shn_db_insert($pop_image,'pop_image',true);
						}
					}
				}
			}
		}
		imap_close($mbox);
	}

/////// FORMAT TABLE DATA FOR DISPLAY IN MODULE ////////////////////////////////////////////////////////////////////////////////////////////////////

	// get configuration settings
	$q = "select * from pop_person order by pop_person_emailDateTime desc;";
	$res = $global['db']->Execute($q);

	while($row = $res->FetchRow() ){
		$index		= $row['pop_person_index'];
		$emailDateTime	= $row['pop_person_emailDateTime'];
		$emailSubject	= $row['pop_person_emailsubject'];
		$emailFrom	= $row['pop_person_emailFrom'];
		$nameFirst	= $row['pop_person_nameFirst'];
		$nameMiddle	= $row['pop_person_nameMiddle'];
		$nameLast	= $row['pop_person_nameLast'];
		$nameTitle	= $row['pop_person_nameTitle'];
		$nameSuffix	= $row['pop_person_nameSuffix'];

		$html .= '<div style="background-color: #F3F6FF; border: 1px solid #C6D1F5; padding: 15px;">';
		$html .= 'Recieved: <b>'. $emailDateTime .'</b><br>From: <b>'. $emailFrom .'</B><hr style="border: none; background-color: #C6D1F5; height: 1px;">';
		if ( $nameTitle == "NULL" ) $nameTitle = "";
		if ( $nameFirst == "NULL" ) $nameFirst = "";
		if ( $nameMiddle == "NULL" ) $nameMiddle = "";
		if ( $nameLast == "NULL" ) $nameLast = "";
		if ( $nameSuffix == "NULL" ) $nameSuffix = "";
		$html .= "Name: <b>". $nameTitle ." ". $nameFirst ." ". $nameMiddle ." ". $nameLast ." ". $nameSuffix ."</b><br>";

		// get images for this missing person
		$q2 = "select * from pop_image where pop_person_index = '". $index ."';";
		$res2 = $global['db']->Execute($q2);

		$count = 1;
		while($row2 = $res2->FetchRow() ){
			$filename = $row2['pop_image_filename'];
			$width = $row2['pop_image_width'];
			$height = $row2['pop_image_height'];
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
	$global['xajax_res']->addAssign('popData','innerHTML',$html);
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