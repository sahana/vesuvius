<?php

/**
 * DSM security.inc.php
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
if(isset($global['module_actions'])==false){
    $global['module_actions'] = array();
}
$actions = array();

$actions[_t('Admin Default')]['functions'] = array ('shn_dsm_adm_default','shn_dsm_adminmenu');

$actions[_t('Disease Definition Admin Page')]['functions'] = array ('shn_dsm_adm_disease_definitions');

$actions[_t('Special Risks')]['functions'] = array ('shn_dsm_adm_dri_water','shn_dsm_adm_age_groups','shn_dsm_adm_nutrition_level','shn_dsm_adm_sanitary','shn_dsm_adm_seasons');
$actions[_t('Special Risks')]['table_perms'] = array ('field_options'=>'crdu','dsm_diseases_risks'=>'rdu');

$actions[_t('Delete Symptoms')]['functions'] = array ('shn_dsm_adm_delete_symptom','shn_dsm_adm_delete_symptom_confirm','shn_dsm_adm_delete_symptom_cr');
$actions[_t('Delete Symptoms')]['table_perms'] = array ('dsm_symptoms'=>'rd','dsm_disease_symptoms'=>'rd');

$actions[_t('Disease Definition Manager')]['functions'] = array ('shn_dsm_adm_disease_definitions','shn_dsm_adm_delete_disease','shn_dsm_add_definition','shn_dsm_adm_view_disease_for_delete_case');

$actions[_t('Delete Disease')]['functions'] = array ('shn_dsm_adm_disease_definitions','shn_dsm_adm_delete_disease','shn_dsm_adm_delete_disease_confirm','shn_dsm_adm_delete_disease_cr');
$actions[_t('Delete Disease')]['table_perms'] = array ('dsm_diseases'=>'rd','dsm_case_data'=>'d','dsm_case_note'=>'d','dsm_case_count'=>'d','dsm_disease_symptoms'=>'d','dsm_diseases'=>'d','dsm_definitions'=>'rd','dsm_field_values'=>'d','dsm_field_params'=>'d','dsm_field_validation'=>'d');

$actions[_t('Edit Disease')]['functions'] = array ('shn_dsm_edit_disease','_shn_dsm_print_header','_shn_edit_tab_menu','_shn_dsm_edit_disease','shn_dsm_edit_general_detailsl','shn_dsm_edit_factors','_shn_dsm_edit_disease_symptoms','_shn_update_disease_symtoms','_shn_dsm_disease_details','_shn_dsm_edit_disease','shn_dsm_edit_general_details_cr','shn_dsm_edit_factors_cr','shn_dsm_delete_disease_symptom_confirm','shn_dsm_disease_delete_symptom_cr');
$actions[_t('Edit Disease')]['table_perms'] = array ('dsm_diseases'=>'rdu','dsm_disease_symptoms'=>'rdu','dsm_symptoms'=>'rdu','dsm_diseases_risks'=>'rdu');

$actions[_t('Edit/Delete Disease Definition')]['functions'] = array ('shn_dsm_adm_disease_definitions','shn_dsm_add_definition','shn_dsm_view_disease_definition','shn_dsm_edit_definition','shn_dsm_delete_fields_confirm','shn_dsm_delete_fields');
$actions[_t('Edit/Delete Disease Definition')]['table_perms'] = array ('field_options'=>'crd','dsm_cases'=>'crd','dsm_case_count'=>'crd','dsm_case_data'=>'crd','dsm_case_note'=>'crd','dsm_definitions'=>'crd','dsm_fields'=>'crdu','dsm_field_params'=>'crd','dsm_field_validation'=>'crd','dsm_field_values'=>'crdu');

$actions[_t('Delete Case')]['functions'] = array ('shn_dsm_adm_disease_definitions','shn_dsm_adm_view_disease_for_delete_case','shn_dsm_adm_view_disease_cases_for_delete_case','shn_dsm_adm_view_individual_case_for_delete_case','shn_dsm_adm_delete_case','shn_dsm_adm_delete_case_note','shn_dsm_adm_delete_case_note_cr');
$actions[_t('Delete Case')]['table_perms'] = array ('dsm_diseases'=>'rd','dsm_case_data'=>'d','dsm_case_note'=>'d','dsm_case_count'=>'d','dsm_disease_symptoms'=>'d','dsm_diseases'=>'d');

$actions[_t('User Home')]['functions'] = array ('shn_dsm_default');

$actions[_t('Add Disease')]['functions'] = array ('shn_dsm_add_dis','_shn_dsm_get_data','_shn_dsm_validate','_shn_dsm_set_datails','_shn_dsm_add_symptoms','_shn_symtoms_todb','_shn_dsm_confirm','_shn_dsm_write_to_db','add_symptoms');
$actions[_t('Add Disease')]['table_perms'] = array ('dsm_symptoms'=>'c','dsm_diseases'=>'c','dsm_disease_symptoms'=>'c','dsm_diseases_risks'=>'c');

$actions[_t('Report Disease')]['functions'] = array ('shn_dsm_rep_dis');
$actions[_t('Report Disease')]['table_perms'] = array ('person_uuid'=>'c','dsm_diagnosis'=>'c');

$actions[_t('Surviellance Reports ')]['functions'] = array ('shn_dsm_sur_rep','_shn_dsm_tab_menu','_shn_dsm_show_locations','_shn_dsm_show_disease_symptoms','_shn_dsm_show_risk','_shn_dsm_show_cost',' _shn_dsm_show_statistics','_shn_dsm_show_general');
$actions[_t('Surviellance Reports ')]['table_perms'] = array ('dsm_diseases'=>'r','dsm_symptoms'=>'r','dsm_disease_symptoms'=>'r');

$actions[_t('Edit Case')]['functions'] = array ('shn_dsm_edit_case','_shn_dsm_case_tab_menu','_shn_dsm_edit_contacts','_shn_dsm_edit_case','_shn_dsm_populate_case');
$actions[_t('Edit Case')]['table_perms'] = array ('dsm_diagnosis'=>'r','contact'=>'r');

$actions[_t('Add/Delete Field Data Type')]['functions'] = array ('shn_dsm_create_field_data_type','shn_dsm_create_field_data_type_cr','shn_dsm_delete_field_data_type','shn_dsm_delete_field_data_type_cr');
$actions[_t('Add/Delete Field Data Type')]['table_perms'] = array ('field_options'=>'crd');

$actions[_t('Add Definition')]['functions'] = array ('shn_dsm_add_definition','shn_dsm_save_definition','shn_dsm_view_disease_definition','shn_dsm_add_fields','shn_dsm_delete_fields_confirm','shn_dsm_delete_fields','shn_dsm_move_field','shn_dsm_edit_definition','shn_dsm_edit_field_text','shn_dsm_edit_field_name','shn_dsm_edit_field_text_cr','shn_dsm_edit_field_name_cr','shn_dsm_edit_value','shn_dsm_edit_value_cr','shn_dsm_delete_value','shn_dsm_delete_value_cr','shn_dsm_add_new_value','shn_dsm_add_new_value_cr','shn_dsm_delete_validation','shn_dsm_delete_validation_cr','shn_dsm_add_validation','shn_dsm_add_validation_cr','shn_dsm_edit_field_type','shn_dsm_edit_field_type_cr','shn_dsm_edit_field_data_type','shn_dsm_edit_field_data_type_cr','shn_dsm_delete_fields','shn_dsm_delete_definition','shn_dsm_add_definition','shn_dsm_delete_definition_confirm','');
$actions[_t('Add Definition')]['table_perms'] = array ('field_options'=>'crd','dsm_cases'=>'crd','dsm_case_count'=>'crd','dsm_case_data'=>'crd','dsm_case_note'=>'crd','dsm_definitions'=>'crd','dsm_fields'=>'crdu','dsm_field_params'=>'crd','dsm_field_validation'=>'crd','dsm_field_values'=>'crdu');

$actions[_t('New Case')]['functions'] = array ('shn_dsm_disease_form','_show_data_entry_form','_show_confirm_data_form','_save_form_data','_show_saved_data');
$actions[_t('New Case')]['table_perms'] = array ('dsm_cases'=>'crd','dsm_case_count'=>'crd','dsm_case_data'=>'crd','dsm_definitions'=>'crd','dsm_fields'=>'crdu');

$actions[_t('Search Case')]['functions'] = array ('shn_dsm_search_case',' _shn_search_case_default','_shn_dsm_search_case','_shn_dsm_search_results');
$actions[_t('Search Case')]['table_perms'] = array ('field_options'=>'r','dsm_diseases'=>'r','dsm_case_data'=>'r','dsm_fields'=>'r','dsm_field_data_type'=>'r');

$actions[_t('View Case')]['functions'] = array ('shn_dsm_view_disease_list','shn_dsm_view_disease_cases','shn_dsm_view_individual_case','shn_dsm_save_note_cr','shn_dsm_case_count_by_disease','shn_dsm_case_count_per_disease');
$actions[_t('View Case')]['table_perms'] = array ('dsm_diseases'=>'r','dsm_case_count'=>'r','dsm_case_data'=>'r','dsm_fields'=>'r','dsm_field_values'=>'r','dsm_case_note'=>'rc');

$actions[_t('Case Count by Disease')]['functions'] = array ('shn_dsm_case_count_by_disease','shn_image_dsm_generate_pichart_by_disease');
$actions[_t('Case Count by Disease')]['table_perms'] = array ('dsm_diseases'=>'r','dsm_case_count'=>'r');

$actions[_t('Case Count per Disease')]['functions'] = array ('shn_dsm_case_count_per_disease','shn_image_dsm_generate_linechart_per_disease');
$actions[_t('Case Count per Disease')]['table_perms'] = array ('dsm_diseases'=>'r','dsm_case_count'=>'r');

$actions[_t('Sirviellance Report')]['functions'] = array ('shn_dsm_sur_rep','_shn_dsm_tab_menu','_shn_dsm_show_locations','_shn_dsm_show_disease_symptoms','_shn_dsm_show_risk','_shn_dsm_show_cost','_shn_dsm_show_statistics','_shn_dsm_show_general');
$actions[_t('Sirviellance Report')]['table_perms'] = array ('dsm_diseases'=>'r','dsm_disease_symptoms'=>'r','dsm_symptoms'=>'r');

$actions[_t('Report A Patient')]['functions'] = array ('shn_dsm_rep_dis','_shn_dsm_set_symptoms','_shn_dsm_commit_patient','_shn_confirm_patient_todb','_shn_dsm_set_patient','_shn_patient_symptoms','_shn_dsm_set_patient','_shn_patient_location','_shn_dsm_print_header','_shn_print_form_one');
$actions[_t('Report A Patient')]['table_perms'] = array ('person_uuid'=>'c','dsm_diagnosis'=>'r');

$actions[_t('Edite Disease')]['functions'] = array ('shn_dsm_edit_disease','_shn_update_disease_details','_shn_dsm_disease_details','_shn_dsm_disease_factors','_shn_update_disease_factors','_shn_dsm_edit_disease_symptoms','_shn_update_disease_symtoms','_shn_dsm_disease_details','shn_dsm_add_disease_symptoms_cr');
$actions[_t('Edite Disease')]['table_perms'] = array ('dsm_diseases'=>'ru','dsm_disease_symptoms'=>'rcd','dsm_symptoms'=>'rcd');

$actions[_t('Search Disease')]['functions'] = array ('shn_dsm_search_dis','_shn_search_dis_default','_shn_dsm_searching','_shn_dsm_search_results','_shn_update_disease_factors','_shn_dsm_edit_disease_symptoms','_shn_update_disease_symtoms','_shn_dsm_disease_details','shn_dsm_add_disease_symptoms_cr');
$actions[_t('Search Disease')]['table_perms'] = array ('dsm_diseases'=>'ru','dsm_disease_symptoms'=>'rcd','dsm_symptoms'=>'rcd');

$global['module_actions']=array('dsm'=>$actions);
?>