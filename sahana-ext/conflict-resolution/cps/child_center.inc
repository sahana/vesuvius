<?php
/* $Id; */

/**Child library for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');
require_once ($global['approot'].'conf/config.inc'); 

//print child center 
function _shn_cps_print(){
global $conf;
$server= $conf['servername'] ;
$center=$_POST['center'];
$centername=$_POST['centername'];
$date=$_POST['date'];
$filed_by=$_POST['filed_by'];
$func=$_POST['func'];
$text="1=$center&2=$centername&3=$date&4=$filed_by&5=$func";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_center_data_excel.php?<?php print $text?>">View in Excel to Print</a>
<?php
}

//add child center
function _shn_cps_cadd_start($errors=false){
if($errors)
display_errors();
global $global;
$db = $global['db'];
?>
<h2 align="center">Register New Children Center</h2>
<?php  
    shn_form_fopen("achildcenter",null);
    shn_form_hidden(array('seq'=>'chk'));
    shn_form_fsopen('Initial Details');
    shn_form_text('CenterCode','center','size="30"',array('req'=>true));
    shn_form_text('CenterName','centername','size="30"',array('req'=>true));
    shn_form_text('Date(YYYY-MM-DD)','date','size="30"');
    shn_form_text('Filed by','filed_by','size="30"');
    shn_form_text('Function','func','size="30"');
    shn_form_fsclose();
    shn_form_submit('Insert');
    ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
    shn_form_fclose();
}



function _shn_cps_cadd_commit(){
_shn_cps_cadd_commit_db();
}



function _shn_cps_validate_error(){
clean_errors();
$error_flag=false;
$center=$_POST['center'];
$centername=$_POST['centername'];
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$date=$_POST['date'];
$dor=date('Y-M-D');
$rep_address=$_POST['rep_address'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
if($center==''){
add_error(_("Please enter the center code"));
$error_flag=true;
}


if($centername==''){
add_error(_("Please enter the center name"));
$error_flag=true;
}

if(trim($date)=='' | trim($date)==null){
add_error(_("Please enter the date"));
$error_flag=true;
}
else{
if(!shn_valid_date(trim($date))){
add_error(_("Please Check the date Format "));
$error_flag=true;
}
}
return $error_flag;
}

function _shn_cps_cadd_commit_db(){
global $global;
$db = $global['db'];
$center=$_POST['center'];
$centername=$_POST['centername'];
$date=$_POST['date'];
$filed_by=$_POST['filed_by'];
$func=$_POST['func'];
$center_con=$centername.$center;
$q="insert into child_center values ('{$center}','{$centername}','{$date}','{$filed_by}','{$func}')";
$q2="insert into field_options values('opt_child_center_names','{$center}','{$center_con}')";
$res1 = $db->Execute($q);
if($res1==false)
{
$result1=$db->ErrorMsg();
print $result1;
}
$res2=$db->Execute($q2);
if($res2==false)
{
$result2=$db->ErrorMsg();
print $result2;
}
if($res1==true & $res2==true){
?>
<h2>You Have Succesfully Registered Center Details with Center Code<?=$center?></h2>
<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>
<?php	
}
}
?>


