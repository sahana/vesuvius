<?
/**
 * @name         PL User Services
 * @version      1.9.4
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0705
 */


function shn_plus_default() {
	shn_plus_reportlog();
}



function shn_plus_header2() {
	global $global;
	echo "<ul>";

	if($global['action'] == "reportlog" || $global['action'] == "default") {
		echo "<li>People Reported</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=reportlog\">People Reported</a></li>";
	}

	if($global['action'] == "rawLog") {
		echo "<li>Raw Access Log</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=rawLog\">Raw Access Log</a></li>";
	}

	if($global['action'] == "stat") {
		echo "<li>Access Statistics</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=stat\">Access Statistics</a></li>";
	}

	if($global['action'] == "settings") {
		echo "<li>Client Settings</li>";
	} else {
		echo "<li><a href=\"index.php?mod=plus&act=settings\">Client Settings</a></li>";
	}

	echo "</ul><hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">";
}



function shn_plus_reportlog() {
	global $global;
	shn_plus_header2();

	echo "<div id=\"home\">";

	// figure out log traversal navigation....

	if(isset($_GET['pagenum'])) {
		$startPoint = (int)$_GET['pagenum']*100;
		$endPoint = $startPoint + 100;
		$msg = "showing people ".($startPoint+1)." to ".$endPoint;
	} else {
		$startPoint = 0;
		$endPoint = $startPoint + 100;
		$msg = "showing last 100";
	}

	if((int)$_GET['pagenum'] > 0) {
		$previous = "<a href=\"index.php?mod=plus&act=reportlog&pagenum=".((int)$_GET['pagenum']-1)."\">◄</a>";
	} else {
		$previous = "◄";
	}

	$q = "
		SELECT count(*)
		FROM `plus_report_log`;
	";
	$result = $global['db']->Execute($q);
	$row = $result->FetchRow();
	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = "<a href=\"index.php?mod=plus&act=reportlog&pagenum=".($_GET['pagenum']+1)."\">►</a>";
	} else {
		$next = "►";
		$msg = "showing people ".($startPoint+1)." to ".$totalCount;
	}

	$query  = "
		SELECT *
		FROM plus_report_log
		ORDER BY report_time DESC
		LIMIT ".$startPoint.", 100;
	";
	$result = $global['db']->Execute($query);
	$count = 0;

	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>People Reported (".$msg." of ".$totalCount." total) ".$previous." ".$next."</legend>";


	echo "<table id=\"regLog\">
		<tr>
			<td class=\"evener\"><b>Origin ID / Origin URL</b></td>
			<td class=\"evener\"><b>Time</b></td>
			<td class=\"evener\"><b>XML Enumeration</b></td>
		</tr>";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		$uu = explode("/", $row['p_uuid']);
		$url = $uu[1];
		echo "  <tr>
				<td ".$odd."><a href=\"".$url."\">".$row['p_uuid']."</a></td>
				<td ".$odd.">".$row['report_time']."</td>
				<td ".$odd.">".$row['enum']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=3 class=\"odder\">No People Rported Yet!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}




function shn_plus_rawLog() {
	global $global;
	shn_plus_header2();

	echo "<div id=\"home\">";

	// figure out log traversal navigation....

	if(isset($_GET['pagenum'])) {
		$startPoint = (int)$_GET['pagenum']*100;
		$endPoint = $startPoint + 100;
		$msg = "showing hits ".($startPoint+1)." to ".$endPoint;
	} else {
		$startPoint = 0;
		$endPoint = $startPoint + 100;
		$msg = "showing last 100";
	}

	if((int)$_GET['pagenum'] > 0) {
		$previous = "<a href=\"index.php?mod=plus&act=rawLog&pagenum=".((int)$_GET['pagenum']-1)."\">◄</a>";
	} else {
		$previous = "◄";
	}

	$q = "
		SELECT count(*)
		FROM `plus_access_log`;
	";
	$result = $global['db']->Execute($q);
	$row = $result->FetchRow();
	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = "<a href=\"index.php?mod=plus&act=rawLog&pagenum=".($_GET['pagenum']+1)."\">►</a>";
	} else {
		$next = "►";
		$msg = "showing hits ".($startPoint+1)." to ".$totalCount;
	}

	$q  = "
		SELECT *
		FROM plus_access_log
		ORDER BY access_time DESC
		LIMIT ".$startPoint.", 100;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Raw Access Log (".$msg." of ".$totalCount." total) ".$previous." ".$next."</legend>";

	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>Time</b></td>
		<td class=\"evener\"><b>Client Name</b></td>
		<td class=\"evener\"><b>Client Version</b></td>
		<td class=\"evener\"><b>IP</b></td>
		<td class=\"evener\" style=\"text-align: left;\"><b>Call</b></td>
		<td class=\"evener\"><b>API Version</b></td>
	</tr>";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd.">".$row['access_time']."</td>
				<td ".$odd.">".$row['application']."</td>
				<td ".$odd.">".$row['version']."</td>
				<td ".$odd.">".$row['ip']."</td>
				<td ".$odd." style=\"text-align: left;\"><b>".$row['call']."</b></td>
				<td ".$odd.">".$row['api_version']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}


function shn_plus_settings() {
	global $global;
	require_once($global['approot'].'/inc/lib_xajax.inc');
	shn_plus_header2();

	$posted = 0;
	// if its a post ~ save configuration after we validate
	if(isset($_POST['timeout'])) {
		$posted = 1;
		$errorCount = 0;
		$t = (int)$_POST['timeout'];
		if(($t < 600) || ($t > 315360000)) {
			$errorCount++;
			add_error("Please use a positive integer value for the timeout in seconds (between 600 and 315,360,000 ~10 minutes to 10 years).");
		}
		if($errorCount == 0 ) {
			add_confirmation('Settings Saved!');
			shn_db_config_update("plus","timeout",  $_POST['timeout']);
		} else {
			add_warning('Errors were encountered, settings were not saved.');
		}
	}
	$timeout = "";
	if ( $posted ) {
		$timeout = $_POST['timeout'];
	} else {
		$timeout = shn_db_get_config("plus","timeout");
	}

	// newly visited... option not yet set, so set and save
	if($timeout == "") {
		$timeout = 864000; // 100 days default
		shn_db_config_update("plus","timeout",  $timeout);
	}

	shn_form_fopen("settings", null,array('req_message'=>true));
		shn_form_fsopen("Client Settings");
		?>
		<table id="popSettings">
		<tr>
			<td class="odd">Client Session Timeout (currently used in ReUnite) [in seconds]</td>
			<td class="odd"><input type="text" name="timeout" id="timeout" value="<?php echo $timeout; ?>" tabindex="1"  /><span class='req'>*</span></td>
		</tr>
		</table>
		<br><br>
		<?php
		shn_form_submit("Save Settings", $submit_opts = "class=\"styleTehButton\"");
		shn_form_fsclose();
	shn_form_fclose();
}



function shn_plus_stat() {
	global $global;
	shn_plus_header2();

	echo "<div id=\"home\">";

	// by api call /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `call`, count(*)
		FROM `plus_access_log`
		group by `call`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 220px; float: left;  margin-right: 5px;\">
			<form>
				<fieldset>
					<legend>Hits by API Function</legend>
					<table id=\"regLog\">
						<tr>
							<td class=\"evener\"><b>Function</b></td>
							<td class=\"evener\"><b>Hits</b></td>
						</tr>
	";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd.">".$row['call']."</td>
				<td ".$odd.">".$row['count(*)']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "
					</table>
				</fieldset>
			</form>
		</div>
	";



	// by api version /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `api_version`, count(*)
		FROM `plus_access_log`
		group by `api_version`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 200px; float: left; margin-right: 5px;\">
			<form>
				<fieldset>
					<legend>Hits by API Version</legend>
					<table id=\"regLog\">
						<tr>
							<td class=\"evener\"><b>Version</b></td>
							<td class=\"evener\"><b>Hits</b></td>
						</tr>
	";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd.">".$row['api_version']."</td>
				<td ".$odd.">".$row['count(*)']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "
					</table>
				</fieldset>
			</form>
		</div>
	";


	// by ip /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `ip`, count(*)
		FROM `plus_access_log`
		group by `ip`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 200px; float: left; margin-right: 5px;\">
			<form>
				<fieldset>
					<legend>Hits by IP Address</legend>
					<table id=\"regLog\">
						<tr>
							<td class=\"evener\"><b>IP Address</b></td>
							<td class=\"evener\"><b>Hits</b></td>
						</tr>
	";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
				<td ".$odd.">".$row['ip']."</td>
				<td ".$odd.">".$row['count(*)']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "
					</table>
				</fieldset>
			</form>
		</div>
	";


	// by application /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `application`, count(*)
		FROM `plus_access_log`
		group by `application`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 200px; float: left; margin-right: 5px;\">
			<form>
				<fieldset>
					<legend>Hits by Application</legend>
					<table id=\"regLog\">
						<tr>
							<td class=\"evener\"><b>Application</b></td>
							<td class=\"evener\"><b>Hits</b></td>
						</tr>
	";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		if(trim($row['application']) == "") {
			$app = "TriagePic and others";
		} else {
			$app = $row['application'];
		}
		echo "  <tr>
				<td ".$odd.">".$app."</td>
				<td ".$odd.">".$row['count(*)']."</td>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Service Calls Yet!</td></tr>";
	}
	echo "
					</table>
				</fieldset>
			</form>
		</div>
	";




	echo "</div>";
}






