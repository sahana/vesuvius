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




$q1=(($_POST['q1']==1)?'Yes':'No');
$q2=(($_POST['q2']==1)?'Yes':'No');
$q3=(($_POST['q3']==1)?'Yes':'No');
$q4=(($_POST['q4']==1)?'Yes':'No');
$q5=(($_POST['q5']==1)?'Yes':'No');
$q6=(($_POST['q6']==1)?'Yes':'No');
$q7=(($_POST['q7']==1)?'Yes':'No');
$other=$_POST['other'];

$text="1=$puuid&2=$opt_child_center_names&3=$q1&4=$q2&5=$q3
&6=$q4&7=$q5&8=$q6&9=$q7&10=$other";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_properties.php?<?php print $text?>">View in Excel to Print</a>
<?php
}


function _shn_cps_search_edt_frm()
{
?><h2 align="center">Edit Existing Child Property</h2>
<?php

shn_form_fopen("edtchildproperties");
shn_form_fsopen("Edit Child Properties");
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
<h2>Update Existing ChildProperty</h2>

<?php
	
$module = $global['module'];
$child_code=$_POST['child_code'];
$first_name=$_POST['first_name'];
$last_name=$_POST['last_name'];
$family_name=$_POST['family_name'];


$recordCount=  _shn_cps_get_session($child_code,$first_name,$last_name,$family_name);

$childproperties=$_SESSION['childproperties'];

if($recordCount>0)
{
shn_form_fopen("edtchildproperties",null);
shn_form_fsopen('Child Property');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>Beating Child</th><th>SexualAbuse</th><th>Neglecting child</th>
<th>ChildTraficing</th><th>Domestic violence</th><th>Edit</th><th>Delete</th>

<?php 

for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childproperties[$k][0] ?></td><td><?php print  $childproperties[$k][1] ?></td>
<td><?php print  $childproperties[$k][2] ?></td><td><?php print  $childproperties[$k][3] ?></td>
<td><?php print  $childproperties[$k][4] ?></td><td><?php print  $childproperties[$k][5] ?></td>
<td><?php print  $childproperties[$k][6] ?></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildproperties&seq=cedt<?php print $childproperties[$k][0]?>' >Edit</a></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildproperties&seq=cdel<?php print $childproperties[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childproperties[$k][0]?>')">Delete</a></td></tr>
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
<h2>Update Existing Child's Properties</h2>

<?php
	

 $childproperties =_shn_cps_get_childdata($id);
$val=count(_shn_cps_get_childdata($id));
	
if($val==10)
{

   //-----------------------------------------
  shn_form_fopen("edtchildproperties",null,array('enctype'=>'enctype="multipart/form-data"'));
shn_form_hidden(array('seq'=>'chck'));    
shn_form_fsopen('Child Properties');
	
        $cc=$_SESSION['child_code'];
        shn_form_text('Child Code','cc','size="30"',array('value'=>$childproperties[0]));
        shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childproperties[1]));
        shn_form_label('Does the child','');
        
        
	        print "<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seem to be a beating child?','q1','',array('value'=>$childproperties[2]));
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of a sexualabuse?','q2','',$childproperties[3]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seems to be a neglecting child?','q3','',$childproperties[4]);

 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of child trafficcing?','q4','',$childproperties[5]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of domestic violence?','q5','',$childproperties[6]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Drink Alcohol?','q6','',$childproperties[7]);
 print"<br/><br/>";
 	shn_form_select(array('1'=>'Yes','0'=>'No'),'Need TDH follow up?','q7','',$childproperties[8]);
 print"<br/><br/>";
 shn_form_textarea('Other Details','other','',array('value'=>$childproperties[9]));
	shn_form_fsclose();
shn_form_submit('Update');
?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
shn_form_close();
}

else 
print 'Record Deleted by another user for child code  '.$id.' Please insert the details using left navigation menu';
   
}


function _shn_cps_cdel_childproperties($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_properties where p_uuid={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  properties  of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildproperties&seq=disp'>
View All Child properties</a>
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
//$_SESSION['child_code']=$puuid;
$opt_child_center_names=$_POST['opt_child_center_names'];
//$_SESSION['center_name']=$opt_child_center_names;



$q1=$_POST['q1'];
$q2=$_POST['q2'];
$q3=$_POST['q3'];
$q4=$_POST['q4'];
$q5=$_POST['q5'];
$q6=$_POST['q6'];
$q7=$_POST['q7'];
	$other=$_POST['other'];
//todo complete the query isuru 2006-04-23 9PM-done
$q1="update child_properties set beating={$q1},sexual_abuse={$q2},neglecting={$q3},
child_trafficing={$q4},domestic_violence={$q5},drink_alcohol={$q6},tdh_followup={$q7},other='{$other}'
where p_uuid={$puuid} ";

//child_trafficing,domestic_violence,drink_alcohol,tdh_followup
 

$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child Properties of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child property information </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildproperties&seq=disp'>
View All Properties Details</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_properties f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childproperties= Array();
$childproperties[$j++]=$res->fields[5];//
$childproperties[$j++]=$res->fields[6];//
$childproperties[$j++]=($res->fields[7]==1)?'1':'';//
$childproperties[$j++]=($res->fields[8]==1)?'1':'';//
$childproperties[$j++]=($res->fields[9]==1)?'1':'';//
$childproperties[$j++]=($res->fields[10]==1)?'1':'';//
$childproperties[$j++]=($res->fields[11]==1)?'1':'';//
$childproperties[$j++]=($res->fields[12]==1)?'1':'';//
$childproperties[$j++]=($res->fields[13]==1)?'1':'';//
$childproperties[$j++]=$res->fields[14];
if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}

return $childproperties;

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
$query1="select * from person_uuid p,child_properties f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_properties pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_properties pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_properties pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_properties pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_properties pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_properties pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_properties pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_properties pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childproperties[$i][$j++]=$res1->fields[5];//childcode
$childproperties[$i][$j++]=$res1->fields[6];//center_code
$childproperties[$i][$j++]=($res1->fields[7]==1)?'Yes':'No';//
$childproperties[$i][$j++]=($res1->fields[8]==1)?'Yes':'No';//
$childproperties[$i][$j++]=($res1->fields[9]==1)?'Yes':'No';//
$childproperties[$i][$j++]=($res1->fields[10]==1)?'Yes':'No';//
$childproperties[$i][$j++]=($res1->fields[11]==1)?'Yes':'No';//

$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childproperties']=$childproperties;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
