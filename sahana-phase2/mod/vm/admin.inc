<?php
/**
* Admin page entry point
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
	 * Handles all administrative functions under the 'Module Config' section
	 * of the 'Admin' module by passing control to the AdminController
	 */

	function shn_vm_adm_default()
	{
		global $global;
		require_once('main.inc');
		shn_vm_load_db();

		$adc = new AdminController();
		$adc->controlHandler($_REQUEST);
	}


