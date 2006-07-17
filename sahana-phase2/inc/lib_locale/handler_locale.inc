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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage localization
* @tutorial	  localization.pkg
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

require_once ("lib_locale.inc");

if (function_exists("gettext")) {

    /**
     * Set default locale
     */
    $defaultlocale = $conf['locale'];

    /**
     * Cookie expiration in 24 hours
     */
    $expire_cookie = time() + 3600 * 24;

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
        setcookie ('locale', $getlocale, $expire_cookie);
        $_SESSION['locale'] = $getlocale;
    } else if ( !isset ($_COOKIE['locale']) ) {
        @ setcookie ('locale', $defaultlocale, $expire_cookie);
        $_SESSION['locale'] = $defaultlocale;
    }

    /**
     * Setting gettext parameters
     */
    if ( isset ($_SESSION["locale"]) ) {
        $locale = $_SESSION["locale"];
        $domain = 'sahana';
        #isset($_GET['mod'])?$domain = $_GET['mod']:$domain = "home";

        putenv("LANG=$locale");
        setlocale(LC_ALL, $locale);
        bindtextdomain($domain, $global['approot'] . "res/locale/");
        textdomain($domain);
    }

} else {
    /**
     * If gettext support isn't available
     */
    include_once $global['approot'] . "/inc/lib_locale/lib_gettext.inc";
}

function _lc($string)
{
    if(trim($string) != '')
	   return gettext($string);
    else
        return $string;
}

?>
