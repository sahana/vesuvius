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
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dsm
 * @subpackage  dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
global $global;
include_once $global['approot'] . '/inc/lib_menu.inc';
include_once $global['approot'] . '/mod/dsm/lib_dsm.inc';
include_once $global['approot'] . '/mod/dsm/dsm_report.inc';
include_once $global['approot'] . "/inc/lib_form.inc";

global $disease_A_B;

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
	//////////////////////////////
	shn_sub_mod_menuopen(_t('Patients/Cases'));
	shn_mod_menuitem('rep_dis', _t('Report a Patient'));
	shn_mod_menuitem('search_case', _t('Search'));
	shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_t("Reports"));
	shn_mod_menuitem('sur_rep', _t('Surviellance Report'));
	shn_mod_menuitem('report', _t('Report'));
	shn_mod_menuitem("report_weekly_communicable_diseases",_t("Weekly Communicable Diseases"),$module);
        shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_t('RTBS'));
	shn_mod_menuitem('h544',_t('H544'));
	shn_mod_menuitem('h544_list_view',_t('View'));
	shn_mod_menuitem("report_weekly_communicable_diseases",_t("Weekly Communicable Diseases"),$module);
	shn_sub_mod_menuclose();
	shn_mod_menuclose();
	
	
    //include the main menu so that the user can navigate outside the module
	include $global['approot'] . '/inc/handler_mainmenu.inc';
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
//	    default :
//	    	{
//	    		//_shn_dsm_get_data(); //every time display the things
//	    	}
	    		
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
//	    case 'contact' :
//			{
//				_shn_patient_contact();
//				break;
//			}
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
        case 'edit_dis' :
			{
				print 'edit dis';
				_shn_update_disease_details();
				_shn_dsm_disease_details($dis_uuid);
				break;
			}
		case 'factors' :
			{
				
				//_shn_edit_tab_menu();
				_shn_dsm_disease_factors();
				break;
			}
        case 'edit_factors' :
			{
				print 'edit fac';
				_shn_update_disease_factors();
				break;
			}
		case 'symptoms' :
			{
               // _shn_edit_tab_menu(); print $_REQUEST['seq'];
                _shn_dsm_disease_symptoms();
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
				 print $dis_uuid;
//				_shn_edit_tab_menu();
				_shn_dsm_disease_details($dis_uuid);
				break;
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
	$sql = "DELETE FROM disease_symptoms WHERE dis_id='{$dis_id}'";
	
	$sql = "DELETE FROM diseases WHERE dis_id='{$dis_id}'";
	
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
			$name = $_POST['name'];
			$disease = $_POST['disease'];
			_shn_dsm_searching($name, $disease);
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


// author: hayeshais@gmail.com
function shn_dsm_report_weekly_communicable_diseases()
{
    shn_dsm_weekly_communicable_diseases_form();
 
}


function shn_dsm_weekly_communicable_diseases_form() {
        global $global;
        $db = $global['db'];

	display_errors();
?>
	<h1 align="center"><?php print _t("Weekly Return of Communicable Diseases"); ?></h1> 
<?php	
	shn_form_fopen('weekly_report_of_communicable_diseases',null,array('req_message'=>true)); 
	shn_form_hidden(array('seq'=>'validate'));
	shn_form_fsopen(_t('Select the filter type')); 
		
	echo '<table> <tbody> <tr> <td colspan="2">';
	$province = _shn_dsm_get_province();
	shn_form_select($province,_t('Province'),'province' ); 
	echo '</td> <td>Health</td> <td>H 399</td> </tr> <tr> <td colspan="2">';
		
	$district =_shn_dsm_get_district();
	shn_form_select($district,_t('District'),'district'); 
	echo '</td> <td colspan="2">'; 

	$moh_area = _shn_dsm_get_moh_area();
	shn_form_select($moh_area,_t('M.O.H. Area'),'moh_area'); 
	echo '</td> </tr>  <tr>  <td colspan="2"> '; 

	$rdhs_div = _shn_dsm_get_rdhs_div();
	shn_form_select($rdhs_div,_t('R.D.H.S. Div'),'rdhs_div'); 
	echo '</td> <td>Week Ending</td> <td>';

	include 'class_week_start_end_date.php';
	$vObj = new weekstartend();
	echo $vObj->gen_cal().'</td> </tr> </tbody> </table><br />';
	 
	shn_form_submit(_t("Generate Report"));
    	shn_form_fsclose();
     	shn_form_fclose();

    	echo '<br />';
} 


function shn_dsm_weekly_report_of_communicable_diseases() { 

	if (_shn_dsm_header_validate()) {

		shn_dsm_weekly_communicable_diseases_form();
		_shn_dsm_weekly_report_of_communicable_diseases();
	}
	else {
		shn_dsm_weekly_communicable_diseases_form();
	}


}


function shn_dsm_h544()
{
    global $global;
	include_once $global['approot'] . '/mod/dsm/h544.inc';

	switch ($_REQUEST['seq']){
	    case 'validate' : {
	        if(!_shn_dsm_h544_validate()){
	            _shn_dsm_h544_input_form();
	        }else{
	            _shn_dsm_h544_to_session();
	            _shn_dsm_h544_location_form();
	        }
	        break;
	    }
	    case 'location':{
	        _shn_dsm_h544_location_to_session();
	        _shn_dsm_h544_commit();
	        break;
	    }
	    default : {
	        _shn_dsm_h544_input_form();
	        break;
	    }
	}
}

function shn_dsm_h544_list_view()
{
    include_once $global['approot'] . '/inc/lib_menu.inc';
    global $global;
    $db = $global['db'];
    echo '<h1>View submited diseases</h1>';
    $sql = "SELECT notify_id FROM rtbs_h544";
    $result = $db->Execute($sql);
    
    while(!$result->EOF){
        $id = $result->fields['notify_id'];
        echo "<a href=index.php?mod=dsm&act=h544_view&id={$id}>{$id}</a><BR>";
        $result->MoveNext();
    }
}

function shn_dsm_h544_view()
{
    include_once $global['approot'] . "/inc/lib_form.inc";
    global $global;
    $db = $global['db'];
    $id = $_REQUEST['id'];
   
    $sql = "SELECT * FROM rtbs_h544 WHERE notify_id='{$id}'";
    $result = $db->Execute($sql);
    echo '<h1>Disease information</h1>';
    
    shn_form_fopen('h544_list_view',null,array('req_message'=>false));
    shn_form_fsopen(_t('Disease information'));
    shn_form_label(_t('Notification ID'),$result->fields['notify_id']);
    shn_form_label(_t('Institute'),$result->fields['institute']);
    shn_form_label(_t('Name of the Patient'),$result->fields['name_of_patient']);
    shn_form_label(_t('Name of the Guardian'),$result->fields['name_of_the_guardian']);
    
    $sql1 = "SELECT disease_name FROM rtbs_disease WHERE disease_id={$result->fields['disease_id']}";
    $r = $db->Execute($sql1);
    shn_form_label(_t('Disease'),$r->fields['disease_name']);
    
    shn_form_label(_t('Date onset'),$result->fields['date_of_onset']);
    shn_form_label(_t('Date of admission'),$result->fields['date_of_admission']);
    shn_form_label(_t('BHT number'),$result->fields['bht_no']);
    shn_form_label(_t('Ward'),$result->fields['ward']);
    shn_form_label(_t('Age'),$result->fields['age']);
    
    if($result->fields['age']=='m'){
        $sex = 'Male';
    }
    else{
        $sex = 'Female';
    }
    shn_form_label(_t('Sex'),$sex);
    shn_form_label(_t('Laboratory Results'),$result->fields['laboratory_results']);
    shn_form_label(_t('Home address'),$result->fields['home_address']);
    shn_form_label(_t('Telephone Number'),$result->fields['telephone_number']);
    shn_form_label(_t('Name of the doctor'),$result->fields['name_of_doctor']);
    shn_form_label(_t('Status of the doctor'),$result->fields['status_of_doctor']);
    shn_form_label(_t('Date'),$result->fields['date']);
    shn_form_submit(_t('OK'));
    shn_form_fsclose();
    shn_form_fclose();
}

?>