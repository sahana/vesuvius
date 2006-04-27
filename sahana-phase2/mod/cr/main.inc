<?php
/**Main home page of the CR
* $Id: main.inc,v 1.13 2006-04-27 04:43:29 mifanc Exp $
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
//var_dump($global[db]);
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cr/main_fns.inc";
include_once $global['approot']."/inc/lib_menu.inc";

function shn_cr_mainmenud(){
	global $global;
	$module = $global['module'];
?>
<div id="modmenuwrap">
	<h2><?php echo _("Camps Registry Menu")?></h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default"><?php echo _("Home")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=srch"><?php echo _("Search")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=acmp"><?php echo _("Add Camp")?></a></li>
		<li><a href="#">Reports</a></li>
		<ul id="modsubmenu">
		  <li><a href="index.php?mod=<?=$module?>&act=arpt"><?php echo _("View All Camps")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=lrpt"><?php echo _("View By Location")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=contact"><?php echo _("View Admin Details")?></a></li>
			<?php
				global $conf;
				if($conf['gis']=='true'){
			?>
				<li><a href="index.php?mod=<?=$module?>&act=gis_show"><?php echo _("Location Map")?></a></li>
			<?php
				}
			?>
		</ul>
		<li><a href="index.php?mod=<?=$module?>&act=ecmp"><?php echo _("Edit Camp")?></a></li>
		
													
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?
include $global['approot']."/inc/handler_mainmenu.inc";
}

function shn_cr_mainmenu()
{
	global $global;
    global $conf;
    $module = $global['module'];
    shn_mod_menuopen(_($conf['mod_cr_name']));
    shn_mod_menuitem("default",_("Home"),$module);
    shn_mod_menuitem("srch",_("Search"),$module);
    shn_mod_menuitem("acmp",_("Add Camp"),$module);
    shn_mod_menuitem("ecmp",_("Edit Camp"),$module);
    shn_sub_mod_menuopen(_("Reports"));
    shn_sub_mod_menuitem("arpt",_("View All Camps"),$module);
    shn_mod_menuitem("lrpt",_("View By Location"),$module);
    shn_mod_menuitem("contact",_("View Admin Details"),$module);
    if($conf['gis'])
    	shn_mod_menuitem("gis_show",_("Location Map"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
