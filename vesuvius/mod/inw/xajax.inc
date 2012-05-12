<?
/**
 * @name         Interactive Notification Wall (Search)
 * @version      21
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


global $global;
global $conf;
require_once($global['approot'].'/mod/inw/SearchDB.php');

// publicly register accessible xajax funtions
$global['xajax_functions'] = array();

array_push($global['xajax_functions'],'inw_getData');
array_push($global['xajax_functions'],'inw_checkForChanges');
array_push($global['xajax_functions'],'inw_hasNextPage');
array_push($global['xajax_functions'],'inw_getNotes');
array_push($global['xajax_functions'],'inw_getAllCount');

function inw_getNotes($uuid) {
	global $global;
	$db = $global['db'];

	$db->EXECUTE("set names 'utf8'");

	$q = "SELECT note_record_id, CONVERT_TZ(source_date, 'America/New_York', 'UTC') AS source_date,
				 author_name,
				 found,
				 REPLACE(status, '_', ' ') as status,
				 last_known_location,
				 text
		    FROM pfif_note WHERE p_uuid = '$uuid' ORDER BY source_date DESC";

	$result = $db->Execute($q);
	while (!$result == NULL && !$result->EOF) {
		$list[] = array('note_id'=>$result->fields["note_record_id"],
						'date'=>$result->fields["source_date"],
						'author'=>$result->fields["author_name"],
						'found'=>$result->fields["found"],
						'status'=>$result->fields["status"],
						'lastSeen'=>$result->fields["last_known_location"],
						'text'=>$result->fields["text"]);

		$result->MoveNext();
	}

        if (!empty($list)) {
                $global["xajax_res"]->addAssign("jsonNotes", "value", json_encode($list));
        }
	$global["xajax_res"]->addScript("Utils.loadNotes()");
	return $global["xajax_res"]->getXML();
}

function inw_getAllCount($incident) {
		global $global;
		$db = $global['db'];
		$qRC = "SELECT COUNT(p.p_uuid) FROM person_uuid p JOIN incident i ON p.incident_id = i.incident_id WHERE i.shortname = '$incident' ;";
		$result = $db->Execute($qRC);
		$allCount = 0;


		while (!$result == NULL && !$result->EOF) {
			$allCount = $result->fields[0];
			break;
		}

		$global["xajax_res"]->addAssign("totalRecordsSQL", "innerHTML", $allCount);
		$global["xajax_res"]->addScript('$("#totalRecordsSQL").html(Utils.addCommas($("#totalRecordsSQL").html()))');

		return $global["xajax_res"]->getXML();
}

function inw_checkForChanges($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital) {
	global $global;

	$search = new SearchDB($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital);
	$search->getLastUpdate();
	$global["xajax_res"]->addAssign("lastCheck", "innerHTML", gmdate("Y-m-d H:i:s")." UTC");
	$global["xajax_res"]->addScript("Utils.changeObserver('". $search->lastUpdated . "');");
	return $global["xajax_res"]->getXML();
}

function inw_hasNextPage($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls ) {
	global $global;

	$mode = strtolower($mode); // just making sure.
	$search2 = new SearchDB($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls);
	$search2->executeSearch();

	if ( count($search2->results) > 0 )
		$global["xajax_res"]->addScript("Globals.hasNextPage = true; DetailsView.setPager()");
	else
		$global["xajax_res"]->addScript("Globals.hasNextPage = false; DetailsView.setPager()");

	return $global["xajax_res"]->getXML();

}

/**
 * params: $aStatus = status imploded
		   $aPageControls = $pageStart, $perPage, $sortBy, $mode
		   $aGender = gender imploded
		   $aAge = age imploded
	 TODO: this needs to be reorganized as it's kind of a mess right now (blame xajax)
 */
 function inw_getData($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls ) {
	global $global;
	global $conf;

	$mode = strtolower($mode); // just making sure.
	$timeElsapsed = 0;
	$search = new SearchDB($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls);
	$timeStart = microtime(true);
	$search->executeSearch();
	$timeElapsed = microtime(true) - $timeStart;


	if ( count($search->results) > 0 ) {
		$global["xajax_res"]->addScript("Globals.resultSet = " . json_encode($search->results));
		//$global["xajax_res"]->addAssign("jsonHolder", "value", json_encode($search->results));
		$global["xajax_res"]->addAssign("SOLRFacets", "value", json_encode($search->SOLRfacetResults));
		$global["xajax_res"]->addAssign("recordsFound", "innerHTML", $search->numRowsFound);
		$global["xajax_res"]->addAssign("totalRecordsSQL", "innerHTML", $search->allCount);
		$global["xajax_res"]->addAssign("totalRecordsSOLR", "innerHTML", $search->allCount);
		$global["xajax_res"]->addScript("Utils.changeObserver('". $search->lastUpdated . "');");
		$global["xajax_res"]->addAssign("timeElapsedSQL", "innerHTML", substr($timeElapsed, 0, 5));
		$global["xajax_res"]->addAssign("timeElapsedSOLR", "innerHTML", substr($timeElapsed, 0, 5));
		if ( $mode == "solr" )
			$global["xajax_res"]->addScript("Globals.timeElapsed = " . $timeElapsed . "; Globals.totalResults = " . $search->numRowsFound . "; Globals.totalRecords = " . $search->allCount . "; handleUuidListResponse();");
		else
			$global["xajax_res"]->addScript("Globals.timeElapsed = " . $timeElapsed . "; handleUuidListResponse();");
	}
	else {
		$global["xajax_res"]->addAssign("jsonHolder", "value", "");
		$global["xajax_res"]->addAssign("SOLRFacets", "value", json_encode($search->SOLRfacetResults));
		$global["xajax_res"]->addScript("Globals.totalResults = 0; $('#recordsFound').html('0');");
		$global["xajax_res"]->addAssign("totalRecordsSQL", "innerHTML", $search->allCount);
		$global["xajax_res"]->addAssign("totalRecordsSOLR", "innerHTML", $search->allCount);
		$global["xajax_res"]->addScript("Utils.changeObserver('". $search->lastUpdated . "');");
		if ( $mode == "solr" )
			$global["xajax_res"]->addScript("Globals.totalRecords = " . $search->allCount . ";");
		$global["xajax_res"]->addScript("showFacets();$('#pager').hide();$('#pager2').hide();$('#perPageWrapper').hide()");
		$global["xajax_res"]->addAssign("scrolling_content", "innerHTML", "<br /><span style='color:red'>No matches for '" . $searchTerm . "'. Please broaden your search criteria and try again.</span>");
		//$global["xajax_res"]->addAssign("scrolling_content", "innerHTML", $searchTerm);
	}
	return $global["xajax_res"]->getXML();
}


//inw_searchSubset("", false, true, true, true, true);
//inw_getAll();
