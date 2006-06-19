<?php
/* $Id; */

/**Child library for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.htmlAdd Chil
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


function _shn_cps_cadd_start($errors=false){
	
if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Child Properties</h2>
<?php  
    if($errors)
        display_errors();
shn_form_fopen("achildproperties",null,array('enctype'=>'enctype="multipart/form-data"'));
shn_form_hidden(array('seq'=>'chk'));    
shn_form_fsopen('Child Properties');
	
        $cc=$_SESSION['child_code'];
        shn_form_text('Child Code','cc','size="30"',array('value'=>$cc));
    shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
		    shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name']));
        shn_form_label('Does the child','');
        
        
	        print "<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seem to be a beating child?','q1');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of a sexualabuse?','q2');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Seems to be a neglecting child?','q3');

 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of child trafficcing?','q4');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Victim of domestic violence?','q5');
 print"<br/><br/>";
	shn_form_select(array('1'=>'Yes','0'=>'No'),'Drink Alcohol?','q6');
 print"<br/><br/>";
 	shn_form_select(array('1'=>'Yes','0'=>'No'),'Need TDH follow up?','q7');
 print"<br/><br/>";
 shn_form_textarea('Other Details','other');
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



$q1=$_POST['q1'];
$q2=$_POST['q2'];
$q3=$_POST['q3'];
$q4=$_POST['q4'];
$q5=$_POST['q5'];
$q6=$_POST['q6'];
$q7=$_POST['q7'];

$other=$_POST['other'];
//enter into person_uuid table
$q1="insert into child_properties values({$puuid},'{$opt_child_center_names}',{$q1},{$q2},{$q3},{$q4},{$q5},{$q6},{$q7},'{$other}')";




$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();

print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the properties for child  code"<?=$_SESSION['child_code']?>"</h2>
<ul>
<li><a href="index.php?mod=cps&act=achildpersonal">AddPersonalData</a></li>

</ul>
<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

