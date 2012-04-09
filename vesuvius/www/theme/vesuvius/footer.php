<?
/**
 * @name         Vesuvius Theme
 * @version      3.0
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

/*
// array of events
$events = array();
*/

?>
<div id="blueBack">&nbsp;</div>
<div id="footer"><center><table id="footerTable">
		<tr>
		<td>
			<a href="http://www.nlm.nih.gov"><img src="theme/lpf3/img/nlm.png"></a>
			<a href="http://www.nih.gov"><img src="theme/lpf3/img/nih.png"></a>
			<a href="http://www.hhs.gov"><img src="theme/lpf3/img/hhs.png"></a><br>
			Based on the People Locator developed<br>
			by the US National Library of Medicine
		</td>
		<td>
			<a href="http://www.bethesdahospitalsemergencypartnership.org/"><img src="theme/lpf3/img/bhepp.png"></a>
			<a href="http://www.suburbanhospital.org/"><img src="theme/lpf3/img/suburban.png"></a>
			<a href="http://www.bethesda.med.navy.mil/"><img src="theme/lpf3/img/nnmc.png"></a>
			<a href="http://clinicalcenter.nih.gov/"><img src="theme/lpf3/img/clinicalcenter.png"></a><br>
			Development funded through the <br>
			Bethesda Hospital Emergency Preparedness Partnership
		</td>
		<td>
			<a href="http://sahanafoundation.org"><img src="theme/lpf3/img/sahana.png"></a><br>
			Powered by<br>
			Sahana Vesuvius
		</td>
		</tr>
	</table>
	<div id="notice"></div>
	</center>
	<?php
		//echo "<br><pre>".print_r($_REQUEST, true)."</pre>";
		//echo "<pre>".print_r($_SERVER, true)."</pre>";
		//echo "<br><pre>".print_r($global, true)."</pre>";
		//echo "<br><pre>".print_r($_SESSION, true)."</pre>";
		//echo "<br><pre>".print_r($conf, true)."</pre>";
	?>
</div>
<?php

/*
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
*/
