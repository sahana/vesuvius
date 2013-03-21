<?php
/**
 * @name         Expiry Queue
 * @version      0.1
 * @package      eq
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1102
 */

global $global;

// create an array as it does not exist previosuly and will make warnings
$global['xajax_functions'] = array();

// publicly register accessible xajax funtions
array_push($global['xajax_functions'],'em_append_log');
array_push($global['xajax_functions'],'em_prepend_log');
array_push($global['xajax_functions'],'em_show_message');
array_push($global['xajax_functions'],'em_show_events');
array_push($global['xajax_functions'],'em_perform_edit');
array_push($global['xajax_functions'],'em_perform_delete');
array_push($global['xajax_functions'],'em_perform_insert');
array_push($global['xajax_functions'],'em_perform_save');
array_push($global['xajax_functions'],'em_perform_help');

// adds a message to the log div @ tail
function em_append_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAppend('rezLog','innerHTML',$message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ head
function em_prepend_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addPrepend('rezLog','innerHTML',$message);
	return $global['xajax_res']->getXML();
}


// shows a status message before another ajax function is executed
function em_show_message($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAssign('rezMain','innerHTML','<div class="loadingMessage"><center><blink>'.$message.'</blink></center></div>');
	return $global['xajax_res']->getXML();
}


// reloads the mainArea div with information of what pages we have
function em_show_events($internal = FALSE) {
	global $conf;
	global $global;
	$htmlLog = "";
	$htmlMain = "";
	$total = 0;
	$char = "<span style=\"text-shadow: 1px 1px 1px #000;\">▶</span>";

	$htmlMain .= "
		<table class=\"emTable\">
			<tr>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Event</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Short Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Type</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Default</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Visibility</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Open</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Edit</b></td>
			</tr>
	";

	// get list of Disasters
	$q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_groups g
		ON i.private_group = g.group_id
		WHERE i.parent_id is NULL
		ORDER BY date desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 1"); }

	// find out how many disasters we have
	$disasters = array();
	$dcount = 0;
	while($row = $result->FetchRow() ){
		$disasters[$dcount] = $row;
		$dcount++;
	}
	$total = $dcount;

	$i = 1; // we start with the 2nd row of teh table (header?) :)
	$eo = 0; // 2nd row is odd ~ of course u knew that computers start counting at 0 :P
	while($i <= $dcount) {
		$row           = $disasters[$i-1];
		$type          = "<b><span style=\"color: red;\">".$char."</span> Disaster</b>";
		$disaster_id   = $row['incident_id'];
		$type2         = $row['type'];
		$longname      = $row['name'];
		$shortname     = $row['shortname'];
		$default       = $row['default'];
		$private_group = $row['private_group'];
		$closed        = $row['closed'];

		// get text for default event
		if($default == "1") {
			$defaultText = "DEFAULT";
		} else {
			$defaultText = "-";
		}

		// show group name or public if null group
		if($private_group == NULL) {
			$groupText = "PUBLIC";
		} else {
			$groupText = $row['group_name'];
		}

		// generate open close text
		if((int)$closed == 0) {
			$closedText = "OPEN";
		} else if((int)$closed == 1) {
			$closedText = "CLOSED";
		} else if((int)$closed == 2) {
			$closedText = "CLOSED(PF)";
		} else {
			$closedText = "OPEN";
		}

		// find class to color the row...
		if( $eo == 0 ) {
			$evenOddClass = "mainRowEven";
		} else {
			$evenOddClass = "mainRowOdd";
		}

		$htmlMain .= "
			<tr>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\"><a href=\"#\" onclick=\"em_append_log('Editting Event #<b>".$disaster_id."</b> ...<br>'); em_perform_edit(".$disaster_id.");\" value=\"Edit\">".$longname."</a></td>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>

<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"em_append_log('Editting Event #<b>".$disaster_id."</b> ...<br>'); em_perform_edit(".$disaster_id.");\" value=\"Edit\"></td>

			</tr>
		";


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// list all incidents with this disaster as a parent
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// get list of incidents
		$q = "
			SELECT *
			FROM incident i
			LEFT JOIN sys_user_groups g
			ON i.private_group = g.group_id
			WHERE i.parent_id = ".$disaster_id."
			ORDER BY date desc;
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 2"); }

		// find out how many incidents we have
		$incidents = array();
		$icount = 0;
		while($row = $result->FetchRow() ){
			$incidents[$icount] = $row;
			$icount++;
		}
		$total += $icount;

		$j = 1;
		while($j <= $icount) {
			$eo++;
			if($eo == 2) {
				$eo = 0;
			}

			$row           = $incidents[$j-1];
			$type          = "<b> &nbsp; &nbsp; <span style=\"color: orange;\">".$char."</span> &nbsp; Incident</b>";
			$incident_id   = $row['incident_id'];
			$type2         = $row['type'];
			$longname      = $row['name'];
			$shortname     = $row['shortname'];
			$default       = $row['default'];
			$closed        = $row['closed'];
			$private_group = $row['private_group'];

			// get text for default event
			if($default == "1") {
				$defaultText = "DEFAULT";
			} else {
				$defaultText = "-";
			}

			// show group name or public if null group
			if($private_group == NULL) {
				$groupText = "PUBLIC";
			} else {
				$groupText = $row['group_name'];
			}

			// generate open close text
			if((int)$closed == 0) {
				$closedText = "OPEN";
			} else if((int)$closed == 1) {
				$closedText = "CLOSED";
			} else if((int)$closed == 2) {
				$closedText = "CLOSED(PF)";
			} else {
				$closedText = "OPEN";
			}

			// find class to color the row...
			if( $eo == 0 ) {
				$evenOddClass = "mainRowEven";
			} else {
				$evenOddClass = "mainRowOdd";
			}

			$htmlMain .= "
				<tr>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$longname."</td>
					<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>
					<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: em_append_log('Editting Event #<b>".$incident_id."</b> ...<br>'); em_perform_edit(".$incident_id.");\">Edit</a></td>
				</tr>
			";

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// list all events with this incident as a parent
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// get list of events
			$q = "
				SELECT *
				FROM incident i
				LEFT JOIN sys_user_groups g
				ON i.private_group = g.group_id
				WHERE i.parent_id = ".$incident_id."
				ORDER BY date desc;
			";
			$result = $global['db']->Execute($q);
			if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 3"); }

			// find out how many events we have
			$events = array();
			$ecount = 0;
			while($row = $result->FetchRow() ){
				$events[$ecount] = $row;
				$ecount++;
			}
			$total += $ecount;

			$k = 1;
			while($k <= $ecount) {
				$eo++;
				if($eo == 2) {
					$eo = 0;
				}

				$row           = $events[$k-1];
				$type          = "<b> &nbsp; &nbsp; &nbsp; &nbsp; <span style=\"color: yellow;\">".$char."</span> &nbsp; Event</b>";
				$event_id      = $row['incident_id'];
				$type2         = $row['type'];
				$longname      = $row['name'];
				$shortname     = $row['shortname'];
				$default       = $row['default'];
				$closed        = $row['closed'];
				$private_group = $row['private_group'];

				// get text for default event
				if($default == "1") {
					$defaultText = "DEFAULT";
				} else {
					$defaultText = "-";
				}

				// show group name or public if null group
				if($private_group == NULL) {
					$groupText = "PUBLIC";
				} else {
					$groupText = $row['group_name'];
				}

				// generate open close text
				if((int)$closed == 0) {
					$closedText = "OPEN";
				} else if((int)$closed == 1) {
					$closedText = "CLOSED";
				} else if((int)$closed == 2) {
					$closedText = "CLOSED(PF)";
				} else {
					$closedText = "OPEN";
				}

				// find class to color the row...
				if( $eo == 0 ) {
					$evenOddClass = "mainRowEven";
				} else {
					$evenOddClass = "mainRowOdd";
				}

				$htmlMain .= "
					<tr>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."</td>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$longname."</td>
						<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$shortname."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$type2."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$defaultText."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$groupText."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$closedText."</td>
						<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: em_append_log('Editting Event #<b>".$event_id."</b> ...<br>'); em_perform_edit(".$event_id.");\">Edit</a></td>
					</tr>
				";
				$k++;
			}
			// end events
			///////////////////////////////////////////////////////////////////////////////////////////////////////................................

			$j++;
		}
		// end incidents
		////////////////////////////////////////////////////////////////////////////////////////////////////....................................

		// spacer row except last row
		if($i != $dcount) {
			$htmlMain .= "<tr><td class=\"emTableSpacer\" colspan=8>&nbsp;</td></tr>";
		}
		$i++;
		$eo = 0; // reset
	}
	// end disasters
	////////////////////////////////////////////////////////////////////////////////////////////////..................................

	if ($dcount == 0) {
		$htmlMain .= "<tr><td colspan=8 class=\"mainRowEven\" style=\"text-align: center;\">No Events have been created thus far.</td></tr>";
	}
	$htmlMain .= "</table>";

	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';

	//---- internally, no ajax, just pass back data
	if ( $internal ) {
		return $htmlMain;
	} else {
		$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

		$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezMain','innerHTML',$htmlMain);

		$htmlLog .= "Found <b>".$total."</b> event(s).<br>";
		$global['xajax_res']->addAppend('rezLog','innerHTML',$htmlLog);
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
		return $global['xajax_res']->getXML();
	}
}



// shows help
function em_perform_help() {
	global $global;

	// help content
	$pageMainHtml = "
		<h2>Adding a New Event</h2>
		<ul>
			<li>Clicking on the new Event button will create a new event with default sample data.</li>
			<li>New events default to being OPEN, TEST, Non-DEFAULT, private to the admin group, and located at NLM.</li>
			<li>Once the new event is created, you are immediately redirected to begin editing it.</li>
		</ul>
		<br>
		<h2>Editing an Existing Event</h2>
		<ul>
			<li>Any changes made to an event are not saved until you click the <b>Save Changes</b> button.</li>
			<li>If you click <b>Cancel Edit / Close</b> any changes are not saved and your edits lost.</li>
			<li><b>Long Name</b> can be up to 60 characters long althought it is recommended to keep it as short as possible.</li>
			<li><b>Short Name</b> can be up to 16 characters long and can only contain lowercase letters and numbers. Any spaces or special characters will be removed and uppercase characters converted to lowercase when saved.</li>
			<li><b>Parent Event</b> is used to associate an event with another event as a parent. ie. creating a new incident or new event, you can choose the disaster or incident to use as their parent. If an event already has children associated with it, this box will be non-editable. So, in order to change the parent of an event of this type, you must first dissociate all children first.</li>
			<li><b>Type</b> can only be changed for <b>Disasters</b> (top level events). If you are editing an <b>incident</b> (level 2) or an <b>event</b> (level 3), then this value is inherited from the disaster parent or grandparent.</li>
			<li><b>Visibility</b> shares the same inheritance rules as <b>Type</b>.</li>
			<li><b>Date</b>: should be entered in the form <b>2010-01-31</b> (YYYY-MM-DD).</li>
			<li><b>Location</b> is used to help identify where an event happened/is occurring. Begin typing a street address into the first box and it will autocomplete allowing you to use the arrow keys to select an address or you may hit enter to search on a fully typed in address. Additionally, you can simply click the <b>Detect My Current Location</b> button to attempt to self-locate yourself using the HTML5 location spec.</li>
		</ul>
		<br>
		<h2>Deleting Events</h2>
		<ul>
			<li>In order to delete an event from the events list page, click on edit for the event you wish to delete.</li>
			<li>Deleting an event will remove the event from the database and remove all relationship data that any other piece of data has with this event.</li>
			<li>Data that is related to an event, ie. person(s) or other sahana entitites attached to this event are not harmed, but may be left dangaling unassociated with any event.</li>
			<li>It is recommended that the other associated data be first removed via some other means (ie. Delete Person Module) prior to deleting an event.</li>
			<li>Events cannot be deleted if they have children. In order to delete these events, the children must be first deleted.</li>
			<li>Events <b>cannot</b> be un-deleted.</li>
			<li>Only administrators can delete events.</li>
		</ul>
		<br>
		<h2>User Interface Definitions</h2>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Event</b>: specifies if the event is a <b>Disaster</b>, an <b>Incident</b>, or an <b>Event</b>. The three levels proceed in this order with <b>Disaster</b> being the top level event. This heiarchy exists so that disaster can can sub-incidents and in turn, incidents may have sub-events.</li>
			<li><b>Name</b>: is the full (long) name of the event.</li>
			<li><b>Short Name</b>: is the exact short string that classifies which event the site will begin handling when passed in via this URL.</li>
			<li><b>Type</b>: indicates whether the event is a <b>REAL</b> or a <b>TEST</b> event. This is spcified by per disaster and all incidents and events that are children of the particular disaster inherit this value from the parent.</li>
			<li><b>Default</b>: shows which event is the default event a user see when they come to the site.</li>
			<li><b>Visibility</b>: shows whether an event is visible to the public (enyone may view it) or whether it is only visible to a specific user class.</li>
			<li><b>Open</b>: an event that is <b>CLOSED</b> cannot accept new persons in the RAP (Report A Person), PLS (Person Locator web Services), and MPRES (Missing Person Registry Email Services). <b>OPEN</b> events allow new persons to be accepted via these three avenues. <b>CLOSED(PF)</b> events are the same as <b>CLOSED</b> events except that they allow the reporting of persons via the Google Person Finder.</li>
			<li><b>Edit</b>: is the link you click on to edit this particular event.</li>
		</ul>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help2.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Event ID#</b> is the internal event number used by Sahana is is automatically assigned.</li>
			<li><b>Description</b>: is a paragraph of text describing the event in more detail.</li>
			<li><b>Date</b>: the date on which the event occurred.</li>
			<li><b>Street Address</b>: is used to lookup a location when editing or creating a new event.</li>
			<li><b>Latitude / Longitude</b>: non-editable fields which are updated as the map is updated.</li>
		</ul>
		<img alt=\"IE6,7,8 dont support inline images, please upgrade to IE9 or Google Chrome, Firefox, Safari\" class=\"inlineHelp\" src=\"data:image/png;base64,".base64_encode(file_get_contents($global['approot'].'/mod/em/help3.png'))."\">
		<br>
		<br>
		<ul>
			<li><b>Log</b>: the log displays notifications as you are using the Event Manager to let you understand what is going on. Example: when started it shows how many events are presnet or when saving or canceling an edit, the status of this operation appears in the log so that a user can see when this operation is complete.

		</ul>
		<br>
		<br>
	";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Closing Help...<br>\'); setTimeout(\'em_show_events();\', 250);" value="Close Help">
	';

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $pageMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $pageControlHtml);
	return $global['xajax_res']->getXML();
}



// find the root parent of the given event...if event is root event, return -1
function em_find_root_parent($eventId) {
	global $global;
	$q = "
		SELECT *
		FROM `incident`
		WHERE incident_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "find root parent 1"); }
	$row = $result->FetchRow();
	$parent = $row['parent_id'];

	// event is a root event, return -1
	if($parent == null) {
		return -1;

	// check if parent event is a root event
	} else {
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$parent."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "find root parent 2"); }
		$row = $result->FetchRow();
		$grandParent = $row['parent_id'];

		if($grandParent == null) {
			return $parent;
		} else {
			return $grandParent;
		}
	}
}



// find if the event has any children
function em_event_has_child($eventId) {
	global $global;
	$q = "
		SELECT count(*)
		FROM `incident`
		WHERE parent_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "has child 1"); }
	$row = $result->FetchRow();
	if($row['count(*)'] > 0) {
		return true;
	} else {
		return false;
	}
}




// save all children visibilities and types
function em_save_children($eventId, $group, $type) {
	global $global;

	// update all children
	$q = "
		UPDATE incident
		SET
			type          = '".$type."',
			private_group = ".$group."
		WHERE parent_id       = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save children 1"); }


	// get list of all children, recurse
	$q = "
		SELECT *
		FROM incident
		WHERE parent_id = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save children 2"); }
	while($row = $result->FetchRow()) {
		em_save_children($row['incident_id'], $group, $type);
	}
}



// saves the event attributes to the database
function em_perform_save($page_id, $rj) {
	global $global;
	$useDerived = false;
	$passOnGenes = false;
	$r = json_decode($rj, true);
	$log = "";
	$suggest = false;

	$eventId     = mysql_real_escape_string((int)$r['eventId']);
	$name        = mysql_real_escape_string($r['longName']);

	$shortName   = $r['shortName'];
	$shortName   = trim($shortName);
	$shortName   = preg_replace("/[^a-zA-Z0-9\s]/", "", $shortName);
	$shortName   = strtolower($shortName);
	$shortName   = mysql_real_escape_string($shortName);

	if($r['shortName'] != $shortName) {
		$log .= "<span style=\"color: red;\"><b>Short Name field revised to match rules: 1) lowercase letters and numbers only 2) max 16 characters in length.</span></b><br>";
		$suggest = true;
	}
	if(strlen($shortName) < 1) {

		$log .= "<span style=\"color: red;\"><b>Since the Short Name field was too short, a new one has been auto-generated for you.</span></b><br>";
		$suggest = true;
		$shortName = "event".date("mdGis");
	}
	if($suggest) {
		$log .= "<span style=\"color: red;\"><b>You may wish to <a onclick=\"javascript: em_append_log('Editting Event #<b>".$eventId."</b> ...<br>'); em_perform_edit(".$eventId.");\">edit</a> this event again to make corrections to the new Short Name: </span>".$shortName."</b><br>";
	}


	$description = mysql_real_escape_string($r['eventDescription']);
	$externalReport = mysql_real_escape_string($r['externalReport']);
	$date        = mysql_real_escape_string($r['eventDate']);
        $pfifUrl     = mysql_real_escape_string($r['pfifUrl']);
        $pfifSync    = $r['pfifSync'];
	$street      = mysql_real_escape_string($r['street']);
	$latitude    = (double)$r['latitude'];
	$longitude   = (double)$r['longitude'];

	// Check for inherited properties ---
	// this is server side validation, we check even if derived parameters are passed

	// check if event its a child of other events
	$parentId = em_find_root_parent($eventId);
	if($parentId >= 0) {
		// user derived values
		$useDerived = true;

	// so, we are a root event, should we pass on teh traits? check if we have children
	} else if(em_event_has_child($eventId)) {
		// update children when the time comes
		$passOnGenes = true;
	}


	// if we are using derived values, find them
	if($useDerived) {
		$q = "
			SELECT *
			FROM `incident`
			WHERE incident_id = '".$parentId."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 1"); }
		$row = $result->FetchRow();
		$visibilityDerived = $row['private_group'];
		$typeDerived       = $row['type'];

	}


	// formulate parent
	$parent = (int)$r['eventParent'];
	if($parent == -1) {
		$parent = "NULL";
	} else {
		$parent = "'".$parent."'";
	}


	// formulate type
	if($useDerived || $r['eventType'] == "DERIVE") {
		$type = $typeDerived;
	} else {
		$type = $r['eventType'];
		if(($type != "REAL") && ($type != "TEST")) {
			$type = "TEST";
		}
	}


	// formulate default
	$default = (int)$r['eventDefault'];
	if($default == 1) {
		// return to non-default the current default
		$q = "
			UPDATE incident
			SET `default` = NULL
			WHERE `default` = '1';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 2"); }
		$row = $result->FetchRow();
		$default = "'1'";
	} else {
		$default = "NULL";
	}

	// check for bad values
	$closed = (int)$r['eventClosed'];
	if(($closed < 0) || ($closed > 2)) {
		$closed = 0;
	}

	// formulate group
	$group = (int)$r['eventVisibility'];
	if($useDerived || ($group == -2)) {
		if($visibilityDerived == null) {
			$group = "NULL";
		} else {
			$group = "'".$visibilityDerived."'";
		}
	} else {
		if( $group == -1) {
			$group = "NULL";
		} else {
			$group = "'".$group."'";
		}
	}

	// save the revision
	$q = "
		UPDATE incident
		SET
			name            = '".$name."',
			shortname       = '".$shortName."',
			description     = '".$description."',
			date            = '".$date."',
			latitude        = '".$latitude."',
			longitude       = '".$longitude."',
			type            = '".$type."',
			private_group   = ".$group.",
			closed          = ".$closed.",
			`default`       = ".$default.",
			parent_id       = ".$parent.",
			street          = '".$street."',
			external_report = '".$externalReport."'
		WHERE incident_id       = '".$eventId."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 3"); }

        $pfifName = 'google'.$shortName;  // repository name = "google"+shortname
        $q = "
                UPDATE pfif_repository
                SET
                        name            = '".$pfifName."',
                        base_url        = '".$pfifUrl."',
                        sched_interval_minutes = '".$pfifSync."'
                WHERE incident_id       = '".$eventId."' AND name LIKE 'google%';
        ";
        $result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "save event 4"); }

	// update visibility and type of children events.......
	if($passOnGenes) {
		em_save_children($eventId, $group, $type);
	}

	$log .= "Event #<b>".$page_id."</b> <span style=\"color: green;\">Saved</span>.<b><br>";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);
	$global['xajax_res']->addAssign('rezMain', 'innerHTML', em_show_events(TRUE));
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $log);
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// delete a page
function em_perform_delete($incident_id, $confirm) {
	global $global;

	if ($confirm == "true") {

		//---- delete the incident from the db
		$q = "
			DELETE from incident
			WHERE incident_id = '".$incident_id."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "delete 1"); }

		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Event <b>#'.$incident_id.'</b> <span style="color: red;">Deleted</span>.<br>');
	} else {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', "Delete operation aborted.<br>");
	}

	//---- update UI
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Creating a new Event...<br>\'); em_perform_edit(0);" value="Create a new Disaster / Incident / Event">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: em_append_log(\'Opening Help...<br>\'); em_perform_help();" value="Help">
	';
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', em_show_events(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// create a new page with default content and return its new page_id
function em_perform_new() {
	global $global;

	$group = $_SESSION['group_id'];

	// generate the new event index
	require_once($global['approot']."/inc/lib_uuid.inc");
	$newId = shn_create_uuid("incident");

	// insert the new incident
	$random = mt_rand();
	$q = "
		INSERT INTO incident
			(incident_id, parent_id, search_id, name, shortname, date, type, latitude, longitude, private_group, closed)
		VALUES
			(".$newId.", null, null, 'new event ".$random."', 'x".$random."', '".date("Y-m-d")."', 'TEST', '39', '-77.101', '".$group."', '0');
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 4"); }


        // insert new Google repositories for import/export
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','source','person',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 5"); }
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','source','note',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 6"); }
	$q = "
		INSERT INTO pfif_repository (name,role,resource_type,incident_id)
		VALUES ('googlexxx','sink','both',".$newId.");
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "new 7"); }

	return $newId;
}



// presents a gui to edit a page and its corresponding fields
function em_perform_edit($incident_id) {
	global $global;

	//$global['xajax_res']->setFlag('debug', true);

	// if incident_id = 0, must create a new incident then continue to edit it
	if ($incident_id == 0) {
		$incident_id = em_perform_new();
		$new = true;
	} else {
		$new = false;
	}

	// get incident info
	$q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_groups g
		ON i.private_group = g.group_id
		WHERE i.incident_id = ".$incident_id."
		ORDER BY date desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 1"); }
	$row = $result->FetchRow();

	// get Google repository info for this incident
	$q = "
		SELECT base_url,sched_interval_minutes
		FROM pfif_repository
		WHERE incident_id = ".$incident_id." AND name LIKE 'google%' LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 2"); }
	$rowpfif = $result->FetchRow();

	// generate some html for special inputs //////// onchange=\"changeEvent(this.value);\"

	// generate parent event select box

		// check if event has children (if so, we don't allow changing of parent then)
		$qp = "
			SELECT COUNT(*)
			FROM incident
			WHERE parent_id = '".$row['incident_id']."';
		";
		$resp = $global['db']->Execute($qp);
		if($resp === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 3"); }
		$rowp = $resp->FetchRow();
		$hasChildren = $rowp['COUNT(*)'] > 0 ? true : false;

		if(!$hasChildren) {

			$options = "<option value=\"-1\">NONE</option>";

			// get list of Disasters
			$qd = "
				SELECT *
				FROM incident
				WHERE parent_id is null
				ORDER BY date desc;
			";
			$resd = $global['db']->Execute($qd);
			if($resd === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 4"); }
			$disasters = array();
			$dcount = 0;
			$disasters = array();
			while($rowd = $resd->FetchRow()) {
				$disasters[$dcount] = $rowd;
				$dcount++;
			}
			$i = 0; // we start with the 2nd row of teh table (header?) :)
			while($i < $dcount) {
				$selected = $row['parent_id'] == $disasters[$i]['incident_id'] ? "SELECTED" : "";

				// dont show self in teh dropdown :)
				if($disasters[$i]['incident_id'] != $row['incident_id']) {
					$options .= "<option value=\"".$disasters[$i]['incident_id']."\" ".$selected." >".$disasters[$i]['name']."</option>";
				}

					// get list of Incidents for this disaster
					$qi = "
						SELECT *
						FROM incident
						WHERE parent_id = '".$disasters[$i]['incident_id']."'
						ORDER BY date desc;
					";
					$resi = $global['db']->Execute($qi);
					if($resi === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 5"); }
					while($rowi = $resi->FetchRow()) {
						$selected = $row['parent_id'] == $rowi['incident_id'] ? "SELECTED" : "";

						// dont show self in teh dropdown :)
						if($rowi['incident_id'] != $row['incident_id']) {
							$options .= "<option value=\"".$rowi['incident_id']."\" ".$selected." >&nbsp;- ".$rowi['name']."</option>";
						}
					}
				$i++;
			}
			$parent = "
				<select id=\"eventParent\">
				".$options."
				</select>
			";

		} else {
			if($row['parent_id'] == null) {
				$pvalue = "-1";
			} else {
				$pvalue = $row['parent_id'];
			}
			$options = "<option value=\"".$pvalue."\" SELECTED >Event Has Children --- Not Edittable</option>";
			$parent = "
				<select id=\"eventParent\" DISABLED>
				".$options."
				</select>
			";
		}

	// end parent select box



	// generate event type
		// if no parent, then you can change these settings...
		if($row['parent_id'] == null) {

			$real = $row['type'] == "REAL" ? "SELECTED" : "";
			$test = $row['type'] == "TEST" ? "SELECTED" : "";
			$type = "
				<select id=\"eventType\">
				<option value=\"REAL\" ".$real.">REAL</option>
				<option value=\"TEST\" ".$test.">TEST</option>
				</select>
			";

		// else they are derived from the parent event
		} else {
			$type = "
				<select id=\"eventType\" DISABLED>
				<option value=\"DERIVE\" SELECTED>Value Dervied From Parent Event</option>
				</select>
			";
		}
	// end type



	// generate default checkbox
		$checked = $row['default'] == "1" ? "CHECKED" : "";
		$default = "<input type=\"checkbox\" id=\"eventDefault\" name=\"eventDefault\" value=\"default\" ".$checked." >";
	// end default


	// generate closed checkboxtextarea
		$checkedZero = $row['closed'] == "0" ? "CHECKED" : "";
		$checkedOne  = $row['closed'] == "1" ? "CHECKED" : "";
		$checkedTwo  = $row['closed'] == "2" ? "CHECKED" : "";
		$closed = "
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"0\" ".$checkedZero." > <b>REPORTING OPEN</b> for RAP/MPRES/PLUS/PFIF<br>
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"1\" ".$checkedOne." > <b>REPORTING CLOSED</b> for RAP/MPRES/PLUS/PFIF<br>
			<input type=\"radio\" id=\"eventClosed\" name=\"eventClosed\" value=\"2\" ".$checkedTwo." > <b>REPORTING CLOSED</b> for RAP/MPRES/PLUS + <b>REPORTING OPEN</b> for PFIF. Enter reporting widget code below:<br>
			<textarea id=\"externalReport\" rows=4 cols=60 />".$row['external_report']."</textarea>
		";
	// end closed

        // generate options for PFIF data sync with Google
                $checkedSync = $rowpfif['sched_interval_minutes'] == "0" ? "" : "CHECKED";
		$pfif = "
			PF repository: <input type=\"text\" id=\"pfifUrl\" name=\"pfifUrl\" size=\"48\" value=\"".htmlspecialchars($rowpfif['base_url'])."\">
                        &nbsp;&nbsp;Keep PL and PF synchronized? <input type=\"checkbox\" id=\"pfifSync\" name=\"pfifSync\" value=\"1\" ".$checkedSync."><br>
                        (e.g. https://turkey-2011.googlepersonfinder.appspot.com)
		";
        // end PFIF options

	// generate visibility select box
		// if no parent, then you can change these settings...
		if($row['parent_id'] == null) {

			$options = "<option value=\"-1\">PUBLIC</option>";

			// get list of GROUPS
			$qg = "
				SELECT *
				FROM  `sys_user_groups`;
			";
			$resg = $global['db']->Execute($qg);
			if($resg === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "edit 6"); }
			while($rowg = $resg->FetchRow()) {
				if($row['private_group'] == $rowg['group_id']) {
					$selected = "SELECTED";
				} else {
					$selected = "";
				}
				$options .= "<option value=\"".$rowg['group_id']."\" ".$selected." >".$rowg['group_name']."</option>";
			}
			$visibility = "
				<select id=\"eventVisibility\">
				".$options."
				</select>
			";

		// else setting is derived from parent ......
		} else {
			$visibility = "
				<select id=\"eventVisibility\" DISABLED>
				<option value=\"-2\" SELECTED>Value Dervied From Parent Event</option>
				</select>
			";
		}
	// end visibility select box

	$editMainHtml = "

<table class=\"emTable\">

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Event ID#</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"eventId\" type=\"text\" value=\"".$row['incident_id']."\" size=8 readonly /></td>
	<tr>


	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Long Name</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"longName\" type=\"text\" size=60 maxlength=60 value=\"".$row['name']."\" /></td>
	<tr>


	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Short Name</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><input id=\"shortName\" type=\"text\" size=16 maxlength=16 value=\"".$row['shortname']."\" /> ( lowercase letters and numbers only )</td>
	</tr>


	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Title Line 2 (appears under People Locator)<br>ie. <b>for the Joplin Tornado</b></td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><textarea id=\"eventDescription\" rows=1 cols=60 />".$row['description']."</textarea></td>
	<tr>

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Parent Event</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$parent."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Type</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\">".$type."</td>
	<tr>

	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Visibility</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$visibility."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Date</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"eventDate\" type=\"text\" value=\"".$row['date']."\" /></td>
	<tr>


	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">Default Event In Web Services</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$default."</td>
	<tr>

	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">Event Status</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\">".$closed."</td>
	<tr>

        <tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">PFIF Settings for Google PF</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$pfif."</td>
        <tr>
</table>
<br>
<table class=\"emTable\">
	<tr>
		<td class=\"mainRowEven\" style=\" border-bottom: none;\" colspan=2>
			<label>Enter a Street Address: </label>
			<input id=\"address\" type=\"text\" /> &nbsp; -OR- &nbsp; <input type=\"button\" style=\"position: relative; top: -2px;\" class=\"styleTehButton\" onclick=\"detect_load();\" value=\"Detect My Current Location\" />
		</td>
	</tr>


	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"border-top: none; border-bottom: none;  padding: 0px;\" colspan=2>
			<div id=\"mapCanvas\" style=\"width: 100%; height: 500px;\"></div>
		</td>
	</tr>

	<tr>
		<td class=\"mainRowEven\" style=\" border-top: none;\" colspan=2>
			<label>latitude: </label>
				<input id=\"latitude\" type=\"text\"/ value=\"".$row['latitude']."\" readonly>
			<label> &nbsp; longitude: </label>
				<input id=\"longitude\" type=\"text\"/ value=\"".$row['longitude']."\" readonly>
		</td>
	</tr>
</table>
	";

	// control HTML
	$editControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Saving Changes...<br>\'); setTimeout(\'em_perform_save('.$incident_id.', em_get_data());\', 250);" value="Save Changes and Close">
		<input class="styleTehButton" type="button" onclick="javascript: em_append_log(\'Canceling Changes...<br>\'); setTimeout(\'em_show_events();\', 250);" value="Cancel Editing and Close">
	';

	// if Admin... show delete button
	if($_SESSION['group_id'] == "1") {
		if($hasChildren) {
			$disabled = "DISABLED style=\"opacity: 0.2;\"";
		} else {
			$disabled = "";
		}
		$editControlHtml .= '
			&nbsp; &nbsp; &nbsp; &nbsp;
			<input class="styleTehButton red" type="button" onclick="javascript: em_delete('.$incident_id.');" value="Delete Event" '.$disabled.' >
		';
	}

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $editMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $editControlHtml);

	if($new) {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Event <b>#'.$incident_id.'</b> <span style="color: green;">Created</span>.<br>');
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Editing event <b>#'.$incident_id.'</b>...<br>');
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	}

	$global['xajax_res']->addScript("load_map(".$row['latitude'].", ".$row['longitude'].", '".$row['street']."');");
	$global['xajax_res']->addScript("initDate();");

	return $global['xajax_res']->getXML();
}




