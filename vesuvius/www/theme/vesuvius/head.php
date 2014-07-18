<?
/**
 * @name         vesuvius theme html head
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0420
 */




function shn_theme_head() {
	global $global;
	global $conf;

// output html head

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title><?php echo _t($global['title']);?></title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="Software " content="US National Library of Medicine People Locator" />
<meta name="Website" content="http://pl.nlm.nih.gov" />
<meta name="Licence" content="Lesser General Public Licence, Version 2.1" />
<meta name="Licence Website" content="http://www.gnu.org/licenses/lgpl-2.1.txt" />

<meta name="google-site-verification" content="Y2Ts00HnBQEr3M3KegrKRRAMVuQPejmqeqPKDsMGRGw" />

<link rel="stylesheet" media="screen, projection" type="text/css" href="theme/<?php echo _t($global['theme']);?>/sahana.css" />
<link rel="stylesheet" media="print" type="text/css" href="theme/<?php echo _t($global['theme']);?>/print.css" />
<link rel="stylesheet" media="handheld" type="text/css" href="theme/<?php echo _t($global['theme']);?>/mobile.css" />
<?
//--- Provide Stylesheets to hack different versions of IEs' css ---//

// IE6
if (file_exists($global['approot']."www/theme/".$global['theme']."/ie6.css")) { ?>
<!--[if IE 6]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($global['theme']);?>/ie6.css" />
<![endif]-->
<?
}

// IE7
if (file_exists($global['approot']."www/theme/".$global['theme']."/ie7.css")) { ?>
<!--[if IE 7]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($global['theme']);?>/ie7.css" />
<![endif]-->
<?
}

// IE8
if (file_exists($global['approot']."www/theme/".$global['theme']."/ie8.css")) { ?>
<!--[if IE 8]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($global['theme']);?>/ie8.css" />
<![endif]-->
<?
}

// IE9
if (file_exists($global['approot']."www/theme/".$global['theme']."/ie9.css")) { ?>
<!--[if IE 9]>
<link rel="stylesheet" type="text/css" href="theme/<?php echo _t($global['theme']);?>/ie9.css" />
<![endif]-->
<?
}
//--- end IE styles ---//
?>

<link rel="icon" type="image/png" href="favicon.png">

<?php
	if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
		echo "<script type=\"text/javascript\" src=\"res/js/locale.js\"></script>";
	}
?>

<script type="text/javascript" src="res/js/vesuvius.js"></script>
<script type="text/javascript" src="index.php?stream=text&amp;mod=xst&amp;act=help"></script>

<?php
}


