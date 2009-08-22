<?php
/* $Id: lib_stream_soap.inc,v 1.17 2009-08-22 17:17:25 ravithb Exp $ */

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
 
global $global;
require_once ($global['approot'].'inc/lib_ws/lib_stream_soap.inc');

function shn_soap_check_perms(){
	return ALLOWED;//skip authentication at this step since , authentication is performed at the last step. i.e at method
				  // invocation level. otherwise cannot let WSDL be visible to any one and still protect the methods.
}

function _shn_soap_display_errors(){
    // do nothing
    return;
}
