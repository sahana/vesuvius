<?php
/**
* Localization library.Handles the I18N and L10N functionality
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
 * get the new language id and refer address
 */
if ( isset($_POST['locale']) ) {
    $getlang = $_POST['locale'];
} else {
    $getlang = $_GET['locale'];
}

/**
 * Set a cookie to value 'locale'.
 * Set the session key 'locale' to the new 'locale' value.
 */
if ( isset ($getlang) ) {
    setcookie ('locale', $getlang, $expire_cookie);
    $_SESSION['locale'] = $getlang;
} else if ( !isset ($_COOKIE['locale']) ) {
    setcookie ('locale', $defaultlocale, $expire_cookie);
    $_SESSION['locale'] = $defaultlocale;
} 

/**
 * including the necessary locale files
 * If the localized version does not exist,
 * the default will be loaded. 
 */
if ( isset ($_SESSION["locale"]) ) { 
    $file_common = $global['approot'] . "res/locale/" . 
                    $_SESSION["locale"] . "_common.inc";
    $file_mod = $global['approot'] . "res/locale/" . $_SESSION["locale"] . 
                 "_" . $global['module'] . ".inc";
    $file_common_default = $global['approot'] . "res/locale/en_US_common.inc";
    $file_mod_default = $global['approot'] . "res/locale/en_US_" . $global['module'] . ".inc";
    
    if ( file_exists($file_common) )
        include_once($file_common);
    else
        include_once($file_common_default);
    
    if ( file_exists($file_mod) )
        include_once($file_mod);
    else
        include_once($file_mod_default);
}

/**
 * TODO:CSS localization
 * Generate the CSS dynamically according to the locale if required
 */
?>
 