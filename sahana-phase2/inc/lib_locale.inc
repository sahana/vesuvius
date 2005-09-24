<?php
/**
* localization helper functions
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

/*
 * Created on Sep 14, 2005
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */

// Find the base location of the Sahana installation
if(!defined('APPROOT')) define('APPROOT',realpath(dirname(__FILE__)).'/');
define ('__DEFAULT_LANGUAGE__', "en_US");

// start the session
session_start ();

// Set the default language.
$defaultlanguage = __DEFAULT_LANGUAGE__;

// Set to 1 if you want to use a cookie.
$use_cookie = 1;

// Cookie expiration in 24 hours
$expire_cookie = time() + 3600 * 24;

// Added support for using post to get the lang value
if ( isset($_POST['lang']) )
	$getlang = $_POST['lang'];
else
	$getlang = $_GET['lang'];

// Set a cookie to the GET arg 'lang' if it exists.
// Set the SESSION key 'lang' to the 'lang' value of the cookie if it exits.
if ( $use_cookie == 1 ) {
	if ( isset ($getlang) ) {
		setcookie ('lang', $getlang, $expire_cookie);
	}
	else if ( !isset ($_COOKIE['lang']) ) {
		setcookie ('lang', $defaultlanguage, $expire_cookie);
	}
	
	if ( isset ($_COOKIE['lang']) ) {
		$_SESSION['lang'] = $_COOKIE['lang'];
	}
	//header ("Location: http://" . $_SERVER['HTTP_HOST'] . "/");
}

// Destroy session and cookie.
if ( isset ($_GET['logoff']) ) {
	session_destroy ();
	if ( $use_cookie == 1 ) { setcookie ('lang',$getlang, -3600); }
	//header ("Location: http://" . $_SERVER['HTTP_HOST'] . "/" . $PHP_SELF);
}


// Return the list of locale files
function get_lang_list()
{
	$dir    = $APPROOT.'res/locale';
	$file_list = scandir($dir);
	
	foreach ($file_list as $file)
	{
		if (strstr($file, 'inc'))
			$lang_list[] = $file; 
	}
	return $lang_list;
}


?>
 
