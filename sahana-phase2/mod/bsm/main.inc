 <?php
/**
* The Sahana Disease Surveillance Module - Main
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	Nuwan Waidyanatha <waidyanatha@gmail.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	mod
* @subpackage   bsm
* @tutorial
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/


//include_once $global['approot']."/inc/lib_modules.inc";
//include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
include_once $global['approot'].'inc/lib_xajax.inc';
include_once $global['approot'].'inc/lib_paging.inc';
include_once $global['approot']."/inc/lib_uuid.inc";
//include_once $global['approot']."/mod/msg/errors.inc";
//require_once $global['approot']."/inc/lib_misc.inc";


/**
 * Biosurveillance main menu
 */
function shn_bsm_mainmenu(){
    global $global;
    $module = $global['module'];

    shn_mod_menuopen("Biosurveillance");
    shn_mod_menuitem("default", _("Home"), $module) ;
    shn_sub_mod_menuopen(_("Manage Health"));
    shn_sub_mod_menuitem("search&entity=location", _("Locations"));
    shn_sub_mod_menuitem("search&entity=service", _("Services"));
    shn_sub_mod_menuitem("search&entity=person", _("Persons"));
    shn_sub_mod_menuitem("search&entity=facility", _("Facilities"));
    shn_sub_mod_menuitem("search&entity=disease", _("Diagnosis"));
    shn_sub_mod_menuitem("search&entity=cases", _("Cases"));
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_('Detection Analysis'));
    shn_sub_mod_menuitem("report&entity=spatialscan", _("Spatial Scan"));
    shn_sub_mod_menuitem("report&entity=temporalscan", _("Temporal Scan"));
    shn_sub_mod_menuitem("report&entity=tipmon", _("TipMon"));
    shn_sub_mod_menuitem("report&entity=wsare", _("WSARE"));
    shn_sub_mod_menuitem("report&entity=weka", _("Weka"));
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_('Standard Reports'));
    shn_sub_mod_menuitem("report&entity=cases", _("Periodic disease counts by location"));
    shn_sub_mod_menuitem("report&entity=service", _("Periodic service status by location"));
    shn_sub_mod_menuitem("report&entity=service", _("Periodic case status by location"));
    shn_sub_mod_menuclose();
    shn_mod_menuclose() ;
    
    include $global['approot']."/inc/handler_mainmenu.inc";
}
function shn_bsm_default(){
    ?>
    <h1 align="center"><?php print _("Biosurveillance Module"); ?> </h1>
    <div class="info"><?=_("Module is geared for recording and detecting diseases by analysisng the case data over geographical or temporal spread,
     curretly for the human species but extendible to other species like animals and crops (future work). The User Interfaces are particitioned in to
    managment of entities, detection analysis for disease surveillance, and stadnrad periodic reports");?><br/><br/>
     <h2><?=_("Synopsis of the entities, their relevance, and relationship ");?></h2>
    <table>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=location'.'">'._("Location").'</a>';?></td>
        <td><?=_("Each person, facility, case, and service can be tagged with a location for geospatial analysis. Locations are grouped categorically
                (e.g. Health location structure, Governance location structure, Judicial location structure) and by type (e.g. National, Provincial,
                Ditrict, Divisional, Tribunal, etc) with a hierarchical chain defining the parent and child relationships. ");?>
        </td></tr>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=service'.'">'._("Service").'</a>';?></td>
        <td><?=_("Especially Healt Care Workers and Facilities are associated with providing services such as at the time of detecting a significan disease
                a hospital (facility) reporting to the Medical Officer of Health who intern is assigned the task of verifying the detected notifiabledisease
                and inspecting the patient residence. These services (or tasks) can be monotored through the service sub module.");?>
    </td></tr>
        <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=person'.'">'._("Person").'</a>';?></td>
        <td><?=_("Typically there are two categories of persons: Healthcare Workers and Patients (or if used for animals:
            Healthcare Workers + Vetenarians, and Animal Patients. The module allows the implementers to define the 
            categories and the associated types for each category at will.");?><br/></td></tr>
     <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=facility'.'">'._("Facility").'</a>';?></td>
        <td><?=_("Hospitals, Clinic, Laboratories, Maternity Homes, etc are defined as facilities. Cases, Persons, and Services are associated with Facilities.
                The user may define the facility types (General Hospital, District Hospital, etc as well as identify the address and contact details of a Facility.
                When recording a case the user may identfy the facility the case was reported. Thereby, allowing follow up of the case if required.");?>
        </td></tr>
    <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=disease'.'">'._("Diagnosis").'</a>';?></td>
        <td><?=_("Diagnosis is the prociess of identifying the disease of a subject based on the presented syndrome (symptoms and signs). This section provides the user
                with the interfaces to define the diseases and assocaited signs, symptoms, and causality factors. When constructing a case the user has the option of defining
                the disease and signs but mandetorily identify the symptoms presented by the patient regardless of a diagnosis.");?>
        </td></tr>
     <tr><td><?php echo '<a align="left" '.'" href="index.php?mod=bsm&act=search&entity=cases'.'">'._("Cases").'</a>';?></td>
        <td><?=_("A patient will report their symptoms to a physician who will record the signs and diagnose the disease, if possible. This historic information is recorded
                as a case associated with a facility, location, person along with medical diagnosis disease and syndrome information. Each case may be assigned a series of services
                such as visiting the patient residence, laboratory testing, periodic care procedures, etc.");?>
        </td></tr>
     </table>

    <?php
}
//function shn_bsm_mng_loc(){
//    include_once ("loc_form.inc");
//    _shn_bsm_form_location(false);
//}
function shn_bsm_search() {
    global $global;
    global $conf;

    $_SESSION['bsm']['main']['entity']= trim($_GET['entity']);
    $_SESSION['bsm']['main']['action']= trim($_GET['act']);
    echo '<h1 align="center">Search '.$_SESSION['bsm']['main']['entity'].'</h1>';

    require ($global['approot'].'mod/bsm/'.$_SESSION['bsm']['main']['action'].'_'.$_SESSION['bsm']['main']['entity'].'.inc');
//print($_REQUEST['seq']);
    switch ($_REQUEST['seq'])
    {
        case 'fetch' :
            shn_bsm_search_default($_SESSION['bsm']['main']['action'].'&entity='.
            $_SESSION['bsm']['main']['entity'],'Search again or proceed to add new, edit or delete exisiting.');
            $sql = shn_bsm_search_result();
            shn_bsm_search_result_vw($sql);
            break;

        case 'lukup':
            $_SESSION['bsm']['main']['rtnid'] = trim($_GET['rtnid']);
            $_SESSION['bsm']['main']['rtnfrm'] = trim($_GET['rtnfrm']);
            $_SESSION['bsm']['main']['rtnfk'] = trim($_GET['rtnfk']);
            $_SESSION['bsm']['main']['disease'] = trim($_REQUEST['disease']);
            if ($_GET['lukupid']==''){

                shn_bsm_search_default($_SESSION['bsm']['main']['action'].'&entity='.
                    $_SESSION['bsm']['main']['entity'].'&seq=lukup'
                    ,_('Lookup required ').$_SESSION['bsm']['main']['entity']);
                if ($_GET['offset'])
                {
                    $sql = shn_bsm_search_lukup_result($_SESSION['bsm']['main']['rtnid']);
                    shn_bsm_search_result_vw($sql);
                }
                else
                {
										//include_once 'search_facility.inc';
//print 'test';
										//require_once 'search_location.inc';
                    $sql = _shn_bsm_search_lukup_result($_SESSION['bsm']['main']['rtnid']);
                    shn_bsm_search_result_vw($sql);
                }
            }
            else
            {
                //echo "DONE, Lookup id is there";
                /*if($conf['debug']){
                	print "<hr>rtnid =".$_GET['rtnid'].", lukup-id =".$_GET['lukupid'].", rtnfk=".$_GET['rtnfk'].", rtnfrm =".$_GET['rtnfrm']."<hr>";
                }	*/
            	require_once ($global['approot'].'mod/bsm/edit_'.$_SESSION['bsm']['main']['rtnfrm'].'.inc');
            	
                shn_bsm_edit_commit_lukup($_GET['rtnid'],$_GET['lukupid'],$_GET['rtnfk'], $_REQUEST['disease']);
                shn_bsm_edit_load($_SESSION['bsm']['main']['rtnid']);
                shn_bsm_edit_entry();
            }
            break;
        default :
            shn_bsm_search_default($_SESSION['bsm']['main']['action'].'&entity='.$_SESSION['bsm']['main']['entity'],'By default first search then the rest: add, edit, or delete (avoid duplication!)');
            break;
    }
}

function shn_bsm_edit() {

    global $global;
    global $conf;
//print 'hello';
    $_SESSION['bsm']['main']['entity']= trim($_GET['entity']);
    $_SESSION['bsm']['main']['action']= trim($_GET['act']);

if($_REQUEST['do'] == 'addcase') {
		include_once 'add_cases.inc';
	 if (shn_bsm_add_validate()){
//print 'test';
     	shn_bsm_add_confirm();
        shn_bsm_add_commit();
        //shn_bsm_default();               
	}
    else {
    	shn_bsm_add_entry(true);}
	} 
	if($_REQUEST['do'] == 'addcontact') {
		include_once 'search_contact.inc';
		_shn_bsm_add_fclty_contact(trim($_REQUEST['lukupid']), trim($_REQUEST['rtnid']));
		//break;
	}
	if($_REQUEST['do'] == 'addaddress') {
		include_once 'search_address.inc';
		_shn_bsm_add_fclty_address(trim($_REQUEST['lukupid']), trim($_REQUEST['rtnid']));
		//break;
	}
	if($_REQUEST['do'] == 'addservice') {
		include_once 'search_service.inc';
		_shn_bsm_add_fclty_service(trim($_REQUEST['lukupid']), trim($_REQUEST['rtnid']));
		//break;
	}

	if($_REQUEST['sympid'] != null || $_REQUEST['sympid'] != '')
	{
		include_once 'delete_data.inc';
		_shn_bsm_delete_symptom($_REQUEST['rtnid'], $_REQUEST['sympid'] );
	}

	if($_REQUEST['signid'] != null || $_REQUEST['signid'] != '')
	{
		include_once 'delete_data.inc';
		_shn_bsm_delete_sign($_REQUEST['rtnid'], $_REQUEST['signid'] );
	}
    
    echo '<h1 align="center">Edit the '.$_SESSION['bsm']['main']['entity'].'</h1>';
    require ($global['approot'].'mod/bsm/'.$_SESSION['bsm']['main']['action'].'_'.$_SESSION['bsm']['main']['entity'].'.inc');
    
    switch ($_REQUEST['seq'])
    {
			
        case 'entry' :
//print 'entry';
		        if (shn_bsm_edit_validate())
		        {
		            shn_bsm_edit_confirm();
		            shn_bsm_edit_commit();
		            /**deafault function commented below 3 functions have ben added*/
		            //shn_bsm_default();
		            add_confirmation(_t('Successfully edited'));
                	shn_bsm_edit_load($_GET['rtnid']); // loading the stored data (handling sessions)
                	shn_bsm_edit_entry(false);
		        }
		        else {shn_bsm_edit_entry(true);}
            break;
            
        case 'commit' :
//print 'commit';
	            shn_bsm_edit_confirm();
	            shn_bsm_edit_commit();
	            shn_bsm_default();
            break;

        default :
	            $_SESSION['bsm']['edit'] = null;
	            shn_bsm_edit_load($_GET['rtnid']); // loading the stored data (handling sessions)
	            shn_bsm_edit_entry(); // pupoulate the UI and capture updates from the user
            break;
    }
}

function shn_bsm_add() {

    global $global;
    global $conf;
    
    $_SESSION['bsm']['main']['entity']= trim($_GET['entity']);
    $_SESSION['bsm']['main']['action']= trim($_GET['act']);
    
    
    require ($global['approot'].'mod/bsm/'.trim($_GET['act']).'_'.trim($_GET['entity']).'.inc');
        
    switch ($_REQUEST['seq'])
    {    	
        case 'entry' :        	
            if (shn_bsm_add_validate()){				
                shn_bsm_add_confirm();
                shn_bsm_add_commit();
                //print($_POST['case_id']);
                if($_POST['case_id']!=null)
                {
                	include_once 'add_disease.inc';
                	
                }
                
                /* commented on mifan's request*/
                //echo '<h1 align="center">Edit this '.trim($_GET['entity']).'</h1>';
                //add_confirmation("Successfully saved");
                //include_once 'edit_disease.inc';
                //shn_bsm_edit_load($_GET['rtnid']); // loading the stored data (handling sessions)
                //shn_bsm_edit_entry(false);
	            switch($_GET['entity']){
			    	case 'disease':
			    		echo '<h1 align="center">Edit this '.trim($_GET['entity']).'</h1>';
			            add_confirmation("Successfully saved");
			            include_once 'edit_disease.inc';
			            shn_bsm_edit_load($_GET['rtnid']); // loading the stored data (handling sessions)
			            shn_bsm_edit_entry(false);
			            break;    		
			    }
            if($_POST['case_uuid']!='')
                {
                	;//shn_bsm_edit();
                }
			}
            else {
            	//echo '<h1 align="center">Add '.trim($_GET['entity']).'</h1>';            	
            	shn_bsm_add_entry(true);
            	print 'hello';
            	
            }
            break;        
        default :
            $_SESSION['bsm']['add'] = null;
            echo '<h1 align="center">Add '.trim($_GET['entity']).'</h1>';
            shn_bsm_add_entry();
            break;
    }
}

function _shn_bsm_search_lukup_result($location_uuid=null){
    global $global;
    global $conf;
//print 'hello';
//    $name = trim($_POST['name']);
//    $category = trim($_POST['category']);
//    $type = trim($_POST['type']);
//    $iso_code = trim($_POST['iso_code']);
    if ($location_uuid !=null){
    $sql = "SELECT loc_type_prnt FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_type = ";
    $sql .= "(SELECT loc_type FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = '".$location_uuid."')";
    $rsql = $global['db']->Execute($sql);
    if ($rsql->RecordCount() > 0){$location_p_type = $rsql->fields['loc_type_prnt'];}
    
    $sql = "SELECT l.loc_uuid FROM bsm_location l INNER JOIN bsm_loc_type lt ON lt.loc_type = l.loc_type ";
    $sql .= "INNER JOIN bsm_loc_cate lc ON lc.loc_cate = lt.loc_cate WHERE l.deactivate_dt IS NULL ";
    //$sql .= "AND l.loc_cate = (SELECT loc_cate FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = '".$location_uuid."') ";
    $sql .= "AND l.loc_type = '".$location_p_type."' ";
    $sql .= 'GROUP BY 1';
    }
    else {$sql = shn_bsm_search_result();}
    return $sql;
}

function shn_bsm_add_contact()
{
	include_once 'add_contact.inc';
	_shn_add_contact();
}

function shn_bsm_add_address()
{
	include_once 'add_address.inc';
	_shn_add_address();
}

function shn_bsm_edit_contact()
{
	include_once 'edit_contact.inc';
	_shn_edit_contact();
}

function shn_bsm_edit_address()
{
	include_once 'edit_address.inc';
	_shn_edit_address();
}

function shn_bsm_add_serviceitem()
{
	include_once 'add_serviceitem.inc';
	_shn_add_service_item();
}

function shn_bsm_edit_serviceitem()
{
	include_once 'edit_serviceitem.inc';
	_shn_edit_service_item();
}

function shn_bsm_add_symptom()
{
	include_once 'add_symptom.inc';	
	_shn_add_symptom();
}

function shn_bsm_edit_symptom()
{
	include_once 'edit_symptom.inc';
	_shn_edit_symptom();
}

function shn_bsm_add_sign()
{
	include_once 'add_sign.inc';
	_shn_add_sign();
}

function shn_bsm_add_caus_factor()
{
	include_once 'add_caus_factor.inc';
	_shn_add_caus_factor();
}

function shn_bsm_edit_sign()
{
	include_once 'edit_sign.inc';
	_shn_edit_sign();
}
?>