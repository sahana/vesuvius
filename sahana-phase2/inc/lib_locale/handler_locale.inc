<?php
/**
* Sahana Localization library,Handles the I18N and L10N functionality
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @author     Prabath Kumarasinghe <prabath@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage localization
* @tutorial	  localization.pkg
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
require_once ("lib_locale.inc");
require_once("gettext.inc");

/**
     * Set default locale
*/
define(DEFAULT_LOCALE, $conf['locale']);

// many institutions do not allow public websites they host to store persistent cookies, 
// therefore, we will only make them persist as long as the session itself
/* $expire_cookie = time() + z; */

/**
     * Set the session key 'locale' with the value 'locale'
     * in the cookie
     */
    if ( isset($_COOKIE['locale']) )
        $_SESSION['locale'] = $_COOKIE['locale'];

    /**
     * get the new locale id
     */
    if ( isset($_POST['locale']) ) {
        $getlocale = $_POST['locale'];
    } else {
        $getlocale = $_GET['locale'];
    }

    /**
     * Set a cookie to value 'locale'.
     * Set the session key 'locale' to the new 'locale' value.
     */
    if ( isset ($getlocale) ) {
        setcookie ('locale', $getlocale); //, $expire_cookie); ~~ we are now setting the cookie to expire with the session
        $_SESSION['locale'] = $getlocale;
    } else if ( !isset ($_COOKIE['locale']) ) {
        setcookie ('locale', $defaultlocale); //, $expire_cookie); ~~ we are now setting the cookie to expire with the session
        $_SESSION['locale'] = $defaultlocale;
    }

    /**
     * Setting gettext parameters
     */
    if ( isset ($_SESSION["locale"]) ) {
        $encoding = 'UTF-8';        
		$locale = (isset($_SESSION["locale"]))? $_SESSION["locale"] : DEFAULT_LOCALE;
		// gettext setup
		T_setlocale(LC_ALL, $locale);
		// Set the text domain as 'messages'
		$domain = 'sahana';
		$path = $global['approot'] . "res/locale";
		T_bindtextdomain($domain, $path);
		T_bind_textdomain_codeset($domain, $encoding);
		T_textdomain($domain);
    }



function _lc($string)
{
    if(trim($string) != '')
	   return gettext($string);
    else
        return $string;
}


