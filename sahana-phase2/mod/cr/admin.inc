<?php
/* $Id: admin.inc,v 1.11 2007-03-15 08:32:25 mifanc Exp $ */

/**Admin Module for CR
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

include_once($global['approot'].'/inc/lib_form.inc');
require_once('acl.inc');

function _shn_cr_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=cr&act=adm_forms">Configure Form Display</a> 
</div>
<br>
<?php
}

function shn_cr_adm_default()
{
   // _shn_cr_adm_sub_menu();
   global $conf;
  ?>
   <h2><?=$conf['mod_cr_name']._(" Administration")?></h2>
   <?php
   shn_cr_adm_forms();
   
}
function shn_cr_adm_forms()
{
    _shn_cr_adm_sub_menu();
    _shn_cr_adm_form_change();
}

function _shn_cr_adm_form_change(){
	global $global;
	/*
	shn_form_fopen(adm_form_setdivision);
	shn_form_fsopen("Select Division");
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_opt_select("opt_location_type","Select Type to be displayed as Division for camps");
	shn_form_fsclose();
	shn_form_submit("Set Division");
	shn_form_fclose();
	*/
	shn_form_fopen(adm_form_commit,null,array("req"=>false));
  	shn_form_fsopen("Add Service / Facility");
	shn_form_opt_select("opt_camp_service","Currently Available Services/Facilities");
	echo "<br/>";
	shn_form_text("Service Name","service_name",'size="30"');
	shn_form_text("Service Abbrevation [3 letter unique abbr. to store in the database]","service_abbr",'size="3"');
	shn_form_fsclose();
	shn_form_submit("Add Service");
	shn_form_fclose();
}

function shn_cr_adm_form_commit(){

	global $global;
	$db = $global['db'];

	if(!empty($_POST['service_name'])){
		if(!empty($_POST['service_abbr'])){
			if(strlen($_POST['service_abbr'])==3){
				$q = "insert into field_options(field_name,option_code,option_description) values('opt_camp_service','{$_POST['service_abbr']}','{$_POST['service_name']}')";
				$res = $db->Execute($q);
				add_confirmation(_("Added Values"));
			}
			else
				add_error(_("Abbrevation should in 3 characters"));
		}
		else{
			//error: enter code
			add_error(_("Please fill in empty values"));
		}
	}
	else{
		// do not store new services
		add_warning(_("Nothing to add"));
	}
	shn_cr_adm_default();
	
}

function shn_cr_adm_form_setdivision(){
	global $global;
  $db = $global['db'];

	$q = "select * from config where confkey='division_type' && module_id='cr'";  
	$res=$db->Execute($q);
	
	if($res->EOF){
		//insert first time
		//echo "first time";
		$q = "INSERT INTO config(module_id,confkey,value) VALUES ('cr', 'division_type','{$_POST['opt_location_type']}')";
		
		$res=$db->Execute($q);
	}
	else{
		//do update
		$q ="update config set value='{$_POST['opt_location_type']}' where confkey='division_type' && module_id='cr'";
		$ref = $db->Execute($q);
	}
	shn_cr_adm_default();
}
?>

