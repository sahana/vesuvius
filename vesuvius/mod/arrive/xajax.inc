<?php
/**
 * @name         Arrival Rate
 * @version      2
 * @package      arrive
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1206
 */


global $global;

// create an array if it does not already exist
$global['xajax_functions'] = array();

// publicly register accessible xajax funtions
array_push($global['xajax_functions'], 'arrive_append_log');
array_push($global['xajax_functions'], 'arrive_fetch_last_updated');
array_push($global['xajax_functions'], 'arrive_show_list');
array_push($global['xajax_functions'], 'arrive_add_spacer');

// adds a message to the log div @ tail
function arrive_append_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAppend('rezLog','innerHTML',$message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// fetches the last_updated time (to find out if we need to update GUI)
function arrive_fetch_last_updated($all, $initial) {
	global $global;
	$last_updated = null;

	if($all == 'true') {
		$q = "
			SELECT *
			FROM arrival_rate
			ORDER BY arrival_time DESC
			LIMIT 1;
		";
	} else {
		$q = "
			SELECT *
			FROM arrival_rate a, incident i
			WHERE i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
			AND i.incident_id = a.incident_id
			ORDER BY arrival_time DESC
			LIMIT 1;
		";
	}

	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "fetch last updated 1 ((".$q."))"); }

	if($result != NULL && !$result->EOF) {
		$last_updated = $result->fields['arrival_time'];
		$global['xajax_res']->addScript("updateLastArrival('".$last_updated."', ".$initial.");");
	}
	return $global['xajax_res']->getXML();
}


// spaces out the log with a $val string/character
function arrive_add_spacer($val) {
	global $global;
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $val);
	return $global['xajax_res']->getXML();
}


// reloads the mainArea div with information of what pages we have
function arrive_show_list($isAnUpdate, $allEvents) {
	global $global;
	$htmlLog = "";
	$htmlMain = "";
	$count = 0;
	$eo = 0;

	if($isAnUpdate == 'true') {
		$isAnUpdate = true;
	} else {
		$isAnUpdate = false;
	}
	if($allEvents == 'true') {
		$allEvents = true;
	} else {
		$allEvents = false;
	}

	$htmlMain .= "
		<table class=\"emTable\">
			<tr>
				<td style=\"font-size: 120%; padding-left: 8px; text-align: center;\" ><b>Arrival Time</b></td>
				<td style=\"font-size: 120%; padding-left: 8px; text-align: center;\" ><b>Event</b></td>
				<td style=\"font-size: 120%; padding-left: 8px; text-align: center;\" ><b>Person UUID</b></td>
				<td style=\"font-size: 120%; padding-left: 8px; text-align: center;\" ><b>Person Name</b></td>
			</tr>
	";

	// get list of last 10 arrivals...
	if($allEvents) {
		$q = "
			SELECT *
			FROM arrival_rate a, incident i, person_uuid p
			WHERE i.incident_id = a.incident_id
			AND p.p_uuid = a.person_uuid
			ORDER BY arrival_time DESC
			LIMIT 10;
		";
	} else {
		$q = "
			SELECT *
			FROM arrival_rate a, incident i, person_uuid p
			WHERE i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
			AND i.incident_id = a.incident_id
			AND p.p_uuid = a.person_uuid
			ORDER BY arrival_time DESC
			LIMIT 10;
		";
	}
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "arrive show list 1 ((".$q."))"); }
	while($row = $result->FetchRow() ){

		$count++;

		if($isAnUpdate && $count == 1) {
			$htmlLog .= "<br>New person arrived >> <b>".$row['person_uuid']." </b>";
		}

		// find class to color the row...
		if( $eo == 0 ) {
			$evenOddClass = "mainRowEven";
		} else {
			$evenOddClass = "mainRowOdd";
		}

		$htmlMain .= "
			<tr>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$row['arrival_time']."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$row['name']."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['person_uuid'])."\" target=\"_blank\">".$row['person_uuid']."</a></td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$row['full_name']."</td>
			</tr>
		";

		$eo++;
		if($eo == 2) {
			$eo = 0;
		}
	}

	if($count == 0) {
		$htmlMain .= "<tr><td colspan=4 class=\"mainRowEven\" style=\"text-align: center;\">No persons have arrived thus far.</td></tr>";
	}
	$htmlMain .= "</table>";

	$pageControlHtml = '
		<input class="styleTehButton" id="allButton" type="button" onclick="arrive_append_log(\'<br>Showing arrivals from <b>ALL events</b>.\'); showAll(true);" value="Show Arrivals from ALL events">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton" id="currentButton" type="button" onclick="arrive_append_log(\'<br>Showing arrivals from <b>only the current event</b>.\'); showAll(false);" value="Show Arrivals from only the current event">
	';

	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $pageControlHtml);
	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $htmlMain);
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $htmlLog);
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500); updateMenu();");
	return $global['xajax_res']->getXML();
}




