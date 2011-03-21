<?
/**
 * @name         Sahana Agasti Main Controller
 * @version      1.0
 * @author       Chamindra de Silva <chamindra@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


// Define the application's root path ~ the base path should not be exposed to the web for more security
$APPROOT = realpath(dirname(__FILE__)).'/../';

// define global $APPROOT for convenience and efficiency;
$global['approot']  = $APPROOT;
$global['previous'] = false;
$global["setup"]    = false;

// uncomment line below to use the internal error handler
//shn_main_error();

// uncomment line below to initialize the debugger
shn_main_debugger();

// uncomment to handle redirection for different browsers/device
//shn_main_redirect();

// include the base libraries
require_once($APPROOT.'inc/lib_config.inc');
require_once($APPROOT.'inc/lib_modules.inc');
require_once($APPROOT.'inc/lib_errors.inc');

// clean get and post variables
shn_main_filter_getpost();

// uncomment the line below to allow a check for the installer (Agasti will be packaged this way) we turn it off to save time when we are sure we are not installing :)
//shn_main_install_check();

// include the main sysconf file
require($APPROOT.'conf/sahana.conf');

// include the main libraries the system depends on
require_once ($APPROOT.'inc/handler_db.inc');
require_once($APPROOT.'inc/lib_security/lib_crypt.inc');
require_once($APPROOT.'inc/handler_session.inc');
//require_once($APPROOT.'inc/lib_security/handler_openid.inc'); // replacing openID lib soon....
require_once($APPROOT.'inc/lib_security/lib_auth.inc');
require_once($APPROOT.'inc/lib_security/constants.inc');
require_once($APPROOT.'inc/lib_locale/handler_locale.inc');
require_once($APPROOT.'inc/lib_exception.inc');
require_once($APPROOT.'inc/lib_user_pref.inc');

// check permissions on the currrent event ~ if using event manager (we check permission in case we need to redirect for permissions violations)
shn_main_checkEventPermissions();

// clean post/get variables
shn_main_clean_getpost();

// populate user preferences
shn_user_pref_populate();

// load all the configurations based on the priority specified files and database, base and mods
shn_config_load_in_order();

// start the front controller pattern
shn_main_front_controller();



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS BELOW /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// cleans the GET and POST
function shn_main_clean_getpost() {
	global $global;

	require_once($global['approot'].'/3rd/htmlpurifier/include.php');
	$purifier = new HTMLPurifier();

	foreach($_POST as $key=>$val) {
		if(!is_array($_POST[$key])) {
			$val = $purifier->purify($val);
			$val = escapeHTML($val);
			$_POST[$key] = $val;
		}
	}
	foreach($_GET as $key=>$val) {
		if(!is_array($_GET[$key])) {
			$val = $purifier->purify($val);
			$val = escapeHTML($val);
			$_GET[$key] = $val;
		}
	}
}



// process the module actions
function shn_main_filter_getpost() {
	global $global, $conf;

	// we set the default module/function here. by default, we send them to the landing page of the resources module
	$m = isset($conf['default_module']) ? $conf['default_module'] : "rez";
	$a = isset($conf['default_action']) ? $conf['default_action'] : "landing";

	if (!$global['previous']) {
		$global['action'] = !isset($_REQUEST['act']) ? $a : $_REQUEST['act'];
		$global['module'] = !isset($_REQUEST['mod']) ? $m : $_REQUEST['mod'];
	}
}



// front controller
function shn_main_front_controller() {
	global $global;
	global $APPROOT;
	global $conf;
	$action = $global['action'];
	$module = $global['module'];

	// check if we should enable database logging....
	if(isset($conf['enable_monitor_sql']) && $conf['enable_monitor_sql'] == true) {
		$global['db']->LogSQL();
	}

	// are we streaming PLUS SOAP Services?
	if(isset($_REQUEST['wsdl'])) {
		shn_main_plus();
		exit();
	}

	// are we straming anything else?
	if(isset($_REQUEST['stream'])) {
		$stream = $_REQUEST['stream'];
	} else {
		$stream = null;
	}

	// check if the appropriate stream library exists
	if(array_key_exists('stream', $_REQUEST) && file_exists($APPROOT.'/inc/lib_stream_'.$stream.'.inc')) {
		require_once ($APPROOT.'/inc/lib_stream_'.$stream.'.inc');
		$stream_ = $stream.'_'; // for convenience

	// else revert to the html stream
	} else {
		if(array_key_exists('stream', $_REQUEST)) {
			add_error(_t('The stream requested is not valid.'));
		}
		require_once $APPROOT."/inc/lib_stream_html.inc";
		$stream_ = null; // the default is html
	}

	// Redirect the module based on the action performed
	// redirect admin functions through the admin module
	if(preg_match('/^adm/',$action)) {
		$global['effective_module'] = $module = 'admin';
		$global['effective_action'] = $action = 'modadmin';
	} // the orignal module and action is stored in $global

	// This is a redirect for the report action
	if(preg_match('/^rpt/',$action)) {
		$global['effective_module'] = $module = 'rs';
		$global['effective_action'] = $action = 'modreports';
	}

	// fixes the security vulnerability associated with null characters in the $module string
	$module = str_replace("\0", "", $module);

	// identify the correct module file based on action and module
	$module_file = $APPROOT.'mod/'.$module.'/main.inc';

	// check if module exists (modules main.inc)
	if(file_exists($module_file)) {
		include($module_file);
	} else {
		// default to the home page if the module main does not exist
		add_error(_t('The requested module is not installed in Sahana'));
		$module = 'rez';
		$action = 'landing';
		include($APPROOT.'mod/rez/main.inc');
	}

	// identify the name of the module function based on the action,
	// stream and module
	$module_function = 'shn_'.$stream_.$module.'_'.$action;

	// if function does not exist re-direct
	if(!function_exists($module_function)) {

		// try to see if there is a generic Xstream function instead
		$module_function='shn_XST_'.$module.'_'.$action;

		if(!function_exists($module_function)) {

			// display the error on the relevant stream
			if( null == $stream_ ) {
				add_error(_t('The action requested is not available'));
				$module_function = 'shn_'.$module.'_default';
			} else {
				// if this does not exist display the error in the html homepage
				add_error(_t('This action does not support the stream type.'));
				$module_function = "display_errors"; // just display the errors
			}
		}
	}

	// list of exceptions generated by calling the function.
	$global['exception_list'] = array();

	// initialize stream based on selected steam POST value this includes the inclusion of various sections in XHTML including the HTTP header,content header, menubar, login
	shn_stream_init();

	// store the last module, stream and action in the history
	$_SESSION['last_module'] = $module;
	$_SESSION['last_action'] = $action;
	$_SESSION['last_stream'] = $stream;

	if($stream_ == null) {

		if((($global['action'] == 'signup_cr') || ($global['action'] == 'signup') || ($global['action'] == 'forgotPassword') || ($global['action'] == 'loginForm')) && ($global['module'] = 'pref')) {
			// TODO: Check on =
			// returns true if self-signup is enabled
			if(shn_acl_is_signup_enabled()) {
				$module_function();
			}
		} else {
			// if not a self-signup action
			$allowed_mods = shn_get_allowed_mods_current_user();

			// check if requested module is within users allowed modules
			$res = array_search($module, $allowed_mods, false);

			if (false !== $res) {
				if( shn_acl_check_perms($module, $module_function) == ALLOWED) {
					$module_function();
				} else {
					shn_error_display_restricted_access();
				}
			} else {
				shn_error_display_restricted_access();
			}
		}

	} else {
		// if the steam is not HTML
		$allowed_mods = shn_get_allowed_mods_current_user();

		// check if requested module is within users allowed modules
		$res = array_search($module, $allowed_mods, false);

		// hack for messaging module receive function
		$res = ($stream='text'&$action='receive_message')?true:$res;
		if(false !== $res) {
			if(shn_acl_check_perms($module, $module_function) == ALLOWED) {
				$module_function();
			} else {
				add_error(shn_error_get_restricted_access_message());
			}
		} else {
			add_error(shn_error_get_restricted_access_message());
		}
	}

	// close up the stream. In HTML send the footer
	shn_stream_close();
}



// check if the event manager is installed and if so, check if the current user has group permission to the currently chosen incident
function shn_main_checkEventPermissions() {
	global $APPROOT;
	global $global;

	// only check if the event manager is installed
	if(file_exists($APPROOT."mod/em/main.inc")) {

		// check if visitor comes in with no shortname and initialize it as the default event if so to avoid a js redirect
		isset($_GET['shortname']) ? $short = $_GET['shortname'] : $short = "";
		if($short == "") {
			$q = "
				SELECT shortname
				FROM incident
				WHERE `default` = '1'
				LIMIT 1;
			";
			$res = $global['db']->GetAll($q);
			if (!empty($res)) {
				foreach($res as $row) {
					$_GET['shortname'] = $row['shortname'];
				}
			}
		}

		// check if the user has the permissions necessary for this event/incident
		$q = "
			SELECT *
			FROM incident
			WHERE shortname = '". mysql_real_escape_string($_GET['shortname'])."'
			LIMIT 1;
		";

		$res = $global['db']->GetAll($q);
		if(!empty($res)) {
			foreach($res as $row) {

				// if the user is not privileged to the event, and the event is not public, then redirect the user to a resource error page
				if($row['private_group'] != null) {
					if(!isset($_SESSION['group_id']) || (isset($_SESSION['group_id']) && $row['private_group'] != $_SESSION['group_id'])) {

						// this is the page we redirect the user to if they dont have permission to view/access this event
						header("Location: ../index.php?mod=rez&act=default&page_id=-20");
					}
				}
			}

		// they provided us a fake/non-existant event... redirect em back to having no event, thus default event :)
		} else {
			header("Location: ../index.php");
		}

		// escape it here in case we forget to elsewhere...
		$_GET['shortname'] =  mysql_real_escape_string($_GET['shortname']);
	}
}



// sahana internal error handling
function shn_main_error() {
	// Include error handling routines
	require_once($APPROOT.'inc/handler_error.inc');
	require_once($APPROOT.'inc/lib_exception.inc');

	// handle error reporting seperately and set our own error handler
	error_reporting(0);
	set_error_handler('shn_sahana_error_handler');

	//add default exception handler
	set_exception_handler('shn_sahana_exception_handler');
}



// php-console debugger
function shn_main_debugger() {
	// only use debugger on these internal staging servers...
	if(($_SERVER['HTTP_HOST'] == "plstage.nlm.nih.gov")
	|| ($_SERVER['HTTP_HOST'] == "plstage")
	|| ($_SERVER['HTTP_HOST'] == "archivestage.nlm.nih.gov")
	|| ($_SERVER['HTTP_HOST'] == "archivestage")) {

		require_once('../3rd/php-console/PhpConsole.php');
		PhpConsole::start(true, true, dirname(__FILE__));

	// if not on development servers, disable error reporting
	} else {
		error_reporting(0);
	}
}



// handle redirection if need be
function shn_main_redirect() {
	global $global;

	// redirect? only if we are not using the stream module
	if (!isset($_GET['stream'])) {
		include_once($global['approot']."/inc/browser_caps.inc");
		//$bc = $global['bcaps']->getBrowser(null, true);

		// EXAMPLE of how to redirect for different user agents
		/*
		// check for iPod/iPhone and redirect them a different site for mobiles
		if ((strstr($bc['browser_name'], "iPod")) || (strstr($bc['browser_name'], "iPhone"))) {
			header("Location: http://sahana/mobile");
		}
		*/
	}
}



// check if we should install Agasti
function shn_main_install_check() {
	// does the sahana.conf exist in the conf directory? if not start the web installer
	if (!file_exists($APPROOT.'conf/sahana.conf')) {
		$global["setup"] = true;
		//shn_main_web_installer();
		// we have to come up with a new web installer... since the old one is gone!
	}
}



// provide SOAP Services
function shn_main_plus() {
	global $APPROOT;
	require_once($APPROOT.'mod/plus/server.php');
}

