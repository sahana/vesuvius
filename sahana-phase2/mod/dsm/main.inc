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

    shn_sub_mod_menuopen(_t('Patients/Cases'));
    shn_mod_menuitem('rep_dis', _t('Report a Patient'));
    shn_mod_menuitem('search_case', _t('Search'));
    shn_sub_mod_menuclose();
    
    shn_mod_menuitem('sur_rep', _t('Surviellance Report'));
       
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
    $sql = "DELETE FROM dsm_disease_symptoms WHERE dis_id='{$dis_id}'";

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
