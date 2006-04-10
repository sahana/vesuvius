<?php
/* $Id: main.inc,v 1.1 2006-04-10 11:54:23 mifanc Exp $ */

/**Main home page of the LR
*
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
include_once $global['approot']."/mod/lr/main_fns.inc";


function shn_lr_mainmenu(){
	global $global;
	$module = $global['module'];
?>
<div id="modmenuwrap">
	<h2><?php echo _("Location Registry Menu")?></h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default"><?php echo _("Home")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=aloc"><?php echo _("Add Location")?></a></li>
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?
include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
