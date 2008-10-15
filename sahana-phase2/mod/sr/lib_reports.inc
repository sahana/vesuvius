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
function shn_sr_view_reports($method='all')
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	// get the logged in user
	$user=$_SESSION['user'];
	
	// incident id
	$incident_id=$_SESSION['user_pref_ims_incident_id'];
	
	// check the requested type
	if($method=='all'){
		// display reports for all the incident
		$q="SELECT sitrep_info.report_id, sitrep_info.name, sitrep_info.description, sitrep_info.create_date, sitrep_detail.update_date, sitrep_detail.author, sitrep_detail.status, sitrep_info.incident_id FROM sitrep_info, sitrep_detail;";
	} else {
		// display only for this incident
		$q="SELECT sitrep_info.report_id, sitrep_info.name, sitrep_info.description, sitrep_info.create_date, sitrep_detail.update_date, sitrep_detail.author, sitrep_detail.status, sitrep_info.incident_id FROM sitrep_info, sitrep_detail WHERE  incident_id='$incident_id';";	
	}
	
	$res=$db->Execute($q);
	
	?>
	<table width="100%">
            <thead>
			<tr>
				<td>Report</td>
				<td>Description</td>
	 			<td>Status</td>
	 			<td>Author</td>
	 			<td>Created Date</td>
	 			<td>Last Update</td>
			</tr>
	   </thead>
        <tbody>
    <?php    
	while(!$res->EOF)
	{
		$rpt_id = $res->fields['report_id'];
		$name = $res->fields['name'];
		$desc = $res->fields['description'];
		$create_date = $res->fields['create_date'];
		$update_date = $res->fields['update_date'];
		$author = $res->fields['author'];
		$status = $res->fields['status'];
		$incident_id = $res->fields['incident_id'];
		
		if($status=="create") {
			$status="<font color='red'>New</font>";
		}
		
		?>
		<tr>
			<td><a href="index.php?mod=sr&act=view"><strong><?php print $name; ?></strong></a></td>
			<td><?php print $desc; ?></td>
			<td><?php print "<center>$status</center>"; ?></td>
			<td><?php print "<center>$author</center>"; ?></td>
			<td><?php print "<center>$create_date</center>"; ?></td>
			<td><?php print "<center>$update_date</center>"; ?></td>
		</tr>
		<?php
		$res->MoveNext();
	}
	print "</table>";
}


?>