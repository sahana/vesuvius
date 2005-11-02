<?php
/* $Id; */

/**Camp library for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_cr_cadd_start(){
	global $global;
	$db = $global['db'];
?>
<h2>Register New Camp</h2>
<?php
	shn_form_fopen(acmp);
	shn_form_fsopen("General Details");
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_text("Camp Name","camp_name",'size="60"');
	shn_form_opt_select("opt_camp_type","Camp Type");
?>
<label>Division</label>
<select name="opt_location_type" >
<?php
// Display selected Division type only
	$q="select value from config where confkey='division_type' && module_id='cr'";
	//$q ="select option_description from field_options where field_name='cr_pref_div'";
	$ref = $db->Execute($q);
		$val=$ref->fields[0];
	$q ="select location_id,name from location where opt_location_type=$val";
	$ref = $db->Execute($q);
	while(!$ref->EOF){	
		$val=$ref->fields[0];
		$name=$ref->fields[1];
?>
<option value='<?=$val?>'><?=$name?></option>
<?php
		$ref->MoveNext();
	}
?>
</select><br>
<?php
			
//-----------------------------------------
	shn_form_textarea("Address","camp_address");
	shn_form_fsclose();
	shn_form_fsopen("Contact Person Details");
	shn_form_text("Full Name","camp_contact_name",'size="60"');
	shn_form_text("Phone Number","camp_contact_number",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen("Camp Population");
	shn_form_text("Family Count","family",'size="10"');
	shn_form_text("Total Count","total",'size="10"');
	shn_form_text("Men","men",'size="10"');
	shn_form_text("Women","women",'size="10"');
	shn_form_text("Children","children",'size="10"');
	shn_form_fsclose();
	shn_form_submit("Next");
	shn_form_fclose();
}

function _shn_cr_cadd_chk(){
	global $global;
	$_SESSION['camp_name']=$_POST['camp_name'];
	$_SESSION['opt_camp_type']=$_POST['opt_camp_type'];
	$_SESSION['opt_location_type']=$_POST['opt_location_type'];
	$_SESSION['camp_address']=$_POST['camp_address'];
	$_SESSION['camp_contact_name']=$_POST['camp_contact_name'];
	$_SESSION['camp_contact_number']=$_POST['camp_contact_number'];
	$_SESSION['camp_family']=$_POST['family'];
	$_SESSION['camp_men']=$_POST['men'];
	$_SESSION['camp_women']=$_POST['women'];
	$_SESSION['camp_children']=$_POST['children'];
	$_SESSION['camp_total']=$_POST['total'];
	//var_dump($_SESSION);
?>
<h2>Camp Checklist</h2>
<?php
shn_form_fopen(acmp);
shn_form_fsopen("Services / Facilities Available");
shn_form_hidden(array('seq'=>'commit'));
shn_form_opt_checkbox("opt_camp_service");
shn_form_textarea("Other Facilities","comments");
shn_form_fsclose();
shn_form_submit("Next");
shn_form_fclose();

}

function _shn_cr_cadd_commit(){
global $global;
//write to database
$_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
$_SESSION['camp_comments']=$_POST['comments'];
foreach($_SESSION['opt_camp_service'] as $a=>$b){
//echo "value is $b";
}
//echo microtime(true);
//var_dump($_SESSION);
_shn_cr_cadd_commit_db();
}

function _shn_cr_create_cid(){
//create unique camp id
//db->GenID();
$id=time();
return $id;

}

function _shn_cr_cadd_commit_db(){
//insert to database;
global $global;
$db = $global['db'];

//call unique camp id
$uid=_shn_cr_create_cid();

//enter into camp table
$q="insert into camp(c_uuid,name,location_id,opt_camp_type,address) values($uid,'{$_SESSION['camp_name']}','{$_SESSION['opt_location_type']}','{$_SESSION['opt_camp_type']}','{$_SESSION['camp_address']}')";


//$res = $db->Execute($q);

//enter into camp_reg table
$q="insert into camp_reg(c_uuid,name,orgid,contact_name,contact_no,comments,services,men,women,family,children,total) values($uid,'{$_SESSION['camp_name']}','orgid','{$_SESSION['camp_contact_name']}','{$_SESSION['camp_contact_number']}','{$_SESSION['camp_comments']}','ser','{$_SESSION['camp_men']}','{$_SESSION['camp_women']}','{$_SESSION['camp_family']}','{$_SESSION['camp_children']}','{$_SESSION['camp_total']}')";

//$res = $db->Execute($q);

/*insert services into camp_services table
//currently add checked values.
@todo:  handle unchecked values
*/								
	foreach($_SESSION['opt_camp_service'] as $a => $b){
	//currently add checked values.
	//@todo:	handle unchecked values
		$q = "insert into camp_services(c_uuid,opt_camp_service,value) values($uid,'{$b}',1)";
	//$res = $db->Execute($q);
	}
?>
<h3>You Have Succesfully Registered <?=$_SESSION['camp_name']?></h3><br>
<h4>Facilities / Services Availability</h4><br>
<ul>



<?php
$a="select option_code,option_description from field_options where field_name='opt_camp_service'";
$ref=$db->Execute($a);
while(!$ref->EOF){
	$val=$ref->fields[0];
	$name=$ref->fields[1];
	$flag=false;
	foreach($_SESSION['opt_camp_service'] as $a => $b){
		if($val==$b){
			echo "<li>$name :  Available </li><br>";
			$flag=true;
		}
	}
	if(!$flag){
		echo "<li>$name : NOT AVAILABLE </li><br>";
	}
	
	$ref->MoveNext();
}

?>
</ul>
<p>Use the Navigation Menu to Continue</p>
<?php	
}
?>

