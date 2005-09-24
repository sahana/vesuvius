<?php
/**
* Sahana error library 
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

/**
* @package Error Container
*/

$error_container = array();

/**
* Add Errors to the container
* @param string $error Error Message to display
*/
function add_error($error)
{
	global $error_container;
	array_push($error_container,$error);
}	
function add_error_debug($file,$line,$intNumber,$strmessage)
{
	global $error_container;
	array_push($error_container,array($file,$line,$intNumber,$strmessage));
}
/** 
* Remove Error from the container
* @param integer $index
* @todo Need to implement
*/
function remove_error($index)
{
	
}

/** 
* Clean the error container
*/
function clean_errors()
{
	global $error_container;
	$error_container = NULL;
}

/**
* Return Errors
*/
function return_errors()
{
	global $error_container;
	return $error_container;
}



?>
