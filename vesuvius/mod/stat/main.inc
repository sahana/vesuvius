<?php
/**
 * @name         Statistics
 * @version      0.1
 * @package      stat
 * @author       Lan Ngoc Le <lale@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0711
 */


global $global;
global $conf;
require_once($global['approot'].'/mod/stat/lib_stat.inc');

function shn_stat_menu() {
	global $global;
	echo "
		<script>".file_get_contents($global['approot']."/mod/stat/stat.js")."</script>
		<ul>
			<li><a href=\"index.php?mod=stat&world\">World</a></li>
			<li><a href=\"index.php?mod=stat&act=galaxy\">Galaxy</a></li>
			<li><a href=\"index.php?mod=stat&act=universe\">Universe</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		
/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_stat_default() {
	global $global;
	shn_stat_menu();
	echo "People Statistics";
	<div id="intro">	
	<h1>People Statistics (PS) Module Beta Site for PL.NLM.NIH.GOV</h1>	   
  	<h4>This is an exploration of the statistics useful to the four groups of users envisioned for the PL.NLM.NIH.GOV site and is an exploratory space leading to a PHP module development.<br />
	<div id="selectEvent">
	<p>Please click the drop-down list to select an event</p>
	
    <select name="event" id="event">
      <option value="01">Joplin Tornado</option>
      <option value="02">Japan Earthquake and Tsunami</option>
      <option value="03">Christchurch Earthquake</option>
	  <option value="04">TriagePic 2010</option>
	  <option value="05">CMAX 2010</option>
      <option value="06">Haiti Earthquake</option>
      <option value="07">CMAX 2009</option>
    </select>
	</p>
	</div>
	<br /> 
	
	<div id="header1">Joplin</div>
	<div id="content">
		<div class="joplin">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status</td>
				<td><a href="status_JO.php">Status</a></td>
				<td><a href="status_JO.php">Status</a></td>
				<td><a href="status_JO.php">Status</a></td>
				<td><a href="status_JO.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td><a href="gender_JO.php">Gender</a></td>
				<td><a href="gender_JO.php">Gender</a></td>
				<td><a href="gender_JO.php">Gender</a></td>
				<td><a href="gender_JO.php">Gender</a></td>
				</tr>
				<tr>
				<td>Age</td>
				<td><a href="age_range_JO.php">Age</a></td>
				<td><a href="age_range_JO.php">Age</a></td>
				<td><a href="age_range_JO.php">Age</a></td>
				<td><a href="age_range_JO.php">Age</a></td>
				</tr>
				<tr>
			</table><br /><br />
		</div>
		<div class="japan">
			<table>
			<tr>
			<th>Report Type</th>
			<th>Public Users</th>
			<th>Hospital Staffs</th>
			<th>NLM-LPF Team</th>
			<th>NLM Management</th>
			</tr>
			<tr>
			<td>Status</td>
			<td><a href="status_JP.php">Status</a></td>
			<td><a href="status_JP.php">Status</a></td>
			<td><a href="status_JP.php">Status</a></td>
			<td><a href="status_JP.php">Status</a></td>
			</tr>
			<tr>
			<td>Gender</td>
			<td><a href="gender_JP.php">Gender</a></td>
			<td><a href="gender_JP.php">Gender</a></td>
			<td><a href="gender_JP.php">Gender</a></td>
			<td><a href="gender_JP.php">Gender</a></td>
			</tr>
			<tr>
			<td>Age</td>
			<td><a href="age_range_JP.php">Age</a></td>
			<td><a href="age_range_JP.php">Age</a></td>
			<td><a href="age_range_JP.php">Age</a></td>
			<td><a href="age_range_JP.php">Age</a></td>
			</tr>
			<tr>
			<td>Reported Rate</td>
			<td><a href="arrival_bydate_JP.php">Reported Rate (per day)</a></td>
			<td><a href="arrival_bydate_JP.php">Reported Rate (per day)</a></td>
			<td><a href="arrival_bydate_JP.php">Reported Rate (per day)</a></td>
			<td><a href="arrival_bydate_JP.php">Reported Rate (per day)</a></td>
			</tr>
			<tr>
			<td>Reported Rate (per hour, zoomable)</td>
			<td><a href="arrival_byhour_JP.php">Reported Rate (per hour)</a></td>
			<td><a href="arrival_byhour_JP.php">Reported Rate (per hour)</a></td>
			<td><a href="arrival_byhour_JP.php">Reported Rate (per hour)</a></td>
			<td><a href="arrival_byhour_JP.php">Reported Rate (per hour)</a></td>
			</tr>
			<tr>
			<td>Expiry Date Counts</td>
			<td>not available</td>
			<td>not available</td>
			<td>
			<form name="content">
			<p align="left">
			<select name="menu">
			<option value="expiry_June">Expiry Count for June</a></option>
			<option value="expiry_July">Expiry Count for July</option>
			<option value="expiry_August">Expiry Count for August</option>
			<option value="expiry_Sept">Expiry Count for September</option>
			<option value="expiry_Oct">Expiry Count for October</option>
			<option value="expiry_Nov">Expiry Count for November</option>
			<option value="expiry_Dec">Expiry Count for December</option>
			<option value="expiry_2011">Expiry Count for 2011</option>
			<option value="expiry_2011">Expiry Count for 2012</option>
			</select>
			<input type="button" onClick="location=document.content.menu.options[document.content.menu.selectedIndex].value;" value="GO">
			</p>
			</form>
			</td>
			<td>not available</td>
			</tr>
			</table>		
		</div>
		<div class="christchurch">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status</td>
				<td><a href="status_CC.php">Status</a></td>
				<td><a href="status_CC.php">Status</a></td>
				<td><a href="status_CC.php">Status</a></td>
				<td><a href="status_CC.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td>not available</td>
				<td>not available</td>
				<td>not available</td>
				<td>not available</td>
				</tr>
				<tr>
				<td>Age</td>
				<td>not available</td>
				<td>not available</td>
				<td>not available</td>
				<td>not available</td>
				</tr>
				<tr>
				<td>Reported Rate (per day)</td>
				<td><a href="arrival_bydate_CC.php">Reported Rate (per day)</a></td>
				<td><a href="arrival_bydate_CC.php">Reported Rate (per day)</a></td>
				<td><a href="arrival_bydate_CC.php">Reported Rate (per day)</a></td>
				<td><a href="arrival_bydate_CC.php">Reported Rate (per day)</a></td>
				</tr>
				<tr>
				<td>Reported Rate (per hour)</td>
				<td><a href="arrival_byhour_CC.php">Reported Rate (per hour)</a></td>
				<td><a href="arrival_byhour_CC.php">Reported Rate (per hour)</a></td>
				<td><a href="arrival_byhour_CC.php">Reported Rate (per hour)</a></td>
				<td><a href="arrival_byhour_CC.php">Reported Rate (per hour)</a></td>
				</tr>
			</table><br /><br />
		</div>
		<div class="triagepic2010">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status (Zone)</td>
				<td>not available</td>
				<td><a href="status_cmax10_sub.php">Status</a></td>
				<td><a href="status_cmax10_sub.php">Status</a></td>
				<td><a href="status_cmax10_sub.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td>not available</td>
				<td><a href="gender_cmax10_sub.php">Gender</a></td>
				<td><a href="gender_cmax10_sub.php">Gender</a></td>
				<td><a href="gender_cmax10_sub.php">Gender</a></td>
				</tr>
				<tr>
				<td>Reported rate by hour</td>
				<td>not available</td>
				<td><a href="TP_sub_byhour.php">Rate by hour</a></td>
				<td><a href="TP_sub_byhour.php">Rate by hour</a></td>
				<td><a href="TP_sub_byhour.php">Rate by hour</a></td>
				</tr>
				<tr>
				<td>Reported rate by minute</td>
				<td>not available</td>
				<td><a href="TP_sub_byminute.php">Rate by minute</a></td>
				<td><a href="TP_sub_byminute.php">Rate by minute</a></td>
				<td><a href="TP_sub_byminute.php">Rate by minute</a></td>
				</tr>
				<tr>
				<td>Status (zone) counts by hour</td>
				<td>not available</td>
				<td><a href="TP_sub_stacked_status_byhour.php">Status count</a></td>
				<td><a href="TP_sub_stacked_status_byhour.php">Status count</a></td>
				<td><a href="TP_sub_stacked_status_byhour.php">Status count</a></td>
				</tr>
				<tr>
			</table><br /><br />
		</div>
		<div class="cmax10">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status</td>
				<td><a href="status_cmax10.php">Status</a></td>
				<td><a href="status_cmax10.php">Status</a></td>
				<td><a href="status_cmax10.php">Status</a></td>
				<td><a href="status_cmax10.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td><a href="gender_cmax10.php">Gender</a></td>
				<td><a href="gender_cmax10.php">Gender</a></td>
				<td><a href="gender_cmax10.php">Gender</a></td>
				<td><a href="gender_cmax10.php">Gender</a></td>
				</tr>
				<tr>
				<td>Age</td>
				<td><a href="age_cmax10.php">Age</a></td>
				<td><a href="age_cmax10.php">Age</a></td>
				<td><a href="age_cmax10.php">Age</a></td>
				<td><a href="age_cmax10.php">Age</a></td>
				</tr>
				<tr>
				<td>Reported Rate</td>
				<td><a href="TP_nnmc_byhour.php">From NNMC</a><br />
					<a href="TP_sub_byhour.php">From Suburban</a><br />
					</td>
				<td><a href="TP_nnmc_byhour.php">From NNMC</a><br />
					<a href="TP_sub_byhour.php">From Suburban</a><br />
					</td>
				<td><a href="TP_nnmc_byhour.php">From NNMC</a><br />
					<a href="TP_sub_byhour.php">From Suburban</li><br />
					</td>
				<td><a href="TP_nnmc_byhour.php">From NNMC</a><br />
					<a href="TP_sub_byhour.php">From Suburban</a><br />    
				</td>
				</tr>
				<tr>
				</tr>
			</table><br />
		</div>
		<div class="haiti">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status</td>
				<td><a href="status_HA.php">Status</a></td>
				<td><a href="status_HA.php">Status</a></td>
				<td><a href="status_HA.php">Status</a></td>
				<td><a href="status_HA.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td><a href="gender_HA.php">Gender</a></td>
				<td><a href="gender_HA.php">Gender</a></td>
				<td><a href="gender_HA.php">Gender</a></td>
				<td><a href="gender_HA.php">Gender</a></td>
				</tr>
				<tr>
				<td>Age</td>
				<td><a href="age_range_HA.php">Age</a></td>
				<td><a href="age_range_HA.php">Age</a></td>
				<td><a href="age_range_HA.php">Age</a></td>
				<td><a href="age_range_HA.php">Age</a></td>
				</tr>
				<tr>
				<td>Reported Rate (per day)</td>
				<td><a href="arrival_bydate_HA.php">Rate</a></td>
				<td><a href="arrival_bydate_HA.php">Rate</a></td>
				<td><a href="arrival_bydate_HA.php">Rate</a></td>
				<td><a href="arrival_bydate_HA.php">Rate</a></td>
				</tr>
				<tr>
				<td>Reported Rate (per hour)</td>
				<td><a href="arrival_byhour_HA.php">Rate</a></td>
				<td><a href="arrival_byhour_HA.php">Rate</a></td>
				<td><a href="arrival_byhour_HA.php">Rate</a></td>
				<td><a href="arrival_byhour_HA.php">Rate</a></td>
				</tr>
				<tr>
				</tr>
			</table><br />
		</div>
		<div class="cmax09">
			<table>
				<tr>
				<th>Report Type</th>
				<th>Public Users</th>
				<th>Hospital Staffs</th>
				<th>NLM-LPF Team</th>
				<th>NLM Management</th>
				</tr>
				<tr>
				<td>Status</td>
				<td>not available</td>
				<td><a href="status_cmax09.php">Status</a></td>
				<td><a href="status_cmax09.php">Status</a></td>
				<td><a href="status_cmax09.php">Status</a></td>
				</tr>
				<tr>
				<td>Gender</td>
				<td>not available</td>
				<td><a href="gender_cmax09.php">Gender</a></td>
				<td><a href="gender_cmax09.php">Gender</a></td>
				<td><a href="gender_cmax09.php">Gender</a></td>
				</tr>
				<tr>
			</table><br />
		</div>
	</div>

	
	
	
	
	
/**
 * the galaxy action!
 * @access public
 * @return void
 */
function shn_stat_galaxy() {
	global $global;
	shn_stat_menu();
	echo "hello galaxy!";
	echo "<script>call_hello();</script>";
}

/**
 * the universe action!
 * @access public
 * @return void
 */
function shn_stat_universe() {
	global $global;
	shn_stat_menu();
	echo "hello universe2!";
	
		$q = "
			SELECT *
			FROM rez_pages
			WHERE rez_page_id = 14
			LIMIT 1;
		";
		$res = $global['db']->Execute($q);
		if($res) {
			while($row = $res->FetchRow() ) {
				echo "<h2>".$row['rez_page_title']."</h2>";
			}
		}
}

