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
	if (!$global['db']->Execute($sql))
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
?>

