<?php
/* $Id: admin.inc,v 1.7 2009-08-22 17:17:23 ravithb Exp $ */

/**Admin Module for GPS module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package      Sahana - http://sahana.sourceforge.net
* @author       Sri Ganeshan <sri@opensource.lk>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_gps_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=gps&act=adm_forms">Configure Form Display</a> 
</div>
<br>
<?php
}

function shn_gps_adm_default()
{
   global $conf;
  ?>
   <h2><?php echo $conf['mod_gps_adm_name']._(" Administration")?></h2>
   <?php
   shn_gps_adm_form();
}

function shn_gps_adm_form()
{
	global $global;

	shn_form_fopen(adm_form_commit,null,array("req"=>false));
  	shn_form_fsopen("Add Waypoint Type");
	shn_form_opt_select("opt_wpt_type","Currently available Waypoint Types");
	echo "<br/>";
	shn_form_text("Waypoint Type","waypoint_type",'size="30"');
	shn_form_text("Type Abbrevation [3 letter unique abbr. to store in the database]","type_abbr",'size="3"');
	shn_form_fsclose();
	shn_form_submit("Add Type");
	shn_form_fclose();
}

function shn_gps_adm_form_commit()
{
	global $global;
	$db = $global['db'];

	if(!empty($_POST['waypoint_type'])){
		if(!empty($_POST['type_abbr'])){
			if(strlen($_POST['type_abbr'])==3){
				$q = "insert into field_options(field_name,option_code,option_description) values('opt_wpt_type','{$_POST['type_abbr']}','{$_POST['waypoint_type']}')";
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
	shn_gps_adm_default();
}


