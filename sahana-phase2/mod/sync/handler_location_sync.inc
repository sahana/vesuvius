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

function get_select_html($name,$arr){
    $html="<select name='".$name."'>";
    foreach($arr as $rec)$html.="<option value=\"".$rec[0]."\">".$rec[1]."</option>";
    $html.="</select>";
    return $html;
}

//setting up the sequence variable if it is not set
$_SESSION['step']=((!isset($_SESSION['step']))||$_SESSION['step']==6)?'1':$_SESSION['step'];

//sequence tracker
switch($_SESSION['step']){
    case '1':
        //###################################
        //get the number of records
        $sql="SELECT count(*) FROM tmp_location WHERE opt_location_type='1'";
        $count=$global['db']->GetOne($sql);
        //
            $con="<div id='formcontainer'>
<form method='POST' action='#' id='loc_form' enctype='multipart/form-data' name='' onsubmit=\"return false;\">
<fieldset>
<legend>Location Info</legend>
<strong>there are <em>".$count."</em> root level locations in imported data. Do you want to merge data manually.<strong>
</fieldset>
<input type='submit' value='Skip' onclick=\"xajax_start_sync('skip');\"/>
<input type='submit' value='Next' onclick=\"xajax_start_sync('next');\"/>
</form></div>";
        //###################################
        $global['xajax']->addAssign("console","innerHTML", $con);
        $_SESSION['step']='2';
        send_responce();
    break;
    case '2':
        $x=$global['form_post'];
        //If skip is clicked jump out and continue
        if($x=='skip'){
            $global['xajax']->addScript("xajax_start_sync()");
            $global['xajax']->addAssign("console","innerHTML", 'Skiping Location......');
            $_SESSION['step']='exit';
            send_responce();
        }
        //get sample 
        $sample=$global['db']->GetAll('SELECT name FROM tmp_location WHERE opt_location_type=1 LIMIT 5');
        foreach($sample as $loc) $sam.=" ".$loc['name'].", ";
        //field option
        $arr=$global['db']->GetAll("SELECT option_code , option_description FROM field_options WHERE field_name='opt_location_type' ORDER BY option_code");

        $arr2=$global['db']->GetAll("SELECT DISTINCT opt_location_type,opt_location_type FROM tmp_location");
//################################################
$con="<div id='formcontainer'>
<form method='POST' action='#' id='loc_form' enctype='multipart/form-data' name='' onsubmit=\"xajax_start_sync(xajax.getFormValues('loc_form'));return false;\">
<fieldset>
<legend>Root Location Type</legend><center>
<strong>Sample of the imported root locations are given bellow</strong><br />
(".$sam.")<br />
<strong>Specify which level does this root locations belongs to.</strong><br />
<strong>Current Level ".get_select_html("current",$arr)." is equal to ".get_select_html("import",$arr2)." imported level<strong>
</center>
</fieldset>
<input type='submit' value='Next' name='submit' />
</form></div>";
//################################################
        $global['xajax']->addAssign("console","innerHTML",$con);
        $_SESSION['step']='3';
        send_responce();
    break;
    case '3':
        $impo=$global['form_post']['import'];
        $curr=$global['form_post']['current'];
        //getting equal locations
        $arr=$global['db']->GetAll("SELECT loc_uuid,name FROM location WHERE opt_location_type='".$curr."'");

        //loop and change the opt_location_type
        $val=(int)$curr-1;
        $_SESSION['opt_location_type']=$val;
        $sql="UPDATE tmp_location SET opt_location_type=opt_location_type+".$val;
        $global['db']->Execute($sql);

        $_SESSION['sync']['loc']['limit_index']=1;
        //get 1 location
        $sql="SELECT loc_uuid, name, description, iso_code FROM tmp_location WHERE opt_location_type='".++$val."' LIMIT   0 , 1";
        $rec=$global['db']->GetAll($sql);
//################################################
$con="<div id='formcontainer'>
<form method='POST' action='#' id='loc_form' enctype='multipart/form-data' name='' onsubmit=\"xajax_start_sync(xajax.getFormValues('loc_form'));return false;\">
<fieldset>
<legend>Set the location root</legend>
<input type='hidden' value='".$rec[0]['loc_uuid']."' name='loc_uuid' id='loc_uuid'>
<center><strong>Location <input type='text' size='10' id='loc_name' value='".$rec[0]['name']."' /> is a child of 
location ".get_select_html("loc_pare",$arr)."</strong></center>
</fieldset>
<input type='submit' value='Next' name='submit' />
</form></div>";
//################################################
        $global['xajax']->addAssign("console","innerHTML", $con);
        $_SESSION['step']='4';
        send_responce();
    break;
    case '4':
        $impo=$global['form_post']['loc_uuid'];
        $curr=$global['form_post']['loc_pare'];
        $sql="UPDATE tmp_location SET parent_id='".$curr."' WHERE loc_uuid='".$impo."';";
        $global['db']->Execute($sql);

        $sql="SELECT loc_uuid, name, description, iso_code FROM tmp_location WHERE opt_location_type='".++$_SESSION['opt_location_type']."' LIMIT ".(int)$_SESSION['sync']['loc']['limit_index']++." , 1";
        $rec=$global['db']->GetAll($sql);
        if(count($rec)==0){
            $global['xajax']->addAssign("console","innerHTML", "Finish Location Sync.....");
            $global['xajax']->addScript("xajax_start_sync();");
            $_SESSION['step']='exit';
            send_responce();
        }
        $global['xajax']->addAssign('loc_uuid','value',$rec[0][0]);
        $global['xajax']->addAssign('loc_name','value',$rec[0][1]);
        send_responce();
    break;
    case 'skip':
        $global['xajax']->addAssign("console","innerHTML", "Skiping Location Sync.....");
    break;
    case 'exit':
        $global['xajax']->addAssign("console","innerHTML", "Mergeing Other Data.....");
    break;
}
        foreach($_SESSION['sync']['tables'] as $table){
            shn_sync_merge($table);
        }
        $global['xajax']->addScript("xajax_get_report();");
        $_SESSION['step']='6';
        send_responce();
