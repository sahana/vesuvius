<?php 
/**
* Sahana front controller, through which all actions are dispatched
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

// Specify the base location of the Sahana insallation
// The base should not be exposed to the web for security reasons
// only the www sub directory should be exposed to the web

$global['approot'] = realpath(dirname(__FILE__)).'/../';
$global['previous']=false;

// === initialize configuration variables ===
if (file_exists($global['approot'].'conf/sysconf.inc.php')) {

	require_once ($global['approot'].'conf/sysconf.inc.php');
	require_once ($global['approot'].'inc/lib_modules.inc'); 
	require_once ($global['approot'].'inc/handler_db.inc');
	require_once ($global['approot'].'inc/lib_config.inc');

	//fetch config values : base values
	shn_config_database_fetch('base');

	require_once ($global['approot'].'inc/lib_session/handler_session.inc');
	require_once ($global['approot'].'inc/lib_locale/handler_locale.inc'); 
	include_once ($global['approot'].'inc/lib_user_pref.inc');

	if(!$global['previous']){
		$global['action'] = (NULL == $_REQUEST['act']) ? "default" : $_REQUEST['act'];
		$global['module'] = (NULL == $_REQUEST['mod']) ? "home" : $_REQUEST['mod'];
	}
	$global['stream_type'] = $_GET['stream_type'];

	// hack to stop the disabling of the Sahna ACL via the streaming module
	if (strpos($_GET['act'], "acl_enable") > -1) {
		die();
	}

	shn_front_controller();

} else { // Launch the web setup
	//Install hack     
	//require ($global['approot'].'inst/setup.inc');
	require_once ($global['approot'].'/inc/lib_st_'.$_GET['stream_type'].'.inc');
	shn_stream_init();
}



// === front controller ===
function shn_front_controller() {
	global $global;
	global $conf;
	$approot = $global['approot'];
	$action = $global['action'];
	$module = $global['module'];
	
	// check the users access permissions for this action
	$req_act='shn_'.$module.'_'.$action;
	//  $acl_enabled=shn_acl_get_state($module);
	//@todo Errors should be thrown properly
	
	//    $module_enabled=shn_acl_is_enabled($module);
	//  $allow = (shn_acl_check_perms_action($_SESSION['user_id'],$req_act) || 
	//           !$acl_enabled)? true : false;
	
	
	// Redirect the module based on the action performed
	// redirect admin functions through the admin module
	if (preg_match('/^adm/',$action)) {
		$module = 'admin';   
		$action = 'modadmin';
	}
	
	//include the coreect streaming library 
	if($global['stream_type'] && file_exists($approot.'/inc/lib_st_'.$global['stream_type'].'.inc') ){
		require_once ($approot.'/inc/lib_st_'.$global['stream_type'].'.inc');
		if(file_exists($approot.'/mod/'.$module.'/'.$global['stream_type'].'.inc'))
		$default_file = $approot.'/mod/'.$module.'/'.$global['stream_type'].'.inc';
		else
		$default_file = 'stream.inc';
	}else
		$default_file = 'main.inc';

	// include the correct module file based on action and module
	$module_file = $approot.'mod/'.$module.'/'.$default_file;
	if (! file_exists($module_file)) {
		$module_file = $approot.'mod/home/'.$default_file;
	}

	//Initilize the stream
	if($default_file == 'stream.inc')
		shn_stream_init($module_file);

	//Include the module file
	include($module_file); 

	// include the module configuration files 
	$d = dir($approot.'mod/');
	while (false !== ($f = $d->read())) {
		if (file_exists($approot.'mod/'.$f.'/conf.inc')) {
		include ($approot.'mod/'.$f.'/conf.inc');
		}
	} 

	//Override config values with database ones
	shn_config_database_fetch('all');

	//    if($allow){
		// compose and call the relevant module function 
		$module_function = 'shn_'.$module.'_'.$action;
		if (!function_exists($module_function)) {
		$module_function='shn_'.$module.'_default';
		}
		$_SESSION['last_module']=$module;
		$_SESSION['last_action']=$action;
		$output = $module_function(); 

		if($default_file == 'stream.inc')
		shn_stream_close($module_function,$output);

	//   }else {
		//@todo : throw the error correctly
	//    }
}

