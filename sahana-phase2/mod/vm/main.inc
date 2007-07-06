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

//Model
require_once('model/Model.php');
require_once('model/dao.php');
require_once('model/Volunteer.php');
require_once('model/Project.php');
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
 * Loads the global database object.
 * @access public
 * @return void
 */
function shn_vm_load_db() {
	error_reporting(E_ALL ^ E_NOTICE);
    global $global;
    $db = $global['db'];

	global $dao;
    $dao = new DAO($db);
}

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

    shn_display_xhtml_head(
    array
    (
		"1" => '<script type="text/javascript" src="'.TREE_JS_PATH.'tree.js"></script>',
		"2" => '<script type="text/javascript" src="'.TREE_JS_PATH.'node.js"></script>',
		"3" => '<script type="text/javascript" src="'.TREE_JS_PATH.'checkbox_node.js"></script>'
	));
}