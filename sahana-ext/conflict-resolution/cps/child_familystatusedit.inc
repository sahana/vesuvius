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
//print $puuid;
//$_SESSION['child_code']=$puuid;

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


function _shn_cps_search_edt_frm()
{
?><h2 align="center">Edit Existing Child Family Status</h2>
<?php

shn_form_fopen("edtchildfstatus");
shn_form_fsopen("Edit Child FamilyStatus");
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

function  _shn_cps_cedt_start($errors=false){
	if($errors)
	display_errors();
           
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing ChildRelation</h2>

<?php
	
$module = $global['module'];
$child_code=$_POST['child_code'];
$first_name=$_POST['first_name'];
$last_name=$_POST['last_name'];
$family_name=$_POST['family_name'];


$recordCount=  _shn_cps_get_session($child_code,$first_name,$last_name,$family_name);

$childfamilystatus=$_SESSION['childfamilystatus'];

if($recordCount>0)
{
shn_form_fopen("edtchildfstatus",null);
shn_form_fsopen('Child Family Status');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>Present Status</th><th>Reason for Nt BkngPreHse</th><th>IsIncomeSufficient?</th>
<th>Family Details</th><th>Special Material Needs</th><th>Material Details</th><th>Edit</th><th>Delete</th>

<?php 

for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childfamilystatus[$k][0] ?></td><td><?php print  $childfamilystatus[$k][1] ?></td><td><?php print  $childfamilystatus[$k][2] ?></td><td><?php print  $childfamilystatus[$k][3] ?></td><td><?php print  $childfamilystatus[$k][4] ?></td><td><?php print  $childfamilystatus[$k][5] ?></td><td><?php print  $childfamilystatus[$k][6] ?></td><td><?php print  $childfamilystatus[$k][7] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildfstatus&seq=cedt<?php print $childfamilystatus[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildfstatus&seq=cdel<?php print $childfamilystatus[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childfamilystatus[$k][0]?>')">Delete</a></td></tr>
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



function  _shn_cps_cedt_showform($errors=false,$id){
	if($errors)
	display_errors();
           
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing Child's Family Status</h2>

<?php
	
//todo by isuru
 $childfamilystatus=  _shn_cps_get_childdata($id);
$val=count(_shn_cps_get_childdata($id));
	
if($val==9)
{

   //-----------------------------------------
   shn_form_fopen("edtchildfstatus",null);
 
shn_form_hidden(array('seq'=>'chck'));
shn_form_fsopen('Child Family Status');
//$cc=$_POST['child_code'];
shn_form_text('Child Code','cc','cc',array('req'=>true,'value'=>$id));  
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childfamilystatus[1]));    
shn_form_opt_select('opt_child_family_status','Currently Family is :','',array('value'=>$childfamilystatus[2]));
shn_form_opt_select('opt_child_house_not_backed_reason','If the family is not back to their previous house due to:','',array('value'=>$childfamilystatus[3]));
shn_form_select(array('1'=>'Yes','0'=>'No'),'Does Family has sufficient income?','has_income','',$childfamilystatus[4]);
print '<br/>';
shn_form_textarea('Family Details','income_des','size="30"',array('value'=>$childfamilystatus[5]));
shn_form_select(array('1'=>'Yes','0'=>'No'),'Special Material needed?','is_needed','',$childfamilystatus[6]);
    print '<br/>';
		 shn_form_textarea('Special Material Needs','materials','size="30"',array('value'=>$childfamilystatus[7]));
		 
		 shn_form_opt_select('opt_house','During the Tsunami:','',array('value'=>$childfamilystatus[8]));
   	
//shn_form_radio(array('name'=>'yes'),'Does the child go to tution classes?','c7q3');

shn_form_fsclose();
shn_form_submit('Update');
   ?>
     <input type=submit size=30 name="print"  value="Print"/>
    <?
 
shn_form_fclose();
 }

else 
print 'Record Deleted by another user for child code  '.$id.' Please insert the details using left navigation menu';
   
}

function _shn_cps_cdel_childfamilystatus($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_family_status where p_uuid={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  family status of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildfstatus&seq=disp'>
View All Child Centers</a>
<?php

}
}


function _shn_cps_cedt_commit()
 {
 _shn_cps_cedt_commit_db();
 }
 
function _shn_cps_cedt_commit_db(){
//insert to database;

global $global;
$module = $global['module'];

$db = $global['db'];
$puuid=$_POST['cc'];
//print $puuid;


$opt_child_center_names=$_POST['opt_child_center_names'];
$opt_child_family_status=$_POST['opt_child_family_status'];
$opt_child_house_not_backed_reason=$_POST['opt_child_house_not_backed_reason'];
$has_income=$_POST['has_income'];
$income_des=$_POST['income_des'];
$is_needed=$_POST['is_needed'];
$materials=$_POST['materials'];
$materialneeds=$_POST['materialneeds'];
	
	$opt_house=$_POST['opt_house'];

$q1="update child_family_status  set at_present_family_status='{$opt_child_family_status}'
,reason_for_ntbk_prehouse='{$opt_child_house_not_backed_reason}',family_income={$has_income},
details_family='{$income_des}'
,special_material_needed={$is_needed},details_material='{$materials}',during_tsunami_situ='{$opt_house}' where p_uuid={$puuid} ";


$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child Family Status  of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child relation </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildfstatus&seq=disp'>
View All Family Status's</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_family_status f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childfamilydata= Array();

$childfamilydata[$j++]=$res->fields[5];//
$childfamilydata[$j++]=$res->fields[6];//
$childfamilydata[$j++]=$res->fields[7];//
$childfamilydata[$j++]=$res->fields[8];//
$childfamilydata[$j++]=($res->fields[10]==1)?'1':'';//
$childfamilydata[$j++]=$res->fields[11];//income

$childfamilydata[$j++]=($res->fields[12]==1)?'1':'';//age
$childfamilydata[$j++]=$res->fields[13];//islivingwithchild
$childfamilydata[$j++]=$res->fields[14];//profession
if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}
//print 'rcds r'.count($childfamilydata);

return $childfamilydata;

}





/**
 * populate session variables from database
 * 	
*/

function _shn_cps_get_session($child_code,$first_name,$last_name,$family_name){
	global $global;
	$db = $global['db'];

$query1='';

if(($child_code==null | $child_code=='') &($first_name==null | $first_name=='')&($last_name==null | $last_name=='') &($family_name==null | $family_name=='') )
$query1="select * from person_uuid p,child_family_status f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_family_status pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_family_status pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_status pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_family_status pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_status pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_status pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_family_status pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_status pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}
$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childfamilystatus[$i][$j++]=$res1->fields[5];//childcode
$childfamilystatus[$i][$j++]=$res1->fields[6];//center_code
$childfamilystatus[$i][$j++]=$res1->fields[7];//at presentfamilystatus
$childfamilystatus[$i][$j++]=$res1->fields[8];//Reason for not bkg pre house
$childfamilystatus[$i][$j++]=$res1->fields[10];//Family Income
$childfamilystatus[$i][$j++]=$res1->fields[11];//Family Details
$childfamilystatus[$i][$j++]=$res1->fields[12];//Special material needs
$childfamilystatus[$i][$j++]=$res1->fields[13];//Details
$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childfamilystatus']=$childfamilystatus;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
