<?
/**
 * @name         Locale Handler
 * @version      11
 * @package      framework
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @author       Prabath Kumarasinghe <prabath@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0818
 */

require_once("lib_locale.inc");
require_once("gettext.inc");

// Set default locale
if(isset($conf)){define("DEFAULT_LOCALE", $conf['locale']);}
else {define("DEFAULT_LOCALE","en_US");}

// many institutions do not allow public websites they host to store persistent cookies,
// therefore, we will only make them persist as long as the session itself
// so all setcookie() calls do not have an expiration parameter

// Set the session key 'locale' with the value 'locale' in the cookie
if(isset($_COOKIE['locale'])) {
	$_SESSION['locale'] = $_COOKIE['locale'];
}

// get the new locale id
if(isset($_REQUEST['locale'])) {
	$getlocale = $_REQUEST['locale'];
} else {
	$getlocale = null;
}

// Set a cookie to value 'locale'. Set the session key 'locale' to the new 'locale' value.
if(isset($getlocale)) {
	setcookie ('locale', $getlocale);
	$_SESSION['locale'] = $getlocale;
} elseif(!isset($_COOKIE['locale'])) {
	setcookie ('locale', DEFAULT_LOCALE);
	$_SESSION['locale'] = DEFAULT_LOCALE;
}

// Setting gettext parameters
//if(isset($_SESSION["locale"])) {
	$encoding = 'UTF-8';
	$locale = (isset($_SESSION["locale"])) ? $_SESSION["locale"] : DEFAULT_LOCALE;

	// gettext setup
	T_setlocale(LC_ALL, $locale);

	// Set the text domain as 'messages'
	$domain = 'sahana';
	$path = $global['approot'] . "res/locale";
	T_bindtextdomain($domain, $path);
	T_bind_textdomain_codeset($domain, $encoding);
	T_textdomain($domain);
//}



function _lc($string) {
	if(trim($string) != '') {
		return gettext($string);
	}
	else {
		return $string;
	}
}


