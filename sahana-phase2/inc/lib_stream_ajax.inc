<?php
/* $Id: lib_stream_ajax.inc,v 1.6 2009-08-22 17:17:25 ravithb Exp $ */

/**
 *
 * ajax stream library
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_ajax
 * @author     H J P Fonseka <jo@respere.com>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

require_once($global['approot']."/3rd/xajax/xajax.inc.php");

function shn_stream_init()
{
    global $global;
    //create the xajax objects
    $global['xajax'] = new xajax();
    $global['xajax_res']= new xajaxResponse();
    //xajax finction registry
    $global['xajax_functions']=array();
}

function shn_stream_close(){
    global $global;

    //since the security is checked only after the initialization, process the request here
    $module=explode('_',$_REQUEST['xajax']);
    $module=$module[0];
    //for safty strip out any slashes 
    $module  = str_replace('/','_' , $module);

    //include the module xajax library
    $filename = $global['approot'].'/mod/'.$module.'/xajax.inc';
    
    if(file_exists($filename)){
        require_once($filename);
        //registor the available functions
        foreach($global['xajax_functions'] as $function){
            $global['xajax']->registerFunction($function);
        }
    }
    else{
        add_error('Function does not exists');
    }

    //process the xajax request
    $global['xajax']->processRequests();
}

function shn_ajax_check_perms(){
	return ALLOWED;//skip authentication for the moment
}

