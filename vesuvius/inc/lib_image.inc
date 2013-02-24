<?
/**
 * @name         Image Library
 * @version      1.0
 * @package      framework
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



/**
 * This function resizes a given image and saves it to a destination.
 * @param mixed $src_path
 * @param mixed $desc_path
 * @param mixed $width
 * @param mixed $height
 * @access public
 * @return void
 */
function shn_image_resize($src_path, $desc_path, $width, $height) {
	$info = getimagesize($src_path);
	if(! $info)
	return false;

	$width_orig = $info[0];
	$height_orig = $info[1];

	if ($width && ($width_orig < $height_orig)) {
		$width = ($height / $height_orig) * $width_orig;
	} else {
		$height = ($width / $width_orig) * $height_orig;
	}

	$imageNew = imagecreatetruecolor($width, $height);

	$func = NULL;
	$func2 = "imagejpeg";

	list(,$mime) = explode("/",$info['mime']);

	$mime = strtolower($mime);

	if(stripos($mime,"bmp")!==FALSE){
		// bitmap
		$func =  "imagecreatefromwbmp";
		$func2 = "imagewbmp";
		$quality = null;

	}else if(stripos($mime,"png")!==FALSE){
		// png
		$func = "imagecreatefrompng";
		$func2 = "imagepng";
		$quality = 9;

	}else if(stripos($mime,"jpeg")!==FALSE){
		// jpeg and pjpeg
		$func = "imagecreatefromjpeg";
		$func2 = "imagejpeg";
		$quality = 100;

	}else if(stripos($mime,"gif")!==FALSE){
		// gif
		$func = "imagecreatefromgif";
		$func2 = "imagegif";
		$quality = null;
	}

	$image = NULL;

	if($func===NULL){
		$func = "imagecreate";
		$image = $func($width,$height);
	}else{
		$image = $func($src_path);
	}

	imagecopyresampled($imageNew, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);

	$func2($imageNew, $desc_path, $quality);
}



/**
 *
 * This function can resize a given image (only width a height constraint) and save it to the given location.
 *
 * @param mixed $src_path
 * @param mixed $desc_path
 * @param mixed $height
 * @access public
 * @return void
 */
function shn_image_resize_height($src_path, $desc_path, $height) {
	$info = getimagesize($src_path);
	if(! $info)
	return false;

	$width_orig = $info[0];
	$height_orig = $info[1];

	$width = ($height / $height_orig) * $width_orig;

	$imageNew = imagecreatetruecolor($width, $height);

	$func = NULL;
	$func2 = "imagejpeg";

	list(,$mime) = explode("/",$info['mime']);

	$mime = strtolower($mime);

	if(stripos($mime,"bmp")!==FALSE){
		// bitmap
		$func =  "imagecreatefromwbmp";
		$func2 = "imagewbmp";
		$quality = null;

	}else if(stripos($mime,"png")!==FALSE){
		// png
		$func = "imagecreatefrompng";
		$func2 = "imagepng";
		$quality = 9;

	}else if(stripos($mime,"jpeg")!==FALSE){
		// jpeg and pjpeg
		$func = "imagecreatefromjpeg";
		$func2 = "imagejpeg";
		$quality = 100;

	}else if(stripos($mime,"gif")!==FALSE){
		// gif
		$func = "imagecreatefromgif";
		$func2 = "imagegif";
		$quality = null;
	}

	$image = NULL;

	if($func===NULL){
		$func = "imagecreate";
		$image = $func($width,$height);
	}else{
		$image = $func($src_path);
	}

	imagecopyresampled($imageNew, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);

	if ($quality != null) {
		$func2($imageNew, $desc_path, $quality);
	} else {
		$func2($imageNew, $desc_path);
	}
}



/**
 *
 * This function determines the correct way to add a border to ttf text
 *
 */
function shn_image_imagettfborder($im, $size, $angle, $x, $y, $color, $font, $text, $width) {
	// top
	imagettftext($im, $size, $angle, $x-$width, $y-$width, $color, $font, $text);
	imagettftext($im, $size, $angle, $x,        $y-$width, $color, $font, $text);
	imagettftext($im, $size, $angle, $x+$width, $y-$width, $color, $font, $text);

	// bottom
	imagettftext($im, $size, $angle, $x-$width, $y+$width, $color, $font, $text);
	imagettftext($im, $size, $angle, $x,        $y+$width, $color, $font, $text);
	imagettftext($im, $size, $angle, $x-$width, $y+$width, $color, $font, $text);

	// left
	imagettftext($im, $size, $angle, $x-$width, $y, $color, $font, $text);

	// right
	imagettftext($im, $size, $angle, $x+$width, $y, $color, $font, $text);

	for ($i = 1; $i < $width; $i++) {
		// top line
		imagettftext($im, $size, $angle, $x-$i, $y-$width, $color, $font, $text);
		imagettftext($im, $size, $angle, $x+$i, $y-$width, $color, $font, $text);

		// bottom line
		imagettftext($im, $size, $angle, $x-$i, $y+$width, $color, $font, $text);
		imagettftext($im, $size, $angle, $x+$i, $y+$width, $color, $font, $text);

		// left line
		imagettftext($im, $size, $angle, $x-$width, $y-$i, $color, $font, $text);
		imagettftext($im, $size, $angle, $x-$width, $y+$i, $color, $font, $text);

		// right line
		imagettftext($im, $size, $angle, $x+$width, $y-$i, $color, $font, $text);
		imagettftext($im, $size, $angle, $x+$width, $y+$i, $color, $font, $text);
	}
}



/**
 *
 * This function can resize a given image and save it to the given
 * location.
 *
 * @param mixed $src_path
 * @param mixed $desc_path
 * @param mixed $width
 * @param mixed $height
 * @access public
 * @return void
 */
function shn_image_resize_from_string($img, $width, $height) {
	global $global;

	// 2009:0707 updated this function to allow the generation
	// of images of any size, not just the 100x100 thumbnails

	$width_orig = $img['image_width'];
	$height_orig = $img['image_height'];

	// first we do a check and see if they are asking for a 100x100 thumbnail
	// this is for backwards compatibility allowing older modules to still use
	// the old functionality
	// in this case, we use the old algorithm:
	// -- Greg

	if (($height == 100) && ($width == 100)) {
		if ($width && ($width_orig < $height_orig)) {
			$width = ($height / $height_orig) * $width_orig;
		} else {
			$height = ($width / $width_orig) * $height_orig;
		}
	}

	// Next, if width and height are both not specified, we will set them both to 100 and
	// then use the old algorithm again

	elseif (($height == null) && ($width == null)) {
		$height = 100;
		$width = 100;
		if ($width && ($width_orig < $height_orig)) {
			$width = ($height / $height_orig) * $width_orig;
		} else {
			$height = ($width / $width_orig) * $height_orig;
		}
	}

	// NEW FEATURE 1 :: if either of the height or width are not specified, we will
	// resize by finding the ratio of the parameter specified and apply this ratio to the
	// other missing parameter (aspect ratio maintained during resize)

	elseif (($height == null) || ($width == null)) {
		if ($height == null) {
			$height = $height_orig * ($width/$width_orig);
		} else {
			$width = $width_orig * ($height/$height_orig);
		}
	}

	// NEW FEATURE 2 :: if both width and height are specified (and they are not both 100)
	// then we will allow for a specific width and height resize
	// (not in this case, aspect ratio may not be maintained and the function calling this
	// one has to take this into account)

	else {
		// nothing :)
	}

	$imageNew = imagecreatetruecolor($width, $height);
	imagealphablending($imageNew, true);

	$mime = $img['image_type'];
	$image = imagecreatefromstring($img['image']);

	imagecopyresampled($imageNew, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
	$func = NULL;
	$func2 = "imagejpeg";

	//list(,$mime) = split("\/",$info['mime']); // removed greg ~ $info undefined? and split() deprecated

	$mime = strtolower($mime);

	if(stripos($mime,"bmp")!==FALSE){
		// bitmap
		$func =  "imagecreatefromwbmp";
		$func2 = "imagewbmp";

	}else if(stripos($mime,"png")!==FALSE){
		// png
		$func = "imagecreatefrompng";
		$func2 = "imagepng";

	}else if(stripos($mime,"jpeg")!==FALSE){
		// jpeg and pjpeg
		$func = "imagecreatefromjpeg";
		$func2 = "imagejpeg";

	}else if(stripos($mime,"gif")!==FALSE){
		// gif
		$func = "imagecreatefromgif";
		$func2 = "imagegif";
	}








	//$func2 = 'image'.strtolower($mime);

	// additional image overlay routines

	// bottom TEXT ///////////////////////////////////////////////////////////////////////////////////////////
	if (isset($_GET['overlay_bottom'])) {
		$font =  $global['approot']."www/res/ttf/arial.ttf";

		// setup text overlay colors
		$white = imagecolorallocatealpha($imageNew, 255, 255, 255, 0);
		$black = imagecolorallocatealpha($imageNew, 0, 0, 0, 111);

		// largest point size to allow for the bottom font
		$fontSize = 24;

		// scale down point by point until we determine the correct size from the bounding box for the bottom text
		$found = FALSE;
		while (!$found) {
			$bbox = imagettfbbox($fontSize, 0, $font, $_GET['overlay_bottom']);
			if ($bbox[2] < $width - 12) {
				$found = TRUE;
			} else {
				$fontSize--;
			}
		}
		$x = ($width - $bbox[2]) / 2;
		$y = $height - $bbox[3] / 2 - 5;

		// draw 4 pixel black border below the bottom text
		shn_image_imagettfborder($imageNew, $fontSize, 0, $x, $y, $black, $font, $_GET['overlay_bottom'], $fontSize/8);

		// draw the bottom text
		imagettftext($imageNew, $fontSize, 0, $x, $y, $white, $font, $_GET['overlay_bottom']);
	}

	// overlay triangle tag with a given color /////////////////////////////////////////////////////////////////////
	if (isset($_GET['triangle'])) {
		$r = sscanf($_GET['triangle'], '%2x%2x%2x');
		$white    = imagecolorallocate($imageNew, 255, 255, 255);
		$gray    = imagecolorallocate($imageNew,  127, 127, 127);
		$tagColor = imagecolorallocate($imageNew, $r[0], $r[1], $r[2]);
		$triangleSize = $height / 6;
		$values1 = array(0, 0, $triangleSize+4, 0, 0, $triangleSize+4);
		$values2 = array(0, 0, $triangleSize,   0, 0, $triangleSize  );
		$values3 = array(0, 0, $triangleSize,   0, 0, $triangleSize  );
		if (0) { //$_GET['triangle'] !== "000000") {
			imagefilledpolygon($imageNew, $values1, 3, $gray);
			imagefilledpolygon($imageNew, $values3, 3, $tagColor);
		} else {
			//imagefilledpolygon($imageNew, $values1, 3, $white);
			imagefilledpolygon($imageNew, $values2, 3, $tagColor);
		}
		//imagefilledpolygon($imageNew, $values2, 3, $tagColor);
	}


	// top TEXT ///////////////////////////////////////////////////////////////////////////////////////////////////
	if (isset($_GET['overlay_top'])) {

		$font =  $global['approot']."www/res/ttf/arial.ttf";

		// setup text overlay colors
		$white = imagecolorallocatealpha($imageNew, 255, 255, 255, 0);
		$black = imagecolorallocatealpha($imageNew, 0, 0, 0, 111);

		// largest point size to allow for the top font
		$fontSize = 24;

		// scale down point by point until we determine the correct size from the bounding box for the top text
		$found = FALSE;
		while (!$found) {
			$bbox = imagettfbbox($fontSize, 0, $font, $_GET['overlay_top']);
			if ($bbox[2] < $width - 12) {
				$found = TRUE;
			} else {
				$fontSize--;
			}
		}
		$x = ($width - $bbox[2]) / 2;
		$y = $fontSize+5; //$bbox[6]; // /2+$fontSize;

		// draw 4 pixel border around the text
		shn_image_imagettfborder($imageNew, $fontSize, 0, $x, $y, $black, $font, $_GET['overlay_top'], ($fontSize/8));

		// draw the text
		imagettftext($imageNew, $fontSize, 0, $x, $y, $white, $font, $_GET['overlay_top']);
	}

	// add Location Icon /////////////////////////////////////////////////////////////////////////////////////////////
	if (isset($_GET['location'])) {
			$icon = imagecreatefrompng("../www/theme/lpf/img/".$_GET['location']);
			imagecopyresampled($imageNew, $icon, $width-25, 0, 0, 0, 25, 25, 50, 50);
	}

	$func2($imageNew);
}



function shn_show_image_stream($p_uuid, $thumbnail=true, $image=null, $session=false, $width=null, $height=null) {

	// 2009:0707 updated this function to allow resizing as with the above function changes
	// the two additional parameters: height, width if not specificed will be created upon the above function call
	// so backwards compatibility with older modules using these functions is maintained
	// -- Greg


	global $global;

	if ($session) {
		shn_image_resize_from_string($image, $width, $height);
	} else {
		$sql = "SELECT image, image_type, image_height, image_width FROM image WHERE p_uuid = '$p_uuid' ";
		$arr = $global['db']->GetAll($sql);

		if(!$arr or !$arr[0]['image']){
			//Create the NOT available image
			$img = imagecreatetruecolor($width, $height);
			$bg_color = imagecolorallocate($img,229,229,229);
			imagefill($img,0,0,$bg_color);
			$txt_color = imagecolorallocate($img, 255, 0, 0);
			imagestring($img, 4,20,15, _t("Image-text|Image"), $txt_color);
			imagestring($img, 4,25,40, _t("Image-text|Not"), $txt_color);
			imagestring($img, 4,12,65, _t("Image-text|Available"), $txt_color);
			imagejpeg($img);
			imagedestroy($img);
		}else{
			$img['image'] = $arr[0]['image'];
			$img['image_width'] = $arr[0]['image_width'];
			$img['image_height'] = $arr[0]['image_height'];
			$img['image_type'] = $arr[0]['image_type'];
			if ($thumbnail) {
				shn_image_resize_from_string($img, $width, $height);
			} else {
				echo $img['image'];
			}
		}
	}
}



/**
 *
 * This function shows the thumbnail if available and says "Image not
 * available" otherwise
 *
 * @param mixed $p_uuid
 * @param mixed $type database, file
 * @param mixed $mod
 * @param mixed $act
 * @param mixed $session
 * @access public
 * @return void
 */
function shn_show_thumb_url($p_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null) {
	global $global;
	global $conf;

	if(is_null($mod))
	$mod = $global['module'];
	if(is_null($act))
	$act = $global['act'];

	if($stream_type == 'database'){
		if($session){
			$src_ori = "index.php?stream=image&mod=$mod&act=$act&session=true";
			$src_tmp = "index.php?stream=image&mod=$mod&act=$act&session=true&thumbnail=true";
		}else{
			//need to get the type
            if($act=='addvictim_img')
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE p_uuid = '$p_uuid'";

			elseif($act=='addfingerprint_img')
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE p_uuid = '$p_uuid'";

			else
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE p_uuid = '$p_uuid'";
			$arr = $global['db']->GetAll($sql);
			if(isset($arr[0]['image_type']) && $arr[0]['image_type'] != null){
				$type='&imagetype='.$arr[0]['image_type'];
				$height = $arr[0]['image_height']+20;
				$width = $arr[0]['image_width']+20;
			}
			$src_ori = "index.php?stream=image&mod=$mod&act=$act&p_uuid=".$p_uuid.$type;

			$src_tmp = "index.php?stream=image&mod=$mod&act=$act&thumbnail=true&p_uuid=".$p_uuid.$type;
		}
	}else{
		//Since we don't know the extension
		$dir = $global['approot'].'www/tmp/';

		if($type!=null)
		{
			//Need a better way
			$d = dir($dir);
			while (false !== ($f = $d->read())){
				if(preg_match('/thumb_fin'.$p_uuid.'(.*)/',$f,$matches)){
					$filename = $dir.trim($f);
					$ext = $matches[1];
					break;
				}
			}
			$filename = trim($filename);

			//if image is not available
			if(! file_exists($global['approot']."www/tmp/ori_fin$p_uuid"."$ext") ){
				echo _t("Image-text|Image Not Available");
				return false;
			}


			$info = getimagesize($global['approot']."www/tmp/ori_fin$p_uuid"."$ext");
			$height = $info[1]+20;
			$width = $info[0]+20;

			$url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
			//remove the index.php
			$url = substr($url,0,strlen($url)-9);
			//add http://
			$src_ori = 'http://'.$url."/tmp/ori_fin$p_uuid"."$ext";
			$src_tmp = "tmp/thumb_fin$p_uuid"."$ext";

		} else {

			//Need a better way
			$d = dir($dir);
			while (false !== ($f = $d->read())){
				if(preg_match('/thumb_'.$p_uuid.'(.*)/',$f,$matches)){
					$filename = $dir.trim($f);
					$ext = $matches[1];
					break;
				}
			}
			$filename = trim($filename);

			//if image is not available
			if(! file_exists($global['approot']."www/tmp/ori_$p_uuid"."$ext") ){
				echo _t("Image-text|Image Not Available");
				return false;
			}


			$info = getimagesize($global['approot']."www/tmp/ori_$p_uuid"."$ext");
			$height = $info[1]+20;
			$width = $info[0]+20;

			$url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
			//remove the index.php
			$url = substr($url,0,strlen($url)-9);
			//add http://
			$src_ori = 'http://'.$url."/tmp/ori_$p_uuid"."$ext";
			$src_tmp = "tmp/thumb_$p_uuid"."$ext";

		}

	}
	//echo $src_tmp.'<br>';echo $src_ori;
	?>
<a title="<?php echo  _t('Image-text|Click to see the original size'); ?>" href="#"
	onclick="window.open('<?php echo $src_ori;?>','hello','width=<?php echo $width?>,height=<?php echo $height?>,scrollbars=no,status=no');return false;">
<img border="0" src="<?php echo $src_tmp;?>" /> </a>
	<?php
	return true;
}



function shn_image_save_to_file($media,$rel_path="res/img/itag",$p_uuid,$media_type=null) {
	global $global;

	$info = getimagesize($_FILES[$media]['tmp_name']);
	//check the image type
	if (! $info) {
		add_error(_("Invalid Image Type Please try again"));
		return false;
	} else {
		$width_orig = $info[0];
			$height_orig = $info[1];
			list($ignore,$mime) = split("\/",$info['mime']);
		//$mime = $_FILES[$media]["name"]['image_type'];
	}
	// list($ignore,$ext) = split("\/",$info['mime']);

	//putting a dot ;-)
	//   $ext = '.'.$ext;
	$upload_dir = $global['approot'].$rel_path;
	$mediaId=shn_create_uuid("media");


	$uploadfile=$upload_dir ."/". $mediaId.".".$mime;
	if (file_exists($uploadfile)) {
		add_error($_FILES[$media]["name"] . " already exists. ");
		return;
	}

	move_uploaded_file($_FILES[$media]['tmp_name'], $uploadfile);
	$db=$global['db'];
	$q="delete from media where p_uuid='$p_uuid'";
	$res=$db->Execute($q);
	$q="insert into media(media_id,p_uuid,url,media_type,media_height,media_width) values('$mediaId','$p_uuid','{$uploadfile}','$mime',$height_orig,$width_orig)";
	$res=$db->Execute($q);
	if ($res==false) {
		return null;
	} else {
		add_confirmation($_FILES[$media]["name"]." was properly saved, in the file system");
		return true;
	}
}



function shn_media_get_url($media_id) {
	global $global;
	$db=$global['db'];
	$query="SELECT url FROM media WHERE media_id ='{$media_id}'";
	file_put_contents("/tmp/a.txt",$query);
	$res=$db->Execute($query);
	return $res->fields["url"];
}



function _shn_image_media_get($media_id) {
	global $global;
	$url=shn_media_get_url($_GET["media_id"]);
	$info = getimagesize($url);
	//check the image type
	if(! $info){
		add_error(_("Invalid Image Type Please try again"));
		return false;
	} else {
		$width_orig = $info[0];
		$height_orig = $info[1];
		list($ignore,$mime) = split("\/",$info['mime']);
		//$mime = $_FILES[$media]["name"]['image_type'];
	}
	switch($mime=="png"){
		case "png":
			$image = imagecreatefrompng($url);
			imagepng($image);
			break;
		default:
			$image = imagecreatefromjpeg($url);
			imagejpeg($image);
			break;
	}
}

/**
 * shn_image_to_db
 *
 * @param mixed $p_uuid
 * @param mixed $image_type
 * @param mixed $image_height
 * @param mixed $image_width
 * @param string $url
 * @param string $thumbUrl
 * @param string $original_filename
 * @access public
 * @return void
 */
function shn_image_to_db($p_uuid,$image_type, $image_height, $image_width,$url=null,$thumbUrl=null,$original_filename=null,$replace_id=null) {
   global $global;

   // Insert image info.
   $image_id = shn_create_uuid("image");
   $sql = "INSERT INTO image (image_id, p_uuid, image_type, image_height, image_width,url, url_thumb, original_filename, principal)
		VALUES ($image_id,'$p_uuid','$image_type','$image_height','$image_width','$url','$thumbUrl','$original_filename',TRUE)";
   $global['db']->Execute($sql);
   $msg = $global['db']->ErrorMsg();
   if (!empty($msg)) {
      throw new RuntimeException($msg);
   }
}

/**
 * Get the error description message for an image upload error.
 *
 * @param Integer $error_code The error code
 */
function shn_file_upload_error_msg($error_code) {
	switch($error_code){
		case UPLOAD_ERR_INI_SIZE:
			return _t("Image-Upload-Error|The uploaded file exceeds the upload_max_filesize directive in php.ini. (<".ini_get('upload_max_filesize')."B)");
		case UPLOAD_ERR_FORM_SIZE:
			return _t("Image-Upload-Error|The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form.");
		case UPLOAD_ERR_PARTIAL:
			return _t("Image-Upload-Error|The uploaded file was only partially uploaded.");
		case UPLOAD_ERR_NO_FILE:
			return _t("Image-Upload-Error|No file was uploaded.");
		case UPLOAD_ERR_NO_TMP_DIR:
			return _t("Image-Upload-Error|Missing a temporary folder.");
		case UPLOAD_ERR_CANT_WRITE:
			return _t("Image-Upload-Error|Failed to write file to disk.");
		case UPLOAD_ERR_EXTENSION:
			return _t("Image-Upload-Error|File upload stopped by extension.");
	}
}



/**
 * Check if the given mime type of (image) is
 * valid within sahana.
 *
 * @param unknown_type $type The mime type string
 * @todo split has been deprecated. Replace with preg_split, str_split or explode as appropriate.
 * Edited: ccornwell 8/19/2010 : replaced deprecated split with explode. Fixed typo in array_search
 */
function shn_check_valid_image_type($type) {
	$mime = $type;
	if(strpos($type,"/")){
		list(,$mime) = explode("/",$type);
	}

	// check types.
    if(array_search($mime,array('png','gif','jpeg','bmp')) === false ){
        return false;
	} else {
		return true;
	}
}
