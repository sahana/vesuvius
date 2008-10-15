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

function shn_sr_store_reg_new_report($rpt_name,$rpt_desc)
{
	print "<br>this will store new report <b>$rpt_name</b> in the db with description <b>$rpt_desc</b>";
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
		
	if($rpt_name==""){ // if report name is empty 
		print "<br>empty report name, try again.";
	} else { // if report name is there then store
		//generate uuid for the report
		$report_id=shn_create_uuid('sitrep');
		
		// get the incident id
		$incident_id=$_SESSION['user_pref_ims_incident_id'];
		
		$q=" INSERT INTO sitrep_info (sitrep_info.report_id, sitrep_info.name, sitrep_info.description, sitrep_info.incident_id) VALUES ('$report_id','$rpt_name','$rpt_desc','$incident_id');";

		$res=$db->Execute($q);
		
	}
		// get group id from the url
		/*$group_id=$_GET['id'];
		
		$q="select grp_name,grp_des,grp_type,grp_type_desc from msg_people_group where m_uuid='$group_id';";
		$res=$db->Execute($q);
		*/
}
?>