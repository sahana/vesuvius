<?php
/**
* Admin Controller
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

/**
 * A class to handle control for the 'Module Config' section under the 'Admin' module
 */

class AdminController extends AdminView implements Controller
{
	/**
	 * Handles control for all administrative functions
	 */

	public function controlHandler($getvars)
	{
		//first authorize the user
 		$ac = new AccessController($getvars);
		if(!$ac->isAuthorized())
			return;


		View::View();
		$this->displayAdminVMenu();

		global $dao;

		switch($getvars['vm_action'])
		{
			case 'display_modify_skills':
				$this->displayAdminSkills();
			break;

			case 'process_add_skill':
				global $global;
				require_once($global['approot'].'mod/vm/lib/vm_validate.inc');

				if(empty($getvars['skill_desc']) || empty($getvars['skill_code']))
					add_error('Please specify both a skill description and skill code');
				else
				{
					$find = array("/\s*".VM_SKILLS_DELIMETER."\s*/", "/^\s+/", "/\s+$/");
					$replace = array(VM_SKILLS_DELIMETER, '', '');
					$description = preg_replace($find, $replace, $getvars['skill_desc']);

					if(!$dao->addSkill($getvars['skill_code'], $description))
						add_error('The specified skill code already exists. Please choose another');
				}
				$this->displayAdminSkills();
			break;

			case 'process_remove_skill':
				if(!empty($_REQUEST['skills']))
					foreach($_REQUEST['skills'] as $code)
						$dao->removeSkill($code);
				$this->displayAdminSkills();
			break;

			case 'display_acl_situations':
				$this->displayAdminACL($dao->getAccessRequestsForDisplay());
			break;

			case 'display_acl_modify':
				if(empty($getvars['request']))
				{
					add_error(SHN_ERR_VM_NO_REQUEST);
					$this->displayAdminACL($dao->getAccessRequestsForDisplay());
				}
				else
				{
					$split = preg_split("/&/", $getvars['request']);
					$act = $split[0];
					$vm_action = $split[1];

					$this->displayAdminACLModify($act, $vm_action, $dao->getAccessRequestDescription($act, $vm_action), $dao->getSpecificAccessRequestConstraints($act, $vm_action), $dao->getPossibleAccessConstraints(), $dao->getDBTables());
				}
			break;

			case 'process_update_phonetics':
				$dao->updatePhonetics();
				add_confirmation('The Search Registry has been updated.');
				$this->displayDefaultAdminPage();
			break;

			case 'process_acl_modifications':
				$dao->removeConstraints($getvars['acl_act'], $getvars['acl_vm_action']);

				//first update the special constraints

				$possible_constraints = $dao->getPossibleAccessConstraints();
				foreach($possible_constraints as $code => $description)
				{
					if($getvars["constraint_{$code}_req"] == 'on')
					{
						$dao->addConstraint($getvars['acl_act'], $getvars['acl_vm_action'], $code);
					}
				}

				//now update the data classification constraints

				$tables = array();
				foreach($getvars as $name => $value)
				{
					$matches = array();
					if($value == 'on' && preg_match("/table_(\w+|_)_req_(\w)/", $name, $matches))
					{
						//arrange the permissions into the 'crud' format

						$table_name = $matches[1];
						$permission = $matches[2];

						if(!isset($tables[$table_name]))
							$tables[$table_name] = $permission;
						else
						{
							$current_permissions = $tables[$table_name];

							if($permission == 'c')
								$tables[$table_name] = 'c'.$current_permissions;
							else if($permission == 'r')
								if(substr_count($tables[$table_name], 'c') > 0)
									$tables[$table_name] = 'cr'.substr($current_permissions, 1);
								else
									$tables[$table_name] = 'r'.$current_permissions;
							else if($permission == 'u')
								if(substr_count($tables[$table_name], 'd') > 0)
									$tables[$table_name] = substr($current_permissions, 0, strlen($current_permissions) - 1).'ud';
								else
									$tables[$table_name] = $current_permissions.'u';
							else //($permission == 'd')
								$tables[$table_name] = $current_permissions.'d';
						}
					}
				}

				$dao->updateClassificationConstraints($getvars['acl_act'], $getvars['acl_vm_action'], $tables);

				add_confirmation('Access control modifications have been saved');
				$this->displayAdminACL($dao->getAccessRequestsForDisplay());
			break;

			case 'display_approve_managers':
				$this->displaySiteManagerApprovalForm($dao->getSiteManagers(VM_MGR_ALL));
			break;

			case 'process_manager_approval':
				$dao->updateManagerStatus($getvars['mgr_id'], isset($getvars['approve']));
				add_confirmation('Site manager approval information has been updated');
				$this->displaySiteManagerApprovalForm($dao->getSiteManagers(VM_MGR_ALL));
			break;

			case 'process_clear_cache':
				$this->engine->clear_cache();
				add_confirmation('Template cache has been cleared');
				$this->displayDefaultAdminPage();
			break;

			default:
				$this->displayDefaultAdminPage();
			break;
		}
	}
}

?>