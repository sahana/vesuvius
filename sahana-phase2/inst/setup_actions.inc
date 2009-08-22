<?php

/**Action functions of the Sahana Advanced Web Setup
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue. <ravithb@yahoo.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage setup
 */

include_once('setup_actions_sub.inc');
global $execution_order_on_complete;
$execution_order_on_complete = array('shn_setup_simple_dbsetup_complete','shn_setup_empty_dbsetup_complete','shn_setup_existing_dbsetup_complete','shn_setup_simple_config_complete','shn_setup_adv_select_modules_complete','shn_setup_adv_advanced_config_complete','shn_setup_adv_pwd_policy_complete');
/*
 * ===================================================================
 * 				Actual System Setup Function
 * ===================================================================
 */
function shn_setup_do_setup()
{
	global $global,$conf,$_state_funct_map,$execution_order_on_complete;

	// create config
	$config_key_vals = array();

	foreach ($_SESSION as $conf_name=>$conf_value){
		// get appropriate setup variables.
		if(stripos($conf_name,"shn_setup_data_")>-1){
			$tmparr = explode("shn_setup_data_",$conf_name);
			$var_real_name = $tmparr[1];
			// process strings first.
			if(is_string($conf_value)){
				$config_key_vals[$var_real_name] = $conf_value;
			} else if(is_array($conf_value)){
				// handle arrays.
			}
		}
	}

	$debug_setup = false;
	// the following code will execute the complete functions for each function called
	// during the setup.
	$_SESSION['shn_setup_function_list'] = array_unique($_SESSION['shn_setup_function_list']);

	//echo "<pre>";var_dump($_SESSION['shn_setup_function_list']);echo "</pre>";
	foreach ($execution_order_on_complete as $pilot_funct){
		//var_dump(array_search($pilot_funct,$_SESSION['shn_setup_function_list']));
		if(array_search($pilot_funct,$_SESSION['shn_setup_function_list'])){
			if(function_exists($pilot_funct)){
				if($debug_setup===true){
					echo "Calling $pilot_funct <br/>";
					echo "Error Count : ".count($global['submit_errors'])."</br>";
				}
				// call it.
				if($pilot_funct(array('config_key_vals'=>$config_key_vals))===false){
					// break on error
					if($debug_setup===true){
						echo " Error occured.<br/>";
					}
					return false;
				} else {
					if($debug_setup===true){
						echo " - Success<br/>";
					}
				}
			}
		}
	}
	return true;
}
/*
 * ===================================================================
 * 				Action Functions
 * ===================================================================
 */

function shn_setup_general_dependencies_submit()
{
	if(shn_setup_validate_general_dependencies()){
		_shn_setup_determine_step_no('shn_setup_general_dependencies_submit',false);

		shn_setup_license(_shn_setup_get_step_no());
	} else {
		shn_setup_general_dependencies();
	}
}

function shn_setup_license_submit()
{
	if(!isset($_POST['back_button'])){
		_shn_setup_determine_step_no('shn_setup_license_submit',false);

		shn_setup_select_setup();
	} else {
		_shn_setup_determine_step_no('shn_setup_license_submit',true);

		shn_setup_general_dependencies();
	}
}

function shn_setup_select_setup_submit()
{
	global $global;
	if(!isset($_POST['back_button'])){

		_shn_setup_determine_step_no('shn_setup_select_setup_submit',false);
		// move to appropriate setup.
		if(isset($_POST['setup_type_simple'])){
			// set the setup type in the session.
			$_SESSION['setup_type'] = 'SIMPLE';
			// add all modules as selected modules.
			include_once($global['approot']."inc/lib_modules.inc");
			$_SESSION['shn_setup_data_selected_modules'] = shn_get_all_modules(false);

			shn_setup_select_dbsetup();

		} else if(isset($_POST['setup_type_adv'])){
			// set the setup type in the session.
			$_SESSION['setup_type'] = 'ADV';

			shn_setup_select_dbsetup();

		} else if(isset($_POST['setup_type_scen'])){
			// set the setup type in the session.
			$_SESSION['setup_type'] = 'SCEN';

		} else {
			// set the setup type in the session.
			$_SESSION['setup_type'] = $_POST['setup_type'];
			shn_setup_select_setup();
		}

	} else {
		_shn_setup_determine_step_no('shn_setup_select_setup_submit',true);

		shn_setup_license();
	}
}

function shn_setup_select_dbsetup_submit()
{
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_select_dbsetup");
	if(!isset($_POST['back_button'])){

		_shn_setup_transfer_to_session();

		if(shn_setup_validate_select_dbsetup()){
			_shn_setup_determine_step_no('shn_setup_simple_dbsetup_submit',false);
			if($_POST['dbsetup_method']=='use_new_db'){
				$_SESSION['dbsetup_method'] = "USE_NEW_DB";
				if($_SESSION['setup_type']=='SIMPLE'){
					shn_setup_simple_dbsetup();
				} else if($_SESSION['setup_type']=='ADV'){
					shn_setup_adv_select_modules();
				} else if($_SESSION['setup_type']=='SCEN'){
				}
			} else if($_POST['dbsetup_method']=='use_empty_db'){
				$_SESSION['dbsetup_method'] = "USE_EMPTY_DB";
				if($_SESSION['setup_type']=='SIMPLE'){
					shn_setup_empty_dbsetup();
				} else if($_SESSION['setup_type']=='ADV'){
					shn_setup_adv_select_modules();
				} else if($_SESSION['setup_type']=='SCEN'){

				}
			} else if($_POST['dbsetup_method']=='use_existing_db'){
				$_SESSION['dbsetup_method'] = "USE_EXISTING_DB";

				shn_setup_existing_dbsetup();

			}
		} else {
			_shn_setup_determine_step_no('shn_setup_simple_dbsetup_submit',true);
			shn_setup_select_dbsetup();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_simple_dbsetup_submit',true);
		shn_setup_select_setup();
	}
}

/*================= Simple Database Setup Step ====================*/
function shn_setup_simple_dbsetup_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_simple_dbsetup_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_determine_step_no('shn_setup_simple_dbsetup_submit',false);

		_shn_setup_transfer_to_session();
		if(shn_setup_validate_simple_dbsetup()){
			//separate the db host and port.
			$host_port = "";
			if(isset($_SESSION[SETUP_DATA_PREFIX."db_host"])){
				$host_port = _shn_setup_get_post_param($_SESSION,"db_host");
			} else {
				$host_port = $_POST['db_host'];
			}
			if(isset($host_port) && strpos($host_port,":")!==false){
				$_vals = explode(":",$host_port);
				_shn_setup_put_value_in_session("db_host",$_vals[0]);
				_shn_setup_put_value_in_session("db_port",$_vals[1]);
			}

			shn_setup_simple_config();
		} else {
			shn_setup_simple_dbsetup();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_simple_dbsetup_submit',true);

		$setup_type = _shn_setup_get_setup_type();

		if($setup_type == 'SIMPLE'){
			shn_setup_select_dbsetup();
		} else if($setup_type ==  'ADV'){
			shn_setup_adv_pwd_policy();
		} else {
			// nothing.
		}
	}
}

function shn_setup_simple_dbsetup_complete($extra_opts=null)
{
	return _shn_setup_setupdb($extra_opts['config_key_vals'],array('create_user','create_db','setup_db'));
}

function shn_setup_empty_dbsetup_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_empty_dbsetup_complete");

	$setup_type = _shn_setup_get_setup_type();
	if(!isset($_POST['back_button'])){

		_shn_setup_transfer_to_session();
		// validation
		if(shn_setup_validate_empty_dbsetup()){
			_shn_setup_determine_step_no('shn_setup_empty_dbsetup_submit',false);
			//separate the db host and port.
			$host_port = "";
			if(isset($_SESSION[SETUP_DATA_PREFIX."db_host"])){
				$host_port = _shn_setup_get_post_param($_SESSION,"db_host");
			} else {
				$host_port = $_POST['db_host'];
			}
			if(isset($host_port) && strpos($host_port,":")!==false){
				$_vals = explode(":",$host_port);
				_shn_setup_put_value_in_session("db_host",$_vals[0]);
				_shn_setup_put_value_in_session("db_port",$_vals[1]);
			}
			shn_setup_simple_config();
		} else {
			_shn_setup_determine_step_no('shn_setup_empty_dbsetup_submit',true);
			shn_setup_empty_dbsetup();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_empty_dbsetup_submit',true);

		if($setup_type == 'SIMPLE'){
			shn_setup_select_dbsetup();
		} else if($setup_type ==  'ADV'){
			shn_setup_adv_pwd_policy();
		} else {
			// nothing.
			shn_setup_select_dbsetup();
		}
	}
}

function shn_setup_empty_dbsetup_complete($extra_opts=null)
{
	return _shn_setup_db_setup_db_mysql($extra_opts['config_key_vals'],array('setup_db'));
}

function shn_setup_existing_dbsetup_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_existing_dbsetup_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_determine_step_no('shn_setup_existing_dbsetup_submit',false);
		_shn_setup_transfer_to_session();
		// validation
		if(shn_setup_validate_existing_dbsetup()){
			_shn_setup_determine_step_no('shn_setup_existing_dbsetup_submit',false);
			//separate the db host and port.
			$host_port = "";
			if(isset($_SESSION[SETUP_DATA_PREFIX."db_host"])){
				$host_port = _shn_setup_get_post_param($_SESSION,"db_host");
			} else {
				$host_port = $_POST['db_host'];
			}
			if(isset($host_port) && strpos($host_port,":")!==false){
				$_vals = explode(":",$host_port);
				_shn_setup_put_value_in_session("db_host",$_vals[0]);
				_shn_setup_put_value_in_session("db_port",$_vals[1]);
			}
			shn_setup_complete();
		} else {
			_shn_setup_determine_step_no('shn_setup_existing_dbsetup_submit',true);
			shn_setup_existing_dbsetup();
		}

	} else {
		_shn_setup_determine_step_no('shn_setup_existing_dbsetup_submit',true);
		shn_setup_select_dbsetup();
	}
}

function shn_setup_existing_dbsetup_complete($extra_opts=null)
{
	return _shn_setup_write_config($extra_opts['config_key_vals']);
}

/*================ Simple Configuration Step ========================*/
function shn_setup_simple_config_submit(){
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_simple_config_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_transfer_to_session();
		if(shn_setup_validate_simple_config()){
			_shn_setup_determine_step_no('shn_setup_simple_config_submit',false);
			// do setup.
			$ret = shn_setup_do_setup();
			if($ret==true){
				shn_setup_complete();
			} else {
				//echo "ERROR::";
				shn_setup_error();
			}
		} else {
			_shn_setup_determine_step_no('shn_setup_simple_config_submit',true);
			shn_setup_simple_config();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_simple_config_submit',true);
		shn_setup_simple_dbsetup();
	}
}

function shn_setup_simple_config_complete($extra_opts=null)
{
	return _shn_setup_write_config($extra_opts['config_key_vals']);
}

/*================ Start Sahana System Step ========================*/
function shn_setup_start_sahana()
{
	header("Location: ".$_POST['shn_url']);
}

/*============== Advanced Setup Select Modules Step ==================*/
function shn_setup_adv_select_modules_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_adv_select_modules_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_determine_step_no('shn_setup_adv_select_modules_submit',false);
		_shn_setup_transfer_to_session();
		$selected_mod_codes = array();
		foreach($_POST as $name=>$value){
			if(stripos($name,"module_")>-1){
				// remove junk parameter from session
				// we will be adding the entire list later.
				unset($_SESSION[$name]);
				$tmparr = explode("module_",$name);
				array_push($selected_mod_codes,$tmparr[1]);
			}
		}
		// set in session.
		$_SESSION['shn_setup_data_selected_modules'] = $selected_mod_codes;

		if(isset($_POST['scenario_customize'])){
			// from scenario setup
			shn_setup_simple_dbsetup();
		} else {
			shn_setup_adv_advanced_config();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_adv_select_modules_submit',true);
		shn_setup_select_dbsetup();
	}
}

function shn_setup_adv_select_modules_complete($extra_opts=null)
{
	return _shn_setup_adv_write_selected_modules();
}

/*=============== Advanced Setup Configuration Step ===================*/
function shn_setup_adv_advanced_config_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_adv_advanced_config_complete");
	if(!isset($_POST['back_button'])){
		_shn_setup_transfer_to_session();
		if(shn_setup_adv_validate_advanced_config()){
			_shn_setup_determine_step_no('shn_setup_adv_advanced_config_submit',false);
			shn_setup_adv_pwd_policy();
		} else {
			_shn_setup_determine_step_no('shn_setup_adv_advanced_config_submit',true);
			shn_setup_adv_advanced_config();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_adv_advanced_config_submit',true);
		shn_setup_adv_select_modules();
	}
}

function shn_setup_adv_advanced_config_complete($extra_opts=null)
{
	return _shn_setup_adv_write_advanced_config($extra_opts['config_key_vals']);
}

/*============== Advanced Setup Password Policy Step ====================*/
function shn_setup_adv_pwd_policy_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_adv_pwd_policy_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_transfer_to_session();
		if(shn_setup_adv_validate_pwd_policy()){
			_shn_setup_determine_step_no('shn_setup_adv_pwd_policy_submit',false);
			if($_SESSION['dbsetup_method'] = "USE_NEW_DB"){
				shn_setup_simple_dbsetup();
			} else if($_SESSION['dbsetup_method'] = "USE_EMPTY_DB"){
				shn_setup_empty_dbsetup();
			} else if($_SESSION['dbsetup_method'] = "USE_EXISTING_DB"){
				shn_setup_existing_dbsetup();
			}
		} else {
			_shn_setup_determine_step_no('shn_setup_adv_pwd_policy_submit',true);
			shn_setup_adv_pwd_policy();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_adv_pwd_policy_submit',true);
		shn_setup_adv_advanced_config();
	}
}

function shn_setup_adv_pwd_policy_complete($extra_opts=null)
{
	return _shn_setup_adv_write_pwd_policy($extra_opts['config_key_vals']);
}

/*============== Scenario Select Scenario Step =========================*/
function shn_setup_scen_select_scen_submit()
{
	// the following line is required to complete the setup.
	array_push($_SESSION['shn_setup_function_list'],"shn_setup_select_scen_complete");

	if(!isset($_POST['back_button'])){
		_shn_setup_determine_step_no('shn_setup_scen_select_scen_submit',false);
		_shn_setup_transfer_to_session();
		// add the pre-selected modules for the scenario to the session.
		$selected_mod_codes = explode(",",$_POST['selected_scenario']);
		// set in session.
		$_SESSION['shn_setup_data_selected_modules'] = $selected_mod_codes;

		if(isset($_POST['scenario_customize'])){
			shn_setup_adv_select_modules();
		} else {
			shn_setup_select_dbsetup();
		}
	} else {
		_shn_setup_determine_step_no('shn_setup_scen_select_scen_submit',true);
	}
}


