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
		$this->displayAdminHMenu();

		global $dao;

		switch($getvars['vm_action'])
		{
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
				add_confirmation(_('The Search Registry has been updated.'));
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

				add_confirmation(_('Access control modifications have been saved'));
				$this->displayAdminACL($dao->getAccessRequestsForDisplay());
			break;

			case 'process_clear_cache':
				$this->engine->clear_cache();
				add_confirmation(_('Template cache has been cleared'));
				$this->displayDefaultAdminPage();
			break;

			case 'process_audit_acl':
				global $global;

				//first process any changes if necessary
				if($getvars['process_action'] != '')
				{
					if($getvars['process_action'] == 'add_request')
					{
						$dao->addAccessRequest($getvars['request_act'], $getvars['request_vm_action'], $getvars['request_desc']);
					}
					else if($getvars['process_action'] == 'remove_request')
					{
						$dao->removeAccessRequest($getvars['request_act'], $getvars['request_vm_action']);
					}
					else //($getvars['process_action'] == 'classify_table')
					{
						$dao->classifyTable($getvars['table_to_classify'], $getvars['classification_level']);
					}
					add_confirmation(_('ACL settings have been updated.'));
				}

				$path = $global['approot'].'mod/vm/controller/';

				//an array for all controller files to test with each key being the 'act' URL parameter associated with it
				$files = array('adm_default' => 'AdminController.php', 'project' => 'ProjectController.php', 'volunteer' => 'VolunteerController.php');

				//an array to store all act and vm_action combinations that are not in the database
				$bad_requests = array();
				$current_requests = $dao->getAccessRequests();

				foreach($files as $act => $file_name)
				{
					$handle = fopen($path.$file_name, 'r');
					$contents = fread($handle, filesize($path.$file_name));

					//temporary, should restrict results to within controlHandler() function
					preg_match_all("/case\s+('|\")(\w+)('|\")\s*?:/", $contents, $cases);

					foreach($cases[2] as $vm_action)
					{
						if(isset($current_requests[$act]))
						{
							if(isset($current_requests[$act][$vm_action]))
							{
								unset($current_requests[$act][$vm_action]);
							}
							else
							{
								$bad_requests[] = array('act' => $act, 'vm_action' => $vm_action);
							}
						}
						else
						{
							$bad_requests[] = array('act' => $act, 'vm_action' => $vm_action);
						}
					}

					//ignore default cases that aren't referenced because they will get picked up by the controller's default action
					unset($current_requests[$act]['default']);
					if(empty($current_requests[$act]))
						unset($current_requests[$act]);

					fclose($handle);
				}

				//now look for any unclassified tables/views

				$tables = $dao->getDBTables();
				$unclassified_tables = array();

				foreach($tables as $table)
				{
					if(substr($table, 0, 3) == 'vm_')
					{
						if(!$dao->isClassified($table))
							$unclassified_tables[] = $table;
					}
				}

				//display the information
				$this->displayACLAudit($bad_requests, $current_requests, $unclassified_tables, $dao->getDataClassificationLevels());
			break;

			default:
				$this->displayDefaultAdminPage();
			break;
		}
	}
}

