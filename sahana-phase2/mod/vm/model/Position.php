<?php

/**
* Position model
* This refers to a specific position in a project.
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

class Position extends PositionType {
	public $title;
	public $pos_id;
	public $proj_id;
	public $proj_name;
	public $ptype_id;
	public $description;
	public $numSlots;
	public $payrate;

	function Position($pos_id=null) {
		if($pos_id != null) {
			Model::Model();
			$p = $this->dao->getPosition($pos_id);
			$this->pos_id			= $pos_id;
			$this->proj_id			= $p['proj_id'];
			$this->ptype_id			= $p['ptype_id'];
			$this->title			= $p['title'];
			$this->proj_id			= $p['proj_id'];
			$this->proj_name			= $p['project_name'];
			$this->description		= $p['description'];
			$this->numSlots			= $p['slots'];
			$this->skill_code		= $p['skill_code'];
			$this->position_title	= $p['ptype_title'];
			$this->payrate          = $p['payrate'];
		}
	}
}


