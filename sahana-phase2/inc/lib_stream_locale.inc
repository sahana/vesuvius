<?php
/**
 *
 * Streaming Help Library
 *
 * PHP version 4 and 5
 * 
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @author     Prabath Kumarasinghe <prabath321@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

function shn_stream_init()
{
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

function shn_locale_admin_default(){
	//	shn_stream_init();
}

function shn_stream_close(){
	//shn_stream_init();
}


function shn_locale_check_perms(){
	return ALLOWED;
}
	
function _shn_locale_display_errors(){
	// do nothing
	return;	
}


