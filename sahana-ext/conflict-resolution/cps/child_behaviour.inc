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



function _shn_cps_cadd_start($errors=false){
	
if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Child Behaviour</h2>
<?php  
    if($errors)
        display_errors();

shn_form_fopen("achildbehaviour",null,array('enctype'=>'enctype="multipart/form-data"'));

   
    shn_form_hidden(array('seq'=>'chk'));    
 
	
	shn_form_fsopen('Childs Behaviour');
        $cc=$_SESSION['child_code'];
        shn_form_text('Child Code','cc','size="30"',array('value'=>$cc));
        shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name']));
        shn_form_text('Spontaneous answer given by:','answered_by','size="30"');
        
        
	shn_form_label('Since the tsunami, have there been changes in the childs behaviour and emotions?','');
        print "<br/><br/>";
	shn_form_label('Does the child ?','');
	print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Have difficulty leaving the house, the family or the caregiver, and or/clings to the mother/caregiver?
','q1');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Have more problems in concentrating or remembering, for example in school homework?         ','q18');
 print"<br/><br/>";	
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Have more sleep difficulties than before, such as getting to sleep or sudden awakenings?
','q3');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of having lost his /her  appetite and eats less than before?
','q2');


 print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Have recurrent dreams or nightmares which refer to the tsunami?
','q5');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show more difficulty in controlling emotions, such as getting upset, angry? ','q7');
 print"<br/><br/>";	


	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being more afraid of strangers than before ?
','q4');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Is  afraid of another tsunami and  talks about it frequently?;','q9');
 print"<br/><br/>";	

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being  less interested in education and future life?
','q6');
 print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Never want to talk about  it and avoid everything  places or situations that remind him/her of it?
','q11');
 print"<br/><br/>";

shn_form_select(array('1'=>'Yes','0'=>'No'),'Show signs of being  more aggressive than before, both with caregivers and family members, or at school?
','q8');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seem more withdrawn or shy than before?  ','q13');
 print"<br/><br/>";


shn_form_select(array('1'=>'Yes','0'=>'No'),'Often cry and look sad?
','q10');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Often seem distracted, dreamy or deep in thoughts?
','q15');

print"<br/><br/>";
 
	shn_form_select(array('1'=>'Yes','0'=>'No'),'When playing or drawing, act out his/her experience of the tsunami?
','q12');
 print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Say he/she has pictures of his / her tsunami experience coming suddenly in the mind ?
','q16');
 print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seek more attention from adults caring for him / her? 
','q17');
 print"<br/><br/>";

//	shn_form_select(array('1'=>'Yes','0'=>'No'),'Avoid talking or thinking about the tsunami, or avoid places and situations that remind him/her of the tsunami?
//','q14');
 print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the family or the child received support since the tsunami from a professional counsellor for these problems?  ','q19');
 print"<br/><br/>";
	shn_form_textarea('If Yes From who ?','who');
 print"<br/><br/>";
 shn_form_opt_select("opt_behaviourimp","Have you noticed any improvement after that?");
//	shn_form_select(array('1'=>'Yes','0'=>'No','-1'=>'NotRelavant'),'Have you noticed any improvement after that?      ','q20');

 print"<br/><br/>";
	shn_form_fsclose();
shn_form_submit('Insert');
?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
shn_form_close();
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
if(trim($cc)==null | trim($cc)=='')
{
add_error(_("Please  enter the child code"));
$error_flag=true;
}
return $error_flag;
}

function _shn_cps_cadd_commit_db(){

global $global;
$db = $global['db'];
$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;
$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;


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



//enter into person_uuid table
$q1="insert into child_behaviour values({$puuid},'{$opt_child_center_names}','{$answered_by}',{$q1},{$q2},{$q3},{$q4},{$q5},{$q6},{$q7},{$q8},{$q9},{$q10},{$q11},{$q12},{$q13},{$q14},{$q15},{$q16},{$q17},{$q18},{$q19},{$q20},'{$who}')";




$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();

print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the behaviour for child  code"<?=$_SESSION['child_code']?>"</h2>
<ul>
<li><a href="index.php?mod=cps&act=achildproperties">AddChildProperties</a></li>

</ul>
<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

