<?php
/**
* The Situation Report (SITRep) Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   sr
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/
include_once "handler_forms.inc";

function shn_sr_store_reg_new_report($rpt_name,$rpt_desc)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
		
	// check for the report name
	if($rpt_name==""){ // if report name is empty 
		add_error("Please provide a Report name!");
		//recall the report reg form
		shn_sr_report_register();
	} else { // if report name is there then store
		//generate uuid for the report
		$report_id=shn_create_uuid('sitrep');
		
		// get the incident id
		$incident_id=$_SESSION['user_pref_ims_incident_id'];
		
		$q=" INSERT INTO sitrep_info (sitrep_info.report_id, sitrep_info.name, sitrep_info.description, sitrep_info.incident_id) VALUES ('$report_id','$rpt_name','$rpt_desc','$incident_id');";

		$res=$db->Execute($q);
		if($res){
			add_confirmation("Situation Report <strong>$rpt_name</strong> was registered successfully!");
		}
	}
}
?>