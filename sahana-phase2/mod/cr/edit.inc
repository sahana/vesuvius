<?php
/* $Id: edit.inc,v 1.21 2007-03-15 11:25:19 mifanc Exp $ */

/**Update functions for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @subpackage cr
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @edited by Isuru Samaraweera <isuru@opensource.lk>
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
<h2><?php echo _("Update Existing Shelter")?></h2>
<?php
	$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields['c_uuid'];
	$_SESSION['editid']=$editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(ecmp);
	shn_form_fsopen(_("General Details"));
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_text(_("Shelter Name"),"camp_name",'size="50"',array('req'=>true,'value'=>$_SESSION['camp_name']));
	shn_form_opt_select("opt_camp_type",_("Shelter Type"),null,array('value'=>$_SESSION['opt_camp_type']));
	shn_form_textarea(_("Address"),"camp_address",null,array('value'=>$_SESSION['camp_address']));
	shn_form_fsclose();
?>
<!--
<label>Division</label>
<select name="opt_location_type" >-->
<?php
// Display selected Division type only
/*
	$q="select value from config where confkey='division_type' && module_id='cr'";
	//$q ="select option_description from field_options where field_name='cr_pref_div'";
	$ref = $db->Execute($q);
		$val=$ref->fields[0];
	$q ="select location_id,name from location where opt_location_type=$val";
	$ref = $db->Execute($q);
	while(!$ref->EOF){	
		$val=$ref->fields[0];
		$name=$ref->fields[1];
*/
?>
<!--
<option value='<?=$val?>'><?=$name?></option>-->
<?php
/*
		$ref->MoveNext();
	}
*/
?>
<!--</select><br>-->
<?php

	global $global;
	include $global['approot']."/inc/lib_location.inc";
	$range=array("start"=>1,"end"=>5);
	//shn_location_form_org($range);
	//shn_location_form_org($range,$_SESSION['opt_location_type']);
	shn_location_form(1,5,$_SESSION['opt_location_type']);	
			
//-----------------------------------------
	shn_form_fsopen(_("Contact Person Details"));
	shn_form_text(_("Full Name"),"camp_contact_name",'size="60"',array('value'=>$_SESSION['camp_contact_name']));
	shn_form_text(_("Phone Number"),"camp_contact_number",'size="60"',array('value'=>$_SESSION['camp_contact_number']));
	shn_form_fsclose();
	shn_form_fsopen(_("Shelter Population"));
	shn_form_text(_("Infected Count"),"family",'size="10"',array('value'=>$_SESSION['camp_family']));
	shn_form_text(_("Total Count"),"total",'size="10"',array('value'=>$_SESSION['camp_total']));
 shn_form_text(_("Capacity"),"capacity",'size="10"',array('value'=>$_SESSION['camp_capacity']));

	shn_form_text(_("Men"),"men",'size="10"',array('value'=>$_SESSION['camp_men']));
	shn_form_text(_("Women"),"women",'size="10"',array('value'=>$_SESSION['camp_women']));
	shn_form_text(_("Children"),"children",'size="10"',array('value'=>$_SESSION['camp_children']));
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}


function shn_cr_all_view(){
	
?>
<script type="text/javascript">
	function editThis(){
		var x=window.confirm("Do You Really Want to Delete?")
		if (x)
		return true;
		else
		return false;
	}
</script>
<?php
	global $global;
	$db = $global['db'];
?>
<h2><?=_("Shelter Details")?></h2>
<?php
	$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields[0];
	$_SESSION['editid']=$editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(crch);
	shn_form_fsopen(_("General Details"));
	shn_form_hidden(array('seq'=>'show'));
	//shn_form_hidden(array('cmp_id'=>$_REQUEST['cmp_id']));
	shn_form_hidden(array('opt_camp_type'=>$_SESSION['opt_camp_type']));
	
	shn_form_label(_("Shelter Name"),$_SESSION['camp_name'],array('br'=>'true'));
	shn_form_label(_("Shelter Type"),$_SESSION['opt_camp_type'],array('br'=>'true'));
?>
<!--
<label>Division</label>
<select name="opt_location_type" >-->
<?php
// Display selected Division type only
/*
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
*/
?>
<!--</select><br>-->
<?php
	
	global $global;
	include $global['approot']."/mod/or/lib_or.inc";
		
//-----------------------------------------
	shn_form_label(_("Address"),$_SESSION['camp_address']);


	//Starts
	        $i = 1  - 1;
					while( $i < 5 ) {
					$i++;
					  $sql = " SELECT location.name , field_options.option_description FROM location ".
				           " INNER JOIN field_options ON field_options.option_code = location.opt_location_type " .
				           " WHERE location.opt_location_type = '$i' AND " .
				           " location.loc_uuid = '{$_SESSION['opt_location_type']}' ";
																																																											                $result = $global['db']->GetRow($sql);
																																																																			                shn_form_label($result['option_description'] , $result['name']);
																																																												
																																																												}
																																																																																					    //Ends
																																																																																					
		
	shn_form_fsclose();
	//shn_location_form_view(1,4,$_SESSION['opt_location_type']);
	shn_form_fsopen(_("Contact Person Details"));
	shn_form_label(_("Full Name"),$_SESSION['camp_contact_name']);
	shn_form_label(_("Phone Number"),$_SESSION['camp_contact_number']);
	shn_form_fsclose();
	shn_form_fsopen(_("Shelter Population"));
	shn_form_label(_("Infected Count"),$_SESSION['camp_family']);
	shn_form_label(_("Total Count"),$_SESSION['camp_total']);
 shn_form_label(_("Capacity"),$_SESSION['camp_capacity']);

	shn_form_label(_("Men"),$_SESSION['camp_men']);
	shn_form_label(_("Women"),$_SESSION['camp_women']);
	shn_form_label(_("Children"),$_SESSION['camp_children']);
	shn_form_fsclose();
	shn_form_submit(_("Close"));
?>
	<input type="button" onClick="location.replace('index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $_REQUEST['cmp_id']?>');" value="Edit Camp" />
	<input type="button" onClick="if(editThis()) location.replace('index.php?mod=cr&act=ecmp&seq=del&cmp_id=<?php echo $_SESSION['editid']?>');" value="Delete Camp" />
<?php
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

 $_SESSION['camp_capacity']=$_POST['capacity'];

	$_SESSION['camp_men']=$_POST['men'];
	$_SESSION['camp_women']=$_POST['women'];
	$_SESSION['camp_children']=$_POST['children'];
	$_SESSION['camp_total']=$_POST['total'];
	$_SESSION['cr_1']=$_POST['1'];
	$_SESSION['cr_2']=$_POST['2'];
	$_SESSION['cr_3']=$_POST['3'];
	$_SESSION['cr_4']=$_POST['4'];
	$_SESSION['cr_5']=$_POST['5'];
							
	//var_dump($_SESSION);
?>
<h2><?=("Shelter Checklist")?></h2>
<?php
shn_form_fopen(ecmp);
shn_form_fsopen(_("Services / Facilities Available"));
shn_form_hidden(array('seq'=>'commit'));
shn_form_opt_checkbox("opt_camp_service");
shn_form_textarea(_("Other Facilities"),"comments");
shn_form_fsclose();
shn_form_submit(_("Next"));
shn_form_fclose();

}

function _shn_cr_del_camp($id){
	global $global;
	$db=$global['db'];
	$q="delete from camp_general where c_uuid='{$id}'";
	$r="delete from camp_reg where c_uuid='{$id}'";
	$s="delete from camp_services where c_uuid='{$id}'";
	$db->Execute($q);
	$db->Execute($r);
	$db->Execute($s);
	add_confirmation("Deleted Shelter Succesfully");
	//shn_cr_crch
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
?><h2 align="center">Edit Existing Shelter</h2><?php
	shn_form_fopen("ecmp");
	shn_form_fsopen(_("Edit Shelter"));
	shn_form_hidden(array('seq'=>'disp'));
	shn_form_text(_("Name of Shelter to edit"),'cmp_id','size="20"');
	shn_form_fsclose();
	shn_form_submit(_("Edit"));
	shn_form_fclose();
	
}
function shn_cr_edt_srch(){
	global $global;
	include($global['approot'].'/mod/cr/search.inc');
	_shn_cr_srch(true);

}


function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


	if(null == ($_POST['camp_name'])){
			add_error(_("Please Enter the Shelter  Name"));
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


  if(!(null == ($_POST['capacity']))){
                if(!is_numeric(trim($_POST['capacity']))){
                        add_error(_("The Capacity is not a valid number"));
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
	
	$query="select a.name,a.location_id,a.opt_camp_type,a.address,admin_name,admin_no,family,total,men,women,children,capacity from camp_general a left outer join camp_reg b on a.c_uuid=b.c_uuid where a.c_uuid='{$camp_id}'";
	
	$res = $db->Execute($query);

	$_SESSION['camp_name']=$res->fields['name'];
	$_SESSION['opt_camp_type']=$res->fields['opt_camp_type'];
	$_SESSION['opt_location_type']=$res->fields['location_id'];
	$_SESSION['camp_address']=$res->fields['address'];
	$_SESSION['camp_contact_name']=$res->fields['admin_name'];
	$_SESSION['camp_contact_number']=$res->fields['admin_no'];
	$_SESSION['camp_family']=$res->fields['family'];
	$_SESSION['camp_men']=$res->fields['men'];
	$_SESSION['camp_women']=$res->fields['women'];
	$_SESSION['camp_children']=$res->fields['children'];
	$_SESSION['camp_total']=$res->fields['total'];

 $_SESSION['camp_capacity']=$res->fields['capacity'];
											
}
function _shn_cr_get_locid(){
	if($_SESSION['cr_5']!=null)
    return $_SESSION['cr_5'];
  else if($_SESSION['cr_4']!=null)
		return $_SESSION['cr_4'];
	else if($_SESSION['cr_3']!=null)
	  return $_SESSION['cr_3'];
	else if($_SESSION['cr_2']!=null)
	  return $_SESSION['cr_2'];
	else
	  return $_SESSION['cr_1'];
}

function _shn_cr_cedt_commit(){
//insert to database;
global $global;
global $editid;
$db = $global['db'];

$loc_id=_shn_cr_get_locid();
//call unique camp id
//$uid=_shn_cr_create_cid();
//enter into camp table
$q="update camp_general set name='{$_SESSION['camp_name']}',location_id='{$loc_id}',opt_camp_type='{$_SESSION['opt_camp_type']}',address='{$_SESSION['camp_address']}',capacity={$_SESSION['camp_capacity']} where c_uuid='{$_SESSION['editid']}'";


$res = $db->Execute($q);
//enter into camp_reg table
$q="update camp_reg set admin_name='{$_SESSION['camp_contact_name']}',admin_no='{$_SESSION['camp_contact_number']}',men='{$_SESSION['camp_men']}',women='{$_SESSION['camp_women']}',family={$_SESSION['camp_family']},children='{$_SESSION['camp_children']}',total={$_SESSION['camp_total']} where c_uuid='{$_SESSION['editid']}'";

$res = $db->Execute($q);

/*insert services into camp_services table
//currently add checked values								
	foreach($_SESSION['opt_camp_service'] as $a => $b){
	//currently add checked values.
		//$q = "update camp_services(c_uuid,opt_camp_service,value) values($editid,'{$b}',1)";
	$res = $db->Execute($q);
	}
*/
?>

<h2><? add_confirmation(_("You Have Succesfully Edited shelter {$_SESSION[camp_name]}"));?></h2>
<br>
<h3><?=_("The availability of Services & Facilities of the shelter are as follows")?></h3>

<ul>

<!--To have the results shown in table format-->
<div id ="result">
<table>
        <thead>
        		<td><?php echo _("Service Type")?></td>
            <td><?php echo _("Availability")?></td>
        </thead>
        
<tbody>
<tr>

<?php
$a="select option_code,option_description from field_options where field_name='opt_camp_service'";
$ref=$db->Execute($a);
while(!$ref->EOF){
	$val=$ref->fields[0];
	$name=$ref->fields[1];
	$flag=false;
	if(isset($_SESSION['opt_camp_service'])){
	 foreach($_SESSION['opt_camp_service'] as $a => $b){
		if($val==$b){
			echo "<td>$name</td>";
    		echo "<td>". _("Available"). "</td>";
    		echo "<br>";
		}
	 }
	}
	if(!$flag){
		echo "<td>$name</td>";
		echo "<td>"._("NOT AVAILABLE")."</td>";
		echo "<br>";
	}
	?>
	</tr>
	<?php
	$ref->MoveNext();
}

?>

</tbody>
</table>
</div>

</ul>
<br><br>
<p><?php echo _("Use the Navigation Menu to Continue")?></p>
<?php	
}
?>

