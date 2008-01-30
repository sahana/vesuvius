<?php

/**
 * DVR Administrative Section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dvr
 * @subpackage  dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * dvr 
 * 
 * @access public
 * @return void
 */
function shn_dvr_adm_default() {
?>
<p><b>
<?php echo _t("Welcome to the Disaster Victim Registry admin page");?> </b></p>
    <p>
    <?php
   shn_dvr_adminmenu();
   ?>
   <br/>
     <p><b> <?php echo _t("Welcome to the DVR administration  page")?> </b></p>
     
    <p> <?php echo _t("Follow above links to administer the disaster victim registry")?></p>
<?php
}


function shn_dvr_adminmenu() {
	global $global;
	$module = $global['module'];
	// Create the module menuj
	shn_adm_menuopen(_t("Disaster Victim Registry"));
 	shn_adm_menuitem("adm_checklist", _t("Manage Checklist"));

	//shn_adm_menuitem("adm_opt_age_group", _t("Manage Groups"));
	shn_adm_menuclose();

}


function shn_dvr_adm_checklist()
{
    global $global;	
    shn_dvr_adminmenu();
    shn_form_fopen("adm_form_commit",null,array("req"=>false));
    shn_form_fsopen(_t("Add Service / Facility"));

?>
<table>
<tr>
<td><?php
   $extra_opts['req'] = true;
   shn_form_opt_select("opt_dvr_service",_t("Currently Available Services/Facilities"),$extra_opts);
	?>
	
	</td></tr>
	<tr>
	<td>
	<?php
		
	shn_form_text(_t("Item Name"),"service_name",'size="30"',$extra_opts);
	?>
	</td></tr>
	<tr><td>
	<?php
	
		
	shn_form_text(_t("Item Abbrevation [3 letter unique abbr. to store in the database]"),"service_abbr",'size="3"',$extra_opts);
	?>
	</td></tr>
	</table>
	<?php
	
    shn_form_fsclose();
	shn_form_submit(_t("Add Item"));
	shn_form_fclose();

} 



function shn_dvr_adm_form_commit()
{
	
    global $global;
	$db = $global['db'];
	
	if(!empty($_POST['service_name']))
	{
		if(!empty($_POST['service_abbr']))
			{
				$q1 = "SELECT * FROM field_options WHERE option_description='{$_POST['service_name']}'";
				$res1 = $db->Execute($q1);
				
				$q2 = "SELECT * FROM field_options WHERE option_code='{$_POST['service_abbr']}'";
				$res2 = $db->Execute($q2);
				if(1 <= $res1->RecordCount())
				{
				add_error(_t("Item already exists"));
				}
				if(1 <= $res2->RecordCount())
				add_error(_t("Use different abbrevation."));
				else{
				$q = "INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_dvr_service','{$_POST['service_abbr']}','{$_POST['service_name']}')";
				$res = $db->Execute($q);
				$_POST['service_abbr']=null;
				$_POST['service_name']=null;
				}
				
		    }else{add_error(_t("Please fill the required fields"));}
	 //shn_dvr_adm_checklist();
	}
	else
	{
	add_error(_t("Please fill the required fields"));
	
	}
	shn_dvr_adm_checklist();
}


?>



