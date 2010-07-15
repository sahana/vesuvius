<?php
/**
 * REG Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module reg
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * This is the test function to get SOAP working
 * @access public
 * @param y
 * @param x
 * @return array
 */
function shn_reg_test($x, $y) {
	$list = array();
	$list[] = array('x'=>$x, 'y'=>$y);
	return $list;
}