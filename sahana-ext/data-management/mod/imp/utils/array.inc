<?php
/* $Id: array.inc,v 1.1 2006-03-20 11:26:11 janakawicks Exp $ */


/**
 * Data Import upload file 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**
 * Simple wrapper class to add a few essential core functions to
 * arrays in PHP
 *
 * 
 */

class imp_Utils_Array {

    /**
     * if the key exists in the list returns the associated value
     *
     * @access public
     *
     * @param array  $list  the array to be searched
     * @param string $key   the key value
     * 
     * @return value if exists else null
     * @static
     * @access public
     *
     */
    static function value( $key, &$list, $default = null ) {
        if ( is_array( $list ) ) {
            return array_key_exists( $key, $list ) ? $list[$key] : $default;
        }
        return $default;
    }

    /**
     * if the value exists in the list returns the associated key
     *
     * @access public
     *
     * @param list  the array to be searched
     * @param value the search value
     * 
     * @return key if exists else null
     * @static
     * @access public
     *
     */
    static function key( $value, &$list ) {
        if ( is_array( $list ) ) {
            $key = array_search( $value, $list );
            return $key ? $key : null;
        }
        return null;
    }

}

?>
