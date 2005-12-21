<?php
/* $Id; */

/**Main home page of the CR
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
//var_dump($global[db]);
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cr/main_fns.inc";

function shn_cr_mainmenu(){
	global $global;
	$module = $global['module'];
	include $global['approot']."/conf/config.inc";
?>
<div id="modmenuwrap">
	<h2>Camps Registry Menu</h2>
	<ul id="modmenu">
		<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
		<li><a href="index.php?mod=<?=$module?>&act=srch">Search</a></li>
		<li><a href="index.php?mod=<?=$module?>&act=acmp">Add Camp</a></li>
		<li><a href="#">Reports</a></li>
		<ul id="modsubmenu">
		  <li><a href="index.php?mod=<?=$module?>&act=arpt">View All Camps</a></li>
			<li><a href="index.php?mod=<?=$module?>&act=lrpt">View By Location</a></li>
			<?php
				if($conf['gis']){
			?>
				<li><a href="index.php?mod=<?=$module?>&act=gis_show">Location Map</a></li>
			<?php
				}
			?>
		</ul>
		<li><a href="index.php?mod=<?=$module?>&act=ecmp">Edit Camp</a></li>
		
													
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?
include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
