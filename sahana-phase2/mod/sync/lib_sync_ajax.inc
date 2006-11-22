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

function process_file(){
    global $global;
    require_once("decompressor.inc");
    switch('xml'){
        case 'xml':
            $xml=require('process_xml_dump.inc');
            if($xml)return $xml;
        break;
        case 'csv':
        break;
        case 'sql':
        break;
        case 'sqlite':
        break;
    }
    $global['xajax']->addAssign('console','innerHTML', _('Combining Data.....'));
    $global['xajax']->addScript('xajax_start_sync();');

    //creating the report object
    $_SESSION['report']=new report();
    $_SESSION['report']=serialize($_SESSION['report']);
    return $global['xajax']->getXML();
}

//function to synchronize
function start_sync($form=array()){
    global $global;
    $global['form_post']=$form;
    $_SESSION['report']=unserialize($_SESSION['report']);
    $_SESSION['report']->set_tables($_SESSION['sync']['tables']);
    $_SESSION['report']->set_all_number();
    include_once('sync_tmp_data.inc');
    $global['xajax']->addAssign('console', 'innerHTML', _('Finish Synchronizing.....'));
    $global['xajax']->addScript('xajax_get_report();');
    $_SESSION['report']=serialize($_SESSION['report']);
    return $global['xajax']->getXML();
}

function get_report(){
    global $global;
    $_SESSION['report']=unserialize($_SESSION['report']);
    $report=$_SESSION['report']->print_report();
    $global['xajax']->addAssign('head','innerHTML', 'Synchronize Report');
    $global['xajax']->addAssign('console','innerHTML', $report);
    return $global['xajax']->getXML();
}
?>