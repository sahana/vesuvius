<?php
/**
* Sahana error handler 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/* INC : $Id: handler_errors.inc,v 1.1.1.1 2005-09-24 21:22:51 chamindra Exp $ */
// Make sure the lib_errors is included
require_once('inc/lib_errors.inc');

/**
* Display Errors
* @param bool $exit Exit the script execution 
*/
function display_errors($exit=true)
{
	$errors = return_errors();
	// @todo Please better output and I18N 
	if($exit){
		echo 'Exiting due to the following errors<br>'; 
	}else{
		echo 'Following errors occured<br>';
	}
	foreach ($errors as $error){
		echo $error.'<br>';
	}
	
	if($exit)
		exit(1);
	else
		return 1;
}

?>
