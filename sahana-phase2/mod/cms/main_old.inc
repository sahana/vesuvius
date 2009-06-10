<?php
/* $Id: main_old.inc,v 1.5 2009-06-10 20:48:22 gmiernicki Exp $ */

/**Main home page of the CMS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    	Sahana - http://sahana.sourceforge.net
* @author   	Chathra Hendehewa <chathra@opensource.lk>
* @author   	Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cms/main_fns.inc";
include_once $global['approot']."/mod/cms/home.inc";


/**
 * Main menu functionality
 * @todo	Add Javascript to handle menu expansion
*/
function shn_cms_mainmenu()
{
	global $global;
	$module = $global['module'];
	$db = $global['db'];
?>
<div id="modmenuwrap">
	<h2><?php echo _t("Camp Management System")?></h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?php echo $module?>&act=default"><?php echo _t("Home")?></a></li>
<?php
	/*
	 * Check whether there are existing camps.
	 * If not, show only Camps creation subsection
	 * Else, show everything
	 */
	$query_camps = "select * from camp";
	$result = $db->Execute($query_camps);
	if($result->EOF || $result==null)
	{	
?>
		<li><a href="index.php?mod=<?php echo $module?>&act=cadd"><?php echo _t("Add New Camp")?></a></li>
<?php
	}//end if
	else
	{
?>
		<li><a href="#"><?php echo _t("Victims")?></a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?php echo $module?>&act=vadd"><?php echo _t("Register Victim")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=vedt"><?php echo _t("Edit Victim")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=vupd"><?php echo _t("Update Victim")?></a></li>
		</ul>
		<li><a href="#"><?php echo _t("Relief Workers")?></a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?php echo $module?>&act=wadd"><?php echo _t("Register Relief Worker")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=wedt"><?php echo _t("Edit Relief Worker")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=wupd"><?php echo _t("Update Relief Worker")?></a></li>
		</ul>
		<li><a href="index.php?mod=<?php echo $module?>&act=srch"><?php echo _t("Search")?></a></li>
		<li><a href="index.php?mod=<?php echo $module?>&act=stat"><?php echo _t("Statistics")?></a></li>
		<li><a href="index.php?mod=<?php echo $module?>&act=rept"><?php echo _t("Reports")?></a></li>
		<li><a href="index.php?mod=<?php echo $module?>&act=invt"><?php echo _t("Inventory")?></a></li>
		<li><a href="#"><?php echo _t("Camp Details")?></a></li>
		<ul id="modsubmenu">	
			<li><a href="index.php?mod=<?php echo $module?>&act=cedt"><?php echo _t("Edit Camp")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=cext"><?php echo _t("Camp Closure")?></a></li>
			<li><a href="index.php?mod=<?php echo $module?>&act=sync"><?php echo _t("Synchronize")?></a></li>
		</ul>
<?php
	}//end else
?>
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->

<?php
include $global['approot']."/inc/handler_mainmenu.inc";
}//end shn_cms_mainmenu