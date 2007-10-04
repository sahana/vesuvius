<?php
/* $Id: lib_stream_ajax.inc,v 1.3 2007-10-04 07:03:02 ravids Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_ajax
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

require_once($global['approot']."/3rd/xajax/xajax.inc.php");

$global['xajax'] = new xajax($conf['base_url'].'stream.php?stream_type=ajax&mod='.$global['module'].'&act='.$global['action']);

#$global['xajax']->debugOn();
#$global['xajax']->setLogFile($global['approot'].'logs/xjax_err.log');

function shn_stream_init($filename)
{
    global $global;
    
    if(! $filename)
        $filename = $global['approot'].'/mod/'.$global['module'].'ajax.inc';

    //open the file and register functions
    $content = file($filename);
    
    foreach($content as $line){
       if(preg_match('/function (.*)\(/',$line,$matches))
            $global['xajax']->registerFunction($matches[1]); 
            
    }

    //Print the javascript src
}

function shn_stream_close($function,$output)
{
    global $global;
    
    $global['xajax']->printJavascript();
}

function shn_ajax_url_append($str)
{
    global $global;
    $global['xajax']->setRequestURI($conf['base_url'].'stream.php?stream_type=ajax&mod='.$global['module'].'&act=' .$global['action'].'&'.$str);
}

function shn_ajax_set_act($act)
{
    global $global;
    $global['xajax']->setRequestURI($conf['base_url'].'stream.php?stream_type=ajax&mod='.$global['module'].'&act='.$act);
}
function shn_ajax_url($url)
{
    global $global;
    $global['xajax']->setRequestURI($url);
}

function shn_ajax_check_perms(){
	return ALLOWED;//skip authentication for the moment
}
?>
