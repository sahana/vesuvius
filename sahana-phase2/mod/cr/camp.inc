<?php

/**Camp library for  CR
 *
 * PHP version 5
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
 * $Id: camp.inc,v 1.70 2009-08-22 17:17:24 ravithb Exp $
*/

include_once($global['approot'] . '/inc/lib_form.inc');
include_once($global['approot'] . '/inc/lib_validate.inc');
include_once($global['approot'] . '/inc/lib_errors.inc');
include_once($global['approot'] . '/inc/lib_xajax.inc');

function _shn_cr_cadd_start($errors = false)
{
    if ($errors) {
        display_errors();
    }
    global $global;
    global $conf;
    $db = $global['db'];
    ?>
<h2 align="center"><?php echo _t("Register New ").$conf['mod_cr_alt']?></h2>
    <?php

    shn_form_fopen(acmp);

    shn_form_fsopen(_t("General Details"));
    //check for gis and goto mapping page

    if ($conf['gis']) {
        shn_form_hidden(array('seq'=>'gis'));
    } else {
        shn_form_hidden(array('seq'=>'chk'));
    }
	shn_xajax_registerFunction('cr_check_shelter_name');
    shn_form_text(_t("Shelter Name"),"camp_name",' onchange="cr_check_shelter_name(this.value)"; ', array('req'=>true,'br'=>false));
	 echo "<span id='check' ></span><br /><br />";
    shn_form_opt_select("opt_camp_type",_t("Shelter Type"));
    ?>

<!--<label>Division</label>
<select name="opt_location_type" >-->

    <?php

    //-----------------------------------------
    shn_form_textarea(_t("Address"),"camp_address");
    shn_form_fsclose();
    //-------------------------
    global $global;
    include $global['approot']."/inc/lib_location.inc";
    global $range;
    shn_form_fsopen(_t("Location Details"));
    shn_location($range);
    shn_form_fsclose();

    //-------------------------
    shn_form_fsopen(_t("Contact Person Details"));
    shn_form_text(_t("Full Name"),"camp_contact_name",'size="60"',array('help'=>'Enter Details of the person in charge of the Shelter'));
    shn_form_text(_t("Phone Number"),"camp_contact_number",'size="60"');
    shn_form_text(_t("Mobile Number"),"contact_mob",'size="60"');
    shn_form_text(_t("Occupation"),"occupation",'size="60"',array('help'=>'Official Occupation of Shelter Administrator'));
    shn_form_fsclose();
    shn_form_fsopen(_t("Shelter Population"));
    shn_form_text(_t("Capacity"),"capacity",'size="10"');
    shn_form_text(_t("Men"),"men",'size="10"');
    shn_form_text(_t("Women"),"women",'size="10"');
    shn_form_text(_t("Children"),"children",'size="10"');
    shn_form_text(_t("Infected Count"),"family",'size="10"');
    shn_form_text(_t("Total Count"),"total",'size="10"');
    shn_form_fsclose();
    /*
     $hospital_help=_t("Check this if you want to enter hospital information related to this {$conf['mod_cr_alt']}");
     shn_form_fsopen(_t("Hospital Metadata"));
     shn_form_checkbox(_t("{$conf['mod_cr_alt']} is of type hospital"),"hospital",null,array('help'=>$hospital_help));
     shn_form_fsclose();
     */
    shn_form_submit(_t("Next"));
    shn_form_fclose();
}

function _shn_cr_hos_bed($errors = false)
{
    if($errors) {
        display_errors;
    }

    $_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
    $_SESSION['camp_comments']=$_POST['comments'];


    global $global;
    global $conf;

    shn_form_fopen(acmp);
    ?>
<h1><?php echo _t("Hospital Capabilities")?></h1>
    <?php
    shn_form_fsopen(_t("Number of Beds"));
    shn_form_hidden(array('seq'=>'commit'));
    shn_form_text(_t("ICU"),"icu",'size="5"');
    shn_form_text(_t("Medicine"),"med",'size="5"');
    shn_form_text(_t("Surgery"),"sur",'size="5"');
    shn_form_text(_t("Paediatrics"),"paed",'size="5"');
    shn_form_text(_t("Obstetrics"),"obs",'size="5"');
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
}



function _shn_cr_cadd_chk($errors = false)
{
    if ($errors) {
        display_errors;
    }
    global $global;
    global $conf;
    if (!$conf['gis']) {
        //add to session if GIS module is not enabled
        $_SESSION['camp_name']=$_POST['camp_name'];
        $_SESSION['opt_camp_type']=$_POST['opt_camp_type'];
        $_SESSION['opt_location_type']=$_POST['opt_location_type'];
        $_SESSION['camp_address']=$_POST['camp_address'];
        $_SESSION['camp_contact_name']=$_POST['camp_contact_name'];
        $_SESSION['camp_contact_number']=$_POST['camp_contact_number'];
        if($_POST['family']==null){
            $_SESSION['camp_family']=0;
		}else{
			$_SESSION['camp_family']=$_POST['family'];
		}
        if($_POST['men']==null){
			$_SESSION['camp_men']=0;
		}else{
			$_SESSION['camp_men']=$_POST['men'];
		}
        if($_POST['women']==null){
			$_SESSION['camp_women']=0;
		}else{
			$_SESSION['camp_women']=$_POST['women'];
		}
        if($_POST['children']==null){
			$_SESSION['camp_children']=0;
		}else{
			$_SESSION['camp_children']=$_POST['children'];
		}
        if($_POST['total']==null){
			$_SESSION['camp_total']=0;
		}else{
			$_SESSION['camp_total']=$_POST['total'];
		}
        if($_POST['capacity']==null){
			$_SESSION['camp_capacity']=0;
		}else{
			$_SESSION['camp_capacity']=$_POST['capacity'];
		}
        $_SESSION['contact_mob']=$_POST['contact_mob'];
        $_SESSION['occupation']=$_POST['occupation'];

        $_SESSION['cr_1']=$_POST['1'];
        $_SESSION['cr_2']=$_POST['2'];
        $_SESSION['cr_3']=$_POST['3'];
        $_SESSION['cr_4']=$_POST['4'];
        $_SESSION['cr_5']=$_POST['5'];

        if (isset($_POST['hospital'])) {
            $_SESSION['hospital'] = true;
        }

    } else {
        if ((null == $_POST['gps_x']) && null == $_POST['gps_y']) {
            $_SESSION['gis_loc_x']=$_POST['loc_x'];
            $_SESSION['gis_loc_y']=$_POST['loc_y'];
        } else {
            $_POST['loc_x'] = $_POST['gps_x'];
            $_POST['loc_y'] = $_POST['gps_y'];
            $_SESSION['gis_loc_x']=$_POST['loc_x'];
            $_SESSION['gis_loc_y']=$_POST['loc_y'];
        }
    }

    ?>
<h2><?php echo _t("Shelter Checklist")?></h2>
    <?php
    //var_dump($_SESSION);
    shn_form_fopen("acmp",'',array('req_message'=>false));
    shn_form_fsopen(_t("Services / Facilities Available"));
    if (isset($_SESSION['hospital'])) {
        shn_form_hidden(array('seq'=>'hos'));
    } else {
        shn_form_hidden(array('seq'=>'confir'));
    }
    shn_form_opt_checkbox("opt_camp_service");
    //shn_form_textarea(_t("Other Facilities"),"comments");
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();

}

function _shn_cr_cadd_commit()
{
    global $global;
    if (isset($_POST['finish'])) {
        //wr ite to database
        /*if(!isset($_SESSION['hospital'])){
        $_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
        $_SESSION['camp_comments']=$_POST['comments'];
        }*/


        if (isset($_SESSION['hospital'])) {
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
		if(!shn_cr_shelter_name_exist($_SESSION['camp_name'])){
			_shn_cr_cadd_commit_db();
		}
		else {
			add_error($_SESSION['camp_name']._t(' is already registered. Please enter new shelter name '));
			_shn_cr_cadd_start(true);
		}
        
    } elseif (isset($_POST['edit'])) {
        _shn_cr_cedt_add();
    }
}

function shn_cr_shelter_name_exist($shetler_name){
	global $global;
	$sql = "SELECT name FROM camp_general WHERE name = '$shetler_name'";
	$res = $global['db']->GetOne($sql);
	
	if (strtolower($res) == strtolower($shetler_name)){
		return true;
	}
	else {
		return false;
	}
}

function _shn_cr_create_cid($val)
{
    global $global;
    include_once($global['approot'].'/inc/lib_uuid.inc');
    $id = shn_create_uuid($val);
    //echo "ID IS: $id";
    return $id;
}

function _shn_cr_sel_map($errors = false)
{
    if ($errors) {
        display_errors();
    } else {
        global $global;
        include $global['approot']."/inc/lib_location.inc";
        $_SESSION['cr']['loc'] = shn_location_get_form_submit_loc();
        $_SESSION['camp_name'] = $_POST['camp_name'];
        $_SESSION['opt_camp_type'] = $_POST['opt_camp_type'];
        $_SESSION['opt_location_type'] = $_POST['opt_location_type'];
        $_SESSION['camp_address'] = $_POST['camp_address'];
        $_SESSION['camp_contact_name'] = $_POST['camp_contact_name'];
        $_SESSION['camp_contact_number'] = $_POST['camp_contact_number'];
        if($_POST['family']==null){
            $_SESSION['camp_family']=0;
		}else{
			$_SESSION['camp_family']=$_POST['family'];
		}
        if($_POST['men']==null){
			$_SESSION['camp_men']=0;
		}else{
			$_SESSION['camp_men']=$_POST['men'];
		}
        if($_POST['women']==null){
			$_SESSION['camp_women']=0;
		}else{
			$_SESSION['camp_women']=$_POST['women'];
		}
        if($_POST['children']==null){
			$_SESSION['camp_children']=0;
		}else{
			$_SESSION['camp_children']=$_POST['children'];
		}
        if($_POST['total']==null){
			$_SESSION['camp_total']=0;
		}else{
			$_SESSION['camp_total']=$_POST['total'];
		}
        if($_POST['capacity']==null){
			$_SESSION['camp_capacity']=0;
		}else{
			$_SESSION['camp_capacity']=$_POST['capacity'];
		}
        if (isset($_POST['hospital'])) {
            $_SESSION['hospital'] = true;
        }
        $_SESSION['contact_mob'] = $_POST['contact_mob'];
        $_SESSION['occupation'] = $_POST['occupation'];
        $_SESSION['cr_loc'] = shn_location_get_form_submit_loc();
        $_SESSION['cr_1'] = $_POST['loc_select_1'];
        $_SESSION['cr_2'] = $_POST['loc_select_2'];
        $_SESSION['cr_3'] = $_POST['loc_select_3'];
        $_SESSION['cr_4'] = $_POST['loc_select_4'];
        $_SESSION['cr_5'] = $_POST['loc_select_5'];
    }




    global $global;
    global $conf;


    shn_form_fopen(acmp,null,array('req'=>false));
    shn_form_fsopen(_t("Location Information"));
    echo _t("Plot the Shelter Location OR Enter its GPS coordinates below");
    shn_form_hidden(array('seq'=>'chk'));
    shn_form_fsclose();

    //call gis api
    include $global['approot']."/inc/lib_gis/gis_fns.inc";
    shn_gis_add_marker_map_form("GIS Map",$_POST['camp_name']);

    ?>

    <?php

    shn_form_submit("Next");
    shn_form_fclose();

}

/**
 * @todo: change variables to lat=y. lon=x
 */
function _shn_cr_validate_gps()
{
    clean_errors();
    $error_flag = false;

    // latitude
    if (!(null == ($_POST['gps_y']))) {
        if (!shn_valid_y_coordinate(trim($_POST['gps_y']))) {
            //add_error(_t("Coordinates invalid: should be between -180 & 180"));
            $error_flag = true;
        }
    }
    //longitude
    if (!(null == ($_POST['gps_x']))) {
        if (!shn_valid_x_coordinate(trim($_POST['gps_x']))) {
            //add_error(_t("Coordinates invalid: should be between -180 & 180"));
            $error_flag = true;
        }
    }
    return $error_flag;


}

function _shn_cr_validate_error()
{
    clean_errors();
    $error_flag = false;
      
    if($_POST['camp_name'] != null && shn_cr_shelter_name_exist($_POST['camp_name'])){
        add_error($_POST['camp_name']._t(' is already registered. Please enter new shelter name '));
        $error_flag = true;
        $_POST = null;
    }else if (null == ($_POST['camp_name'])) {
        add_error(_t("Please enter the shelter name"));
        $error_flag = true;
    }
    //echo $_POST['family'];
    if (!(null == ($_POST['family']))) {
        if (!is_numeric(trim($_POST['family']))) {
            add_error(_t("The infected count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['family'])) {
            add_error(_t("The infected count cannot be negative"));
            $error_flag = true;
        }
    }
    /*
     if(!(null == ($_POST['camp_contact_number']))){
     if(!shn_valid_phone(trim($_POST['camp_contact_number']))){
     add_error(_t("The Phone Number is not valid"));
     $error_flag=true;
     }
     }

     if(!(null == ($_POST['contact_mob']))){
     if(!shn_valid_phone(trim($_POST['contact_mob']))){
     add_error(_t("The Mobile Phone Number is not valid"));
     $error_flag=true;
     }
     }
     */


    if (!(null == ($_POST['capacity']))) {
        if (!is_numeric(trim($_POST['capacity']))) {
            add_error(_t("The capacity is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['capacity'])) {
            add_error(_t("The capacity cannot be negative"));
            $error_flag=true;
        }
    }


    if (!(null == ($_POST['men']))) {
        if (!is_numeric(trim($_POST['men']))) {
            add_error(_t("The men count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['men'])) {
            add_error(_t("The men count cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['women']))) {
        if (!is_numeric(trim($_POST['women']))) {
            add_error(_t("The women count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['women'])) {
            add_error(_t("The women count cannot be negative"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['children']))) {
        if (!is_numeric(trim($_POST['children']))) {
            add_error(_t("The children count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['children'])) {
            add_error(_t("The children count cannot be negative"));
            $error_flag = true;
        }
    }

    if (!(null == ($_POST['total']))) {
        if (!is_numeric(trim($_POST['total']))) {
            add_error(_t("The total count is not a valid number"));
            $error_flag = true;
        } else if (!positive_number($_POST['total'])) {
            add_error(_t("The total count cannot be negative"));
            $error_flag = true;
        }


    }

    if ($_POST['children'] != null || $_POST['women'] != null || $_POST['men'] != null) {
        $totalcount = $_POST['children'] + $_POST['women'] + $_POST['men'];
        if ($totalcount != $_POST['total']) {
            add_error(_t("The total count should be equal to men, women and children count"));
            $error_flag = true;
        }
        	if($_POST['family'] > $totalcount){
        		add_error(_t("The Infected count should be less or equal than the total count"));
            	$error_flag = true;
        	}
    }

    return $error_flag;
}

function positive_number($nr)
{
    if (ereg("^[0-9]+$", $nr) && $nr >= 0) {
        return true;
    } else {
        return false;
    }
}

function _shn_cr_bed_validate_error()
{

    //if(isset($_SESSION['hospital'])){
    clean_errors();
    $error_flag = false;



    if (!(null == ($_POST['icu']))) {
        if (!is_numeric(trim($_POST['icu']))) {
            add_error(_t("The ICU beds is not a valid number"));
            $error_flag = true;
        }
    }

    if (!(null == ($_POST['med']))) {
        if (!is_numeric(trim($_POST['med']))) {
            add_error(_t("The medicine beds is not a valid number"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['sur']))) {
        if (!is_numeric(trim($_POST['sur']))) {
            add_error(_t("The surgery beds is not a valid number"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['paed']))) {
        if (!is_numeric(trim($_POST['paed']))) {
            add_error(_t("The paediatrics Beds is not a valid number"));
            $error_flag = true;
        }
    }
    if (!(null == ($_POST['obs']))) {
        if(!is_numeric(trim($_POST['obs']))) {
            add_error(_t("The obstetrics Beds is not a valid number"));
            $error_flag = true;
        }
    }

    return $error_flag;

}


function _shn_cr_get_locid()
{
    if ($_SESSION['cr_5'] != null) {
        return $_SESSION['cr_5'];
    } else if ($_SESSION['cr_4'] != null) {
        return $_SESSION['cr_4'];
    } else if ($_SESSION['cr_3'] != null) {
        return $_SESSION['cr_3'];
    } else if ($_SESSION['cr_2'] != null) {
        return $_SESSION['cr_2'];
    } else {
        return $_SESSION['cr_1'];
    }
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
    $loc_id = _shn_cr_get_locid();
    $loc_id = $_SESSION['cr_loc'];

    //enter into camp table
    $q = "INSERT INTO camp_general(c_uuid,name,location_id,opt_camp_type,address,capacity) " .
		"VALUES('{$uid}','{$_SESSION['camp_name']}','{$loc_id}','{$_SESSION['opt_camp_type']}','{$_SESSION['camp_address']}','{$_SESSION['camp_capacity']}')";
    $res = $db->Execute($q);

    //enter into camp_reg table
    $q = "INSERT INTO camp_reg (c_uuid,admin_name,admin_no,men,women,family,children,total) " .
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

    if ($conf['gis']) {
        require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
        $class = 'cr_camp';
        if($_SESSION['opt_camp_type'] == 'gov' || $_SESSION['opt_camp_type'] == 'tmp' || $_SESSION['opt_camp_type'] == 'ngo'){
            $class = $class . '_' . $_SESSION['opt_camp_type'];
        }
        $coords = shn_gis_coord_encode(array(array($_SESSION['gis_loc_x'],$_SESSION['gis_loc_y'], 0)), 'point');
        $keys = array(  
            'f_class'         => $class,
            'f_type'          => 'point',
            'f_coords'        => $coords,
            'f_module_item'   => $uid,
            'f_name'          => $_SESSION['camp_name'],
            'f_url'           => ('mod=cr&act=ecmp&seq=view&cmp_id=' . $uid),
            'f_address'       => $_SESSION['camp_address']
        );
        shn_gis_create_feature($keys);
    }

    /*insert services into camp_services table
     *currently add checked values.
     */
    if (isset($_SESSION['opt_camp_service'])) {
        foreach ($_SESSION['opt_camp_service'] as $a => $b) {
            //currently add checked values.
            $q = "INSERT INTO camp_services(c_uuid,opt_camp_service,value) VALUES('{$uid}','{$b}',1)";
            $res = $db->Execute($q);
        }
    }
    add_confirmation(_t("You have succesfully registered shelter ") . $_SESSION["camp_name"]);
    ?>
<br />
<div id="note"><?php echo _t("The availability of services & facilities of the shelter are as follows:")?>
</div>
<!--<p>Facilities / Services Availability</p>-->
<ul>

	<!--To have the results shown in table format-->
	<div id="result">
	<table>
		<thead>
			<td><?php echo _t("Service Type")?></td>
			<td><?php echo _t("Availability")?></td>
		</thead>

		<tbody>
			<tr>
			<?php
			$a = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_camp_service'";
			$ref = $db->Execute($a);
			while (!$ref->EOF)  {
			    $val = $ref->fields[0];
			    $name = $ref->fields[1];
			    $flag = false;
			    if (isset($_SESSION['opt_camp_service'])) {
			        foreach ($_SESSION['opt_camp_service'] as $a => $b) {
			            if ($val == $b) {

			                echo "<td>" . _lc($name) . "</td>";
			                echo "<td>" . _t("Available") . "</td>";

			                //echo "<li>$name :  Available </li><br>";
			                $flag = true;
			            }
			        }
			    }
			    if (!$flag) {
			        echo "<td>" . _lc($name) . "</td>";
			        echo "<td>" . _t("NOT AVAILABLE") . "</td>";
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
<br />
<div id="note"><?php echo _t("Use the Left Navigation Menu to Continue.")?>
</div>

<?php
unset($_SESSION['hospital']);
}

//code to add confirmation page
function _shn_cr_cadd_confir($errors = false)
{
    if ($errors) {
        display_errors;
    }
    global $global;
    global $conf;
    $db = $global['db'];
    ?>
<h2><?php echo  _t('Confirm Registration Details of ').$_SESSION['camp_name'] ?></h2>
    <?php
    shn_form_fopen("acmp",null,array('req_message'=>false,'name'=>""));
    shn_form_fsopen(_t('General Details'));
    shn_form_label(_t("Shelter Name") . " : ",$_SESSION['camp_name']);
    $q = "SELECT option_description FROM field_options WHERE field_name='opt_camp_type' AND option_code='" . $_SESSION['opt_camp_type'] . "'";
    $ref = $db->Execute($q);
    shn_form_label(_t("Shelter Type") . " : ",$ref->fields[0]);
    shn_form_label(_t("Address") . " : ",$_SESSION['camp_address']);
    shn_form_fsclose();
    shn_form_fsopen(_t('Location Details'));

    $location = _shn_cr_location_string($_SESSION['cr']['loc']);
    shn_form_label(_t("Location : "),$location);
    shn_form_fsclose();
    shn_form_fsopen(_t('Contact Person Details'));
    shn_form_label(_t("Full Name") . " : ",$_SESSION['camp_contact_name']);
    shn_form_label(_t("Phone Number") . " : ",$_SESSION['camp_contact_number']);
    shn_form_label(_t("Mobile Number") . " : ",$_SESSION['contact_mob']);
    shn_form_label(_t("Occupation") . " : ",$_SESSION['occupation']);
    shn_form_fsclose();
    shn_form_fsopen(_t('Shelter Population'));
    shn_form_label(_t("Capacity") . " : ",$_SESSION['camp_capacity']);
    shn_form_label(_t("Men") . " : ",$_SESSION['camp_men']);
    shn_form_label(_t("Women") . " : ",$_SESSION['camp_women']);
    shn_form_label(_t("Children") . " : ",$_SESSION['camp_children']);
    shn_form_label(_t("Infected Count") . " : ",$_SESSION['camp_family']);
    shn_form_label(_t("Total Count") . " : ",$_SESSION['camp_total']);
    shn_form_hidden(array('seq'=>'commit'));
    shn_form_fsclose();
    shn_form_fsopen(_t('GPS Coordinates'));
    shn_form_label(_t("Latitude") . " : ",$_SESSION['gis_loc_y']);
    shn_form_label(_t("Longitude") . " : ",$_SESSION['gis_loc_x']);

    shn_form_fsclose();
    shn_form_fsopen(_t('Services / Facilities Available'));
    if (!isset($_SESSION['hospital'])) {
        $_SESSION['opt_camp_service'] = $_POST['opt_camp_service'];
        $_SESSION['camp_comments'] = $_POST['comments'];
    }
    $a = "SELECT option_code,option_description FROM field_options WHERE field_name='opt_camp_service'";
    $ref = $db->Execute($a);
    while (!$ref->EOF) {
        $val = $ref->fields[0];
        $name = $ref->fields[1];
        $flag = false;
        if (isset($_SESSION['opt_camp_service'])) {
            foreach ($_SESSION['opt_camp_service'] as $a => $b) {
                if ($val == $b) {
                    shn_form_label(_lc($name) . " : ",_t('Available'));

                    $flag = true;
                }
            }
        }
        if (!$flag) {
            shn_form_label(_lc($name) . " : ",_t('Not Available'));

        }
        ?>
<!-- </tr>-->
        <?php
        $ref->MoveNext();
}


shn_form_fsclose();
echo '<center>';
shn_form_submit(_t("Finish"),'name="finish"');
shn_form_submit(_t("Edit"),'name="edit"');
echo '</center>';
shn_form_fclose();





}

function _shn_cr_cedt_add($errors = false)
{
    if ($errors) {
        display_errors();
    }
    global $global;
    $db = $global['db'];
    ?>
<h2>
<center><?php echo _t("Register New Shelter")?></center>
</h2>
    <?php

    shn_form_fopen('acmp');
    shn_form_fsopen(_t("General Details"));
    shn_form_hidden(array('seq'=>'gis'));
    shn_form_text(_t("Shelter Name"),"camp_name",'size="50"',array('req'=>true,'value'=>$_SESSION['camp_name']));
    shn_form_opt_select("opt_camp_type",_t("Shelter Type"),null,array('value'=>$_SESSION['opt_camp_type']));
    shn_form_textarea(_t("Address"),"camp_address",null,array('value'=>$_SESSION['camp_address']));
    shn_form_fsclose();
    ?>

    <?php

    global $global;
    include $global['approot'] . "/inc/lib_location.inc";
    global $range;
    shn_form_fsopen(_t("Location Details"));
    shn_location($range,$_SESSION['cr']['loc']);
    shn_form_fsclose();

    //-----------------------------------------
    shn_form_fsopen(_t("Contact Person Details"));
    shn_form_text(_t("Full Name"),"camp_contact_name",'size="60"',array('value'=>$_SESSION['camp_contact_name']));
    shn_form_text(_t("Phone Number"),"camp_contact_number",'size="60"',array('value'=>$_SESSION['camp_contact_number']));
    shn_form_text(_t("Mobile Number"),"contact_mob",'size="60"',array('value'=>$_SESSION['camp_contact_mob']));
    shn_form_text(_t("Occupation"),"occupation",'size="60"',array('value'=>$_SESSION['camp_occupation']));
    shn_form_fsclose();
    shn_form_fsopen(_t("Shelter Population"));
    shn_form_text(_t("Capacity"),"capacity",'size="10"',array('value'=>$_SESSION['camp_capacity']));

    shn_form_text(_t("Men"),"men",'size="10"',array('value'=>$_SESSION['camp_men']));
    shn_form_text(_t("Women"),"women",'size="10"',array('value'=>$_SESSION['camp_women']));
    shn_form_text(_t("Children"),"children",'size="10"',array('value'=>$_SESSION['camp_children']));
    shn_form_text(_t("Infected Count"),"family",'size="10"',array('value'=>$_SESSION['camp_family']));
    shn_form_text(_t("Total Count"),"total",'size="10"',array('value'=>$_SESSION['camp_total']));

    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();
}

function _shn_cr_location_string($loc)
{
    global $global;
    $db = $global["db"];
    $loc_arr = array();
    include $global['approot'] . "/inc/lib_location.inc";
   	shn_get_parents($loc, &$loc_arr);
   	if ($loc_arr[0] == 'unknown') {
   	    //shn_form_label(_t("Organization Location"),"Unknown");
   	} else {

   	    $max = count($loc_arr) - 1;
   	    array_pop($loc_arr);
   	    for ($count = 0; $count < $max; $count++) {
   	        $x = array_pop($loc_arr);
   	        $q = "SELECT name FROM location WHERE loc_uuid='{$x}'";
   	        $res = $db->Execute($q);
   	        if ($count == 0) {
   	            $location = $location . $res->Fields("name");
   	        } else {
   	            $location = $location . " -->" . $res->Fields("name");
   	        }

   	    }
   	}
    return $location;
}

