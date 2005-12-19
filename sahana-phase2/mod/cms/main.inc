<?php
/* $Id; */

/**Main home page of the CMS
*
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

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cms/main_fns.inc";
include_once $global['approot']."/mod/cms/home.inc";

function shn_cms_mainmenu(){
	global $global;
	$module = $global['module'];
?>
<div id="modmenuwrap">
	<h2>Camps Management System</h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
		<li><a href="#">Camps</a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?=$module?>&act=cadd">Add New Camp</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=cedt">Edit Camp</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=cext">Close Camp</a></li>
		</ul>
		<li><a href="#">Victims</a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?=$module?>&act=vadd">Register Victim</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=vedt">Edit Victim</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=vupd">Update Victim</a></li>
		</ul>
		<li><a href="#">Relief Workers</a></li>
		<ul id="modsubmenu">
			<li><a href="index.php?mod=<?=$module?>&act=wadd">Register Relief Worker</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=wedt">Edit Relief Worker</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=wupd">Update Relief Worker</a></li>
		</ul>
		<li><a href="index.php?mod=<?=$module?>&act=srch">Search</a></li>
		<li><a href="index.php?mod=<?=$module?>&act=stat">Statistics</a></li>
		<li><a href="index.php?mod=<?=$module?>&act=rept">Reports</a></li>
		<li><a href="index.php?mod=<?=$module?>&act=invt">Inventory</a></li>
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?
include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
