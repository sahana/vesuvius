<?php
/* $Id; */

/**Update functions for  CR
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

global $editid;
function _shn_cr_cedt_start($errors=false){
	if($errors)
		display_errors();
	global $global;
	$db = $global['db'];
?>
<h2>Update Existing Camp</h2>
<?php
	$query="select c_uuid from camp where name='{$_POST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields[0];
	$_SESSION['editid']=$editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(ecmp);
	shn_form_fsopen("General Details");
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_text("Camp Name","camp_name",'size="50"',array('req'=>true,'value'=>$_SESSION['camp_name']));
	shn_form_opt_select("opt_camp_type","Camp Type",array('value'=>$_SESSION['opt_camp_type']));
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
	shn_form_textarea("Address","camp_address",array('value'=>$_SESSION['camp_address']));
	shn_form_fsclose();
	shn_form_fsopen("Contact Person Details");
	shn_form_text("Full Name","camp_contact_name",'size="60"',array('value'=>$_SESSION['camp_contact_name']));
	shn_form_text("Phone Number","camp_contact_number",'size="60"',array('value'=>$_SESSION['camp_contact_number']));
	shn_form_fsclose();
	shn_form_fsopen("Camp Population");
	shn_form_text("Family Count","family",'size="10"',array('value'=>$_SESSION['camp_family']));
	shn_form_text("Total Count","total",'size="10"',array('value'=>$_SESSION['camp_total']));
	shn_form_text("Men","men",'size="10"',array('value'=>$_SESSION['camp_men']));
	shn_form_text("Women","women",'size="10"',array('value'=>$_SESSION['camp_women']));
	shn_form_text("Children","children",'size="10"',array('value'=>$_SESSION['camp_children']));
	shn_form_fsclose();
	shn_form_submit("Next");
	shn_form_fclose();
}

function _shn_cr_cedt_chk($errors=false){
if($errors)
	display_errors;
	
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
shn_form_fopen(ecmp);
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

function _shn_cr_search_edt_frm(){
?><h2 align="center">Edit Existing Camp</h2><?php
	shn_form_fopen("ecmp");
	shn_form_fsopen("Edit Camp");
	shn_form_hidden(array('seq'=>'disp'));
	shn_form_text('Name of Camp to edit','cmp_id','size="20"');
	shn_form_fsclose();
	shn_form_submit("Edit");
	shn_form_fclose();
	
													

}

function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


	if(null == ($_POST['camp_name'])){
			add_error(_("Please Enter the Camp Name"));
			$error_flag=true;
	}
	//echo $_POST['family'];
	if(!(null == ($_POST['family']))){
		if(!is_numeric(trim($_POST['family']))){
			add_error(_("The Familiy Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['total']))){
		if(!is_numeric(trim($_POST['total']))){
			add_error(_("The Total Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['men']))){
		if(!is_numeric(trim($_POST['men']))){
			add_error(_("The Men Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['women']))){
		if(!is_numeric(trim($_POST['women']))){
			add_error(_("The Women Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['children']))){
		if(!is_numeric(trim($_POST['children']))){
			add_error(_("The Children Count is not a valid number"));
			$error_flag=true;
		}
	}
	

	
	return $error_flag;
}


/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
*/
function _shn_cr_get_session($camp_id){
	global $global;
	$db = $global['db'];
	
	$query="select a.name,a.location_id,a.opt_camp_type,a.address,contact_name,contact_no,family,total,men,women,children from camp a left outer join camp_reg b on a.c_uuid=b.c_uuid where a.c_uuid=$camp_id";
	
	$res = $db->Execute($query);

	$_SESSION['camp_name']=$res->fields['name'];
	$_SESSION['opt_camp_type']=$res->fields['opt_camp_type'];
	$_SESSION['opt_location_type']=$res->fields['location_id'];
	$_SESSION['camp_address']=$res->fields['address'];
	$_SESSION['camp_contact_name']=$res->fields['contact_name'];
	$_SESSION['camp_contact_number']=$res->fields['contact_no'];
	$_SESSION['camp_family']=$res->fields['family'];
	$_SESSION['camp_men']=$res->fields['men'];
	$_SESSION['camp_women']=$res->fields['women'];
	$_SESSION['camp_children']=$res->fields['children'];
	$_SESSION['camp_total']=$res->fields['total'];
											
}


function _shn_cr_cedt_commit(){
//insert to database;
global $global;
global $editid;
$db = $global['db'];

//call unique camp id
//$uid=_shn_cr_create_cid();
//enter into camp table
$q="update camp set name='{$_SESSION['camp_name']}',location_id='{$_SESSION['opt_location_type']}',opt_camp_type='{$_SESSION['opt_camp_type']}',address='{$_SESSION['camp_address']}' where c_uuid='{$_SESSION['editid']}'";


$res = $db->Execute($q);

//enter into camp_reg table
$q="update camp_reg set name='{$_SESSION['camp_name']}',contact_name='{$_SESSION['camp_contact_name']}',contact_no='{$_SESSION['camp_contact_number']}',comments='{$_SESSION['camp_comments']}',men='{$_SESSION['camp_men']}',women='{$_SESSION['camp_women']}',family='{$_SESSION['camp_family']}',children='{$_SESSION['camp_children']}',total='{$_SESSION['camp_total']}' where c_uuid='{$_SESSION['editid']}'";

$res = $db->Execute($q);

/*insert services into camp_services table
//currently add checked values.
*/								
	foreach($_SESSION['opt_camp_service'] as $a => $b){
	//currently add checked values.
		//$q = "update camp_services(c_uuid,opt_camp_service,value) values($editid,'{$b}',1)";
	$res = $db->Execute($q);
	}
?>
<h2>You Have Succesfully Registered "<?=$_SESSION['camp_name']?>"</h2>
<!--<h3>You Have Succesfully Registered <?=$_SESSION['camp_name']?></h3><br>-->
<br>
<br>
<h3>The availability of Services & Facilities of the camp are as follows.</h3>
<!--<p>Facilities / Services Availability</p>-->
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
		echo "<li class=\"fontspecial\">$name : NOT AVAILABLE </li><br>";
	}
	
	$ref->MoveNext();
}

?>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue</p>
<?php	
}
?>

