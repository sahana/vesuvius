<?php

/**Main Controller of the Sahana Advanced Web Setup
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
 
session_start();
global $global;

if (!function_exists("gettext")) {
	include_once ($global['approot'].'inc/lib_locale/lib_gettext.inc');
}
require_once ($global['approot'].'inc/lib_locale/gettext.inc');
require_once ($global['approot'].'inc/lib_security/constants.inc');
require_once ($global['approot'].'inc/lib_security/lib_auth.inc');
require_once ($global['approot'].'inc/handler_html_head.inc');
require_once ($global['approot'].'inc/lib_modules.inc');
require_once ($global['approot'].'inc/lib_form.inc');
require_once ($global['approot'].'inc/lib_errors.inc');
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');
require_once ($global['approot'].'inc/lib_uuid.inc');
require_once ($global['approot'].'inc/lib_validate.inc');
require_once ($global['approot'].'inc/lib_config.inc');

global $writableDirectories;
$writableDirectories = array('www/tmp', 'conf', 'backups');

include('setup_actions.inc');
include('setup_pages.inc');
include('setup_validations.inc');
include('setup_utils.inc');

/**
 * Start the setup process.
 *
 */
function shn_setup_start()
{
	global $global;

	if(isset($_SESSION['setup_step_no'])==false){
		// initialize only the first time.
		session_unset();
		$_SESSION['setup_step_no'] = 1;
		$_SESSION['shn_setup_function_list'] = array();
		shn_setup_general_dependencies();
	}else{
		$act = $_REQUEST['act'];
		if($act==null || $act==''){
			session_unset();
			shn_setup_start();
		}else{
			$function_name = 'shn_setup_'.$act;
            //echo $function_name."<br/>";
			$function_name();
		}
	}
}
shn_setup_header();
shn_setup_start();
shn_setup_footer();

