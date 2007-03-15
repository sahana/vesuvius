<?php
/* $Id: camp.inc,v 1.41 2007-03-15 07:07:14 mifanc Exp $ */

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
* @edited by Isuru Samaraweera <isuru@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_cr_cadd_start($errors=false){
	if($errors)
		display_errors();
	global $global;
	global $conf;
	$db = $global['db'];
?>
<h2 align="center"><?php echo _("Register New Shelter")?></h2>
<?php
	
	shn_form_fopen(acmp);
	
	shn_form_fsopen(_("General Details"));
	//check for gis and goto mapping page
	
	if($conf['gis']){
		shn_form_hidden(array('seq'=>'gis'));
	}
	else{
		shn_form_hidden(array('seq'=>'chk'));
	}
	
	shn_form_text(_("Shelter Name"),"camp_name",'size="50"',array('req'=>true));
	shn_form_opt_select("opt_camp_type",_("Shelter Type"));
?>

<!--<label>Division</label>
<select name="opt_location_type" >-->

<?php
/*
// Display selected Division type only
	$q="select value from config where confkey='division_type' && module_id='sr'";
	//$q ="select option_dessription from field_options where field_name='sr_pref_div'";
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
	//small hack until lib_location is corrected
	//shn_location_form_org($range);
	shn_location_form_org(1,5);
		
//-------------------------
	shn_form_fsopen(_("Contact Person Details"));
	shn_form_text(_("Full Name"),"camp_contact_name",'size="60"',array('help'=>'Enter Details of the person in charge of the Shelter'));
	shn_form_text(_("Phone Number"),"camp_contact_number",'size="60"');
	shn_form_text(_("Mobile Number"),"contact_mob",'size="60"');
	shn_form_text(_("Occupation"),"occupation",'size="60"',array('help'=>'Official Occupation of Shelter Administrator'));
	shn_form_fsclose();
	shn_form_fsopen(_("Shelter Population"));
	shn_form_text(_("Infected Count"),"family",'size="10"');

	shn_form_text(_("Total Count"),"total",'size="10"');
        shn_form_text(_("Capacity"),"capacity",'size="10"');
	shn_form_text(_("Men"),"men",'size="10"');
	shn_form_text(_("Women"),"women",'size="10"');
	shn_form_text(_("Children"),"children",'size="10"');
	shn_form_fsclose();
	$hospital_help=_("Check this if you want to enter hospital information related to this shelter");
	shn_form_fsopen(_("Hospital Metadata"));
	shn_form_checkbox(_("Shelter is of type hospital"),"hospital",null,array('help'=>$hospital_help));
	shn_form_fsclose();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function _shn_cr_hos_bed($errors=false)
{
	if($errors)
	display_errors;

	$_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
	$_SESSION['camp_comments']=$_POST['comments'];
	
	
	global $global;
	global $conf;
	
	shn_form_fopen(acmp);
?>
	<h1><?=_("Hospital Capabilities")?></h1>
<?php
	shn_form_fsopen(_("Number of Beds"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_("ICU"),"icu",'size="5"');
	shn_form_text(_("Medicine"),"med",'size="5"');
	shn_form_text(_("Surgery"),"sur",'size="5"');
	shn_form_text(_("Paediatrics"),"paed",'size="5"');
	shn_form_text(_("Obstetrics"),"obs",'size="5"');
	shn_form_fsclose();
	shn_form_submit(_("Next"));
}



function _shn_cr_cadd_chk($errors=false){
if($errors)
	display_errors;
	global $global;
	global $conf;
	if(!$conf['gis']){
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
		
		if(isset($_POST['hospital'])){
			$_SESSION['hospital']=true;
		}
					
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
<h2>Shelter Checklist</h2>
<?php
//var_dump($_SESSION);
shn_form_fopen(acmp);
shn_form_fsopen(_("Services / Facilities Available"));
if(isset($_SESSION['hospital'])){
	shn_form_hidden(array('seq'=>'hos'));
}
else{
	shn_form_hidden(array('seq'=>'commit'));
}
shn_form_opt_checkbox("opt_camp_service");
shn_form_textarea(_("Other Facilities"),"comments");
shn_form_fsclose();
shn_form_submit(_("Next"));
shn_form_fclose();

}

function _shn_cr_cadd_commit(){
global $global;
//write to database
if(!isset($_SESSION['hospital'])){
	$_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
	$_SESSION['camp_comments']=$_POST['comments'];
}


	if(isset($_SESSION['hospital'])){
		$_SESSION['icu']=$_POST['icu'];
		$_SESSION['med']=$_POST['med'];
		$_SESSION['sur']=$_POST['sur'];
		$_SESSION['paed']=$_POST['paed'];
		$_SESSION['obs']=$_POST['obs'];
	}
//foreach($_SESSION['opt_camp_service'] as $a=>$b){
//echo "value is $b";
//}
//echo microtime(true);
//var_dump($_SESSION);
_shn_cr_cadd_commit_db();
}

function _shn_cr_create_cid($val){
	global $global;
	include_once($global['approot'].'/inc/lib_uuid.inc');
	$id = shn_create_uuid($val);
	//echo "ID IS: $id";
	return $id;
}

function _shn_cr_sel_map($errors=false){
	if($errors)
		display_errors();
	
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
      $_SESSION['camp_capacity']=$_POST['capacity'];	
//var_dump($_POST);
	if(isset($_POST['hospital'])){
		$_SESSION['hospital']=true;
	}
	$_SESSION['cr_1']=$_POST['1'];
	$_SESSION['cr_2']=$_POST['2'];
	$_SESSION['cr_3']=$_POST['3'];
	$_SESSION['cr_4']=$_POST['4'];
	$_SESSION['cr_5']=$_POST['5'];
		$_SESSION['contact_mob']=$_POST['contact_mob'];
		$_SESSION['occupation']=$_POST['occupation'];

	global $global;
	global $conf;
	
	//include_once $global['approot']."/mod/gis/plugins/google_maps/handler_google_maps.inc";
	//shn_js_show();
	//add_marker_out("some name");
											
	shn_form_fopen(acmp);
	shn_form_fsopen(_("Location Information"));
	echo _("Plot the Shelter Location OR Enter its GPS coordinates below");
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_fsclose();
	
	//call gis api
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_add_marker_map_form("GIS Map",$_POST['camp_name']);
	
?>
	
	<?php
	
	shn_form_submit("Next");
	shn_form_close();

}
function _shn_cr_validate_gps(){
	clean_errors();
	$error_flag=false;
	
	if(!(null == ($_POST['gps_x']))){
		if(!is_numeric(trim($_POST['gps_x']))){
			add_error(_("The GPS X values are not valid coordinates"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['gps_y']))){
		if(!is_numeric(trim($_POST['gps_y']))){
			add_error(_("The GPS Y values are not valid coordinates"));
			$error_flag=true;
		}
	}
	return $error_flag;
	
	
}

function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


	if(null == ($_POST['camp_name'])){
			add_error(_("Please Enter the Shelter Name"));
			$error_flag=true;
	}
	//echo $_POST['family'];
	if(!(null == ($_POST['family']))){
		if(!is_numeric(trim($_POST['family']))){
			add_error(_("The Infected Count is not a valid number"));
			$error_flag=true;
		}
	}
	
	

 if(!(null == ($_POST['capacity']))){
                if(!is_numeric(trim($_POST['capacity']))){
                        add_error(_("The Capacity is not a valid number"));
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
}
	
	function _shn_cr_bed_validate_error(){
		
		//if(isset($_SESSION['hospital'])){
		
				clean_errors();
				$error_flag=false;			
	
					

 					if(!(null == ($_POST['icu']))){
               			 if(!is_numeric(trim($_POST['icu']))){
                        	add_error(_("The ICU Beds is not a valid number"));
                       		 $error_flag=true;
                		}
        			}

					if(!(null == ($_POST['med']))){
						if(!is_numeric(trim($_POST['med']))){
							add_error(_("The Medicine Beds is not a valid number"));
							$error_flag=true;
						}
					}
					if(!(null == ($_POST['sur']))){
						if(!is_numeric(trim($_POST['sur']))){
							add_error(_("The Surgery Beds is not a valid number"));
							$error_flag=true;
						}
					}
					if(!(null == ($_POST['paed']))){
						if(!is_numeric(trim($_POST['paed']))){
							add_error(_("The Paediatrics Beds is not a valid number"));
							$error_flag=true;
						}
					}
					if(!(null == ($_POST['obs']))){
				    	if(!is_numeric(trim($_POST['obs']))){
							add_error(_("The Obstetrics Beds is not a valid number"));
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

/**
 * Database inserts for Sheter Registry
 * @access private
 */
function _shn_cr_cadd_commit_db()
{
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_uuid.inc');
	$db = $global['db'];
	
	$uid = shn_create_uuid('c');
	$puid = shn_create_uuid('p');
	
	shn_db_insert_phonetic('camp_name',$uid);
	$loc_id= _shn_cr_get_locid();

	//enter into camp table
	$q="INSERT INTO camp_general(c_uuid,name,location_id,opt_camp_type,address,capacity) " .
		"VALUES('{$uid}','{$_SESSION['camp_name']}','{$loc_id}','{$_SESSION['opt_camp_type']}','{$_SESSION['camp_address']}','{$_SESSION['camp_capacity']}')";
	$res = $db->Execute($q);
	
	//enter into camp_reg table
	$q="INSERT INTO camp_reg (c_uuid,admin_name,admin_no,men,women,family,children,total) " .
		"VALUES ('{$uid}','{$_SESSION['camp_contact_name']}','{$_SESSION['camp_contact_number']}','{$_SESSION['camp_men']}','{$_SESSION['camp_women']}','{$_SESSION['camp_family']}','{$_SESSION['camp_children']}','{$_SESSION['camp_total']}')";
	$res = $db->Execute($q);
	
	// insert into camp admin
	$qa = "INSERT INTO camp_admin(c_uuid,contact_puuid) VALUES ('{$uid}','{$puid}')";
	$resa = $db->Execute($qa);
	
	// insert into person_details
	$qb = "INSERT INTO person_details(p_uuid,occupation) " .
		  "VALUES('{$puid}','{$_SESSION['occupation']}')";
	$resb = $db->Execute($qb);
	
	// insert into admin contact
	$qc = "INSERT INTO contact(pgoc_uuid,opt_contact_type,contact_value) " .
		  "VALUES ('{$puid}','cmob','{$_SESSION['contact_mob']}')";
	$resc = $db->Execute($qc);
	
	//insert hospital meta
	if(isset($_SESSION['hospital'])){
		$qc = "INSERT INTO hospital_beds (c_uuid,icu,med,surg,paed,obs) " .
			  "VALUES ('{$uid}',{$_SESSION['icu']},{$_SESSION['med']},{$_SESSION['sur']},{$_SESSION['paed']},{$_SESSION['obs']})";
		$resc = $db->Execute($qc);
	}

	if($conf['gis']){
	  include $global['approot']."/mod/gis/gis_fns.inc";
		shn_gis_dbinsert($uid,$loc_id,$conf['mod_gis'],$_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'],NULL);
	}

	/*insert services into camp_services table
	 *currently add checked values.
	*/								
		if(isset($_SESSION['opt_camp_service'])){
		 foreach($_SESSION['opt_camp_service'] as $a => $b){
		//currently add checked values.
			$q = "insert into camp_services(c_uuid,opt_camp_service,value) values('{$uid}','{$b}',1)";
		 $res = $db->Execute($q);
		 }
		}
	add_confirmation(_("You Have Succesfully Registered shelter $_SESSION[camp_name]"));
	?>
	<br />
	<div id="note">
		<?php echo _("The Availability of Services & Facilities of the Shelter are as follows:")?>
	</div>
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
<br/>
<div id="note">
	<?php echo _("Use the Left Navigation Menu to Continue.")?>
</div>

<?php	
unset($_SESSION['hospital']);
}
?>
