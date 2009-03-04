<?php
/**
 * DSM main.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @author     Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . '/inc/lib_menu.inc';
include_once $global['approot'] . '/mod/dsm/lib_dsm.inc';
include_once ($global['approot']."/inc/lib_form.inc");
include_once $global['approot'].'/inc/reporting/lib_chart.inc';
include_once $global['approot'].'/inc/reporting/lib_reporting.inc';
include_once $global['approot'].'/inc/lib_paging.inc';
include_once 'disease_definitions.inc';
include_once 'graph.inc';
include_once 'lib_dsm_validation.inc';
include_once $global['approot'].'/inc/lib_xajax.inc';

function shn_dsm_mainmenu()
{
	global $global;
	$module = $global['module'];
	shn_mod_menuopen(_t('Disease Surviellance Module'));

	shn_mod_menuitem('default',_t('Home'));
	//if and only if admin user (do the coding)
	shn_sub_mod_menuopen(_t('Manage Diseases'));
	shn_mod_menuitem('add_dis',_t('Add New Disease'));
	shn_mod_menuitem('edit_disease',_t('Edit Disease Details'));
	shn_mod_menuitem('search_dis',_t('Search'));
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t('Manage Disease Form Definitions'));
	shn_mod_menuitem('view_field_data_type',_t('Field Data Types'));
	shn_mod_menuitem('add_definition',_t('Add / Edit / Delete Form Definitions'));
	shn_mod_menuitem('disease_form',_t('Show Data Entry Form'));
	shn_sub_mod_menuclose();

	shn_sub_mod_menuopen(_t('Patients/Cases'));
	shn_mod_menuitem('rep_dis', _t('Report a Patient'));
	shn_mod_menuitem('disease_form',_t('New Case'));
	shn_mod_menuitem('search_case', _t('Search'));
	shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_t('Report of Disease'));
	shn_mod_menuitem('sur_rep', _t('Surviellance Report'));
	//shn_mod_menuitem('report', _t('Report'));
	shn_mod_menuitem('view_disease_list',_t('View by Disease'));
	shn_mod_menuitem('case_count_by_disease',_t('Case Count by Disease'));
	shn_mod_menuitem('case_count_per_disease',_t('Case Count per Disease'));

	shn_sub_mod_menuclose();
	shn_mod_menuclose();


	//include the main menu so that the user can navigate outside the module
	include_once($global['approot'] . '/inc/handler_mainmenu.inc');
}

function shn_dsm_default()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/home.inc';
}

function shn_dsm_add_dis()
{
	/*
	 * here check admin user == true
	 */
	global $global;
	include_once $global['approot'] . '/mod/dsm/add_dis.inc';
	/*
	 * otherwise add error no permmision
	 */
	if(isset($_REQUEST['seq'])) {
		switch ($_REQUEST['seq']) {
			case 'page2' :
				{
					if (_shn_dsm_validate()) {
						_shn_dsm_get_data(true);
					} else {
						_shn_dsm_set_datails();
						//if (!$_SESSION['priority']) {
						$_SESSION['priority'] = 'Primary';
						//}
						_shn_dsm_add_symptoms('Primary');
					}
					break;
				}
			case 'page3' :
				{
					$button = $_POST['button'];
					if ($button == 'Next') {
						if ($_SESSION['priority'] == 'Primary') {
							$_SESSION['priority'] = 'Minor';
							_shn_dsm_add_symptoms('Minor');
						} else {
							//_shn_symtoms_todb();
							_shn_dsm_confirm();
						}
					} else {

						if ($_POST['symptom']) {
							_shn_symtoms_todb();
						}
						_shn_dsm_add_symptoms($_SESSION['priority']);
					}
					break;
				}
			case 'finish' :
				{
						
					_shn_dsm_write_to_db();
					unset($_SESSION['Primary']);unset($_SESSION['Minor']);
					shn_dsm_default();
					break;
				}
				//      default :
				//          {
				//              //_shn_dsm_get_data(); //every time display the things
				//          }

		}
	} else {
		unset($_SESSION['Primary']);
		unset($_SESSION['Minor']);
		_shn_dsm_get_data(); //very first time to the page
	}
}

function shn_dsm_rep_dis()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/rep_dis.inc';
	switch ($_REQUEST['seq']) {
		case 'finish' :
			{
				_shn_dsm_set_symptoms();
				_shn_dsm_commit_patient();
				_shn_confirm_patient_todb();
				//_shn_print_form_one();
				break;
			}
		case 'form2' :
			{
				_shn_dsm_set_patient();
				_shn_patient_symptoms();
				//_shn_patient_contact();
				break;
			}
		case 'loc' :
			{
				_shn_dsm_set_patient();
				_shn_patient_location();
				break;
			}
			//      case 'contact' :
			//          {
			//              _shn_patient_contact();
			//              break;
			//          }
		default :
			{
				_shn_dsm_print_header('Report A Patient');
				_shn_print_form_one();
				break;
			}
	}
}

function shn_dsm_edit_disease()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/edt_dis.inc';


	if (!isset($_REQUEST['seq'])) {
		$_SESSION['disease_id'] = $_GET['dis_uuid'];
	}
	if ($_SESSION['disease_id']) {
		_shn_dsm_print_header('Edit Disease');
		_shn_edit_tab_menu();
		switch ($_REQUEST['seq']) {
				
			case 'view_disease':
				{
					_shn_dsm_edit_disease();
					break;
				}
			case 'edit_dis' :
				{
					//print 'edit dis';
						
					//_shn_update_disease_details();
					//_shn_dsm_disease_details($dis_uuid);
					break;
				}
			case 'general':
				{
					shn_dsm_edit_general_detailsl();
					break;
				}
			case 'factors' :
				{

					//_shn_edit_tab_menu();
					shn_dsm_edit_factors();
					break;
				}
			case 'edit_factors' :
				{
					//print 'edit fac';
						
					break;
				}
			case 'symptoms' :
				{
					_shn_dsm_edit_disease_symptoms();
					//_shn_dsm_disease_symptoms();
					break;
				}
			case 'edit_symptoms' :
				{
					print 'edit sym';
					_shn_update_disease_symtoms();
					break;
				}
			default :
				{
					//print $dis_uuid;
					//_shn_edit_tab_menu();
					_shn_dsm_disease_details($dis_uuid);
					//break;
				}
		}
	} else {
		_shn_dsm_edit_disease();

	}
}

function shn_dsm_sur_rep()
{
	global $global;
	if (!$_REQUEST['sub']) {
		$_SESSION['disease_id'] = $_GET['dis_uuid'];
	}
	include_once $global['approot'] . '/mod/dsm/sur_rep.inc';
}

function shn_dsm_edit_case()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/edit_case.inc';

	if($_POST['finish']) {
		update();print 'code for update';
	}

}

function shn_dsm_delete_disease()
{
	$dis_id = $_GET['dis_id'];
	$sql = "DELETE FROM dsm_dsdisease_symptoms WHERE dis_id='{$dis_id}'";

	$sql = "DELETE FROM dsm_diseases WHERE dis_id='{$dis_id}'";

	//update patients with this disease as unknown
}

function shn_dsm_view_case()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/view_case.inc';

}

function shn_dsm_search_case()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/search_case.inc';

	switch ($_REQUEST['seq']) {
		case 'search' : {
			_shn_dsm_search_case();
			break;
		}
		default : {
			_shn_search_case_default();
			break;
		}
	}

}

function shn_dsm_search_dis()
{
	global $global;
	//include_once $global['approot'] . '/mod/dsm/search_case.inc';

	include_once $global['approot'] . '/mod/dsm/search_dis.inc';

	switch ($_REQUEST['seq']) {
		case 'search' : {
			$gname = $_POST['gname'];
			$mname = $_POST['mname'];
			_shn_dsm_searching($gname, $mname);
			break;
		}
		default : {
			_shn_search_dis_default();
			break;
		}
	}
}

function shn_dsm_report()
{
	global $global;
	include_once $global['approot'] . '/mod/dsm/report.inc';
	shn_dsm_report_default();
}

//----------------------------------------------------------------------------------------------------------
//function for edit definition
function shn_dsm_edit_definition(){
	echo "<h2>"._t("Edit Field Infomation")."</h2>";
	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		global $global;
		$db = $global['db'];
		$field_id = $_REQUEST['field_id'];
		$disease_id = $_REQUEST['disease_id'];
		//echo $field_id."<br>";
		//echo $disease_id;

		//pass form information
		shn_form_fopen('update_field_info','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

		//start fsopen for text, type, name
		shn_form_fsopen(_t("Field Type")); ?>
		<div class="info"><?= _t("These are the basic details of Created Field.");?></div>
		<?php

		//get field text
		$field_info_query = "SELECT text,type,name,data_type FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($field_info_query,array($field_id));
		$text=$res1->fields["text"];
		$type=$res1->fields["type"];
		$name=$res1->fields["name"];
		$data_type=$res1->fields["data_type"];

		echo "<table><tr>";
		echo "<td>"._t('Field Text')."</td><td>".$text."</td>";
		//echo "<td><a href=index.php?mod=dsm&act=edit_field_text&field_id=".$field_id."&disease_id=".$disease_id.">"._t("Edit")."</a> </td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','edit_field_text','Edit',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
		echo "</td>";
		echo "</tr>";

		echo "<tr><td>"._t('Field Data Type')."</td><td>".$data_type."</td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','edit_field_data_type','Edit',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
		echo "</td>";
		echo "</tr>";

		echo "<tr><td>"._t('Field Type')."</td><td>".$type."</td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','edit_field_type','Edit',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id,'type'=>$type),$text_opts='');
		echo "</td>";
		echo "</tr>";

		echo "<tr><td>"._t('field Name')."</td><td>".$name."</td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','edit_field_name','Edit',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
		echo "</td>";
		echo "</tr></table>";

		shn_form_fsclose();

		//start fsopen for value
		shn_form_fsopen(_t("Values for Field"));

		//get field_value_text & field_value
		$query1 = $db->Prepare('SELECT vals_text,value,field_value_id FROM dsm_field_values WHERE field_id=?');
		$res1=$db->Execute($query1,array($field_id));

		if($data_type=="sex"){

			echo "Values are can't change for Data Type Sex,because this values are auto generated.";
		}else{
			if($res1){
				if($res1->RecordCount()>0){

					echo "<table width='60%'><tr>";
					echo "<th>"._t('Value Text').'</th>';
					echo "<th>"._t('Value').'</th>';
					echo "<th>&nbsp;</th>";
					echo "<th>&nbsp;</th></tr>";

					while($row=$res1->FetchRow()){
						$vals_text=$row["vals_text"];
						$vals=$row["value"];
						$field_value_id=$row["field_value_id"];

						echo "<tr>";
						echo "<td>".$vals_text."</td>";
						echo "<td>".$vals."</td>";
						//echo "<td>".$field_value_id."</td>"; //test only
						echo "<td>";
						shn_acl_secure_hyperlink('dsm','edit_value','Edit',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id,'field_value_id'=>$field_value_id),$text_opts='');
						echo "</td>";
						echo "<td>";
						shn_acl_secure_hyperlink('dsm','delete_value','Delete',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id,'field_value_id'=>$field_value_id),$text_opts='');
						echo "</td>";
						echo "</tr>";
					}
					echo "</tr></table>";

					if($type=="dropdown" OR $type=="radio" OR $type=="check"){
						echo "<table><tr>";
						echo "<td>";
						shn_acl_secure_hyperlink('dsm','add_new_value','Add New Value',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
						echo "</td>";
						echo "</tr></table>";
					}
				}
				if(($type=="text" OR $type=="textarea" OR $type=="date") && ($res1->RecordCount()==0)){
					echo "<table><tr>";
					echo "<td>";
					shn_acl_secure_hyperlink('dsm','add_new_value','Add New Value',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
					echo "</td>";
					echo "</tr></table>";
				}
				if(($type=="text" OR $type=="textarea" OR $type=="date") && ($res1->RecordCount()>0)){
					echo "<table><tr>";
					//echo "<td><a href=index.php?mod=dsm&act=add_new_value&field_id=".$field_id."&disease_id=".$disease_id.">"._t("Add New Value")."</a> </td>";
					echo "</tr></table>";
				}
			}
		}
		shn_form_fsclose();

		//fsopen for validation & parameters
		shn_form_fsopen(_t("Validation Rules & Parameters for Field"));
		//get validation rule
		$field_validation_query = "SELECT rule_order,rule FROM dsm_field_validation WHERE field_id=$field_id";
		$res3 = $db->Execute($field_validation_query);

		if($res3->RecordCount()>0){
			echo "<table>";
			echo "<th>"._t('Rule Order')."</th>";
			echo "<th>"._t('Rule')."</th>";
			while($row=$res3->FetchRow()){
				$rule=$row["rule"];
				$rule_order=$row["rule_order"];
					
				echo "<tr>";
				echo "<td>".$rule_order."</td>";
				echo "<td>".$rule."</td>";
				echo "</tr>";

			}
			echo "</table>";
			echo "<br><br>";
		}
		//get field_param_key & field_param
		$query2 = $db->Prepare('SELECT param_key,param,field_param_id FROM dsm_field_params WHERE field_id=?');
		$res2=$db->Execute($query2,array($field_id));

		if($res2){
			if($res2->RecordCount()>0){

				echo "<table width='60%'><tr>";
				echo "<th>"._t('Param Key')."</th>";
				echo "<th>"._t('Param')."</th>";

				while($row=$res2->FetchRow()){
					$param_key=$row["param_key"];
					$param=$row["param"];
					$field_param_id=$row["field_param_id"];

					echo "<tr>";
					echo "<td>".$param_key."</td>";
					echo "<td>".$param."</td>";
					echo "</tr>";
				}
				echo "</table>";
			}
		}

		echo "<br><br>";
		if($res3->RecordCount()>0 || $res2->RecordCount()>0){

			shn_acl_secure_hyperlink('dsm','delete_validation','Delete Validation Rule',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
		}else{

			shn_acl_secure_hyperlink('dsm','add_validation','Add Validation Rule',$stream=null,$params=array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
		}
		shn_form_fsclose();

		shn_acl_secure_hyperlink('dsm','view_disease_definition','Go Back',$stream=null,$params=array('disease_id'=>$disease_id),$text_opts='');

		shn_form_fclose();

		?></td>
	</tr>
</table>
		<?php

}

//edit field text
function shn_dsm_edit_field_text(){
	echo "<h2>"._t("Edit Field Text")."</h2>";

	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$field_value_id = $_REQUEST['field_value_id'];
	//echo $field_id."<br>";
	//echo $disease_id."<br>";

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('edit_field_text_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

		//start fsopen for text, type, name
		shn_form_fsopen(_t("Edit Field Text")); ?>
		<div class="info"><?= _t("These are the basic details of created field.");?></div>
		<?php

		//get field text
		$field_info_query = "SELECT text,type,name FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($field_info_query,array($field_id));
		$text=$res1->fields["text"];
		$type=$res1->fields["type"];
		$name=$res1->fields["name"];

		echo "<table><tr>";
		echo "<td>"._t("Old Field Text").":</td><td>".$text."</td>";
		echo "<td>"._t("New Field Text").":";
		shn_form_text(_t(""),'dsm_field_text');
		echo "</td></tr>";
		echo "<tr><td>"._t("Field Name").":</td><td>".$name."</td></tr>";
		echo "<tr><td>"._t("Field Type").":</td><td>".$type."</td></tr>";
		echo "</table>";
		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Edit Field Text"),'name="edit_text"');
		shn_form_submit(_t("Cancel"),'name="cancel"');

		shn_form_fclose();
		?></td>
	</tr>
</table>
		<?php
}

//edit field name
function shn_dsm_edit_field_name(){
	echo "<h2>"._t("Edit Field Name")."</h2>";

	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$field_value_id = $_REQUEST['field_value_id'];
	//echo $field_id."<br>";
	//echo $disease_id."<br>";

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('edit_field_name_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

		//start fsopen for text, type, name
		shn_form_fsopen(_t("Edit Field Name")); ?>
		<div class="info"><?= _t("These are the basic details of created field.");?></div>
		<?php

		//get field text
		$field_info_query = "SELECT text,type,name FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($field_info_query,array($field_id));
		$text=$res1->fields["text"];
		$type=$res1->fields["type"];
		$name=$res1->fields["name"];

		echo "<table>";
		echo "<tr><td>"._t("Field Text").":</td><td>".$text."</td></tr>";
		echo "<tr><td>"._t("Field Name").":</td><td>".$name."</td>";
		echo "<td>"._t("New Field Name").":";
		shn_form_text(_t(""),'dsm_field_name');
		echo "</td></tr>";
		echo "<tr><td>"._t("Field Type").":</td><td>".$type."</td></tr>";
		echo "</table>";
		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Edit Field Name"),'name="edit_name"');
		shn_form_submit(_t("Cancel"),'name="cancel"');

		shn_form_fclose();
		?></td>
	</tr>
</table>
		<?php
}

//update field text
function shn_dsm_edit_field_text_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];

	$text_new=$_POST['dsm_field_text'];
	$name_new=$_POST['dsm_field_name'];
	//var_dump($name_new);

	//update field text
	if(isset($_REQUEST['edit_text'])){

		$errors = array();
		if($_POST['dsm_field_text']==null){
			add_error(_t("Please fill the Field text"));
			shn_dsm_edit_field_text();
		}
		else{
			//post data from shn_dsm_edit_definition()
			$field_info_query = "SELECT text,type,name FROM dsm_fields WHERE field_id=?";
			$res1 = $db->Execute($field_info_query,array($field_id));
			$type=$res1->fields["type"];
			$name=$res1->fields["name"];

			//save text, type, name
			//$db->debug = true; //debug code
			$query1 = "UPDATE dsm_fields SET text=? ,type=? ,name=? WHERE field_id=? ";
			$res1 = $db->Execute($query1,array($text_new,$type,$name,$field_id));

			shn_dsm_edit_definition();
		}
	}
	else{
		shn_dsm_edit_definition();
	}
}

//update field name
function shn_dsm_edit_field_name_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];

	$text_new=$_POST['dsm_field_text'];
	$name_new=$_POST['dsm_field_name'];
	//var_dump($name_new);
	//update field text
	if(isset($_REQUEST['edit_name'])){

		$errors = array();
		if($_POST['dsm_field_name']==null){
			add_error(_t("Please fill the Field Name"));
			shn_dsm_edit_field_name();
		}
		else{
			//post data from shn_dsm_edit_definition()
			$field_info_query = "SELECT text,type,name FROM dsm_fields WHERE field_id=?";
			$res1 = $db->Execute($field_info_query,array($field_id));
			$text=$res1->fields["text"];
			$type=$res1->fields["type"];

			//save text, type, name
			//$db->debug = true; //debug code
			$query1 = "UPDATE dsm_fields SET text=? ,type=? ,name=? WHERE field_id=? ";
			$res1 = $db->Execute($query1,array($text,$type,$name_new,$field_id));

			shn_dsm_edit_definition();
		}
	}
	else{
		shn_dsm_edit_definition();
	}
}

//function for edit old field value
function shn_dsm_edit_value(){
	echo "<h2>"._t("Edit Field Value")."</h2>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	$field_value_id=$_REQUEST['field_value_id'];
	//var_dump($_REQUEST);

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('edit_value_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id,'field_value_id'=>$field_value_id));

		//start fsopen for value
		shn_form_fsopen(_t("Values for Field"));

		//get field_value_text & field_value
		$query1 ="SELECT field_id,vals_text,value,field_value_id FROM dsm_field_values WHERE field_value_id=?";
		$res1=$db->Execute($query1,array($field_value_id));

		if($res1){
			if($res1->RecordCount()>0){
				$row=$res1->FetchRow();
				$vals_text=$row["vals_text"];
				$vals=$row["value"];

				echo "<table width='60%'><tr>";
				echo "<th>"._t('Old Value Text').'</th>';
				echo "<th>"._t('Old Value').'</th>';
				echo "<th>&nbsp;</th></tr>";

				echo "<tr>";
				echo "<td>".$vals_text."</td>";
				echo "<td>".$vals."</td>";
				//echo "<td>".$field_value_id."</td>"; //test only
				echo "</tr>";
				echo "</tr></table>";

				echo "<table width='60%'><tr>";
				echo "<th>"._t('New Value Text').'</th>';
				echo "<th>"._t('New Value').'</th>';
				echo "<th>&nbsp;</th></tr>";

				echo "<tr>";
				echo "<td>";
				shn_form_text(_t(""),'dsm_field_value_text');
				echo "</td>";
				echo "<td>";
				shn_form_text(_t(""),'dsm_field_value');
				echo "</td>";
				//echo "<td>".$field_value_id."</td>"; //test only
				echo "</tr>";
				echo "</tr></table>";
			}
		}
		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Edit Field Value"),'name="edit_value"');
		shn_form_submit(_t("Cancel"),'name="cancel"');
		shn_form_fclose();
		?></td>
	</tr>
</table>
		<?php
}

//update field value
function shn_dsm_edit_value_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	$field_value_id=$_REQUEST['field_value_id'];
	//var_dump($_REQUEST);

	$dsm_field_value_text_new=$_POST['dsm_field_value_text'];
	$dsm_field_value_new=$_POST['dsm_field_value'];

	if(isset($_REQUEST['edit_value'])){

		$errors = array();
		if($_POST['dsm_field_value_text']==null OR $_POST['dsm_field_value']==null){
			add_error(_t("Please fill the Field Value text & Field Value"));
			shn_dsm_edit_value();
		}
		else{

			//save text, type, name
			//$db->debug = true; //debug code
			$query1 = "UPDATE dsm_field_values SET field_id=?, vals_text=? ,value=? WHERE field_value_id=?";
			$res1 = $db->Execute($query1,array($field_id,$dsm_field_value_text_new,$dsm_field_value_new,$field_value_id));

			shn_dsm_edit_definition();
		}
	}
	else{
		shn_dsm_edit_definition();
	}
}

//function for delet value
function shn_dsm_delete_value(){
	echo "<h2>"._t("Confirm to Delet Value")."</h2>";
	echo "<p>"._t("Are you sure you need to delete the following value?.")."<br/>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	$field_value_id=$_REQUEST['field_value_id'];
	//var_dump($_REQUEST);

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('delete_value_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id,'field_value_id'=>$field_value_id));

		//start fsopen for value
		shn_form_fsopen(_t("Values for Field"));

		//get field_value_text & field_value
		$query1 ="SELECT field_id,vals_text,value,field_value_id FROM dsm_field_values WHERE field_value_id=?";
		$res1=$db->Execute($query1,array($field_value_id));

		if($res1){
			if($res1->RecordCount()>0){
				$row=$res1->FetchRow();
				$vals_text=$row["vals_text"];
				$vals=$row["value"];

				echo "<table width='60%'><tr>";
				echo "<th>"._t('Old Value Text').'</th>';
				echo "<th>"._t('Old Value').'</th>';
				echo "<th>&nbsp;</th></tr>";

				echo "<tr>";
				echo "<td>".$vals_text."</td>";
				echo "<td>".$vals."</td>";
				//echo "<td>".$field_value_id."</td>"; //test only
				echo "</tr>";
				echo "</tr></table>";
			}
		}
		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Delet Field Value"),'name="delete_value"');
		shn_form_submit(_t("Cancel"),'name="cancel"');
		shn_form_fclose();
		?></td>
	</tr>
</table>
		<?php
}

//delet value
function shn_dsm_delete_value_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	$field_value_id=$_REQUEST['field_value_id'];
	//var_dump($_REQUEST);

	if(isset($_REQUEST['delete_value'])){
		$query1 = "DELETE FROM dsm_field_values WHERE field_value_id=?";
		$res1 = $db->Execute($query1,array($field_value_id));
		shn_dsm_edit_definition();
	}
	else{
		shn_dsm_edit_definition();
	}
}

//function for add new value to field
function shn_dsm_add_new_value(){
	echo "<h2>"._t("Add New Value")."</h2>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	$field_value_id=$_REQUEST['field_value_id'];
	//var_dump($_REQUEST);

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('add_new_value_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

		//start fsopen for value
		shn_form_fsopen(_t("Values for Field"));

		//get field_value_text & field_value
		$query1 = $db->Prepare('SELECT vals_text,value,field_value_id FROM dsm_field_values WHERE field_id=?');
		$res1=$db->Execute($query1,array($field_id));

		if($res1){
			if($res1->RecordCount()>0){

				echo "<table width='60%'><tr>";
				echo "<th>"._t('Value Text').'</th>';
				echo "<th>"._t('Value').'</th>';
				echo "<th>&nbsp;</th></tr>";

				while($row=$res1->FetchRow()){
					$vals_text=$row["vals_text"];
					$vals=$row["value"];
					$field_value_id=$row["field_value_id"];
					//shn_form_hidden(array('field_value_id'=>$field_value_id));

					echo "<tr>";
					echo "<td>".$vals_text."</td>";
					echo "<td>".$vals."</td>";
					echo "</tr>";
				}
				echo "</tr></table>";
			}
		}

		echo "<table width='60%'><tr>";
		echo "<th>"._t('New Value Text').'</th>';
		echo "<th>"._t('New Value').'</th>';
		echo "<th>&nbsp;</th></tr>";

		echo "<tr>";
		echo "<td>";
		shn_form_text(_t(""),'dsm_field_value_text');
		echo "</td>";
		echo "<td>";
		shn_form_text(_t(""),'dsm_field_value');
		echo "</td>";
		echo "</tr></table>";
		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Add New Value"),'name="add_value"');
		shn_form_submit(_t("Cancel"),'name="cancel"');
		shn_form_fclose();
		?></td>
	</tr>
</table>
		<?php
}

//add new value
function shn_dsm_add_new_value_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	$dsm_field_value_text_new=$_POST['dsm_field_value_text'];
	$dsm_field_value_new=$_POST['dsm_field_value'];

	if(isset($_REQUEST['add_value'])){

		$errors = array();
		if($_POST['dsm_field_value_text']==null OR $_POST['dsm_field_value']==null){
			add_error(_t("Please fill the Field Value text & Field Value"));
			shn_dsm_add_new_value();
		}
		else{
			//save text, type, name
			//$db->debug = true; //debug code
			$query1 = "INSERT INTO dsm_field_values (field_id, vals_text, value) VALUES(?,?,?)";
			$res1 = $db->Execute($query1,array($field_id,$dsm_field_value_text_new,$dsm_field_value_new));

			shn_dsm_edit_definition();
		}
	}
	else{
		shn_dsm_edit_definition();
	}
}
//delete confirmation for validation rule and pararmeter
function shn_dsm_delete_validation(){
	echo "<h2>"._t("Edit Validation")."</h2>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	shn_form_fopen('delete_validation_cr','dsm',array('req_message'=>false));
	shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

	echo "<p>"._t("Are you sure you need to delete the following field validation rules & parameters?. <br/> <br/><em>Note that all validation rules and all parameters of field will be deleted!</em>")."</p><br/>";
	//fsopen for validation & parameters
	shn_form_fsopen(_t("Validation Rules & Parameters for Field"));
	//get validation rule
	$field_validation_query = "SELECT rule_order,rule FROM dsm_field_validation WHERE field_id=?";
	$res3 = $db->Execute($field_validation_query,array($field_id));

	echo "<table>";
	echo "<th>"._t('Rule Order')."</th>";
	echo "<th>"._t('Rule')."</th>";
	while($row=$res3->FetchRow()){
		$rule=$row["rule"];
		$rule_order=$row["rule_order"];

		echo "<tr>";
		echo "<td>".$rule_order."</td>";
		echo "<td>".$rule."</td>";
		echo "</tr>";
			
	}
	echo "</table>";
	echo "<br><br>";

	//get field_param_key & field_param
	$query2 = $db->Prepare('SELECT param_key,param,field_param_id FROM dsm_field_params WHERE field_id=?');
	$res2=$db->Execute($query2,array($field_id));

	if($res2){
		if($res2->RecordCount()>0){

			echo "<table width='60%'><tr>";
			echo "<th>"._t('Param Key')."</th>";
			echo "<th>"._t('Param')."</th>";

			while($row=$res2->FetchRow()){
				$param_key=$row["param_key"];
				$param=$row["param"];
				$field_param_id=$row["field_param_id"];

				echo "<tr>";
				echo "<td>".$param_key."</td>";
				echo "<td>".$param."</td>";
				echo "</tr>";
			}
			echo "</table>";
		}
	}
	shn_form_fsclose();

	//form submit
	shn_form_submit(_t("Delete Validation"),'name="delete_validation"');
	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_fclose();
}

//delete validation
function shn_dsm_delete_validation_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	if(isset($_REQUEST['delete_validation'])){

		$query3 = "DELETE FROM dsm_field_params WHERE field_id=?";
		$res3 = $db->Execute($query3,array($field_id));

		$query4 = "DELETE FROM dsm_field_validation WHERE field_id=?";
		$res4 = $db->Execute($query4,array($field_id));

		shn_dsm_edit_definition();
			
	}
	else{

		shn_dsm_edit_definition();
	}

}

//add validation rule & parameter
function shn_dsm_add_validation(){
	echo "<h2>"._t("Edit Validation")."</h2>";

	shn_xajax_registerFunction('dsm_add_field_param');
	shn_xajax_registerFunction('dsm_delete_param');
	shn_xajax_registerFunction('dsm_put_value_in_session');
	shn_xajax_registerFunction('dsm_add_validation_rule');
	shn_xajax_registerFunction('dsm_clear_validation_rules');

	?>

<script type="text/javascript">
<!--
    //java script for display validation rule
       function add_validation_rule(){
            var validation = document.getElementById('validation_rules');
            if(validation){
                var rule = validation.options[validation.selectedIndex].value;
                var rule_text = validation.options[validation.selectedIndex].text;
                dsm_add_validation_rule(rule,rule_text);
            }
        } 
//-->
</script>
	<?php

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	?>
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('add_validation_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

		shn_form_fsopen(_t("Validation for Field"));

		$extra_opts['req']=false;
		//$extra_opts['help']=_t("Enter the Validation Critearia using <, >, ||, &  for the fied");
		$opts = dsm_validation_get_rules();
		shn_form_select($opts,_t('Validation Rule'),'validation_rules','',array('br'=>false,'value'=>'not_empty'));
		shn_form_button(_t('Add Rule'),' onclick="add_validation_rule()"');
		echo "<h4>"._t("Current Ruleset")."</h4>";
		echo "<div id='validation_rule_div'>";

		// show previously entered validations
		if(isset($validations) && count($validations)>0){
			$hidden = array();
			echo "<ul>";
			foreach($validations as $i=>$r){
				$hidden['dsm_validation_rule_'.$i] = $r;
				echo "<li>".dsm_validation_get_rule_text($r)."<div class=\"info\">".dsm_validation_get_rule_information($r,$i)."</div></li>";
			}
			echo "</ul>";
			shn_form_hidden($hidden);
		}

		echo "</div>";
		shn_form_button(_t('Clear All'),'onclick="dsm_clear_validation_rules()"');
		shn_form_fsclose();

		shn_form_fsopen(_t("Parameters"));
		?>
		<div id="param_div">
		<table>
			<tr>
				<th><?php echo _t('Key')?></th>
				<th><?php echo _t('Value')?></th>
			</tr>
			<?php
			if(isset($param_keys) && isset($param_vals)){
				if(count($param_keys)==0){
					?>
			<tr>
				<td><?php shn_form_text(_t(""),'dsm_field_param_key_1','onblur="put_value_in_session(\'param_key\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
				<td><?php shn_form_text(_t(""),'dsm_field_param_value_1','onblur="put_value_in_session(\'param_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
			</tr>
			<?php
				}else{
					foreach ($param_keys as $i=>$v){
						?>
			<tr>
				<td><?php shn_form_text(_t(""),'dsm_field_param_key_'.$i,'onblur="put_value_in_session(\'param_key\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v));?></td>
				<td><?php shn_form_text(_t(""),'dsm_field_param_value_'.$i,'onblur="put_value_in_session(\'param_value\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v)); ?></td>
			</tr>
			<?php
					}
				}
			}else{
				?>
			<tr>
				<td><?php shn_form_text(_t(""),'dsm_field_param_key_1','onblur="put_value_in_session(\'param_key\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
				<td><?php shn_form_text(_t(""),'dsm_field_param_value_1','onblur="put_value_in_session(\'param_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
			</tr>
			<?php
			}
			?>
			<tr>
				<td colspan="2"><?php shn_form_button(_t('Add New param'),' onclick="add_field_param(1)" ');?></td>
			</tr>
		</table>
		</div>

		<?php
		shn_form_fsclose();

		shn_form_submit(_t("Cancel"),'name="cancel"');
		shn_form_submit(_t("Save"),'name="save"');
		;
		shn_form_fclose();
		?></td>
	</tr>
</table>

<script type="text/javascript">

<!--
    // caller function for the xajax function       
    //delete parameter
    function delete_param(number) {
        dsm_delete_param(number,'<?php echo $disease_id;?>');          

    }
    
    // caller function for the xajax function
    function add_field_param(number){
        //var key = document.getElementById('dsm_field_param_key_'+number);
        //var val = document.getElementById('dsm_field_param_value_'+number);
        dsm_add_field_param(number,'<?php echo $disease_id;?>');
    }
    
    // variable indexes for parameters
    var param_index=1;
 
    // setter method for value index
    // called by xajax
    function setValueIndex(v){
        //alert(v);
        value_index = v;
    } 
   
    // setter method for param index
    // called by xajax
    function setParamIndex(p){
        //alert(p);
        param_index = p;
    }
    
    function put_value_in_session(type,indx,value,dis_id){
        dsm_put_value_in_session(type,indx,value,dis_id);
    }
//-->

</script>
		<?php
}

//save validation rule & parameter
function shn_dsm_add_validation_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	if(isset($_REQUEST['save'])){
		$field_param_keys=array();
		$field_param_values=array();
		$field_validations = array();
		 
		//explode value and param
		foreach($_POST as $k=>$v){
			$i = 0;
			if(preg_match('/dsm_field_param_key_\d+/',$k)!=0){
				$i = explode('dsm_field_param_key_',$k);
				$i = $i[1];
				if(strlen(trim($v))>0){
					$field_param_keys[$i] = $v;
				}

			}else if(preg_match('/dsm_field_param_value_\d+/',$k)!=0){
				$i = explode('dsm_field_param_value_',$k);
				$i = $i[1];
				if(strlen(trim($v))>0){
					$field_param_values[$i] = $v;
				}
			}else if(preg_match('/dsm_validation_rule_\d+/',$k)!=0){
				$i = explode('dsm_validation_rule_',$k);
				$i = $i[1];
				$field_validations[$i] = $v;
			}
		}

		if(count($field_validations)>0){
			$status = true;
			$param_array = array();
			foreach($field_param_keys as $k=>$v){
				$param_array[$v] = $field_param_values[$k];
			}
			foreach($field_validations as $i=>$r){
				$status &= dsm_validation_check_params($r,$i,$param_array);
			}

			$errors = !$status;
		}

		if($errors == true){
			shn_dsm_add_validation(true,$field_param_keys,$field_param_values,$field_validations);
		}else{
			$db->StartTrans();
			//$db->debug = true; //debug code
			//save field param
			$query3 = $db->Prepare('INSERT INTO dsm_field_params(param_key,param,field_id) VALUES (?,?,?)');

			$array_keys = array_keys($field_param_keys);
			foreach ($array_keys as $k){
				$db->Execute($query3,array($field_param_keys[$k],$field_param_values[$k],$field_id));
			}

			//save field validation rule
			$query4 = $db->Prepare('INSERT INTO dsm_field_validation(field_id,rule,rule_order) VALUES (?,?,?)');
			$array_keys = array_keys($field_validations);
			foreach ($array_keys as $k){
				$db->Execute($query4,array($field_id,$field_validations[$k],$k));
			}

			$failed = $db->HasFailedTrans();
			$db->CompleteTrans();
			if($failed){
				add_error(_t('An unknown error occured while saving data.'));
			}else{
				// clear session;
				unset($_SESSION['dsm']);
				unset($_POST);
			}

			shn_dsm_edit_definition();
		}
	}else{
		shn_dsm_edit_definition();
	}
}

//function for edit type
function shn_dsm_edit_field_type(){
	echo "<h2>"._t("Edit Field Type")."</h2>";

	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$type = $_REQUEST['type'];
	//echo $field_id."<br>";
	//echo $disease_id."<br>";
	//var_dump($_REQUEST);

	?>
<div id="result">
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 

		//pass form information
		shn_form_fopen('edit_field_type_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id,));

		//start fsopen for type
		shn_form_fsopen(_t("Edit Field Type")); ?>
		<div class="info"><?= _t("These are the basic details of Created field.");?></div>
		<?php

		if($type=="text" OR $type=="textarea" OR $type=="date"){
			echo "<table>";
			echo "<tr><td>"._t("Old Field Type").":</td><td>".$type."</td></tr>";
			echo "<tr><td>"._t("New Field Type").":</td><td>";
			$options = array('text'=>_t('Text Box'),'textarea'=>_t('Text Aria'),'date'=>_t('Date Field'));
			shn_form_select($options,_t(""),'dsm_field_type','',array('value'=>$type_new));
			echo "</table>";
		}

		if($type=="dropdown" OR $type=="radio" OR $type=="check"){
			echo "<table>";
			echo "<tr><td>"._t("Old Field Type").":</td><td>"._t($type)."</td></tr>";
			echo "<tr><td>"._t("New Field Type").":</td><td>";
			$options = array('dropdown'=>_t('Dropdown Box'),'radio'=>_t('Radio Button'),'check'=>_t('Check Box'));
			shn_form_select($options,_t(""),'dsm_field_type','',array('value'=>$type_new));
			echo "</table>";
		}

		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Edit Field Type"),'name="edit_type"');
		shn_form_submit(_t("Cancel"),'name="cancel"');

		shn_form_fclose();
		?></td>
	</tr>
</table>
</div>
		<?php
}

//update field type
function shn_dsm_edit_field_type_cr(){
	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$type_new = $_REQUEST['dsm_field_type'];
	//echo $field_id."<br>";
	//echo $disease_id."<br>";
	//echo $type_new."<br>";
	//var_dump($_REQUEST);

	if(isset($_REQUEST['edit_type'])){

		//post data from shn_dsm_edit_definition()
		$field_info_query = "SELECT text,name FROM dsm_fields WHERE field_id=$field_id";
		$res1 = $db->Execute($field_info_query);
		$text=$res1->fields["text"];
		$name=$res1->fields["name"];

		//update field type
		$query1 = "UPDATE dsm_fields SET text=? ,type=? ,name=? WHERE field_id=?";
		$res = $db->Execute($query1,array($text,$type_new,$name,$field_id));

		shn_dsm_edit_definition();
	}
	else{
		shn_dsm_edit_definition();
	}
}

//edit fielld data type
function shn_dsm_edit_field_data_type(){
	echo "<h2>"._t("Edit Field Data Type")."</h2>";

	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];

	?>
<div id="result">
<table style="border: none; padding: 0px; width: 890px;" cellspacing="0"
	border="0">
	<tr>
		<td><?php 
		$field_info_query = "SELECT data_type FROM dsm_fields WHERE field_id=$field_id";
		$res1 = $db->Execute($field_info_query);
		$data_type=$res1->fields["data_type"];
		//pass form information
		shn_form_fopen('edit_field_data_type_cr','dsm',$form_opts);
		shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id,'data_type'=>$data_type));

		//start fsopen for type
		shn_form_fsopen(_t("Edit Field Data Type")); ?>
		<div class="info"><?= _t("These are the basic details of Created field.");?></div>
		<?php

		echo "<table>";
		echo "<tr><td>"._t("Old Field DataType")."</td><td>".$data_type."</td></tr>";
		echo "<tr><td>"._t("New Field Data Type")."</td><td>";
		shn_form_opt_select("dsm_field_data_type",_('Filed Data Type'));
		echo "</table>";

		shn_form_fsclose();

		//form submit
		shn_form_submit(_t("Edit Field Data Type"),'name="edit_data_type"');
		shn_form_submit(_t("Cancel"),'name="cancel"');

		shn_form_fclose();
		?></td>
	</tr>
</table>
</div>
		<?php
}

//update field data type
function shn_dsm_edit_field_data_type_cr(){
	global $global;
	$db = $global['db'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$data_type_new = $_REQUEST['dsm_field_data_type'];
	$data_type_old = $_REQUEST['data_type'];
	//$db->debug=true;
	if(isset($_REQUEST['edit_data_type'])){
		if($data_type_old=="sex" && $data_type_new!=="sex"){
			//update field type
			$query1 = "UPDATE dsm_fields SET data_type=? WHERE field_id=?";
			$res = $db->Execute($query1,array($data_type_new,$field_id));
		}
		else if($data_type_old!=="sex" && $data_type_new=="sex"){
			//delete existing value
			$query_delete_old_values = "DELETE FROM dsm_field_values WHERE field_id=?";
			$res_delete = $db->Execute($query_delete_old_values,array($field_id));

			//update field type
			$query1 = "UPDATE dsm_fields SET data_type=? ,type=? WHERE field_id=?";
			$res1 = $db->Execute($query1,array($data_type_new,'radio',$field_id));
			//save field values
			$query_sex ="INSERT INTO dsm_field_values(vals_text,value,field_id,indx) VALUES ('Male','male','$field_id','1'),('Female','female','$field_id','2')";
			$res_sex = $db->Execute($query_sex);
		}else{
			//update field type
			$query1 = "UPDATE dsm_fields SET data_type=? WHERE field_id=?";
			$res = $db->Execute($query1,array($data_type_new,$field_id));
		}
		shn_dsm_edit_definition();
	}
	else{
		shn_dsm_edit_definition();
	}
}

//delete field_definiton
function shn_dsm_delete_fields(){

	global $global;
	$db = $global['db'];

	if(isset($_REQUEST['cancel'])){
		shn_dsm_view_disease_definition();
	}else{
		$module = $global['module'];
		$field_id = $_REQUEST['field_id'];

		$query1 = "DELETE FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($query1,array($field_id));

		$query2 = "DELETE FROM dsm_field_values WHERE field_id=?";
		$res2 = $db->Execute($query2,array($field_id));

		$query3 = "DELETE FROM dsm_field_params WHERE field_id=?";
		$res3 = $db->Execute($query3,array($field_id));

		$query4 = "DELETE FROM dsm_field_validation WHERE field_id=?";
		$res4 = $db->Execute($query4,array($field_id));

		$query5 = "DELETE FROM dsm_definitions WHERE field_id=";
		$res5 = $db->Execute($query5,array($field_id));

		//call shn_dsm_view_disease_definition() for view & edite
		shn_dsm_view_disease_definition();
	}
}

//function for delete definition
function shn_dsm_delete_definition(){

	global $global;
	$db = $global['db'];

	if(isset($_REQUEST['cancel'])){
		shn_dsm_add_definition();
	}else{

		$module = $global['module'];
		$disease_id = $_REQUEST['disease_id'];
		//var_dump($_REQUEST);

		$delete_case_data = "DELETE FROM dsm_case_data WHERE dis_id=?";
		$res_delete=$db->Execute($delete_case_data,array($disease_id));

		$delete_case_note = "DELETE FROM dsm_case_note WHERE dis_id=";
		$res_delete2=$db->Execute($delete_case_note,array($disease_id));

		$delete_case_count = "DELETE FROM dsm_case_count WHERE dis_id=";
		$res_delete3=$db->Execute($delete_case_count,array($disease_id));

		$query1 = $db->Prepare('SELECT field_id FROM dsm_definitions WHERE dis_id=?');
		$res1=$db->Execute($query1,array($disease_id));

		foreach($res1 as $row){
			$field_id=$row["field_id"];

			$query1 = "DELETE FROM dsm_fields WHERE field_id=?";
			$res1 = $db->Execute($query1,array($field_id));

			$query2 = "DELETE FROM dsm_field_values WHERE field_id=?";
			$res2 = $db->Execute($query2,array($field_id));

			$query3 = "DELETE FROM dsm_field_params WHERE field_id=?";
			$res3 = $db->Execute($query3,array($field_id));

			$query4 = "DELETE FROM dsm_field_validation WHERE field_id=?";
			$res4 = $db->Execute($query4,array($field_id));

			$query5 = "DELETE FROM dsm_definitions WHERE field_id=?";
			$res5 = $db->Execute($query5,array($field_id));

		}
		shn_dsm_add_definition();
	}
}

//function for add definition
function shn_dsm_add_definition(){
	echo "<h2>"._t("Disease Definitions")."</h2>";
	global $global;
	$db = $global['db'];

	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM dsm_diseases";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=10;

	$sql = "SELECT DISTINCT dis.dis_id as dis_id,dis_name,med_name,def.dis_id as fields FROM dsm_diseases dis LEFT JOIN dsm_definitions def ON dis.dis_id=def.dis_id";
	$res = $db->SelectLimit($sql,$rpp,$page*$rpp);

	echo "<div id='result'><table>";
	echo "<tr><th>"._t('Disease Name')."</th><th>"._t('Medical Name')."</th><th>"._t("Definition Status")."</th></tr>";
	while($row=$res->FetchRow()){
		echo "<tr><td>".$row['dis_name']."</td><td>".$row['med_name']."</td>";
		if($row['fields']==NULL || strlen(trim($row['fields']))==0){
			echo "<td>";
			shn_acl_secure_hyperlink('dsm','add_fields','Add Definition',$stream=null,$params=array('disease_id'=>$row['dis_id']),$text_opts='');
			echo "</td>";
		}else{
			echo "<td>";
			shn_acl_secure_hyperlink('dsm','view_disease_definition','Edit Definition',$stream=null,$params=array('disease_id'=>$row['dis_id']),$text_opts='');
			echo "&nbsp &nbsp";
			shn_acl_secure_hyperlink('dsm','delete_definition_confirm','Delete Definition',$stream=null,$params=array('disease_id'=>$row['dis_id']),$text_opts='');
			echo "</td> ";
		}
	}
	echo "</table></div>";
	echo "<br";

	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('dsm','add_definition','First',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','add_definition','&lt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','add_definition',($i+1),$stream=null,$params=array('dis_id'=>$dis_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','add_definition','&gt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','add_definition','Last',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
	}
}

//view befor delete disease definition
function shn_dsm_delete_definition_confirm(){

	echo "<h2>"._t("Confirm to Delete Disease Definition")."</h2>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$disease_id = $_REQUEST['disease_id'];

	shn_form_fopen('delete_definition','dsm',$form_opts = array('req_message'=>false));
	shn_form_hidden(array('disease_id'=>$disease_id));

	$field_query = $db->Prepare("SELECT df.* FROM dsm_definitions dd JOIN dsm_fields df ON dd.field_id=df.field_id WHERE dd.dis_id=? ORDER BY df.field_id");
	$res5 = $db->Execute($field_query,array($disease_id));

	if($res5){
		if($res5->RecordCount()>0){
			echo "<p>"._t("Are you sure you need to delete the following fields?. <br/> <br/><em>Note that all fields of definition and all data of disease will be deleted!</em>")."</p><br/>";

			echo "<table width='100%'>";
			//create edit and delete field
			while($row=$res5->FetchRow()){
				$field_id = $row['field_id'];
				$text = $row['text'];
				$type = $row['type'];
				$name = $row['name'];
				$data_type=$row['data_type'];

				echo "<tr>";
				echo "<td >";

				$query1 = "SELECT vals_text,value FROM dsm_field_values WHERE field_id=?";
				$res1 = $db->Execute($query1,array($disease_id));

				//display field type
				if ($type=="text"){
					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				//text aria
				else if ($type=="textarea"){
					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				//drop down
				else if($type=="dropdown"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :";

					$vals_array = array();
					foreach($res1 as $row){
						$vals_textb=$row["vals_text"];
						$vals=$row["value"];
						$vals_array[$vals]=$vals;

						echo $vals."<br>";
					}
				}

				//radio
				else if($type=="radio"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :";

					while($row=$res1->FetchRow()){
						$vals_text=$row["vals_text"];
						$vals=$row["value"];

						echo $vals."<br>";
					}
				}

				//check
				else if($type=="check"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :";

					while($row=$res1->FetchRow()){
						$vals_text=$row["vals_text"];
						$vals=$row["value"];

						echo $vals."<br>";
					}
				}

				//date
				else if ($type=="date"){

					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br>";
					echo _t("Field Data Type").":".$data_type. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				echo "</td>";
			}
			echo "</tr>";
			echo "</table>";
			echo "<br>";
		}
	}
	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_submit(_t("Delete"),'name="delete"');

	shn_form_fclose();

}

// view Field Data Type
function shn_dsm_view_field_data_type(){
	echo "<h2>"._t("Create Field Data Type")."</h2>";

	global $global;
	$db = $global['db'];

	shn_form_fopen('','',array('req_message'=>false));
	shn_form_fsopen(_t("View Field Data Type"));

	$field_data_type_query = "SELECT field_name,option_code,option_description FROM field_options WHERE field_name=?";
	$res1 = $db->Execute($field_data_type_query,array('dsm_field_data_type'));

	echo "<table>";
	echo "<th>"._t("Available Field DataType").'</th>';
	foreach ( $res1 as $row){
		$field_name=$res1->fields["field_name"];
		$option_code=$res1->fields["option_code"];
		$option_description=$res1->fields["option_description"];

		//echo "<tr><td>".$field_name."</td></tr>";
		echo "<tr>";
		echo "<td>".$option_description."</td>";
		//echo "<td><a href=index.php?mod=dsm&act=edit_field_data_type>"._t("Edit")."</a> </td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','delete_field_data_type','Delete',$stream=null,$params=array('option_description'=>$option_description),$text_opts='');
		echo "</td>";
		echo "<tr>";
	}
	echo "</table>";
	echo "<br/>";
	shn_acl_secure_hyperlink('dsm','create_field_data_type','Add New',$stream=null,$params=null,$text_opts='');
}

// select & create field_data_type to field_option table
function shn_dsm_create_field_data_type(){
	echo "<h2>"._t("Create Field Data Type")."</h2>";

	global $global;
	$db = $global['db'];

	shn_form_fopen('create_field_data_type_cr','dsm',array('req_message'=>false));
	shn_form_hidden(array('option_description'=>$option_description));
	shn_form_fsopen(_t("Available Field Data Type"));

	$field_data_type_query = "SELECT field_name,option_code,option_description FROM field_options WHERE field_name=?";
	$res1 = $db->Execute($field_data_type_query,array('dsm_field_data_type'));

	echo "<table>";
	foreach ( $res1 as $row){
		$field_name=$res1->fields["field_name"];
		$option_code=$res1->fields["option_code"];
		$option_description=$res1->fields["option_description"];

		//echo "<tr><td>".$field_name."</td></tr>";
		echo "<tr>";
		echo "<td>".$option_description."</td>";
		echo "</tr>";
	}
	echo "</table>";
	shn_form_fsclose();


	shn_form_fsopen(_t("New Field Data Type"));
	shn_form_text(_t("Field Data Type"),'dsm_field_data_type');
	shn_form_fsclose();

	//form submit
	shn_form_submit(_t("Save"),'name="creat_new_data_type"');
	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_fclose();
}

//insert field_data_type to field_option table
function shn_dsm_create_field_data_type_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$dsm_field_data_type=$_POST['dsm_field_data_type'];

	if(isset($_REQUEST['creat_new_data_type'])){

		$check_query = "SELECT option_description FROM field_options WHERE option_description=?";
		$res_check = $db->Execute($check_query,array($dsm_field_data_type));


		$errors = array();
		if($_POST['dsm_field_data_type']==null){
			add_error(_t("Please fill the Field Data Type"));
			shn_dsm_create_field_data_type();
		}
		else{
			if(($res_check->RecordCount()==0)){
				//$db->debug = true; //debug code
				$query1 = "INSERT INTO field_options (field_name, option_code, option_description) VALUES(?,?,?)";
				$res1 = $db->Execute($query1,array('dsm_field_data_type',$dsm_field_data_type,$dsm_field_data_type));

				add_confirmation("Add New Field Data Successful");
				shn_dsm_view_field_data_type();
			}
			else{
				add_error(_t("This Field Data Type is exsist"));
				shn_dsm_view_field_data_type();
			}
		}

	}
	else{
		shn_dsm_view_field_data_type();
	}

}

//delet field data type
function shn_dsm_delete_field_data_type(){
	echo "<h2>"._t("Delete Field Data Type")."</h2>";
	echo "<p>"._t("Are you sure you need to delete the following Field Data Type?")."<br/> ";
	global $global;
	$db = $global['db'];
	$option_description = $_REQUEST['option_description'];

	shn_form_fopen('delete_field_data_type_cr','dsm',array('req_message'=>false));
	shn_form_hidden(array('option_description'=>$option_description));
	shn_form_fsopen(_t("Field Data Type"));

	echo "<tr>";
	echo "<td>".$option_description."</td>";
	echo "</tr>";
	echo "</table>";
	shn_form_fsclose();

	//form submit
	shn_form_submit(_t("Delet Field Data Type"),'name="delet_data_type"');
	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_fclose();
}

//delet field data type confirm
function shn_dsm_delete_field_data_type_cr(){
	global $global;
	$db = $global['db'];
	$option_description = $_REQUEST['option_description'];

	if(isset($_REQUEST['delet_data_type'])){
		$query1 = "DELETE FROM field_options WHERE option_description=?";
		$res1 = $db->Execute($query1,array($option_description));
		shn_dsm_view_field_data_type();
	}
	else{
		shn_dsm_view_field_data_type();
	}
}

//view diseas list
function shn_dsm_view_disease_list(){
	echo "<h2>"._t("View Disease")."</h2>";
	global $global;
	$db = $global['db'];

	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM dsm_diseases";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=10;

	$note_query = "SELECT dis_id, dis_name,med_name FROM dsm_diseases ";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
	echo "<table>";
	echo "<tr><th>"._t("Disease")."</th><th>&nbsp;</th></tr>";
	while($row=$rs->FetchRow()){
		$dis_id=$row["dis_id"];
		$dis_name = $row["dis_name"];
		//echo "<li><div>".$row['dis_id']."</div></li>";
		echo "<tr><td>".$row['dis_name'].((strlen(trim($row['med_name']))==0)?"":(" (".$row['med_name'].")"))."</td>";
		echo "<td>";
		shn_acl_secure_hyperlink('dsm','view_disease_cases','View Cases',$stream=null,$params=array('dis_id'=>$dis_id),$text_opts='');
		echo "</td></tr>";
	}
	echo "</table>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('dsm','view_disease_list','First',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_list','&lt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_list',($i+1),$stream=null,$params=array('dis_id'=>$dis_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_list','&gt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_list','Last',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
	}

}

//view cases by dieseas
function shn_dsm_view_disease_cases(){
	echo "<h2>"._t("View Cases")."</h2>";
	global $global;
	$db = $global['db'];
	$dis_id=$_REQUEST['dis_id'];

	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM dsm_case_count";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=10;

	$note_query = "SELECT case_id FROM dsm_case_count WHERE dis_id='$dis_id'";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
	echo "<table>";
	echo "<th> Case ID </th>";
	echo "<th> </th>";

	while($row=$rs->FetchRow()){
		$case_id=$res1->fields["case_id"];
		//echo "<li><div>".$row['case_id']."</div></li>";
		echo "<tr><td>".$row['case_id']."</td><td>";
		shn_acl_secure_hyperlink('dsm','view_individual_case','View Case',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id),$text_opts='');
		echo "</td></tr>";
	}
	echo "</table>";
	echo "<br";

	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('dsm','view_disease_cases','First',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_cases','&lt',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_cases',($i+1),$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_cases','&gt',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_disease_cases','Last',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
	}

	echo "<br><br>";
	shn_acl_secure_hyperlink('dsm','view_disease_list','Go Back',$stream=null,$params=null,$text_opts='');

}

//view individual case
function shn_dsm_view_individual_case(){
	echo "<h2>"._t("Case Information")."</h2>";
	global $global;
	$db = $global['db'];
	$case_id=$_REQUEST['case_id'];
	$dis_id=$_REQUEST['dis_id'];

	shn_form_fopen('save_note_cr','dsm',$form_opts);
	shn_form_hidden(array('case_id'=>$case_id,'shn_dsm_note'=>$shn_dsm_note,'dis_id'=>$dis_id));
	shn_form_fsopen(_t("Case Information"));
	//$db->debug=true;

	$form_query = 'SELECT cd.*,df.text,df.type,df.name,dfv.vals_text FROM dsm_case_data cd JOIN dsm_fields df ON df.field_id = cd.field_id LEFT OUTER JOIN dsm_field_values dfv ON dfv.field_id=cd.field_id AND dfv.value=cd.value WHERE cd.dis_id = ? AND cd.case_id = ? ORDER BY df.indx,cd.field_id,cd.data_id';
	$res = $db->Execute($form_query,array($dis_id,$case_id));

	echo "<table valign=\"top\">";
	echo "<tr><td>"._t("Patient Identification Code")."</td><td>".$res->fields['patient_identifier']."</td></tr>";
	$_tdata_id = 0;
	$vals = array();
	while($row=$res->FetchRow()){
		$name = $row['name'];
		$type = $row['type'];
		$text = $row['text'];
		$value = $row['value'];
		$vals_text = $row['vals_text'];
		if(isset($vals[$name])==false){
			$vals[$name] = array();
			$vals[$name]['text'] = $text;
			$vals[$name]['type'] = $type;
			$vals[$name]['value'] = array($value);
			$vals[$name]['vals_text'] = array($vals_text);
		}else{
			$vals[$name]['value'][] = $value;
			$vals[$name]['vals_text'][] = $vals_text;
		}
	}

	foreach($vals as $n=>$v){
		$type = $vals[$n]['type'];
		$text = $vals[$n]['text'];
		$value = $vals[$n]['value'];
		$val_text = $vals[$n]['vals_text'];

		if ($type=="text" || $type=="textarea" || $type=="date" || $type=="dropdown"){
			echo "<tr><td>".$text."</td><td>".$value[0]."</td></tr>";
		}
		
		else if($type=='radio'){
			echo "<tr><td>".$text."</td><td>".$val_text[0]."</td></tr>";
			
		}
		else if($type=="check"){
			
			echo "<tr><td>".$text."</td><td><ul>";
			
			foreach($val_text as $value){
				echo "<li>".$value."</li>";
			}

			
			echo "</ul></td></tr>";

		}
	}
	echo "</table>";

	shn_form_fsclose();

	shn_form_fsopen(_t("Previous Notes"));


	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM dsm_case_note WHERE case_id=?";
	$rs = $db->Execute($q,array($case_id));
	$count=$rs->fields['c'];
	$rpp=2;

	$note_query = "SELECT note_id,date,note FROM dsm_case_note WHERE case_id=? ORDER BY note_id DESC";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($case_id));
	echo "<ul>";
	while($row=$rs->FetchRow()){
		echo "<li><div> Note ID : ".$row['note_id']."</div></li>";
		echo "<li><div>".$row['date']."</div></li>";
		echo "<div>".$row['note']."</div><br>";
	}
	echo "</ul>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);

	if($page>0){
		shn_acl_secure_hyperlink('dsm','view_individual_case','First',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_individual_case','&lt',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_individual_case',($i+1),$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_individual_case','&gt',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('dsm','view_individual_case','Last',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_form_fsopen(_t("New Note"));
	shn_form_wysiwyg(_t('Type the Note in This Editor'), 'shn_dsm_note' , array('value'=>$note));
	shn_form_fsclose();

	shn_form_submit(_t("Submit Note"),'name="submit_note"');
	echo "<br><br>";
	shn_acl_secure_hyperlink('dsm','view_disease_cases','Go Back',$stream=null,$params=array('dis_id'=>$dis_id),$text_opts='');

	shn_form_fclose();
}

//save note for individual case
function shn_dsm_save_note_cr(){
	echo "<h2>"._t("Case Note")."</h2>";
	global $global;
	$db = $global['db'];
	$case_id=$_REQUEST['case_id'];
	$shn_dsm_note=$_REQUEST['shn_dsm_note'];
	$dis_id=$_REQUEST['dis_id'];
	//var_dump($_REQUEST);
	//$db->debug = true;
	$date=date("Y-m-d");

	if(isset($_REQUEST['submit_note'])){

		if($_POST['shn_dsm_note']==null){
			add_error(_t("Please type the note"));
			shn_dsm_view_individual_case();
		}else{
			$query1 = "INSERT INTO dsm_case_note (case_id,dis_id,date,note) VALUES(?,?,?,?)";
			$res1 = $db->Execute($query1,array($case_id,$dis_id,$date,$shn_dsm_note));
			shn_dsm_view_disease_cases();
		}

	}else{
		shn_dsm_view_disease_cases();
	}
}

//case count disease report by graph
function shn_dsm_case_count_by_disease(){
	echo "<h2>"._t("Case Count by Disease")."</h2>";
	global $global;
	$db = $global['db'];
	echo "<img src=\"index.php?mod=dsm&act=generate_pichart_by_disease&stream=image\" border=\"2\" />";
	echo "<hr />";
}

//case count disease report by graph
function shn_dsm_case_count_per_disease(){
	echo "<h2>"._t("Case Count per Disease")."</h2>";
	global $global;
	$db = $global['db'];

	/*if(isset($_REQUEST['display'])){
	 unset($_REQUEST['display']);
	 }*/
	shn_form_fopen('case_count_per_disease','dsm',array('req_message'=>false));
	//shn_form_hidden(array('dis_id'=>$dis_id));
	shn_form_fsopen();

	$query = "SELECT dis_id,dis_name,med_name FROM dsm_diseases ";
	$rs = $db->Execute($query);

	//shn_form_date("Report Start Date","start_date",$extra_opts ='');
	//shn_form_date("Report End Date","end_date",$extra_opts ='');

	echo _t("Select Disease(s)");
	echo "<table>";
	$col_count =5;
	$i = 0;
	while($row=$rs->FetchRow()){
		$dis_id = $row['dis_id'];
		$dis_name = $row['dis_name'];

		if($i%$col_count==0){
			echo "<tr>";
		}
		$text = $row['dis_name'].((strlen(trim($row['med_name']))==0)?"":(" (".$row['med_name'].")"));
		//echo "<td>"." ".$text."<input type=\"checkbox\" name=\"vehicle\" value=\"Car\">"."</td>";
		echo "<td>";
		//echo $dis_name;
		shn_form_checkbox($dis_name,'dis_id[]',null,array('value'=>$dis_id));
		echo "</td>";
		if($i%$col_count==($col_count-1)){
			echo "</tr>";
		}
		$i++;
	}
	$rem = $i%$col_count;
	if($rem>0){
		for($j=0;$j<=$rem;$j++){
			echo "<td>&nbsp;</td>";
		}
		echo "</tr>";
	}
	echo "</table>";
	echo "<br>";

	shn_form_date("Report Start Date","start_date",$extra_opts ='');
	shn_form_date("Report End Date","end_date",$extra_opts ='');

	shn_form_submit(_t("View Graph"),'name="display"');
	shn_form_fsclose();

	if($_REQUEST['display']){
		$dis_id = '';

		foreach($_REQUEST['dis_id'] as $k=>$v){
			$dis_id .= '&dis_id[]='.$v;
		}
			
		$start_date=$_REQUEST['start_date'];
		$end_date=$_REQUEST['end_date'];

		$errors = false;
		if($start_date==null || $end_date==null){
			add_error(_t("Please fill the Report Start Date & Report End Date Fields"));
			$errors = true;
		}else{
			echo "<img src=\"index.php?mod=dsm&act=generate_linechart_per_disease&stream=image$dis_id&start_date=$start_date&end_date=$end_date\" border=\"2\" />";
			echo "<br><br>";
			shn_acl_secure_hyperlink('dsm','case_count_per_disease','Go Back',$stream=null,$params=null,$text_opts='');
		}
	}
	shn_form_fclose();
}

//delete disease symptoms
function shn_dsm_delete_disease_symptom_confirm(){
	echo "<h2>"._t("Confirm to Delete  Disease Symptom")."</h2>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$sym_id = $_REQUEST['sym_id'];

	shn_form_fopen('disease_delete_symptom_cr','dsm',$form_opts = array('req_message'=>false));
	shn_form_hidden(array('sym_id'=>$sym_id));
	shn_form_fsopen('Symptom');

	$symptom_query = "SELECT sym_id,description FROM dsm_symptoms WHERE sym_id=?";
	$res = $db->Execute($symptom_query,array($sym_id));
	//$sym_id=$res->fields["sym_id"];
	$description = $res->fields['description'];
	echo "<p>"._t("Are you sure you need to delete this symptom <br/> <br/><em>Note that symptom will be deleted permanently from disease!</em>")."</p><br/>";
	echo "<ul>";
	echo "<div> Description : ".$description."</div>";
	echo "</ul>";

	shn_form_fsclose();

	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_submit(_t("Delete"),'name="delete"');
	shn_form_fclose();
}

//delete disease symptom cr
function shn_dsm_disease_delete_symptom_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$sym_id = $_REQUEST['sym_id'];

	if(isset($_REQUEST['cancel'])){

		shn_dsm_edit_disease();
	}else{

		$delete_diseas_symptom = "DELETE FROM dsm_disease_symptoms WHERE sym_id=?";
		$res_dis_sym_delete = $db->Execute($delete_diseas_symptom,array($sym_id));

		shn_dsm_edit_disease();
	}
}

//add disease symptoms cr
function shn_dsm_add_disease_symptoms_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$dis_id = $_REQUEST['dis_id'];
	//var_dump($_REQUEST);
	$primary_symptoms=$_POST['primary'];
	$minor_symptoms=$_POST['minor'];

	if(isset($_REQUEST['primary_symptom'])){
		foreach($primary_symptoms as $sym_id){
			$query1 = "INSERT INTO dsm_disease_symptoms(dis_id,sym_id,code,priority) VALUES(?,?,?,?)";
			$res1 = $db->Execute($query1,array($dis_id,$sym_id,'sym','Primary'));
			shn_dsm_edit_disease();
		}
	}
	else if(isset($_REQUEST['minor_symptom'])){

		foreach($minor_symptoms as $sym_id){
			$query2 = "INSERT INTO dsm_disease_symptoms(dis_id,sym_id,code,priority) VALUES(?,?,?,?)";
			$res2 = $db->Execute($query2,array($dis_id,$sym_id,'sym','Minor'));
			shn_dsm_edit_disease();
		}
	}


}

//edit disesse general detail (from edit_dis.inc)
function shn_dsm_edit_general_details_cr(){

	//include_once $global['approot'] . '/mod/dsm/edt_dis.inc';
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	//$db->debug=true;
	$dis_id = $_SESSION['disease_id'];
	//var_dump($_REQUEST);
	$name = $_POST['name'];
	$med_name = $_POST['med_name'];
	$cause = $_POST['cause'];
	$carrier = $_POST['carrier'];
	$age_group = $_POST['age_groups'];

	if(isset($_REQUEST['save_general'])){

		if($_POST['name']==null){

			add_error(_t("Please fill Disease Name"));
			shn_dsm_edit_disease();
		}else{

			$query1 = "UPDATE dsm_diseases SET dis_name=?,  med_name=?, age_group=?, cause=?, carrier=? WHERE dis_id=?";
			$res1 = $db->Execute($query1,array($name,$med_name,$age_group,$cause,$carrier,$dis_id));
			shn_dsm_edit_disease();
		}
	}else{

		shn_dsm_edit_disease();
	}
}

//edit disease factor
function shn_dsm_edit_factors_cr(){

	//include_once $global['approot'] . '/mod/dsm/edt_dis.inc';
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	//$db->debug=true;
	$dis_id = $_SESSION['disease_id'];
	//var_dump($_REQUEST);
	$eff_gender = $_POST['eff_gender'];
	$dri_water = $_POST['dri_water'];
	$nutrition_level = $_POST['nutrition_level'];
	$sanitary = $_POST['sanitary'];
	$seasons = $_POST['seasons'];

	if(isset($_REQUEST['save_factors'])){

		$query1 = "UPDATE dsm_diseases_risks SET eff_gender=?,  dri_water=?, nutrition_level=?, sanitary=?, seasons=? WHERE dis_id=?";
		$res1 = $db->Execute($query1,array($eff_gender,$dri_water,$nutrition_level,$sanitary,$seasons,$dis_id));
		shn_dsm_edit_disease();

		/* $_SESSION['eff_gender'] = $eff_gender;
		 $_SESSION['drink_water'] = $dri_water;
		 $_SESSION['nutrition'] = $nutrition_level;
		 $_SESSION['sanitary'] = $sanitary;
		 $_SESSION['seasons'] = $seasons;*/

	}else{

		shn_dsm_edit_disease();
	}
}
?>
