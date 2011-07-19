<?php

/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <leif.neve at aqulient dot com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */

include_once($global['approot']."/inc/lib_uuid.inc");

/**
 * This function commits the given Missing person's data to the database.
 * @access public
 * @return void
 */
function shn_mpr_addperson_commit() {
	global $global;
	global $conf;

	$audit_flag = false;
	//Basic Details : person_uuid
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['incident_id'])){
		$insert_array['incident_id'] = $_SESSION['mpr_add']['entry']['incident_id'];
	}
	if(isset($_SESSION['mpr_add']['entry']['expiry_date'])){
		$insert_array['expiry_date'] = $_SESSION['mpr_add']['entry']['expiry_date'];
	}
	if(isset($_SESSION['mpr_add']['entry']['full_name'])){
		$insert_array['full_name'] = $_SESSION['mpr_add']['entry']['full_name'];
	}
	if(isset($_SESSION['mpr_add']['entry']['given_name'])){
		$insert_array['given_name'] = $_SESSION['mpr_add']['entry']['given_name'];
	}
	if(isset($_SESSION['mpr_add']['entry']['family_name'])){
		$insert_array['family_name'] = $_SESSION['mpr_add']['entry']['family_name'];
	}
	shn_db_insert($insert_array,'person_uuid',$audit_flag,'p_uuid');
	$insert_array = null; // reset array


	//Contacts
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(!empty($_SESSION['mpr_add']['entry']['address'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['address'];
		$insert_array['opt_contact_type'] = 'home';
		shn_db_insert($insert_array,'contact',$audit_flag, 'p_uuid');
	}
	$insert_array = null; // reset array

    	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['email'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['email'];
		$insert_array['opt_contact_type'] = 'email';
	        shn_db_insert($insert_array,'contact', $audit_flag, 'p_uuid');
	}
	$insert_array = null; // reset array

	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['phone'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['phone'];
		$insert_array['opt_contact_type'] = 'curr';
		shn_db_insert($insert_array,'contact', $audit_flag, 'p_uuid');
	}
	$insert_array = null; // reset array

	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['mobile'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['mobile'];
		$insert_array['opt_contact_type'] = 'cmob';
		shn_db_insert($insert_array,'contact',$audit_flag,'p_uuid');
	}
	$insert_array = null; // reset array

	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['zip'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['entry']['zip'];
		$insert_array['opt_contact_type'] = 'zip';
		shn_db_insert($insert_array,'contact',$audit_flag,'p_uuid');
	}
	$insert_array=null; // reset array


	//person_physical
        // No relevant fields from PFIF unless we parse person.other.


	//person_details
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	if(isset($_SESSION['mpr_add']['entry']['dob'])) {
		$insert_array['birth_date'] = $_SESSION['mpr_add']['entry']['dob'];
	}
	if(isset($_SESSION['mpr_add']['entry']['years_old'])) {
		$insert_array['years_old'] = $_SESSION['mpr_add']['entry']['years_old'];
	}
	if(isset($_SESSION['mpr_add']['entry']['minAge'])) {
		$insert_array['minAge'] = $_SESSION['mpr_add']['entry']['minAge'];
	}
	if(isset($_SESSION['mpr_add']['entry']['maxAge'])) {
		$insert_array['maxAge'] = $_SESSION['mpr_add']['entry']['maxAge'];
	}
	if(isset($_SESSION['mpr_add']['entry']['opt_gender'])) {
		$insert_array['opt_gender'] = $_SESSION['mpr_add']['entry']['opt_gender'];
	}
	if(isset($_SESSION['mpr_add']['entry']['other_comments'])) {
		$insert_array['other_comments'] = $_SESSION['mpr_add']['entry']['other_comments'];
	}
	shn_db_insert($insert_array,'person_details',$audit_flag,'p_uuid');
	$insert_array = null; // reset array

	//person_status
	$insert_array['p_uuid'] = $_SESSION['mpr_add']['entry']['p_uuid'];
	$insert_array['opt_status'] = $_SESSION['mpr_add']['entry']['opt_status'];
	$insert_array['last_updated'] = $_SESSION['mpr_add']['entry']['last_updated'];
	$insert_array['creation_time'] = $_SESSION['mpr_add']['entry']['creation_time'];
	$insert_array['isvictim'] = 'TRUE';
	shn_db_insert($insert_array,'person_status',$audit_flag,'p_uuid');
	$insert_array = null; // reset array

	shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['entry']['p_uuid']);

	//image
        // print_r($_SESSION['mpr']['entry']);
	if (!empty($_SESSION['mpr']['entry']['image_type'])){
		shn_image_to_db($_SESSION['mpr_add']['entry']['p_uuid'],
                             $_SESSION['mpr']['entry']['image_type'],
                             $_SESSION['mpr']['entry']['image_height'],
                             $_SESSION['mpr']['entry']['image_width'],
                             $_SESSION['mpr']['entry']['url'],
                             $_SESSION['mpr']['entry']['url_thumb'],
                             $_SESSION['mpr']['entry']['original_filename'],
                             '','person');
                $errchk = $global['db']->ErrorMsg();
                if (!empty($errchk)) {
                    error_log("Error saving image info:".$errchk);
                }
	}
}

/**
 * This function creates the reporter uuid and inserts it into the DB.
 * @param mixed $p_uuid
 * @access public
 * @return void
 */
function shn_mpr_addmp_insert_reporter($p_uuid) {
	$audit_flag = false;
	//Create reported person uuid 
	$rep_uuid = shn_create_uuid('p');

	//person_uuid
	$insert_array['p_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['incident_id'])){
		$insert_array['incident_id'] = $_SESSION['mpr_add']['report_person']['incident_id'];
	}
	if(isset($_SESSION['mpr_add']['report_person']['rep_full_name'])){
		$insert_array['full_name'] = $_SESSION['mpr_add']['report_person']['rep_full_name'];
	}
	shn_db_insert($insert_array, 'person_uuid', $audit_flag, 'p_uuid');
	$insert_array = null; // reset array

	//person_status
	$insert_array['p_uuid'] = $rep_uuid;
	$insert_array['opt_status'] = 'ali';
	$insert_array['isvictim'] = 'FALSE';
	shn_db_insert($insert_array,'person_status', $audit_flag, 'p_uuid');
	$insert_array = null; // reset array

        //contact
	$insert_array['p_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_phone'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['report_person']['rep_phone'];
		$insert_array['opt_contact_type'] = 'curr';
	        shn_db_insert($insert_array,'contact', $audit_flag, 'p_uuid');
	}
	$insert_array = null; // reset array

	$insert_array['p_uuid'] = $rep_uuid;
	if(isset($_SESSION['mpr_add']['report_person']['rep_email'])){
		$insert_array['contact_value'] = $_SESSION['mpr_add']['report_person']['rep_email'];
		$insert_array['opt_contact_type'] = 'email';
	        shn_db_insert($insert_array,'contact', $audit_flag,'p_uuid');
	}
	$insert_array = null; // reset array

	/*
	* Insert into person_to_report
	*/
	shn_add_person_to_report($p_uuid,$rep_uuid,$_SESSION['mpr_add']['report_person']['opt_relationship_type']);
}



/**
 * This function helps you to add reporting persons to the missing person
 * @param mixed $p_uuid
 * @param mixed $rep_uuid
 * @param mixed $relation
 * @access public
 * @return void
 */
function shn_add_person_to_report($p_uuid, $rep_uuid, $relation) {
	global $global;

	$insert_array['p_uuid'] = $p_uuid;
	$insert_array['rep_uuid'] = $rep_uuid;
	if($relation != null) {
		$insert_array['relation'] = $relation;
	} else {
		$insert_array['relation'] = "Not Specified";
	}
	shn_db_insert($insert_array,'person_to_report', false, 'p_uuid');
}
