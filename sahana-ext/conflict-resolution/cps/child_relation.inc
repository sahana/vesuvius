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
$_SESSION['child_code']=$puuid;
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


function _shn_cps_cadd_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];

?>
<h2 align="center">Child Relation Details</h2>
<?php  
    if($errors)
    display_errors();
    shn_form_fopen("achildrelation",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'chk'));    
    shn_form_fsopen('Relation');
   
$cc=$_SESSION['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$cc));
shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));



shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name']));    
shn_form_opt_select('opt_relationship_type','RelationshiptoChild');

    shn_form_text('Name','nm','size="30"');
    shn_form_text('Age','age','size="30"');
    shn_form_text('Profession','prf','size="30"');
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Alive','lv');
     print '<br/>';
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Is living with child','lvwith');
  print '<br/>';
 shn_form_textarea('Address if not living with child','lcn','size="30"');
    shn_form_select(array('1'=>'Yes','0'=>'No'),'Is in Center','is_incen');
     print '<br/>';
shn_form_select(array('1'=>'Yes','0'=>'No'),'Is registered in School','is_reg_in_school');
 print '<br/>';
shn_form_select(array('1'=>'Yes','0'=>'No'),'Is Official fostering','is_off_foster');
 print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Died in Tsunami','is_died');
 print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is Reported Missing','is_missing');
  print '<br/>';
 shn_form_textarea('Reason to Living with child','reason','size="30"');
    
    shn_form_fsclose();
    shn_form_submit('Insert');
    ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
    shn_form_fclose();
   
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
//child code validation
$cc=$_POST['cc'];

if(trim($cc)=='' | trim($cc)==null)
{
add_error(_("Please enter the child code..."));
    
$error_flag=true;


}
//age validation
$age=$_POST['age'];

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

function _shn_cps_cadd_commit_db(){
//insert to database;
global $global;
$db = $global['db'];
$puuid=$_POST['cc'];
$_SESSION['child_code']=$puuid;
//print $puuid;

$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
$opt_relationship_type=$_POST['opt_relationship_type'];
$nm=$_POST['nm'];
$age=$_POST['age'];
$prf=$_POST['prf'];
$lvwith=$_POST['lvwith'];
$lv=$_POST['lv'];
//print $lvwith;
$lcn=$_POST['lcn'];
$is_incen=$_POST['is_incen'];
$is_reg_in_school=$_POST['is_reg_in_school'];
$is_off_foster=$_POST['is_off_foster'];
	$reason=$_POST['reason'];
if($age==null)
$age=-1;

$is_died=$_POST['is_died'];
	$is_missing=$_POST['is_missing'];
//insert into person_uuid table
$q1="insert into child_family_data values('',{$puuid},'{$opt_child_center_names}','{$opt_relationship_type}','{$nm}'
,{$lv},{$age},{$lvwith},'{$prf}','{$lcn}',{$is_incen},{$is_reg_in_school},{$is_off_foster},{$is_died},{$is_missing},'{$reason}')";


$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
//include('errorpage.html');
print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the relation for child  code <?=$puuid?> </h2>
<ul>
<li><a href="index.php?mod=cps&act=achildfstatus">AddChildFamilyStatus</a></li>
</ul>
<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

