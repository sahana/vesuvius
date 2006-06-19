<?php
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



function  _shn_cps_print()
{
global $conf;
$server= $conf['servername'] ;
$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;


$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$dor=$_POST['dor'];
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
$rep_address=$_POST['rep_address'];


$text="1=$puuid&2=$opt_child_center_names&3=$dor&4=$rep_full_name&5=$rep_relation
&6=$rep_phone&7=$rep_email&8=$rep_address";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_reporting_person.php?<?php print $text?>">View in Excel to Print</a>
<?php
}

function _shn_cps_cadd_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Reporting Person Details</h2>
<?php  
shn_form_fopen("achildreporter",null);
    
    shn_form_hidden(array('seq'=>'chk'));
         
    shn_form_fsopen('Reporter Details');
    $cc=$_SESSION['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$cc));
shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name'])); 
    shn_form_text('Name','rep_full_name','size="30"',array('req'=>true));
    shn_form_text('Date of Registration(YYYY-MM-DD)','dor','size="30"');
		shn_form_text('Relation','rep_relation','size="30"');

    shn_form_textarea('Address','rep_address');
    shn_form_text('Phone','rep_phone','size="30"');
    shn_form_text('Email','rep_email','size="30"');
    shn_form_text('Date Interviewed(YYYY-MM-DD)','di','size="30"');
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
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$date=$_POST['dor'];
$di=$_POST['di'];
$rep_address=$_POST['rep_address'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
$cc=$_POST['cc'];
if(trim($cc)=='' | trim($cc)==null)
{
add_error(_("Please enter the child code..."));
$error_flag=true;
}

if($rep_full_name=='')
{
add_error(_("Please enter the reporters name"));
$error_flag=true;
}




if(trim($date)=='' | trim($date)==null )
{
add_error(_("Please enter the date of registration"));
$error_flag=true;

}
else
{
if(!shn_valid_date(trim($date)))
{
add_error(_("Please Check the date Formats "));
$error_flag=true;
}
}

if(trim($di)=='' | trim($di)==null)
{
add_error(_("Please enter the date of Interview"));
$error_flag=true; 
}
else
{
if(!shn_valid_date(trim($di)))
{
add_error(_("Please check the  format for date of interview"));
$error_flag=true;
}

}


$isAddressInValid=trim($rep_address)==null | trim($rep_address)=='';
$isPhoneInValid=trim($rep_phone)==null | trim($rep_phone)=='';
$isEmailInValid=trim($rep_email)==null | trim($rep_email)=='';

//Reporting person contact


if(($isAddressInValid &  $isPhoneInValid &  $isEmailInValid))
    {
        add_error(_("Please enter any contact method of the reporting person"));
        $error_flag=true;
     }



return $error_flag;
}

function _shn_cps_cadd_commit_db(){
global $global;
$db = $global['db'];

$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;
//print $puuid;

$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$dor=$_POST['dor'];
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
$rep_address=$_POST['rep_address'];
$di=$_POST['di'];

$center_con=$centername.$center;
//$q="insert into child_center values ('{$center}','{$centername}','{$date}','{$filed_by}','{$func}','{$dor}','{$rep_full_name}','{$rep_relation}','{$rep_address}','{$rep_phone}','{$rep_email}')";
$q="insert into child_reporter values ({$puuid},'{$opt_child_center_names}','{$rep_full_name}','{$dor}','{$rep_relation}',
'{$rep_address}','{$rep_phone}','{$rep_email}','{$di}')";

//$q2="insert into field_options values('opt_child_center_names','{$center}','{$center_con}')";

$res1 = $db->Execute($q);
if($res1==false)
{
$result1=$db->ErrorMsg();
print $result1;
}

if($res1==true ){
?>
<h2>You Have Succesfully Registered Reporter Details for Child Code"<?=$_SESSION['child_code']?>"</h2>
<li><a href="index.php?mod=cps&act=achildrelation">AddChildRelation</a></li>

<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>
















