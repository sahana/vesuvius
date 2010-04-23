<?php
/**
 * Main Controller of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Chamindra de Silva <chamindra@opensource.lk>
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . "/inc/lib_modules.inc";
include_once $global['approot'] . "/inc/lib_menu.inc";
include_once $global['approot'] . "/inc/lib_form.inc";
include_once $global['approot'] . "/inc/lib_validate.inc";
include_once $global['approot'] . "/inc/lib_errors.inc";
include_once $global['approot'] . 'mod/mpr/tools.inc';
include_once $global['approot'] . '/inc/lib_image.inc';
include_once $global['approot'] . 'mod/mpr/report.inc';
include_once $global['approot'] . '/conf/pfifconf_tmp.inc.php';

/* {{{ Hack Need to fix */
if (empty ($_SESSION['user_pref_ims_incident_id'])) {
	$sql = "SELECT incident_id FROM incident ORDER BY incident_id";
	$rs = $global['db']->GetAll($sql);
	if ($rs) {
		$_SESSION['user_pref_ims_incident_id'] = $rs[0][0];
	} else {
		add_warning('There are no incidents added. Please use the admin console to add atleast one incident.');
		add_warning('You cannot use Missing Person Registry without adding an incident.');
	}
}
if($_SESSION['user_pref_ims_incident_id']==null && $_REQUEST['act']!='default') {
     header('Location: index.php?mod=mpr&act=default');   
}



/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_mpr_mainmenu() {
	#debug($_SESSION,1);
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";

	// Create the module menu
	shn_mod_menuopen(_t("Missing Person Registry"));
		shn_mod_menuitem("default", _t("MPR Home"));
		shn_mod_menuitem("search&type=all", _t("Search for a Person"));
		shn_mod_menuitem("addmp&type=missing", _t("Report a Missing Person"));
		shn_mod_menuitem("search&type=missing", _t("Edit a Missing Person"));
		shn_mod_menuitem("addmp&type=found", _t("Report a Found Person"));
		shn_mod_menuitem("list_missing", _t("List Missing People"), $module);
		shn_mod_menuitem("list_found", _t("List Found People"), $module);

		// Add PFIF Menu: chc 1/22/2010
		if ($user = $_SESSION["user"]!='Anonymous'){
			shn_sub_mod_menuopen(_t("PFIF"));
				shn_mod_menuitem("import", _t("Import"), $module);
				shn_mod_menuitem("export", _t("Export"), $module);
			shn_sub_mod_menuclose();
		}
		
	shn_mod_menuclose();
	//shn_mod_menuitem("manimg",_t("Manage Images"));
	//shn_mod_menuitem("test","Test");
	//shn_mod_menuitem("stats","Statistics");
	//shn_mod_menuclose();

	// include the main menu
	//include $global['approot'] . "/inc/handler_mainmenu.inc";
}



/**
 *
 * This is a testing function.
 *
 * @todo remove shn_mpr_test
 * @access public
 * @return void
 */
function shn_mpr_test() {
	global $global;
	require ($global['approot'] . 'mod/mpr/test.inc');
}



function shn_mpr_list_missing() {
	//print 'missing';
	global $global;
	require ($global['approot'] . 'mod/mpr/list_missing.inc');
}



function shn_mpr_list_found() {
	global $global;
	require ($global['approot'] . 'mod/mpr/list_found.inc');
}



/**
 *
 * This is a testing function.
 *
 * @todo remove shn_mpr_test
 * @access public
 * @return void
 */
function shn_mpr_manimg() {
	global $global;
	require ($global['approot'] . 'mod/mpr/images.inc');
	shn_mpr_manage_images_form('p-77', 'xx');
}



/**
 * 
 * This function displays the home page of the missing person registry
 *
 * @access public
 * @return void
 */
function shn_mpr_default() {
	global $global;
	require ($global['approot'] . 'mod/mpr/home.inc');

}



/**
 * This function displays the basic search form
 * @deprecated 
 * @todo shn_mpr_fndmp to be removed 
 * @access public
 * @return void
 */
function shn_mpr_fndmp() {
	global $global;
	$header = array ('method' => 'POST', 'action' => 'index.php?mod=mpr&act=addmp', 'id' => 'formset');
	shn_form_open($header, false);
	?>  <input type="text" value="hello"/>          <?php
	shn_form_close();
}



/**
 * This is the MPR Edit Controller
 * @access public
 * @return void
 */
function shn_mpr_editmp() {
	global $global;
	require ($global['approot'] . 'mod/mpr/edit.inc');
	require_once ($global['approot'] . 'mod/mpr/add.inc');
	//validation
	switch ($_REQUEST['seq']) {
		case 'entry' :
			echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			if (shn_mpr_editmp_validate()) {
				shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
			} else {
				shn_mpr_editmp_entry(true);
			}
		break;

		case 'trackers' :
			echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			shn_mpr_editmp_confirm();
			break;

		case 'commit' :
			if(isset($_POST['yes'])) {
				shn_mpr_editmp_commit();
				//Send Back to the Main Page
				shn_mpr_default();
			} else {
				shn_mpr_editmp_entry();  
			}
		break;

		case 'add_tracker' :
			echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			$_POST = null;
			$_SESSION['mpr_add']['add_tracker'] = null;
			echo '<h1 align="center">' . _t('Add a tracker to') . ' ' .
			$_SESSION['mpr_edit']['entry']['full_name'] . ' </h1>';
			$_SESSION['mpr_add']['add_tracker']['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
			// todo: check the p_uuid exists or not *** VERY URGENT
			shn_mpr_addmp_reporter();
		break;

		case 'report_person' :
			echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			if (shn_mpr_addmp_reporter_validate() || isset ($_GET['offset'])) {
				if ($_POST['reported_before'] == 'yes' || isset ($_GET['offset'])) {
					require_once ($global['approot'] . 'mod/mpr/search.inc');
					if (isset ($_GET['offset'])) {
						$arr = shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'], $_GET['offset'], true);
						shn_mpr_search_select($arr);
					} else {
						$search_sql = new SearchQuery();
						$search_sql->set_name($_POST['rep_full_name']);
						$search_sql->set_address($_POST['rep_address']);
						$search_sql->set_phone($_POST['rep_phone']);
						$arr = shn_mpr_search_result_vw($search_sql->get_sql(), -1, true);
						shn_mpr_search_select($arr);
					}
				} else {
					shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
					shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
					$_SESSION['mpr_add']['add_tracker'] = null;
				}
			} else {
				echo '<h1 align="center">' . _t('Add a tracker to') . ' ' . $_SESSION['mpr_add']['add_tracker']['name'] . ' </h1>';
				shn_mpr_addmp_reporter(true);
			}
		break;
		
		case 'tracker_select' :
			shn_add_person_to_report($_SESSION['mpr_edit']['entry']['p_uuid'], $_GET['tracker_id'], $_SESSION['mpr_add']['report_person']['rep_relation']);
			$_SESSION['mpr_add']['add_tracker'] = null;
			shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
		break;
		
		case 'del_tracker' :
			echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			//todo : Clean the input
			$tracker_uuid = $_POST['tracker_id'];
			if(isset($_POST['yes'])){
			    shn_edit_del_tracker($_SESSION['mpr_edit']['entry']['p_uuid'], $tracker_uuid);
			}
			shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
		break;

		case 'con_del_tracker':	
			echo '<h1 align="center">' . _('Edit Missing Person Entry') . '</h1>';	    
			shn_form_fopen("editmp",null,array('req_message'=>false,'id'=>'del'));
			shn_form_fsopen('Confirm');
			shn_form_hidden(array('seq'=>'del_tracker','tracker_id'=>$_GET['tracker_id']));
			echo sprintf(_('Are you sure you want to delete tracker %s from tracker list'),$_GET['tracker_name']);
			echo '<br/>';
			echo '<br/>';
			shn_form_submit("Yes",'name="yes"');
			shn_form_submit("No",'name="no"');
			shn_form_fsclose();
			shn_form_fclose();
			shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
		break;
		
		default :
			$_SESSION['mpr_edit']['entry'] = null;
			shn_mpr_editmp_load($_GET['id']);//load details
			if($_SESSION['mpr_edit']['entry']['opt_status']=='mis'){
			    echo '<h1 align="center">' . _t('Edit Missing Person Entry') . '</h1>';
			}else{
			    echo '<h1 align="center">' . _t('Edit Found Person Entry') . '</h1>';
			}
			shn_mpr_editmp_entry();
		break;
	}
}



/**
 * This is the MPR View Controller
 * @access public
 * @return void
 */
function shn_mpr_viewmp() {
	global $global;
	require ($global['approot'] . 'mod/mpr/view.inc');
	echo '<h1 align="center">' . _t('View Person') . '</h1>';
	shn_mpr_view($_GET['id']);
}



/**
 * This is the MPR Add Tracker Controller
 * @access public
 * @return void
 */
function shn_mpr_add_tracker() {
	global $global;
	require ($global['approot'] . 'mod/mpr/add.inc');
	//Controller
	switch ($_REQUEST['seq']) {
		case 'report_person' :
			if (shn_mpr_addmp_reporter_validate()) {
				if ($_POST['reported_before'] == 'yes') {
					require_once ($global['approot'] . 'mod/mpr/search.inc');
					$search_sql = new SearchQuery();
					$search_sql->set_name($_POST['rep_full_name']);
					$search_sql->set_address($_POST['rep_address']);
					$search_sql->set_phone($_POST['rep_phone']);
					$arr = shn_mpr_search_result_vw($search_sql->get_sql(), -1, -1, true);
					shn_mpr_search_select($arr);
				} else {
					shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
					// todo: redirect back to search results (that'll be great)
					shn_mpr_default();
					$_SESSION['mpr_add']['add_tracker'] = null;
				}
			} else {
				echo '<h1 align="center">' . _t('Add a tracker to') . ' ' . $_SESSION['mpr_add']['add_tracker']['name'] . ' </h1>';
				shn_mpr_addmp_reporter(true);
			}
		break;

		case 'tracker_select' :
			shn_add_person_to_report($_SESSION['mpr_add']['add_tracker']['p_uuid'], $_GET['tracker_id'], $_SESSION['mpr_add']['report_person']['rep_relation']);
			shn_mpr_default();
			$_SESSION['mpr_add']['add_tracker'] = null;
		break;

		default :
			//clean the $_POST to remove the conflicts
			$_POST = null;
			$_SESSION['mpr_add']['add_tracker'] = null;
			echo '<h1 align="center">' . _t('Add a tracker to') . ' ' . $_GET['name'] . ' </h1>';
			$_SESSION['mpr_add']['add_tracker']['p_uuid'] = $_GET['id'];
			$_SESSION['mpr_add']['add_tracker']['name'] = $_GET['name'];
			// todo: check the p_uuid exists or not *** VERY URGENT
			shn_mpr_addmp_reporter();
		break;
	}
}



/**
 * This is the MPR Delete Tracker Controller
 * @access public
 * @return void
 */
function shn_mpr_del_tracker() {
	global $global;
	if (shn_mpr_addmp_reporter_validate()) {
		shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
		// todo: rediddrect back to search results (that'll be great)
		#shn_mpr_default();                
		$_SESSION['mpr_add']['add_tracker'] = null;
	} else {
		echo '<h1 align="center">' . _t('Add a tracker to') . ' ' . $_SESSION['mpr_add']['add_tracker']['name'] . ' </h1>';
		shn_mpr_addmp_reporter(true);
	}
}



/**
 * This is the MPR Add Controller
 * @access public
 * @return void
 */
function shn_mpr_addmp() {
	global $global;
	require ($global['approot'] . 'mod/mpr/add.inc');

	if ($_GET['type'] == 'found') {
		$_SESSION['mpr_add']['entry_type'] = 'found';
	} else if ($_GET['type'] == 'missing') {
		$_SESSION['mpr_add']['entry_type'] = 'missing';
	}

	//Controller
	switch ($_REQUEST['seq']) {
		case 'entry' :
			if (shn_mpr_addmp_validate()) {
				//clean the $_POST to remove the conflicts
				$_POST = null;
				echo $heading;
				echo '<h1 align="center">' . _t('Person Registry : Reporting a '.ucwords($_SESSION['mpr_add']['entry_type']).' Person'). '</h1>';
				shn_mpr_addmp_reporter();
			} else {
				echo $heading;
				echo '<h1 align="center">' . _t('Person Registry : Person Details') . '</h1>';
				shn_mpr_addmp_entry(true);
			}
		break;

		case 'tracker_back' :
			echo $heading;
			echo '<h1 align="center">' . _t('Person Registry : Reporting a '.ucwords($_SESSION['mpr_add']['entry_type']).' Person') . '</h2>';
			shn_mpr_addmp_reporter();
		break;

		case 'tracker_select' :
			$_SESSION['mpr_add']['entry']['tracker_id'] = $_GET['tracker_id'];
			shn_mpr_addmp_commit();
			echo $heading;
			echo '<h2 align="center">' . _t('The missing person have been added') . '</h2>';
			shn_mpr_addmp_confirm();
			//shn_mpr_addmp_commit();
		break;

		case 'report_person' :
			if (shn_mpr_addmp_reporter_validate() || isset ($_GET['offset'])) {
				//if reported before then send to the search 
				if ($_POST['reported_before'] == 'yes' || isset ($_GET['offset'])) {
					echo $heading;
					echo '<h2 align="center">(' . _t('Please Select the person who is reporting') . ')</h2>';
					require_once ($global['approot'] . 'mod/mpr/search.inc');
					if (isset ($_GET['offset'])) {
						$arr = shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'], $_GET['offset'], true);
						shn_mpr_search_select($arr);
					} else {
						$search_sql = new SearchQuery();
						$search_sql->set_name($_POST['rep_full_name']);
						$search_sql->set_address($_POST['rep_address']);
						$search_sql->set_phone($_POST['rep_phone']);
						$arr = shn_mpr_search_result_vw($search_sql->get_sql(), -1, true);
						shn_mpr_search_select($arr);
					}
				} else {
					shn_mpr_addmp_commit();
					echo $heading;
					echo '<h2 align="center">(' . _t('The missing person have been added') . ')</h2>';
					shn_mpr_addmp_confirm();
				}
			} else {
				echo $heading;
				echo '<h1 align="center">' . _t('Person Registry : Reporting a '.ucwords($_SESSION['mpr_add']['entry_type']).' Person') . '</h1>';
				shn_mpr_addmp_reporter(true);
			}
		break;

		case 'commit' :
			shn_mpr_addmp_commit();
			break;

		default :
			echo $heading;
			echo '<h1 align="center">' . _t('Person Registry : Reporting a '.ucwords($_SESSION['mpr_add']['entry_type']).' Person') . '</h1>';
			shn_mpr_addmp_entry();
			$_SESSION['mpr_add'] = null;
		break;
	}
}




/**
 * This is the Search Controller
 * @access public
 * @return void
 */
function shn_mpr_search() {
	global $global;
	echo '<h1 align="center">Search</h1>';
	require ($global['approot'] . 'mod/mpr/search.inc');
	
	
	$search=false;
	if($_REQUEST['type']=='all')
	{
		$search=true;
	}	
	
	//Controller for Normal Search
	if ($_GET['act'] == 'search') {
		switch ($_REQUEST['seq']) {
			case 'result' :
				shn_mpr_search_default();//echo $_SESSION['mpr']['search']['subquery'];
				if (isset($_SESSION['mpr']['search']['subquery'])){
					shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'],null,null,$search);
				} else {
					$search_sql = new SearchQuery();
					if (!empty ($_POST['name']))
						$search_sql->set_name($_POST['name']);
					if (!empty ($_POST['idcard']))
						$search_sql->set_serial_no($_POST['idcard']);
					if (empty ($_POST['idcard']) && empty ($_POST['name'])) {
						$search_sql->set_name($_POST['name']);
						$search_sql->set_serial_no($_POST['idcard']);
					}
					#$search_sql->isvictim = true; 
					if (!isset ($_REQUEST['all_incidents']))
						$search_sql->incident_list = "'" . implode(shn_db_get_all_incidents($_SESSION['user_pref_ims_incident_id']), "','") . "'";
					if ($_REQUEST['type'] == 'missing') {
						$search_sql->missing_only = true;
						$search_sql->isvictim = true;
					}
					#debug($search_sql->get_sql());
					$arr = shn_mpr_search_result_vw($search_sql->get_sql(),null,null,$search);
				}
			break;

			default :
				unset($_SESSION['mpr']['search']['subquery']);
				shn_mpr_search_default();
			break;
		}
		//Controller for Advance Search
	} else if ($_GET['act'] == 'search_adv') {
		switch ($_POST['seq']) {
			case 'result' :
				shn_mpr_search_result();
			break;
		
			default :
				shn_mpr_search_advance();
			break;
		}
	}
}



/**
 * This is the Advance Search Controller
 * @todo Add Advance Filters
 * @access public
 * @return void
 */
function shn_mpr_search_adv() {
	global $global;
	echo '<h1 align="center">Search</h1>';
	require ($global['approot'] . 'mod/mpr/search.inc');
}



/**
 * This is the Auditing Controller
 * @todo Need to discuss this further
 * @access public
 * @return void
 */
function shn_mpr_auditmp() {
	global $global;
	require ($global['approot'] . 'mod/mpr/audit.inc');
	shn_audit_show($_GET['id']);
}



/**
 * This is function change the status from missing to alive and well
 * @access public
 * @return void
 */
function shn_mpr_status() {
	global $global;

	//clean and check
	$update_array['p_uuid'] = shn_db_clean($_GET['id']);
	if (!$global['db']->Execute("SELECT p_uuid FROM person_status WHERE p_uuid = {$update_array['p_uuid']}")) {
		shn_mpr_default();
	} else {
		//flush and refill baby
		$global['db']->Execute("DELETE FROM person_status WHERE p_uuid = {$update_array['p_uuid']}");
		$update_array['p_uuid'] = $_GET['id'];
		//Insert Into person_status mis
		$update_array['opt_status'] = 'ali';
		shn_db_insert($update_array, 'person_status');
		//reset $update_array 
		$update_array = null;
		shn_mpr_default();
	}
}

function shn_mpr_import(){
    // if there is no post, render the form to upload
    // var_dump('$_POST' , $_POST);
    //var_dump('$_FILES' , $_FILES);
    if( ! isset( $_POST['upload'])){
        shn_form_fopen("import",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
        add_warning(_t('Please make sure that you are adding a PFIF xml file.'));
        shn_form_fsopen(_t('Import from PFIF xml'));
        shn_form_hidden(array('upload'=>'upload'));
        // Added 1/23/10 (c.cornwell)  Google daily PFIF snapshot requires increasing max allowed upload size
        // @todo get max size from configuration file
        // @see http://www.php.net/manual/en/features.file-upload.php#74692 regarding alternate solution for large file upload
        shn_form_upload(_t('Upload PFIF xml'),'xml',array('max_file_size'=>'128M'));
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fsopen(_t('Download from Google PFIF API'));
        shn_form_text(_t('Enter person_record_id'),'pfif_id');
        shn_form_submit(_t('Download'));
        shn_form_fsclose();
        shn_form_fclose();
    }else{
        //validate
        if (isset($_POST['pfif_id']) && !empty($_POST['pfif_id'])) {
            // TODO: Need to restructure this to maximize reuse
            include_once 'pfif.inc';
             $pfif = new Pfif();
             $loaded = $pfif->loadFromService($_POST['pfif_id']);
             // error_log( $pfif->storeInXML() );
             $result = $loaded ? $pfif->storeInDatabase() : false;
             if($result == true){
                 add_confirmation('Successfully Imported');
             } else {
                 add_error('There was an error in Importing');
             }
             shn_mpr_default();                     
        }
        else if(  $_FILES['xml']['error'] != 0){
            add_warning('Please select a file to upload');
            unset($_FILES); unset($_POST);
            shn_mpr_import();
        }else{
             //if there is a post, upload the file and import the file to the database.
             if(is_uploaded_file($_FILES['xml']['tmp_name'])){
                 include_once 'pfif.inc';
                 $pfif = new Pfif();
                 $loaded = $pfif->loadFromXML($_FILES['xml']['tmp_name']);
                 // $loaded = $pfif->readFromXML($_FILES['xml']['tmp_name']);
                 //$pfif->storeInXML();
                 $result = $loaded ? $pfif->storeInDatabase() : false;
                 if($result == true){
                     add_confirmation('Successfully Imported');
                 } else {
                     add_error('There was an error in Importing');
                 }
                 shn_mpr_default();                     
             
             }
        }
        
    }
   
}

function shn_mpr_export(){

    if( ! isset( $_POST['upload'])){
        echo '<h1 align="center">Get Export XML</h1>';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=missing' >Get Missing </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=alive' > Get Alive </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=injured' > Get Injured </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=deceased' > Get Deceased </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=unknown' > Get Unknown </a>";

        echo '<br />';
        echo '<h1 align="center">Export To Google PFIF API</h1>';
        shn_form_fopen("export",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
        add_warning(_t('EXPERIMENTAL: Add source, time range selection parameters to replace id in Upload Selected ... section'));
        shn_form_fsopen(_t('Upload PFIF XML file'));
        shn_form_hidden(array('upload'=>'upload'));
        shn_form_upload(_t('Source File'),'xml');
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fsopen(_t('Upload Selected Records'));
        shn_form_text(_t('Enter person_record_id'),'pfif_id');
        shn_form_submit(_t('Submit'));
        shn_form_fsclose();
        shn_form_fclose();
    }else{
        //validate
        if (isset($_POST['pfif_id']) && !empty($_POST['pfif_id'])) {
            // TODO: Need to restructure this to maximize reuse with upload case.
            // TODO: Need to have post parse the return status and return true status for reporting.
            include_once 'pfif.inc';
             $pfif = new Pfif();
             $result = $pfif->postDbToService($_POST['pfif_id']);
             if(!($result == false)){
                 add_confirmation('Successfully Exported<br/>'.$result);
             } else {
                 add_error('There was an error in Exporting');
             }
             shn_mpr_default();                     
        }
        else if(  $_FILES['xml']['error'] != 0){
            add_warning('Please select a file to upload');
            unset($_FILES); unset($_POST);
            shn_mpr_export();
        }else{
             if(is_uploaded_file($_FILES['xml']['tmp_name'])){
                 include_once 'pfif.inc';
                 $pfif = new Pfif();
                 $result = $pfif->postFileToService($_FILES['xml']['tmp_name']);
                 if(!($result == false)){
                     add_confirmation('Successfully Exported<br/>'.$result);
                 } else {
                     add_error('There was an error in Exporting');
                 }
                 shn_mpr_default();                     
             }
        }
        
    }

       
}


/**
 * shn_soap_mpr_addmp 
 * 
 * @access public
 * @return string
 */
function shn_soap_mpr_addmp() {
}



/**
 * shn_soap_mpr_findmp 
 * 
 * @param mixed $strAnyName 
 * @param mixed $strAnyID 
 * @param mixed $strIncident 
 * @access public
 * @return string
 */
function shn_soap_mpr_findmp() {
}



/**
 * shn_soap_mpr_default 
 * 
 * @access public
 * @return string
 */
function shn_soap_mpr_default() {
	return "hello";
}



/**
 * pull images 
 * update: 2009:0707 ~ Added the capability to reference this function call by other outside sources
 * which require MPR image data in specific resolutions (if height and width are not specified in the GET, 
 * the old behavior is maintained in the patch to /inc/lib_image.inc - Greg
 */
function shn_image_mpr_addmp_img() {
	global $global;
	$x_uuid = $_GET['x_uuid'];
	$height = isset($_GET['height']) ? $_GET['height'] : null;
	$width  = isset($_GET['width']) ? $_GET['width'] : null;
	switch ($_GET['stream']){
		case 'image' :
			if($_GET['session']){
				shn_show_image_stream($x_uuid, true, $_SESSION['mpr']['entry'], true, null, $width, $height);
			} else {
				if($_GET['thumbnail']) {
					shn_show_image_stream($x_uuid, true, null, false, null, $width, $height); 
				} else {
					shn_show_image_stream($x_uuid, false, null, false, null, $width, $height);
				}
			}
		break;
	}
}



/**
 * End the add or edit mpr record flow by clearing the session
 * and redirecting to the default view.
 *
 */
function shn_mpr_end_flow() {
	unset($_SESSION['mpr_add']);
	unset($_SESSION['mpr']['entry']);
	shn_mpr_default();
}

function shn_xml_mpr_pfif_export(){
	//status could be 'missing' , 'injured' , 'deceased' , 'alive','unknown' (TODO: add 'found = fou')
	$status = $_GET['status'];		
	
	include_once 'pfif.inc';
    // include_once $global['approot'] . '/inc/lib_stream_xml.inc';

	$pfif = new Pfif();
	//$pfif->storeInXML();
	$pfif->loadFromDatabase($status); // TODO: add 'since' arg
    // shn_stream_init(false);
	// $pfif->storeInXML();
    print $pfif->storeInXML();
	
}

function shn_xml_mpr_pfif_import(){
	//status could be 'missing' , 'injured' , 'deceased' , 'alive'
	global $global;
	include_once 'pfif.inc';
	$pfif = new Pfif();
	$loaded = $pfif->loadFromXML($global['approot'] . '/mod/mpr/test.xml'); // TODO: how is an arbitrary file imported using this action?
	if ($loaded) {
        $pfif->storeInDatabase();
        // error_log( $pfif->storeInXML() );
    } else {
        error_log( "shn_mod_mpr_pfif_import: Import failed" );
    }
	
}



/**
 * This is "Report a Person" Selection Page
 * @access public
 * @return void
 */
function shn_mpr_report_select() {
?>
	<div id="home">
		<h2>Person Registry : Reporting a Person</h2><br>
		<br> 
		<b>Please choose the status of the person you are reporting: </b><br>
		<br> 
		<br> 
		<table style="width: 100%;"> 
			<tbody><tr><td> 
				<div id="reportMissing" style="float: left;" onclick="location.href='index.php?mod=mpr&amp;act=addmp&amp;type=missing';"> 
					<img src="theme/default/img/icon-girl-missing.png" alt="Report a Missing Person" style="margin: 0px 20px 0px 0px;" align="middle">Missing
				</div> 
				<div id="reportFound" style="float: right;" onclick="location.href='index.php?mod=mpr&amp;act=addmp&amp;type=found';"> 
					<img src="theme/default/img/icon-girl-found.png" alt="Report a Found Person" style="margin: 0px 20px 0px 0px;" align="middle">Found
				</div> 
			</td></tr> 
			</tbody>
		</table> 
		<br>
	</div>
<?php
}