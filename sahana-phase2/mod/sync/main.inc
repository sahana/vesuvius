<?php

/* $Id: main.inc,v 1.34 2009-08-22 17:17:23 ravithb Exp $ */
/* $Id: main.inc,v 1.34 2009-08-22 17:17:23 ravithb Exp $ */
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

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/3rd/xajax/xajax.inc.php";
include_once 'lib_report.inc';


/**
 * This function defines the menu list.
 *
 * @access public
 * @return void
 */
function shn_sync_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_t("Synchronization Module"));

    shn_mod_menuitem("default",_t("Home"));
//     shn_sub_mod_menuopen(_t("Sahana Servers"));
//     shn_sub_mod_menuitem("sws",_t("Sync with Servers"));
//     shn_sub_mod_menuitem("ads",_t("Add Server"));
//     shn_sub_mod_menuclose();
//     shn_sub_mod_menuopen(_t("Pony Express"));
    shn_mod_menuitem("download",_t("Export Data"));
    shn_mod_menuitem("upload",_t("Import Data"));
//     shn_sub_mod_menuclose();
    shn_mod_menuitem("history",_t("History"));
    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 



/**
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



/** 
 * This function display the Data Download Form
 *
 * @access public
 * @return void
 */
function shn_sync_download()
{
    include_once('handler_download.inc');
}



/**
 * This function display the Upload Form and If a upload file detected it will display its Information
 *
 * @access public
 * @return void
 */
function shn_sync_upload()
{
    include_once('handler_upload.inc');
}



/**
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
    $xajax->printJavascript("res/js");
    echo '<h2 id="head">Synchronize</h2>';
    //echo '<div id="console">'._t('Creating Temp Tables.....').'</div>';
    echo '<div id="console"></div>';
    echo '<script type="text/javascript">loading(\''._t('Creating Temp Tables.....').'\');</script>';
    echo '<script type="text/javascript">xajax_process_file();</script>';
}



/**
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
 * This function out put the download file
 *
 * @access public
 * @return void
 */
function shn_text_sync_download_file()
{
    include_once('handler_download_file.inc');
}



/**
 * This function will stream out sync.js javascript file
 *
 * @access public
 * @return void
 */
function shn_text_sync_js(){
    header("Content-type: text");
    header("Content-Disposition: attachment; filename=sync.js");
    header("Cache-Control: max-age=0, must-revalidate");
    include "sync.js";
}



/**
 * This function will display the history of synchronization
 *
 * @access public
 * @return void
 */
function shn_sync_history(){
    include_once('handler_history.inc');
}


/* following functions are still under development */

function shn_text_sync_info(){
    global $conf;
    echo $conf['base_uuid']."\n";
    echo $conf['root_name']."\n";
    echo $conf['root_email'].", ".$conf['root_tel']."\n";
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
    echo '<h2>'._t('Add Sahana Server').'</h2>';
    shn_form_fopen("ads",null,array('enctype'=>"onSubmit='connect(document.getElementById(\"server_url\").value);return false;'",'style'=>'add'));
    shn_form_fsopen(_t('Add Sahana Server'));
    shn_form_text(_t('Server Url'),'server_url','size="60" id="server_url"',array('value'=>'http://'));
    shn_form_fsclose();
    shn_form_submit(_t('Next >>'));
    shn_form_fclose();
    echo '</div>';
    $xajax->printJavascript("res/js");
    echo '<script type="text/javascript" src="index.php?stream=text&mod=sync&act=js"></script>';
}



function shn_sync_sws(){

}

