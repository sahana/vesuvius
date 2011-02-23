<?php
/**
 * This is the main admin file for the INW module.
 *
 * PHP version 5.2+
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	Merwan Rodriguez
 * @package	module
 * @subpackage	inw
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

	include_once ($global['approot'].'/inc/lib_menu.inc');
	include_once ($global['approot'].'/inc/lib_errors.inc');
	require_once ($global['approot'].'/inc/handler_db.inc');

	include_once $global['approot'].'/inc/lib_xajax.inc';
	include_once ($global['approot'].'/mod/inw/xajax.inc');

	shn_xajax_registerFunction('inw_getData');
	shn_xajax_registerFunction('inw_checkForChanges');



/**
 * Default Admin function
 *
 * @access public
 * @return void
 */
function shn_inw_default() {
	global $global;
	// iWall
	error_reporting(E_ERROR);
	require_once("languageStrings.php");
	?>
		<link rel="stylesheet" type="text/css" href="res/iWall.css" media="screen" />
		<link rel="stylesheet" type="text/css" href="res/iWall_print.css" media="print" id="printSheet" />
		<!--[if IE]>
			<style type="text/css">
				.ieStubBorder {
					border-width: 1px !important;
				}
			</style>
		<![endif]-->

			<input type="text" id="jsonHolder" style="display:none" />
			<div id="searchOptions" style="display:none;">
				<div style="font-weight: bold; background-color: #6289B0; color: white; padding:2px">Display</div>
				<div style="float:left;">
					<!--input type="textbox" autocomplete="off" value="Enter a name..." id="searchBox"/-->
					<div id="sortBy" style="float:right;margin-right: 4px;">
					<br />
					<b>Sort By</b>
						<img id="sortOrderIcon" style="width:10px; height:10px; display: none;" src="res/img/desc.png" title="Descending (click for ascending)" />
						<select id="selectSort" style="width: 85px;" onchange="Utils.sortBy( this )">
							<option value="">Relevance</option>
							<option value="t.updated">Time</option>
							<option value="t.full_name">Name</option>
							<option value="t.years_old">Age</option>
							<option value="t.opt_status">Status</option>
						</select>
					</div>
					<div style="clear:both;"></div>
					<div id="displayModeWrapper" style="float:right;margin-right: 4px; margin-top:5px;">
						<b>Mode</b>
						<select id="displayMode" style="width: 105px;" onchange="Utils.displayMode(this.value)">
							<option value="interactive">Interactive</option>
							<option value="handsFree">Hands Free</option>
							<option value="fullScreen">Full Screen</option>
						</select>
					</div>
					<div style="clear:both;"></div>
					<div id="scrollControls">
						<img src="res/img/play_up.png" title="Play" onmousedown="this.src='res/img/play_down.png'" onmouseup="ScrollView.play();this.src='res/img/play_up.png'" />
						<img src="res/img/pause_up.png" title="Pause" onmousedown="this.src='res/img/pause_down.png'" onmouseup="ScrollView.pause();this.src='res/img/pause_up.png'" />
						<img src="res/img/faster_up.png" title="Scroll faster" onmousedown="this.src='res/img/faster_down.png'" onmouseup="ScrollView.increaseSpeed();this.src='res/img/faster_up.png'" />
						<img src="res/img/slower_up.png" title="Scroll slower" onmousedown="this.src='res/img/slower_down.png'" onmouseup="ScrollView.decreaseSpeed();this.src='res/img/slower_up.png'" />
						<div style="height: 20px;" id="speedDisplayWrapper">
							<div style="display: none;" id="speedDisplay">
								0
							</div>
						</div>
					</div>
					<div style="clear:both;"></div>
					<br/>
					<div id="filtersWrapper">
						<div id="filtersBox" style="display: block;">
							<div style="font-weight: bold; background-color: #6289B0; color: white; padding:2px;">Status</div>
							<input type="checkbox" id="checkMissing" name="checkMissing" checked onclick="Utils.formSearch()" /><label for="checkMissing" id="missing" class="bold"><? echo MISSING; ?></label>
							<br />
							<input type="checkbox" id="checkAliveWell" name="checkAliveWell" checked onclick="Utils.formSearch()" /><label for="checkAliveWell" class="bold" id="alive"><? echo ALIVE_AND_WELL; ?></label>
							<br />
							<input type="checkbox" id="checkInjured"   name="checkInjured"  checked onclick="Utils.formSearch()" /><label for="checkInjured" class="bold" id="injured"><? echo INJURED; ?></label>
							<br />
							<input type="checkbox" id="checkDeceased"  name="checkDeceased" checked onclick="Utils.formSearch()" /><label for="checkDeceased" class="bold" id="deceased"><? echo DECEASED; ?></label>
							<br />
							<input type="checkbox" id="checkUnknown"  name="checkUnknown" checked onclick="Utils.formSearch()" /><label for="checkUnknown" id="unknown" class="bold"><? echo UNKNOWN; ?></label>
							<br />
							<br />
							<div id="gender">
								<div style=" font-weight: bold; background-color: #6289B0; color: white; padding:2px;"><? echo GENDER; ?> </div>
								<input type="checkbox" id="checkSexMale"   checked onclick="Utils.formSearch()" /><label for="checkSexMale"><? echo MALE; ?></label><br />
								<input type="checkbox" id="checkSexFemale" checked onclick="Utils.formSearch()" /><label for="checkSexFemale"><? echo FEMALE; ?></label><br />
								<input type="checkbox" id="checkSexOther"  checked onclick="Utils.formSearch()" /><label for="checkSexOther"><? echo OTHER_UNKNOWN; ?></label><br />
							</div>
							<br />
							<div id="age">
								<div style=" font-weight: bold; background-color: #6289B0; color: white; padding:2px;"><? echo AGE; ?></div>
								<input type="checkbox" id="checkAgeChild"   checked onclick="Utils.formSearch()" /><label for="checkAgeChild">Youth (0-17)</label><br />
								<input type="checkbox" id="checkAgeYouth"   checked onclick="Utils.formSearch()" /><label for="checkAgeYouth">Adult (18+)</label><br />
								<input type="checkbox" id="checkAgeUnknown" checked onclick="Utils.formSearch()" /><label for="checkAgeUnknown"><? echo UNKNOWN; ?></label><br />
							</div>
							<br />
							<div id="hospital">
								<div style=" font-weight: bold; background-color: #6289B0; color: white; padding:2px;">Source</div>
								<input type="checkbox" id="checkSuburban"   checked onclick="Utils.formSearch()" /><label for="checkSuburban">Suburban Hospital</label><br />
								<input type="checkbox" id="checkNNMC"   checked onclick="Utils.formSearch()" /><label for="checkNNMC">Navy Medical Center</label><br />
								<input type="checkbox" id="checkOtherHosp"   checked onclick="Utils.formSearch()" /><label for="checkOtherHospital">Public/Other</label><br />
							</div>
						</div>
					</div>
					<!--a href="#"  id="filtersSwitch" onmouseover="this.style.cursor='pointer'" onclick="$('#filtersBox').toggle(); this.innerHTML = this.innerHTML == '+ More Options' ? '- Less Options' : '+ More Options'">+ More Options</a-->
					<br /><br />
				</div>
			</div>
			<form action="javascript:Utils.formSearch()" id="searchForm">
				<div style="margin-bottom: 5px;font-size: 16pt;display: block;" id="searchFor">
					Search For...
				</div>
				<input type="textbox" autocomplete="off" value="Enter a name..." id="searchBox"/>
				<div id="searchButtonWrapper" style="display: inline;">
					<input type="submit" value="Search" id="buttonSearch"/>
				</div>
				<div style="clear:both;"></div>
				<div style="float:left;font-size: .85em; display: none;" id="foundLabel">
					Found <span id="recordsFound">0</span> out of <span id="totalRecords">0</span> records in <span id="timeElapsed">0</span> seconds
				</div>
				<div id="updateAlerts" style=" font-weight: bold;float:left;font-size: .85em; display: none; margin-left: 5px; color: #C00">
					<span style="color: black"> | </span> There are new or updated records in the database, click <a href="javascript:searchSubset()">here</a> to refresh the results
				</div>
				<div id="updateAlerts2" style="float:left;font-size: .85em; font-weight: bold; display: none; margin-left: 5px; color: #C00">
					<span style="color: black"> | </span> There are new or updated records in the database, the results will be automatically refreshed in 1 minute.
				</div>
				<span id="printLink" style="display: none;float: right;margin-right:15px;margin-top:0px;">
					<a href="#" onclick="Utils.printSet()">Print Results</a>
				</span>
				<div style="clear:both;"></div>
			</form>
			<br />
		<div id="pager" style="display:none;float:left;margin-right:15px;margin-top:5px;"></div>
		<div id="perPageWrapper" style="display:none;float:left; margin-right:15px;">
			<span style="margin-right: 15px;">|</span>
			Results Per Page -
			<select id="perPage" onchange="Globals.currPage = 1; Globals.perPage = this.value; searchSubset()">
				<option value="25">25</option>
				<option value="50">50</option>
				<option value="100">100</option>
			</select>
		</div>

		<div style="clear:both;" id="beforeScrollingContent"></div> <!-- for IE -->
		<div id="scrolling_content">
			To search for a specific person, enter a name above and press "Enter" or click "Search"<br />
			If you would like to see all the records for this incident, leave the search field blank and press "Enter" or click "Search".
		</div>
		<div id="detailsPane">
		<div id="dt_eapLink" onclick="Utils.closeDetail();"><a href="#" style="color:#6694E3; text-decoration: underline">View/Edit Full Record</a></div>
		<div id="close" onclick="Utils.closeDetail();"><a href="#" style="color:#6694E3; text-decoration: underline">Close</a></div>
		<div id="dt_print" onclick="Utils.printDetail();"><a href="#" style="color:#6694E3; text-decoration: underline">Print</a></div>
		<!--div id="showMap" onclick="Utils.showMap();"><a href="#" style="color:#6694E3; text-decoration: underline">Map</a></div-->
		<div id="dt_image" style="float:left;padding:5px 5px 5px 5px; border:solid 1px #CCC;position:relative;z-index:2;" >
			<!--span id="caption">caption here</span-->
		</div>
		<div id="detailInfo" style="text-align:left;float:left;margin-top:5px;margin-left:20px; width:400px; position:relative; border: solid 0px #CCC;">
			<label for="dt_uuid">ID</label>
			<div id="dt_uuid" style="font-weight:normal;"></div>
			<label for="dt_fullName">Name</label>
			<div id="dt_fullName" style="font-weight:normal;"></div>
			<label for="dt_age">Age Group</label>
			<div id="dt_age" style="font-weight:normal;"></div>
			<label for="dt_gender">Gender </label>
			<div id="dt_gender" style="font-weight:normal;"></div>
			<label for="dt_status">Status </label>
			<div id="dt_status" style="font-weight:normal;"></div>
			<label for="dt_statusSahanaUpdated">When Reported</label>
			<div id="dt_statusSahanaUpdated" style="font-weight:normal;"></div>
			<label for="dt_location">Last Known Location</label>
			<div id="dt_location" style="font-weight:normal;"></div>
		</div>
		<div id="dt_hospitalIcon" ></div>
		<div id="map_canvas" class="map">Loading...</div>
		<div style="clear:both;"></div>
		</div>
		<div id="exitFullScreen"></div>
		<div id="exitFullScreenIpad" onclick="ScrollView.exitFullScreen()">Tap here to exit...</div>
		<div id="glass" onclick="Utils.closeDetail();">&nbsp;</div>

		<input name="language" id="language" type="hidden" value="<? echo L; ?>">
		<br />

		<!--script type="text/javascript" src="https://maps-api-ssl.google.com/maps/api/js?v=2&client=gme-hhs&sensor=false"></script-->
		<script type="text/javascript" src="res/js/jquery-1.4.4.min.js" ></script>
		<script type="text/javascript" src="res/js/jquery-ui-effectscore.min.js" ></script>
		<!--script type="text/javascript" src="res/js/inw/jquery.animate-enhanced.min.js" ></script-->

		<script type="text/javascript" src="res/js/date.js" ></script>
		<script type="text/javascript" src="res/js/inw/Globals.js" ></script>
		<script type="text/javascript" src="res/js/inw/detailsView.js"></script>
		<script type="text/javascript" src="res/js/inw/Utils.js" ></script>
		<script type="text/javascript" src="res/js/inw/ScrollView.js" ></script>
		<script type="text/javascript" src="res/js/inw/iWall.js" ></script>
		<div class="push"></div>
	<?
}

/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_inw_mainmenu() {
	global $global;
	$module = $global['module'];
	include $global['approot']."/inc/handler_mainmenu.inc";

	// Create the module menu
	shn_mod_menuopen(_t("Search for a Person"));
	//	shn_mod_menuitem("default", _t("Search Home"));
	shn_mod_menuclose();
}

