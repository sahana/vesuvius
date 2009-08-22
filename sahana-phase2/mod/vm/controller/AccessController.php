<?php
/**
* Access Controller
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

global $global;
require_once($global['approot'].'inc/lib_security/lib_acl.inc');
require_once($global['approot'].'inc/lib_errors.inc');

/**
 * A class to use to verify that the current logged in user has the correct permissions to view a page.
 */


class AccessController
{
	public	$getvars;	//the $_REQUEST parameters
	public	$access;	//a multi-dimensional array storing all access constraints for the entire module

	/**
	 * Constructs an AccessController Object
	 *
	 * @param $getvars	- (optional) the default parameters to check access against
	 */

	public function __construct($getvars=null)
	{
		global $dao;

		//store the $getvars

		$this->getvars = $getvars;

		//store all access constraint information

		$access = $dao->getAccessRequestConstraints();
		$access['default'] = $access['volunteer'];
		$this->access = $access;
	}

	/**
	 * Validates that the current user is authorized to view the current page, using
	 * the access guidelines outlined in this class's private $access.
	 *
	 * If access is denied, an error message is automatically displayed.
	 *
	 * @access public
	 * @param $error_msg		- true to output an error message if not authorized, false to suppress it
	 * @param $new_getvars	- (optional), if specified, these getvars will be checked for authorization
	 * 							instead of the default ones
	 * @return true if the user is authorized, false if not
	 */

	public function isAuthorized($error_msg=true, $new_getvars=null)
	{
		global $dao;

		if(is_null($new_getvars))
			$auth_vars = $this->getvars;
		else
			$auth_vars = $new_getvars;

		//store a variable to represent if 'act' is set and present in our list

		if(isset($auth_vars['act']))
		{
			$act_found = in_array($auth_vars['act'], array_keys($this->access));
		}
		else
		{
			$act_found = false;
		}

		//store a variable to represent if 'vm_action' is set and present in our list

		if(isset($auth_vars['vm_action']) && $act_found)
		{
			$vm_act_found = in_array($auth_vars['vm_action'], array_keys($this->access[$auth_vars['act']]));
		}
		else
		{
			$vm_act_found = false;
		}

		/*
		 * Store the appropriate 'act' and 'vm_action' into $act and $vm_act respectively. If $vm_act is not found, use
		 * 'default' for it, and if $act is not found, use 'volunteer' for $act and 'default' for $vm_action
		 */


		if($act_found && $vm_act_found)
		{
			$act = $auth_vars['act'];
			$vm_action = $auth_vars['vm_action'];
		}
		else if($act_found)
		{
			$act = $auth_vars['act'];
			$vm_action = 'default';
		}
		else
		{
			$act = 'volunteer';
			$vm_action = 'default';
		}

		//assume the user passes to begin with

		$passed_sahana_acl = true;
		$passed_vm_acl = true;

		//check for database information access

		if(is_array($this->access[$act][$vm_action]['tables']))
		{
			if(shn_acl_is_enabled()==true){ ///check for authorization only if ACL is enabled
				$passed_sahana_acl = $this->dataAccessIsAuthorized($this->access[$act][$vm_action]['tables'], false);
			}else{
				$passed_sahana_acl=true;
			}
		}

		//check for possible constraints/overrides imposed through the 'extra' array

		if(is_array($this->access[$act][$vm_action]['extra']))
		{
			foreach($this->access[$act][$vm_action]['extra'] as $value)
			{
				//user must be logged in

				if($value == 'req_login')
					$passed_vm_acl = $passed_vm_acl && $_SESSION['logged_in'];

				//user must be a volunteer

				if($value == 'req_volunteer')
					$passed_vm_acl = $passed_vm_acl && $dao->isVolunteer($_SESSION['user_id']);

				//user must be an approved site manager

				if($value == 'req_manager')
					$passed_vm_acl = $passed_vm_acl && $dao->isSiteManager($_SESSION['user_id']);

				//override if user is an approved site manager

				if($value == 'ovr_manager')
					if($dao->isSiteManager($_SESSION['user_id']))
						return true;

				//override if user is requesting access to his own information

				if($value == 'ovr_my_info')
					if($auth_vars['p_uuid'] == $_SESSION['user_id'])
						return true;

				//override if user is requesting access to one of his own project's information

				if($value == 'ovr_my_proj')
					if(in_array($auth_vars['proj_id'], array_keys($dao->listProjects($_SESSION['user_id']))))
						return true;

				//override if the user is requesting access to one of the projects he is a site manager for

				if($value == 'ovr_mgr_proj')
				{
					if($dao->isSiteManagerForProject($_SESSION['user_id'], $auth_vars['proj_id']))
						return true;
				}

				//override if the user has the Main Operations handler role

				if($value == 'ovr_mainops')
					if(in_array(MAINOPS, array_keys(_shn_acl_get_roles($_SESSION['user_id']))))
						return true;

				//override if the user is a site manager who is requesting access to one of his projects' positions' information (active or retired)

				if($value == 'ovr_mgr_pos')
					if($dao->isPositionUnderManager($auth_vars['pos_id'], $_SESSION['user_id']))
						return true;
			}
		}

		if($passed_vm_acl && $passed_sahana_acl)
		{
			return true;
		}
		else
		{
			if($error_msg)
				shn_error_display_restricted_access();

			return false;
		}

	}

	/**
	 * A function to check Sahana's data classification records. This is necessary
	 * because presently there is no way to check authorization and suppress output.
	 * To suppress Sahana's default message (if desired), this function uses output buffering.
	 *
	 * @param $tables		- an array of tables to request access to
	 * @param $error_msg		- true to output the error message, false to suppress it
	 * @return true if authorized, false if not
	 */

	public function dataAccessIsAuthorized($tables, $error_msg=true)
	{
		if(!$error_msg)
			ob_start();

		$result = shn_acl_check_table_only_perms($tables) == ALLOWED;

		if(!$error_msg)
			ob_end_clean();

		return $result;
	}

	/**
	 * A function to add a menu item based on these access control settings. If the current
	 * user does not have access to the page, the menu item is not displayed. The default
	 * $getvars stored during construction are used during authorization.
	 *
	 * $text		- the text to display for the menu item
	 * $getvars		- the $_GET parameters to check for authorization (as an array, with each key as a parameter name and each value as a parameter value)
	 * $submenu		- (optional) true to create a submenu item, defaults to false
	 * $extra_vars	- (optional) any extra $_GET parameters to pass to the URL for this menu item
	 */

	public function addMenuItem($text, $getvars, $submenu=false)
	{
		global $global;
		if($this->isAuthorized(false, $getvars))
		{
			$url_params = '';
			foreach($getvars as $key => $value)
			{
				if($key == 'act')
					$url_params .= "$value";
				else
					$url_params .= "&amp;$key=$value";
			}

			if($submenu)
				shn_sub_mod_menuitem($url_params, _($text), $global['module']);
			else
				shn_mod_menuitem($url_params, _($text), $global['module']);
		}
	}

	/**
	 * A simple function to build the URL GET parameters to pass to addMenuItem()
	 *
	 * @param $act			- the 'act'
	 * @param $vm_action		- the 'vm_action'
	 * @param $extra_vars	- any extra parameters (as an array, with each key as a parameter name and each value as a parameter value)
	 * @return an array of $getvars that can be fed into addMenuItem()
	 */

	public function buildURLParams($act, $vm_action, $extra_vars=array())
	{
		$url_params = array('act' => $act, 'vm_action' => $vm_action);

		foreach($extra_vars as $key => $value)
			$url_params[$key] = $value;

		return $url_params;
	}
}

