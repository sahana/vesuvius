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




function _shn_cps_cadd_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center">Child Educational status</h2>
<?php  
    if($errors)
        display_errors();

shn_form_fopen("achildeducation",null,array('enctype'=>'enctype="multipart/form-data"'));

   
    shn_form_hidden(array('seq'=>'chk'));    
shn_form_fsopen('Educational Details');
$cc=$_SESSION['child_code'];
shn_form_text('Child Code','cc','size="30"',array('value'=>$cc));
shn_form_text('Child Name','','size="30"',array('value'=>$_SESSION['commonname']));
shn_form_opt_select("opt_child_center_names","Center Name",'',array('value'=>$_SESSION['center_name'])); 
shn_form_select(array('1'=>'Yes','0'=>'No'),'Was the Child going to School before tsunami?','is_school_tsunami');
     print '<br/>';
shn_form_text('School Name','snm_tsunami','size="30"');

shn_form_text('Why','why_tsunami','size="30"');

shn_form_text('Level','level_tsunami','size="30"');
    


    shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the Child going to School now?','is_school_now');
     print '<br/>';
		shn_form_text('School Name','snm_now','size="30"');
    shn_form_text('Why','why_now','size="30"');
	  shn_form_text('Level','level_now','size="30"');
  

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to tution now?','is_tution');
 print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to religious school now?','is_religious');
 print '<br/>';

shn_form_select(array('1'=>'Yes','0'=>'No'),'Is the child going to temple or mosque now?','is_temple');
 print '<br/>';
  shn_form_text('Childs Best Friends Name','bf1','size="30"');
 shn_form_select(array('1'=>'Yes','0'=>'No'),'Best Friend registeredin center?','is_bf1_reg');
 print '<br/>';
  shn_form_text('Childs Best Friends Name','bf2','size="30"');
 shn_form_select(array('1'=>'Yes','0'=>'No'),'Best Friend registeredin center?','is_bf2_reg');
 print '<br/>';
    

    shn_form_fsclose();
    shn_form_submit('Insert');
    
    ?>
    <input type=submit size=30 name="print"  value="Print"/>
    <?php
    shn_form_fclose();
   //shn_form_fsclose();
}




function _shn_cps_cadd_commit()
{
//write  to database
_shn_cps_cadd_commit_db();
}



function _shn_cps_validate_error()
{
	clean_errors();
	$error_flag=false;
    
//print($_POST['center']);
//fullname is entered?

$cc=$_POST['cc'];


    //Reporting person name
   if(trim($cc)==null | trim($cc)==''){
        add_error(_("Please enter the child code"));
        $error_flag=true;
    }

   return $error_flag;
}

function _shn_cps_cadd_commit_db(){

global $global;
$db = $global['db'];

$puuid=$_POST['cc'];

$_SESSION['child_code']=$puuid;
$is_school_tsunami=$_POST['is_school_tsunami'];

$opt_child_center_names=$_POST['opt_child_center_names'];
$_SESSION['center_name']=$opt_child_center_names;
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



//enter into person_uuid table
$q1="insert into child_education values({$puuid},'{$opt_child_center_names}',{$is_school_tsunami},'{$snm_tsunami}','{$level_tsunami}'
,'{$why_tsunami}',{$is_school_now},'{$snm_now}','{$level_now}','{$why_now}',{$is_tution},{$is_religious},{$is_temple},
'{$bf1}','{$bf2}',{$is_bf1_reg},{$is_bf2_reg})";

//$q1="insert into child_family_data values({$puuid},'{$rtc}','{$nm}'
//,{$lv},{$age},1,'ee','ff',1,1,1)";

$res1 = $db->Execute($q1);
if($res1==false)
{
$result1=$db->ErrorMsg();
//include('errorpage.html');
print $result1;
}



if($res1==true ){

?>
<h2>You Have Succesfully Registered the Education details for child  code <?=$_SESSION['child_code']?> </h2>


<ul>
<!--<li><a href="index.php?mod=cps&act=achildpersonal">AddPersonalData</a></li>-->
<!--<li><a href="index.php?mod=cps&act=achildrelation">AddChildRelation</a></li>-->
<!--<li><a href="index.php?mod=cps&act=achildfstatus">AddChildFamilyStatus</a></li>-->
<!--<li><a href="index.php?mod=cps&act=achildeducation">AddChildEducation</a></li>-->
<li><a href="index.php?mod=cps&act=achildhealth">AddChildHealth</a></li>
<!--<li><a href="index.php?mod=cps&act=achildbehaviour">AddChildBehaviour</a></li>-->
	<!--<li><a href="index.php?mod=cps&act=achildproperties">AddChildProperties</a></li>-->
</ul>

<br>
<br>
<br><br>
<p>Use the Left Navigation Menu to Continue..............</p>

<?php	
}
}
?>

