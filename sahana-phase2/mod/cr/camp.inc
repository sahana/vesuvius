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

function _shn_cr_cadd_start($errors=false){
	if($errors)
		display_errors();
	global $global;
	$db = $global['db'];
?>
<h2 align="center"><?php echo _("Register New Camp")?></h2>
<?php
	shn_form_fopen(acmp);
	shn_form_fsopen(_("General Details"));
	//check for gis and goto mapping page
	include $global['approot']."/conf/config.inc";
	
	if($conf['gis']=='true'){
		shn_form_hidden(array('seq'=>'gis'));
	}
	else{
		shn_form_hidden(array('seq'=>'chk'));
	}
	
	shn_form_text(_("Camp Name"),"camp_name",'size="50"',array('req'=>true));
	shn_form_opt_select("opt_camp_type",_("Camp Type"));
?>

<!--<label>Division</label>
<select name="opt_location_type" >-->

<?php
/*
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
*/			
//-----------------------------------------
	shn_form_textarea(_("Address"),"camp_address");
	shn_form_fsclose();
//-------------------------
	global $global;
	include $global['approot']."/inc/lib_location.inc";
	$range=array("start"=>1,"end"=>5);
	shn_location_form_org($range);
		
//-------------------------
	shn_form_fsopen(_("Contact Person Details"));
	shn_form_text(_("Full Name"),"camp_contact_name",'size="60"');
	shn_form_text(_("Phone Number"),"camp_contact_number",'size="60"');
	shn_form_text(_("Mobile Number"),"contact_mob",'size="60"');
	shn_form_text(_("Occupation"),"occupation",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen(_("Camp Population"));
	shn_form_text(_("Family Count"),"family",'size="10"');
	shn_form_text(_("Total Count"),"total",'size="10"');
	shn_form_text(_("Men"),"men",'size="10"');
	shn_form_text(_("Women"),"women",'size="10"');
	shn_form_text(_("Children"),"children",'size="10"');
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function _shn_cr_cadd_chk($errors=false){
if($errors)
	display_errors;
	global $global;
	include $global['approot']."/conf/config.inc";
	if($conf['gis']=='false'){
		//add to session if GIS module is not enabled
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
		$_SESSION['contact_mob']=$_POST['contact_mob'];
		$_SESSION['occupation']=$_POST['occupation'];
		
		$_SESSION['cr_1']=$_POST['1'];
		$_SESSION['cr_2']=$_POST['2'];
		$_SESSION['cr_3']=$_POST['3'];
		$_SESSION['cr_4']=$_POST['4'];
		$_SESSION['cr_5']=$_POST['5'];
					
	}
	else{
		if((null==$_POST['gps_x']) && null==$_POST['gps_y']){
			$_SESSION['gis_loc_x']=$_POST['loc_x'];
			$_SESSION['gis_loc_y']=$_POST['loc_y'];
		}
		else{
			$_POST['loc_x'] = $_POST['gps_x'];
			$_POST['loc_y'] = $_POST['gps_y'];
			$_SESSION['gis_loc_x']=$_POST['loc_x'];
			$_SESSION['gis_loc_y']=$_POST['loc_y'];
		}
	}
?>
<h2>Camp Checklist</h2>
<?php
shn_form_fopen(acmp);
shn_form_fsopen(_("Services / Facilities Available"));
shn_form_hidden(array('seq'=>'commit'));
shn_form_opt_checkbox("opt_camp_service");
shn_form_textarea(_("Other Facilities"),"comments");
shn_form_fsclose();
shn_form_submit(_("Next"));
shn_form_fclose();

}

function _shn_cr_cadd_commit(){
global $global;
//write to database
$_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
$_SESSION['camp_comments']=$_POST['comments'];
//foreach($_SESSION['opt_camp_service'] as $a=>$b){
//echo "value is $b";
//}
//echo microtime(true);
//var_dump($_SESSION);
_shn_cr_cadd_commit_db();
}

function _shn_cr_create_cid(){
//create unique camp id
//db->GenID();
$id=time();
sleep(2);
return $id;

}

function _shn_cr_sel_map(){
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
	$_SESSION['cr_1']=$_POST['1'];
	$_SESSION['cr_2']=$_POST['2'];
	$_SESSION['cr_3']=$_POST['3'];
	$_SESSION['cr_4']=$_POST['4'];
	$_SESSION['cr_5']=$_POST['5'];
		$_SESSION['contact_mob']=$_POST['contact_mob'];
		$_SESSION['occupation']=$_POST['occupation'];
											
	shn_form_fopen(acmp);
	shn_form_fsopen(_("Location Information"));
	echo _("Plot the Camp Location OR Enter its GPS coordinates below");
	shn_form_fsclose();
	shn_form_fsopen(_("Plot Location on Map"));
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_hidden(array('loc_x'=>''));
	shn_form_hidden(array('loc_y'=>''));
	global $global;
	$db=$global['db'];
	include $global['approot']."/conf/config.inc";
	echo "<h2>"._("Area Map")."</h2>";

	//if mod_gis
	if($conf['gis']){
	  include $global['approot']."/mod/gis/conf.inc";
	  if($conf['mod_gis']=='google_maps'){
	  	/*
		 	 * google maps
		 	 *@todo check for online connectivity: exit gracefully
	  	*/
	 		include_once $global['approot']."/mod/gis/plugins/google_maps/handler_google_maps.inc";
			echo _("Enter Camp Location. Click on Map where camp exists");

			$a="select value from config where module_id='gis' and confkey='google_key'";
      $ares=$db->Execute($a);
			$keys=$ares->fields[0];

	
			$w="select value from config where module_id='gis' and confkey='center_x'";
			$wres=$db->Execute($w);
			$wkey=$wres->fields[0];

			$e="select value from config where module_id='gis' and confkey='center_y'";
			$eres=$db->Execute($e);
			$ekey=$eres->fields[0];
																		
			init_map($keys);
		}
	}
	else
	{
?>
   <p>No Currently Selected GIS</p> 
<?php
  }
	shn_form_fsclose();
	shn_form_fsopen(_("GPS Coordinates"));
	shn_form_text(_("Northing / Latitude"),"gps_x",'size="60"');
	shn_form_text(_("Easting / Longitude"),"gps_y",'size="60"');
	shn_form_fsclose();
			
	shn_form_submit("Next");
	shn_form_close();
	add_footer();
	load_map($wkey,$ekey);
	add_marker($_POST['camp_name']);
	end_page();
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
			add_error(_("The Family Count is not a valid number"));
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

function _shn_cr_cadd_commit_db(){
//insert to database;
global $global;
$db = $global['db'];

//call unique camp id
$uid=_shn_cr_create_cid();

/*--------Phonetic Insertions------------*/
shn_db_insert_phonetic('camp_name',$uid);
/*---------------------------------------*/

$loc_id=_shn_cr_get_locid();

//create admin id
$puid = _shn_cr_create_cid();

//echo "location is".$loc_id;
//echo "camp is".$uid;

//enter into camp table
$q="insert into camp_general(c_uuid,name,location_id,opt_camp_type,address) values($uid,'{$_SESSION['camp_name']}',$loc_id,'{$_SESSION['opt_camp_type']}','{$_SESSION['camp_address']}')";


$res = $db->Execute($q);

//enter into camp_reg table
//$q="insert into camp_reg(c_uuid,name,orgid,contact_name,contact_no,comments,services,men,women,family,children,total) values($uid,'{$_SESSION['camp_name']}','orgid','{$_SESSION['camp_contact_name']}','{$_SESSION['camp_contact_number']}','{$_SESSION['camp_comments']}','ser','{$_SESSION['camp_men']}','{$_SESSION['camp_women']}','{$_SESSION['camp_family']}','{$_SESSION['camp_children']}','{$_SESSION['camp_total']}')";
$q="insert into camp_reg(c_uuid,admin_name,admin_no,men,women,family,children,total) values($uid,'{$_SESSION['camp_contact_name']}','{$_SESSION['camp_contact_number']}','{$_SESSION['camp_men']}','{$_SESSION['camp_women']}','{$_SESSION['camp_family']}','{$_SESSION['camp_children']}','{$_SESSION['camp_total']}')";

$res = $db->Execute($q);

// insert into camp admin
$qa = "insert into camp_admin(c_uuid,contact_puuid) values($uid,$puid)";
$resa = $db->Execute($qa);


// insert into person_details
$qb = "insert into person_details(p_uuid,occupation) values($puid,'{$_SESSION['occupation']}')";
$resb = $db->Execute($qb);


// insert into admin contact
$qc = "insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($puid,'cmob','{$_SESSION['contact_mob']}')";
$resc = $db->Execute($qc);
/*
 * GIS Insertion
*/

global $global;
include $global['approot']."/conf/config.inc";
	

//if mod_gis
if($conf['gis']){
  include $global['approot']."/mod/gis/conf.inc";
  include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_dbinsert($uid,$loc_id,$conf['mod_gis'],$_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'],NULL);
}
				



/*insert services into camp_services table
 *currently add checked values.
*/								
	if(isset($_SESSION['opt_camp_service'])){
	 foreach($_SESSION['opt_camp_service'] as $a => $b){
	//currently add checked values.
		$q = "insert into camp_services(c_uuid,opt_camp_service,value) values($uid,'{$b}',1)";
	 $res = $db->Execute($q);
	 }
	}
?>
<h2><?=_("You Have Succesfully Registered camp'{$_SESSION[camp_name]}'")?></h2>

<br>
<br>
<?php echo _("The Availability of Services & Facilities of the Camp are as follows:")?></h3>
<!--<p>Facilities / Services Availability</p>-->
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
					
			//echo "<li>$name :  Available </li><br>";
			$flag=true;			
		}
	 }
	}
	if(!$flag){
		echo "<td>$name</td>";
		echo "<td>"._("NOT AVAILABLE")."</td>";
		//echo "<li class=\"fontspecial\">$name : NOT AVAILABLE </li><br>";
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
<p><?php echo _("Use the Left Navigation Menu to Continue.")?></p>

<?php	
}
?>

