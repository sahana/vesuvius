<?php
/**Action functions of the Sahana Advanced Web Setup
*
* PHP version 4 and 5
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
/*
 * ===================================================================
 * 				Actual System Setup Function 
 * ===================================================================
 */
function shn_setup_do_setup(){
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
			}else if(is_array($conf_value)){
				// handle arrays.
			}
		}
	}


	// reorder the setup_state_list according to the execution order.
	if(isset($execution_order_on_complete) && isset($_SESSION['setup_state_list'])){
		foreach($execution_order_on_complete as $ord_state){
			foreach($_SESSION['setup_state_list'] as $state){
				if(isset($_state_funct_map[$state]['ON_COMPLETE']) && ($state==$ord_state)){
					_shn_setup_call_function($_state_funct_map[$state]['ON_COMPLETE'],array('config_key_vals'=>$config_key_vals));
				}
			}
		}
	}else{
		// call the complete call backs in the order of states
		if(isset($_SESSION['setup_state_list'])){
			foreach($_SESSION['setup_state_list'] as $state){
				if(isset($_state_funct_map[$state]['ON_COMPLETE'])){
					_shn_setup_call_function($_state_funct_map[$state]['ON_COMPLETE'],array('config_key_vals'=>$config_key_vals));
				}
			}
		}
	}
	//call the call backs in the defined order (if defined in global $execution_order_on_complete) to complete setup.



	return true;

	/*
	 $result = true;
	 $result &= _shn_setup_write_config($config_key_vals);

	 $result &= _shn_setup_setupdb($config_key_vals);

	 if($result==false){
		//undo all changes.
		_shn_setup_db_undo_mysql($config_key_vals);
		_shn_setup_write_config($config_key_vals,true);
		}

		// return the inverse. 1 if error 0 if no errors.
		return !$result;*/

}
/*
 * ===================================================================
 * 				Action Functions
 * ===================================================================
 */

function shn_setup_general_dependencies_ch_state(){
	$_SESSION['setup_state'] = 'SELECT_SETUP';
}

function shn_setup_select_setup_next(){
	// move to appropriate setup.
	if(isset($_POST['setup_type_simple'])){
		// set the setup type in the session.
		$_SESSION['setup_type'] = 'SIMPLE';
		shn_setup_simple_dbsetup();
	}else if(isset($_POST['setup_type_adv'])){
		// set the setup type in the session.
		$_SESSION['setup_type'] = 'ADV';
		shn_setup_adv_select_modules();

	}else if(isset($_POST['setup_type_scen'])){
		// set the setup type in the session.
		$_SESSION['setup_type'] = 'SCEN';
		shn_setup_simple_dbsetup();
	}else{
		// set the setup type in the session.
		$_SESSION['setup_type'] = $_POST['setup_type'];
		shn_setup_simple_dbsetup();
	}
}

function shn_setup_select_setup_ch_state($action='forward'){
	if($action=='forward'){
		// change the state appropriately.
		if($_SESSION['setup_type']=='SIMPLE'){

			$_SESSION['setup_state'] = 'SIMPLE_DB_SETUP';

		}else if($_SESSION['setup_type'] == 'ADV'){

			$_SESSION['setup_state'] = 'ADV_MOD_SETUP';

		}else if($_SESSION['setup_type'] == 'SCEN'){

			$_SESSION['setup_state'] = 'SIMPLE_DB_SETUP';

		}else{
			// default.
			$_SESSION['setup_state'] = 'SIMPLE_DB_SETUP';

		}
	}else{
		$_SESSION['setup_state'] = 'SELECT_SETUP';
	}
}

/*================= Simple Database Setup Step ====================*/
function shn_setup_simple_dbsetup_next(){
	//separate the db host and port.
	$host_port = _shn_setup_get_post_param($_SESSION,"db_host");
	if(isset($host_port) && strpos($host_port,":")!==false){
		$_vals = explode($host_port,":");
		_shn_setup_put_value_in_session("db_host",$_vals[0]);
		_shn_setup_put_value_in_session("db_port",$_vals[1]);
	}
	
	shn_setup_simple_config();
}

function shn_setup_simple_dbsetup_back(){
	if($_SESSION['setup_type']=='SIMPLE'){
		shn_setup_select_setup();
	}else if($_SESSION['setup_type'] == 'ADV'){
		shn_setup_adv_pwd_policy();
	}else if($_SESSION['setup_type'] == 'SCEN'){
		
	}else{
		// default.
		shn_setup_select_setup();
	}
}

function shn_setup_simple_dbsetup_ch_state($action='forward'){
	if($action=='forward'){
		$_SESSION['setup_state'] = 'SIMPLE_CFG_SETUP';
	}else{
		$_SESSION['setup_state'] = 'SELECT_SETUP';
	}
}

function shn_setup_simple_dbsetup_complete($extra_opts){
	return _shn_setup_setupdb($extra_opts['config_key_vals']);
}

/*================ Simple Configuration Step ========================*/
function shn_setup_simple_config_next(){
	// do setup.
	$res = shn_setup_do_setup();
	if(isset($res) && $res == false){
		// there were errors during setup.
		add_error(_("There was an error, due to which the setup can not complete successfully. All changes made were attempted to be rolled back."));
		shn_setup_error();
	}else{
		shn_setup_complete();
	}
}

function shn_setup_simple_config_back(){
	shn_setup_simple_dbsetup();
}

function shn_setup_simple_config_ch_state($action='forward'){
	if($action=='forward'){
		$_SESSION['setup_state'] = 'COMPLETE';
	}else{
		$_SESSION['setup_state'] = 'SIMPLE_DB_SETUP';
	}
}

function shn_setup_simple_config_complete($extra_opts){
	return _shn_setup_write_config($extra_opts['config_key_vals']);
}

/*================ Start Sahana System Step ========================*/
function shn_setup_start_sahana(){
	header("Location: ".$_POST['shn_url']);
}

/*============== Advanced Setup Select Modules Step ==================*/
function shn_setup_adv_select_modules_next(){
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

	shn_setup_adv_advanced_config();
}

function shn_setup_adv_select_modules_back(){
	shn_setup_select_setup();
}

function shn_setup_adv_select_modules_ch_state($action='forward'){
	if($action=='forward'){
		$_SESSION['setup_state'] = 'ADV_CFG_SETUP';
	}else{
		$_SESSION['setup_state'] = 'SELECT_SETUP';
	}
}

function shn_setup_adv_select_modules_complete(){
	_shn_setup_adv_write_selected_modules();
}

/*=============== Advanced Setup Configuration Step ===================*/
function shn_setup_adv_advanced_config_next(){
	shn_setup_adv_pwd_policy();
}

function shn_setup_adv_advanced_config_back(){
	shn_setup_adv_select_modules();
}

function shn_setup_adv_advanced_config_ch_state($action='forward'){
	if($action=='forward'){
		$_SESSION['setup_state'] = 'ADV_PWD_POL_SETUP';
	}else{
		$_SESSION['setup_state'] = 'ADV_MOD_SETUP';
	}
}

function shn_setup_adv_advanced_config_complete($extra_opts){
	_shn_setup_adv_write_advanced_config($extra_opts['config_key_vals']);
}

/*============== Advanced Setup Password Policy Step ====================*/
function shn_setup_adv_pwd_policy_next(){
	shn_setup_simple_dbsetup();
}

function shn_setup_adv_pwd_policy_back(){
	shn_setup_adv_advanced_config();
}

function shn_setup_adv_pwd_policy_ch_state($action='forward'){
	if($action=='forward'){
		$_SESSION['setup_state'] = 'SIMPLE_DB_SETUP';
	}else{
		$_SESSION['setup_state'] = 'ADV_CFG_SETUP';
	}
}

function shn_setup_adv_pwd_policy_complete($extra_opts){
	_shn_setup_adv_write_pwd_policy($extra_opts['config_key_vals']);
}
?>
