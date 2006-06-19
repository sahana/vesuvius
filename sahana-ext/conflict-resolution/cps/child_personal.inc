<?php
/* $Id; */

/**Child library for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
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
$cd=$_POST['cd'];
$opt_child_center_names=$_POST['opt_child_center_names'];
$full_name=$_POST['full_name'];
$family_name=$_POST['family_name'];
$local_name=$_POST['local_name'];
$commonname=$local_name.'  '.$full_name;
	
$dob=$_POST['dob'];
$pob=$_POST['pob'];//to child_personal
$pr=$_POST['pr'];//to child_personal
$cf=$_POST['cf'];//to child_personal
$idtype=$_POST['opt_bc_type'];//birth certificate changeisuru
$age=$_POST['age'];
$id_card=$_POST['id_card'];
$agegroup=$_POST['opt_age_group'];
$maritalstatus=$_POST['opt_marital_status'];
$maritalstatus=get_option_description($maritalstatus);
$country=$_POST['opt_country'];
$country=get_option_description($country);
$religion=$_POST['opt_religion'];
$religion=get_option_description($religion);
$race=$_POST['opt_race'];
$race=get_option_description($race);
$gender=$_POST['opt_gender'];
$gender=get_option_description($gender);
$opt_bc_status=$_POST['opt_bc_status'];
$opt_bc_status=get_option_description($opt_bc_status);
$is_regd=$_POST['is_regd'];


$text="1=$cd&2=$opt_child_center_names&3=$full_name&4=$family_name&5=$local_name
&6=$dob&7=$pob&8=$pr&9=$cf&10=$idtype&11=$age&12=$id_card&13=$agegroup&14=$maritalstatus&15=$country
&16=$religion&17=$race&18=$gender&19=$opt_bc_status&20=$is_regd";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_personal_data_excel.php?<?php print $text?>">View in Excel to Print</a>
<?php
}

function get_option_description($option_code){
global $global;
$module = $global['module'];
$db = $global['db'];
$query="select option_description from field_options where option_code='{$option_code}'";
$res = $db->Execute($query);
$optiondescription=$res->fields[0];//
return $optiondescription;
}

function _shn_cps_cadd_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Child Personal Data</h2>

<?php
    if($errors)
        display_errors();

shn_form_fopen("achildpersonal",null);
shn_form_hidden(array('seq'=>'chk'));
shn_form_fsopen('Child Personal Details');
$cc=$_SESSION['child_code'];
shn_form_text('Child Code','cd','size="30"',array('req'=>true,'value'=>$cc));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name'])); 
shn_form_text('First Name','local_name','size="30"');
shn_form_text('Last Name','full_name','size="30"',array('req'=>true));
shn_form_text('Family Name','family_name','size="30"');
shn_form_text('Date of Birth   (YYYY-MM-DD)','dob','size=8',array('req'=>true));
shn_form_text('Place of Birth','pob','size=30');
shn_form_textarea('Current Address','pr','size=90');
shn_form_text('Coming From','cf','size=30');
shn_form_opt_select("opt_bc_status","Birth Certificate");
shn_form_text('BCNumber','id_card','size=30');
shn_form_text('Age','age','size="10"');
shn_form_opt_select("opt_gender","Gender");
shn_form_opt_select("opt_marital_status","Marital Status");
shn_form_opt_select("opt_country","Country")    ;
shn_form_opt_select("opt_religion","Religion");
shn_form_opt_select("opt_race","Race");
shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child registered in school ?','is_regd');
print '<br/>';
shn_form_fsclose();
shn_form_submit('Insert');
?>
    <input type=submit size=30 name="print"  value="Print"/>
<?php
shn_form_fclose();
?>
<?php
}

function _shn_cps_cadd_commit(){
_shn_cps_cadd_commit_db();
}



function _shn_cps_validate_error()
{
clean_errors();
$error_flag=false;
$center=$_POST['full_name'];
$cd=$_POST['cd'];
$dob=$_POST['dob'];
$age=$_POST['age'];
if($cd==''){
add_error(_("Please enter the Child Code"));
        
$error_flag=true;
}
else
{
if(!is_numeric($cd))
{
add_error(_("ChildCode Should be an Integer"));
    
$error_flag=true;
}
}


if($age==''){
add_error(_("Please enter the Age"));
        
$error_flag=true;
}
else
{
if(!is_numeric($age))
{
add_error(_("Age Should be an Integer"));
    
$error_flag=true;
}
}



   if($center==''){
        add_error(_("Please enter the Full Name"));
 
$error_flag=true;
}

    //Date of birth
 
if(trim($dob)=='' | trim($dob)==null)
{
add_error(_("Please enter the date of birth"));
$error_flag=true; 
}
else
{
if(!shn_valid_date(trim($dob)))
{
add_error(_("Please check the  format for date of birth"));
$error_flag=true;
}

}

	
	return $error_flag;
}

function _shn_cps_cadd_commit_db(){
//insert to database;
global $global;
$db = $global['db'];


	$cd=$_POST['cd'];
        $opt_child_center_names=$_POST['opt_child_center_names'];
	$full_name=$_POST['full_name'];
	$family_name=$_POST['family_name'];
	$local_name=$_POST['local_name'];
	
	$commonname=$local_name.'  '.$full_name;
	
	$dob=$_POST['dob'];
	$pob=$_POST['pob'];//to child_personal
	$pr=$_POST['pr'];//to child_personal
	$cf=$_POST['cf'];//to child_personal
  $idtype=$_POST['opt_bc_type'];//birth certificate changeisuru
  $age=$_POST['age'];
	$id_card=$_POST['id_card'];
	$agegroup=$_POST['opt_age_group'];
	$maritalstatus=$_POST['opt_marital_status'];
  $country=$_POST['opt_country'];
	$religion=$_POST['opt_religion'];
	$race=$_POST['opt_race'];
  $gender=$_POST['opt_gender'];

$opt_bc_status=$_POST['opt_bc_status'];
$is_regd=$_POST['is_regd'];
$_SESSION['child_code']=$cd;
$_SESSION['center_name']=$opt_child_center_names;
$_SESSION['commonname']=$commonname;
$date=date("Y-m-d H:i:s");
//enter into person_uuid table
$q1="insert into person_uuid values({$cd},'{$full_name}','{$family_name}','{$local_name}','child')";
$q2="insert into person_details values({$cd},0,'{$dob}','{$agegroup}','em','{$country}','{$race}','{$religion}','{$maritalstatus}','{$gender}','child')";
$q3="insert into identity_to_person values({$cd},'{$id_card}','{$idtype}')";
$q4="insert into child_personal_data values({$cd},'{$opt_child_center_names}',{$age},'{$pob}','{$pr}','{$cf}',' ','{$opt_bc_status}','{$date}',{$is_regd})";

$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
//include('errorpage.html');
print $result1;
}
$res2 = $db->Execute($q2);
if($res2==false)
{
$result2=$db->ErrorMsg();
//include('errorpage.html');
print $result2;
}



$res3 = $db->Execute($q3);
if($res3==false)
{
$result3=$db->ErrorMsg();
//include('errorpage.html');
print $result3;
}

$res4 = $db->Execute($q4);
if($res4==false)
{
$result4=$db->ErrorMsg();
//include('errorpage.html');
print $result4;
}



if($res1==true & $res2==true & $res3==true & $res4==true){

?>
<h2>You Have Succesfully Registered "<?=$_SESSION['child_code']?>"</h2>

<ul>

<li><a href="index.php?mod=cps&act=achildreporter">AddChildReporter</a></li>

</ul>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue.........</p>


<?php	
}
}
?>

