<?php
/**
 * Library containing ajax functions for synchronization servers
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**Function connect to a sahana server and get details
 * @param form_data
 * @return string  - xajax out put
 */

function _shn_server_ajax_connect($url){
    global $global;
    $para="?mod=sync&act=info&stream=text";
    try{
        $xml=file($url.$para);
    } catch (Exception $e) {
    echo 'Caught exception: ',  $e->getMessage(), "\n";
    }
    $connect=$xml;
//access the web service
    if($connect){
        $html="<ul><li>Instance ID:".$xml[0]."</li>
                <li>Owner:".$xml[1]."</li>
                <li>Contact:".$xml[2]."</li>
                </ul>";
        $global['xajax']->addAssign("status", "innerHTML", $html);
    }
    else{
        $html="<b>Can not connect to server...</b><br/>";
        $html.="<form action='#' onSubmit='connect(\"".$url."\");return false;'><input type='submit' value='Retry'></form>";
        $global['xajax']->addAssign("status", "innerHTML", $html);
    }
    //$global['xajax']->addScript('alert("'.$url.'");');
    return $global['xajax']->getXML();
}



?>