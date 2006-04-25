<?php

require_once ($global['approot'].'mod/mpr/tools.inc');

/**
 * shn_home_default 
 * 
 * @access public
 * @return string
 */
function shn_mpr_default()
{
$message = _("
        Welcome to the Sahana FOSS Disaster Management System
        Sahana is an integrated set of pluggable, web based disaster management applications that pr ovide solutions to large-scale humanitarian problems in the aftermath of a disaster. These applications a nd problems they address are as follows:");
    switch ($_GET['stream_type']){
        case 'soap' :
            return $message;
        break;

        case 'xml' :
            return '<description>'.$message.'</description>';
        break;

        default:
            return $message;
        break;

    }
        
}

function shn_mpr_addmp_img()
{
    global $global; 

    //clean clean
    $p_uuid = $_GET['p_uuid'];
    switch ($_GET['stream_type']){
        case 'image' :
            if($_GET['session']){
                shn_image_resize_from_string($_SESSION['mpr']['entry'],100,100);
            }else{
                $sql = "SELECT image, image_type, image_height, image_width FROM person_image WHERE p_uuid ='$p_uuid'";
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
                    if($_GET['thumbnail'])
                        shn_image_resize_from_string($img,100,100);
                    else
                        echo $img['image'];
                }
            }
        break;
    }
}
?>
