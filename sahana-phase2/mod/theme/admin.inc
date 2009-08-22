<?php
/**
 * This is the admin file for the Sahana module. This file is optional
 * if it exists a section is created in the administation section of Sahana
 * to configure this module
 * IMPORTANT: The <action> part of the functions in shn_<mod name>_<action>
 * should be prefixed with "adm_" for this module to be reflected in admin
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   akshit sharma
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage theme
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * The default page for the theme admin page. 
 * This page displays all roles and allows admin to set which role should
 * be given access to the custom_theme module.
 * 
 * @access public
 * @return void
 */
function shn_theme_adm_default()
{
?>
    <p><b><?php echo _t("Welcome to Custom Theme admin page. You can use this page to give permissions to different roles for using the Custom Theme module. Select roles to which access should be granted.")?> </b></p>
<?php
	global $global;
	$db=$global['db'];
	$roles=array();
	$roles_enabled=array();

	//get a list of all roles
	$q="select * from sys_user_groups";	
	$res=$db->Execute($q);
	
	//get all roles which are given access to theme module
	$q1="select * from sys_group_to_module where module=\"theme\"";
	$res1=$db->Execute($q1);
	
	// Iterate over all roles and see which of them are allowed access to theme module.
	// roles_enabled is set to "enabled" for roles which have access to theme module. 
	// Else role_enabled is set to "disabled".
	while(($res!=null) &&(!$res->EOF)){
		$roles[$res->fields["group_id"]]=$res->fields["group_name"];

		$flag = 0;
		while(($res1!=null) &&(!$res1->EOF))
		{
			if($res->fields["group_id"] == $res1->fields["group_id"] && $res1->fields["status"] == "enabled")
			{	
				$flag = 1;
				$roles_enabled[$res->fields["group_id"]]="enabled";
			}
			
			if ($flag == 0)
				$roles_enabled[$res->fields["group_id"]]="disabled";
			
			$res1->MoveNext();
		}
		$res1->MoveFirst();
		$res->MoveNext();
	}
	
	//create a form where admin can give access permissions to various roles
	$role_id=1;
	shn_form_fopen("save_permissions", null,array('req_message'=>true));
	shn_form_fsopen("Allow access to following roles");
	
	//create a checkbox for each role except for admin role 
	foreach ($roles as $role=>$role_name)
	{
		if($role_id == 1)
		{
			$role_id++;
			continue;
		}
		else
		{
			//checkbox is checked if access permission was granted to that role, else unchecked.
			if ($roles_enabled[$role_id] == "enabled")
				echo "<td><input type=\"checkbox\" name=".$role_id." checked=\"true\" align=\"right\" /> ".$role_name."</td></br>";
			else
				echo "<td><input type=\"checkbox\" name=".$role_id." align=\"right\" /> ".$role_name."</td></br>";
		}
		$role_id++;
	}
	shn_form_fsclose();
	echo '<br /> <center>';
	shn_form_submit("Save");                       // Create the submit button
	echo '</center> <br />';
    shn_form_fclose(); 
}

