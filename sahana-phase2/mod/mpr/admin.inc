<?php

/**
 * Administration of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Greg Miernicki <g@miernicki.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');

/**
 * shn_mpr_adminmenu 
 * 
 * @access public
 * @return void
 */
function shn_mpr_adminmenu() {
	global $global;
	$module = $global['module'];

	// Create the module menu
	shn_adm_menuopen(_t("Missing Person Registry"));
 		shn_adm_menuitem("adm_gen", _t("General Configuration"));
		//shn_adm_menuitem("adm_images", _t("Manage Images"));
		shn_adm_menuitem("adm_opt_age_group", _t("Manage Age Groups"));
		shn_adm_menuitem("adm_opt_race", _t("Manage Race"));
		shn_adm_menuitem("adm_opt_religion", _t("Manage Religion"));
		shn_adm_menuitem("adm_opt_blood_type", _t("Manage Blood Group"));
		shn_adm_menuitem("adm_opt_eye_color", _t("Manage Eye Colors"));
		shn_adm_menuitem("adm_opt_hair_color", _t("Manage Hair Colors"));
		shn_adm_menuitem("adm_opt_skin_color", _t("Manage Skin Colors"));
	shn_adm_menuclose();
}



/**
 * Main admin page for the MPR module ~ defaults to the general configuration page now -- greg
 * 
 * @access public
 * @return void
 */
function shn_mpr_adm_default() {
	shn_mpr_adm_gen();
}



/**
 * Provides the general configuration options available to the MPR module.
 *
 * @access public
 * @return void
 */
function shn_mpr_adm_gen() {
	shn_mpr_adminmenu();
	global $conf;
	global $global;
	if ($errors) {
		display_errors();
	}
	if ($updated) {
		?><p align="center"><?php
		add_confirmation(_t("Updated"));
	}
	?><br /><h2><?php echo _("General Configuration"); ?></h2><?php
	shn_form_fopen("adm_gen", null);
	shn_form_hidden(array ('seq' => 'general'));

	// get form values, use defaults if not already saved
	$pictures_per_page    = (shn_db_get_config("mpr", "pictures_per_page")   !== FALSE) ? shn_db_get_config("mpr", "pictures_per_page")    : 6;  // default to 6 pictures
	$show_updates_found   = (shn_db_get_config("mpr", "show_updates_found")  !== FALSE) ? shn_db_get_config("mpr", "show_updates_found")   : 0;  // default to hide
	$show_updates_missing = (shn_db_get_config("mpr", "show_updates_missing")!== FALSE) ? shn_db_get_config("mpr", "show_updates_missing") : 0;  // default to hide
	$show_warning         = (shn_db_get_config("mpr", "show_warning")        !== FALSE) ? shn_db_get_config("mpr", "show_warning")         : 0;  // default to hide
	$use_english_metrics  = (shn_db_get_config("mpr", "use_english_metrics") !== FALSE) ? shn_db_get_config("mpr", "use_english_metrics")  : 0;  // default to SI units
	$alternate_homepage   = (shn_db_get_config("mpr", "alternate_homepage")  !== FALSE) ? shn_db_get_config("mpr", "alternate_homepage")   : ""; // 0 uses content from home.inc, any other value 
	                                                                                                                                             // uses the page content from the mod Rez page

	// if theres a post...
	if (isset($_POST['seq'])) {
		// set form values
		$pictures_per_page    = $_POST['pictures_per_page'];
		$show_updates_found   = $_POST['show_updates_found'];
		$show_updates_missing = $_POST['show_updates_missing'];
		$show_warning         = $_POST['show_warning'];
		$use_english_metrics  = $_POST['use_english_metrics'];
		$alternate_homepage   = $_POST['alternate_homepage'];

		// validate
		clean_errors();
		$error_flag = false;
		if ($pictures_per_page == "" || $pictures_per_page == null) {
			add_error(_t("Please enter the number of images per page!"));
			$error_flag = true;
		} else if ($alternate_homepage == "") {
			add_error(_t("Please enter a number for the alternate homepage!"));
			$error_flag = true;
		} else if (!shn_valid_number($pictures_per_page)) {
			$error_flag = true;
			add_error(_t("Search limit should be a number!"));
		}
		// if no errors, save config
		if (!$error_flag) {
			shn_db_config_update("mpr", "pictures_per_page",    $pictures_per_page);
			shn_db_config_update("mpr", "show_updates_found",   $show_updates_found);
			shn_db_config_update("mpr", "show_updates_missing", $show_updates_missing);
			shn_db_config_update("mpr", "show_warning",         $show_warning);
			shn_db_config_update("mpr", "use_english_metrics",  $use_english_metrics);
			shn_db_config_update("mpr", "alternate_homepage",   $alternate_homepage);
			add_confirmation(_t("Configuration saved."));
		} else {
			add_error(_t("Configuration not saved."));
		}
	} 

	// cast form value to array
	$pictures_per_page  = array("value"=>$pictures_per_page);

	// build form
	shn_form_fsopen(_t('Search'));
		shn_form_text(_t('Number of images per page'), 'pictures_per_page', 'size="10"', $pictures_per_page);
	shn_form_fsclose();

	shn_form_fsopen(_t('Show missing/found updates on the MPR main page'));
		shn_form_radio2(array("1"=>"Show","0"=>"Hide"),"Show Found Person Updates",   "show_updates_found",   $show_updates_found,   null); 
		shn_form_radio2(array("1"=>"Show","0"=>"Hide"),"Show Missing Person Updates", "show_updates_missing", $show_updates_missing, null); 
	shn_form_fsclose();

	shn_form_fsopen(_t('Show warning message before "Reporting a Person"'));
		shn_form_radio2(array("1"=>"Show","0"=>"Hide"),"Show Warning", "show_warning", $show_warning, null); 
	shn_form_fsclose();
	
	shn_form_fsopen(_t('Use English Metrics'));
		shn_form_radio2(array("1"=>"English","0"=>"SI"),"Use English measurements (pounds/feet) instead of the SI standards (kilograms/meters).", "use_english_metrics", $use_english_metrics, null); 
	shn_form_fsclose();	

	shn_form_fsopen(_t('MPR Main Page'));
		if (file_exists($global['approot'].'/mod/rez')) {
			$q = "select * from rez_pages where rez_visibility = 'External Page' order by rez_menu_order asc;";
			$res = $global['db']->Execute($q);
			// build <select> list of external page choices
			$html_out = "Select the content that will appear on the MPR home page. You may select an <b>External Page</b> from the <b>Resources Module</b>, or just leave it as default and the standard content will be displayed.<br><br><select name=\"alternate_homepage\"><option value=\"0\">New Default Page Content</option><option value=\"-1\">Old Default Page Content</option>";
			while($row = $res->FetchRow() ){
				if ($row['rez_page_id'] == $alternate_homepage) {
					$select_text = "SELECTED";
				} else {
					$select_text = "";
				}
				$html_out .= "<option value=\"".$row['rez_page_id']."\" ".$select_text.">Page #".$row['rez_page_id']." -- ".$row['rez_page_title']."</option>";
			}
			$html_out .= "</select>";
			echo _t($html_out);
		} else {
			echo _t("Resources module not installed, using default homepage.");
		}
	shn_form_fsclose();
		?><center><?php
		shn_form_submit(_t('Update'));
		?></center><?php
	shn_form_fclose();
}



function shn_mpr_adm_images() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Search"); ?></h2><?php
}



function shn_mpr_adm_opt_age_group() {
	shn_mpr_adminmenu();
	//print 'button is'.$_POST['button_name'];
	?><br /><h2><?php echo _t("Manage Age Groups"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_age_group');
}



function shn_mpr_adm_opt_race() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Race"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_race');
}



function shn_mpr_adm_opt_religion() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Religion"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_religion');
}



function shn_mpr_adm_opt_blood_type() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Blood Groups"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_blood_type');
}



function shn_mpr_adm_opt_eye_color() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Eye Color"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_eye_color');
}



function shn_mpr_adm_opt_hair_color() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Hair Color"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_hair_color');
}



function shn_mpr_adm_opt_skin_color() {
	shn_mpr_adminmenu();
	?><br /><h2><?php echo _t("Manage Skin Color"); ?></h2><?php
	_shn_mpr_adm_field_options_controller('opt_skin_color');
}



//temporary fix
function _shn_mpr_adm_field_options_controller($type) {
	switch ($_POST['seq']) {
		case 'update' :
			if (_shn_mpr_adm_field_options_validate($type)) {
				_shn_mpr_adm_field_options_form($type, false);
			} else {
				_shn_mpr_adm_field_options_form($type, true);
			}
			break;
		default :
			_shn_mpr_adm_field_options_form($type);
			break;
	}
}



function _shn_mpr_delete_option($optioncode) {
	global $global;
	$sql="DELETE FROM field_options WHERE option_code='{$optioncode}'";
	$global['db']->Execute($sql);
	add_confirmation(_('Field was successfully deleted.'));
}



function is_optioncode_exists($optioncode) {
	$found=false;
	global $global;
	$sql="SELECT * FROM field_options WHERE option_code='{$optioncode}'";
	$res=$global['db']->Execute($sql);
	while(!$res->EOF) {
		$code=$res->fields['option_code'];
		$found=true;
		$res->MoveNext();
	}
	return $found;
}

function _shn_mpr_update_option($optioncode,$optiondescription) {
	global $global;
	$sql="UPDATE field_options SET option_description='{$optiondescription}' WHERE option_code='{$optioncode}'";
	$global['db']->Execute($sql);
	//add_confirmation($optiondescription.' updated');
}



function _shn_mpr_insert_option($field_name,$optioncode,$optiondescription) {
	global $global;
	$sql="INSERT INTO field_options (field_name,option_code,option_description) VALUES ('{$field_name}','{$optioncode}','{$optiondescription}')";
	$global['db']->Execute($sql);
	if ($sql) {
		add_confirmation(_($_POST['new_desc'] .' was successfully added.'));
	}
	$_POST['new_code'] = $_POST['new_desc'] = null;
}



function _shn_mpr_adm_field_options_form($type) {
	global $global;
	global $conf;
	$button_type=$_POST['button_name'];
	if ($button_type=='Update') {
		$sql = "SELECT field_name, option_code, option_description  FROM field_options WHERE field_name = '{$type}'";
		$sel = $global['db']->GetAll($sql);
		$count=0;
		foreach ($sel as $row) {
			$opcode=$row['option_code'];
			$fname=$row['field_name'];
			$code=$_POST[$opcode];
			$desc= $_POST[$count++];
			$todelete=$_POST[$count++];
			//print $code.$todelete;
			if($todelete=='on') {
				//print $code;
				_shn_mpr_delete_option($code);
			} else {
				_shn_mpr_update_option($code,$desc);		
			}
		}
	} else if($button_type=='AddNew') {
		$code=$_POST['new_code'];
		$desc=$_POST['new_desc'];
		if($code==null | $desc==null) {
			if($code==null) {
				add_error(_t("Please  enter the code"));
			}
			if($desc==null) {
				add_error(_t("Please  enter the description"));
			}
			display_errors();
		} else if(is_optioncode_exists($code)) {
			add_error(_t("Code already exists"));
			display_errors();
		} else
			_shn_mpr_insert_option($type,$code,$desc);
		}
		$sql = "SELECT field_name, option_code, option_description  FROM field_options WHERE field_name = '{$type}'";
		$arr = $global['db']->GetAll($sql);
		if (!empty ($arr)) {
			shn_form_fopen('adm_' . $type, null);
			shn_form_fsopen(_t('Update'));
			shn_form_hidden(array ('seq' => 'update'));
			?>
<table>
<script language="JavaScript"></script>
<thead>
<td><strong><?php echo _t('Code');?></strong></td>
<td width="100%"><strong><?php echo _t('Description');?></strong></td>
<td width="100%"><strong><?php echo _t('Delete');?></strong></td>
</thead>
<?php
	$count=0;
	foreach ($arr as $row) { ?>
<tr>
	<td><input type="text" READONLY name="<?php echo $row['option_code'];?>" value="<?php echo $row['option_code'];?>"  /></td>
	<td><input type="text" name="<?php echo $count++;?>" value="<?php echo $row['option_description'];?>" /></td>
	<td><input type="checkbox" name="<?php echo $count++;?>" /></td>
</tr>
<?php
	}?>
</table>
<?php
	shn_form_submit(_t('Update'),"name='button_name'");
	shn_form_fsclose();
	}
	shn_form_fsopen(_t('Add New '));
	shn_form_text(_t("Code"), 'new_code', null, array('req'=>true));
	shn_form_text(_t("Description"), 'new_desc', null, array('req'=>true));
	shn_form_submit(_t('AddNew'),"name='button_name'");
	shn_form_fclose();
}




function _shn_mpr_adm_field_options_validate($type, $error = false) {
	// todo?
}