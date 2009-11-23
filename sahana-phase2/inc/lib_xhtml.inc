<?php
/**
* Sahana front controller, through which all actions are dispatched
* Sahana - http://sahana.sourceforge.net
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage handler
* @author     http://www.linux.lk/~chamindra & Tim McNamara
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


/**
 * shn_display_xhtml_head
 *
 * @param $arrPostfix array stores the list of lines you want to insert into the header
 * @param $theme string decides on what css theme you are using
 * @param $title string if you want to change it from the default
 */

function shn_display_xhtml_head( $arrPostfix = null, $theme = null, $title = null ) {
	global $conf;
	global $global;

	# if the database is configured, then select the
	# incident's name from the database via ADODB.
	if ($global['db'] == TRUE){
		# get an array of current incidents, and store them
		# in the $title_result variable
		$sql_incident = "SELECT name FROM incident a inner JOIN user_preference b ON a.incident_id = b.value WHERE b.p_uuid = '{$_SESSION['user_id']}' AND b.pref_key = 'incident_id' ";
		$title_result = $global['db']->GetAll($sql_incident);

		$title_part_1 = $conf['mod_'.$global['module'].'_name']; # the current module
		$title_part_2 = $title_result[0]['name'];                # the current incident
		$title_part_3 = (shn_db_get_config("base", "alternate_title_string")!== FALSE) ? shn_db_get_config("base", "alternate_title_string") : _t("Sahana FOSS Disaster Management System");

		#if an incident has been created
		if ( count($title_result) != 0) {
			#use all three parts
			if (shn_db_get_config("base","alternate_title_method") === "TRUE") {
				$title = $title_part_3." :: ".$title_part_1." :: ".$title_part_2;
			} else {
				$title = $title_part_1." - ".$title_part_2." - ".$title_part_3;
			}
		} else {
			# otherwise, simply use the module name and Sahana's full name
			$title = $title_part_1." - ".$title_part_3;
		}
	} else {
		# Simply use Sahana's name as the title if a disaster
		# has not yet been set.
		$title = $title_part_3;
	}

	# set the theme if it is not given as a parameter
	$theme || $theme = $conf['theme'];
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title><?php echo _t($title)."\n";?></title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="Software " content="Sahana Free and Open Source Disaster Management System" />
<meta name="Website" content="http://www.sahana.lk/" />
<meta name="Copyright Owner" content="Lanka Software Foundation" />
<meta name="Licence" content="Lesser General Public Licence, Version 2.1" />
<meta name="Licence Website" content="http://www.gnu.org/licenses/lgpl-2.1.txt" />

<link rel="stylesheet" media="screen, projection" type="text/css" href="theme/<?php echo _t($theme);?>/sahana.css" />
<link rel="stylesheet" media="print" type="text/css" href="theme/<?php echo _t($theme);?>/print.css" />
<link rel="stylesheet" media="handheld" type="text/css" href="theme/<?php echo _t($theme);?>/mobile.css" />
<? 
//--- Provide Stylesheets to hack different versions of IEs' css ---//

// IE6 
if (file_exists($global['approot']."www/theme/".$theme."/ie6.css")) { ?>
<!--[if IE 6]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($theme);?>/ie6.css" />
<![endif]-->
<? 
}

// IE7
if (file_exists($global['approot']."www/theme/".$theme."/ie7.css")) { ?>
<!--[if IE 7]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($theme);?>/ie7.css" />
<![endif]-->
<? 
}

// IE8
if (file_exists($global['approot']."www/theme/".$theme."/ie8.css")) { ?>
<!--[if IE 8]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($theme);?>/ie8.css" />
<![endif]-->
<? 
}

// IE9
if (file_exists($global['approot']."www/theme/".$theme."/ie9.css")) { ?>
<!--[if IE 9]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($theme);?>/ie9.css" />
<![endif]-->
<? 
} 
//--- end IE styles ---//
?>

<link rel="icon" type="image/png" href="favicon.png">

<script type="text/javascript" src="res/js/libsahana.js"></script>
<script type="text/javascript" src="res/js/libprint.js"></script>
<script type="text/javascript" src="theme/<?php echo _t($theme);?>/sahana.js"></script>
<script type="text/javascript" src="res/js/popup.js"></script>
<script type="text/javascript" src="res/js/locale.js"></script>
<script type="text/javascript" src="index.php?stream=text&amp;mod=xst&amp;act=help"></script>
	<?php
	if ($arrPostfix != null) {
		foreach ($arrPostfix as $i) {
		echo '        '.$i."\n";
		}
	}
	echo "</head>\n";
}
