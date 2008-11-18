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
function shn_sr_report_list($type, $method='all')
{
	if ($type=="view") echo "<h1>View Situation Reports</h1>";
	elseif ($type=="update") echo "<h1>Update Situation Reports</h1>";
	
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
		//$q="SELECT sitrep_info.report_id, sitrep_info.name, sitrep_info.description, DATE_FORMAT(sitrep_info.create_date, '%b %D, %Y') AS create_date, MAX(DATE_FORMAT(sitrep_detail.update_date, '%b %D, %Y -  %r')) AS update_date, sitrep_detail.author, sitrep_detail.status, sitrep_info.incident_id FROM sitrep_info inner join sitrep_detail GROUP BY report_id;";
		//$q="SELECT sitrep_info.report_id, sitrep_info.name, sitrep_info.description, DATE_FORMAT(sitrep_info.create_date, '%b %D, %Y') AS create_date, MAX(DATE_FORMAT(sitrep_detail.update_date, '%b %D, %Y - %r')) AS update_date, MAX(sitrep_detail.author) AS author, MAX(sitrep_detail.status) AS status, sitrep_info.incident_id FROM sitrep_info inner join sitrep_detail GROUP BY report_id;";
		$q=" select t1.report_id, t1.name, t1.description, MAX(t2.author) as author, MAX(t2.status) as status, DATE_FORMAT(t1.create_date,'%b %D %Y') as create_date, MAX(DATE_FORMAT(t2.update_date,'%b %D, %Y - %r')) as update_date, t1.incident_id from sitrep_info as t1 inner join sitrep_detail t2 on t1.report_id=t2.report_id group by report_id;";
		//print $q;
	} else {
		// display only for this incident
		//$q="SELECT sitrep_info.report_id, sitrep_info.name, sitrep_info.description, DATE_FORMAT(sitrep_info.create_date, '%b %D, %Y') AS create_date, DATE_FORMAT(sitrep_detail.update_date, '%b %D, %Y -  %r') AS update_date, sitrep_detail.author, sitrep_detail.status, sitrep_info.incident_id FROM sitrep_info inner join sitrep_detail WHERE  incident_id='$incident_id';";	
	}
	
	//print $q;
	
	$res=$db->Execute($q);
	
	shn_form_fopen("",null,array ('req_message' => false));
	shn_form_fsopen('Report List');
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
		} elseif ($status=="updated"){
			$status="<font color='green'>Updated</font>";	
		}
		?>
		<tr>
			<td><a href="index.php?mod=sr&act=<?php // this code snipt is used for both report update and report view
													if($type=="update") {
														echo "report_update";
													} elseif ($type=="view") {
														echo "report_view";
													}		
											   ?>&id=<?php echo $rpt_id; ?>&rpt=<?php echo $name ?>"><strong><?php print $name; ?></strong></a></td>
			<td><?php print $desc; ?></td>
			<td><?php print "<center>$status</center>"; ?></td>
			<td><?php print "<center>$author</center>"; ?></td>
			<td><?php print "<center>$create_date</center>"; ?></td>
			<td><?php print "<center>$update_date</center>"; ?></td>
		</tr>
		<?php

		$res->MoveNext();
	}
	
	shn_form_fsclose();
	print "</table>";
	 
	print "<p><br>Select:&nbsp;&nbsp;&nbsp;<a href='index.php?mod=sr&act=default'>Back</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=sr&act=";
	if ($type=="update") {
		print "update'";
	} else {	
		print "view";
	} print ">Refresh</a>&nbsp;&nbsp;</p>";
	shn_form_fclose();
	
	
	
}

// Switch board
function _shn_switch_board($switches)
{
	print "<p><br>Select:&nbsp;&nbsp;&nbsp;";
	
	switch ($switches) {
		
		case "back":
			
		break;
		
		case "refresh":
			
		break;	
	}
	
	print "<br></p>";
}

// Check whether the report is already in the db
function shn_sr_chk_rpt_name($report_name)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q="SELECT name,report_id FROM sitrep_info;";
	
	$res=$db->Execute($q);
	
	$x=0;
	while (!$res->EOF)
	{
		//$list[$x] = $res->fields['name'];
		$list[($res->fields['report_id'])] = ($res->fields['name']);
		
		//$list[$x][1] = $res->fields['report_id'];
		$list[$x] = strtolower($list[$x]);// convert all of them to lower case
		
		$x=$x+1;
		$res->MoveNext();
	}
	//print_r($list);
	
	// Check whether the given report name is available in the db
	
	// convert all the report names to lowercase
	$report_name = strtolower($report_name);
	
	if (in_array($report_name,$list)){
		$chk=array("yes");
	} else {
		return $chk="no";
	}
}

// Display a given (id) report
function shn_sr_pull_report($rpt_id)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q="SELECT r1.report_id, r1.name, r2.author, r2.summary, r2.event_dev, r2.act, r2.key_fig, r2.status, DATE_FORMAT(r2.update_date,'%b %D, %Y - %r') AS update_date FROM sitrep_detail AS r2 INNER JOIN sitrep_info r1 ON r1.report_id=r2.report_id WHERE r1.report_id='$rpt_id' ORDER BY update_date DESC LIMIT 1;";
	
	$res=$db->Execute($q);

	 while(!$res->EOF)
	{
		$rpt_id = $res->fields['report_id'];
		$name = $res->fields['name'];
		$author = $res->fields['author'];
		$summary = $res->fields['summary'];
		$event = $res->fields['event_dev'];
		$action = $res->fields['act'];
		$figure = $res->fields['key_fig'];
		$status = $res->fields['status'];
		$update_date = $res->fields['update_date'];
		$res->MoveNext();
	}
	
	shn_sr_view_report($rpt_id, $name, $author, $summary, $event, $action, $figure, $status, $update_date);
}
?>