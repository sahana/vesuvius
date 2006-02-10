<?php
/**
* Sahana Localization library
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

include_once $global['approot']."/inc/lib_form.inc";

/**
 * Set the 'locale' value in the 'config' table
 *
 * @param string $locale
 * @access protected
 * @return bool
 */
function _shn_lc_setdblc($locale)
{
	global $global;

	$sql = "INSERT INTO config " .
		   "VALUES('admin', 'locale', '$locale')";

    $sql_up = "UPDATE config SET value = '$locale' " .
              "WHERE module_id = 'admin' " .
              "AND confkey = 'locale'";

	if (!$global['db']->Execute($sql))
	{
		print $global['db']->ErrorMsg();
		return false;
	}
    elseif (!$global['db']->Execute($sql_up))
    {
        print $global['db']->ErrorMsg();
        return false;
    }

	return true;
}

/**
 * Get the 'locale' value from the database
 *
 * @access protected
 * @return mixed
 */
function _shn_lc_getdblc()
{
	global $global;

	$sql = "SELECT value FROM config " .
			"WHERE module_id = 'admin' " .
			"AND confkey = 'locale'";

	$rs = $global['db']->Execute($sql);

	if(!$rs)
	{
		print "Error : " . $global['db']->ErrorMsg();
		return false;
	}
	else if(1>$rs->RecordCount())
	{
		return false;
	}
	else
	{
		$rs = $rs->getArray();
		return $rs[0][0];
	}
}

/**
 * Checks whether the 'locale' value is set or not in the database
 *
 * @access protected
 * @return bool
 */
function _shn_lc_issetdblc()
{
	global $global;

	$res = _shn_lc_getdblc();

	if(!$res)
	{
		return false;
	}
	else
	{
		return true;
	}
}

function _shn_lc_issetcookie()
{
	return isset($_COOKIE['locale']);
}

function _shn_lc_setcookielc($locale)
{
	$_COOKIE['locale'] = $locale;
}

function _shn_lc_setsessionlc($locale)
{
	$_SESSION["locale"] = $locale;
}

function _shn_lc_issetsession()
{
	return isset($_SESSION['locale']);
}

/**
 * Displays the list of available languages
 */
function _shn_lc_lang_list($mode=1)
{
    $lc_list = array(
                    'de_DE'=>_("Sinhala"),
                    'en_US'=>_("English")
                    );
    $locale = $_SESSION['locale'];

    shn_form_fopen("lc_set",null,array('req_message'=>false,'style'=>"language"));

    shn_form_hidden(array('seq'=>'set_locale'));

    shn_form_select($lc_list,"","locale",'onChange=submit(this);',array('value'=>"$locale"));

    shn_form_fclose();
}

?>