<?php
/**
* Adds Pure PHP gettext support
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage localization
* @tutorial	  localization.pkg
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * Dummy function to emulate the gettext() function when gettext is not installed
 * This will be replaced by a pure PHP gettext library
 *
 * @param string $string
 * @access public
 * @return string
 */
function gettext($string)
{
    return $string;
}

/**
 * Dummy function to emulate the _t() function when gettext is not installed
 * This will be replaced by a pure PHP gettext library
 *
 * @param mixed $string
 * @access protected
 * @return void
 */
function _t($string)
{
    return $string;
}



