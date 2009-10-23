<?php

require_once ($global['approot'].'mod/mpr/tools.inc');
require_once ($global['approot'].'inc/lib_image.inc');

/**
 * shn_home_default 
 * 
 * @access public
 * @return string
 */
function shn_mpr_default() {
	$message = _t("Welcome to the Sahana FOSS Disaster Management System Sahana is an integrated set of pluggable, web based disaster management applications that pr ovide solutions to large-scale humanitarian problems in the aftermath of a disaster. These applications a nd problems they address are as follows:");
	switch ($_GET['stream_type']) {
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



function shn_mpr_addmp_img() {
	global $global; 

	// clean clean
	$x_uuid = $_GET['x_uuid'];
	switch ($_GET['stream_type']) {
		case 'image' :
			if($_GET['session']) {
				shn_show_image_stream($x_uuid, true, $_SESSION['mpr']['entry'],true);
			} else {
				if ($_GET['thumbnail']) {
					shn_show_image_stream($x_uuid,true); 
				} else {
					shn_show_image_stream($x_uuid,false); 
				}
			}
		break;
	}
}