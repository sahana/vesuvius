  <script language='JavaScript'>
function confirmdelete(child_code)
{
return confirm('This record for child code'+child_code+' will be permanently deleted');
}
</script>

<?php
/* $Id; */

/**Update functions for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_cps_print_data()
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
  $idtype=get_option_description($idtype);
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


function  _shn_cps_cedt_start($errors=false){
	if($errors)
	display_errors();
           
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing ChildCenters</h2>

<?php
	
$module = $global['module'];

$child_code=$_POST['child_code'];
$first_name=$_POST['first_name'];
$last_name=$_POST['last_name'];
$family_name=$_POST['family_name'];

$recordCount=  _shn_cps_get_session($child_code,$first_name,$last_name,$family_name);

$childpersonaldata=$_SESSION['childpersonaldata'];	
if($recordCount>0)
{
shn_form_fopen("edtchildpersonal",null);
shn_form_fsopen('Child Personal Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>FirstName</th><th>LastName</th><th>FamilyName</th><th>Dob</th>
<th>Pob</th><th>Edit</th><th>Delete</th>

<?php 
for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childpersonaldata[$k][0] ?></td><td><?php print  $childpersonaldata[$k][1] ?></td><td><?php print  $childpersonaldata[$k][2] ?></td><td><?php print  $childpersonaldata[$k][3] ?></td><td><?php print  $childpersonaldata[$k][4] ?></td><td><?php print  $childpersonaldata[$k][5] ?></td><td><?php print  $childpersonaldata[$k][6] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildpersonal&seq=cedt<?php print $childpersonaldata[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildpersonal&seq=cdel<?php print $childpersonaldata[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childpersonaldata[$k][0]?>')">Delete</a></td></tr>
<?php
}
?>
</table>
<?php
shn_form_fsclose();
shn_form_fclose(); 
}
else
print 'Record Not Found for child   '.$child_code.' Please insert the details using left navigation menu';

}



function _shn_cps_cdel_childpersonal($child_code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from person_uuid where p_uuid={$child_code}";
$q2="delete from person_details where p_uuid={$child_code}";
$q3="delete from identity_to_person where p_uuid={$child_code}"; 
$q4="delete from child_personal_data where p_uuid={$child_code}";


$res1 = $db->Execute($q1);
$res2 = $db->Execute($q2);
$res3 = $db->Execute($q3);
$res4 = $db->Execute($q4);


if($res1==false | $res2==false | $res3==false | $res4==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  Details of"<?=$child_code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildpersonal&seq=disp'>
View All Child Centers</a>
<?php

}
}

function  _shn_cps_cedt_showform($errors=false,$child_code){
	if($errors)
	display_errors();
           
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing Child's Personal Data</h2>
<?php
	

 $childpersonaldetails=  _shn_cps_get_childdata($child_code);
	
if(count($childpersonaldetails)==19)
{

   //-----------------------------------------
shn_form_fopen("edtchildpersonal",null);
shn_form_hidden(array('seq'=>'chck'));
shn_form_fsopen('Child Personal Details');
shn_form_text('Child Code','cd','size="30"',array('req'=>true,'value'=>$childpersonaldetails[0]));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childpersonaldetails[1]));
shn_form_text('First Name','local_name','size="30"',array('value'=>$childpersonaldetails[2]));
    
    shn_form_text('Last Name','full_name','size="30"',array('req'=>true,'value'=>$childpersonaldetails[3]));
    shn_form_text('Family Name','family_name','size="30"',array('value'=>$childpersonaldetails[4]));
    shn_form_text('Date of Birth   (YYYY-MM-DD)','dob','size=8',array('value'=>$childpersonaldetails[5]));
    shn_form_text('Place of Birth','pob','size=30',array('value'=>$childpersonaldetails[6]));
    shn_form_text('Present Residence)','pr','size=30',array('value'=>$childpersonaldetails[7]));
    shn_form_text('Coming From','cf','size=30',array('value'=>$childpersonaldetails[8]));
 shn_form_opt_select("opt_bc_status","Birthday certificate",'',array('value'=>$childpersonaldetails[17]));
  ?>
  
  <?php
	  shn_form_text('BDCNumber','id_card','size=30',array('value'=>$childpersonaldetails[10]));
//    shn_form_opt_select("opt_age_group","Age Group",'',array('value'=>$childpersonaldetails[11]));
shn_form_text('Age','age','size="10"',array('value'=>$childpersonaldetails[11]));
    shn_form_opt_select("opt_gender","Gender",'',array('value'=>$childpersonaldetails[12]));
    shn_form_opt_select("opt_marital_status","Marital Status",'',array('value'=>$childpersonaldetails[13]));
shn_form_opt_select('opt_country','Country','',array('value'=>$childpersonaldetails[14]))    ;
shn_form_opt_select("opt_religion","Religion",'',array('value'=>$childpersonaldetails[15]));
    shn_form_opt_select("opt_race","Race",'',array('value'=>$childpersonaldetails[16]));
shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child registered in school ?','is_regd','',$childpersonaldetails[18]);
 print '<br/>';
    shn_form_fsclose();
    shn_form_submit('Update');
    ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
    shn_form_fclose();
 }

else 
print 'Record Deleted by another user for child code  '.$child_code.' Please insert the details using left navigation menu';
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


function _shn_cps_cedt_chk($errors=false){
        if($errors)
	display_errors;
	global $global;
	$_SESSION['center_code']=$_POST['cd'];
	$_SESSION['center_name']=$_POST['center_name'];
	$_SESSION['date']=$_POST['date'];
	$_SESSION['filed_by']=$_POST['filed_by'];
	$_SESSION['function']=$_POST['function'];
	$_SESSION['date_regd']=$_POST['date_regd'];
	$_SESSION['rep_full_name']=$_POST['rep_full_name'];
  $_SESSION['rep_relation']=$_POST['rep_relation'];
  $_SESSION['rep_address']=$_POST['rep_address'];
  $_SESSION['rep_phone']=$_POST['rep_phone'];
  $_SESSION['rep_email']=$_POST['rep_email'];
}



    
function _shn_cps_cedt_commit()
{
_shn_cps_cedt_commit_db();
}

function _shn_cps_get_childdata($child_code)
{
	global $global;
	$db = $global['db'];
$query="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid and p.p_uuid={$child_code}";
$recordCount=0;
$res = $db->Execute($query);
$recordCount=$res->RecordCount();
$j=0;
$childpersonaldata= Array();
$childpersonaldata[$j++]=$res->fields[0];//child_code
$childpersonaldata[$j++]=$res->fields[20];//center_code
$childpersonaldata[$j++]=$res->fields[3];//first_name
$childpersonaldata[$j++]=$res->fields[1];//last_name
$childpersonaldata[$j++]=$res->fields[2];//family_name
$childpersonaldata[$j++]=$res->fields[7];//dob
$childpersonaldata[$j++]=$res->fields[22];//pob
$childpersonaldata[$j++]=$res->fields[23];//pr present_residence
$childpersonaldata[$j++]=$res->fields[24];//cf coming from
$childpersonaldata[$j++]=$res->fields[18];//opt_id_type
$childpersonaldata[$j++]=$res->fields[17];//id_card
$childpersonaldata[$j++]=$res->fields[21];//opt_age_group
$childpersonaldata[$j++]=$res->fields[14];//opt_gender
$childpersonaldata[$j++]=$res->fields[13];//opt_marital_status
$childpersonaldata[$j++]=$res->fields[10];//opt_country
$childpersonaldata[$j++]=$res->fields[12];//opt_religion
$childpersonaldata[$j++]=$res->fields[11];//opt_race
$childpersonaldata[$j++]=$res->fields[26];//opt_bcstatus
$childpersonaldata[$j++]=($res->fields[28]==1)?'1':'';//school
if($res==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $childpersonaldata;

}


function _shn_cps_search_edt_frm()
{
?><h2 align="center">Edit Existing Children</h2><?php
	shn_form_fopen("edtchildpersonal");
	shn_form_fsopen("Edit Child Personal Data");
	shn_form_hidden(array('seq'=>'disp'));
//shn_form_opt_select("opt_child_center_names","Center Name");   
	shn_form_text('Code of the Child ','child_code','size="20"');
shn_form_text('First Name ','first_name','size="20"');
shn_form_text('Last Name ','last_name','size="20"');
shn_form_text('Family Name ','family_name','size="20"');

        

	shn_form_fsclose();
	shn_form_submit("Search");
	shn_form_fclose();
	

}



function _shn_cps_validate_error(){
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


return $error_flag;
}


/**
 * populate session variables from database
 * @param center_code	
*/
function _shn_cps_get_session($child_code,$first_name,$last_name,$family_name){
	global $global;
	$db = $global['db'];

$query1='';
if(($child_code==null | $child_code=='') &($first_name==null | $first_name=='')&($last_name==null | $last_name=='') &($family_name==null | $family_name=='') )
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid ";/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";

*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))

{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}
else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */

}
else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}
else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p, pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and   p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}
else
{
$query1="select * from person_uuid p,person_details pd,identity_to_person itp,child_personal_data pdt  where   itp.p_uuid=pdt.p_uuid and pd.p_uuid=pdt.p_uuid and pd.p_uuid=p.p_uuid and p.p_uuid={$child_code}";/* and p.local_name like '%{$first_name}%'"; and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";*/

}


$res1 = $db->Execute($query1);

$record_count=$res1->RecordCount();
$childpersonaldata= Array();
$i=0;//keep track of rows
$j=0;//keep track of columns 
while(!$res1->EOF)
{
$childpersonaldata[$i][$j++]=$res1->fields[0];//child_code
$childpersonaldata[$i][$j++]=$res1->fields[20];//center_code
$childpersonaldata[$i][$j++]=$res1->fields[3];//first_name
$childpersonaldata[$i][$j++]=$res1->fields[1];//last_name
$childpersonaldata[$i][$j++]=$res1->fields[2];//family_name
$childpersonaldata[$i][$j++]=$res1->fields[7];//dob
$childpersonaldata[$i][$j++]=$res1->fields[22];//pob
$childpersonaldata[$i][$j++]=$res1->fields[23];//pr present_residence
$childpersonaldata[$i][$j++]=$res1->fields[24];//cf coming from
$childpersonaldata[$i][$j++]=$res1->fields[18];//opt_id_type
$childpersonaldata[$i][$j++]=$res1->fields[17];//id_card
$childpersonaldata[$i][$j++]=$res1->fields[21];//opt_age_group
$childpersonaldata[$i][$j++]=$res1->fields[14];//opt_gender
$childpersonaldata[$i][$j++]=$res1->fields[13];//opt_marital_status
$childpersonaldata[$i][$j++]=$res1->fields[10];//opt_country
$childpersonaldata[$i][$j++]=$res1->fields[12];//opt_religion
$childpersonaldata[$i][$j++]=$res1->fields[11];//opt_race
//$childpersonaldata[$i][$j++]=$res1->fields[3];//opt_marital_status

$j=0;
$i++;

$res1->MoveNext();

}
$i=0;				
$_SESSION['childpersonaldata']=$childpersonaldata;
if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;

}


function _shn_cps_cedt_commit_db(){
//insert to database;
global $global;
$module = $global['module'];

$db = $global['db'];

//person_uuid table
$child_code=$_POST['cd'];

$full_name=$_POST['full_name'];
$family_name=$_POST['family_name'];
$local_name=$_POST['local_name'];

//person_details
$dob=$_POST['dob'];
$opt_age_group=$_POST['opt_age_group'];
$opt_country=$_POST['opt_country'];
$opt_race=$_POST['opt_race'];
$opt_religion=$_POST['opt_religion'];
$opt_marital_status=$_POST['opt_marital_status'];
$opt_gender=$_POST['opt_gender'];

//identity_to_person
$opt_id_type=$_POST['opt_bc_type'];
$id_card=$_POST['id_card'];

//child_personal_data
$pob=$_POST['pob'];
$opt_child_center_names=$_POST['opt_child_center_names'];
$pr=$_POST['pr'];
$cf=$_POST['cf'];
$opt_bc_status=$_POST['opt_bc_status'];
$age=$_POST['age'];
$is_regd=$_POST['is_regd'];
$q1="update person_uuid set full_name='{$full_name}',family_name='{$family_name}',l10n_name='{$local_name}' where p_uuid={$child_code} ";

$q2="update person_details set birth_date='{$dob}',opt_age_group='{$opt_age_group}',opt_country='{$opt_country}',opt_race='{$opt_race}',opt_religion='{$opt_religion}',opt_marital_status='{$opt_marital_status}',opt_gender='{$opt_gender}' where p_uuid={$child_code}";

$q3="update identity_to_person set opt_id_type='$opt_id_type',serial='{$id_card}' where p_uuid={$child_code}";

$q4="update child_personal_data set age={$age},center_code='{$opt_child_center_names}',place_of_birth='{$pob}',present_residence='{$pr}',coming_from='{$cf}',bc_status='{$opt_bc_status}',is_reg_in_school={$is_regd} where p_uuid={$child_code}";

$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

$res2=$db->Execute($q2);
if($res2==false)
{
$result2=$db->ErrorMsg();
print 'error2 is'.$result2;
}


$res3=$db->Execute($q3);
if($res3==false)
{
$result3=$db->ErrorMsg();
print 'error3 is'.$result3;
}

$res4=$db->Execute($q4);
if($res4==false)
{
$result4=$db->ErrorMsg();
print 'error4 is'.$result4;
}

if($res1==true & $res2==true & $res3==true & $res4==true)
{

?>
<h2>You Have Succesfully Updated Child personal details of Details of <?=$child_code?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child center </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildpersonal&seq=disp'>
View All Children</a>

<?php	
}
}
?>

