<?php
/* $Id: main.inc,v 1.4 2006-06-08 13:19:09 mifanc Exp $; */

/**
* Main home page of the GIS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
//var_dump($global[db]);
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/gis/main_fns.inc";
include_once $global['approot']."/mod/gis/conf.inc";

function shn_gis_mainmenu(){
	global $global;
	global $conf;
	$module = $global['module'];
?>
<div id="modmenuwrap">
	<h2><?= $conf['mod_gis_name']?></h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default"><?php echo _("Home")?></a></li>
    <li><a href="index.php?mod=<?=$module?>&act=aloc"><?php echo _("Add Location")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=show"><?= _('Show')?></a></li>
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?
include $global['approot']."/inc/handler_mainmenu.inc";
}



?>
