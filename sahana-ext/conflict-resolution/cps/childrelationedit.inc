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
$_SESSION['child_code']=$puuid;
//print $puuid;

$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$opt_relationship_type=$_POST['opt_relationship_type'];
$opt_relationship_type=get_option_description($opt_relationship_type);

$nm=$_POST['nm'];
$age=$_POST['age'];
$prf=$_POST['prf'];
$lvwith=$_POST['lvwith'];
if($lvwith==1)
$lvwith=='Yes';
else
$lvwith='No';

$lv=$_POST['lv'];
if($lv==1)
$lv==Yes;
else
$lv=No;

//print $lvwith;
$lcn=$_POST['lcn'];
$is_incen=$_POST['is_incen'];
if($is_incen==1)
$is_incen=='Yes';
else
$is_incen='No';


$is_reg_in_school=$_POST['is_reg_in_school'];
if($is_reg_in_school==1)
$is_reg_in_school=='Yes';
else
$is_reg_in_school='No';



$is_off_foster=$_POST['is_off_foster'];
if($is_off_foster==1)
$is_off_foster=='Yes';
else
$is_off_foster='No';

	
if($age==null)
$age=-1;
if($age==0)
$age="";

$is_died=$_POST['is_died'];


$is_missing=$_POST['is_missing'];

$text="1=$puuid&2=$opt_child_center_names&3=$opt_relationship_type&4=$nm&5=$age
&6=$prf&7=$lvwith&8=$lv&9=$lcn&10=$is_incen&11=$is_reg_in_school&12=$is_off_foster&13=$age
&14=$is_died&15=$is_missing";

//print $is_died;
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/child_relation_print.php?<?php print $text?>">View in Excel to Print</a>
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
?><h2 align="center">Edit Existing Child Relational Data</h2>
<?php

shn_form_fopen("edtchildrelation");
shn_form_fsopen("Edit Child Relation Data");
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

$childrelationdata=$_SESSION['childrelationdata'];

if($recordCount>0)
{
shn_form_fopen("edtchildrelation",null);
shn_form_fsopen('Child Relation Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>Relationship to child</th><th>Name</th><th>IsAlive</th><th>Age</th>
<th>isLvgWthChild</th><th>Edit</th><th>Delete</th>

<?php 
for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childrelationdata[$k][1] ?></td><td><?php print  $childrelationdata[$k][2] ?></td><td><?php print  $childrelationdata[$k][3] ?></td><td><?php print  $childrelationdata[$k][4] ?></td><td><?php print  $childrelationdata[$k][5] ?></td><td><?php print  $childrelationdata[$k][6] ?></td><td><?php print  $childrelationdata[$k][7] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildrelation&seq=cedt<?php print $childrelationdata[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildrelation&seq=cdel<?php print $childrelationdata[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childrelationdata[$k][0]?>')">Delete</a></td></tr>
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

//child code validation
$cc=$_POST['cc'];

if(trim($cc)=='' | trim($cc)==null)
{
add_error(_("Please enter the child code..."));
    
$error_flag=true;


}
//age validation
$age=$_POST['age'];
//$age=$_POST['age'];

if($age!=null)
{
if(!is_numeric($age))
{
add_error(_("Age Should be an Integer"));
    
$error_flag=true;
}
}

	return $error_flag;
}



function  _shn_cps_cedt_showform($errors=false,$id){
	if($errors)
	display_errors();
           
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing Child's Relation Data</h2>

<?php
	

 $childrelationdetails=  _shn_cps_get_childdata($id);
 $_SESSION['id']=$id;
	
if(count($childrelationdetails)==16)
{

   //-----------------------------------------
   shn_form_fopen("edtchildrelation",null);
 
   shn_form_hidden(array('seq'=>'chck'));
    shn_form_fsopen('Child Relation Details');
//$cc=$_POST['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$childrelationdetails[1]));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childrelationdetails[2]));    
shn_form_opt_select('opt_relationship_type','RelationshiptoChild','',array('value'=>$childrelationdetails[3]));
shn_form_text('Name','nm','size="30"',array('value'=>$childrelationdetails[4]));
shn_form_text('Age','age','size="30"',array('value'=>$childrelationdetails[6]));
shn_form_text('Profession','prf','size="30"',array('value'=>$childrelationdetails[8]));
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Alive','lv','',$childrelationdetails[5]);
  ?>
  <br/>
  <?php
	  shn_form_select(array('1'=>'Yes','0'=>'No'),'Is living with child','lvwith','',$childrelationdetails[7]);
 ?>
 <br/>
 <?php
 shn_form_textarea('Address if not living with child','lcn','size="30"',array('value'=>$childrelationdetails[9]));
 shn_form_select(array('1'=>'Yes','0'=>'No'),'Is in Center','is_incen','',$childrelationdetails[10]);
?>
<br/>
<?php

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is registered in School','is_reg_in_school','',$childrelationdetails[11]);
?>
<br/>
<?php
shn_form_select(array('1'=>'Yes','0'=>'No'),'Is Official fostering','is_off_foster','',$childrelationdetails[12]);
    print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Died in Tsunami','is_died','',$childrelationdetails[13]);
 print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is Reported Missing','is_missing','',$childrelationdetails[14]);
 print '<br/>';
shn_form_textarea('Reason to Living with child','reason','size="30"',array('value'=>$childrelationdetails[15]));
 
    shn_form_fsclose();
    shn_form_submit('Update');
    ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?
    shn_form_fclose();
 }

else 
print 'Record Deleted by another user for child code  '.$child_code.' Please insert the details using left navigation menu';
   
}

function _shn_cps_cdel_childrelation($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_family_data where id={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  Details of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildrelation&seq=disp'>
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
$id=$_SESSION['id'];
print 'id is'.$id;
$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;
//print $puuid;

$opt_child_center_names=$_POST['opt_child_center_names'];

$opt_relationship_type=$_POST['opt_relationship_type'];
$nm=$_POST['nm'];
$age=$_POST['age'];
$prf=$_POST['prf'];
$lvwith=$_POST['lvwith'];
$lv=$_POST['lv'];
print $lvwith;
$lcn=$_POST['lcn'];
$is_incen=$_POST['is_incen'];
$is_reg_in_school=$_POST['is_reg_in_school'];
$is_off_foster=$_POST['is_off_foster'];
$is_died=$_POST['is_died'];
$is_missing=$_POST['is_missing'];
if($age==null)
$age=-1;
$reason=$_POST['reason'];
$q1="update child_family_data  set relationship_to_child='{$opt_relationship_type}',center_code='{$opt_child_center_names}'
,relation_name='{$nm}',relation_is_alive={$lv},relation_age={$age},relation_is_living_with_child={$lvwith},
relation_profession='{$prf}',relation_location='{$lcn}',relation_is_incenter={$is_incen},
relation_is_registeredinschool={$is_reg_in_school},relation_is_official_fostering={$is_off_foster}
,died_in_tsunami={$is_died},is_reported_missing={$is_missing},reason_to_livewith='{$reason}'   where id={$id} ";


$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child relation details of Details of <?=$p_uuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child relation </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildrelation&seq=disp'>
View All Relations</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];


$query1="select * from person_uuid p,child_family_data f where p.p_uuid=f.p_uuid and f.id={$id}";
$recordCount=0;
	$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childrelationdata= Array();

$childrelationdata[$j++]=$res->fields[5];//id
$childrelationdata[$j++]=$res->fields[6];//child_code
$childrelationdata[$j++]=$res->fields[7];//center_code
$childrelationdata[$j++]=$res->fields[8];//relationship
$childrelationdata[$j++]=$res->fields[9];//relationname
$childrelationdata[$j++]=($res->fields[10]==1)?'1':'';//isalive

$childrelationdata[$j++]=$res->fields[11];//age
$childrelationdata[$j++]=($res->fields[12]==1)?'1':'';//islivingwithchild
$childrelationdata[$j++]=$res->fields[13];//profession
$childrelationdata[$j++]=$res->fields[14];//location
$childrelationdata[$j++]=($res->fields[15]==1)?'1':'';//isincenter
$childrelationdata[$j++]=($res->fields[16]==1)?'1':'';//isreginschool
$childrelationdata[$j++]=($res->fields[17]==1)?'1':'';//isofficialfostering
$childrelationdata[$j++]=($res->fields[18]==1)?'1':'';//isofficialfostering
$childrelationdata[$j++]=($res->fields[19]==1)?'1':'';//isofficialfostering
$childrelationdata[$j++]=$res->fields[20];
if($res==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $childrelationdata;

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
$query1="select * from person_uuid p,child_family_data f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_family_data pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_family_data pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_data pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_family_data pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_data pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_data pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_family_data pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_family_data pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}
$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childrelationdata[$i][$j++]=$res1->fields[5];//key
//print '<br><br>data is'.$childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[6];//child_code
//print '<br><br>data is'.$childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[7];//center_code
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[8];//relationshp
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[9];//relation name
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=($res1->fields[10]==1?'Yes':'No');//isalive
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[11];//age
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=($res1->fields[12]==1?'Yes':'No');//islivingwithchild
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[13];//profession
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=$res1->fields[14];//location
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=($res1->fields[15]==1?'Yes':'No');//is_in_center
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=($res1->fields[16]==1?'Yes':'No');//is_registered in school
//print $childrelationdata[$i][$j-1].'<br>';
$childrelationdata[$i][$j++]=($res1->fields[17]==1?'Yes':'No');//is off fostering
//print $childrelationdata[$i][$j-1].'<br>';
$i++;
$j=0;
$res1->MoveNext();
}


				
$_SESSION['childrelationdata']=$childrelationdata;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
