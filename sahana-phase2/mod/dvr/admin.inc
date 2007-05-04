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
<?=_("Welcome to the Disaster Victim Registry admin page");?> </b></p>
    <p>
    <?php
   shn_dvr_adminmenu();

}


function shn_dvr_adminmenu() {
	global $global;
	$module = $global['module'];
	// Create the module menuj
	shn_adm_menuopen(_("Disaster Victim Registry"));
 	shn_adm_menuitem("adm_checklist", _("Manage Checklist"));

	//shn_adm_menuitem("adm_opt_age_group", _("Manage Groups"));
	shn_adm_menuclose();

}


function shn_dvr_adm_checklist()
{
global $global;	
shn_dvr_adminmenu();
shn_form_fopen("adm_form_commit",null,array("req"=>false));
shn_form_fsopen("Add Service / Facility");

?>
<table>
<tr>
<td><?php
shn_form_opt_select("opt_dvr_service","Currently Available Services/Facilities");
	?>
	
	</td></tr>
	<tr>
	<td>
	<?php
		
	shn_form_text("Item Name","service_name",'size="30"');
	?>
	</td></tr>
	<tr><td>
	<?php
	
		
	shn_form_text("Item Abbrevation [3 letter unique abbr. to store in the database]","service_abbr",'size="3"');
	?>
	</td></tr>
	</table>
	<?php
	
	shn_form_fsclose();
	shn_form_submit("Add Item");
	shn_form_fclose();

} 


function shn_dvr_adm_form_commit()
{
	
global $global;
	$db = $global['db'];
	
	if(!empty($_POST['service_name'])){
		if(!empty($_POST['service_abbr'])){
				$q = "insert into field_options(field_name,option_code,option_description) values('opt_dvr_service','{$_POST['service_abbr']}','{$_POST['service_name']}')";
				$res = $db->Execute($q);
		}
	 shn_dvr_adm_checklist();
	}
}


?>




