<?php

/**
* PositionType model
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

class PositionType extends Model {
	public $ptype_id;
	public $position_title;
	public $position_description;
	public $skill_code;

	function PositionType($ptype_id=null) {
		$this->ptype_id = $ptype_id;
		$this->skills = array();
	}

	function setSkill($skill_code) {
		$this->skill_code = $skill_code;
	}

	function getSkill() {
		return $this->skill_code;
	}

	function save() {
		$this->dao->savePositionType($this);
	}

	function delete($pos_id) {
		$this->dao->deletePositionType($pos_id);
	}

	function getPosition($pos_id=null) {
		return $this->dao->getPositionType($pos_id);
	}

}


