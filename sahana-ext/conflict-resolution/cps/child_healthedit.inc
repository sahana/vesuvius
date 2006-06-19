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
//$_SESSION['child_code']=$puuid;
$opt_child_center_names=$_POST['opt_child_center_names'];
//$_SESSION['center_name']=$opt_child_center_names;
$question1=(($_POST['question1']==1)?'Yes':'No');
$q1explain=$_POST['q1explain'];

$question2=(($_POST['question1']==2)?'Yes':'No');
$q2explain=$_POST['q2explain'];

$question3=(($_POST['question3']==1)?'Yes':'No');
$q3explain=$_POST['q3explain'];


$question4=(($_POST['question4']==1)?'Yes':'No');
$question5=(($_POST['question5']==1)?'Yes':'No');
$question6=(($_POST['question6']==1)?'Yes':'No');
$question7=(($_POST['question7']==1)?'Yes':'No');
$question8=(($_POST['question8']==1)?'Yes':'No');
$question9=(($_POST['question9']==1)?'Yes':'No');
$question10=(($_POST['question10']==1)?'Yes':'No');
$question11=(($_POST['question11']==1)?'Yes':'No');
$q11explain=$_POST['q11explain'];
$question12=(($_POST['question12']==1)?'Yes':'No');
$q12explain=$_POST['q12explain'];
$question13=(($_POST['question13']==1)?'Yes':'No');
$q13explain=$_POST['q13explain'];

$question14=(($_POST['question14']==1)?'Yes':'No');	
$q14explain=$_POST['q14explain'];



$text="1=$puuid&2=$opt_child_center_names&3=$question1&4=$q1explain&5=$question2
&6=$q2explain&7=$question3&8=$q3explain&9=$question4&10=$question5&11=$question6&12=$question7&13=$question8&14=$question9&15=$question10
&16=$question11&17=$q11explain&18=$question12&19=$q12explain&20=$question13&21=$q13explain
&22=$question14&23=$q14explain";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_health.php?<?php print $text?>">View in Excel to Print</a>
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
?><h2 align="center">Edit Existing Child Health Status</h2>
<?php

shn_form_fopen("edtchildhealth");
shn_form_fsopen("Edit Child Health Status");
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

$childhealth=$_SESSION['childhealth'];

if($recordCount>0)
{
shn_form_fopen("edtchildhealth",null);
shn_form_fsopen('Child Health Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>IsDisbled</th><th>ReceivedAssistance</th><th>PhysicallyAffected</th>
<th>HealthAffected</th><th>HasHeadache</th><th>Edit</th><th>Delete</th>

<?php 

for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childhealth[$k][0] ?></td><td><?php print  $childhealth[$k][1] ?></td>
<td><?php print  $childhealth[$k][2] ?></td><td><?php print  $childhealth[$k][3] ?></td>
<td><?php print  $childhealth[$k][4] ?></td><td><?php print  $childhealth[$k][5] ?></td>
<td><?php print  $childhealth[$k][6] ?></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildhealth&seq=cedt<?php print $childhealth[$k][0]?>' >Edit</a></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildhealth&seq=cdel<?php print $childhealth[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childhealth[$k][0]?>')">Delete</a></td></tr>
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
<h2>Update Existing Child's Health Details</h2>

<?php
	
//todo by isuru
 $childhealth= _shn_cps_get_childdata($id);
$val=count(_shn_cps_get_childdata($id));
	
if($val==25)
{

   //-----------------------------------------
   shn_form_fopen("edtchildhealth",null);
 
shn_form_hidden(array('seq'=>'chck'));
shn_form_fsopen('Child Health Details');
//$cc=$_POST['child_code'];
shn_form_text('Child Code','cc','size="30"',array('req'=>true,'value'=>$childhealth[0]));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childhealth[1])); 
shn_form_select(array('1'=>'Yes','0'=>'No'),'Does the child show any disability (mental or physical)? ','question1','',$childhealth[2]);
print"<br/><br/>";

	shn_form_textarea('Explain in Detail','q1explain','',array('value'=>$childhealth[3]));
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child received any specific assistance or support for that? (Special school, artificial limb...)','question2','',$childhealth[4]);
print"<br/><br/>";
shn_form_textarea('Explain in Detail','q2explain','',array('value'=>$childhealth[5]));
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been physically affected by the tsunami?','question3','',$childhealth[6]);
print"<br/><br/>";

	shn_form_textarea('Explain in detail','q3explain','',array('value'=>$childhealth[7]));
print"<br/><br/>";
	
 shn_form_label('Does child have physical problems?  ','');

//print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),' Headaches','question4','',$childhealth[10]);
print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Nausea, feels sick','question5','',$childhealth[11]);
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Eye problems (not if corrected by glasses).','question6','',$childhealth[12]);
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Rashes or other skin problems','question7','',$childhealth[13]);
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Aches and pains (not stomach or headaches)','question8','',$childhealth[14]);
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),' Vomiting, throwing up','question9','',$childhealth[15]);
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been seen by a doctor since the tsunami','question10','',$childhealth[16]);
print"<br/><br/>";
 	shn_form_label('Before Tsunami Incident','');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Did the child suffer from any chronic disease?','question11','',$childhealth[17]);
print"<br/><br/>";
shn_form_textarea('Explain in detail','q11explain','',array('value'=>$childhealth[18]));
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Had the child been seriously ill or injured in the last 12months?','question12','',$childhealth[19]);
print"<br/><br/>";
shn_form_textarea('Explain in detail','q12explain','',array('value'=>$childhealth[20]));
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been operated in the last 12 months?','question13','',$childhealth[21]);
print"<br/><br/>";

shn_form_textarea('Explain in detail','q13explain','',array('value'=>$childhealth[22]));
print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'At Present Child health is still affected?','question14','',array('value'=>$childhealth[23]));
print"<br/><br/>";
shn_form_textarea('Explain in detail','q14explain','',array('value'=>$childhealth[24]));
	shn_form_fsclose();
shn_form_submit('Update');
?>
     <input type=submit size=30 name="print"  value="Print"/>
    <?
shn_form_close();
}

else 
print 'Record Deleted by another user for child code  '.$id.' Please insert the details using left navigation menu';
   
}


function _shn_cps_cdel_childhealth($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_health where p_uuid={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  healthddetails  of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildeducation&seq=disp'>
View All Child Health Details</a>
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

$opt_child_center_names=$_POST['opt_child_center_names'];
$question1=$_POST['question1'];
$q1explain=$_POST['q1explain'];

$question2=$_POST['question2'];
$q2explain=$_POST['q2explain'];

$question3=$_POST['question3'];
$q3explain=$_POST['q3explain'];


$question4=$_POST['question4'];
$question5=$_POST['question5'];
$question6=$_POST['question6'];
$question7=$_POST['question7'];
$question8=$_POST['question8'];
$question9=$_POST['question9'];
$question10=$_POST['question10'];
$question11=$_POST['question11'];
$q11explain=$_POST['q11explain'];
$question12=$_POST['question12'];
$q12explain=$_POST['q12explain'];
$question13=$_POST['question13'];
$q13explain=$_POST['q13explain'];
	$question14=$_POST['question14'];
	$q14explain=$_POST['q14explain'];
//todo complete the query isuru 2006-04-23 9PM
$q1="update child_health set is_disabled={$question1},
disability_explanation='{$q1explain}',is_received_assistance={$question2},
assistance_explanation='{$q2explain}',is_physically_affected={$question3},
physically_affected_explanation='{$q3explain}',has_headache={$question4},
has_nausea={$question5},has_eye_problems={$question6},has_rashes_or_skin_problems={$question7}
,has_aches_or_panes={$question8},has_vomiting={$question9},
has_seen_by_doctor={$question10},is_suffered_from_chronic_disease_before_disaster={$question11}
, chronic_disease_explanation='{$q11explain}',
 has_child_been_seriouly_injured_before_disaster={$question12},injured_explanation='{$q12explain}'
 ,has_child_been_operated_last12months={$question13},operation_explanation='{$q13explain}'
 ,at_present_still_effected={$question14},affected_explain='{$q14explain}' where p_uuid={$puuid} ";




$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child Family Health details   of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child health information </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildhealth&seq=disp'>
View All Health Details</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_health f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childhealth= Array();

$childhealth[$j++]=$res->fields[5];//
$childhealth[$j++]=$res->fields[6];//
$childhealth[$j++]=($res->fields[7]==1)?'1':'';//
$childhealth[$j++]=$res->fields[8];//
$childhealth[$j++]=($res->fields[9]==1)?'1':'';//
$childhealth[$j++]=$res->fields[10];//


$childhealth[$j++]=($res->fields[11]==1)?'1':'';//
$childhealth[$j++]=$res->fields[12];//
$childhealth[$j++]=($res->fields[13]==1)?'1':'';//
$childhealth[$j++]=($res->fields[14]==1)?'1':'';//
$childhealth[$j++]=($res->fields[15]==1)?'1':'';//
$childhealth[$j++]=($res->fields[16]==1)?'1':'';//
$childhealth[$j++]=($res->fields[17]==1)?'1':'';//
$childhealth[$j++]=($res->fields[18]==1)?'1':'';//
$childhealth[$j++]=($res->fields[19]==1)?'1':'';//
$childhealth[$j++]=($res->fields[20]==1)?'1':'';//
$childhealth[$j++]=$res->fields[21]==1?'1':'';

$childhealth[$j++]=($res->fields[22]==1)?'1':'';//
$childhealth[$j++]=$res->fields[23];
$childhealth[$j++]=($res->fields[24]==1)?'1':'';//
$childhealth[$j++]=$res->fields[25];
$childhealth[$j++]=($res->fields[26]==1)?'1':'';//
$childhealth[$j++]=$res->fields[27];
$childhealth[$j++]=($res->fields[28]==1)?'1':'';
$childhealth[$j++]=$res->fields[29];


//$childrelationdata[$j++]=$res->fields[13];//profession
if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}
//print 'rcds r'.count($childfamilydata);

return $childhealth;

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
$query1="select * from person_uuid p,child_health f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_health pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_health pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_health pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_health pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_health pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_health pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_health pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_health pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childhealth[$i][$j++]=$res1->fields[5];//childcode
$childhealth[$i][$j++]=$res1->fields[6];//center_code
$childhealth[$i][$j++]=($res1->fields[7]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[9]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[11]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[13]==1)?'Yes':'No';//
$childhealth[$i][$j++]=($res1->fields[15]==1)?'Yes':'No';//
/*$childhealth[$i][$j++]=$res1->fields[12];//name
$childhealth[$i][$j++]=$res1->fields[13];//level
$childhealth[$i][$j++]=$res1->fields[14];//why
$childhealth[$i][$j++]=$res1->fields[15];//tution
$childhealth[$i][$j++]=$res1->fields[16];//religious school
$childhealth[$i][$j++]=$res1->fields[17];//temple
$childhealth[$i][$j++]=$res1->fields[18];//temple
$childhealth[$i][$j++]=$res1->fields[19];//temple
$childhealth[$i][$j++]=$res1->fields[20];//temple
$childhealth[$i][$j++]=$res1->fields[21];//temple
$childhealth[$i][$j++]=$res1->fields[22];//temple
$childhealth[$i][$j++]=$res1->fields[23];//temple
$childhealth[$i][$j++]=$res1->fields[24];//temple
$childhealth[$i][$j++]=$res1->fields[25];//temple
$childhealth[$i][$j++]=$res1->fields[26];//temple
*/
$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childhealth']=$childhealth;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
