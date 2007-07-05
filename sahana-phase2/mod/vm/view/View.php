<?php

/**
* A super class with references to the model and the template engine
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
 * View.php - define the View class.
 *
 * The View class is a superclass of all views in the entire module. Mainly, it takes care of setting up
 * the PHP Template library.
 */


class View
{

	/**
	 * Define instance variables
	 */

	protected $model;		//a reference to the particular model being used (Volunteer, Project, etc.)
	protected $engine;		//a reference to the Template Engine Object for later use when displaying

	/**
	 * The View constructor, which simply creates a smarty object and sets the appropriate directories
	 * for a Smarty object, so that all subclasses can use this object to display
	 * PHP Templates.
	 *
	 * @param $model a reference to the model used in the particular View.
	 */

	function View(&$model=null) {
		global $global;
		$this->model = &$model;
		$this->engine = new Whiz(SHN_VM_ENGINE_CACHE_DIR, SHN_VM_ENGINE_TEMPLATE_DIR);
	}

	function displayConfirmation($msg) {
		echo "<div class=\"confirmation message\">$msg</div>\n";
	}
}

?>
