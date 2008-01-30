<?php
/**Main Controller of the Sahana Advanced Web Setup
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
session_start();
global $global;

if (!function_exists("gettext"))
{
	include_once ($global['approot'].'inc/lib_locale/lib_gettext.inc');
}
require_once ($global['approot'].'inc/lib_locale/gettext.inc');
require_once ($global['approot'] . 'inc/lib_security/constants.inc');
require_once ($global['approot'] . 'inc/lib_security/lib_auth.inc');
require_once ($global['approot'].'inc/handler_html_head.inc');
require_once ($global['approot'].'inc/lib_modules.inc');
require_once ($global['approot'].'inc/lib_form.inc');
require_once ($global['approot'].'inc/lib_errors.inc');
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');
require_once ($global['approot'].'inc/lib_uuid.inc');
require_once ($global['approot'].'inc/lib_validate.inc');
require_once ($global['approot'].'inc/lib_config.inc');

include('setup_actions.inc');
include('setup_pages.inc');
include('setup_validations.inc');
include('setup_utils.inc');
//state to function maps.
// The PAGE function is called on entering the state.
// The VALIDATE function is called on submit from the state.
// The NEXT function is called on successful submission with valid data. The action to be performed shoud go in this function.
// The BACK function is called when the user clicks the back button on the page.
// THe CH_STATE function is called if available just after the NEXT function call to set/update the state.
// The ON_COMPLETE function is called when the setup is complete in order to commit any required changes.
global $_state_funct_map;
$_state_funct_map = array(
	'CHECK_DEPS'=>array(	'PAGE'=>'shn_setup_general_dependancies',
							'VALIDATE'=>'shn_setup_validate_general_dependancies',
							'NEXT'=>'shn_setup_select_setup',
							'CH_STATE'=>'shn_setup_general_dependencies_ch_state'),

	'SELECT_SETUP'=>array(	'PAGE'=>'shn_setup_select_setup',
							'NEXT'=>'shn_setup_select_setup_next',
							'CH_STATE'=>'shn_setup_select_setup_ch_state'),

	'SIMPLE_DB_SETUP'=>array(	'PAGE'=>'shn_setup_simple_dbsetup',
								'VALIDATE'=>'shn_setup_validate_simple_dbsetup',
								'NEXT'=>'shn_setup_simple_dbsetup_next',
								'BACK'=>'shn_setup_simple_dbsetup_back',
								'CH_STATE'=>'shn_setup_simple_dbsetup_ch_state',
								'ON_COMPLETE'=>'shn_setup_simple_dbsetup_complete'),

	'SIMPLE_CFG_SETUP'=>array(	'PAGE'=>'shn_setup_simple_config',
								'VALIDATE'=>'shn_setup_validate_simple_config',
								'NEXT'=>'shn_setup_simple_config_next',
								'BACK'=>'shn_setup_simple_config_back',
								'CH_STATE'=>'shn_setup_simple_config_ch_state',
								'ON_COMPLETE'=>'shn_setup_simple_config_complete'),

	'ADV_MOD_SETUP'=>array(	'PAGE'=>'shn_setup_adv_select_modules',
							'VALIDATE'=>'shn_setup_adv_validate_select_modules',
							'NEXT'=>'shn_setup_adv_select_modules_next',
							'BACK'=>'shn_setup_adv_select_modules_back',
							'CH_STATE'=>'shn_setup_adv_select_modules_ch_state',
							'ON_COMPLETE'=>'shn_setup_adv_select_modules_complete'),

	'ADV_CFG_SETUP'=>array(	'PAGE'=>'shn_setup_adv_advanced_config',
							'VALIDATE'=>'shn_setup_adv_validate_advanced_config',
							'NEXT'=>'shn_setup_adv_advanced_config_next',
							'BACK'=>'shn_setup_adv_advanced_config_back',
							'CH_STATE'=>'shn_setup_adv_advanced_config_ch_state',
							'ON_COMPLETE'=>'shn_setup_adv_advanced_config_complete'),

	'ADV_PWD_POL_SETUP'=>array(	'PAGE'=>'shn_setup_adv_pwd_policy',	
								'VALIDATE'=>'shn_setup_adv_validate_pwd_policy',		
								'NEXT'=>'shn_setup_adv_pwd_policy_next',
								'BACK'=>'shn_setup_adv_pwd_policy_back',
								'CH_STATE'=>'shn_setup_adv_pwd_policy_ch_state',
								'ON_COMPLETE'=>'shn_setup_adv_pwd_policy_complete'),

	'SCEN_SEL_SETUP'=>array(	'PAGE'=>'shn_setup_scen_select_scenario',	
								'NEXT'=>'shn_setup_scen_select_scen_next',
								'BACK'=>'shn_setup_scen_select_scen_back',
								'CH_STATE'=>'shn_setup_scen_select_scen_ch_state'),

	'COMPLETE'=>array(	'PAGE'=>'shn_setup_start_sahana'),
);

// The execution order of on_complete function callbacks, because some call backs may depend on others.
global $execution_order_on_complete;
$execution_order_on_complete = array('SIMPLE_CFG_SETUP','SIMPLE_DB_SETUP','ADV_CFG_SETUP','ADV_MOD_SETUP');

// initialize only the first time.
if(isset($_SESSION['setup_state'])==false){
	// declaring the starting state and step no.
	$_SESSION['setup_state'] = 'CHECK_DEPS';
	$_SESSION['setup_step_no'] = 1;
}

shn_setup_header();

shn_setup_start();

shn_setup_footer();

/**
 * Start the setup process.
 *
 */
function shn_setup_start(){
	global $_state_funct_map,$global;

	if(isset($_SESSION['setup_state']) == false){
		echo "<p>"._t("There is an error within the setup script. The setup_state was not found in the session.")."</p>";
		return;
	}
	// record all states.
	if(!isset($_SESSION['setup_state_list'])){
		$_SESSION['setup_state_list']=array();
	}

	// do not enter duplicate states.
	$_res = array_search($_SESSION['setup_state'],$_SESSION['setup_state_list']);
	if($_res==FALSE || $_res==null){
		// state not pushed previously.
		array_push($_SESSION['setup_state_list'],$_SESSION['setup_state']);
	}

	// start setup.
	if($_SERVER['REQUEST_METHOD']=='POST'){
		// check whether back button or forward button
		if(isset($_POST['back_button'])){
			$_SESSION['setup_step_no'] = $_SESSION['setup_step_no']-1;
			_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['BACK']);
			_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['CH_STATE'],"backward");
		}else{
			// put every thing in the $_POST session with the special prefix
			_shn_setup_transfer_to_session();
				
			// validate only if validation function exists.

			if(isset($_state_funct_map[$_SESSION['setup_state']]['VALIDATE']) && (strlen($_state_funct_map[$_SESSION['setup_state']]['VALIDATE']) > 0)){
				// put every thing in the $_POST session with the special prefix
				//_shn_setup_transfer_to_session();
				// call validate function if exists.
				$return_value= _shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['VALIDATE']);

				if($return_value==true){
					$_SESSION['setup_step_no'] = $_SESSION['setup_step_no']+1;

					// call next page function if return value is true.
					_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['NEXT']);
					_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['CH_STATE']);

				}else{
					/*
					 *	The errors of the page are saved in to the session to avoid them
					 *  dissappear when the page is refreshed. The saved errors are restored
					 *  when the page is requested again.
					 */
					// make errors to be displayed when refreshed.

					if(isset($global['submit_errors'])){
						$_SESSION['setup_errors'] = $global['submit_errors'];
					}
					// show same page if error.
					_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['PAGE']);

				}
					
			}else{
				$_SESSION['setup_step_no'] = $_SESSION['setup_step_no']+1;

				// move to next step
				_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['NEXT']);
				_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['CH_STATE']);
			}
		}
	}else{
		/*
		 * This is used to restore the page errors even when the page is refreshed.
		 * The errrors saved in the session are restored in to the global variable.
		 */
		// restore any errors if any to be displayed in page.
		if(isset($_SESSION['setup_errors'])){
			$global['submit_errors'] = $_SESSION['setup_errors'];
		}

		_shn_setup_call_function($_state_funct_map[$_SESSION['setup_state']]['PAGE'],$_SESSION['step_no']);

	}
	//var_dump($_SESSION);
}

/**
 * Call a call back function by it's name.
 *
 * @param String $funct_name The name of the function to be called.
 * @param String/Array $extra_opts Any parameters, as a string or as an array as required by the called function.
 * @return unknown The return value of the called function.
 */
function _shn_setup_call_function($funct_name,$extra_opts=null){

	if(function_exists($funct_name)){
		//echo "<pre> Calling function $funct_name() with params ".var_dump($extra_opts).".</pre>";
		if($extra_opts==null){
			return $funct_name();
		}else{
			return $funct_name($extra_opts);
		}
	}else{
		echo "<p>"._t("There is an error within the setup script. The function ")."<b>".$funct_name."</b>"._t(" was not found.")."</p>";
	}

	if (!($_POST{"user_pwd"}==$re_password)){
		$error=true;
		add_error("User password and confirm password should match");
	}

	if($error){
		return false;
	}

	if (shn_validate_password($_POST["admin_name"],$_POST["root_pwd"])==false){
		$error=true;
		return false;
	}
	if (shn_validate_password($_POST["user_name"],$_POST["user_pwd"])==false){
		$error=true;
		return false;
	}
	global $global;
	include_once $global['approot']. 'inc/lib_security/lib_acl.inc';
	return (shn_acl_install($_POST['admin_name'],$_POST['root_pwd'],$_POST['user_name'],$_POST['user_pwd'],$_POST['acl']=='enable'));


}

?>