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
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 


/**
 * Dummy function to emulate the gettext function when gettext is not installed
 * 
 * @param mixed $string 
 * @access public
 * @return void
 */
function gettext($string) {
    return $string;
}
 
/**
 * _ 
 * 
 * @param mixed $string 
 * @access protected
 * @return void
 */
function _($string) {
    return $string;
}
?>
