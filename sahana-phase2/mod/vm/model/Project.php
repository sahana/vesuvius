<?php
/**
* Project object
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
 * Represents projects
 */
class Project extends Model {
	public $proj_id;
	public $positions; // array of positions
	public $info;

	function Project($proj_id=null) {
		Model::Model();
		if ($proj_id != null) {
			$this->info = $this->dao->getProject($proj_id);
			$this->positions = $this->info['positions'];
			unset($this->info['positions']);
			$this->proj_id = $proj_id;
		}
	}

	/**
	 * This function saves in the DB any changes made in the project object. It calls the saveProject() function in the DAO clas.
	 *
	 * @access public
	 * @return void
	 */
	function save() {
		$this->dao->saveProject($this);
	}
	 
	/**
	 * Retrieve a list of project information
	 *
	 * @access public
	 * @param $p_uuid		- (optional) if specified, only return projects that this volunteer is working on (site managers are handled as well)
	 * @param $mgr			- (optional) if specified, $p_uuid is treated as site manager and only projects he is a site manager for will be returned; if $p_uuid
	 * 							is a site manager but this is false, it will also return any projects that the site manager may just be assigned to
	 * @param $simple		- (optional) if true, the return array only contains the proj_id for each key and the project name for each value
	 * @param $paged		- (optional) if true, the current place in the paging navigation as well as rows per page are taken into account when querying
	 * @return an array of project information arrays, where each key is the project ID and each value
	 * is an array with the following structure:
	 *
	 * 	Array
	 * 	(
	 * 		'name'			=> the name of the project
	 * 		'description'	=> the project's description
	 * 	)
	 */

	function getProjects($p_uuid=null, $mgr=false, $simple=false, $paging=false) {
		return $this->dao->listProjects($p_uuid, $mgr, $simple, $paging);
	}

	/**
	 * A function to delete a project
	 *
	 * @param $id - the value of the project id
	 * @return void
	 */

	function delete($proj_id){
		$this->dao->deleteProject($proj_id);
	}

}


