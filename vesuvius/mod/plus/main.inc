<?
/**
 * @name         PL User Services
 * @version      24
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0214
 */



global $tabid;
$tabid = "&tabid=".$_GET['tabid'];



function shn_plus_default() {

	global $global;

	$control = "";

	shn_tabmenu_open();
	shn_tabmenu_item("plus",     _t("PLUS+"), "plus");
	shn_tabmenu_item("reported", _t("People Reported"),    "plus");
	shn_tabmenu_item("raw",      _t("Raw Access Log"),     "plus");
	shn_tabmenu_item("stat",     _t("Access Statistics"),  "plus");

	shn_tabmenu_close();


	if(isset($_GET['plus'])) {
		$control = "shn_plus_plus";

	} elseif(isset($_GET['raw'])) {
		$control = "shn_plus_raw";

	} elseif(isset($_GET['stat'])) {
		$control = "shn_plus_stat";

	} elseif(isset($_GET['reported'])) {
		$control = "shn_plus_reported";
	}

	if($control == "") {
		$control = "shn_plus_plus";
	}

	$control();
}


function shn_plus_plus() {
	echo '
		<br>
		<br>
		<li><a href="http://goo.gl/z5VnJ" target="_blank">PLUS API Specification</a></li>
		<li><a href="https://groups.google.com/forum/#!forum/plus-web-services" target="_blank">PLUS Mailing List</a></li>
	';
}



function shn_plus_reported() {

	global $global;
	global $tabid;

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

	if(isset($_GET['pagenum']) && (int)$_GET['pagenum'] > 0) {
		$previous = '<a href="plus?reported&pagenum='.((int)$_GET['pagenum']-1).$tabid.'">◄</a>';
	} else {
		$previous = "◄";
		$_GET['pagenum'] = 0;
	}

	$q = "
		SELECT count(*)
		FROM `plus_report_log`;
	";
	$result = $global['db']->Execute($q);
	$row = $result->FetchRow();
	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = '<a href="plus?reported&pagenum='.($_GET['pagenum']+1).$tabid.'">►</a>';
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
		echo "  <tr>
				<td ".$odd."><a href=\"".makePersonUrl($row['p_uuid'])."\" target=\"_blank\">".$row['p_uuid']."</a></td>
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




function shn_plus_raw() {

	global $global;
	global $tabid;

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

	if(isset($_GET['pagenum']) && (int)$_GET['pagenum'] > 0) {
		$previous = '<a href="plus?raw&pagenum='.((int)$_GET['pagenum']-1).$tabid.'">◄</a>';
	} else {
		$previous = "◄";
		$_GET['pagenum'] = 0;
	}

	$q = "
		SELECT count(*)
		FROM `plus_access_log`;
	";
	$result = $global['db']->Execute($q);
	$row = $result->FetchRow();
	$totalCount = $row['count(*)'];

	if($endPoint < $totalCount) {
		$next = '<a href="plus?raw&pagenum='.($_GET['pagenum']+1).$tabid.'">►</a>';
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



function shn_plus_stat() {

	global $global;
	global $tabid;

	$where = "";
	if(isset($_GET['last'])) {
		$where = "WHERE access_time > DATE_SUB(NOW(), INTERVAL ".(int)$_GET['last']." day) ";
		$last = "&last=".(int)$_GET['last'];
	} else {
		$where = "WHERE access_time > DATE_SUB(NOW(), INTERVAL 9999 day) ";
		$last = "&last=9999";
		$_GET['last'] = 9999;
	}

	$notLike = "";
	$ext = "";
	if(isset($_GET['ext'])) {
		if($where == "") {
			$notLike = "
				WHERE ip NOT LIKE '130.14.109%'
				AND ip NOT LIKE '130.14.108%'
				AND ip NOT LIKE '130.14.119%'
			";
		} else {
			$notLike = "
				AND ip NOT LIKE '130.14.109%'
				AND ip NOT LIKE '130.14.108%'
				AND ip NOT LIKE '130.14.119%'
			";
		}
		$ext = "&ext";
	}

	echo "<div id=\"home\">";

	// by ip /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `ip`, count(*)
		FROM `plus_access_log`
		".$where."
		".$notLike."
		group by `ip`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "<br><br>";

	if($ext != "") {
		echo 'SOURCE: <span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$last.$tabid.'\'">ALL</span> <span class="styleTehButton" style="opacity: 0.5">Excluding Internal Sources</span>';
	} else {
		echo 'SOURCE: <span class="styleTehButton" style="opacity: 0.5">ALL</span> <span class="styleTehButton" onclick="window.location.href=\'plus?stat&ext'.$last.$tabid.'\'">Excluding Internal Sources</span>';
	}

	echo " &nbsp; &nbsp; DURING LAST: ";

	if((int)$_GET['last'] == 30) {
		echo '<span class="styleTehButton" style="opacity: 0.5">30</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=30'.$tabid.'\'">30</span> ';
	}
	if((int)$_GET['last'] == 60) {
		echo '<span class="styleTehButton" style="opacity: 0.5">60</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=60'.$tabid.'\'">60</span> ';
	}
	if((int)$_GET['last'] == 90) {
		echo '<span class="styleTehButton" style="opacity: 0.5">90</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=90'.$tabid.'\'">90</span> ';
	}
	if((int)$_GET['last'] == 120) {
		echo '<span class="styleTehButton" style="opacity: 0.5">120</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=120'.$tabid.'\'">120</span> ';
	}
	if((int)$_GET['last'] == 180) {
		echo '<span class="styleTehButton" style="opacity: 0.5">180</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=180'.$tabid.'\'">180</span> ';
	}
	if((int)$_GET['last'] == 365) {
		echo '<span class="styleTehButton" style="opacity: 0.5">365</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=365'.$tabid.'\'">365</span> ';
	}
	if((int)$_GET['last'] == 9999) {
		echo '<span class="styleTehButton" style="opacity: 0.5">9999</span> ';
	} else {
		echo '<span class="styleTehButton" onclick="window.location.href=\'plus?stat'.$ext.'&last=9999'.$tabid.'\'">9999</span> ';
	}

	echo "
		DAYS<br>
		<br><br>
		<div class=\"form-container\" style=\"width: 230px; float: left; margin-right: 5px;\">
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
				<td ".$odd."><a href=\"http://www.geoiptool.com/en/?IP=".$row['ip']."\" target=\"_blank\">".$row['ip']."</a></td>
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

	// by api call /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `call`, count(*)
		FROM `plus_access_log`
		".$where."
		".$notLike."
		group by `call`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 270px; float: left;  margin-right: 5px;\">
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
		".$where."
		".$notLike."
		group by `api_version`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 230px; float: left; margin-right: 5px;\">
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


	// by application /////////////////////////////////////////////////////////////////////////////////

	$q  = "
		SELECT `application`, count(*)
		FROM `plus_access_log`
		".$where."
		".$notLike."
		group by `application`
		order by count(*) desc;
	";
	$result = $global['db']->Execute($q);
	$count = 0;

	echo "
		<div class=\"form-container\" style=\"width: 230px; float: left; margin-right: 5px;\">
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


