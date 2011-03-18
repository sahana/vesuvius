<?
/**
 * @name         Lost Person Finder Theme
 * @version      3.0
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

// array of events
$events = array();

?>
<div id="blueBack">&nbsp;</div>
<div id="disaster_selekta"><label for="event" id="eventLabel">Event </label><?selekta(); ?><script>checkEvent('<? echo $_GET['shortname']; ?>', '<? getDefaultEvent(); ?>');</script></div>
<div id="footer"><center><table id="footerTable">
		<tr>
		<td>
			<a href="http://www.nlm.nih.gov"><img src="theme/lpf3/img/nlm.png"></a>
			<a href="http://www.nih.gov"><img src="theme/lpf3/img/nih.png"></a>
			<a href="http://www.hhs.gov"><img src="theme/lpf3/img/hhs.png"></a><br>
			Developed and Hosted by the<br>
			US National Library of Medicine
		</td>
		<td>
			<a href="http://www.bethesdahospitalsemergencypartnership.org/"><img src="theme/lpf3/img/bhepp.png"></a>
			<a href="http://www.suburbanhospital.org/"><img src="theme/lpf3/img/suburban.png"></a>
			<a href="http://www.bethesda.med.navy.mil/"><img src="theme/lpf3/img/nnmc.png"></a>
			<a href="http://clinicalcenter.nih.gov/"><img src="theme/lpf3/img/clinicalcenter.png"></a><br>
			Funded through the <br>
			Bethesda Hospital Emergency Preparedness Partnership
		</td>
		<td>
			<a href="http://sahanafoundation.org"><img src="theme/lpf3/img/sahana.png"></a><br>
			Powered by<br>
			Sahana
		</td>
		</tr>
	</table>
	<div id="notice">Notice: Submission of information is voluntary. All submitted information will be made publicly available. OMB NO: 0925-0612 EXPIRATION DATE: 6/30/2013 Public reporting burden for this collection of information is estimated to average 0.08 hours per response. This estimate includes the time for reviewing instructions, gathering, and entering data. An agency may not conduct or sponsor, and a person is not required to respond to, a collection of information unless it displays a currently valid OMB control number. Send comments regarding this burden estimate or any other aspect of this collection of information, including suggestions for reducing this burden, to: NIH, Project Clearance Branch, 6705 Rockledge Drive, MSC 7974, Bethesda, MD 20892-7974, ATTN: PRA (0925-0612). Do not return the completed form to this address.<br>
	<?php
		// show build & version

		global $global;
		$revision_file = $global['approot']."/www/theme/lpf3/version";
		$time_file     = $global['approot']."/www/theme/lpf3/time";

		// only show the rev/build info on stage/production ~ not dev as version/time dont exist there or in svn
		if(file_exists($revision_file) && file_exists($time_file)) {
			// open file with the revision number in the first line
			$handle = fopen($revision_file, "r");

			// read first line. TODO: check if it's not empty, etc.
			$version = fgets($handle);

			// open file to read timestamp
			$handle2 = fopen($time_file, "r");

			// extract time
			$time = fgets($handle2);

			// print generated link
			echo "<span id=\"build\">version: <b>r".$version."</b> &nbsp; Build Time: <b>".$time."</b></span>";
		}
	?>
	</div>
	</center>
	<?php
		/*
		echo "<br>shortname(".$_GET['shortname'].")";
		echo "<br><pre>".print_r($_REQUEST, true)."</pre>";
		echo "<pre>".print_r($_SERVER, true)."</pre>";
		//echo "<br><pre>".print_r($global, true)."</pre>";
		//echo "<br><pre>".print_r($conf, true)."</pre>";
		*/
	?>
</div>
<?php


function addChildren($id, $spacer) {
	global $events;
	global $global;
	$q = "
		SELECT *
		FROM incident
		WHERE parent_id = '".$id."'
		ORDER BY date DESC;
	";
	$res = $global['db']->Execute($q);

	// add child to the array and then find its children recursively
	while($row = $res->FetchRow() ){
		$row['name'] = $spacer.$row['name'];
		$events[] = $row;
		addChildren($row['incident_id'], $spacer."&nbsp;&nbsp;&nbsp;&nbsp;");
	}
}



// Displays the Event/Disaster Dropdown menu and allows redirection via the js code
function selekta() {
	global $global;
	global $conf;
	global $events;

	echo "<select id=\"disasterList\" onchange=\"changeEvent(this.value);\">";

	if(isset($_SESSION['group_id'])) {
		$groupSql = "(private_group IS NULL OR private_group = '".$_SESSION['group_id']."')";
	} else {
		$groupSql = "private_group IS NULL";
	}

	$q = "
		SELECT *
		FROM incident
		WHERE parent_id is NULL
		AND ".$groupSql."
		ORDER BY date DESC;
	";
	$res = $global['db']->Execute($q);

	// add disasters to the array
	while($row = $res->FetchRow() ){
		$events[] = $row;
		addChildren($row['incident_id'], "&nbsp;&nbsp;&nbsp;&nbsp;");
	}

	foreach($events as $row) {
		if($_GET['shortname'] == $row['shortname']) {
			$selected = "selected";
		} else {
			$selected = "";
		}
		if($row['closed'] == "1") {
			echo "<option ".$selected." value=\"".$row['shortname']."\" class=\"110 grey\">".$row['name']."</option>";
		} else {
			echo "<option ".$selected." value=\"".$row['shortname']."\" class=\"110\">".$row['name']."</option>";
		}
	}
	echo "</select>";
}



// Check whether we are on the default event when we enter the site
function getDefaultEvent() {
	global $global;
	global $conf;

	$sql = "SELECT shortname FROM incident WHERE `default` = 1 LIMIT 1;";
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		foreach($arr as $row) {
			echo $row['shortname'];
		}
	}
}

