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


include_once ($global['approot'].'/inc/lib_menu.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');
require_once ($global['approot'].'/inc/handler_db.inc');
include_once ($global['approot'].'/inc/lib_xajax.inc');
include_once ($global['approot'].'/mod/inw/xajax.inc');

shn_xajax_registerFunction('inw_getData');
shn_xajax_registerFunction('inw_checkForChanges');
shn_xajax_registerFunction('inw_hasNextPage');
shn_xajax_registerFunction('inw_getNotes');
shn_xajax_registerFunction('inw_getAllCount');


/**
 * Default Admin function
 *
 * @access public
 * @return void
 */
function shn_inw_default() {
	global $global;
	global $conf;
	// iWall
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
			<noscript>Your browser does not support JavaScript! You will need to enable it or use a modern browser before searching.</noscript>
			<input type="text" id="jsonHolder" style="display:none" />
			<input type="text" id="jsonNotes" style="display:none" />
			<input type="text" id="SOLRFacets" style="display:none" />
			<input type="text" id="shortName" style="display:none" value="<?= $_REQUEST["shortname"] ?>" />
			<input type="hidden" id="searchMode" value="<?= $conf["enable_solr_for_search"] ? "solr" : "sql" ?>" />
			<div id="searchOptions" style="display:none;">
				<div class="searchOptionsHeader">Search Options</div>
				<div style="float:left;">
					<div id="sortBy" style="float:right;margin-right: 4px;width:160px; text-align: right;">
					<b>Sort By</b>
						<img id="sortOrderIcon" style="width:10px; height:10px; <?= $conf["enable_solr_for_search"] ? "display: none" : "" ?>" src="res/img/desc.png" title="Descending (click for ascending)" alt="descending sort order, click for ascending"/>
						<select id="selectSort" onchange="Utils.sortBy( this )">
							<? if ( $conf["enable_solr_for_search"] ) { ?>
								<option value="">Relevance</option>
							<? } ?>
							<option value="updated">Time</option>
							<option value="full_name">Name</option>
							<option value="years_old">Age</option>
							<option value="opt_status">Status</option>
							<? if ( preg_match('(cmax|shield)',$_REQUEST["shortname"])) { ?>
							        <option value="mass_casualty_id">Mass Casualty ID</option>
							<? } ?>
						</select>
					</div>
					<div style="clear:both;"></div>
					<div id="displayModeWrapper" style="float:right;margin-right: 4px; margin-top:5px;">
						<b>Mode</b>
						<select id="displayMode" onchange="Utils.displayMode(this.value)">
							<option value="interactive">Interactive</option>
							<option value="handsFree">Hands Free</option>
							<option value="fullScreen">Full Screen</option>
						</select>
					</div>
					<div style="clear:both;"></div>
					<div id="scrollControls">
						<img src="res/img/play_up.png" title="Play" onmousedown="this.src='res/img/play_down.png'" onmouseup="ScrollView.play();this.src='res/img/play_up.png'" alt="play"/>
						<img src="res/img/pause_up.png" title="Pause" onmousedown="this.src='res/img/pause_down.png'" onmouseup="ScrollView.pause();this.src='res/img/pause_up.png'" alt="pause"/>
						<img src="res/img/faster_up.png" title="Scroll faster" onmousedown="this.src='res/img/faster_down.png'" onmouseup="ScrollView.increaseSpeed();this.src='res/img/faster_up.png'" alt="faster"/>
						<img src="res/img/slower_up.png" title="Scroll slower" onmousedown="this.src='res/img/slower_down.png'" onmouseup="ScrollView.decreaseSpeed();this.src='res/img/slower_up.png'" alt="slower"/>
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
							<div class="searchOptionsHeader">Status</div>
							<input type="checkbox" id="checkMissing" name="checkMissing" checked onclick="Utils.formSearch()" /><label for="checkMissing" id="missing" class="bold"><? echo MISSING; ?></label>
							<br />
							<input type="checkbox" id="checkAliveWell" name="checkAliveWell" checked onclick="Utils.formSearch()" /><label for="checkAliveWell" id="alive" class="bold"><? echo ALIVE_AND_WELL; ?></label>
							<br />
							<input type="checkbox" id="checkInjured"   name="checkInjured"  checked onclick="Utils.formSearch()" /><label for="checkInjured" id="injured" class="bold"><? echo INJURED; ?></label>
							<br />
							<input type="checkbox" id="checkDeceased"  name="checkDeceased" checked onclick="Utils.formSearch()" /><label for="checkDeceased" id="deceased" class="bold"><? echo DECEASED; ?></label>
							<br />
							<input type="checkbox" id="checkUnknown"  name="checkUnknown" checked onclick="Utils.formSearch()" /><label for="checkUnknown" id="unknown" class="bold"><? echo UNKNOWN; ?></label>
							<br />
							<input type="checkbox" id="checkFound"  name="checkFound" checked onclick="Utils.formSearch()" /><label for="checkFound" id="found" class="bold"><? echo FOUND; ?></label>
							<br />
							<br />
							<div id="gender">
								<div class="searchOptionsHeader"><? echo GENDER; ?> </div>
								<input type="checkbox" id="checkSexMale"    checked onclick="Utils.formSearch()" /><label for="checkSexMale" id="male"><? echo MALE; ?></label><br />
								<input type="checkbox" id="checkSexFemale"  checked onclick="Utils.formSearch()" /><label for="checkSexFemale" id="female"><? echo FEMALE; ?></label><br />
								<input type="checkbox" id="checkSexComplex" checked onclick="Utils.formSearch()" /><label for="checkSexComplex" id="complex">Complex</label><br />
								<input type="checkbox" id="checkSexOther"   checked onclick="Utils.formSearch()" /><label for="checkSexOther" id="otherGender"><? echo OTHER_UNKNOWN; ?></label><br />
							</div>
							<br />
							<div id="age">
								<div class="searchOptionsHeader"><? echo AGE; ?></div>
								<input type="checkbox" id="checkAgeChild"   checked onclick="Utils.formSearch()" /><label for="checkAgeChild" id="child">Youth (0-17)</label><br />
								<input type="checkbox" id="checkAgeYouth"   checked onclick="Utils.formSearch()" /><label for="checkAgeYouth" id="adult">Adult (18+)</label><br />
								<input type="checkbox" id="checkAgeUnknown" checked onclick="Utils.formSearch()" /><label for="checkAgeUnknown" id="otherAge"><? echo UNKNOWN; ?></label><br />
							</div>
							<br />
							<div id="hospital">
								<div class="searchOptionsHeader">Source</div>
								<input type="checkbox" id="checkSuburban"   checked onclick="Utils.formSearch()" /><label for="checkSuburban" id="suburban">Suburban Hospital</label><br />
								<input type="checkbox" id="checkNNMC"   checked onclick="Utils.formSearch()" /><label for="checkNNMC" id="nnmc">Navy Medical Center</label><br />
								<input type="checkbox" id="checkOtherHosp"   checked onclick="Utils.formSearch()" /><label for="checkOtherHospital" id="otherHospital">Public/Other</label><br />
							</div>
						</div>
					</div>
					<!--a href="#"  id="filtersSwitch" onmouseover="this.style.cursor='pointer'" onclick="$('#filtersBox').toggle(); this.innerHTML = this.innerHTML == '+ More Options' ? '- Less Options' : '+ More Options'">+ More Options</a-->
				</div>
			</div>
			<form action="javascript:Utils.formSearch()" id="searchForm">
				<input type="textbox" autocomplete="off" value="Enter a name..." id="searchBox" x-webkit-speech="" x-webkit-grammar="builtin:search"/>
				<div id="searchButtonWrapper" style="float:left">
					<input type="submit" value="Search" id="buttonSearch" class="styleTehButton"/>
					<input type="button" value="Clear"  id="buttonClear" class="styleTehButton" onclick="Utils.clear()"/>
					<input type="button" style="margin-left: 20px; display: none;" value="Help"  id="buttonHelp" class="styleTehButton" onclick="Utils.showHelp()"/>
				</div>
				<div style="clear:both;"></div>
				<div id="foundLabel" style="float:left;font-size:.85em;display:none;margin-top: 2px;">
					<span id="solrFoundLabel" style="display:none">Found <span id="recordsFound">0</span> out of <span id="totalRecordsSOLR">0</span> records in <span id="timeElapsedSOLR">0</span> seconds </span>
					<span id="sqlFoundLabel"  style="display:none">Searched <span id="totalRecordsSQL">0</span> records in <span id="timeElapsedSQL">0</span> seconds </span>
					<span id="maxShown" style="display:none;font-size:.6em">(max 2,000 shown)</span>
					<span id="refreshLabel" style="display:none;"> | Last updated: <span id="lastCheck"></span>, last new record: <span id="lastChange">none</span></span>
				</div>
				<div id="updateAlerts2" style="float:left;font-size: .85em; font-weight: bold; display: none; margin-left: 5px; color: #C00">
					<span style="color: black"> | </span> There are new or updated records in the database, the results will be automatically refreshed in 1 minute.
				</div>
				<span id="printLink" style="display: none;float: right;margin-right:15px;margin-top:0px;">
					<a href="#" onclick="Utils.printSet()">Print Results Page</a>
				</span>
				<div style="clear:both;"></div>
			</form>
			<br />
		<div id="perPageWrapper" style="display:none;float:right; margin-right:15px;">
			<label for="perPage">Results Per Page -</label>
			<select id="perPage" onchange="Globals.currPage = 1; Globals.perPage = this.value; searchSubset()">
				<option value="25">25</option>
				<option value="50">50</option>
				<option value="100">100</option>
			</select>
		</div>
		<div id="pager" style="display:none;float:left;margin-right:25px;margin-top:5px;"></div>
		<div style="clear:both;" id="beforeScrollingContent"></div>
		<div id="scrolling_content">
			<ul>
			  <li>Enter "unknown" to search records without names.</li>
			  <li>Leave the box blank to browse all records.</li>
			  <li>Use * as a wildcard (for example: "Cath*" will find "Catherine").</li>
			  <li>Search is case-insensitive.</li>
			</ul>

		</div>
		<div id="pager2" style="display:none;float:left;margin-right:25px;margin-top:5px;"></div>
		<div id="detailsPane">
			<div id="dt_eapLink" onclick="Utils.closeDetail();"><a href="#" style="color:#6694E3; text-decoration: underline">See more information about this person (full record)</a></div>
			<div id="close" onclick="Utils.closeDetail();"><a href="javascript:void(0)" style="color:#6694E3; text-decoration: underline">Close</a></div>
			<div id="dt_print" onclick="Utils.printDetail();"><a href="javascript:void(0)" style="color:#6694E3; text-decoration: underline">Print</a></div>
			<div id="dt_notesTab" onclick="Utils.showNotes();"><a href="javascript:void(0)" style="color:#6694E3; text-decoration: underline">Notes</a></div>
			<!--div id="showMap" onclick="Utils.showMap();"><a href="#" style="color:#6694E3; text-decoration: underline">Map</a></div-->
			<div id="dt_image">
				<!--span id="caption">caption here</span-->
			</div>

			<div id="detailInfo" style="text-align:left;float:left;margin-top:5px;margin-left:20px; width:300px; position:relative; border: solid 0px #CCC;">
				<!--label for="dt_uuid">ID</label>
				<div id="dt_uuid" style="font-weight:normal;"></div-->
				<label for="dt_fullName">Name</label>
				<div id="dt_fullName" style="font-weight:normal;"></div>
				<label for="dt_age">Age</label>
				<div id="dt_age" style="font-weight:normal;"></div>
				<label for="dt_gender">Gender </label>
				<div id="dt_gender" style="font-weight:normal;"></div>
				<label for="dt_status">Status </label>
				<div id="dt_status" style="font-weight:normal;"></div>
				<label for="dt_statusSahanaUpdated">When Reported</label>
				<div id="dt_statusSahanaUpdated" style="font-weight:normal;"></div>
				<label for="dt_location">Last Known Location</label>
				<div id="dt_location" style="font-weight:normal;"></div>
				<label for="dt_comments">Comments</label>
				<div id="dt_comments" style="font-weight: normal; height: 50px; overflow-y: auto;"></div>
				<!--label id="dt_notes_label" for="dt_notes" style="display:none;">Note Contents</label-->
				<div id="dt_notes"></div>
			</div>
			<div id="dt_hospitalIcon" ></div>
			<div id="map_canvas" class="map">Loading...</div>
			<div style="clear:both;"></div>
		</div>
		<div id="exitFullScreen"></div>
		<div id="exitFullScreenIpad" onclick="ScrollView.exitFullScreen()">Tap here to exit...</div>
		<div id="glass" onclick="Utils.closePopup();">&nbsp;</div>

		<div id="helpPane">
			<div id="close" onclick="Utils.closeHelp();"><a href="javascript:void(0)" style="color:#6694E3; text-decoration: underline">Close</a></div>
			<div id="helpInfo" style="text-align:left;float:left;margin-top:35px;margin-left:20px; position:relative; border: solid 0px #CCC;">
			</div>
			<div style="clear:both;"></div>
		</div>
		<input name="language" id="language" type="hidden" value="<? echo L; ?>">
		<br />

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


