<?php

/**
* Main include file for Sahana
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

error_reporting(E_ALL ^ E_NOTICE);
ini_set("display_errors", "1");

// include the sahana libraries.
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once($global['approot'].'/inc/lib_log.inc');
include_once($global['approot'].'/inc/lib_location.inc');

// include our own classes.
require_once('lib/Constants.php');
require_once('lib/vm_validate.inc');

//Model
require_once('model/Model.php');
require_once('model/dao.php');
require_once('model/Volunteer.php');
require_once('model/Project.php');
require_once('model/PositionType.php');
require_once('model/Position.php');
require_once('model/VMPicture.php');

//View
require_once('whiz/Whiz.php');
require_once('view/View.php');
require_once('view/AdminView.php');
require_once('view/VolunteerView.php');
require_once('view/ProjectView.php');

//Controller
require_once('controller/AccessController.php');
require_once('controller/Controller.php');
require_once('controller/AdminController.php');
require_once('controller/VolunteerController.php');
require_once('controller/ProjectController.php');

// include the function to display the main menu
require_once('menu.inc');


require_once(TREE_DIR.'tree.inc');
require_once(TREE_DIR.'node.inc');

/**
 * Updates the Sahana Breadcrumbs by adding the current page to the end of
 * the list and moving the list down
 */

function shn_vm_update_breadcrumbs() {
	global $dao;
	$act = $_GET['act'];
	$vm_action = $_GET['vm_action'];
	if($act == "" || $act == "default") {
		$act = "volunteer";
	}
	if($vm_action == "") {
		$vm_action = "default";
	}
	$name = $dao->getAccessRequestName($act, $vm_action);
	if($name != null) {
		$parts = explode("-", $name);
		array_shift($parts);
		$name = implode($parts);
		$new_entry = array($name, "mod=vm&act=$act&vm_action=$vm_action", "vm");

		if(count($_SESSION['shn_breadcrumb']) < 3) {
			array_push($_SESSION['shn_breadcrumb'], $new_entry);
		} else {
			array_shift($_SESSION['shn_breadcrumb']);
			array_push($_SESSION['shn_breadcrumb'], $new_entry);
		}
	}
}

/**
 * Loads the global database object.
 * @access public
 * @return void
 */
function shn_vm_load_db() {
	//only load the DAO if it has not yet been loaded
	if(!defined('VM_DAO_LOADED')) {
		error_reporting(E_ALL ^ E_NOTICE);
	    global $global;
	    $db = $global['db'];

		global $dao;
	    $dao = new DAO($db);
	    define('VM_DAO_LOADED', true);
	}
}

shn_vm_load_db();
shn_vm_update_breadcrumbs();

/**
 * Default VM function, calls the appropriate controller's controlHandler() function
 * @access public
 * @return void
 */

function shn_vm_default()
{
	if($_GET['act'] == 'project' && $_SESSION['logged_in'])
	{
		$controller = new ProjectController();
		$controller->controlHandler($_REQUEST);
	}
	else
	{
		$controller = new VolunteerController();

		if(!$_SESSION['logged_in'] && $_GET['vm_action'] != 'process_add')
		{
			/*
			 * If the user is not logged in and is not processing his own volunteer
			 * registration, display the volunteer registration form
			 */

			$controller->controlHandler(array_merge($_REQUEST, array('vm_action' => 'display_add')));
		}
		else
		{
			$controller->controlHandler($_REQUEST);
		}
	}
}

/**
 * Display additional elements in the HTML head
 */

function shn_vm_html_head()
{
	global $global;
	require_once($global['approot'].'inc/lib_xhtml.inc');

    shn_display_xhtml_head(array(
		"1" => '<script type="text/javascript" src="'.TREE_JS_PATH.'tree.js"></script>',
		"2" => '<script type="text/javascript" src="'.TREE_JS_PATH.'node.js"></script>',
		"3" => '<script type="text/javascript" src="'.TREE_JS_PATH.'checkbox_node.js"></script>'
	));
}

function shn_vm_credits() {
	echo nl2br(file_get_contents("../mod/vm/README"));
}


/**
 * Load sample data into db.
 */
/*
function shn_vm_load_sample() {
	set_time_limit(0);
	global $dao;
	for($volNum = 1; $volNum <= 51; $volNum++) {
		$p_uuid = shn_create_uuid();
		$name = 'vol'.$volNum;
		shn_auth_add_user($name, $name, 'test', ANONYMOUS, $p_uuid);
		$names = preg_split("/\s+/", $name);
        foreach($names as $single_name) {
            $dao->execute("INSERT INTO phonetic_word VALUES('" . soundex($single_name) . "', '" . metaphone($single_name) . "', '$p_uuid')");
        }
		$dao->execute("insert into person_uuid (p_uuid, full_name) values ('".$p_uuid."', '".$name."')");
		$dao->execute("insert into person_details (p_uuid, gender) values ('".$p_uuid."', '".((round(rand()) == 1) ? 'F' : 'M')."')");
		$dao->execute("insert into vm_vol_details (p_uuid,date_avail_start,date_avail_end) values ('$p_uuid', '2008-01-01', '2009-01-01')");
		$skills = array('ANI1', 'ANI2', 'VEH1', 'WAR1');
		foreach($skills as $skill) {
			$dao->execute("INSERT INTO vm_vol_skills (p_uuid, opt_skill_code) VALUES('$p_uuid', '$skill')");
		}
		echo "added $name <br />";
	}
}
*/

