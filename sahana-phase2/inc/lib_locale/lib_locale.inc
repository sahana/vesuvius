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


/**
 * _shn_lc_setdblc 
 * 
 * @param mixed $locale 
 * @access protected
 * @return void
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
 * _shn_lc_getdblc 
 * 
 * @access protected
 * @return void
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
 * _shn_lc_issetdblc 
 * 
 * @access protected
 * @return void
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

