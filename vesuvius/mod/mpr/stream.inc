<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


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
	$p_uuid = mysql_real_escape_string($_GET['p_uuid']);
	switch ($_GET['stream_type']) {
		case 'image' :
			if($_GET['session']) {
				shn_show_image_stream($p_uuid, true, $_SESSION['mpr']['entry'],true);
			} else {
				if ($_GET['thumbnail']) {
					shn_show_image_stream($p_uuid,true);
				} else {
					shn_show_image_stream($p_uuid,false);
				}
			}
		break;
	}
}