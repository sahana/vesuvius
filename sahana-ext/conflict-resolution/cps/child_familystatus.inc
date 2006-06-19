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
$puuid=$_POST['cc'];
$opt_child_center_names=$_POST['opt_child_center_names'];
//$_SESSION['center_name']=$opt_child_center_names;
$opt_child_family_status=$_POST['opt_child_family_status'];
$opt_child_family_status=get_option_description($opt_child_family_status);
$opt_child_house_not_backed_reason=$_POST['opt_child_house_not_backed_reason'];
$opt_child_house_not_backed_reason=get_option_description($opt_child_house_not_backed_reason);

$has_income=(($_POST['has_income']=='1')?'Yes':'No');
//print $has_income;
$income_des=$_POST['income_des'];
$is_needed=(($_POST['is_needed']=='1')?'Yes':'No');
$materials=$_POST['materials'];
$materialneeds=$_POST['materialneeds'];
	$opt_house=$_POST['opt_house'];
$opt_house=get_option_description($opt_house);

$text="1=$puuid&2=$opt_child_center_names&3=$opt_child_family_status&4=$opt_child_house_not_backed_reason&5=$has_income
&6=$income_des&7=$materials&8=$is_needed&9=$opt_house";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_family_status.php?<?php print $text?>">View in Excel to Print</a>
<?php
}



function get_option_description($option_code)
{
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
<h2 align="center">Child Family Status</h2>
<?php  
   if($errors)
        display_errors();
   shn_form_fopen("achildfstatus",null,array('enctype'=>'enctype="multipart/form-data"'));
   shn_form_hidden(array('seq'=>'chk'));
   shn_form_fsopen('Family situation');

   $cc=$_SESSION['child_code'];
   shn_form_text('Child Code','cc','cc',array('value'=>$cc));  
   shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
   shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name']));    
   shn_form_opt_select('opt_child_family_status','Currently Family is :');
   
   shn_form_opt_select('opt_child_house_not_backed_reason','If the family is not back to their previous house due to:');
    
   
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Does Family has sufficient income?','has_income');
    print '<br/>';
    
	  shn_form_textarea('Family Details','income_des','size="30"');
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Special Material needed?','is_needed');
    print '<br/>';
		 shn_form_textarea('Special Material Needs','materials','size="30"');
		 //opt_child_house_not_backed_reason'
	 shn_form_opt_select('opt_house','During the Tsunami:');
    shn_form_fsclose();
    shn_form_submit('Insert');
    ?>
     <input type=submit size=30 name="print"  value="Print"/>
    <?
    shn_form_fclose();
}



function _shn_cps_cadd_commit()
{
//write to database
_shn_cps_cadd_commit_db();
}



function _shn_cps_validate_error()
{
	clean_errors();
	$error_flag=false;
  $cc=$_POST['cc'];
  if(trim($cc)==''){
  add_error(_("Please enter the child code"));
  $error_flag=true;
  }
	return $error_flag;
}

function _shn_cps_cadd_commit_db(){
//insert t{$lv}o database;
global $global;
$db = $global['db'];
$puuid=$_POST['cc'];
//print $puuid;
$_SESSION['child_code']=$puuid;

$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$opt_child_family_status=$_POST['opt_child_family_status'];
$opt_child_house_not_backed_reason=$_POST['opt_child_house_not_backed_reason'];
$has_income=$_POST['has_income'];
$income_des=$_POST['income_des'];
$materials=$_POST['materials'];
$materialneeds=$_POST['materialneeds'];
	$opt_house=$_POST['opt_house'];


//insert into family status
$q1="insert into child_family_status values({$puuid},'{$opt_child_center_names}','{$opt_child_family_status}','{$opt_child_house_not_backed_reason}'
,' ',{$has_income},'{$income_des}','{$is_needed}','{$materials}','{$opt_house}')";



$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
//include('errorpage.html');
print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the family status  for child  code <?=$puuid?> </h2>
<!--<h3>You Have Succesfully Registered <?=$_SESSION['c_code']?></h3><br>-->

<ul>
<li><a href="index.php?mod=cps&act=achildeducation">AddChildEducation</a></li>
</ul>

<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

