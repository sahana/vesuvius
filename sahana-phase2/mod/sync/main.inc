<?php
/* $Id: main.inc,v 1.20 2006-11-23 10:18:16 priyanga Exp $ */

/**
 * Main Controller of the Synchronization Module
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
/*check*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/3rd/xajax/xajax.inc.php";
include_once 'lib_report.inc';

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
    shn_sub_mod_menuopen(_("Pony Express"));
    shn_mod_menuitem("download",_("Download Data"));
    shn_mod_menuitem("upload",_("Upload Data"));
    shn_sub_mod_menuclose();
    shn_mod_menuitem("history",_("History"));
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
    echo "<h2>"._('Upload File')."</h2>";
    //Check the file upload and display its messages;
    $_SESSION['sync']['file']="./tmp/".basename($_FILES['file_dump']['name']);
    
    //check for tmp file permision
    if(!is_writable('./tmp')){
        echo _('make sure the tmp folder is writerble')."<br />";
    }
    else if (move_uploaded_file($_FILES['file_dump']['tmp_name'],$_SESSION['sync']['file']))
    {
        include 'handler_upload_file.inc';
        return;
    }

    //Print the error message If an error occord with the Upload File
    if($_GET['up']=='true'){
        echo _('error with the upload file');
    }

    //Upload Data Dump Form
    shn_form_fopen("upload&up=true",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_('Upload Sahana Dump File'));
    shn_form_upload(_('File'),'file_dump');
    shn_form_fsclose();
    shn_form_submit(_('Next'));
    shn_form_fclose();
}
/* }}} */

/**
 * 
 * This function is the main controler for synchronization 
 * It will handell all the ajax calls used in synchronization.
 *
 * @access public
 * @return void
 */
function shn_sync_synchronize(){
    global $global;
    include_once('lib_sync_ajax.inc');
    //$global['xajax']= new xajaxResponse();
    //checking and setting the threshold value
    $_SESSION['threshold']=(isset($_POST['threshold']))?$_POST['threshold']:$_SESSION['threshold'];
    $_SESSION['oed']=(isset($_POST['oed']))?$_POST['oed']:$_SESSION['oed'];
    //function to populate tmp database
    //Ajax controler for synchronization 
    $xajax = new xajax('index.php?mod=sync&act=synchronize&stream=text');
    $xajax->registerFunction('process_file');
    $xajax->registerFunction('start_sync');
    $xajax->registerFunction('get_report');
    $xajax->processRequests();
    $xajax->printJavascript("../3rd/xajax");
    echo '<h2 id="head">Synchronize</h2>';
    echo '<div id="console">'._('Creating Temp Tables.....').'</div>';
    echo '<script type="text/javascript">xajax_process_file();</script>';
}

/**
 * 
 * This function will handell all the ajax calls used in synchronization.
 *
 * @access public
 * @return void
 */
function shn_text_sync_synchronize(){
    global $global;
    require_once('lib_sync_ajax.inc');
    $global['xajax']= new xajaxResponse();
    $xajax = new xajax();
    $xajax->registerFunction('process_file');
    $xajax->registerFunction('start_sync');
    $xajax->registerFunction('get_report');
    $xajax->processRequests();
}
/**
 *
 * This function out put the download file
 *
 * @access public
 * @return void
 */
function shn_text_sync_download_file()
{
    include_once('handler_download_file.inc');
}


function shn_text_sync_ads(){
    global $global;
    require_once('lib_server_ajax.inc');
    $global['xajax']= new xajaxResponse();
    $xajax = new xajax();
    $xajax->registerFunction('_shn_server_ajax_add_server');
    $xajax->registerFunction('_shn_server_ajax_connect');
    $xajax->processRequests();
}

function shn_sync_ads(){
    global $global;
    require_once('lib_server_ajax.inc');
    $xajax = new xajax('index.php?stream=text&mod=sync&act=ads');
    $xajax->registerFunction('_shn_server_ajax_add_server');
    $xajax->registerFunction('_shn_server_ajax_connect');
    
    echo '<div id="console">';
    echo '<h2>'._('Add Sahana Server').'</h2>';
    shn_form_fopen("ads",null,array('enctype'=>"onSubmit='connect(document.getElementById(\"server_url\").value);return false;'",'style'=>'add'));
    shn_form_fsopen(_('Add Sahana Server'));
    shn_form_text(_('Server Url'),'server_url','size="60" id="server_url"',array('value'=>'http://'));
    shn_form_fsclose();
    shn_form_submit(_('Next >>'));
    shn_form_fclose();
    echo '</div>';
    $xajax->printJavascript("../3rd/xajax");
    echo '<script type="text/javascript" src="index.php?stream=text&mod=sync&act=js"></script>';
}

function shn_sync_sws(){

}
/** This function will stream out sync.js javascript file
 * @return void
 */
function shn_text_sync_js(){
    header("Content-type: text");
    header("Content-Disposition: attachment; filename=sync.js");
    header("Cache-Control: max-age=0, must-revalidate");
    include "sync.js";
}

/**
 *
 * This function will display the history of synchronization
 *
 * @access public
 * @return void
 */
function shn_sync_history(){
    global $global;
    echo "<h2>"._('Synchronization History')."</h2>";
    $sql="SELECT * FROM sync_instance";
    $rs=$global['db']->GetAll($sql);
    echo "<div id ='result'>
            <table><thead><td>"._('Instance ID')."</td>
            <td>"._('Owner')."</td>
            <td>"._('Contacts')."</td>
            <td>"._('Last Update')."</td>
            <td>"._('Update Count')."</td>
            </thead>";
    foreach($rs as $row){
        echo "<tr>";
            echo "<td>".$row[0]."</td>";
            echo "<td>".$row[1]."</td>";
            echo "<td>".$row[2]."</td>";
            echo "<td>".$row[4]."</td>";
            echo "<td>".$row[5]."</td>";
        echo "</tr>";
    }
    echo "</table></div>";
}


function shn_text_sync_info(){
    global $conf;
    echo $conf['base_uuid']."\n";
    echo $conf['root_name']."\n";
    echo $conf['root_email'].", ".$conf['root_tel']."\n";
}

function shn_soap_sync_test(){
    return "test";
}
?>
