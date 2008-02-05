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
$APPROOT = realpath(dirname(__FILE__)).'/../';

// define global $APPROOT for convenience and efficiency;
$global['approot'] = $APPROOT;
$global['previous'] = false;

// Include error handling routines
require_once($APPROOT.'inc/lib_errors.inc');

// handle error reporting seperately and set our own error handler
if (true) { // set to false if you want to develop without the custom error handler
	error_reporting(0);
	set_error_handler('shn_sahana_error_handler');
}

// include the base libraries for both the web installer and main app
// require_once ($APPROOT.'inc/handler_error.inc');
require_once ($APPROOT.'inc/lib_config.inc');
require_once ($APPROOT.'inc/lib_modules.inc');

// === filter the GET and POST ===
shn_main_filter_getpost();

// === Setup if not setup and load configuration ===

// if installed the sysconf.inc will exist in the conf directory
// if not start the web installer
if (!file_exists($APPROOT.'conf/sysconf.inc')){
	$global["setup"]=true;
	// Call the web installer
	shn_main_web_installer();

} else {
	$global["setup"]=false;
	// define the configuration priority order
	require_once ($APPROOT.'conf/conf-order.inc');

	// include the main sysconf file
	require ($APPROOT.'conf/sysconf.inc');

	// include the main libraries the system depends on
	require_once ($APPROOT.'inc/handler_db.inc');

	require_once ($APPROOT.'inc/lib_security/lib_crypt.inc');
	require_once ($APPROOT.'inc/lib_session/handler_session.inc');
	require_once ($APPROOT.'inc/lib_security/handler_openid.inc');
	require_once ($APPROOT.'inc/lib_security/lib_auth.inc');
	require_once ($APPROOT.'inc/lib_security/constants.inc');
	require_once ($APPROOT.'inc/lib_locale/handler_locale.inc');
	require_once ($APPROOT.'3rd/htmlpurifier/library/HTMLPurifier.auto.php');
	require_once ($APPROOT.'3rd/htmlpurifier/smoketests/common.php');
	shn_main_clean_getpost();
	//include the user preferences
	include_once ($APPROOT.'inc/lib_user_pref.inc');
	shn_user_pref_populate();

	// load all the configurations based on the priority specified
	// files and database, base and mods
	shn_config_load_in_order();
	/*
	 $mods=shn_get_allowed_mods_current_user();
	 foreach ($mods as $mod){
	 $conf['mod_'.$mod.'_enabled']=true;
	 }*/
	if(($_GET["mod"]="admin")&&($_GET["act"]=="acl_enable_acl_cr")){
		if( shn_acl_check_perms("admin","acl_enable_acl_cr")==true){
			include_once ($APPROOT.'mod/admin/acl.inc');
			_shn_admin_acl_enable_acl_cr(false);
		}
	}

	// start the front controller pattern
	shn_main_front_controller();

}

// === cleans the GET and POST ===
function shn_main_clean_getpost()
{

	$purifier = new HTMLPurifier();

	foreach ($_POST as $key=>$val){
		if(is_array($_POST[$key])==true){

		}else{
			//$val=shn_db_clean($val);
			$val = $purifier->purify($val);
			$val=escapeHTML($val);
			$_POST[$key]=$val;
		}

	}

}
// === process the GET and POST ===
function shn_main_filter_getpost()
{
	global $global;

	if(!$global['previous']){
		$global['action'] = (NULL == $_REQUEST['act']) ?
                                "default" : $_REQUEST['act'];
		$global['module'] = (NULL == $_REQUEST['mod']) ?
                                "home" : $_REQUEST['mod'];

		if(( $global['action']=='signup')&&($_REQUEST['mod']==null)){
			$global['module']="pref";
		}

	}
}

// === front controller ===
function shn_main_front_controller()
{
	global $global, $APPROOT, $conf;
	$action = $global['action'];
	$module = $global['module'];
    $stream = $_REQUEST['stream'];
    // check if the appropriate stream library exists

	if( array_key_exists('stream', $_REQUEST) &&
        file_exists($APPROOT.'/inc/lib_stream_'.$stream.'.inc')) {

		require_once ($APPROOT.'/inc/lib_stream_'.$stream.'.inc');
		$stream_ = $stream.'_'; // for convenience

	} else { // else revert to the html stream

        if (array_key_exists('stream', $_REQUEST)) {
            add_error(_t('The stream requested is not a valid stream'));
        }
		require_once $APPROOT."/inc/lib_stream_html.inc";
		$stream_ = null; // the default is html
	}

	// Redirect the module based on the action performed
	// redirect admin functions through the admin module
	if (preg_match('/^adm/',$action)) {

		$global['effective_module'] = $module = 'admin';
		$global['effective_action'] = $action = 'modadmin';
	} // the orignal module and action is stored in $global

	// This is a redirect for the report action
	if (preg_match('/^rpt/',$action)) {

		$global['effective_module'] = $module = 'rs';
		$global['effective_action'] = $action = 'modreports';
	}

	// identify the correct module file based on action and module
	$module_file = $APPROOT.'mod/'.$module.'/main.inc';

	// check if module exists (modules main.inc)
	if (file_exists($module_file)) {
		include($module_file);
	} else { // default to the home page if the module main does not exist
        add_error(_t('The requested module is not installed in Sahana'));
        $module = 'home';
        $action = 'default';
		include($APPROOT.'mod/home/main.inc');
	}

	// identify the name of the module function based on the action,
    // stream and module
	$module_function = 'shn_'.$stream_.$module.'_'.$action;

    // if function does not exist re-direct
    if (!function_exists($module_function)) {

        // try to see if there is a generic Xstream function instead
        $module_function='shn_XST_'.$module.'_'.$action;

        if (!function_exists($module_function)) {

            // display the error on the relevant stream
            if ( null == $stream_ ) {
                add_error(_t('The action requested is not available'));
                $module_function = 'shn_'.$module.'_default';
            } else {
                // if this does not exist display the error in the html homepage
                add_error(_t('This action does not support the '.$stream.' stream type.'));
                $module_function = "display_errors"; // just display the errors
            }
        }

    }

	// list of exceptions generated by calling the function.
	$global['exception_list'] = array();

	// initialize stream based on selected steam POST value
	// this includes the inclusion of various sections in XHTML
    // including the HTTP header,content header, menubar, login
	shn_stream_init();

    // If this is a new session redirect to a welcome page
	if($_SESSION['first_time_run']==true) {

		include_once($APPROOT.'mod/home/main.inc');
		shn_home_welcome();

	} else { // default behavior

        // store the last module, stream and action in the history
		$_SESSION['last_module']=$module;
		$_SESSION['last_action']=$action;
		$_SESSION['last_stream']=$stream;

		if($stream_==null) {

			if(( ($global['action'] == 'signup_cr')
                    or ($global['action'] == 'signup'))
                    && ($global['module'] = 'pref')) {  // TODO: Check on =

                // returns true if self-signup is enabled
				if( shn_acl_is_signup_enabled() ) {
                    $module_function();
                }

			} else { // if not a self-signup action

				$allowed_mods = shn_get_allowed_mods_current_user();

                // check if requested module is within users allowed modules
				$res = array_search($module,$allowed_mods,false);

				if(false !== $res){

					if( shn_acl_check_perms($module,$module_function) == ALLOWED){
						$module_function();
					}else{
						//shn_error_display_restricted_access();
					}

				} else {
					shn_error_display_restricted_access();
				}
			}

		} else { // if the steam is not HTML

            // each stream has it's own check permissions function.
			$stream_acl_funct='shn_'.$stream_.'check_perms';

			if( $stream_acl_funct() == ALLOWED ){
				$module_function();
			}
		}
	}

	// close up the stream. In HTML send the footer
	shn_stream_close();


}

// Call the web installer
function shn_main_web_installer()
{
	global $global, $APPROOT, $conf;

	// The 'help' action is a special case. The following allows the popup help text
	// to be accessed before the sysconf.inc file has been created.
	if ($global['action'] == "help"){
		require_once ($APPROOT."/inc/lib_stream_{$_REQUEST['stream']}.inc");

		$module = $global['module'];

		$module_file = $APPROOT.'mod/'.$module.'/main.inc';

		include($module_file);

		shn_stream_init();

		$module_function='shn_'.$_REQUEST['stream'].'_'.$module.'_'.$global['action'];

		$_SESSION['last_module']=$module;
		$_SESSION['last_action']=$action;

		$module_function();

		shn_stream_close();
	}
	else{
		// include the sysconfig template for basic conf dependancies
		require_once ($APPROOT.'conf/sysconf.inc.tpl');

		// launch the web setup wizard
		require ($APPROOT.'inst/setup.inc');
	}
}
