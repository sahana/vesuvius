<?
/**
 * @name         Locale Stream Library
 * @version      1.0
 * @package      framework
 * @author       Prabath Kumarasinghe <prabath321@gmail.com>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


function shn_stream_init() {
	global $global;
	global $conf;
	$approot = $global['approot'];
	$request  = $_REQUEST['request'];
	if($request=='first'){
		require_once $approot."/mod/admin/lc_first_process_request.inc";
		_find_translated_str();
	}
	else if($request=='second'){
		require_once $approot."/mod/admin/lc_second_process_request.inc";
		_find_str();
	}
	else if($request=='third'){
		require_once $approot."/mod/admin/lc_third_process_request.inc";
		_find_str();
	}
	else if($request=='select'){
		require_once $approot."/mod/admin/lc_select_process_request.inc";
		shn_admin_lc_select_tag();
	}
}



function shn_locale_admin_default() {}



function shn_stream_close() {}



function shn_locale_check_perms() {
	return ALLOWED;
}



function _shn_locale_display_errors() {
	// do nothing
	return;
}


