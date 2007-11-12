<?php 
/* $Id: lib_image.inc,v 1.6 2007-11-12 09:06:49 isurunishan Exp $ */

/**
 *
 * This is the database handler. A vital component of the framework.
 * This will be included from the front controller and the reset of the 
 * application can use the database resourse, availabe in $global['db'] 
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
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

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

/* {{{ Image Resize From String */
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


function shn_show_image_stream($x_uuid, $thumbnail=true, $image=null,$session=false)
{
    global $global;    

    if($session){
        shn_image_resize_from_string($image, 100, 100);
    }else{
        $sql = "SELECT image, image_type, image_height, image_width FROM image WHERE x_uuid = '$x_uuid' ";
        $arr = $global['db']->GetAll($sql);

        if(!$arr){
			//Create the NOT available image
			$img = imagecreatetruecolor(100,100);
			$bg_color = imagecolorallocate($img,229,229,229);
			imagefill($img,0,0,$bg_color);
			$txt_color = imagecolorallocate($img, 255, 0, 0);
			imagestring($img, 4,20,15, _("Image"), $txt_color);
			imagestring($img, 4,25,40, _("Not"), $txt_color);
			imagestring($img, 4,12,65, _("Available"), $txt_color);
			imagejpeg($img);
			imagedestroy($img);
        }else{
			$img['image'] = $arr[0]['image'];
			$img['image_width'] = $arr[0]['image_width'];
			$img['image_height'] = $arr[0]['image_height'];
			$img['image_type'] = $arr[0]['image_type'];
			if($thumbnail)
			    shn_image_resize_from_string($img,100,100);
			else
			    echo $img['image'];
        }
    }

}

/* {{{ Show Thumbnail URL */
/**
 *
 * This is function show the tumbnail if available and say "Image not
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
function shn_show_thumb_url($x_uuid,$stream_type,$mod=null,$act=null,$session=false,$type=null)
{
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
            
            $sql = "SELECT image_type,image_height, image_width FROM image WHERE x_uuid = '$x_uuid'";
            $arr = $global['db']->GetAll($sql);
            if(isset($arr[0]['image_type'])){
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
	        echo _("Image Not Available");
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
  
 }
 
 
 else
 {
 	
 	
 	
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
	        echo _("Image Not Available");
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
    //echo $src_tmp;
?>
    <a title="<?= _('Click to see the original size'); ?>" href="#" onclick="window.open('<?=$src_ori;?>','hello','width=<?=$width?>,height=<?=$height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="<?=$src_tmp;?>" />
    </a>
<?php
    return true;
}
/* }}} */

/* {{{ Image to DB */
/**
 * shn_image_to_db 
 * 
 * @param mixed $image_upload 
 * @param mixed $x_uuid 
 * @param mixed $replace_id 
 * @access public
 * @return void
 */
function shn_image_to_db($image_upload,$x_uuid,$replace_id=null)
{
    global $global;

    $info = getimagesize($image_upload['tmp_name']);   
    list($ignore,$ext) = split("\/",$info['mime']);

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
/* }}} */

/* {{{ Image to DB Extended */
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
 
 
function shn_image_to_db_ex($x_uuid,$image,$image_type, $image_height, $image_width,$replace_id=null,$category=null)
{
    global $global;
    
    $image = addslashes($image);
    
    if($replace_id){
        $sql = "UPDATE image SET 
                    image = '$image',
                    image_type = '$image_type',
                    image_height = '$image_height',
                    image_width = '$image_width',
                WHERE image_id = '$replace_id'";
    }else{
        $sql = "INSERT INTO image (x_uuid, image, image_type, image_height, image_width,category) 
                VALUES ('$x_uuid','$image','$image_type','$image_height','$image_width','$category')";
    }
    $global['db']->Execute($sql);
   // exit();
}
/* }}} */
?>
