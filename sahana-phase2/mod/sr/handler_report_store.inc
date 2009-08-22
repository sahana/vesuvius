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

// store new basic report information to the db
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
		
		// get the logged in user
		$user=$_SESSION['user'];
		
		// get the incident id
		$incident_id=$_SESSION['user_pref_ims_incident_id'];
		
		$q="INSERT INTO sitrep_info (sitrep_info.report_id, sitrep_info.name, sitrep_info.description, sitrep_info.incident_id) VALUES ('$report_id','$rpt_name','$rpt_desc','$incident_id');";

		$res=$db->Execute($q);
		if($res){
			$q="INSERT INTO sitrep_detail (sitrep_detail.report_id, sitrep_detail.author, sitrep_detail.status) VALUES ('$report_id','$user','create');";
			
			$res=$db->Execute($q);
			if($res){
				add_confirmation("Situation Report <strong>$rpt_name</strong> was registered successfully!");
			} else {
				add_error("Can not add Situation Report <strong>$rpt_name</strong> to the system!");	
			}
		}
	}
}

// store detail information about reports as updates
function shn_sr_store_report_update($rpt_id, $rpt_name, $rpt_summary, $rpt_event, $rpt_action, $rpt_figure)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	// check whether reports are NOT empty
	if($rpt_summary=="" && $rpt_event=="" && $rpt_action=="" && $rpt_figure==""){
		add_warning('Reports are blank. Please fill the reports and click the <strong>Update</strong> button.');
		shn_sr_report_detail_form($rpt_id);
	} else {
		
		// get the logged in user
		$user=$_SESSION['user'];
		
		// get the incident id
		$incident_id=$_SESSION['user_pref_ims_incident_id'];
		
		$q="INSERT INTO sitrep_detail (report_id, author, summary, event_dev, act, key_fig, status) VALUES ('$rpt_id','$user','$rpt_summary','$rpt_event','$rpt_action','$rpt_figure','updated');";
		
		$res=$db->Execute($q);
		if($res){
			add_confirmation("Situation Report <strong>$rpt_name</strong> was updated successfully!");
			shn_sr_report_detail_form($rpt_id, $rpt_name); // recalling the report again (modified)
		} else {
			add_error("Can not update Situation Report <strong>$rpt_name</strong> to the system!");	
		}
	}
	
}

function shn_sr_pull_report_content($rpt_id)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q="select * from sitrep_detail where report_id='$rpt_id' order by update_date desc limit 1;";
	//$q="select report_id,DATE_FORMAT(update_date,'%W %M %Y') as updated_date,author,summary,event_dev,act,key_fig,status from sitrep_detail where report_id='$rpt_id' order by update_date desc limit 1;";
	
	$res=$db->Execute($q);
	
	while (!$res->EOF)
	{
		$update_date = "{$res->fields['update_date']}";
		$author = "{$res->fields['author']}";
		$summary = "{$res->fields['summary']}";
		$event = "{$res->fields['event_dev']}";
		$action = "{$res->fields['act']}";
		$figure = "{$res->fields['key_fig']}";
		
		$res->MoveNext();
	}
	
	$result = array($update_date, $author, $summary, $event, $action, $figure);
	return $result;
}
