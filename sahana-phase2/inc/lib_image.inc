<?php
/* $Id: lib_image.inc,v 1.20 2009-08-22 15:16:00 ravithb Exp $ */

/**
 *
 * This is the database handler. A vital component of the framework.
 * This will be included from the front controller and the reset of the
 * application can use the database resource, available in $global['db']
 * you may need to make it into a global scope. i.e global $global;
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage image
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @author     Greg Miernicki
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


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
function shn_image_resize($src_path,$desc_path,$width,$height) {
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

	$image_p = imagecreatetruecolor($width, $height);

	$func = NULL;
	$func2 = "imagejpeg";

	list(,$mime) = split("\/",$info['mime']);

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

	$image = NULL;

	if($func===NULL){
		$func = "imagecreate";
		$image = $func($width,$height);
	}else{
		$image = $func($src_path);
	}

	imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);

	$func2($image_p,$desc_path,100);
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

	$image_p = imagecreatetruecolor($width, $height);

	$mime = $img['image_type'];
	$image = imagecreatefromstring($img['image']);

	imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
	$func2 = 'image'.$mime;
	$func2($image_p);
}



function shn_show_image_stream($x_uuid, $thumbnail=true, $image=null, $session=false, $category=null, $width=null, $height=null) {

	// 2009:0707 updated this function to allow resizing as with the above function changes
	// the two additional parameters: height, width if not specificed will be created upon the above function call
	// so backwards compatibility with older modules using these functions is maintained
	// -- Greg


	global $global;

	if ($session) {
		shn_image_resize_from_string($image, $width, $height);
	} else {
		if (isset($category)) {
			$sql = "SELECT image, image_type, image_height, image_width FROM image WHERE x_uuid = '$x_uuid' AND category = '$category'";
		} else {
			$sql = "SELECT image, image_type, image_height, image_width FROM image WHERE x_uuid = '$x_uuid' ";
		}
		$arr = $global['db']->GetAll($sql);

		if(!$arr or !$arr[0]['image']){
			//Create the NOT available image
			$img = imagecreatetruecolor($width, $height);
			$bg_color = imagecolorallocate($img,229,229,229);
			imagefill($img,0,0,$bg_color);
			$txt_color = imagecolorallocate($img, 255, 0, 0);
			imagestring($img, 4,20,15, _t("Image"), $txt_color);
			imagestring($img, 4,25,40, _t("Not"), $txt_color);
			imagestring($img, 4,12,65, _t("Available"), $txt_color);
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
 * @param mixed $x_uuid
 * @param mixed $type database, file
 * @param mixed $mod
 * @param mixed $act
 * @param mixed $session
 * @access public
 * @return void
 */
function shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null) {
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
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE x_uuid = '$x_uuid' AND category ='dvr_person'";

			elseif($act=='addfingerprint_img')
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE x_uuid = '$x_uuid' AND category ='finger_print'";

			else
			$sql = "SELECT image_type,image_height, image_width FROM image WHERE x_uuid = '$x_uuid'";
			$arr = $global['db']->GetAll($sql);
			if(isset($arr[0]['image_type']) && $arr[0]['image_type'] != null){
				$type='&imagetype='.$arr[0]['image_type'];
				$height = $arr[0]['image_height']+20;
				$width = $arr[0]['image_width']+20;
			}
			$src_ori = "index.php?stream=image&mod=$mod&act=$act&x_uuid=".$x_uuid.$type;

			$src_tmp = "index.php?stream=image&mod=$mod&act=$act&thumbnail=true&x_uuid=".$x_uuid.$type;
		}
	}else{
		//Since we don't know the extension
		$dir = $global['approot'].'www/tmp/';

		if($type!=null)
		{
			//Need a better way
			$d = dir($dir);
			while (false !== ($f = $d->read())){
				if(preg_match('/thumb_fin'.$x_uuid.'(.*)/',$f,&$matches)){
					$filename = $dir.trim($f);
					$ext = $matches[1];
					break;
				}
			}
			$filename = trim($filename);

			//if image is not available
			if(! file_exists($global['approot']."www/tmp/ori_fin$x_uuid"."$ext") ){
				echo _t("Image Not Available");
				return false;
			}


			$info = getimagesize($global['approot']."www/tmp/ori_fin$x_uuid"."$ext");
			$height = $info[1]+20;
			$width = $info[0]+20;

			$url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
			//remove the index.php
			$url = substr($url,0,strlen($url)-9);
			//add http://
			$src_ori = 'http://'.$url."/tmp/ori_fin$x_uuid"."$ext";
			$src_tmp = "tmp/thumb_fin$x_uuid"."$ext";

		} else {

			//Need a better way
			$d = dir($dir);
			while (false !== ($f = $d->read())){
				if(preg_match('/thumb_'.$x_uuid.'(.*)/',$f,&$matches)){
					$filename = $dir.trim($f);
					$ext = $matches[1];
					break;
				}
			}
			$filename = trim($filename);

			//if image is not available
			if(! file_exists($global['approot']."www/tmp/ori_$x_uuid"."$ext") ){
				echo _t("Image Not Available");
				return false;
			}


			$info = getimagesize($global['approot']."www/tmp/ori_$x_uuid"."$ext");
			$height = $info[1]+20;
			$width = $info[0]+20;

			$url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
			//remove the index.php
			$url = substr($url,0,strlen($url)-9);
			//add http://
			$src_ori = 'http://'.$url."/tmp/ori_$x_uuid"."$ext";
			$src_tmp = "tmp/thumb_$x_uuid"."$ext";

		}

	}
	//echo $src_tmp.'<br>';echo $src_ori;
	?>
<a title="<?php echo  _t('Click to see the original size'); ?>" href="#"
	onclick="window.open('<?php echo $src_ori;?>','hello','width=<?php echo $width?>,height=<?php echo $height?>,scrollbars=no,status=no');return false;">
<img border="0" src="<?php echo $src_tmp;?>" /> </a>
	<?php
	return true;
}



function shn_image_save_to_file($media,$rel_path="res/img/itag",$category="jpeg_maps",$x_uuid,$media_type=null) {
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
	$q="delete from media where x_uuid='$x_uuid' and category='$category'";
	$res=$db->Execute($q);
	$q="insert into media(media_id,x_uuid,url,media_type,media_height,media_width,category) values('$mediaId','$x_uuid','{$uploadfile}','$mime',$height_orig,$width_orig,'$category')";
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
 * @param mixed $image_upload
 * @param mixed $x_uuid
 * @param mixed $replace_id
 * @access public
 * @return void
 */
function shn_image_to_db($image_upload,$x_uuid,$replace_id=null) {
	global $global;

	$info = getimagesize($image_upload['tmp_name']);
	list(,$ext) = split("\/",$info['mime']);

	$size = filesize($image_upload['tmp_name']);
	$image = fread(fopen($image_upload['tmp_name'],"r"),$size);

	$image = addslashes($image);
	$image_type = $ext;
	$image_height = $info[1];
	$image_width = $info[0];

	if($replace_id){
		$sql = "UPDATE image SET
                    image = '$image',
                    image_type = '$image_type',
                    image_height = '$image_height',
                    image_width = '$image_width',
                WHERE image_id = '$replace_id'";
	}else{
		$sql = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width)
                VALUES ('$x_uuid','$image','$image_type','$image_height','$image_width')";
	}

	$global['db']->Execute($sql);
}



/**
 * shn_image_to_db_ex
 *
 * @param mixed $image
 * @param mixed $x_uuid
 * @param mixed $image_type
 * @param mixed $image_height
 * @param mixed $image_width
 * @param mixed $replace_id
 * @access public
 * @return void
 */
function shn_image_to_db_ex($x_uuid,$image,$image_type, $image_height, $image_width,$replace_id=null,$category=null) {
	global $global;

	$image = addslashes($image);

	if($replace_id){
		$sql = "UPDATE image SET image = '$image', image_type = '$image_type', image_height = '$image_height', image_width = '$image_width' 
			WHERE image_id = '$replace_id'";
	} else {
		$sql = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width,category)
			VALUES ('$x_uuid','$image','$image_type','$image_height','$image_width','$category')";
	}
	$global['db']->Execute($sql);
	// exit();
}



/**
 * Get the error description message for an image upload error.
 *
 * @param Integer $error_code The error code
 */
function shn_file_upload_error_msg($error_code) {
	switch($error_code){
		case UPLOAD_ERR_INI_SIZE:
			return _t("The uploaded file exceeds the upload_max_filesize directive in php.ini. (<".ini_get('upload_max_filesize')."B)");
		case UPLOAD_ERR_FORM_SIZE:
			return _t("The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form.");
		case UPLOAD_ERR_PARTIAL:
			return _t("The uploaded file was only partially uploaded.");
		case UPLOAD_ERR_NO_FILE:
			return _t("No file was uploaded.");
		case UPLOAD_ERR_NO_TMP_DIR:
			return _t("Missing a temporary folder.");
		case UPLOAD_ERR_CANT_WRITE:
			return _t("Failed to write file to disk.");
		case UPLOAD_ERR_EXTENSION:
			return _t("File upload stopped by extension.");
	}
}



/**
 * Check if the given mime type of (image) is
 * valid within sahana.
 *
 * @param unknown_type $type The mime type string
 */
function shn_check_valid_image_type($type) {
	$mime = $type;
	if(strpos($type,"/")){
		list(,$mime) = split("\/",$info['mime']);
	}

	// check types.
	if(stripos($mime,"png") || stripos($mime,"gif") || stripos($mime,"jpeg") || stripos($mime,"bmp")) {
		return true;
	} else {
		return false;
	}
}