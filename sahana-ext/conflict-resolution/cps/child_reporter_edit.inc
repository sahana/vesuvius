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
  $age=$_POST['age'];
	$id_card=$_POST['id_card'];
	$agegroup=$_POST['opt_age_group'];
	$maritalstatus=$_POST['opt_marital_status'];
  $country=$_POST['opt_country'];
	$religion=$_POST['opt_religion'];
	$race=$_POST['opt_race'];
  $gender=$_POST['opt_gender'];

$opt_bc_status=$_POST['opt_bc_status'];
$text="1=$cd&2=$opt_child_center_names&3=$full_name&4=$family_name&5=$local_name
&6=$dob&7=$pob&8=$pr&9=$cf&10=$idtype&11=$age&12=$id_card&13=$agegroup&14=$maritalstatus&15=$country
&16=$religion&17=$race&18=$gender&19=$opt_bc_status";
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

$childpersonaldata=$_SESSION['childreporter'];	
if($recordCount>0)
{
shn_form_fopen("edtchildreporter",null);
shn_form_fsopen('Child Reporter Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>FullName</th><th>Date Regd</th><th>Relation</th><th>Address</th><th>Phone</th>
<th>Edit</th><th>Delete</th>

<?php 
for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childpersonaldata[$k][0] ?></td><td><?php print  $childpersonaldata[$k][1] ?></td><td><?php print  $childpersonaldata[$k][2] ?></td><td><?php print  $childpersonaldata[$k][3] ?></td><td><?php print  $childpersonaldata[$k][4] ?></td><td><?php print  $childpersonaldata[$k][5] ?></td><td><?php print  $childpersonaldata[$k][6] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildreporter&seq=cedt<?php print $childpersonaldata[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildpersonal&seq=cdel<?php print $childpersonaldata[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childpersonaldata[$k][0]?>')">Delete</a></td></tr>
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



function _shn_cps_cdel_childreporter($child_code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_reporter where p_uuid={$child_code}";


$res1 = $db->Execute($q1);



if($res1==false)
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
<h2>Update Existing Child's Reporter Data</h2>
<?php
	

 $childpersonaldetails=  _shn_cps_get_childdata($child_code);
	
if(count($childpersonaldetails)==9)
{

   //-----------------------------------------
   shn_form_fopen("edtchildreporter",null);
    
    shn_form_hidden(array('seq'=>'chck'));
         
    shn_form_fsopen('Reporter Details');
    $cc=$_SESSION['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$childpersonaldetails[0]));
//shn_form_text('Child Name','','size="30"',array('value'=>$childpersonaldetails[1]));



shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childpersonaldetails[1])); 

    shn_form_text('Name','rep_full_name','size="30"',array('req'=>true,'value'=>$childpersonaldetails[2]));
    shn_form_text('Date of Registration(YYYY-MM-DD)','dor','size="30"',array('value'=>$childpersonaldetails[3]));
		shn_form_text('Relation','rep_relation','size="30"',array('value'=>$childpersonaldetails[4]));

   shn_form_textarea('Address','rep_address','',array('value'=>$childpersonaldetails[5]));
    shn_form_text('Phone','rep_phone','size="30"',array('value'=>$childpersonaldetails[6]));
    shn_form_text('Email','rep_email','size="30"',array('value'=>$childpersonaldetails[7]));
    shn_form_text('Date Interviewed(YYYY-MM-DD)','di','size="30"',array('value'=>$childpersonaldetails[8]));
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

function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_reporter f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childfamilydata= Array();

$childfamilydata[$j++]=$res->fields[5];//
$childfamilydata[$j++]=$res->fields[6];//
$childfamilydata[$j++]=$res->fields[7];//
$childfamilydata[$j++]=$res->fields[8];//
$childfamilydata[$j++]=$res->fields[9];//
$childfamilydata[$j++]=$res->fields[10];//income
$childfamilydata[$j++]=$res->fields[11];//age
$childfamilydata[$j++]=$res->fields[12];//age
$childfamilydata[$j++]=$res->fields[13];//age

if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}
//print 'rcds r'.count($childfamilydata);

return $childfamilydata;

}

function _shn_cps_search_edt_frm()
{
?><h2 align="center">Edit Existing Children</h2><?php
	shn_form_fopen("edtchildreporter");
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
$cd=$_POST['cc'];
$dor=$_POST['dor'];
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


   

    //Date of reg
 
if(trim($dor)=='' | trim($dor)==null)
{
add_error(_("Please enter the date of registration"));
$error_flag=true; 
}
else
{
if(!shn_valid_date(trim($dor)))
{
add_error(_("Please check the  format for date of registration"));
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
$query1="select * from person_uuid p,child_reporter f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_reporter pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_reporter pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_reporter pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_reporter pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_reporter pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_reporter pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_reporter pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_reporter pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}
$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();
//print 'Record count is'.$record_count;

while(!$res1->EOF)
{
$childfamilystatus[$i][$j++]=$res1->fields[5];//childcode
$childfamilystatus[$i][$j++]=$res1->fields[6];//center_code
$childfamilystatus[$i][$j++]=$res1->fields[7];//full name
$childfamilystatus[$i][$j++]=$res1->fields[8];//dor
$childfamilystatus[$i][$j++]=$res1->fields[9];//relation
$childfamilystatus[$i][$j++]=$res1->fields[10];//address
$childfamilystatus[$i][$j++]=$res1->fields[11];//phone
$childfamilystatus[$i][$j++]=$res1->fields[12];//email
$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childreporter']=$childfamilystatus;

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
$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;
//print $puuid;
//print 'i';
$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$dor=$_POST['dor'];
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
$rep_address=$_POST['rep_address'];
$di=$_POST['di'];
$q1="update child_reporter set rep_full_name='{$rep_full_name}',date_of_reg='{$dor}',
rep_relation='{$rep_relation}',rep_address='{$rep_address}',rep_phone='{$rep_phone}',rep_email='{$rep_email}',di='{$di}' where p_uuid={$puuid} ";


$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child reporters details of Details of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child reporter </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildreporter&seq=disp'>
View All Reporters</a>

<?php	
}
}
?>

