<?php

/* {{{ Show Thumbnail */
/**
 *
 * This is function show the tumbnail if available and say "Image not
 * available" otherwise
 *
 * @todo Need to move to a different file, possibly to a library.
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_show_thumb($p_uuid,$session=false)
{
    global $global;
    global $conf;

    if($conf['mod_mpr']['upload_picture']['savehandler'] == 'database'){
        if($session && $_SESSION['mpr']['entry']['image']){
	        $src_ori = "stream.php?stream_type=image&mod=mpr&act=addmp_img&session=true";
            $src_tmp = "stream.php?stream_type=image&mod=mpr&act=addmp_img&session=true&thumbnail=true";
        }else{
            //need to get the type
            $sql = "SELECT image_type,image_height, image_width FROM person_image WHERE p_uuid = '$p_uuid'";
            $arr = $global['db']->GetAll($sql);
            if(isset($arr[0]['image_type'])){
                $type='&imagetype='.$arr[0]['image_type'];
                $height = $arr[0]['image_height']+20;
                $width = $arr[0]['image_width']+20;
            } 
	        $src_ori = "stream.php?stream_type=image&mod=mpr&act=addmp_img&p_uuid=".$p_uuid.$type;
            $src_tmp = "stream.php?stream_type=image&mod=mpr&act=addmp_img&thumbnail=true&p_uuid=".$p_uuid.$type;
        }
    }else{
        //Since we don't know the extension
        $dir = $global['approot'].'www/tmp/';
 
        //Need a better way
        $d = dir($dir);
        while (false !== ($f = $d->read())){
            if(preg_match('/thumb_'.$p_uuid.'(.*)/',$f,&$matches)){
                $filename = $dir.trim($f);
                $ext = $matches[1];
                break; 
            }
        }
        $filename = trim($filename);
    
	    //if image is not available 
	    if(! file_exists($global['approot']."www/tmp/ori_$p_uuid"."$ext") ){
	        echo _("Image Not Available");
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
?>
    <a title="<?= _('Click to see the original size'); ?>" href="#" onclick="window.open('<?=$src_ori;?>','hello','width=<?=$width?>,height=<?=$height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="<?=$src_tmp;?>" />
    </a>
<?php
    return true;
}
/* }}} */

/* {{{ get field option description */
/**
 *
 * Shows the Description of the field_option, when given the vaule
 *
 * @todo Need to move this to a library.
 * @param mixed $value 
 * @param mixed $field_name 
 * @access public
 * @return void
 */
function shn_get_field_opt($value,$field_name)
{

    global $global;
    return $global['db']->GetOne("SELECT option_description FROM field_options WHERE option_code = '$value' AND field_name='$field_name'");
}
/* }}} */

/* {{{ Image Resize */
/**
 *
 * This function can resize a given image and save it to the given
 * location. 
 *
 * @todo Need to move this out to a library, e.g. image library
 * @param mixed $src_path 
 * @param mixed $desc_path 
 * @param mixed $width 
 * @param mixed $height 
 * @access public
 * @return void
 */
function shn_image_resize($src_path,$desc_path,$width,$height)
{
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

    list($ignore,$mime) = split("\/",$info['mime']);
    $func = 'imagecreatefrom'.$mime;
    $image = $func($src_path);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p,$desc_path,100);
}
/* }}} */

/* {{{ Image Resize DB */
/**
 *
 * This function can resize a given image and save it to the given
 * location. 
 *
 * @todo Need to move this out to a library, e.g. image library
 * @param mixed $src_path 
 * @param mixed $desc_path 
 * @param mixed $width 
 * @param mixed $height 
 * @access public
 * @return void
 */
function shn_image_resize_from_string($img,$width,$height)
{
    
    $width_orig = $img['image_width'];
    $height_orig = $img['image_height'];

    if ($width && ($width_orig < $height_orig)) {
       $width = ($height / $height_orig) * $width_orig;
    } else {
       $height = ($width / $width_orig) * $height_orig;
    }
    
    $image_p = imagecreatetruecolor($width, $height);

    $mime = $img['image_type'];
    $image = imagecreatefromstring($img['image']);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p);
}
/* }}} */

/* {{{ Image To Database */

function _shn_mpr_image_to_db($p_uuid,$pic,$type,$height,$width,$replace_id=null)
{    
    global $global;
    
    $pic = addslashes($pic);
    
    if($replace_id){
        $sql = "UPDATE person_image SET 
                    image = '$pic',
                    image_type = '$type',
                    image_height = '$height',
                    image_width = '$width',
                WHERE image_id = '$replace_id'";
    }else{
        $sql = "INSERT INTO person_image (p_uuid, image, image_type, image_height, image_width) 
                VALUES ('$p_uuid','$pic','$type','$height','$width')";
    }
    
    $global['db']->Execute($sql);
    
}
    
/* }}} */

?>
