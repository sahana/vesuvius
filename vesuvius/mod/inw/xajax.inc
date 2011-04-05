<?php
/**
 * modRez xajax library
 *
 * @package	module
 * @subpackage	inw
 * @author 	Merwan Rodriguez
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


include  ($global['approot'].'/mod/inw/SearchDB.php');
include  ($global['approot'].'/conf/sahana.conf');

// publicly register accessible xajax funtions
$global['xajax_functions'] = array();

array_push($global['xajax_functions'],'inw_getData');
array_push($global['xajax_functions'],'inw_checkForChanges');
array_push($global['xajax_functions'],'inw_hasNextPage');

function inw_checkForChanges($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital) {
	global $global;

	$search = new SearchDB($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital);
	$search->getLastUpdate();
	$global["xajax_res"]->addScript("Utils.changeObserver('". $search->lastUpdated . "');");
	return $global["xajax_res"]->getXML();
}

function inw_hasNextPage($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls ) {
	global $global;
	
	$mode = strtolower($mode); // just making sure.
	$search = new SearchDB($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls);
	$search->executeSearch();

	if ( count($search->results) > 0 ) 
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
		   Also, needs to account for age ranges (how? good question).
 */
 function inw_getData($mode, $incident, $searchTerm, $sStatus, $sGender, $sAge, $sHospital, $sPageControls ) {
	global $global;
	
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
		$global["xajax_res"]->addAssign("timeElapsedSQL", "innerHTML", substr($timeElapsed, 0, 5));
		$global["xajax_res"]->addAssign("timeElapsedSOLR", "innerHTML", substr($timeElapsed, 0, 5));
		$global["xajax_res"]->addScript("Globals.timeElapsed = " . $timeElapsed . "; Globals.totalResults = " . $search->numRowsFound . "; Globals.totalRecords = " . $search->allCount . "; handleUuidListResponse();");
		
		//$global["xajax_res"]->addScript("alert('" . count($search->results) . ", " . $search->numRowsFound . ", " . $search->allCount . "')");
	}
	else {
		$global["xajax_res"]->addAssign("jsonHolder", "value", "");
		$global["xajax_res"]->addAssign("SOLRFacets", "value", json_encode($search->SOLRfacetResults));  
		//$global["xajax_res"]->addScript("recordsFound", "innerHTML", "0");  //ugh... i hate xajax...
		$global["xajax_res"]->addScript("Globals.totalResults = 0; $('#recordsFound').html('0');");
		$global["xajax_res"]->addAssign("totalRecordsSQL", "innerHTML", $search->allCount);
		$global["xajax_res"]->addAssign("totalRecordsSOLR", "innerHTML", $search->allCount);
		$global["xajax_res"]->addScript("Globals.totalRecords = " . $search->allCount . ";");
		$global["xajax_res"]->addScript("$('#scrollingContent').html('');showFacets();$('#pager').hide();$('#perPageWrapper').hide()");
		$global["xajax_res"]->addAssign("scrolling_content", "innerHTML", "<br /><span style='color:red'>No matches for '" . $searchTerm . "'. Please broaden your search criteria and try again.</span>");
		//$global["xajax_res"]->addAssign("scrolling_content", "innerHTML", $searchTerm);
	}
	return $global["xajax_res"]->getXML();
}


//inw_searchSubset("", false, true, true, true, true);
//inw_getAll();
