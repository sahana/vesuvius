<?php
/**
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

global $global;

//this function is used to print xajax responce
function send_responce(){
    global $global;
    header ("Cache-Control: no-cache, must-revalidate");
    header ("Pragma: no-cache");
    header("Content-type: text/xml");
    echo ($global['xajax']->getXML());
    $_SESSION['report']=serialize($_SESSION['report']);
    exit(0);
}

//setting up the sequence variable if it is not set
$_SESSION['step']=((!isset($_SESSION['step']))||$_SESSION['step']==6)?'1':$_SESSION['step'];

//sequence tracker
switch($_SESSION['step']){
    case '1':
        //###################################
        //get a sample of root records

        //get the number of records

        //
            $con="<div id='formcontainer'>
<form method='POST' action='#' id='loc_form' enctype='multipart/form-data' name='' onsubmit=\"xajax_start_sync(xajax.getFormValues('loc_form'));return false;\">
<fieldset>
<legend>Location Info</legend>
<input type='text' value='t1'  />
</fieldset>
<input type='submit' value='Skip' name='submit' />
<input type='submit' value='Next' name='submit' />
</form></div>";
        //###################################
        $global['xajax']->addAssign("console","innerHTML", $con);
        $_SESSION['step']='2';
        send_responce();
    break;
    case '2':
        $global['form_post']['submit'];
        //If skip is clicked jump out and continue
        if($x=='Skip'){
            $global['xajax']->addScript("xajax_start_sync()");
            $global['xajax']->addAssign("console","innerHTML", 'Skiping Location......');
            $_SESSION['step']='6';
            send_responce();
        }
        $global['xajax']->addAssign("console","innerHTML", $x);
        $global['xajax']->addScript("");
        $_SESSION['step']='3';
        send_responce();
    break;
    case '3':
        
        $global['xajax']->addAssign("console","innerHTML", "three");
        $global['xajax']->addScript("xajax_start_sync();");
        $_SESSION['step']='6';
        send_responce();
    break;
}
?>