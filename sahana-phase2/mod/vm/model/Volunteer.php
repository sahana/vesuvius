<?php
/**
* Volunteer object
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
 * Represents the Volunteer object.
 *
 * @var string p_uuid - volunteer's id
 * @var array proj_pos_id - array of project position IDs
 * @var array info - stores the information retrieved fotm the queries to the DB
 */
class Volunteer extends Model {

	public $p_uuid;
	public $img_uuid;
	public $info = array();
	public $proj_pos_id = array();

/**
 * The Volunteer function declares a constructor method that is called on each newly-created volunteer object.
 * If the volunteer object has aready been initialized, it makes a query to the DB to retrieve the information under the specified id and stores it in an array (info). The id of the specific volunteer object is passed to the p_uuid variable.
 *
 * @param string $id
 * @access public
 * @return void
 */
	function Volunteer($id=null) {
		Model::Model();
		if ($id != null)
		{
			$result = $this->dao->getVol($id);
			$this->info = $result;
			$this->p_uuid = $id;

			$this->proj_id = $this->info['proj_id'];
			unset($this->info['proj_id']);
		}
	}

	// the following functions are all just wrappers around the DAO.

/**
 * This function saves in the DB any changes made in the volunteer object. It called the saveVol() function in the DAO class by passing the volunteer object.
 *
 * @access public
 * @param $shn_user 	- (optional, default false) set to true if registering a current Sahana user as a volunteer
 * @return void
 */
	function save($shn_user=false)
	{
		$this->dao->saveVol($this, $shn_user);
	}

/**
 * Calls a function in the DAO class to delete a volunteer
 *
 * @param @id - String
 * @return void
 */
	function delete($id) {
		$this->dao->deleteVolunteer($id);
	}

	function getSkillList() {
		return $this->dao->getSkillList();
	}

	function getPicture($p_uuid=null) {
		return new VMPicture($dao->getPictureID($p_uuid==null?$this->p_uuid:$p_uuid));
	}

	function getPictureID($p_uuid=null) {
		return $this->dao->getPictureID($p_uuid==null?$this->p_uuid:$p_uuid);
	}

	function getVolunteerAssignments() {
		$positions = array();
		foreach($this->dao->listPositions(null, $this->p_uuid) as $thisPosition){
			$positions[] = $thisPosition;
		}
		return $positions;
	}
	
	function getHoursByProject($proj_id) {
		return $this->dao->getVolHoursByProject($this->p_uuid, $proj_id);
	}
}

