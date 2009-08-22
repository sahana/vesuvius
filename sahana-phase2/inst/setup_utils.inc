<?php
/**Utility functions of the Sahana Advanced Web Setup
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

define ('SETUP_DATA_PREFIX',"shn_setup_data_");


/**
 * Get the selected type of setup. Returns either of SIMPLE_SETUP,ADVANCED_SETUP,SCENARIO_SETUP defined above.
 *
 * @return String The type of setup selected.
 */
function _shn_setup_get_setup_type(){
	return $_SESSION['setup_type'];
}


/**
 * Returns the list of module short codes selected to be installed, as an array.
 *
 * @return List of module short codes selected for installation.
 */
function _shn_setup_get_selected_modules(){
	return $_SESSION['shn_setup_data_selected_modules'];
}

/**
 * Return whether modules were specifically selected for installation.
 *
 * @return boolean whether modules were specifically selected.
 */
function _shn_setup_are_modules_selected(){
	return isset($_SESSION['shn_setup_data_selected_modules']);
}

/**
 * Whether the user selected to setup sample data.
 *
 * @return boolean Whether to setup sample data.
 */
function _shn_setup_is_setup_sample_data(){
	return isset($_SESSION['shn_setup_data_dbsample']);
}

/**
 * Whether the user selected to drop the existing database with the same name as the given database name.
 *
 * @return boolean Whether to drop the existing database.
 */
function _shn_setup_is_drop_db(){
	return isset($_SESSION['shn_setup_data_drop_ex_db']);
}

/**
 * Whether the user selected to keep the existing user with the same name as the system database user.
 *
 * @return boolean Whether to keep the user.
 */
function _shn_setup_is_keep_user(){
	return isset($_SESSION['shn_setup_data_keep_ex_user']);
}
/*
 function is_post_request(){
 return $_SERVER['REQUEST_METHOD']=='POST';
 }

 function is_get_request(){
 return $_SERVER['REQUEST_METHOD']=='GET';
 }
 */
/**
 * Transfer all parameters in the $_POST to the $_SESSION. The key would be prefixed by SETUP_DATA_PREFIX define above.
 *
 */
function _shn_setup_transfer_to_session(){
	foreach ($_POST as $key=>$value){
		_shn_setup_put_value_in_session($key,$value);
	}
}

/**
 * Filter the given array to obtain values having key "shn_setup_data_" prefix.
 *
 * @param Array $source The parameter source array
 * @return Array The filtered parameters with the real keys.
 */
function _shn_setup_filter_post_params($source){
	$dest = array();
	if(isset($source)){
		foreach($source as $key=>$value){
			if(stripos($key,SETUP_DATA_PREFIX) !== FALSE){
				$_txt = explode(SETUP_DATA_PREFIX,$key);
				$dest[$_txt[1]]=$value;
			}
		}
	}
	return $dest;
}

/**
 * Get the appropriate named parameter value from the parameter list passed in.
 *
 * @param Array $params_list The list of parameters.
 * @param String $param The required key.
 * @return unknown $params_list[$param]
 */
function _shn_setup_get_post_param($params_list,$param){
	return $params_list[SETUP_DATA_PREFIX.$param];
}

/**
 * Put a setup data key and value in the session for later use. The key is prefixed using the SETUP_DATA_PREFIX.
 *
 * @param String $key The data key.
 * @param unknown_type $value The data value.
 */
function _shn_setup_put_value_in_session($key,$value){
	$_SESSION[SETUP_DATA_PREFIX.$key]=$value;
}

/**
 * Get a list of avaliable themes in the theme directory.
 *
 * @return Array List of themes.
 */
function _shn_setup_get_available_themes(){
	global $global;

	$themes_dir = opendir($global['approot']."www/theme");

	$available_themes = array();
	while(false !== ($file = readdir($themes_dir))){
		if(is_dir($global['approot']."www/theme/".$file)){
			if($file!="." && $file!=".." && $file!="CVS"){
				array_push($available_themes,$file);
			}

		}
	}
	return $available_themes;
}

/**
 * Get a listo of module short codes of the essencial modules.
 *
 * @return Array Array containing the essencial modules' short codes.
 */
function _shn_setup_get_essencial_modules(){
	return array ('home','admin','pref');
}

function _shn_setup_set_step_function($funct){
	$_SESSION['setup_step_function'] = $funct;
}

function _shn_setup_get_step_function(){
	return $_SESSION['setup_step_function'];
}

function _shn_setup_get_step_no(){
	return $_SESSION['setup_step_no'];
}

/**
 * Determines and appropriately increments/decrements the step number
 * depending on whether a page refresh occured or not.
 *
 * @param String $function_call The name of the function currently in execution
 * @param boolean $back_button Whether the back button was presed.
 */
function _shn_setup_determine_step_no($function_call,$back_button){
	//echo "Determining step number...<br/>";
	//echo $_SESSION['setup_step_no']."<br/>";
	if($function_call == $_SESSION['setup_previous_step_function']){
		// page refresh occured.
		// leave the number as it is.
	}else{
		if($back_button==true){
			$_SESSION['setup_step_no'] = $_SESSION['setup_step_no']-1;
		}else{
			$_SESSION['setup_step_no'] = $_SESSION['setup_step_no']+1;
		}
		$_SESSION['setup_previous_step_function'] = $function_call;
	}
}


