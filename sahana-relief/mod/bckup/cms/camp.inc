<?php
/* $Id; */

/**Camp library for  CMS
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


/**
 * display camp creation form
 */
function _shn_cms_cadd_form($errors=false){
	echo "<h2>"._t("Add New Camp - Details")."</h2>";
	
	if($errors)
		display_errors();
		
	global $global;
	$db=$global['db'];
	include $global['approot']."/inc/lib_location.inc";
		
	// store session
	$_SESSION['opt_camp_service'] = $_POST['opt_camp_service'];
	
	//initialize array for organizaton drop-down
	$org_q="select o_uuid,name from org_main";
	$org_res=$db->Execute($org_q);
	while(!$org_res->EOF){
		$org_array[$org_res->fields['o_uuid']] = ($org_res->fields['name']);
		$org_res->MoveNext();
	}
		
	var_dump($org_array);
	//show add camp form
	shn_form_fopen(cadd);
	shn_form_fsopen(_t("Name and Type"));
	shn_form_hidden(array('seq'=>'adm'));
	shn_form_text(_t("Camp Name"),"camp_name",'size="50"',array('req'=>true));
	shn_form_opt_select("opt_camp_type",_t("Camp Type"));
	shn_form_textarea(_t("Address"),"camp_address");
	shn_form_fsclose();
	shn_location_form_org(1,4);
	shn_form_fsopen(_t("Camp Administrator"));
	shn_form_text(_t("Camp Admin Name"),"admin_name",'size="50"');
	shn_form_text(_t("Contact Number"),"admin_no",'size="50"');
	shn_form_select($org_array,_t("Administrative Organization(s)"),"org_name");
	shn_form_fsclose();
	shn_form_fsopen(_t("Demographics"));
	//shn_form_text(_t("Distance from City [km]"),"city_dis",'size="50"');
	//shn_form_text(_t("Distance from Disaster [km]"),"disas_dis",'size="50"');
	shn_form_text(_t("Approximate Capacity [people]"),"capacity",'size="50"');
	shn_form_text(_t("Number of Shelters"),"shelters",'size="50"');
	shn_form_text(_t("Approximate Area Size [with units]"),"camp_size",'size="50"');
	shn_form_text(_t("Number of Persons per camp"),"per_camp",'size="50"');
	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();
			
}

/**
 * Camp Admin form
 */
function _shn_cms_cadd_admin(){
	shn_form_fopen(cadd);
	shn_form_fsopen(_t("Camp Administrator Details"));
	shn_form_hidden(array('seq'=>'ser'));
	shn_form_text(_t("Administrator Full Name"),"admin_name",'size="50"',array('req'=>true));
	shn_form_text(_t("ID/Passport/SSN"),"admin_id");
	shn_form_text(_t("Camp Phone"),"camp_contact");
	shn_form_text(_t("Mobile Number"),"admin_mobile");
	shn_form_text(_t("ID/Passport/SSN"),"admin_id");
	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();
}

/**
 * Add service-organization form
 */
function _shn_cms_cadd_serorg(){
	
	global $global;
	$db = $global['db'];
	
	//initialize array for organizaton drop-down
	$org_q="select o_uuid,name from org_main";
	$org_res=$db->Execute($org_q);
	while(!$org_res->EOF){
		$org_array[$org_res->fields['o_uuid']] = ($org_res->fields['name']);
		$org_res->MoveNext();
	}
	
	shn_form_fopen(cadd);
	shn_form_fsopen(_t("Service Organizations"));
	shn_form_hidden(array('seq'=>'map'));
	
	//get camp services from database
	$cmp_ser = "select * from field_options where field_name='opt_camp_service'";
	$cmp_ser_res = $db->Execute($cmp_ser);
	while(!$cmp_ser_res->EOF){
		shn_form_select($org_array,_lc($cmp_ser_res->fields['option_description']),"org_ser_name");
		$cmp_ser_res->MoveNext();
	}
	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();
}

function _shn_cms_cadd_guide(){
	global $global;
	//attach guidelines;
	
?>
	<h2>New Camp Guidlines</h2>
	<div id="home">
<?php
	include($global['approot'].'/mod/cms/guide.inc');
?>
	</div>
<?php
	shn_form_fopen(cadd);
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_submit(_t("Accept"));
}

function _shn_cms_cadd_chk(){
	global $global;
	echo "<h2>"._t("Camp Service Checklist")."</h2>";
	shn_form_fopen(cadd);
	shn_form_fsopen(_t("Facilities / Services"));
	shn_form_hidden(array('seq'=>'form'));
	shn_form_opt_checkbox("opt_camp_service");
	shn_form_fsclose();
	shn_form_submit(_t("Done"));
	shn_form_fclose();
			
}

/**
 *	add camp location gis 
 */
function _shn_cms_add_map()
{
	$_SESSION['opt_camp_service'] = $_POST['opt_camp_service'];
	$_SESSION['camp_name']=$_POST['camp_name'];
	$_SESSION['opt_camp_type']=$_POST['opt_camp_type'];
	$_SESSION['opt_location_type']=$_POST['opt_location_type'];
	$_SESSION['camp_address']=$_POST['camp_address'];
	$_SESSION['city_dis']=$_POST['city_dis'];
	$_SESSION['disas_dis']=$_POST['disas_dis'];
	$_SESSION['admin_name']=$_POST['admin_name'];
	$_SESSION['admin_no']=$_POST['admin_no'];
	$_SESSION['org_name']=$_POST['org_name'];
	$_SESSION['capacity']=$_POST['capacity'];
	$_SESSION['shelters']=$_POST['shelters'];
	$_SESSION['camp_size']=$_POST['camp_size'];
	
	shn_form_fopen(cadd);
	shn_form_fsopen(_t("Location Information"));
	echo _t("Plot the Camp Location OR Enter its GPS coordinates below");
	shn_form_fsclose();
	shn_form_fsopen(_t("Plot Location on Map"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_hidden(array('loc_x'=>''));
	shn_form_hidden(array('loc_y'=>''));
	global $global;
	$db=$global['db'];
	echo "<h2>"._t("Area Map")."</h2>";

	//if gis enabled
	if($conf['gis']){
	  if($conf['gis_dflt']=='google_maps'){
	  	/*
		 	 * google maps
		 	 *@todo check for online connectivity: exit gracefully
	  	*/
	 		include_once $global['approot']."/inc/lib_gis/plugins/google_maps/handler_google_maps.inc";
			echo _t("Enter Camp Location. Click on Map where camp exists");

			$a="select value from config where module_id='admin' and confkey='gis_google_key'";
      		$ares=$db->Execute($a);
			$keys=$ares->fields[0];

	
			$w="select value from config where module_id='admin' and confkey='gis_center_x'";
			$wres=$db->Execute($w);
			$wkey=$wres->fields[0];

			$e="select value from config where module_id='admin' and confkey='gis_center_y'";
			$eres=$db->Execute($e);
			$ekey=$eres->fields[0];
																		
			init_map($keys);
			load_map($wkey,$ekey);
			add_marker($_POST['camp_name']);
		}
	}
	else
	{
?>
   <p>No Currently Selected GIS</p> 
<?php
  }
	shn_form_fsclose();
	shn_form_fsopen(_t("GPS Coordinates"));
	shn_form_text(_t("Northing / Latitude"),"gps_y",'size="60"');
	shn_form_text(_t("Easting / Longitude"),"gps_x",'size="60"');
	shn_form_fsclose();
			
	shn_form_submit("Next");
	shn_form_close();
}	

/**
 * commit new camp
 */
function _shn_cms_camp_commit()
{
	
	//override map location by gps location box values
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
	
	global $global;
	$db = $global['db'];
	
	//create unique camp id
	$uid=shn_create_uuid();
	
	// phonetic inclusion
	shn_db_insert_phonetic('camp_name',$uid);
	
	$loc_id=_shn_cr_get_locid();
	
	//enter into camp table
	$query="insert into camp(c_uuid,name,location_id,opt_camp_type,address) values($uid,'{$_SESSION['camp_name']}',$loc_id,'{$_SESSION['opt_camp_type']}','{$_SESSION['camp_address']}')";
	$res = $db->Execute($query);
	
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
	
	// Insert GIS location
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        $class = 'cr_camp';
        if($_SESSION['opt_camp_type'] == 'gov' || $_SESSION['opt_camp_type'] == 'tmp' || $_SESSION['opt_camp_type'] == 'ngo'){
            $class = $class . '_' . $_SESSION['opt_camp_type'];
        }
        $coords = shn_gis_coord_encode(array(array($_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'], 0)), 'point');
        $keys_ = array(  
            'f_class'         => $class,
            'f_type'          => 'point',
            'f_coords'        => $coords,  
            'f_module_item'   => $uid,
            'f_name'          => $_SESSION['camp_name'],
            'f_url'           => ('mod=cr&act=ecmp&seq=view&cmp_id=' . $uid),
            'f_address'       => $_SESSION['camp_address']
        );                
        shn_gis_create_feature($keys_);
    }
}	

//dummy function.replace with janakas
function shn_create_uuid()
{
	$id=time();
	return $id;
}
	
/**
 * hack for location
 */
function _shn_cr_get_locid(){
	if($_SESSION['cr_4']!=null)
		return $_SESSION['cr_4'];
	else if($_SESSION['cr_3']!=null)
		return $_SESSION['cr_3'];
	else if($_SESSION['cr_2']!=null)
		return $_SESSION['cr_2'];
	else 
		return $_SESSION['cr_1'];
}

function _shn_cms_cedt(){
	global $global;
?>
<h2>Edit Existing Camp</h2>
<?php
}

function _shn_cms_exit(){
	global $global;
?>
<h2>Camp Exit Procedure</h2>
<?php
}