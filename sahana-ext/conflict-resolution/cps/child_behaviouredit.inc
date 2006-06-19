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


$answered_by=$_POST['answered_by'];
$who=$_POST['who'];
$q1=(($_POST['q1']==1)?'Yes':'No');
$q2=(($_POST['q2']==1)?'Yes':'No');
$q3=(($_POST['q3']==1)?'Yes':'No');
$q4=(($_POST['q4']==1)?'Yes':'No');
$q5=(($_POST['q5']==1)?'Yes':'No');
$q6=(($_POST['q6']==1)?'Yes':'No');
$q7=(($_POST['q7']==1)?'Yes':'No');
$q8=(($_POST['q8']==1)?'Yes':'No');
$q9=(($_POST['q9']==1)?'Yes':'No');
$q10=(($_POST['q10']==1)?'Yes':'No');
$q11=(($_POST['q11']==1)?'Yes':'No');
$q12=(($_POST['q12']==1)?'Yes':'No');
$q13=(($_POST['q13']==1)?'Yes':'No');
$q14='1';
$q15=(($_POST['q15']==1)?'Yes':'No');
$q16=(($_POST['q16']==1)?'Yes':'No');
$q17=(($_POST['q17']==1)?'Yes':'No');
$q18=(($_POST['q18']==1)?'Yes':'No');
$q19=(($_POST['q19']==1)?'Yes':'No');
$q20=$_POST['opt_behaviourimp'];
if($q20=='0')
$q20='No';
else if($q20=='1')
$q20='Yes';
else 
$q20='NotRelavant';

$text="1=$puuid&2=$opt_child_center_names&3=$answered_by&4=$q1&5=$q2
&6=$q3&7=$q4&8=$q5&9=$q6&10=$q7&11=$q8&12=$q9&13=$q10&14=$q11&15=$q12
&16=$q13&17=$q15&18=$q16&19=$q17&20=$q18&21=$q19
&22=$q20&23=$who";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_behaviour.php?<?php print $text?>">View in Excel to Print</a>
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
?><h2 align="center">Edit Existing Child Behaviour</h2>
<?php

shn_form_fopen("edtchildbehaviour");
shn_form_fsopen("Edit Child Behaviour");
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
<h2>Update Existing ChildBehaviour</h2>

<?php
	
$module = $global['module'];
$child_code=$_POST['child_code'];
$first_name=$_POST['first_name'];
$last_name=$_POST['last_name'];
$family_name=$_POST['family_name'];


$recordCount=  _shn_cps_get_session($child_code,$first_name,$last_name,$family_name);

$childbehaviour=$_SESSION['childbehaviour'];

if($recordCount>0)
{
shn_form_fopen("edtchilbehaviour",null);
shn_form_fsopen('Child Behaviour Details');
   
?>	
<table border="1" width=100% scrolling=true>
<th>ChildCode</th><th>CenterCode</th><th>AnswergvnBy</th><th>DiffiCultyInlvg</th><th>Lost appettite</th>
<th>HaveSleepdifficulties</th><th>BeAfraid</th><th>Edit</th><th>Delete</th>

<?php 

for($k=0;$k<$recordCount;$k++)
{
?>
<tr><td ><?php print $childbehaviour[$k][0] ?></td><td><?php print  $childbehaviour[$k][1] ?></td>
<td><?php print  $childbehaviour[$k][2] ?></td><td><?php print  $childbehaviour[$k][3] ?></td>
<td><?php print  $childbehaviour[$k][4] ?></td><td><?php print  $childbehaviour[$k][5] ?></td>
<td><?php print  $childbehaviour[$k][6] ?></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildbehaviour&seq=cedt<?php print $childbehaviour[$k][0]?>' >Edit</a></td>
<td><a href='index.php?mod=<?php print $module ?>&act=edtchildbehaviour&seq=cdel<?php print $childbehaviour[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $child[$k][0]?>')">Delete</a></td></tr>
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
<h2>Update Existing Child's Behaviour Details</h2>

<?php
	
//todo by isuru
 $childbehaviour= _shn_cps_get_childdata($id);
$val=count(_shn_cps_get_childdata($id));
	
if($val==23)
{

   //-----------------------------------------
   shn_form_fopen("edtchildbehaviour",null);
 
shn_form_hidden(array('seq'=>'chck'));
shn_form_fsopen('Child Behaviour');
//$cc=$_POST['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$id));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$childbehaviour[1]));
shn_form_text('Spontaneous answer given by:','answered_by','size="30"',array('value'=>$childbehaviour[2]));
        
	shn_form_label('Since the tsunami, have there been changes in the childs behaviour and emotions?','');
        print "<br/><br/>";
	shn_form_label('Does the child ?','');
	print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Have difficulty leaving the house, the family or the caregiver, and or/clings to the mother/caregiver?
','q1','',$childbehaviour[3]);
 print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Have more problems in concentrating or remembering, for example in school homework?         ','q18','',$childbehaviour[20]);
 print"<br/><br/>";	
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Have more sleep difficulties than before, such as getting to sleep or sudden awakenings?
','q3','',$childbehaviour[5]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of having lost his /her  appetite and eats less than before?
','q2','',$childbehaviour[4]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Have recurrent dreams or nightmares which refer to the tsunami?
','q5','',$childbehaviour[7]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show more difficulty in controlling emotions, such as getting upset, angry? ','q7','',$childbehaviour[9]);
 print"<br/><br/>";	
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being more afraid of strangers than before ?
','q4','',$childbehaviour[6]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Is  afraid of another tsunami and  talks about it frequently?;','q9','',$childbehaviour[11]);
 print"<br/><br/>";	
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being  less interested in education and future life?
','q6','',$childbehaviour[8]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Never want to talk about  it and avoid everything  places or situations that remind him/her of it?
','q11','',$childbehaviour[13]);
 print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being  more aggressive than before, both with caregivers and family members, or at school?
','q8','',$childbehaviour[10]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seem more withdrawn or shy than before?  ','q13','',$childbehaviour[15]);
 print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Often cry and look sad?
','q10','',$childbehaviour[12]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Often seem distracted, dreamy or deep in thoughts?
','q15','',$childbehaviour[17]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'When playing or drawing, act out his/her experience of the tsunami?
','q12','',$childbehaviour[14]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Say he/she has pictures of his / her tsunami experience coming suddenly in the mind ?
','q16','',$childbehaviour[18]);
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seek more attention from adults caring for him / her? 
','q17','',$childbehaviour[19]);
print"<br/><br/>";
//shn_form_select(array('1'=>'Yes','0'=>'No'),'Avoid talking or thinking about the tsunami, or avoid places and situations that remind him/her of the tsunami?
//','q14','',$childbehaviour[16]);
 
 print"<br/><br/>";

shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the family or the child received support since the tsunami from a professional counsellor for these problems?  ','q19','',$childbehaviour[21]);
 print"<br/><br/>";
	shn_form_textarea('If Yes From who ?','who','',array('value'=>$childbehaviour[23]));
 print"<br/><br/>";
	shn_form_opt_select("opt_behaviourimp","Have you noticed any improvement after that?",'',array('value'=>$childbehaviour[22]));
 print"<br/><br/>";
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


function _shn_cps_cdel_childbehaviour($code)
{
global $global;
$module = $global['module'];
$db = $global['db'];

$q1="delete from child_behaviour where p_uuid={$code}";
$res1 = $db->Execute($q1);

if($res1==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else
{
?>
<h2>You Have Succesfully  deleted the  behaviour details  of"<?=$code?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildbehaviour&seq=disp'>
View All Child Behaviour Details</a>
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


$answered_by=$_POST['answered_by'];
$who=$_POST['who'];
$q1=$_POST['q1'];
$q2=$_POST['q2'];
$q3=$_POST['q3'];
$q4=$_POST['q4'];
$q5=$_POST['q5'];
$q6=$_POST['q6'];
$q7=$_POST['q7'];
$q8=$_POST['q8'];
$q9=$_POST['q9'];
$q10=$_POST['q10'];
$q11=$_POST['q11'];
$q12=$_POST['q12'];
$q13=$_POST['q13'];
$q14='1';
$q15=$_POST['q15'];
$q16=$_POST['q16'];
$q17=$_POST['q17'];
$q18=$_POST['q18'];
$q19=$_POST['q19'];
$q20=$_POST['opt_behaviourimp'];


	
//
$q1="update child_behaviour set spontanious_answer_given_by='{$answered_by}',
 question1={$q1},question2={$q2},question3={$q3},question4={$q4},question5={$q5},
 question6={$q6}, question7={$q7},question8={$q8},question9={$q9},question10={$q10}
,question11={$q11},question12={$q12},question13={$q13},question14={$q14},question15={$q15},question16={$q16}
,question17={$q17},question18={$q18},question19={$q19},question20={$q20},councellor_name='{$who}'
 where p_uuid={$puuid}  ";


$res1=$db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
print 'error1 is'.$result1;
}

if($res1==true)
{

?>
<h2>You Have Succesfully Updated Child Behaviour details   of <?=$puuid?></h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child behaviour information </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildbehaviour&seq=disp'>
View All Behaviour Details</a>

<?php	
}
}


function _shn_cps_get_childdata($id)
{
	global $global;
	$db = $global['db'];
$query1="select * from person_uuid p,child_behaviour f where p.p_uuid=f.p_uuid and f.p_uuid={$id}";
$recordCount=0;
$res = $db->Execute($query1);
$recordCount=$res->RecordCount();
$j=0;
$childbehaviour= Array();

$childbehaaviour[$j++]=$res->fields[5];//
$childbehaviour[$j++]=$res->fields[6];//
$childbehaviour[$j++]=$res->fields[7];//
$childbehaviour[$j++]=($res->fields[8]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[9]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[10]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[11]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[12]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[13]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[14]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[15]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[16]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[17]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[18]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[19]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[20]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[21]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[22]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[23]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[24]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[25]==1)?'1':'';//
$childbehaviour[$j++]=($res->fields[26]==1)?'1':'';//
$childbehaviour[$j++]=$res->fields[27];


//print $childbehaviour[$j];


//$childbehaviour[$j++]=($res->fields[27]==1)?'1':($res->fields[27]==-1)?'-1':'';//
$childbehaviour[$j++]=$res->fields[28];//




//$childrelationdata[$j++]=$res->fields[13];//profession
if($res==false)
print 'error is'.$resulti;
{
$resulti=$db->ErrorMsg();
}

return $childbehaviour;

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
$query1="select * from person_uuid p,child_behaviour f where p.p_uuid=f.p_uuid";

/* and p.local_name like '%{$first_name}%' and p.full_name like '%{$last_name}%' and p.family_name like '%{$family_name}%'";
*/
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_behaviour pd  where   pd.p_uuid=p.p_uuid  and p.l10n_name like '%{$first_name}%'";/* and p.full_name like '%{$last_name}%' 
*/
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name==null | $family_name==''))
{
$query1="select * from person_uuid p,child_behaviour pd where   pd.p_uuid=p.p_uuid  and p.full_name like '%{$last_name}%'";/* and p.full_name like '%{$last_name}%' */
}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_behaviour pd where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%'";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code!=null ) & ($first_name==null | first_name=='')&($last_name==null | $last_name=='') &($family_name==null)| ($family_name==''))
{

$query1="select * from person_uuid p,child_behaviour pd where pd.p_uuid=p.p_uuid  and p.p_uuid={$child_code}";/* and p.full_name like '%{$last_name}%' */

}

else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_behaviour pd  where  pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name==null | $last_name=='') &($family_name!=null))
{
$query1="select * from person_uuid p,child_behaviour pd  where pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.l10n_name like '%{$first_name}%' ";

}
else if(($child_code==null | $child_code=='') & ($first_name!=null)&($last_name!=null) &($family_name==null|$family_name==''))
{
$query1="select * from person_uuid p,child_behaviour pd  where   pd.p_uuid=p.p_uuid  and p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%' and p.l10n_name like '%{$first_name}%' ";

}

else if(($child_code==null | $child_code=='') & ($first_name==null | first_name=='')&($last_name!=null) &($family_name!=null))
{
$query1="select * from person_uuid p,child_behaviour pd  where  p.family_name like '%{$family_name}%' and  p.full_name like '%{$last_name}%'";

}$i=0;
$j=0;
$res1 = $db->Execute($query1);


$record_count=$res1->RecordCount();


while(!$res1->EOF)
{
$childbehaviour[$i][$j++]=$res1->fields[5];//childcode
$childbehaviour[$i][$j++]=$res1->fields[6];//center_code
$childbehaviour[$i][$j++]=$res1->fields[7];
$childbehaviour[$i][$j++]=($res1->fields[8]==1)?'Yes':'No';//
$childbehaviour[$i][$j++]=($res1->fields[9]==1)?'Yes':'No';//
$childbehaviour[$i][$j++]=($res1->fields[10]==1)?'Yes':'No';//
$childbehaviour[$i][$j++]=($res1->fields[11]==1)?'Yes':'No';//


$i++;
$j=0;
$res1->MoveNext();
}
$_SESSION['childbehaviour']=$childbehaviour;

if($res1==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $record_count;
}




?>
