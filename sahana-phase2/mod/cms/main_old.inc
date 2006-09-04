<?php
/* $Id: main_old.inc,v 1.2 2006-09-04 09:05:47 mifanc Exp $ */

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
	<h2><?=_("Camp Management System")?></h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default"><?=_("Home")?></a></li>
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
		<li><a href="index.php?mod=<?=$module?>&act=cadd"><?=_("Add New Camp")?></a></li>
<?php
	}//end if
	else
	{
?>
		<li><a href="#"><?=_("Victims")?></a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?=$module?>&act=vadd"><?=_("Register Victim")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=vedt"><?=_("Edit Victim")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=vupd"><?=_("Update Victim")?></a></li>
		</ul>
		<li><a href="#"><?=_("Relief Workers")?></a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?=$module?>&act=wadd"><?=_("Register Relief Worker")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=wedt"><?=_("Edit Relief Worker")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=wupd"><?=_("Update Relief Worker")?></a></li>
		</ul>
		<li><a href="index.php?mod=<?=$module?>&act=srch"><?=_("Search")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=stat"><?=_("Statistics")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=rept"><?=_("Reports")?></a></li>
		<li><a href="index.php?mod=<?=$module?>&act=invt"><?=_("Inventory")?></a></li>
		<li><a href="#"><?=_("Camp Details")?></a></li>
		<ul id="modsubmenu">	
			<li><a href="index.php?mod=<?=$module?>&act=cedt"><?=_("Edit Camp")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=cext"><?=_("Camp Closure")?></a></li>
			<li><a href="index.php?mod=<?=$module?>&act=sync"><?=_("Synchronize")?></a></li>
		</ul>
<?php
	}//end else
?>
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->

<?php
include $global['approot']."/inc/handler_mainmenu.inc";
}//end shn_cms_mainmenu
?>
