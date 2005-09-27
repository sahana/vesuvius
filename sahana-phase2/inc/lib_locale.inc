<?php
/**
* Description for file
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


/*
 * Set default locale
 */
$defaultlocale = $conf['locale'];

/*
 * Cookie expiration in 24 hours
 */
$expire_cookie = time() + 3600 * 24;

/*
 * get the new language id and refer address
 */
if ( isset($_POST['locale']) ) {
    $getlang = $_POST['locale'];
} else {
    $getlang = $_GET['locale'];
}

$_SESSION['locale'] = $_COOKIE['locale'];

/*
 * Set a cookie to value 'lang'.
 * Set the SESSION key 'lang' to the 'lang' value of the cookie if it exits.
 */
if ( isset ($getlang) ) {
    setcookie ('locale', $getlang, $expire_cookie);
    $_SESSION['locale'] = $getlang;
} else if ( !isset ($_COOKIE['locale']) ) {
    setcookie ('locale', $defaultlocale, $expire_cookie);
    $_SESSION['locale'] = $defaultlocale;
} 

/*
 * Destroy session and cookie.
 */ 
if ( isset ($_GET['logoff']) ) {
    session_destroy ();
    if ( $use_cookie == 1 ) 
        setcookie ('locale',$getlang, -3600);
    header ("Location: index.php");
 }

?>
 