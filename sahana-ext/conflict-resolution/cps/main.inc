<?php
/* $Id; */

/**Main home page of the CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
*@author   Isuru Samaraweera
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
//var_dump($global[db]);
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/mod/cps/main_fns.inc";

function shn_cps_mainmenu(){
	global $global;
	global $conf;
$server= $conf['servername'] ;
	$module = $global['module'];
?>
<div id="modmenuwrap">
	<h2>Children Registry Menu</h2>
	<ul id="modmenu">
<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
     
<li><a href="#">Add Child</a></li>
<ul id="modsubmenu">
<li><a href="index.php?mod=<?=$module?>&act=achildcenter">AddChildCenter</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildpersonal">AddPersonalData</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildreporter">ReportersData</a></li>


<li><a href="index.php?mod=<?=$module?>&act=achildrelation">AddChildRelation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildfstatus">AddChildFamilyStatus</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildeducation">AddChildEducation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildhealth">AddChildHealth</a></li>
<li><a href="index.php?mod=<?=$module?>&act=achildbehaviour">AddChildBehaviour</a></li>
	<li><a href="index.php?mod=<?=$module?>&act=achildproperties">AddChildProperties</a></li>
		</ul>                

<li><a href="#">Search/Edit/Delete Child</a></li>
<ul id="modsubmenu">
<li><a href="index.php?mod=<?=$module?>&act=edtchildcenter">Sch/Edt/Del ChildCenter</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildpersonal">Sch/Edt/Del PersonalData</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildreporter">Sch/Edt/Del ReportersData</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildrelation">Sch/Edt/Del EditChildRelation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildfstatus">Sch/Edt/Del ChildFamilyStatus</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildeducation">Sch/Edt/Del EditChildEducation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildhealth">Sch/Edt/Del EditChildHealth</a></li>
<li><a href="index.php?mod=<?=$module?>&act=edtchildbehaviour">Sch/Edt/Del EditChildBehaviour</a></li>
	<li><a href="index.php?mod=<?=$module?>&act=edtchildproperties">Sch/Edt/Del EditChildProperties</a></li>
		</ul>                

<!--
<li><a href="#">Search Child</a></li>
<ul id="modsubmenu">
<li><a href="index.php?mod=<?=$module?>&act=schchildcenter">SearchChildCenter</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildpersonal">SearchPersonalData</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildrelation">SearchChildRelation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildfstatus">SearchChildFamilyStatus</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildeducation">SearchChildEducation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildhealth">SearchChildHealth</a></li>
<li><a href="index.php?mod=<?=$module?>&act=schchildbehaviour">SearchChildBehaviour</a></li>
</ul>           


<li><a href="#">Delete Child</a></li>
<ul id="modsubmenu">
<li><a href="index.php?mod=<?=$module?>&act=delchildcenter">DeleteChildCenter</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildpersonal">DeletePersonalData</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildrelation">DeleteChildRelation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildfstatus">DeleteChildFamilyStatus</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildeducation">DeleteChildEducation</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildhealth">DeleteChildHealth</a></li>
<li><a href="index.php?mod=<?=$module?>&act=delchildbehaviour">DeleteChildBehaviour</a></li>
		</ul>-->                
<li><a href="#">Backup/Restore Database</a></li>
<ul id="modsubmenu">
<li><a href="http://<?php print $server?>/sahana-phase2/mod/cps/backuprestore/backup.php">BackUp/Restore Database</a></li>
<!--<li><a href="index.php?mod=<?=$module?>&act=restoredatabase">RestoreDatabase</a></li>-->
</ul>

   <li><a href="#">Query View</a></li>
		  <ul id="modsubmenu">
		  <li><a href="index.php?mod=<?=$module?>&act=queryview">GotoQueryView</a></li>
			
		</ul>
		
		
													
	</ul><!--end div=modmenu-->
</div><!--end div=modmenuwrap-->
<?php
include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
