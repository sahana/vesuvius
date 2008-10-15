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

// Display all the reports as a list
function shn_sr_view_reports($type)
{
	// get the logged in user
	$user=$_SESSION['user'];
	
	// check the requested type
	if($type=='all'){
		// display all the reports
		
	} else {
		// display only for this incident
		
		// incident id
		$incident_id=$_SESSION['user_pref_ims_incident_id'];
			
		
	}
}


?>