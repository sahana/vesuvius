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
include_once $global['approot']."/inc/lib_menu.inc";


function shn_cps_mainmenu(){
	global $global;
	global $conf;
$server= $conf['servername'] ;
	$module = $global['module'];
	
	shn_mod_menuopen(_($conf['mod_cps_name']));
	shn_sub_mod_menuopen("Add Child");
    shn_mod_menuitem("achildcenter","Add Child Center",$module);
    shn_mod_menuitem("achildpersonal","Add Child Personal",$module);
  shn_mod_menuitem("achildreporter","Add Child Reporter",$module);
 shn_mod_menuitem("achildrelation","Add Child Relation",$module);
 shn_mod_menuitem("achildeducation","Add Child Education",$module);
 shn_mod_menuitem("achildhealth","Add Child Health",$module);
 shn_mod_menuitem("achildbehaviour","Add Child Behaviour",$module);
 shn_mod_menuitem("achildproperties","Add Child Properties",$module);


    shn_sub_mod_menuclose();
	shn_sub_mod_menuopen("Sch/Edt/Del Child Center");
	shn_mod_menuitem("edtchildcenter","Sch/Edt/Del Child Center",$module);
    shn_mod_menuitem("edtchildpersonal","Sch/Edt/Del Child Personal",$module);
  shn_mod_menuitem("edtchildreporter","Sch/Edt/Del Child Reporter",$module);
 shn_mod_menuitem("edtchildrelation","Sch/Edt/Del Child Relation",$module);
 shn_mod_menuitem("edtchildeducation","Sch/Edt/Del Child Education",$module);
 shn_mod_menuitem("edtchildhealth","Sch/Edt/Del Child Health",$module);
 shn_mod_menuitem("edtchildbehaviour","Sch/Edt/Del Child Behaviour",$module);
 shn_mod_menuitem("edtchildproperties","Sch/Edt/Del Child Properties",$module);
shn_sub_mod_menuclose();

shn_sub_mod_menuopen("Backup/Restore Database");
//shn_mod_menuitem("backuprestore","Backup/Restore Database",$module);
print '<a href="http://localhost/~isuru/sahana-phase2/mod/cps/backuprestore/backup.php">BackUp/Restore</a>';

shn_sub_mod_menuclose();
shn_sub_mod_menuopen("Query View");

shn_mod_menuitem("queryview","GoToQueryView",$module);
//print '<a href="http://localhost/sahana-phase2/mod/cps/backuprestore/backup.php">Query</a>';
shn_sub_mod_menuclose();
shn_mod_menuclose();
include $global['approot']."/inc/handler_mainmenu.inc";
	
	

?>


<?php
//include $global['approot']."/inc/handler_mainmenu.inc";
}


?>
