<?php
/**
 * 
 * This file represents the streaming
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

require_once ($global['approot'].'inc/lib_image.inc');

/**
 * shn_home_default 
 * 
 * @access public
 * @return string
 */
function shn_dvr_default()
{
    $message = _t("
        Welcome to the Sahana FOSS Disaster Management System
        Sahana is an integrated set of pluggable, web based disaster management applications that provide solutions to large-scale humanitarian problems in the aftermath of a disaster. These applications a nd problems they address are as follows:");
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

function shn_dvr_addvictim_img()
{
    global $global; 

    
    $x_uuid = $_GET['x_uuid'];
    switch ($_GET['stream_type']){
        case 'image' :
            if($_GET['session']){
                shn_show_image_stream($x_uuid, true, $_SESSION['dvr']['person']['image'],true);
            }else{
                if($_GET['thumbnail'])
                    shn_show_image_stream($x_uuid,true); 
                else
                    shn_show_image_stream($x_uuid,false); 
            }
     break;
    }
}
    
function shn_dvr_addfingerprint_img()
{
    global $global; 

    
    $x_uuid = $_GET['x_uuid'];
    switch ($_GET['stream_type']){
        case 'image' :
            if($_GET['session']){
                shn_show_image_stream($x_uuid, true, $_SESSION['dvr']['person']['finger_image'],true);
            }else{
                if($_GET['thumbnail'])
                    shn_show_image_stream($x_uuid,true); 
                else
                    shn_show_image_stream($x_uuid,false); 
            }
     break;
    }
    
}

