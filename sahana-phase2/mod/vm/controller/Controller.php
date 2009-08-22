<?php
/**
* Controller interface
*
* The Controller interface is to be implemented by each Controller in the
* module to ensure consistency across the system with regards to controllers.
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

interface Controller
{
	/**
	 * The function that decides what to do and which page to view.
	 *
	 * @param $getvars an associative array, representing the GET variables
	 *                 from the URL
	 * @return void
	 */

	public function controlHandler($getvars);
}

