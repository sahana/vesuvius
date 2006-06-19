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

function  _shn_cps_print()
{
global $conf;
$server= $conf['servername'] ;
$puuid=$_POST['cc'];
$opt_child_center_names=$_POST['opt_child_center_names'];

$is_school_tsunami=(($_POST['is_school_tsunami']=='1')?'Yes':'No');
$snm_tsunami=$_POST['snm_tsunami'];
$level_tsunami=$_POST['level_tsunami'];
$why_tsunami=$_POST['why_tsunami'];
$is_school_now=(($_POST['is_school_now']=='1')?'Yes':'No'); 
$snm_now=$_POST['snm_now'];
$why_now=$_POST['why_now'];
$level_now=$_POST['level_now'];
$is_tution=(($_POST['is_tution']=='1')?'Yes':'No');
	$is_religious=(($_POST['is_religious']=='1')?'Yes':'No');$_POST['is_religious'];
	$is_temple=(($_POST['is_temple']=='1')?'Yes':'No');
	
	$bf1=$_POST['bf1'];
	$bf2=$_POST['bf2'];
	
	
$is_bf1_reg=(($_POST['is_bf1_reg']=='1')?'Yes':'No');
$is_bf2_reg=(($_POST['is_bf2_reg']=='1')?'Yes':'No');

$text="1=$puuid&2=$opt_child_center_names&3=$is_school_tsunami&4=$snm_tsunami&5=$why_tsunami
&6=$level_tsunami&7=$is_school_now&8=$snm_now&9=$why_now&10=$level_now&11=$is_tution
&12=$is_religious&13=$is_temple&14=$bf1&15=$is_bf1_reg&16=$bf2&17=$is_bf2_reg";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_education.php?<?php print $text?>">View in Excel to Print</a>
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
?><h2 align="center">Edit Existing Child Education Status</h2>
<?php

shn_form_fopen("edtchildeducation");
shn_form_fsopen("Edit Child Educational Status");
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

$childeducation=$_SESSION['childeducation'];

if($recordCount>0)
{
shn_form_fopen("edtchildeducation",null);
shn_form_fsopen('Child Educational Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>SclinTsmi</th><th>Name</th><th>Level</th>
<th>Sclnow</th><th>Name</th><th>Level</th><th>Edit</th><th>Delete</th>

<?php 

for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childeducation[$k][0] ?></td><td><?php print  $childeducation[$k][1] ?></td><td><?php print  $childeducation[$k][2] ?></td><td><?php print  $childeducation[$k][3] ?></td><td><?php print  $childeducation[$k][4] ?></td><td><?php print  $childeducation[$k][6] ?></td><td><?php print  $childeducation[$k][7] ?></td><td><?php print  $childeducation[$k][8] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildeducation&seq=cedt<?php print $childeducation[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildeducation&seq=cdel<?php print $childeducation[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childeducation[$k][0]?>')">Delete</a></td></tr>
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


    
   if(trim($cc)==null | trim($cc)==''){
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
<h2>Update Existing Child's Educational Details</h2>

<?php
	
//todo by isuru
 $childeducation= _shn_cps_get_childdata($id);
$val=count(_shn_cps_get_childdata($id));
	
if($val==17)
{

   //-----------------------------------------
   shn_form_fopen("edtchildeducation",null);
 
shn_form_hidden(array('seq'=>'chck'));
shn_form_fsopen('Child Educational Details');
//$cc=$_POST['child_code'];
shn_form_text('Child Code','cc','size="30"',array('req'=>true,'value'=>$childeducation[0]));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childeducation[1])); 
shn_form_select(array('1'=>'Yes','0'=>'No'),'Was the Child going to School before tsunami?','is_school_tsunami','',$childeducation[2]);
   print  '<br/>';
shn_form_text('School Name','snm_tsunami','size="30"',array('value'=>$childeducation[3]));

  shn_form_text('Why','why_tsunami','size="30"',array('value'=>$childeducation[5]));

shn_form_text('Level','level_tsunami','size="30"',array('value'=>$childeducation[4]));
  
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the Child going to School now?','is_school_now','',$childeducation[6]);
   print  '<br/>'; 
	
	  shn_form_text('School Name','snm_now','size="30"',array('value'=>$childeducation[7]));
    shn_form_text('Why','why_now','size="30"',array('value'=>$childeducation[9]));

    shn_form_text('Level','level_now','size="30"',array('value'=>$childeducation[8]));

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to tution now?','is_tution','',$childeducation[10]);
  print  '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to religious school now?','is_religious','',$childeducation[11]);
  print  '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to temple or mosque now?','is_temple','',$childeducation[12]);
  print  '<br/>';

    shn_form_text('Child Best Friend1','bf1','size="30"',array('value'=>$childeducation[13]));
    
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Best Friend registeredin center?','is_bf1_reg','',$childeducation[15]);
 print '<br/>';
shn_form_text('Childs Best Friend2','bf2','size="30"',array('value'=>$childeducation[14]));
shn_form_select(array('1'=>'Yes','0'=>'No'),'Best Friend registeredin center?','is_bf2_reg','',$childeducation[16]);
 print '<br/>';

    shn_form_fsclose();
    shn_form_submit('Update');
     ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
    shn_form_fclose(); 
}

else 
print 'Record Deleted by another user for child code  '.$id.' Please insert the details using left navigation menu';
   
}

function _shn_cps_cdel_childeducation($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_education where p_uuid={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  educationaldetails  of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildeducation&seq=disp'>
View All Child Education Details</a>
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


$puuid=$_POST['cc'];
$opt_child_center_names=$_POST['opt_child_center_names'];
$is_school_tsunami=$_POST['is_school_tsunami'];
$snm_tsunami=$_POST['snm_tsunami'];
$level_tsunami=$_POST['level_tsunami'];
$why_tsunami=$_POST['why_tsunami'];
$is_school_now=$_POST['is_school_now']; 
$snm_now=$_POST['snm_now'];
$why_now=$_POST['why_now'];
$level_now=$_POST['level_now'];
$is_tution=$_POST['is_tution'];
$is_religious=$_POST['is_religious'];
$is_temple=$_POST['is_temple'];
	
	$bf1=$_POST['bf1'];
	$bf2=$_POST['bf2'];
	$is_bf1_reg=$_POST['is_bf1_reg'];
	$is_bf2_reg=$_POST['is_bf2_reg'];
	

$q1="update child_education  set was_gng_to_school_tsunami={$is_school_tsunami}
,school_name_tsunami='{$snm_tsunami}',level_tsunami='{$level_tsunami}',
why_tsunami='{$why_tsunami}',is_gng_to_school_now='{$is_school_now}',
school_name_now='{$snm_now}',level_now='{$level_now}',why_now='{$why_now}',is_gng_tution={$is_tution},
is_gng_religious_school={$is_religious},is_gng_templ={$is_temple},best_friend_1='{$bf1}',best_friend_2='{$bf2}'
,is_bf1_regd={$is_bf1_reg},is_bf2_regd={$is_bf2_reg} where p_uuid={$puuid} ";


$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child Family Educational details   of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child relation </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildeducation&seq=disp'>
View All EducationalDetails</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_education f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childeducation= Array();

$childeducation[$j++]=$res->fields[5];//
$childeducation[$j++]=$res->fields[6];//
$childeducation[$j++]=($res->fields[7]==1)?'1':'';//
$childeducation[$j++]=$res->fields[8];//
$childeducation[$j++]=$res->fields[9];//
$childeducation[$j++]=$res->fields[10];//

$childeducation[$j++]=($res->fields[11]==1)?'1':'';//
$childeducation[$j++]=$res->fields[12];//
$childeducation[$j++]=$res->fields[13];//
$childeducation[$j++]=$res->fields[14];//
$childeducation[$j++]=($res->fields[15]==1)?'1':'';//
$childeducation[$j++]=($res->fields[16]==1)?'1':'';//
$childeducation[$j++]=($res->fields[17]==1)?'1':'';//
$childeducation[$j++]=$res->fields[18];//
$childeducation[$j++]=$res->fields[19];//
$childeducation[$j++]=($res->fields[20]==1)?'1':'';//
$childeducation[$j++]=($res->fields[21]==1)?'1':'';//




//$childrelationdata[$j++]=$res->fields[13];//profession
if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}
//print 'rcds r'.count($childfamilydata);

return $childeducation;

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
$query1="select * from person_uuid p,child_education f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_education pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_education pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_education pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_education pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_education pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_education pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_education pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_education pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childeducation[$i][$j++]=$res1->fields[5];//childcode
$childeducation[$i][$j++]=$res1->fields[6];//center_code
$childeducation[$i][$j++]=($res1->fields[7]==1)?'Yes':'No';//gng to school b4 tsunami
$childeducation[$i][$j++]=$res1->fields[8];//school name
$childeducation[$i][$j++]=$res1->fields[9];//level
$childeducation[$i][$j++]=$res1->fields[10];//why
$childeducation[$i][$j++]=($res1->fields[11]==1)?'Yes':'No';//school now
$childeducation[$i][$j++]=$res1->fields[12];//name
$childeducation[$i][$j++]=$res1->fields[13];//level
$childeducation[$i][$j++]=$res1->fields[14];//why
$childeducation[$i][$j++]=$res1->fields[15];//tution
$childeducation[$i][$j++]=$res1->fields[16];//religious school
$childeducation[$i][$j++]=$res1->fields[17];//temple
$childeducation[$i][$j++]=$res1->fields[18];//bf1
$childeducation[$i][$j++]=$res1->fields[19];//bf2


$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childeducation']=$childeducation;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
