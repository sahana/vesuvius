<?php
/* $Id: main.inc,v 1.9 2006-08-01 08:05:42 priyanga Exp $ */

/**
 * Main Controller of the Synchronization Module
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @author	   J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once('lib_report.inc');
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once($global['approot']."/3rd/xajax/xajax.inc.php");


/* {{{ Main Menu */
/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_sync_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_("Synchonization Module"));

    shn_mod_menuitem("default",_("Home"));
    shn_sub_mod_menuopen(_("Sahana Servers"));
    shn_sub_mod_menuitem("sws",_("Sync with Servers"));
    shn_sub_mod_menuitem("ads",_("Add Server"));
    shn_sub_mod_menuclose();
    shn_mod_menuitem("download",_("Download Data"));
    shn_mod_menuitem("upload",_("Upload Data"));

    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
/* }}} */	


/* {{{ Action: Default (Home Page) */
/**
 * 
 * This function displays the home page of the Synchronization Module
 *
 * @access public
 * @return void
 */
function shn_sync_default()
{
    global $global;
    require($global['approot'].'mod/sync/home.inc');
}
/* }}} */

/* {{{ Action: Default (Home Page) */
/**
 * 
 * This function display the Data Download Form
 *
 * @access public
 * @return void
 */
function shn_sync_download()
{
    include_once('handler_download_data.inc');
}
/* }}} */

/* {{{ Action: Default (Home Page) */
/**
 * 
 * This function display the Upload Form and If a upload file detected it will display its Information
 *
 * @access public
 * @return void
 */
function shn_sync_upload()
{
    global $global;
    echo "<h2>Upload File</h2>";
    //Check the file upload and display its messages;
    $_SESSION['sync']['file']="./tmp/".basename($_FILES['file_dump']['name']);
    if (move_uploaded_file($_FILES['file_dump']['tmp_name'],$_SESSION['sync']['file']))
    {
        include 'handler_upload_file.inc';
        return;
    }

    //Print the error message If an error occord with the Upload File
    if($_GET['up']=='true'){echo 'error with the upload file';}

    //Upload Data Dump Form
    shn_form_fopen("upload&up=true",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_('Upload Sahana Dump File'));
    shn_form_upload(_('File'),"file_dump");
    shn_form_fsclose();
    shn_form_submit(_('Next'));
    shn_form_fclose();
}
/* }}} */

function shn_sync_synchronize(){
    global $global;
    $global['xajax']= new xajaxResponse();
    //function to populate tmp database
    function process_file(){
        global $global;
        switch("xml"){
            case "xml":
                $xml=require("process_xml_dump.inc");
                if($xml)return $xml;
            break;
            case 'csv':
            break;
            case 'sql':
            break;
            case 'sqlite':
            break;
        }
        $global['xajax']->addAssign("console","innerHTML", "Combining Data.....");
        $global['xajax']->addScript("xajax_start_sync();");
        return $global['xajax']->getXML();
    }

    //function to synchronize
    function start_sync(){
        global $global;
        $_SESSION['report']=new report();
        $_SESSION['report']->set_tables($_SESSION['sync']['tables']);
        $_SESSION['report']->set_all_number();
        include_once('sync_tmp_data.inc');
        $global['xajax']->addAssign("console","innerHTML", "Finish Synchronizing.....");
        $global['xajax']->addScript("xajax_get_report();");
        $_SESSION['report']=serialize($_SESSION['report']);
        return $global['xajax']->getXML();
    }

    function get_report(){
        global $global;
        $_SESSION['report']=unserialize($_SESSION['report']);
        $report=$_SESSION['report']->print_report();
        $global['xajax']->addAssign("head","innerHTML", "Synchronize Report");
        $global['xajax']->addAssign("console","innerHTML", $report);
        return $global['xajax']->getXML();
    }

    //Ajax controler for synchronization 
    $xajax = new xajax("stream.php?mod=sync&act=synchronize");
    $xajax->registerFunction("process_file");
    $xajax->registerFunction("start_sync");
    $xajax->registerFunction("get_report");
    $xajax->processRequests();
    $xajax->printJavascript("../3rd/xajax");
    echo "<h2 id='head'>Synchronize</h2>";
    echo "<div id='console'>Creating Temp Tables.....</div>";
    echo "<script type='text/javascript'>xajax_process_file();</script>";
}


/**
 *
 * This function out pu the download file
 *
 * @access public
 * @return void
 */
function shn_sync_download_file()
{
    include_once('handler_download_file.inc');
}

function shn_sync_ads(){

}

function shn_sync_sws(){

}
?>