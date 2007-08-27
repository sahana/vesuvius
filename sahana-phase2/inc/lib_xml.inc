<?php
/* $Id: lib_xml.inc,v 1.1 2007-08-27 02:55:40 ravids Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_soap
 * @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
 

function findAttribute($object, $attribute) {
  foreach($object->attributes() as $a => $b) {
    if ($a == $attribute) {
      $return = $b;
    }
  }
  if($return) {
    return (string)$return;
  }
}

 
?>