<?php
/* $Id; */

/**  CPS
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



function _shn_cps_cadd_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Child Health status</h2>
<?php  
    if($errors)
        display_errors();

shn_form_fopen("achildhealth",null,array('enctype'=>'enctype="multipart/form-data"'));

   
    shn_form_hidden(array('seq'=>'chk'));    
 
	shn_form_fsopen('Childs health  status');

$cc=$_SESSION['child_code'];
shn_form_text('Child Code','cc','size="30"',array('req'=>true,'value'=>$cc));
shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name'])); 
shn_form_select(array('1'=>'Yes','0'=>'No'),'Does the child show any disability (mental or physical)? ','question1');
print"<br/><br/>";

	shn_form_textarea('Explain in Detail','q1explain');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child received any specific assistance or support for that? (Special school, artificial limb...)','question2');
print"<br/><br/>";
shn_form_textarea('Explain in Detail','q2explain');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been physically affected by the tsunami?','question3');
print"<br/><br/>";

	shn_form_textarea('Explain in detail','q3explain');
print"<br/><br/>";
	
 shn_form_label('Does child have physical problems?  ','');

//print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),' Headaches','question4');
print"<br/><br/>";

	shn_form_select(array('1'=>'Yes','0'=>'No'),'Nausea, feels sick','question5');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Eye problems (not if corrected by glasses).','question6');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Rashes or other skin problems','question7');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Aches and pains (not stomach or headaches)','question8');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),' Vomiting, throwing up','question9');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been seen by a doctor since the tsunami','question10');
print"<br/><br/>";
 	shn_form_label('Before Tsunami Incident','');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Did the child suffer from any chronic disease?','question11');
print"<br/><br/>";
shn_form_textarea('Explain in detail','q11explain');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Had the child been seriously ill or injured in the last 12months?','question12');
print"<br/><br/>";
shn_form_textarea('Explain in detail','q12explain');
print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Has the child been operated in the last 12 months?','question13');
print"<br/><br/>";

shn_form_textarea('Explain in detail','q13explain');
print"<br/><br/>";
shn_form_select(array('1'=>'Yes','0'=>'No'),'At Present Child health is still affected?','question14');
print"<br/><br/>";
shn_form_textarea('Explain in detail','q14explain');
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
$_SESSION['child_code']=$puuid;
$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
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


//enter into person_uuid table
$q1="insert into child_health values({$puuid},'{$opt_child_center_names}',{$question1},'{$q1explain}',{$question2}
,'{$q2explain}',{$question3},'{$q3explain}',' ',' ',{$question4},{$question5},{$question6},{$question7},{$question8},{$question9},{$question10},{$question11},'{$q11explain}',{$question12},'{$q12explain}',{$question13},'{$q13explain}',{$question14},'{$q14explain}')";



$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
//include('errorpage.html');
print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the Health details for child  code <?=$_SESSION['child_code']?> </h2>
<ul>
<li><a href="index.php?mod=cps&act=achildbehaviour">AddChildBehaviour</a></li>
</ul>
<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

