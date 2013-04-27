<?php
/**
 * @name         Statistics
 * @version      0.7
 * @package      stat
 * @author       Lan Ngoc Le <lale@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1027
 */


global $global;
global $conf;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

/* function shn_stat_mainmenu() {
}
function shn_stat_header() {
}
function shn_stat_footer() {
} */
function shn_stat_html_head() {
	echo '
			<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
			<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
			<head>
			<title>People Statistics</title>
			<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
			<meta name="Software " content="US National Library of Medicine People Locator" />
			<meta name="Website" content="http://pl.nlm.nih.gov" />
			<meta name="Licence" content="Lesser General Public Licence, Version 2.1" />
			<meta name="Licence Website" content="http://www.gnu.org/licenses/lgpl-2.1.txt" />
			<meta name="google-site-verification" content="Y2Ts00HnBQEr3M3KegrKRRAMVuQPejmqeqPKDsMGRGw" />
			<link rel="chrome-webstore-item" href="https://chrome.google.com/webstore/detail/fbnpmpdcnjkhfcgeeklebjmopaheplce">
			<link rel="stylesheet" media="screen, projection" type="text/css" href="theme/lpf3/sahana.css" />
			<link rel="stylesheet" media="print" type="text/css" href="theme/lpf3/print.css" />
			<link rel="stylesheet" media="handheld" type="text/css" href="theme/lpf3/mobile.css" />
			<!--[if IE 6]>
			<link rel="stylesheet" type="text/css" href="theme/lpf3/ie6.css" />
			<![endif]-->
			<!--[if IE 7]>
			<link rel="stylesheet" type="text/css" href="theme/lpf3/ie7.css" />
			<![endif]-->
			<!--[if IE 8]>
			<link rel="stylesheet" type="text/css" href="theme/lpf3/ie8.css" />
			<![endif]-->
			<!--[if IE 9]>
			<link rel="stylesheet" type="text/css" href="theme/lpf3/ie9.css" />
			<![endif]-->
			<script type="text/javascript" src="res/js/jquery.js"></script>
			<script type="text/javascript" src="res/js/highcharts.js"></script>
			<script type="text/javascript" src="res/js/exporting.js"></script>
			<script type="text/javascript" src="res/js/excanvas.compiled.js"></script>
			<script type="text/javascript" src="res/js/showHide.js"></script>
			<script type="text/javascript">
			window.setTimeout(function(){console.log("refresh!"); location.reload(true);}, 120000);
			</script>
			<link rel="icon" type="image/png" href="favicon.png">
			<style>
			h1 {
			color: #34689A;
			font-family: arial;
			font-size: 28px;
			line-height: 28px;
			font-weight: normal;
}

			html {
			height: 100%;
}
			body {
			height: 100%;
			margin: 0px;
}
			#container {
			background: #FFFFFF;
			margin: auto;
			// 			font: 1.5em arial, verdana, sans-serif;
			width: 100%;
			min-height: 100%;
}
	  </style>
			</head>
			';
}
function shn_stat_login() {
}


function shn_stat_menu() {

	global $global;

	$shortname = $_GET['shortname'];

	$q = "
			SELECT *
			FROM incident
			WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
					";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
	}
	if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
		$description = "";
	}

	echo "
			<div style=\"margin: 20px;\">
			<h1>People Statistics ".$description."</h1>\n
					<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; min-height:100%;\">
					\n
					Please select from these available statistics:\n
					<ul>
					<li><a href=\"index.php?mod=stat&act=arrival\">Arrival Rates</a></li>
					<li><a href=\"index.php?mod=stat&act=cummulative_arrival\">Cummulative Arrivals</a></li>
					<li><a href=\"index.php?mod=stat&act=stacked_cummulative_arrival\">Stacked Cummulative Arrivals</a></li>
					<li><a href=\"index.php?mod=stat&&act=stacked_status_daily_irregular_interval\">TriagePic Zone Status on Arrivals</a></li>
					<li><a href=\"index.php?mod=stat&act=demographic\">Demographic Pie Charts</a></li>
					<li><a href=\"index.php?mod=stat&act=pie_status\">People Locator Status Pie Chart</a></li>
					<li><a href=\"index.php?mod=stat&act=transit\">Patient Transit Time</a></li>
						
					</ul>
					<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
					";

	//if($shortname=='test' or $shortname=='testtp') {
	//echo "
	//<ul>
	//<li><a href=\"index.php?mod=stat&&act=stacked_status_daily_irregular_interval\">Daily Stacked Status</a></li>
	//</ul></div>
	//<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
	//";
	//}
	//echo "</ul></div>";
}



/** default module action */
function shn_stat_default() {

	global $global;
	shn_stat_menu();
	shn_stat_html_head();
}



/***********************************************************
 The report rate by date for sendai, christchurch, hepl, turkey
***********************************************************/
function shn_stat_arrival_bydate() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	//for sendai2011, add 'a.source_date >'2011-01-01'' in the where filter
	if($shortname=="sendai2011") {
		$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				join incident c ON c.incident_id= b.incident_id
				where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-01-01')
						GROUP BY DATE(source_date) order by DATE(source_date)";
	}
	//for hepl
	if($shortname=="hepl") {
		$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				join incident c ON c.incident_id= b.incident_id
				where (c.shortname like '".$shortname."' and a.source_date >'2010-01-11')
						GROUP BY DATE(source_date) order by DATE(source_date)";
	}
	//for christchurch
	if($shortname=="christchurch") {
		$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				join incident c ON c.incident_id= b.incident_id
				where (c.shortname like '".$shortname."' and a.source_date >'2011-02-20')
						GROUP BY DATE(source_date) order by DATE(source_date)";
	}
	//for turkey
	if($shortname=="christchurch") {
		$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				join incident c ON c.incident_id= b.incident_id
				where (c.shortname like '".$shortname."' and a.source_date >'2011-10-22')
						GROUP BY DATE(source_date) order by DATE(source_date)";
	}
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();

	if($row === FALSE) {
		die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
	}

	while($row = $res->FetchRow());
	echo json_encode($count_source_date);
	echo json_encode($source_date);
	?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);
echo json_encode($source_date);
echo json_encode($count_source_date);
echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Date for $shortname'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I: %M %p',\n" ;
echo "minute: '%I: %M %p',\n" ;
echo "hour: '%I',\n" ;
echo "day: '%e. %b',\n" ;
echo "week: '%e. %b',\n" ;
echo "month: '%b \'%y',\n" ;
echo "year: '%Y'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";
echo "title: {\n" ;
echo "text: 'People Count'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "tooltip: {\n" ;
echo "enabled: false,\n" ;
echo "formatter: function() {\n" ;
echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
echo "this.x +': '+ this.y;\n" ;
echo "}\n" ;
echo "},\n" ;
echo "plotOptions: {\n" ;
echo "line: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true\n" ;
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;
echo "},\n" ;
echo "series: [{\n" ;
echo "name: '". $shortname;
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data\n" ;
echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;
echo "</script>\n" ;
}
/********************************************
 * Arrival Rate by Hour
* For sendai2011, hepl, christchurch, turkey
*********************************************/
function shn_stat_arrival_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];

	//for sendai2011, add 'a.source_date >'2011-01-01'' in the where filter

	if($shortname=="sendai2011") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				join incident c ON c.incident_id= b.incident_id
				where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-01-01')
					GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date)";
	}
	//for hepl
	if($shortname=="hepl") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
							join person_uuid b ON a.p_uuid= b.p_uuid
							join incident c ON c.incident_id= b.incident_id
							where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2010-01-11')
							GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date)";
	}
	//for christchurch
	if($shortname=="christchurch") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
							join person_uuid b ON a.p_uuid= b.p_uuid
							join incident c ON c.incident_id= b.incident_id
							where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-02-20')
							GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date)";
	}
	//for turkey
	if($shortname=="turkey2011") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			join incident c ON c.incident_id= b.incident_id
			where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-10-22')
			GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date)";
	}
	//for CMAX2010, cannot filter by incidentid for cmax2010
	if($shortname=="cmax2010") {
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
 		JOIN edxl_co_header b ON b.de_id = a.de_id
 		JOIN edxl_co_lpf c ON c.co_id = b.co_id
 		GROUP BY DATE( when_sent ) , HOUR(when_sent)
 		ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	}
	//for new
	if($shortname=="new"){
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
			JOIN edxl_co_header b ON b.de_id = a.de_id
			JOIN edxl_co_lpf c ON c.co_id = b.co_id
			WHERE (c.event_name ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date like '2011-10-19%')
						GROUP BY DATE( when_sent ) , HOUR(when_sent)
						ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	}
	//for testtp or test
	if(($shortname=="testtp") || ($shortname=="test")){
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
				JOIN edxl_co_header b ON b.de_id = a.de_id
				JOIN edxl_co_lpf c ON c.co_id = b.co_id
				WHERE c.event_name ='".mysql_real_escape_string($_GET['shortname'])."'
								GROUP BY DATE( when_sent ) , HOUR(when_sent)
								ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	}
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	die(mysql_error());
	}

	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}

		while($row = $res->FetchRow());
		echo json_encode($count_source_date);
		echo json_encode($source_date);
		?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);
echo json_encode($source_date);
echo json_encode($count_source_date);
echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n";
echo "zoomType: 'x',\n";
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Hour for $shortname'\n" ;
echo "},\n" ;
echo "subtitle: {\n";
echo "text: document.ontouchstart === undefined ?\n";
echo "'Click and drag in the plot area to zoom in' :\n";
echo "'Drag your finger over the plot to zoom in'\n";
echo "},\n";
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %p',\n" ;
echo "minute: '%I:%M %p',\n" ;
echo "hour: '%I:%M %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n";
echo "title: {\n";
echo "allowDecimals: false,\n";
echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "enabled: false\n";
echo "},\n";
echo "plotOptions: {\n";
echo "area: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,0,0,0)']\n";
echo "]\n";
echo "},\n";

echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "series: [{\n" ;
echo "name: '". $shortname;
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data\n" ;

echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;
echo "</script>\n" ;
}
/********************************************
 * Arrival Rate by Minute
* For sendai2011, hepl, christchurch, turkey
*********************************************/
function shn_stat_arrival_byminute() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];

	//for sendai2011, add 'a.source_date >'2011-01-01'' in the where filter

	if($shortname=="sendai2011") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
							join person_uuid b ON a.p_uuid= b.p_uuid
							join incident c ON c.incident_id= b.incident_id
							where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-01-01')
							GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date), MINUTE(source_date)";
	}
	//for hepl
	if($shortname=="hepl") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
							join person_uuid b ON a.p_uuid= b.p_uuid
							join incident c ON c.incident_id= b.incident_id
							where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2010-01-11')
			GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date),MINUTE(source_date)";
	}
	//for christchurch
	if($shortname=="christchurch") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			join incident c ON c.incident_id= b.incident_id
			where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-02-20')
 		GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date),MINUTE(source_date)";
	}
	//for turkey
	if($shortname=="turkey2011") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			join incident c ON c.incident_id= b.incident_id
			where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date >'2011-10-23')
				GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date),MINUTE(source_date)";
	}
	//for CMAX2010, cannot filter by incidentid for cmax2010
	if($shortname=="cmax2010") {
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
								JOIN edxl_co_header b ON b.de_id = a.de_id
								JOIN edxl_co_lpf c ON c.co_id = b.co_id
								GROUP BY DATE( when_sent ) , HOUR(when_sent),MINUTE(when_sent)
								ORDER BY DATE( when_sent ) , HOUR(when_sent),MINUTE(when_sent)";
	}
	//for new
	if($shortname=="new"){
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
								JOIN edxl_co_header b ON b.de_id = a.de_id
								JOIN edxl_co_lpf c ON c.co_id = b.co_id
								WHERE (c.event_name ='".mysql_real_escape_string($_GET['shortname'])."' and a.source_date like '2011-10-19%')
						GROUP BY DATE( when_sent ) , HOUR(when_sent), MINUTE(when_sent)
						ORDER BY DATE( when_sent ) , HOUR(when_sent), MINUTE(when_sent)";
	}
	//for testtp or test
	if(($shortname=="testtp") || ($shortname=="test")){
	$q="SELECT when_sent as source_date, count(when_sent) as count_source_date FROM `edxl_de_header` a
						JOIN edxl_co_header b ON b.de_id = a.de_id
						JOIN edxl_co_lpf c ON c.co_id = b.co_id
						WHERE c.event_name ='".mysql_real_escape_string($_GET['shortname'])."'
			GROUP BY DATE( when_sent ) , HOUR(when_sent), MINUTE(when_sent)
			ORDER BY DATE( when_sent ) , HOUR(when_sent), MINUTE(when_sent)";
	}
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	die(mysql_error());
	}

	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}

		while($row = $res->FetchRow());
		echo json_encode($count_source_date);
		echo json_encode($source_date);
		?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);
echo json_encode($source_date);
echo json_encode($count_source_date);
echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "zoomType: 'x',\n";
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Minute for $shortname'\n" ;
echo "},\n" ;
echo "subtitle: {\n";
echo "text: document.ontouchstart === undefined ?\n";
echo "'Click and drag in the plot area to zoom in' :\n";
echo "'Drag your finger over the plot to zoom in'\n";
echo "},\n";
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %p',\n" ;
echo "minute: '%I:%M %p',\n" ;
echo "hour: '%I:%M %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n";
echo "title: {\n";
echo "allowDecimals: false,\n";
echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "enabled: false\n";
echo "},\n";
echo "plotOptions: {\n";
echo "area: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,0,0,0)']\n";
echo "]\n";
echo "},\n";

echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "series: [{\n" ;
echo "name: '". $shortname;
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data\n" ;

echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;
echo "</script>\n" ;
}
/** The expiry rate for JP
 *** @access public
 *** @return void
 */
function shn_stat_expiry_date() {
global $global;
shn_stat_menu();
echo "People Statistics for  ";
echo $_GET['shortname'];
$shortname = $_GET['shortname'];

$q="SELECT DATE( expiry_date ) AS expiry_date, count( p_uuid ) AS count_puuid
							FROM `person_uuid` a
							JOIN incident b ON a.incident_id = b.incident_id
							WHERE (
							b.shortname LIKE '".$shortname."'
							AND a.expiry_date IS NOT NULL
							AND a.expiry_date > '2011-10-31'
							AND a.expiry_date < '2011-11-31')
							GROUP BY DATE( expiry_date )
							ORDER BY expiry_date";

$res = $global['db']->Execute($q);

$row = $res->FetchRow();

if($row === FALSE) {
    	die(mysql_error());
	}
	$json_expiry_date = array();
	$json_count_puuid = array();
	do{
		$expiry_date[] = (strtotime($row['expiry_date'])*1000);
		//date_default_timezone_set('UTC');
		array_push($json_expiry_date, $row['expiry_date']);
		$row['count_puuid'] = (int) $row['count_puuid'];
		$count_puuid[] = $row['count_puuid'];
		array_push($json_count_puuid, $row['count_puuid']);
		}
		while($row = $res->FetchRow());
		echo json_encode($expiry_date);
		echo json_encode($count_puuid);

		//<div id="container" style="width: 500 px; height: 300px; margin: 0 auto; background-image:url('ajax-loader2.gif');background-repeat:no-repeat;"></div>
		?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
$json_count_puuid = implode("','",$json_count_puuid);
$json_count_expiry_date = implode(",", $json_expiry_date);
echo $json_count_puuid;
echo $json_expiry_date;
echo "<script type=\"text/javascript\"> \n" ;
echo "\$(document).ready(function() {\n" ;

echo "var points = [$json_count_puuid],\n";
echo "dates = .json_encode($expiry_date)";
echo ",\n";
echo "\n";
echo "i, data = [], chart;\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "$(document).ready(function() {\n";
echo "chart = new Highcharts.Chart({\n";
echo "chart: {\n";
echo "renderTo: 'content'\n";
echo "zoomType: 'x'\n";
echo "},\n";
echo "title: {\n";
echo "text: 'PL Expiry Date Count for Japan Earthquake and Tsunami in 2011'\n";
echo "},\n";
echo "xAxis: {\n";
echo "type: 'datetime',\n";
echo "dateTimeLabelFormats: {\n";
echo "second: '%e. %b %H %M %S',\n";
echo "minute: '%e. %b %H %M',\n";
echo "hour: '%e. %b %H',\n";
echo "day: '%e. %b',\n";
echo "week: '%e. %b',\n";
echo "month: '%b \'%y',\n";
echo "year: '%Y'\n";
echo "},\n";
echo "maxZoom: 24 * 3600 * 1000\n";
echo "},\n";
echo "yAxis: {\n";
echo "title: {\n";
echo "allowDecimals: false,\n";
echo "text: 'Expiry Date Count'\n";
echo "}\n";
echo "},\n";
echo "tooltip: {\n";
echo "enabled: false,\n";
echo "formatter: function() {\n";
echo "return '<b>'+ this.series.name +'</b><br/>'+\n";
echo "this.x +': '+ this.y;\n";
echo "}\n";
echo "},\n";
echo "plotOptions: {\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "},\n";
echo "enableMouseTracking: false\n";
echo "}\n";
echo "},\n";
echo "series: [{\n";
echo "name: 'Japan Earthquake and Tsunami',\n";
echo "type: 'line',\n";
echo "data: data,\n";
echo "pointInterval: 24 * 3600\n";
echo "]";
echo "});\n";
echo "});\n";
}

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
}
/**
 * the test action!
 * @access public
 * @return void
 */


function shn_stat_TP_sub_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	//old table
	//$q="SELECT update_time, count(update_time) as count_update_time
	//FROM `mpres_log` where email_subject like 'New Disaster Patient%Sub%'
	//GROUP BY DATE(update_time), HOUR(update_time) order by DATE(update_time), HOUR(update_time)";
	if ($shortname=="new") {
		$q="SELECT when_sent as update_time, count(when_sent) as count_update_time FROM `edxl_de_header` a
							JOIN edxl_co_header b ON b.de_id = a.de_id
							JOIN edxl_co_lpf c ON c.co_id = b.co_id
							WHERE (c.event_name like ='".mysql_real_escape_string($_GET['shortname'])."' and when_sent > '2011-10-19%')
							GROUP BY DATE( when_sent ) , HOUR(when_sent)
							ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	}
	else {
	$q="SELECT when_sent as update_time, count(when_sent) as count_update_time FROM `edxl_de_header` a
							JOIN edxl_co_header b ON b.de_id = a.de_id
							JOIN edxl_co_lpf c ON c.co_id = b.co_id
							WHERE c.event_name ='".mysql_real_escape_string($_GET['shortname'])."'
							GROUP BY DATE( when_sent ) , HOUR(when_sent)
							ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	}

	$res = $global['db']->Execute($q);

	$row = $res->FetchRow();

	if($row === FALSE) {
    	die(mysql_error());
	}
	$json_update_time = array();
	$json_count_update_time = array();
	do{
		$update_time[] = (strtotime($row['update_time'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_update_time, $row['update_time']);
		$count_update_time[] = $row['count_update_time'];
		array_push($json_count_update_time, $row['count_update_time']);
		}
		while($row = $res->FetchRow());
		echo json_encode($count_update_time);
		echo json_encode($update_time);
		?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_update_time = implode("','",$json_update_time);
$json_count_update_time = implode(",", $json_count_update_time);
echo json_encode($update_time);
echo json_encode($count_update_time);
echo "\n";
echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_update_time],\n";
echo "dates = " .json_encode($update_time);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";
echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'areaspline'\n";
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Hour for $shortname'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I: %M %p',\n" ;
echo "minute: '%I: %M %p',\n" ;
echo "hour: '%I: %M %p',\n" ;
echo "day: '%e. %b',\n" ;
echo "week: '%e. %b',\n" ;
echo "month: '%b \'%y',\n" ;
echo "year: '%Y'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";
echo "title: {\n" ;
echo "text: 'People Count'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "tooltip: {\n";
echo "formatter: function() {\n";
echo "return '<strong>'+ this.series.name +'</strong>'+\n";
echo "Highcharts.dateFormat('%e. %b %Y, %H: %M: %S', this.x) +': '+ this.y +' people';\n";
echo "}\n";
echo "},\n";
echo "plotOptions: {\n" ;
echo "area: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true\n" ;
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;
echo "},\n" ;
echo "series: [{\n" ;
echo "name: '". $shortname;
echo "',\n";
echo "type: 'areaspline',\n" ;
echo "data: data\n" ;
echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;
echo "</script>\n" ;
}


/***************************************
 * TP_sub_stacked_status_byhour function
***************************************/
function shn_stat_TP_sub_stacked_status_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);

	$queryR="SELECT count( triage_category ) AS count_statusR, '9-10 am' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '9'AND '9')
				UNION
				SELECT count( triage_category ) AS count_statusR, '10-11 am' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '10'AND '10')
				UNION
				SELECT count( triage_category ) AS count_statusR, '11-12 am' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '11'AND '11')
				UNION
				SELECT count( triage_category ) AS count_statusR, '12-1 pm' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '12'AND '12')
				UNION
				SELECT count( triage_category ) AS count_statusR, '1-2 pm' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '1'AND '1')
				UNION
				SELECT count( triage_category ) AS count_statusR, '2-3 pm' AS time_rangeR
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '2'AND '2')";



	$rR=mysql_query($queryR);
	$rowR = mysql_fetch_array($rR);
	//check result
	if($rowR === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeR = array();
	$json_count_statusR = array();
	do{
		$time_rangeR[] = $rowR['time_rangeR'];
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeR, $rowR['time_rangeR']);
		$row['count_statusR'] = (int) $rowR['count_statusR'];
		$count_statusR[] = $row['count_statusR'];
		array_push($json_count_statusR, $row['count_statusR']);
	}
	while($rowR = mysql_fetch_array($rR));
	echo 'red';
	//echo json_encode($count_statusR);
	//echo json_encode($time_rangeR);

	//green

	$queryG="SELECT count( triage_category ) AS count_statusG, '9-10 am' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '9'AND '9')
			UNION
			SELECT count( triage_category ) AS count_statusG, '10-11 am' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '10'AND '10')
			UNION
			SELECT count( triage_category ) AS count_statusG, '11-12 am' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '11'AND '11')
			UNION
			SELECT count( triage_category ) AS count_statusG, '12-1 pm' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '12'AND '12')
			UNION
			SELECT count( triage_category ) AS count_statusG, '1-2 pm' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '1'AND '1')
			UNION
			SELECT count( triage_category ) AS count_statusG, '2-3 pm' AS time_rangeG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '2'AND '2')";


	$rG=mysql_query($queryG);
	$rowG = mysql_fetch_array($rG);
	//check result
	if($rowG === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeG = array();
	$json_count_statusG = array();
	do{
		$time_rangeG[] = $rowG['time_rangeG'];
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeG, $rowG['time_rangeG']);
		$row['count_statusG'] = (int) $rowG['count_statusG'];
		$count_statusG[] = $row['count_statusG'];
		array_push($json_count_statusG, $row['count_statusG']);
	}
	while($rowG = mysql_fetch_array($rG));
	echo 'green';
	//echo json_encode($count_statusG);
	//echo json_encode($time_rangeG);

	//BH green

	$queryBHG="SELECT count( triage_category ) AS count_statusBHG, '9-10 am' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '9'AND '9')
			UNION
			SELECT count( triage_category ) AS count_statusBHG, '10-11 am' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '10'AND '10')
			UNION
			SELECT count( triage_category ) AS count_statusBHR, '11-12 am' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '11'AND '11')
			UNION
			SELECT count( triage_category ) AS count_statusBHR, '12-1 pm' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '12'AND '12')
			UNION
			SELECT count( triage_category ) AS count_statusBHR, '1-2 pm' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '1'AND '1')
			UNION
			SELECT count( triage_category ) AS count_statusBHR, '2-3 pm' AS time_rangeBHG
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'BH Green' AND HOUR( when_sent ) BETWEEN '2'AND '2')";


	$rBHG=mysql_query($queryBHG);
	$rowBHG = mysql_fetch_array($rBHG);
	//check result
	if($rowBHG === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeBHG = array();
	$json_count_statusBHG = array();
	do{
		$time_rangeBHG[] = $rowBHG['time_rangeBHG'];
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeBHG, $rowBHG['time_rangeBHG']);
		$row['count_statusBHG'] = (int) $rowBHG['count_statusBHG'];
		$count_statusBHG[] = $row['count_statusBHG'];
		array_push($json_count_statusBHG, $row['count_statusBHG']);
	}
	while($rowBHG = mysql_fetch_array($rBHG));
	echo 'BH green';
	echo json_encode($count_statusBHG);
	echo json_encode($time_rangeBHG);

	//yellow

	$queryY="SELECT count( triage_category ) AS count_statusY, '9-10 am' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '9'AND '9')
			UNION
			SELECT count( triage_category ) AS count_statusY, '10-11 am' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '10'AND '10')
			UNION
			SELECT count( triage_category ) AS count_statusY, '11-12 am' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '11'AND '11')
			UNION
			SELECT count( triage_category ) AS count_statusY, '12-1 pm' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '12'AND '12')
			UNION
			SELECT count( triage_category ) AS count_statusY, '1-2 pm' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '1'AND '1')
			UNION
			SELECT count( triage_category ) AS count_statusY, '2-3 pm' AS time_rangeY
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '2'AND '2')";


	$rY=mysql_query($queryY);
	$rowY = mysql_fetch_array($rY);

	if($rowY === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeY = array();
	$json_count_statusY = array();
	do{
		$time_rangeY[] = $rowY['time_rangeY'];
		date_default_timezone_set('UTC');
		array_push($json_time_rangeY, $rowY['time_rangeY']);
		$row['count_statusY'] = (int) $rowY['count_statusY'];
		$count_statusY[] = $row['count_statusY'];
		array_push($json_count_statusY, $row['count_statusY']);
	}
	while($rowY = mysql_fetch_array($rY));

	echo 'yellow';
	echo json_encode($count_statusY);
	echo json_encode($time_rangeY);

	//gray

	$queryGr="SELECT count( triage_category ) AS count_statusGr, '9-10 am' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '9'AND '9')
 				UNION
 				SELECT count( triage_category ) AS count_statusGr, '10-11 am' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '10'AND '10')
 				UNION
 				SELECT count( triage_category ) AS count_statusGr, '11-12 am' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '11'AND '11')
 				UNION
 				SELECT count( triage_category ) AS count_statusGr, '12-1 pm' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '12'AND '12')
 				UNION
 				SELECT count( triage_category ) AS count_statusGr, '1-2 pm' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '1'AND '1')
 				UNION
 				SELECT count( triage_category ) AS count_statusGr, '2-3 pm' AS time_rangeGr
 				FROM `edxl_co_lpf` a
 				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
 				WHERE (triage_category = 'Gray' AND HOUR( when_sent ) BETWEEN '2'AND '2')";


	$rGr=mysql_query($queryGr);
	$rowGr = mysql_fetch_array($rGr);

	if($rowGr === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeGr = array();
	$json_count_statusGr = array();
	do{
		$time_rangeGr[] = $rowGr['time_rangeGr'];
		date_default_timezone_set('UTC');
		array_push($json_time_rangeGr, $rowGr['time_rangeGr']);
		$row['count_statusGr'] = (int) $rowGr['count_statusGr'];
		$count_statusGr[] = $row['count_statusGr'];
		array_push($json_count_statusGr, $row['count_statusGr']);
	}
	while($rowGr = mysql_fetch_array($rGr));

	//black

	$queryB="SELECT count( triage_category ) AS count_statusB, '9-10 am' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '10'AND '10')
		UNION
		SELECT count( triage_category ) AS count_statusB, '10-11 am' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '10'AND '10')
		UNION
		SELECT count( triage_category ) AS count_statusB, '11-12 am' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '11'AND '11')
		UNION
		SELECT count( triage_category ) AS count_statusB, '12-1 pm' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '12'AND '12')
		UNION
		SELECT count( triage_category ) AS count_statusB, '1-2 pm' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '1'AND '1')
		UNION
		SELECT count( triage_category ) AS count_statusB, '2-3 pm' AS time_rangeB
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Black' AND HOUR( when_sent ) BETWEEN '2'AND '2')";


	$rB=mysql_query($queryB);
	$rowB = mysql_fetch_array($rB);

	if($rowB === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeB = array();
	$json_count_statusB = array();
	do{
		$time_rangeB[] = $rowB['time_rangeB'];
		date_default_timezone_set('UTC');
		array_push($json_time_rangeB, $rowB['time_rangeB']);
		$row['count_statusB'] = (int) $rowB['count_statusB'];
		$count_statusB[] = $row['count_statusB'];
		array_push($json_count_statusB, $row['count_statusB']);
	}
	while($rowB = mysql_fetch_array($rB));

	echo 'black';
	echo json_encode($count_statusB);
	echo json_encode($time_rangeB);
	?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
//to do
$json_time_rangeR = implode("','",$json_time_rangeR);
$json_count_statusR = implode(",", $json_count_statusR);

$json_time_rangeG = implode("','",$json_time_rangeG);
$json_count_statusG = implode(",", $json_count_statusG);

$json_time_rangeY = implode("','",$json_time_rangeY);
$json_count_statusY = implode(",", $json_count_statusY);

$json_time_rangeBHG = implode("','",$json_time_rangeBHG);
$json_count_statusBHG = implode(",", $json_count_statusBHG);

$json_time_rangeGr = implode("','",$json_time_rangeGr);
$json_count_statusGr = implode(",", $json_count_statusGr);

$json_time_rangeB = implode("','",$json_time_rangeB);
$json_count_statusB = implode(",", $json_count_statusB);

echo "<script type=\"text/javascript\"> \n" ;
//Red
echo "var pointsR = [$json_count_statusR],\n" ;
echo "datesR = " .json_encode($time_rangeR);
echo ",\n" ;
echo "i, dataR = [], chart;\n" ;
echo "for(i=0; i<pointsR.length; i++) {\n" ;
echo "dataR.push([datesR[i], pointsR[i]]);\n" ;
echo"}\n";
//green
echo "var pointsG = [$json_count_statusG],\n";
echo "datesG = ".json_encode($time_rangeG);
echo ",\n" ;
echo "j, dataG = [], chart;\n" ;
echo "for(j=0; j<pointsG.length; j++) {\n" ;
echo "dataG.push([datesG[j], pointsG[j]]);\n" ;
echo"}\n" ;
//BH Green
echo "var pointsBHG = [$json_count_statusBHG],\n" ;
echo "datesBHG = ".json_encode($time_rangeBHG);
echo ",\n" ;
echo "l, dataBHG = [], chart;\n" ;
echo "for(l=0; l<pointsBHG.length; l++) {\n" ;
echo "dataBHG.push([datesBHG[l], pointsBHG[l]]);\n" ;
echo"}\n" ;
//Gray
echo "var pointsGr = [$json_count_statusGr],\n" ;
echo "datesGr= " .json_encode($time_rangeGr);
echo ",\n" ;
echo "m, dataGr = [], chart;\n" ;
echo "for(m=0; i<pointsGr.length; m++) {\n" ;
echo "dataGr.push([datesGr[m], pointsGr[m]]);\n" ;
echo"}\n";
//yellow
echo "var pointsY = [$json_count_statusY],\n";
echo "datesY = ".json_encode($time_rangeY);
echo ",\n" ;
echo "j, dataY = [], chart;\n" ;
echo "for(j=0; j<pointsY.length; j++) {\n" ;
echo "dataY.push([datesY[j], pointsY[j]]);\n" ;
echo"}\n" ;
//black
echo "var pointsB = [$json_count_statusB],\n" ;
echo "datesB = ".json_encode($time_rangeB);
echo ",\n" ;
echo "n, dataB = [], chart;\n" ;
echo "for(n=0; n<pointsB.length; n++) {\n" ;
echo "dataB.push([datesB[n], pointsB[n]]);\n" ;
echo"}\n" ;

echo "\$(document).ready(function() {\n";
echo "var chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'column'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'TriagePic Zone Status on Arrival for $name',\n" ;
echo "style: {\n" ;
echo "color: '#000000',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo " " ;
echo "style: {\n" ;
echo "color: '#FF00FF',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "title: {\n" ;
echo "text: 'Time Range'\n" ;
echo "},\n";
echo "maxPadding: 0.1,\n";
echo "categories: ['9-10 AM','10-11 AM','11-12 PM','12-1 PM','1-2 PM','2-3 PM']\n" ;
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";

echo "stackLabels: {\n";
echo "enabled: true,\n";
echo "style: {\n";
echo "fontWeight: 'bold',\n";
echo "color: (Highcharts.theme && Highcharts.theme.textColor) || 'black'\n";
echo "}\n";
echo "},\n";
echo "title: {\n" ;
echo "text: 'Patient Counts'\n" ;
echo "}\n" ;
echo "},\n" ;
echo"
							tooltip: {
							formatter: function() {
							return '<b>'+ this.x +'</b><br/>'+
							this.series.name +': '+ this.y +'<br/>'+
							'Total: '+ this.point.stackTotal;
         }
      },
							\n";
echo "plotOptions: {\n" ;
echo "column: {
			stacking: 'normal',
			dataLabels: {
			enabled: true,
			color: (Highcharts.theme && Highcharts.theme.dataLabelsColor) || 'black'
            }
         }
      },\n" ;
echo "series: [\n" ;

echo "{\n" ;
echo "name: 'Green Zone',\n" ;
echo "color:'#339900',\n" ;
echo "data: pointsG\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'BH Green Zone',\n" ;
echo "color:'#2EFE64',\n" ;
echo "data: pointsBHG\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Yellow Zone',\n" ;
echo "color: '#FFFF00',\n" ;
echo "data: pointsY\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Red Zone',\n" ;
echo "color:'#FF0000',\n" ;
echo "data: pointsR\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Gray Zone',\n" ;
echo "color:'#6E6E6E',\n" ;
echo "data: pointsGr\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Black Zone',\n" ;
echo "color: '#000000',\n" ;
echo "data: pointsB\n" ;
echo "}\n" ;
echo "]\n" ;
echo "});\n";
echo "});\n";
echo "</script>\n" ;
}

/***************************************
 * stacked_status_daily_regular_interval function
***************************************/
function shn_stat_stacked_status_daily_regular_interval() {

	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);

	$q = "
						SELECT *
						FROM incident
						WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
						";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	//start and end date
	$q_start_date="SELECT arrival_time from arrival_rate a
						where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));

	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
						where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	$queryR="SELECT b.arrival_time AS time_rangeR, count( triage_category ) AS count_statusR
				FROM `edxl_co_lpf` a
				LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
				WHERE (	triage_category = 'Red'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
			GROUP BY date( b.arrival_time )";


	$rR=mysql_query($queryR);
	$rowR = mysql_fetch_array($rR);
	//check result
	if($rowR === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeR = array();
	$json_count_statusR = array();
	do{
		//$time_rangeR[] = $rowR['time_rangeR'];
		//date_default_timezone_set('UTC');
		$time_rangeR[] = (strtotime($rowR['time_rangeR'])*1000);
		array_push($json_time_rangeR, $rowR['time_rangeR']);
		$row['count_statusR'] = (int) $rowR['count_statusR'];
		$count_statusR[] = $row['count_statusR'];
		array_push($json_count_statusR, $row['count_statusR']);
	}
	while($rowR = mysql_fetch_array($rR));
	echo 'red';

	//green
	$queryG="SELECT b.arrival_time AS time_rangeG, count( triage_category ) AS count_statusG
		FROM `edxl_co_lpf` a
		LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
		WHERE (	triage_category = 'Green'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
		GROUP BY date( b.arrival_time )";

	$rG=mysql_query($queryG);
	$rowG = mysql_fetch_array($rG);
	//check result
	if($rowG === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeG = array();
	$json_count_statusG = array();
	do{
		//$time_rangeG[] = $rowG['time_rangeG'];
		$time_rangeG[] = (strtotime($rowG['time_rangeG'])*1000);
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeG, $rowG['time_rangeG']);
		$row['count_statusG'] = (int) $rowG['count_statusG'];
		$count_statusG[] = $row['count_statusG'];
		array_push($json_count_statusG, $row['count_statusG']);
	}
	while($rowG = mysql_fetch_array($rG));
	echo 'green';

	//BH green
	$queryBHG="SELECT b.arrival_time AS time_rangeBHG, count( triage_category ) AS count_statusBHG
		FROM `edxl_co_lpf` a
		LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
		WHERE (	triage_category = 'BH Green'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
		GROUP BY date( b.arrival_time )";

	$rBHG=mysql_query($queryBHG);
	$rowBHG = mysql_fetch_array($rBHG);
	//check result
	if($rowBHG === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeBHG = array();
	$json_count_statusBHG = array();
	do{
		//$time_rangeBHG[] = $rowBHG['time_rangeBHG'];
		//date_default_timezone_set('UTC');
		$time_rangeBHG[] = (strtotime($rowBHG['time_rangeBHG'])*1000);
		array_push($json_time_rangeBHG, $rowBHG['time_rangeBHG']);
		$row['count_statusBHG'] = (int) $rowBHG['count_statusBHG'];
		$count_statusBHG[] = $row['count_statusBHG'];
		array_push($json_count_statusBHG, $row['count_statusBHG']);
	}
	while($rowBHG = mysql_fetch_array($rBHG));
	echo 'BH green';
	echo json_encode($count_statusBHG);
	echo json_encode($time_rangeBHG);


	//yellow
	$queryY="SELECT b.arrival_time AS time_rangeY, count( triage_category ) AS count_statusY
									FROM `edxl_co_lpf` a
									LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
									WHERE (	triage_category = 'Yellow'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
			GROUP BY date( b.arrival_time )";

	$rY=mysql_query($queryY);
	$rowY = mysql_fetch_array($rY);

	if($rowY === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeY = array();
	$json_count_statusY = array();
	do{
		//$time_rangeY[] = $rowY['time_rangeY'];
		$time_rangeY[] = (strtotime($rowY['time_rangeY'])*1000);
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeY, $rowY['time_rangeY']);
		$row['count_statusY'] = (int) $rowY['count_statusY'];
		$count_statusY[] = $row['count_statusY'];
		array_push($json_count_statusY, $row['count_statusY']);
	}
	while($rowY = mysql_fetch_array($rY));

	echo 'yellow';
	echo json_encode($count_statusY);
	echo json_encode($time_rangeY);


	//gray
	$queryGr="SELECT b.arrival_time AS time_rangeGr, count( triage_category ) AS count_statusGr
					FROM `edxl_co_lpf` a
					LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
					WHERE (	triage_category = 'Gray'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
 				GROUP BY date( b.arrival_time )";

	$rGr=mysql_query($queryGr);
	$rowGr = mysql_fetch_array($rGr);

	if($rowGr === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	$json_time_rangeGr = array();
	$json_count_statusGr = array();
	do{
		//$time_rangeGr[] = $rowGr['time_rangeGr'];
		//date_default_timezone_set('UTC');
		$time_rangeGr[] = (strtotime($rowGr['time_rangeGr'])*1000);
		array_push($json_time_rangeGr, $rowGr['time_rangeGr']);
		$row['count_statusGr'] = (int) $rowGr['count_statusGr'];
		$count_statusGr[] = $row['count_statusGr'];
		array_push($json_count_statusGr, $row['count_statusGr']);
	}
	while($rowGr = mysql_fetch_array($rGr));


	//black
	$queryB="SELECT b.arrival_time AS time_rangeB, count( triage_category ) AS count_statusB
			FROM `edxl_co_lpf` a
			LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
			WHERE (	triage_category = 'Black'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
										GROUP BY date( b.arrival_time )";

	$rB=mysql_query($queryB);
	$rowB = mysql_fetch_array($rB);

	if($rowB === FALSE) {
    	//die(mysql_error()); // TODO: better error handling

	}
	$json_time_rangeB = array();
	$json_count_statusB = array();
	do{
		//$time_rangeB[] = $rowB['time_rangeB'];
		//date_default_timezone_set('UTC');
		$time_rangeB[] = (strtotime($rowB['time_rangeB'])*1000);
		array_push($json_time_rangeB, $rowB['time_rangeB']);
		$row['count_statusB'] = (int) $rowB['count_statusB'];
		$count_statusB[] = $row['count_statusB'];
		array_push($json_count_statusB, $row['count_statusB']);
	}
	while($rowB = mysql_fetch_array($rB));

	echo 'black';
	echo json_encode($count_statusB);
	echo json_encode($time_rangeB);
	?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
//to do
$json_time_rangeR = implode("','",$json_time_rangeR);
$json_count_statusR = implode(",", $json_count_statusR);

$json_time_rangeG = implode("','",$json_time_rangeG);
$json_count_statusG = implode(",", $json_count_statusG);

$json_time_rangeY = implode("','",$json_time_rangeY);
$json_count_statusY = implode(",", $json_count_statusY);

$json_time_rangeBHG = implode("','",$json_time_rangeBHG);
$json_count_statusBHG = implode(",", $json_count_statusBHG);

$json_time_rangeGr = implode("','",$json_time_rangeGr);
$json_count_statusGr = implode(",", $json_count_statusGr);

$json_time_rangeB = implode("','",$json_time_rangeB);
$json_count_statusB = implode(",", $json_count_statusB);

echo "<script type=\"text/javascript\"> \n" ;
/*
 //Red
echo "var pointsR = [$json_count_statusR],\n" ;
echo "datesR = " .json_encode($time_rangeR);
echo ",\n" ;
echo "i, dataR = [], chart;\n" ;
echo "for(i=0; i<pointsR.length; i++) {\n" ;
			echo "dataR.push([datesR[i], pointsR[i]]);\n" ;
echo"}\n";
//green
echo "var pointsG = [$json_count_statusG],\n";
echo "datesG = ".json_encode($time_rangeG);
echo ",\n" ;
echo "j, dataG = [], chart;\n" ;
echo "for(j=0; j<pointsG.length; j++) {\n" ;
			echo "dataG.push([datesG[j], pointsG[j]]);\n" ;
echo"}\n" ;
//BH Green
echo "var pointsBHG = [$json_count_statusBHG],\n" ;
echo "datesBHG = ".json_encode($time_rangeBHG);
echo ",\n" ;
echo "l, dataBHG = [], chart;\n" ;
echo "for(l=0; l<pointsBHG.length; l++) {\n" ;
			echo "dataBHG.push([datesBHG[l], pointsBHG[l]]);\n" ;
echo"}\n" ;
//Gray
echo "var pointsGr = [$json_count_statusGr],\n" ;
echo "datesGr= " .json_encode($time_rangeGr);
echo ",\n" ;
echo "m, dataGr = [], chart;\n" ;
echo "for(m=0; i<pointsGr.length; m++) {\n" ;
			echo "dataGr.push([datesGr[m], pointsGr[m]]);\n" ;
echo"}\n";
//yellow
echo "var pointsY = [$json_count_statusY],\n";
echo "datesY = ".json_encode($time_rangeY);
echo ",\n" ;
echo "j, dataY = [], chart;\n" ;
echo "for(j=0; j<pointsY.length; j++) {\n" ;
			echo "dataY.push([datesY[j], pointsY[j]]);\n" ;
echo"}\n" ;
//black
echo "var pointsB = [$json_count_statusB],\n" ;
echo "datesB = ".json_encode($time_rangeB);
echo ",\n" ;
echo "n, dataB = [], chart;\n" ;
echo "for(n=0; n<pointsB.length; n++) {\n" ;
			echo "dataB.push([datesB[n], pointsB[n]]);\n" ;
echo"}\n" ;
*/

echo "\$(document).ready(function() {\n";
echo "var chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'column'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'TriagePic Zone Status on Arrival $description',\n" ;
echo "style: {\n" ;
echo "color: '#000000',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
	
echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds',\n" ;
echo "style: {\n" ;
echo "color: '#FF00FF',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n";
echo "},\n";
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%e. %b',\n" ;
echo "minute: '%e. %b',\n" ;
echo "hour: '%e. %b %I',\n" ;
echo "day: '%e. %b',\n" ;
echo "week: '%e. %b',\n" ;
echo "month: '%e. %b',\n" ;
echo "year: '%Y'\n" ;
echo "}\n" ;
echo "},\n" ;

echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";

echo "stackLabels: {\n";
echo "enabled: true,\n";
echo "style: {\n";
echo "fontWeight: 'bold',\n";
echo "color: (Highcharts.theme && Highcharts.theme.textColor) || 'black'\n";
echo "}\n";
echo "},\n";
echo "title: {\n" ;
echo "text: 'Patient Counts'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "
			tooltip: {
			formatter: function() {
			return '<b>'+ this.x +'</b><br/>'+
			this.series.name +': '+ this.y +'<br/>'+
			'Total: '+ this.point.stackTotal;
         }
      },
	  \n";
echo "plotOptions: {\n" ;
echo "column: {
			stacking: 'normal',
			dataLabels: {
			enabled: true,
			color: (Highcharts.theme && Highcharts.theme.dataLabelsColor) || 'black'
            },
			//fixed point start
			pointStart: Date.UTC(2011, 10, 1),
			pointInterval: 150* 24 * 3600 * 1000 // 150 days
         	}
           },\n" ;
echo "series: [\n" ;

echo "{\n" ;
echo "name: 'Green Zone',\n" ;
echo "color:'#339900',\n" ;
echo "data: pointsG\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'BH Green Zone',\n" ;
echo "color:'#2EFE64',\n" ;
echo "data: pointsBHG\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Yellow Zone',\n" ;
echo "color: '#FFFF00',\n" ;
echo "data: pointsY\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Red Zone',\n" ;
echo "color:'#FF0000',\n" ;
echo "data: pointsR\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Gray Zone',\n" ;
echo "color:'#6E6E6E',\n" ;
echo "data: pointsGr\n" ;
echo "},\n" ;
echo "{\n" ;
echo "name: 'Black Zone',\n" ;
echo "color: '#000000',\n" ;
echo "data: pointsB\n" ;
echo "}\n" ;
echo "]\n" ;
echo "});\n";
echo "});\n";
echo "</script>\n" ;
}
/*************************************************
 * stacked_status_daily_irregular_interval function
*************************************************/
function shn_stat_stacked_status_daily_irregular_interval() {

	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);

	$q = "
				SELECT *
				FROM incident
				WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
						";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	//start and end date
	$q_start_date="SELECT arrival_time from arrival_rate a
						where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);

	if($res != NULL && !$res->EOF) {
		$row = $res->FetchRow();
		$start_date= $row[0];
		$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	} else {
	  $start_date = "";
	}

	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
				where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	if($res != NULL && !$res->EOF) {
		$row = $res->FetchRow();
		$end_date= $row[0];
		$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));
	} else {
	  $end_date = "";
	}

	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){
	$queryR="SELECT date(b.arrival_time) AS time_rangeR, count( triage_category ) AS count_statusR
		FROM `edxl_co_lpf` a
		LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
		WHERE (	triage_category = 'Red'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
		GROUP BY date( b.arrival_time ), HOUR( b.arrival_time )
		ORDER BY date( b.arrival_time ), HOUR( b.arrival_time )";
	}
	else {
	$queryR="SELECT count( triage_category ) AS count_statusR, HOUR(when_sent) AS time_rangeR
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Red' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
		group by DATE(when_sent),HOUR(when_sent)
		order by DATE(when_sent),HOUR(when_sent)";
	}

	$res = $global['db']->Execute($queryR);
	if($res != NULL && !$res->EOF) {
		$rR=mysql_query($queryR);
	  
		$rowR = mysql_fetch_array($rR);
	} else {
	  $rowR = "";
	}


	$json_time_rangeR = array();
	$json_count_statusR = array();
	do{
		//$time_rangeR[] = $rowR['time_rangeR'];

		$time_rangeR[] = (strtotime($rowR['time_rangeR'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_time_rangeR, $rowR['time_rangeR']);
		$row['count_statusR'] = (int) $rowR['count_statusR'];
		$count_statusR[] = $row['count_statusR'];
		array_push($json_count_statusR, $row['count_statusR']);
	}
	while($rowR = mysql_fetch_array($rR));
	echo 'red';

	//green
	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){
	$queryG="SELECT date(b.arrival_time) AS time_rangeG, count( triage_category ) AS count_statusG
		FROM `edxl_co_lpf` a
		LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
		WHERE (	triage_category = 'Green'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
			GROUP BY date( b.arrival_time ),HOUR( b.arrival_time )
			ORDER BY date( b.arrival_time ),HOUR( b.arrival_time )";
	}
	else {
	$queryG="SELECT count( triage_category ) AS count_statusG, HOUR(when_sent) AS time_rangeG
						FROM `edxl_co_lpf` a
						LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
						WHERE (triage_category = 'Green' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
							group by DATE(when_sent), HOUR(when_sent)
							ORDER BY DATE(when_sent), HOUR(when_sent)";
	}
	$res = $global['db']->Execute($queryG);
	if($res != NULL && !$res->EOF) {
		$rG=mysql_query($queryG);
		$rowG = mysql_fetch_array($rG);
	} else {
	  $rowG = "";
	}
	$json_time_rangeG = array();
	$json_count_statusG = array();
	do{
		//$time_rangeG[] = $rowG['time_rangeG'];
		$time_rangeG[] = (strtotime($rowG['time_rangeG'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_time_rangeG, $rowG['time_rangeG']);
		$row['count_statusG'] = (int) $rowG['count_statusG'];
		$count_statusG[] = $row['count_statusG'];
		array_push($json_count_statusG, $row['count_statusG']);
	}
	while($rowG = mysql_fetch_array($rG));
	echo 'green';

	//BH green
	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){
	$queryBHG="SELECT date(b.arrival_time) AS time_rangeBHG, count( triage_category ) AS count_statusBHG
									FROM `edxl_co_lpf` a
									LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
									WHERE (	triage_category = 'BH Green' AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
					GROUP BY date( b.arrival_time )
					ORDER BY date( b.arrival_time )";
	}
	else {
	$queryBHG="SELECT count( triage_category ) AS count_statusBHG, HOUR(when_sent) AS time_rangeBHG
					FROM `edxl_co_lpf` a
					LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
					WHERE (triage_category = 'BH Green' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
 				group by DATE(when_sent),HOUR(when_sent)
 				order by DATE(when_sent),HOUR(when_sent)";
	}
	$res = $global['db']->Execute($queryBHG);
	if($res != NULL && !$res->EOF) {
		$rBHG=mysql_query($queryBHG);
		$rowBHG = mysql_fetch_array($rBHG);
	}
	else {
	  $rowBHG = "";
	}

	$json_time_rangeBHG = array();
	$json_count_statusBHG = array();
	do{
		//$time_rangeBHG[] = $rowBHG['time_rangeBHG'];
		date_default_timezone_set('UTC');
		$time_rangeBHG[] = (strtotime($rowBHG['time_rangeBHG'])*1000);
		array_push($json_time_rangeBHG, $rowBHG['time_rangeBHG']);
		$row['count_statusBHG'] = (int) $rowBHG['count_statusBHG'];
		$count_statusBHG[] = $row['count_statusBHG'];
		array_push($json_count_statusBHG, $row['count_statusBHG']);
	}
	while($rowBHG = mysql_fetch_array($rBHG));
	echo 'BH green';
	echo json_encode($count_statusBHG);
	echo json_encode($time_rangeBHG);


	//yellow
	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){
	$queryY="SELECT date(b.arrival_time) AS time_rangeY, count( triage_category ) AS count_statusY
			FROM `edxl_co_lpf` a
			LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
			WHERE (	triage_category = 'Yellow'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
				GROUP BY date( b.arrival_time ),hour( b.arrival_time )
				ORDER BY date( b.arrival_time ),hour( b.arrival_time )";
    }
    else {
	$queryY="SELECT count( triage_category ) AS count_statusY, HOUR(when_sent) AS time_rangeY
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				WHERE (triage_category = 'Yellow' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
		group by date(when_sent),HOUR(when_sent)
		order by date(when_sent),HOUR(when_sent)";
	}
	$res = $global['db']->Execute($queryY);
	if($res != NULL && !$res->EOF) {
		$rY=mysql_query($queryY);
		$rowY = mysql_fetch_array($rY);
	}
	else {
	  $rowY = "";
	}
	$json_time_rangeY = array();
	$json_count_statusY = array();
	do{
		//$time_rangeY[] = $rowY['time_rangeY'];
		$time_rangeY[] = (strtotime($rowY['time_rangeY'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_time_rangeY, $rowY['time_rangeY']);
		$row['count_statusY'] = (int) $rowY['count_statusY'];
		$count_statusY[] = $row['count_statusY'];
		array_push($json_count_statusY, $row['count_statusY']);
	}
	while($rowY = mysql_fetch_array($rY));

	echo 'yellow';
	echo json_encode($count_statusY);
	echo json_encode($time_rangeY);


	//gray
	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){

	$queryGr="SELECT date(b.arrival_time) AS time_rangeGr, count( triage_category ) AS count_statusGr
		FROM `edxl_co_lpf` a
		LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
		WHERE (	triage_category = 'Gray'	AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
		GROUP BY date( b.arrival_time ),hour(( b.arrival_time )
		ORDER BY date( b.arrival_time ), hour( b.arrival_time )";
	}
	else {
	$queryGr="SELECT count( triage_category ) AS count_statusGr, HOUR(when_sent) AS time_rangeGr
		FROM `edxl_co_lpf` a
		LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
		WHERE (triage_category = 'Gray' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
		group by date(when_sent),HOUR(when_sent)
		order by date(when_sent),HOUR(when_sent)";
	}
	$res = $global['db']->Execute($queryGr);
	if($res != NULL && !$res->EOF) {
		$rGr=mysql_query($queryGr);
		$rowGr = mysql_fetch_array($rGr);
	}
	else {
	  $rowGr = "";
	}

	$json_time_rangeGr = array();
	$json_count_statusGr = array();
	do{
		//$time_rangeGr[] = $rowGr['time_rangeGr'];
		//date_default_timezone_set('UTC');
		$time_rangeGr[] = (strtotime($rowGr['time_rangeGr'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_time_rangeGr, $rowGr['time_rangeGr']);
		$row['count_statusGr'] = (int) $rowGr['count_statusGr'];
		$count_statusGr[] = $row['count_statusGr'];
		array_push($json_count_statusGr, $row['count_statusGr']);
	}
	while($rowGr = mysql_fetch_array($rGr));


	//black
	if ($shortname=='test' or $shortname=='testtp' or 'testind' or $shortname=='testindmon' or $shortname=='testintues' or $shortname=='testindwed'){

	$queryB="SELECT date(b.arrival_time) AS time_rangeB, count( triage_category ) AS count_statusB
			FROM `edxl_co_lpf` a
			LEFT JOIN arrival_rate b ON ( a.p_uuid = b.person_uuid )
			WHERE (	triage_category = 'Black' AND b.arrival_time IS NOT NULL and event_name='".mysql_real_escape_string($_GET['shortname'])."')
									GROUP BY date( b.arrival_time ), hour( b.arrival_time )
									ORDER BY date( b.arrival_time ), hour( b.arrival_time )";
    }
    //$rB=mysql_query($queryB);
    //$rowB = mysql_fetch_array($rB);

    //if($rowB === FALSE) {
    ////die(mysql_error()); // TODO: better error handling

    //}
    else {
    	$queryB="SELECT count( triage_category ) AS count_statusB, HOUR(when_sent) AS time_rangeB
			FROM `edxl_co_lpf` a
			LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
			WHERE (triage_category = 'Black' and a.event_name='".mysql_real_escape_string($_GET['shortname'])."')
									group by date(when_sent),HOUR(when_sent)
									order by date(when_sent),HOUR(when_sent)";
    }
    $res = $global['db']->Execute($queryB);
    if($res != NULL && !$res->EOF) {
		$rB=mysql_query($queryB);
		$rowB = mysql_fetch_array($rB);
	}
	else {
	  $rowB = "";
	}
	$json_time_rangeB = array();
	$json_count_statusB = array();
	do{
		//$time_rangeB[] = $rowB['time_rangeB'];
		//date_default_timezone_set('UTC');
		$time_rangeB[] = (strtotime($rowB['time_rangeB'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_time_rangeB, $rowB['time_rangeB']);
		$row['count_statusB'] = (int) $rowB['count_statusB'];
		$count_statusB[] = $row['count_statusB'];
		array_push($json_count_statusB, $row['count_statusB']);
	}
	while($rowB = mysql_fetch_array($rB));

	echo 'black';
	echo json_encode($count_statusB);
	echo json_encode($time_rangeB);
	?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
//to do
$json_time_rangeR = implode("','",$json_time_rangeR);
$json_count_statusR = implode(",", $json_count_statusR);

$json_time_rangeG = implode("','",$json_time_rangeG);
$json_count_statusG = implode(",", $json_count_statusG);

$json_time_rangeY = implode("','",$json_time_rangeY);
$json_count_statusY = implode(",", $json_count_statusY);

$json_time_rangeBHG = implode("','",$json_time_rangeBHG);
$json_count_statusBHG = implode(",", $json_count_statusBHG);

$json_time_rangeGr = implode("','",$json_time_rangeGr);
$json_count_statusGr = implode(",", $json_count_statusGr);

$json_time_rangeB = implode("','",$json_time_rangeB);
$json_count_statusB = implode(",", $json_count_statusB);

echo "<script type=\"text/javascript\"> \n" ;
//Red
echo "var pointsR = [$json_count_statusR],\n" ;
echo "datesR = " .json_encode($time_rangeR);
echo ",\n" ;
echo "i, dataR = [], chart;\n" ;
echo "for(i=0; i<pointsR.length; i++) {\n" ;
echo "dataR.push([datesR[i], pointsR[i]]);\n" ;
echo"}\n";
//green
echo "var pointsG = [$json_count_statusG],\n";
echo "datesG = ".json_encode($time_rangeG);
echo ",\n" ;
echo "j, dataG = [], chart;\n" ;
echo "for(j=0; j<pointsG.length; j++) {\n" ;
echo "dataG.push([datesG[j], pointsG[j]]);\n" ;
echo"}\n" ;
//BH Green
echo "var pointsBHG = [$json_count_statusBHG],\n" ;
echo "datesBHG = ".json_encode($time_rangeBHG);
echo ",\n" ;
echo "l, dataBHG = [], chart;\n" ;
echo "for(l=0; l<pointsBHG.length; l++) {\n" ;
echo "dataBHG.push([datesBHG[l], pointsBHG[l]]);\n" ;
echo"}\n" ;
//Gray
echo "var pointsGr = [$json_count_statusGr],\n" ;
echo "datesGr= " .json_encode($time_rangeGr);
echo ",\n" ;
echo "m, dataGr = [], chart;\n" ;
echo "for(m=0; i<pointsGr.length; m++) {\n" ;
echo "dataGr.push([datesGr[m], pointsGr[m]]);\n" ;
echo"}\n";
//yellow
echo "var pointsY = [$json_count_statusY],\n";
echo "datesY = ".json_encode($time_rangeY);
echo ",\n" ;
echo "j, dataY = [], chart;\n" ;
echo "for(j=0; j<pointsY.length; j++) {\n" ;
echo "dataY.push([datesY[j], pointsY[j]]);\n" ;
echo"}\n" ;
//black
echo "var pointsB = [$json_count_statusB],\n" ;
echo "datesB = ".json_encode($time_rangeB);
echo ",\n" ;
echo "n, dataB = [], chart;\n" ;
echo "for(n=0; n<pointsB.length; n++) {\n" ;
echo "dataB.push([datesB[n], pointsB[n]]);\n" ;
echo"}\n" ;



echo "\$(document).ready(function() {\n";
echo "var chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'column'\n" ;
echo "},\n" ;

echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "text: 'TriagePic Zone Status on Arrival $description'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '20px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "y: 50,\n";
if ($startdate_has_data=true){
         echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
		 }
		 echo "},\n" ;
		 echo "xAxis: {\n" ;
		 echo "type: 'datetime',\n" ;
		 	
		 echo "dateTimeLabelFormats: {\n" ;
		 echo "second: '%I:%M %H %p',\n" ;
		 echo "minute: '%I:%M %H %p',\n" ;
		 echo "hour: '%I:%M %H %p',\n" ;
		 echo "day: '%b %e',\n" ;
		 echo "week: '%b %e',\n" ;
		 echo "month: '%b %e',\n" ;
		 echo "year: '%b %e'\n" ;
		 echo "}\n" ;
		 echo "},\n" ;
		 echo "yAxis: {\n" ;
		 echo "allowDecimals: false,\n";

		 echo "stackLabels: {\n";
		 echo "enabled: true,\n";
		 echo "style: {\n";
		 echo "fontWeight: 'bold',\n";
		 echo "color: (Highcharts.theme && Highcharts.theme.textColor) || 'black'\n";
		 echo "}\n";
		 echo "},\n";
		 echo "title: {\n" ;
		 echo "text: 'Patient Counts'\n" ;
			echo "}\n" ;
			echo "},\n" ;
			//echo "
			//tooltip: {

				//formatter: function() {
				//return '<b>'+ this.x +'</b><br/>'+
				//this.series.name +': '+ this.y +'<br/>'+
			//'Total: '+ this.point.stackTotal;
			//}
			//},
	  //\n";
	  echo "
 		tooltip: {
 		shared: true
	},
 		legend: {
 		column: {
 		align: 'right',
 		backgroundColor: '#FCFFC5',
 		enabled: true
	}
	},
 		\n";
	  echo "plotOptions: {\n" ;
	  echo "pointPadding: 0,\n";
	  echo "column: {
			stacking: 'normal',
			dataLabels: {
			enabled: true,
			color: (Highcharts.theme && Highcharts.theme.dataLabelsColor) || 'black'
            }
         	}
           },\n" ;
	  echo "series: [\n" ;

	  echo "{\n" ;
	  echo "name: 'Green Zone',\n" ;
			echo "color:'#339900',\n" ;
			echo "data: dataG\n" ;
			echo "},\n" ;
			echo "{\n" ;
			echo "name: 'BH Green Zone',\n" ;
			echo "color:'#2EFE64',\n" ;
			echo "data: dataBHG\n" ;
			echo "},\n" ;
			echo "{\n" ;
			echo "name: 'Yellow Zone',\n" ;
			echo "color: '#FFFF00',\n" ;
			echo "data: dataY\n" ;
			echo "},\n" ;
			echo "{\n" ;
			echo "name: 'Red Zone',\n" ;
			echo "color:'#FF0000',\n" ;
			echo "data: dataR\n" ;
			echo "},\n" ;
			echo "{\n" ;
			echo "name: 'Gray Zone',\n" ;
			echo "color:'#6E6E6E',\n" ;
			echo "data: dataGr\n" ;
			echo "},\n" ;
			echo "{\n" ;
			echo "name: 'Black Zone',\n" ;
			echo "color: '#000000',\n" ;
			echo "data: dataB\n" ;
			echo "}\n" ;
			echo "]\n" ;
			echo "});\n";
			echo "});\n";
			echo "</script>\n" ;
}

/***************************************
 * TP_stacked_status_byhour function
***************************************/
function shn_stat_TP_new_stacked_status_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);

	$query="SELECT distinct(triage_category), count( triage_category ) AS count_status, hour( when_sent ) AS time_range
				FROM `edxl_co_lpf` a
				LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id )
				GROUP BY triage_category, hour(when_sent)
				";

	$r=mysql_query($query);
	$row = mysql_fetch_array($r);
	//check result
	if($row === FALSE) {
    	//die(mysql_error()); // TODO: better error handling
	}
	if ($row['triage_category']=='Green'){
	$json_time_rangeG = array();
	$json_count_statusG = array();
	do{
		$time_rangeG[] = $row['time_range'];
		//date_default_timezone_set('UTC');
		array_push($json_time_rangeG, $row['time_range']);
		$row['count_status'] = (int) $row['count_status'];
		$count_statusG[] = $row['count_status'];
		array_push($json_count_statusG, $row['count_status']);
	}
	while($row = mysql_fetch_array($r));
	//echo 'red';
	echo json_encode($count_statusG);
	echo json_encode($time_rangeG);
	}

	?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$shortname = $_GET['shortname'];
//to do
$json_time_rangeG = implode("','",$json_time_rangeG);
$json_count_statusG = implode(",", $json_count_statusG);

echo "<script type=\"text/javascript\"> \n" ;
//all
echo "var pointsG = [$json_count_statusG],\n" ;
echo "datesG = " .json_encode($time_range);
echo ",\n" ;
echo "i, dataG = [], chart;\n" ;
echo "for(i=0; i<pointsG.length; i++) {\n" ;
echo "dataG.push([datesG[i], pointsG[i]]);\n" ;
echo"}\n";

echo "\$(document).ready(function() {\n";
echo "var chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'column'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'TriagePic Zone Status on Arrival for $name',\n" ;
echo "style: {\n" ;
echo "color: '#000000',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo " " ;
echo "style: {\n" ;
echo "color: '#FF00FF',\n" ;
echo "fontWeight: 'bold'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "title: {\n" ;
echo "text: 'Time Range'\n" ;
echo "},\n";
echo "maxPadding: 0.1,\n";
echo "categories: ['9-10 AM','10-11 AM','11-12 PM','12-1 PM','1-2 PM','2-3 PM']\n" ;
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";

echo "stackLabels: {\n";
echo "enabled: true,\n";
echo "style: {\n";
echo "fontWeight: 'bold',\n";
echo "color: (Highcharts.theme && Highcharts.theme.textColor) || 'black'\n";
echo "}\n";
echo "},\n";
echo "title: {\n" ;
echo "text: 'Patient Counts'\n" ;
echo "}\n" ;
echo "},\n" ;
echo"
					tooltip: {
					formatter: function() {
					return '<b>'+ this.x +'</b><br/>'+
					this.series.name +': '+ this.y +'<br/>'+
					'Total: '+ this.point.stackTotal;
         }
      },
					\n";
echo "plotOptions: {\n" ;
echo "column: {
					stacking: 'normal',
					dataLabels: {
					enabled: true,
					color: (Highcharts.theme && Highcharts.theme.dataLabelsColor) || 'black'
            }
         }
      },\n" ;
echo "series: [\n" ;

echo "{\n" ;
echo "name: 'Zone',\n" ;
echo "color:'#339900',\n" ;
echo "data: points\n" ;
echo "}\n" ;
echo "]\n" ;
echo "});\n";
echo "});\n";
echo "</script>\n" ;
}


/***************************************
 * display random stats
* for CMAX2010 event
***************************************/
/*
 function shn_stat_TP_random() {
	global $global;
shn_stat_menu();
echo "People Statistics for  ";
echo $_GET['shortname'];
$shortname = $_GET['shortname'];

echo "<script type=\"text/javascript\">\n";
echo "function timedRefresh(timeoutPeriod) {";
	echo "setTimeout("location.reload(true);",timeoutPeriod);";
echo "}";
echo "</script>\n" ;
$pagesArray = array("http://archivestage/~lale/vesuvius/vesuvius/www/cmax2010/index.php?mod=stat&act=status", "http://archivestage/~lale/vesuvius/vesuvius/www/cmax2010/index.php?mod=stat&act=gender","http://archivestage/~lale/vesuvius/vesuvius/www/cmax2010/index.php?mod=stat&act=age");
$randNum = rand(0, count($pagesArray)-1);
include($pagesArray[$randNum]);
echo "<div "container" onload="JavaScript:timedRefresh(15000);">";
echo "<div id="note" align="center" >";
echo "This page will refresh every 15 seconds. <br>";
echo "<a href="http://archivestage/~lale/vesuvius/vesuvius/www/index.php">Back to People Statistics Home</a>";
echo "</div>\n";
}
*/

/***********************************************************
 NEW Arrival_rate- from arrival rate table
***********************************************************/
function shn_stat_new_arrival_rate() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];


	$q="SELECT arrival_time as source_date, source_all AS count_source_date
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$q1="SELECT arrival_time as source_date1, source_triagepic AS count_source_date1
		FROM `arrival_rate` a
		join incident b ON a.incident_id= b.incident_id
		WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$q2="SELECT arrival_time as source_date2, source_reunite AS count_source_date2
		FROM `arrival_rate` a
		join incident b ON a.incident_id= b.incident_id
		WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$q3="SELECT arrival_time as source_date3, source_website AS count_source_date3
				FROM `arrival_rate` a
				join incident b ON a.incident_id= b.incident_id
				WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$q4="SELECT arrival_time as source_date4, source_pfif AS count_source_date4
								FROM `arrival_rate` a
								join incident b ON a.incident_id= b.incident_id
								WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$q5="SELECT arrival_time as source_date5, source_vanilla_email AS count_source_date5
						FROM `arrival_rate` a
						join incident b ON a.incident_id= b.incident_id
						WHERE (b.shortname ='".mysql_real_escape_string($_GET['shortname'])."') GROUP BY DATE( arrival_time ) ORDER BY DATE( arrival_time )";

	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$res1 = $global['db']->Execute($q1);
	$row1 = $res1->FetchRow();

	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	$res5 = $global['db']->Execute($q5);
	$row5 = $res5->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}
		while($row = $res->FetchRow());


		if($row1 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date1 = array();
	$json_count_source_date1 = array();
	do{
		$source_date1[] = (strtotime($row1['source_date1'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date1, $row1['source_date1']);
		$count_source_date1[] = $row1['count_source_date1'];
		array_push($json_count_source_date1, $row1['count_source_date1']);
		}
		while($row1 = $res1->FetchRow());

		if($row2 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date2 = array();
	$json_count_source_date2 = array();
	do{
		$source_date2[] = (strtotime($row2['source_date2'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date2, $row2['source_date2']);
		$count_source_date2[] = $row2['count_source_date2'];
		array_push($json_count_source_date2, $row2['count_source_date2']);
		}
		while($row2 = $res2->FetchRow());

		if($row3 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date3 = array();
	$json_count_source_date3 = array();
	do{
		$source_date3[] = (strtotime($row3['source_date3'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date3, $row3['source_date3']);
		$count_source_date3[] = $row3['count_source_date3'];
		array_push($json_count_source_date3, $row3['count_source_date3']);
		}
		while($row3 = $res3->FetchRow());

		if($row4 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date4 = array();
	$json_count_source_date4 = array();
	do{
		$source_date4[] = (strtotime($row4['source_date4'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date4, $row4['source_date4']);
		$count_source_date4[] = $row4['count_source_date4'];
		array_push($json_count_source_date4, $row4['count_source_date4']);
		}
		while($row4 = $res4->FetchRow());

		if($row5 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date5 = array();
	$json_count_source_date5 = array();
	do{
		$source_date5[] = (strtotime($row5['source_date5'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date5, $row5['source_date5']);
		$count_source_date5[] = $row5['count_source_date5'];
		array_push($json_count_source_date5, $row5['count_source_date5']);
		}
		while($row5 = $res5->FetchRow());


		//for status
		$q_s="SELECT DISTINCT d.option_description as opt_status, count( opt_status ) as count_opt_status FROM person_status a
		join field_options d ON a.opt_status=d.option_code
		join person_uuid b ON a.p_uuid= b.p_uuid
		join incident c ON c.incident_id= b.incident_id where c.shortname ='".mysql_real_escape_string($_GET['shortname'])."'
			GROUP BY opt_status";
		$res = $global['db']->Execute($q_s);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_opt_status = array();
	$json_count_opt_status = array();
	do{
		$opt_status[] = $row['opt_status'];
		array_push($json_opt_status, $row['opt_status']);
		$count_opt_status[] = $row['count_opt_status'];
		array_push($json_count_opt_status, $row['count_opt_status']);
		}
		while($row = $res->FetchRow());

		//for gender
		$q_g="SELECT DISTINCT d.option_description as opt_gender, count( opt_gender ) AS count_opt_gender
			FROM person_details a
			JOIN field_options d ON a.opt_gender = d.option_code
			JOIN person_uuid b ON a.p_uuid = b.p_uuid
			JOIN incident c ON c.incident_id = b.incident_id
			WHERE c.shortname LIKE '".$shortname."'
									GROUP BY option_description";

		$res = $global['db']->Execute($q_g);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_opt_gender = array();
	$json_count_opt_gender = array();
	do{
		$opt_gender[] = $row['opt_gender'];
		array_push($json_opt_gender, $row['opt_gender']);
		$count_opt_gender[] = $row['count_opt_gender'];
		array_push($json_count_opt_gender, $row['count_opt_gender']);
		}
		while($row = $res->FetchRow());


		//for pediatrics/adults
		$q_a="SELECT 'pediatrics' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			JOIN incident c ON b.incident_id = c.incident_id
			where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 1 and a.years_old <= 17))
					UNION
					SELECT 'adult' as opt_status, count(years_old) as count_status FROM `person_details` a
					join person_uuid b ON a.p_uuid= b.p_uuid
					JOIN incident c ON b.incident_id = c.incident_id
					where (c.shortname ='".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 18))";

		$res = $global['db']->Execute($q_a);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_opt_age = array();
	$json_count_opt_age = array();
	do{
		$opt_age[] = $row['opt_age'];
		array_push($json_opt_age, $row['opt_age']);
		$count_opt_age[] =  $row['count_opt_age'];
		array_push($json_count_opt_age, $row['count_opt_age']);
		}
		while($row = $res->FetchRow());

		//for tp category

		$q_tp="SELECT distinct (triage_category) as opt_category, count(distinct triage_category) as count_optcategory FROM `edxl_co_lpf` a
					join person_uuid b ON a.p_uuid= b.p_uuid
					JOIN incident c ON b.incident_id = c.incident_id
					where c.shortname ='".mysql_real_escape_string($_GET['shortname'])."'
			group by a.triage_category";

		$res = $global['db']->Execute($q_tp);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_opt_category = array();
	$json_count_opt_category = array();
	do{
		$opt_category[] = $row['opt_category'];
		array_push($json_opt_category, $row['opt_category']);
		$count_optcategory[] =  (int) $row['count_optcategory'];
		array_push($json_count_optcategory, $row['count_optcategory']);
		}
		while($row = $res->FetchRow());

		?>
<div id="container" style="width: 600px; height: 800px;"></div>
;

<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);

$json_source_date1 = implode("','",$json_source_date1);
$json_count_source_date1 = implode(",", $json_count_source_date1);

$json_source_date2 = implode("','",$json_source_date2);
$json_count_source_date2 = implode(",", $json_count_source_date2);

$json_source_date3 = implode("','",$json_source_date3);
$json_count_source_date3 = implode(",", $json_count_source_date3);

$json_source_date4 = implode("','",$json_source_date4);
$json_count_source_date4 = implode(",", $json_count_source_date4);

$json_source_date5 = implode("','",$json_source_date5);
$json_count_source_date5 = implode(",", $json_count_source_date5);

$json_opt_status = implode("','",$json_opt_status);
$json_count_opt_status = implode(",", $json_count_opt_status);

$json_opt_gender = implode("','",$json_opt_gender);
$json_count_opt_gender = implode(",", $json_count_opt_gender);

$json_opt_age = implode("','",$json_opt_age);
$json_count_opt_age = implode(",", $json_count_opt_age);


$json_opt_category = implode("','",$json_opt_category);
$json_count_optcategory = implode(",", $json_count_optcategory);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\n";
echo "var points1 = [$json_count_source_date1],\n";
echo "dates1 = " .json_encode($source_date1);
echo ",\n";
echo "j, data1 = [], chart;";
echo "\n";
echo "for(j=0; j<points1.length; j++) {\n";
echo "data1.push([dates1[j], points1[j]]);\n";
echo "}\n";

echo "\n";
echo "var points2 = [$json_count_source_date2],\n";
echo "dates2 = " .json_encode($source_date2);
echo ",\n";
echo "k, data2 = [], chart;";
echo "\n";
echo "for(k=0; k<points2.length; k++) {\n";
echo "data2.push([dates2[k], points2[k]]);\n";
echo "}\n";

echo "\n";
echo "var points3 = [$json_count_source_date3],\n";
echo "dates3 = " .json_encode($source_date3);
echo ",\n";
echo "l, data3 = [], chart;";
echo "\n";
echo "for(l=0; l<points3.length; l++) {\n";
echo "data3.push([dates3[l], points3[l]]);\n";
echo "}\n";

echo "\n";
echo "var points4 = [$json_count_source_date4],\n";
echo "dates4 = " .json_encode($source_date4);
echo ",\n";
echo "m, data4 = [], chart;";
echo "\n";
echo "for(m=0; m<points4.length; m++) {\n";
echo "data4.push([dates4[m], points4[m]]);\n";
echo "}\n";

echo "\n";
echo "var points5 = [$json_count_source_date5],\n";
echo "dates5 = " .json_encode($source_date5);
echo ",\n";
echo "n, data5 = [], chart;";
echo "\n";
echo "for(n=0; n<points5.length; n++) {\n";
echo "data5.push([dates5[n], points5[n]]);\n";
echo "}\n";

echo "var counts = [$json_count_opt_status],\n";
echo "names = " .json_encode($opt_status);
echo ",\n";
echo "j, data_status = [], chart;";
echo "\n";
echo "for(j=0; j<counts.length; j++) {\n";
echo "data_status.push([names[j], counts[j]]);\n";
echo "}\n";

echo "var counts_g = [$json_count_opt_gender],\n";
echo "names_g = " .json_encode($opt_gender);
echo ",\n";
echo "j, data_gender = [], chart;";
echo "\n";
echo "for(j=0; j<counts_g.length; j++) {\n";
echo "data_gender.push([names_g[j], counts_g[j]]);\n";
echo "}\n";

echo "var counts_a = [$json_count_opt_age],\n";
echo "names_a = " .json_encode($opt_age);
echo ",\n";
echo "j, data_age = [], chart;";
echo "\n";
echo "for(j=0; j<counts_a.length; j++) {\n";
echo "data_age.push([names_a[j], counts_a[j]]);\n";
echo "}\n";

echo "var counts_c = [$json_count_optcategory],\n";
echo "names_c = " .json_encode($opt_category);
echo ",\n";
echo "j, data_category = [], chart;";
echo "\n";
echo "for(j=0; j<counts_c.length; j++) {\n";
echo "data_category.push([names_c[j], counts_c[j]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Date (new table) from $shortname'\n" ;
echo "},\n" ;

echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %p',\n" ;
echo "minute: '%I:%M %p',\n" ;
echo "hour: '%I:%M %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n";
echo "allowDecimals: false,\n";
echo "title: {\n";
echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "area: {\n";
echo "align: 'right',\n";
echo "backgroundColor: '#FCFFC5',\n";
echo "enabled: true,\n";
echo "},\n";
echo "pie: {\n";
echo "enabled: true,\n";
echo "align: 'left',\n";
echo "layout: 'horizontal',\n";
echo "verticalAlign: 'top',\n";
echo "floating: true,\n";
echo "backgroundColor: 'yellow'\n";
echo "}\n";
echo "},\n";
echo "plotOptions: {\n";

echo "area: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,1,0,0)']\n";
echo "]\n";
echo "},\n";
echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: true,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "area: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true\n" ;
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "},\n" ;
echo "pie: {\n" ;
echo "allowPointSelect: true,\n" ;
echo "cursor: 'pointer',\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true,\n" ;
echo "formatter: function() {\n" ;
echo "return '<b>'+ this.point.name +'</b><br/>'+\n" ;
echo "this.y;\n" ;
echo "}\n" ;
echo "}\n" ;
echo "}\n" ;
echo "},\n";
echo "series: [{\n" ;
//echo "name: '". $shortname;
echo "name: 'All sources";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'TriagePic";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data1\n" ;
echo "},\n";

echo "{\n" ;
echo "name: 'ReUnite";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data2\n" ;
echo "},\n";

echo "{\n" ;
echo "name: 'Website";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data3\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'PFIF";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data4\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'Vanilla Email";
echo "'";
echo ",\n";
echo "type: 'area',\n" ;
echo "data: data5\n" ;
echo "},\n";
echo "{\n";
echo "type: 'pie',\n";
echo "data: data_gender,\n" ;
echo "center: [275, 150],\n";
echo "size: 150,\n";
echo "showInLegend: true,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";
echo "{\n";
echo "type: 'pie',\n";
echo "data: data_age,\n" ;
echo "center: [575, 150],\n";
echo "size: 150,\n";
echo "showInLegend: true,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";

echo "{\n";
echo "type: 'pie',\n";
echo "data: data_category,\n" ;
echo "center: [875, 150],\n";
echo "size: 150,\n";
echo "showInLegend: true,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";

//echo "{\n";
echo "{\n";
echo "type: 'pie',\n";
echo "data: data_status,\n" ;
echo "center: [1075, 150],\n";
echo "size: 150,\n";
echo "showInLegend: true,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;

// the button action
echo "
		$('#button').click(function() {
		if (chart.series.length) {
		chart.series[0].remove();
    }
});
		";
echo "</script>\n" ;
echo "Test area ";
}
/***********************************************************
 Cummulative arrivals- from arrival rate table
***********************************************************/
function shn_stat_cummulative_arrival() {
	global $global;
	shn_stat_menu();
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	//$item = $_GET['item'];

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	//shn_stat_menu();

	$q = "
			SELECT *
			FROM incident
			WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
			";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}


	//start and end date
	/*
	if ($shortname=='shield2012' or $shortname=='cmax2010' or $shortname='new'){
	 $q_start_date="SELECT when_sent as arrival_time FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id
	WHERE (c.event_name ='".mysql_real_escape_string($_GET['shortname'])."')
	ORDER BY arrival_time asc limit 1";

	}else{
	*/
	$q_start_date="SELECT arrival_time from arrival_rate a
									where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
									ORDER BY arrival_time asc limit 1";

	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	/*
	if ($shortname=='shield2012' or $shortname=='cmax2010' or $shortname='new'){
	 $$q_end_date="SELECT when_sent as arrival_time FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id
	WHERE (c.event_name ='".mysql_real_escape_string($_GET['shortname'])."')
	ORDER BY arrival_time desc limit 1";

	}else{
	*/
	$q_end_date="SELECT arrival_time from arrival_rate a
					where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
					ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));
	//}


	$q="SELECT arrival_time as source_date, source_all AS count_source_date
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q1="SELECT arrival_time as source_date1, source_triagepic AS count_source_date1
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."')  group by arrival_time  ORDER BY  arrival_time";

	$q2="SELECT arrival_time as source_date2, source_reunite AS count_source_date2
					FROM `arrival_rate` a
					join incident b ON a.incident_id= b.incident_id
					WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q3="SELECT arrival_time as source_date3, source_website AS count_source_date3
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q4="SELECT arrival_time as source_date4, source_pfif AS count_source_date4
										FROM `arrival_rate` a
										join incident b ON a.incident_id= b.incident_id
										WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q5="SELECT arrival_time as source_date5, source_vanilla_email AS count_source_date5
				FROM `arrival_rate` a
				join incident b ON a.incident_id= b.incident_id
				WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";
	//}
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$res1 = $global['db']->Execute($q1);
	$row1 = $res1->FetchRow();

	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	$res5 = $global['db']->Execute($q5);
	$row5 = $res5->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}
		while($row = $res->FetchRow());


		if($row1 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date1 = array();
	$json_count_source_date1 = array();
	do{
		$source_date1[] = (strtotime($row1['source_date1'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date1, $row1['source_date1']);
		$count_source_date1[] = $row1['count_source_date1'];
		array_push($json_count_source_date1, $row1['count_source_date1']);
		}
		while($row1 = $res1->FetchRow());

		if($row2 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date2 = array();
	$json_count_source_date2 = array();
	do{
		$source_date2[] = (strtotime($row2['source_date2'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date2, $row2['source_date2']);
		$count_source_date2[] = $row2['count_source_date2'];
		array_push($json_count_source_date2, $row2['count_source_date2']);
		}
		while($row2 = $res2->FetchRow());

		if($row3 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date3 = array();
	$json_count_source_date3 = array();
	do{
		$source_date3[] = (strtotime($row3['source_date3'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date3, $row3['source_date3']);
		$count_source_date3[] = $row3['count_source_date3'];
		array_push($json_count_source_date3, $row3['count_source_date3']);
		}
		while($row3 = $res3->FetchRow());

		if($row4 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date4 = array();
	$json_count_source_date4 = array();
	do{
		$source_date4[] = (strtotime($row4['source_date4'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date4, $row4['source_date4']);
		$count_source_date4[] = $row4['count_source_date4'];
		array_push($json_count_source_date4, $row4['count_source_date4']);
		}
		while($row4 = $res4->FetchRow());

		if($row5 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date5 = array();
	$json_count_source_date5 = array();
	do{
		$source_date5[] = (strtotime($row5['source_date5'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date5, $row5['source_date5']);
		$count_source_date5[] = $row5['count_source_date5'];
		array_push($json_count_source_date5, $row5['count_source_date5']);
		}
		while($row5 = $res5->FetchRow());



		?>
<div id="container" style="width: 100%; height: 100%;"></div>
;
<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);

$json_source_date1 = implode("','",$json_source_date1);
$json_count_source_date1 = implode(",", $json_count_source_date1);

$json_source_date2 = implode("','",$json_source_date2);
$json_count_source_date2 = implode(",", $json_count_source_date2);

$json_source_date3 = implode("','",$json_source_date3);
$json_count_source_date3 = implode(",", $json_count_source_date3);

$json_source_date4 = implode("','",$json_source_date4);
$json_count_source_date4 = implode(",", $json_count_source_date4);

$json_source_date5 = implode("','",$json_source_date5);
$json_count_source_date5 = implode(",", $json_count_source_date5);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\n";
echo "var points1 = [$json_count_source_date1],\n";
echo "dates1 = " .json_encode($source_date1);
echo ",\n";
echo "j, data1 = [], chart;";
echo "\n";
echo "for(j=0; j<points1.length; j++) {\n";
echo "data1.push([dates1[j], points1[j]]);\n";
echo "}\n";

echo "\n";
echo "var points2 = [$json_count_source_date2],\n";
echo "dates2 = " .json_encode($source_date2);
echo ",\n";
echo "k, data2 = [], chart;";
echo "\n";
echo "for(k=0; k<points2.length; k++) {\n";
echo "data2.push([dates2[k], points2[k]]);\n";
echo "}\n";

echo "\n";
echo "var points3 = [$json_count_source_date3],\n";
echo "dates3 = " .json_encode($source_date3);
echo ",\n";
echo "l, data3 = [], chart;";
echo "\n";
echo "for(l=0; l<points3.length; l++) {\n";
echo "data3.push([dates3[l], points3[l]]);\n";
echo "}\n";

echo "\n";
echo "var points4 = [$json_count_source_date4],\n";
echo "dates4 = " .json_encode($source_date4);
echo ",\n";
echo "m, data4 = [], chart;";
echo "\n";
echo "for(m=0; m<points4.length; m++) {\n";
echo "data4.push([dates4[m], points4[m]]);\n";
echo "}\n";

echo "\n";
echo "var points5 = [$json_count_source_date5],\n";
echo "dates5 = " .json_encode($source_date5);
echo ",\n";
echo "n, data5 = [], chart;";
echo "\n";
echo "for(n=0; n<points5.length; n++) {\n";
echo "data5.push([dates5[n], points5[n]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "text: 'Cummulative Arrivals $description Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '16px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "y: 50,\n";
echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
//echo "second: '%b %e',\n" ;
//echo "minute: '%b %e',\n" ;
//echo "hour: '%b %e',\n" ;
echo "second: '%I:%M %H %p',\n" ;
echo "minute: '%I:%M %H %p',\n" ;
echo "hour: '%I:%M %H %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis:  [{
							allowDecimals: false,
							lineWidth: 3,
							title: {
							text: 'Total People Count'
			}
		}, {
							allowDecimals: false,
							lineWidth: 3,
							opposite: true,
							title: {
							text: 'Total People Count'
			}
		}],\n";

//echo "min: 0.6,\n";
//echo "startOnTick: true,\n";
//echo "showFirstLabel: true\n";
//echo "},\n";

echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "area: {\n";
echo "align: 'right',\n";
echo "backgroundColor: '#FCFFC5',\n";
echo "enabled: true\n";
echo "}\n";

echo "},\n";
echo "plotOptions: {\n";
echo "line: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,1,0,0)']\n";
echo "]\n";
echo "},\n";

echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: true,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "area: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: false\n" ; //disable the point labels
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;
//echo "
//series: {
//events: {
	//hide: function(event) {
	//alert ('The series was just hidden');
		//}
		//}
		//}
		//";

		echo "},\n";
		echo "series: [{\n" ;
		//echo "name: '". $shortname;
		echo "name: 'All sources";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data\n" ;
		echo "},\n";
		echo "{\n" ;
		echo "name: 'TriagePic";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data1\n" ;
		echo "},\n";

		echo "{\n" ;
		echo "name: 'ReUnite";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data2\n" ;
		echo "},\n";

		echo "{\n" ;
		echo "name: 'Website";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data3\n" ;
		echo "},\n";
		echo "{\n" ;
		echo "name: 'PFIF";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data4\n" ;
		echo "},\n";
		echo "{\n" ;
		echo "name: 'Vanilla Email";
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
		echo "data: data5\n" ;

		echo "}]\n" ;
		echo "});\n" ;
		echo "});\n" ;

		// the button action
		/*
		echo "
		$('#button').click(function() {
    if (chart.series.length) {
        chart.series[0].remove();
				}
				});
		";
		*/
		echo "</script>\n" ;
		//echo "Test area ";
}
/***********************************************************
 Stacked Cummulative arrivals- from arrival rate table
***********************************************************/
function shn_stat_stacked_cummulative_arrival() {
	global $global;
	shn_stat_menu();
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	//$item = $_GET['item'];

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	//shn_stat_menu();

	$q = "
			SELECT *
			FROM incident
			WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
		";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	//start and end date
	$q_start_date="SELECT arrival_time from arrival_rate a
		where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
		ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
		where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
		ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	//$q="SELECT arrival_time as source_date, source_all AS count_source_date
	//FROM `arrival_rate` a
	//join incident b ON a.incident_id= b.incident_id
	//WHERE (b.shortname = '". $shortname ."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q1="SELECT arrival_time as source_date1, source_triagepic AS count_source_date1
		FROM `arrival_rate` a
		join incident b ON a.incident_id= b.incident_id
		WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q2="SELECT arrival_time as source_date2, source_reunite AS count_source_date2
		FROM `arrival_rate` a
		join incident b ON a.incident_id= b.incident_id
		WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q3="SELECT arrival_time as source_date3, source_website AS count_source_date3
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q4="SELECT arrival_time as source_date4, source_pfif AS count_source_date4
						FROM `arrival_rate` a
						join incident b ON a.incident_id= b.incident_id
						WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	$q5="SELECT arrival_time as source_date5, source_vanilla_email AS count_source_date5
							FROM `arrival_rate` a
							join incident b ON a.incident_id= b.incident_id
							WHERE (b.shortname = '".mysql_real_escape_string($_GET['shortname'])."') GROUP BY ( arrival_time ) ORDER BY ( arrival_time )";

	//$res = $global['db']->Execute($q);
	//$row = $res->FetchRow();
	$res1 = $global['db']->Execute($q1);
	$row1 = $res1->FetchRow();

	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	$res5 = $global['db']->Execute($q5);
	$row5 = $res5->FetchRow();
	/*
	 if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
	date_default_timezone_set('UTC');
	array_push($json_source_date, $row['source_date']);
	$count_source_date[] = $row['count_source_date'];
	array_push($json_count_source_date, $row['count_source_date']);
	}
	while($row = $res->FetchRow());
	*/

	if($row1 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date1 = array();
	$json_count_source_date1 = array();
	do{
		$source_date1[] = (strtotime($row1['source_date1'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date1, $row1['source_date1']);
		$count_source_date1[] = $row1['count_source_date1'];
		array_push($json_count_source_date1, $row1['count_source_date1']);
		}
		while($row1 = $res1->FetchRow());

		if($row2 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date2 = array();
	$json_count_source_date2 = array();
	do{
		$source_date2[] = (strtotime($row2['source_date2'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date2, $row2['source_date2']);
		$count_source_date2[] = $row2['count_source_date2'];
		array_push($json_count_source_date2, $row2['count_source_date2']);
		}
		while($row2 = $res2->FetchRow());

		if($row3 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date3 = array();
	$json_count_source_date3 = array();
	do{
		$source_date3[] = (strtotime($row3['source_date3'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date3, $row3['source_date3']);
		$count_source_date3[] = $row3['count_source_date3'];
		array_push($json_count_source_date3, $row3['count_source_date3']);
		}
		while($row3 = $res3->FetchRow());

		if($row4 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date4 = array();
	$json_count_source_date4 = array();
	do{
		$source_date4[] = (strtotime($row4['source_date4'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date4, $row4['source_date4']);
		$count_source_date4[] = $row4['count_source_date4'];
		array_push($json_count_source_date4, $row4['count_source_date4']);
		}
		while($row4 = $res4->FetchRow());

		if($row5 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date5 = array();
	$json_count_source_date5 = array();
	do{
		$source_date5[] = (strtotime($row5['source_date5'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date5, $row5['source_date5']);
		$count_source_date5[] = $row5['count_source_date5'];
		array_push($json_count_source_date5, $row5['count_source_date5']);
		}
		while($row5 = $res5->FetchRow());


		?>
<div id="container" style="width: 100%; height: 100%;"></div>
;

<?php
$shortname = $_GET['shortname'];
echo "\n";
//$json_source_date = implode("','",$json_source_date);
//$json_count_source_date = implode(",", $json_count_source_date);

$json_source_date1 = implode("','",$json_source_date1);
$json_count_source_date1 = implode(",", $json_count_source_date1);

$json_source_date2 = implode("','",$json_source_date2);
$json_count_source_date2 = implode(",", $json_count_source_date2);

$json_source_date3 = implode("','",$json_source_date3);
$json_count_source_date3 = implode(",", $json_count_source_date3);

$json_source_date4 = implode("','",$json_source_date4);
$json_count_source_date4 = implode(",", $json_count_source_date4);

$json_source_date5 = implode("','",$json_source_date5);
$json_count_source_date5 = implode(",", $json_count_source_date5);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
//echo "var points = [$json_count_source_date],\n";
//echo "dates = " .json_encode($source_date);
//echo ",\n";
//echo "i, data = [], chart;";
//echo "\n";
//echo "for(i=0; i<points.length; i++) {\n";
//echo "data.push([dates[i], points[i]]);\n";
//echo "}\n";

echo "\n";
echo "var points1 = [$json_count_source_date1],\n";
echo "dates1 = " .json_encode($source_date1);
echo ",\n";
echo "j, data1 = [], chart;";
echo "\n";
echo "for(j=0; j<points1.length; j++) {\n";
echo "data1.push([dates1[j], points1[j]]);\n";
echo "}\n";

echo "\n";
echo "var points2 = [$json_count_source_date2],\n";
echo "dates2 = " .json_encode($source_date2);
echo ",\n";
echo "k, data2 = [], chart;";
echo "\n";
echo "for(k=0; k<points2.length; k++) {\n";
echo "data2.push([dates2[k], points2[k]]);\n";
echo "}\n";

echo "\n";
echo "var points3 = [$json_count_source_date3],\n";
echo "dates3 = " .json_encode($source_date3);
echo ",\n";
echo "l, data3 = [], chart;";
echo "\n";
echo "for(l=0; l<points3.length; l++) {\n";
echo "data3.push([dates3[l], points3[l]]);\n";
echo "}\n";

echo "\n";
echo "var points4 = [$json_count_source_date4],\n";
echo "dates4 = " .json_encode($source_date4);
echo ",\n";
echo "m, data4 = [], chart;";
echo "\n";
echo "for(m=0; m<points4.length; m++) {\n";
echo "data4.push([dates4[m], points4[m]]);\n";
echo "}\n";

echo "\n";
echo "var points5 = [$json_count_source_date5],\n";
echo "dates5 = " .json_encode($source_date5);
echo ",\n";
echo "n, data5 = [], chart;";
echo "\n";
echo "for(n=0; n<points5.length; n++) {\n";
echo "data5.push([dates5[n], points5[n]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "text: 'Stacked Cummulative Arrivals $description Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '16px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "y: 50,\n";
echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %H %p',\n" ;
echo "minute: '%I:%M %H %p',\n" ;
echo "hour: '%I:%M %H %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
/*
 echo "yAxis: {\n";
			echo "allowDecimals: false,\n";
echo "labels: {\n";
            echo "formatter: function() {\n";
                echo "return '<b>'+this.value;\n";
echo "}\n";
echo "},\n";
echo "title: {\n";
            echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
*/
echo "yAxis: [{
			allowDecimals: false,
			lineWidth: 3,
			title: {
			text: 'Total People Count'
			}
		}, {
			allowDecimals: false,
			lineWidth: 3,
			opposite: true,
			title: {
			text: 'Total People Count'
			}
		}],\n";

echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "area: {\n";
echo "align: 'right',\n";
echo "backgroundColor: '#FCFFC5',\n";
echo "enabled: true\n";
echo "}\n";

echo "},\n";
echo "plotOptions: {\n";
echo "series: {\n";
echo "stacking: 'normal'\n";
echo "},\n";
echo "area: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,1,0,0)']\n";
echo "]\n";
echo "},\n";

echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: true,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "area: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: false\n" ;//disable the point labels
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;
//echo "
//series: {
//events: {
	//hide: function(event) {
	//alert ('The series was just hidden');
		//}
		//}
		//}
		//";

		echo "},\n";
		echo "series: [{\n" ;
		//echo "name: '". $shortname;
		//echo "name: 'All sources";
		//echo "'";
		//echo ",\n";
		//echo "type: 'area',\n" ;
		//echo "data: data\n" ;
		//echo "},\n";
		//echo "{\n" ;
		echo "name: 'TriagePic";
		echo "'";
		echo ",\n";
		echo "type: 'area',\n" ;
		echo "data: data1\n" ;
		echo "},\n";

		echo "{\n" ;
		echo "name: 'ReUnite";
		echo "'";
		echo ",\n";
		echo "type: 'area',\n" ;
		echo "data: data2\n" ;
		echo "},\n";

		echo "{\n" ;
		echo "name: 'Website";
		echo "'";
		echo ",\n";
		echo "type: 'area',\n" ;
		echo "data: data3\n" ;
		echo "},\n";
		echo "{\n" ;
		echo "name: 'PFIF";
		echo "'";
		echo ",\n";
		echo "type: 'area',\n" ;
		echo "data: data4\n" ;
		echo "},\n";
		echo "{\n" ;
		echo "name: 'Vanilla Email";
		echo "'";
		echo ",\n";
		echo "type: 'area',\n" ;
		echo "data: data5\n" ;

		echo "}]\n" ;
		echo "});\n" ;
		echo "});\n" ;

		// the button action
		/*
		echo "
		$('#button').click(function() {
    if (chart.series.length) {
        chart.series[0].remove();
				}
				});
		";
		*/
		echo "</script>\n" ;
		//echo "Test area ";
}
/***************************************
 demographic charts
****************************************/
function shn_stat_demographic() {
	global $global;
	shn_stat_menu();

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	//shn_stat_menu();
	//shn_stat_screen_detection();

	//echo "width: " .$width;
	//echo " height: " .$height;

	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
		";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	$groupID = $_SESSION['group_id'];
	//echo "Shortname: " .$shortname."";
	//echo "Group ID: " .$groupID."";

	//start and end date
	$q_start_date="SELECT arrival_time from arrival_rate a
		where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
		ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
		where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
		ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	//for status

	//$q_s="SELECT DISTINCT d.option_code as opt_status, d.option_description as color, count( opt_code ) as count_opt_status FROM person_status a
	//join field_options d ON a.opt_status=d.option_code where (d.field_name ='opt_status_color')
	//join person_uuid b ON a.p_uuid= b.p_uuid
	//join incident c ON c.incident_id= b.incident_id where c.shortname = '".$shortname."'
	//GROUP BY opt_status";
	$q_s="SELECT DISTINCT f.option_description AS opt_status, COUNT( opt_status ) AS count_opt_status, g.option_description
			FROM person_status s
			LEFT JOIN field_options f ON s.opt_status = f.option_code
			LEFT JOIN field_options g ON f.option_code = g.option_code
			JOIN person_uuid p ON p.p_uuid= s.p_uuid
			JOIN incident i ON i.incident_id = p.incident_id
			WHERE i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
						AND g.field_name = 'opt_status_color'
						GROUP BY opt_status ";

	//using status_count view
	//$q_s="SELECT opt_status, count_opt_status, color FROM status_count where incident_id = '".$shortname."'";

	$res = $global['db']->Execute($q_s);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
		$status_has_data=false;
	}
	$status_has_data=true;
	$json_opt_status = array();
	$json_count_opt_status = array();
	//to match color
	$json_colors=array();
	do{
		$opt_status[] = $row['opt_status'];
		array_push($json_opt_status, $row['opt_status']);
		$count_opt_status[] = $row['count_opt_status'];
		array_push($json_count_opt_status, $row['count_opt_status']);
		//color
		$color[] = $row['option_description'];
		array_push($json_colors, $row['option_description']);
		}
		while($row = $res->FetchRow());

		//if ($shortname!=='testind') {
		//for gender
		$q_g="SELECT DISTINCT d.option_description as opt_gender, count( opt_gender ) AS count_opt_gender
									FROM person_details a
									JOIN field_options d ON a.opt_gender = d.option_code
									JOIN person_uuid b ON a.p_uuid = b.p_uuid
									JOIN incident c ON c.incident_id = b.incident_id
									WHERE c.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
					GROUP BY option_description";
		//using view gender_count
		//$q_g="SELECT opt_gender, count_opt_gender where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_g);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$gender_has_data=false;
	}
	$gender_has_data=true;
	$json_opt_gender = array();
	$json_count_opt_gender = array();
	do{
		$opt_gender[] = $row['opt_gender'];
		array_push($json_opt_gender, $row['opt_gender']);
		$count_opt_gender[] = $row['count_opt_gender'];
		array_push($json_count_opt_gender, $row['count_opt_gender']);
		}
		while($row = $res->FetchRow());


		//for pediatrics/adults
		$q_a="SELECT 'pediatrics' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			JOIN incident c ON b.incident_id = c.incident_id
			where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 1 and a.years_old <= 17))
					UNION
					SELECT 'adult' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
					join person_uuid b ON a.p_uuid= b.p_uuid
					JOIN incident c ON b.incident_id = c.incident_id
					where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 18))";
		//using view 'age_group_age'
		//$q_a="select opt_age, count_opt_age from age_group_count where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_a);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$agegroup_has_data=false;
	}
	$agegroup_has_data=true;
	$json_opt_age = array();
	$json_count_opt_age = array();
	do{
		$opt_age[] = ucfirst($row['opt_age']);
		array_push($json_opt_age, $row['opt_age']);
		$count_opt_age[] =  $row['count_opt_age'];
		array_push($json_count_opt_age, $row['count_opt_age']);
		}
		while($row = $res->FetchRow());

		//for tp category
		$q_tp="SELECT distinct (triage_category) as opt_category, count(triage_category) as count_optcategory FROM `edxl_co_lpf` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				JOIN incident c ON b.incident_id = c.incident_id
				where c.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
		group by a.triage_category
		order by a.triage_category";

		//using view 'tp_zonecolor_count'
		//$q_tp="SELECT opt_category, count_optcategory FROM `tp_zonecolor_count` where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_tp);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//echo 'No data available: ' . mysql_error();
     $TP_has_data=false;
	}
	$TP_has_data=true;
	$json_opt_category = array();
	$json_count_optcategory = array();
	do{
		$opt_category[] = $row['opt_category'];
		array_push($json_opt_category, $row['opt_category']);
		$count_optcategory[] = $row['count_optcategory'];
		array_push($json_count_optcategory, $row['count_optcategory']);
		}
		while($row = $res->FetchRow());
		//}//end if event not=testIND
		?>


<div id="container" style="width: 100%; height: 100%;"></div>


<?php
$shortname = $_GET['shortname'];
echo "\n";

$json_opt_status = implode("','",$json_opt_status);
$json_count_opt_status = implode(",", $json_count_opt_status);
$json_colors= implode("','", $json_colors);

$json_opt_gender = implode("','",$json_opt_gender);
$json_count_opt_gender = implode(",", $json_count_opt_gender);

$json_opt_age = implode("','",$json_opt_age);
$json_count_opt_age = implode(",", $json_count_opt_age);

$json_opt_category = implode("','",$json_opt_category);
$json_count_optcategory = implode(",", $json_count_optcategory);

echo "\n";

echo "<script type=\"text/javascript\">\n";

echo "counts = [$json_count_opt_status],\n";
echo "names = " .json_encode($opt_status);
echo ",\n";
echo "colors = ['".$json_colors ;
echo "'], \n";

//echo "colors = [$json_colors],\n";
//echo "colors= ['#348017','#000000', '#990033','red','blue','#333333'],\n";
echo "j, data_status = [], chart;";
echo "\n";
echo "for(j=0; j<counts.length; j++) {\n";

echo "
					data_status.push({
					name: names[j],
					y: counts[j],
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_g = [$json_count_opt_gender],\n";
echo "names_g = " .json_encode($opt_gender);
echo ",\n";
echo "colors= ['#9900FF', '#0099FF','#CCFFCC'],\n";
echo "j, data_gender = [], chart;";
echo "\n";
echo "for(j=0; j<counts_g.length; j++) {\n";
//echo "data_gender.push([names_g[j], counts_g[j]]);\n";
echo "
					data_gender.push({
					name: names_g[j],
					y: counts_g[j],
					color: colors[j]
			});
					";
echo "}\n";


echo "var counts_a = [$json_count_opt_age],\n";
echo "names_a = " .json_encode($opt_age);
echo ",\n";
echo "colors= ['#FFCCCC', '#FFCC99'],\n";
echo "j, data_age = [], chart;";
echo "\n";
echo "for(j=0; j<counts_a.length; j++) {\n";
//echo "data_age.push([names_a[j], counts_a[j]]);\n";
echo "
					data_age.push({
					name: names_a[j],
					y: counts_a[j],
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_c = [$json_count_optcategory],\n";
echo "names_c = " .json_encode($opt_category);
echo ",\n";
//echo "colors: ['#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";
echo "j, data_category = [], chart;";
echo "\n";
echo "for(j=0; j<counts_c.length; j++) {\n";

//echo "data_category.push([names_c[j], counts_c[j]])\n";
echo "
			data_category.push({
			name: names_c[j],
			y: counts_c[j],
			color: names_c[j]
			});
			";
echo "}\n";


echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
//echo "colors: ['pink', 'cyan', 'lime', 'cinnabar', 'orange', 'lilac', 'green', 'black', 'royal blue','blue','emerald', 'lime', 'yellow', 'red','gray','black'],\n";
echo "colors: ['#FCDFFF', '#00FFFF', '#8AFB17', '#7E2217', '#F87217', '#D462FF', '#4CC417', '#000000', '#151B8D','#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";

echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "text: 'Arrivals $description Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '20px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "y: 50,\n";
if ($startdate_has_data=true){
         echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
		 }
		 echo "},\n" ;

	  echo "xAxis: {\n" ;
	  echo "type: 'datetime',\n" ;
		 echo "maxZoom:  3600000,\n";
		 echo "dateTimeLabelFormats: {\n" ;
		 echo "second: '%I:%M %p',\n" ;
		 echo "minute: '%I:%M %p',\n" ;
		 echo "hour: '%I:%M %p',\n" ;
		 echo "day: '%b %e',\n" ;
		 echo "week: '%b %e',\n" ;
		 echo "month: '%b %e',\n" ;
		 echo "year: '%b %e'\n" ;
		 echo "}\n" ;
		 echo "},\n" ;
		 echo "yAxis: {\n";
			echo "allowDecimals: false,\n";
			echo "title: {\n";
			echo "text: 'Count of Persons Reported'\n";
			echo "},\n";
			echo "min: 0.6,\n";
			echo "startOnTick: true,\n";
			echo "showFirstLabel: true\n";
			echo "},\n";
			echo "tooltip: {\n";
			echo "shared: true\n";
			echo "},\n";
			echo "legend: {\n";

			echo "pie: {\n";
			echo "enabled: false,\n";
			echo "align: 'left',\n";
			echo "layout: 'horizontal',\n";
			echo "verticalAlign: 'top',\n";
			echo "floating: true,\n";
			echo "backgroundColor: 'yellow'\n";
			echo "}\n";
			echo "},\n";

			echo "plotOptions: {\n";
			//display more details
		 echo "pie: {\n" ;
			echo "allowPointSelect: true,\n" ;
			echo "cursor: 'pointer',\n" ;
			echo "dataLabels: {\n" ;
			echo "enabled: true,\n" ;
			echo "formatter: function() {\n" ;
			echo "return '<b>'+ this.point.name +'</b><br/>'+\n" ;
			echo "this.y;\n" ;
			echo "}\n" ;
			echo "}\n" ;
			echo "},\n" ;

		 //test
		 echo "
		 series: {
			events: {
			hide: function(event) {
			alert ('The series was just hidden');
                }
            }
        }
		 ";

		 echo "},\n";
	  //test
		 echo "series: [{\n" ;
		 //echo "name: '". $shortname;
		 echo "name: 'Gender";
		 echo "'";
		 echo ",\n";

		 //echo "{\n";
		 echo "type: 'pie',\n";
		 echo "data: data_gender,\n" ;
		 //echo "center: [200, 300],\n";
		 echo "center: ['15%', '50%'],\n";
		 echo "size: 200,\n";
		 echo "showInLegend: false,\n";
		 echo "showLegend: true,\n";
		 echo "dataLabels: {\n";
			echo "enabled: true\n";
			echo "}\n";
			echo "},\n";
			echo "{\n";
			echo "type: 'pie',\n";
			echo "data: data_age,\n" ;
			//echo "center: [550, 300],\n";
			echo "center: ['35%', '50%'],\n";
			echo "size: 200,\n";
			echo "showInLegend: false,\n";
			echo "showLegend: true,\n";
			echo "dataLabels: {\n";
			echo "enabled: true\n";
			echo "}\n";
			echo "},\n";

			echo "{\n";
			echo "type: 'pie',\n";
			echo "data: data_status,\n" ;
			//echo "colors: ['#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";
			//echo "colors: ['Green','Cyan', 'Yellow', 'Red', 'Grey', 'Black'],\n";
			//echo "center: [900, 300],\n";
			echo "center: ['60%', '50%'],\n";
			echo "size: 200,\n";
			echo "showInLegend: false,\n";
			//echo "showLegend: true,\n";
			echo "dataLabels: {\n";
			echo "enabled: true\n";
			echo "}\n";
			echo "},\n";

			//echo "{\n";
			echo "{\n";
			echo "name: 'Initial Triage Zones',\n";
			echo "type: 'pie',\n";
			echo "data: data_category,\n" ;
			//echo "center: [1250, 300],\n";
			echo "center: ['85%', '50%'],\n";
			echo "size: 200,\n";
			echo "showInLegend: false,\n";
			echo "showLegend: true,\n";
			echo "dataLabels: {\n";
			echo "enabled: true\n";
			echo "}\n";
			echo "}]\n" ;

			/*hide labels
			 //add labels for each pie charts
			//if ($has_data=true) then
			echo "labels: {\n" ;
        echo "items: [{\n" ;
		    if ($gender_has_data=='true'){
            echo "html: 'Gender',\n" ;
			echo "style: {\n" ;
                echo "left: '260px',\n" ;
			echo "top: '600px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			echo "}\n" ;
			echo "}\n";
			}
			if ($agegroup_has_data=='true'){
			echo ",{\n" ;
			echo "html: 'Age Group',\n" ;
			echo "style: {\n" ;
                echo "left: '630px',\n" ;
			echo "top: '600px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			//echo "zIndex=\"2\"\n";
			echo "}\n" ;
			echo "}\n";
			}
			if ($status_has_data=='true'){
			echo ",{\n" ;
			echo "html: 'People Locator Status',\n" ;
			echo "style: {\n" ;
                echo "left: '1100px',\n" ;
			echo "top: '600px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			//echo "zIndex=\"2\"\n";
			echo "}\n" ;
			echo "}\n";
			}
			//if it's hospital-based
			//if ($groupID='2'){
			if ($shortname=='cmax2010' or $shortname=='new' or $shortname=='test') {
			echo ",{\n" ;
            echo "html:'Based on Initial Triage Zones ',\n" ;
			echo "style: {\n" ;
                echo "left: '1500px',\n" ;
			echo "top: '600px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			//echo "zIndex=\"2\"\n";
			echo "}\n" ;
			echo "}\n";
			}
			//end if
			echo "]}\n" ;
			end labels */

			 
			echo "});\n" ;
			//for text label
			/*
			echo "
			function(chart) {

        //var point = chart.series[0].data_gender[1];
			var point = 260;
			var text = chart.renderer.text(
                'Testing1',
					point.plotX + chart.plotLeft + 10,
					point.plotY + chart.plotTop - 10
            ).attr({
                zIndex: 445
            		}).add();

			var box = text.getBBox();
			chart.renderer.rect(box.x - 5, box.y - 5, box.width + 10, box.height + 10, 5)
			.attr({
                fill: '#FFFFEF',
					stroke: 'gray',
					'stroke-width': 1,
					zIndex: 444
					})
			.add();

			});
			";
			*/
			echo "});\n" ;


			// the button action
			//echo "
			//$('#button').click(function() {
			//if (chart.series.length) {
			//chart.series[0].remove();
				//}
			//});
			//";


			echo "</script>\n" ;
			echo "Test area ";
}
/***********************************************************
 arrivals- from arrival rate table
***********************************************************/
function shn_stat_arrival() {
	global $global;
	shn_stat_menu();
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	//$item = $_GET['item'];

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	//shn_stat_menu();

	$q = "
									SELECT *
									FROM incident
									WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
									";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	//for starting date for all sources
	$q_start_date="SELECT arrival_time from arrival_rate a
									where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
					where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
					ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	$q="SELECT (arrival_time) as source_date, count(*) as count_source_date from arrival_rate a
 				where ((source_all >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
			GROUP by date(arrival_time)";

	$q1="SELECT (arrival_time) as source_date1, count(*) as count_source_date1 from arrival_rate a
			where ((source_triagepic >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
								GROUP by date(arrival_time)";

	$q2="SELECT (arrival_time) as source_date2, count(*) as count_source_date2 from arrival_rate a
								where ((source_reunite >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
						GROUP by date(arrival_time)";

	$q3="SELECT (arrival_time) as source_date3, count(*) as count_source_date3 from arrival_rate a
						where ((source_website >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
			GROUP by date(arrival_time)";

	$q4="SELECT (arrival_time) as source_date4, count(*) as count_source_date4 from arrival_rate a
    			where ((source_pfif >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
				GROUP by date(arrival_time)";

	$q5="SELECT (arrival_time) as source_date5, count(*) as count_source_date5 from arrival_rate a
				where ((source_vanilla_email >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
			GROUP by date(arrival_time)";

	if ($shortname=='shield2012' or $shortname=='testind' or $shortname=='testindmon' or $shortname=='testindtues' or $shortname=='testindwed' or $shortname=='testindthur'){

	$q="SELECT (arrival_time) as source_date, count(*) as count_source_date from arrival_rate a
		where ((source_all >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time), hour(arrival_time)";

	$q1="SELECT (arrival_time) as source_date1, count(*) as count_source_date1 from arrival_rate a
		where ((source_triagepic >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time),hour(arrival_time)";

	$q2="SELECT (arrival_time) as source_date2, count(*) as count_source_date2 from arrival_rate a
		where ((source_reunite >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time),hour(arrival_time)";

	$q3="SELECT (arrival_time) as source_date3, count(*) as count_source_date3 from arrival_rate a
		where ((source_website >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time),hour(arrival_time)";

	$q4="SELECT (arrival_time) as source_date4, count(*) as count_source_date4 from arrival_rate a
		where ((source_pfif >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time),hour(arrival_time)";

	$q5="SELECT (arrival_time) as source_date5, count(*) as count_source_date5 from arrival_rate a
		where ((source_vanilla_email >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time),hour(arrival_time)";
	}

	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$res1 = $global['db']->Execute($q1);
	$row1 = $res1->FetchRow();

	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	$res5 = $global['db']->Execute($q5);
	$row5 = $res5->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}
		while($row = $res->FetchRow());


		if($row1 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date1 = array();
	$json_count_source_date1 = array();
	do{
		$source_date1[] = (strtotime($row1['source_date1'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date1, $row1['source_date1']);
		$count_source_date1[] = $row1['count_source_date1'];
		array_push($json_count_source_date1, $row1['count_source_date1']);
		}
		while($row1 = $res1->FetchRow());

		if($row2 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date2 = array();
	$json_count_source_date2 = array();
	do{
		$source_date2[] = (strtotime($row2['source_date2'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date2, $row2['source_date2']);
		$count_source_date2[] = $row2['count_source_date2'];
		array_push($json_count_source_date2, $row2['count_source_date2']);
		}
		while($row2 = $res2->FetchRow());

		if($row3 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date3 = array();
	$json_count_source_date3 = array();
	do{
		$source_date3[] = (strtotime($row3['source_date3'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date3, $row3['source_date3']);
		$count_source_date3[] = $row3['count_source_date3'];
		array_push($json_count_source_date3, $row3['count_source_date3']);
		}
		while($row3 = $res3->FetchRow());

		if($row4 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date4 = array();
	$json_count_source_date4 = array();
	do{
		$source_date4[] = (strtotime($row4['source_date4'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date4, $row4['source_date4']);
		$count_source_date4[] = $row4['count_source_date4'];
		array_push($json_count_source_date4, $row4['count_source_date4']);
		}
		while($row4 = $res4->FetchRow());

		if($row5 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date5 = array();
	$json_count_source_date5 = array();
	do{
		$source_date5[] = (strtotime($row5['source_date5'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date5, $row5['source_date5']);
		$count_source_date5[] = $row5['count_source_date5'];
		array_push($json_count_source_date5, $row5['count_source_date5']);
		}
		while($row5 = $res5->FetchRow());


		?>
<div
	id="container" style="width: 100%; min-height: 100%;"></div>
;



<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);

$json_source_date1 = implode("','",$json_source_date1);
$json_count_source_date1 = implode(",", $json_count_source_date1);

$json_source_date2 = implode("','",$json_source_date2);
$json_count_source_date2 = implode(",", $json_count_source_date2);

$json_source_date3 = implode("','",$json_source_date3);
$json_count_source_date3 = implode(",", $json_count_source_date3);

$json_source_date4 = implode("','",$json_source_date4);
$json_count_source_date4 = implode(",", $json_count_source_date4);

$json_source_date5 = implode("','",$json_source_date5);
$json_count_source_date5 = implode(",", $json_count_source_date5);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\n";
echo "var points1 = [$json_count_source_date1],\n";
echo "dates1 = " .json_encode($source_date1);
echo ",\n";
echo "j, data1 = [], chart;";
echo "\n";
echo "for(j=0; j<points1.length; j++) {\n";
echo "data1.push([dates1[j], points1[j]]);\n";
echo "}\n";

echo "\n";
echo "var points2 = [$json_count_source_date2],\n";
echo "dates2 = " .json_encode($source_date2);
echo ",\n";
echo "k, data2 = [], chart;";
echo "\n";
echo "for(k=0; k<points2.length; k++) {\n";
echo "data2.push([dates2[k], points2[k]]);\n";
echo "}\n";

echo "\n";
echo "var points3 = [$json_count_source_date3],\n";
echo "dates3 = " .json_encode($source_date3);
echo ",\n";
echo "l, data3 = [], chart;";
echo "\n";
echo "for(l=0; l<points3.length; l++) {\n";
echo "data3.push([dates3[l], points3[l]]);\n";
echo "}\n";

echo "\n";
echo "var points4 = [$json_count_source_date4],\n";
echo "dates4 = " .json_encode($source_date4);
echo ",\n";
echo "m, data4 = [], chart;";
echo "\n";
echo "for(m=0; m<points4.length; m++) {\n";
echo "data4.push([dates4[m], points4[m]]);\n";
echo "}\n";

echo "\n";
echo "var points5 = [$json_count_source_date5],\n";
echo "dates5 = " .json_encode($source_date5);
echo ",\n";
echo "n, data5 = [], chart;";
echo "\n";
echo "for(n=0; n<points5.length; n++) {\n";
echo "data5.push([dates5[n], points5[n]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "text: 'Reported Rate $description Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '16px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "y: 50,\n";
echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %p',\n" ;
echo "minute: '%I:%M %p',\n" ;
echo "hour: '%I:%M %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
//echo "categories: ['dates']\n";
echo "},\n" ;
echo "yAxis: {\n";
echo "allowDecimals: false,\n";
echo "labels: {\n";
echo "formatter: function() {\n";
echo "return '<b>'+this.value;\n";
echo "}\n";
echo "},\n";
echo "title: {\n";
echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
echo "tooltip: {\n";
echo "shared: true\n";
echo "},\n";
echo "legend: {\n";
echo "line: {\n";
echo "align: 'right',\n";
echo "backgroundColor: '#FCFFC5',\n";
echo "enabled: true\n";
echo "}\n";

echo "},\n";
echo "plotOptions: {\n";

echo "area: {\n";
echo "fillColor: {\n";
echo "linearGradient: [0, 0, 0, 300],\n";
echo "stops: [\n";
echo "[0, Highcharts.getOptions().colors[1]],\n";
echo "[1, 'rgba(2,1,0,0)']\n";
echo "]\n";
echo "},\n";
echo "lineWidth: 1,\n";
echo "marker: {\n";
echo "enabled: true,\n";
echo "states: {\n";
echo "hover: {\n";
echo "enabled: true,\n";
echo "radius: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "shadow: false,\n";
echo "states: {\n";
echo "hover: {\n";
echo "lineWidth: 1\n";
echo "}\n";
echo "}\n";
echo "},\n";
echo "line: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true\n" ;
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;

echo "},\n";
echo "series: [{\n" ;
//echo "name: '". $shortname;
echo "name: 'All sources";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'TriagePic";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data1\n" ;
echo "},\n";

echo "{\n" ;
echo "name: 'ReUnite";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data2\n" ;
echo "},\n";

echo "{\n" ;
echo "name: 'Website";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data3\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'PFIF";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data4\n" ;
echo "},\n";
echo "{\n" ;
echo "name: 'Vanilla Email";
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data5\n" ;

echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;

// the button action
/*
 echo "
$('#button').click(function() {
    if (chart.series.length) {
        chart.series[0].remove();
		}
		});
";
*/

echo "</script>\n" ;

}
/***********************************************************
 Testing-new arrival_rate table
***********************************************************/
function shn_stat_test_select() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];


	/*testing
	 if (is_array($_POST['col'])) {
		//$sql = "SELECT ";
	foreach($_POST['col'] AS $value) {
			//$sql .= "{$value}, ";
	}
	//$sql  = substr($sql, 0, -2);
	//$sql .= " FROM table";
	//echo "sql= " . $sql . "<br /><br />\n";
	echo $value;
	} else {
		echo "No column was selected<br /><br />\n";
	}
	end testing
	*/
	$quantity = $_POST['quantity'];
	$item = $_POST['item'];
	echo "You chose ". $quantity . " " . $item . ".<br />";
	echo "Thank you!";


	$q="SELECT arrival_time as source_date, count( arrival_time ) AS count_source_date
			FROM `arrival_rate` a
			join incident b ON a.incident_id= b.incident_id
			WHERE (
			b.shortname ='".mysql_real_escape_string($_GET['shortname'])."'
	 and a.source_triagepic=1
		)
		GROUP BY DATE( arrival_time )
		ORDER BY DATE( arrival_time )";

	//for all sources
	$q_all="SELECT arrival_time as source_date, count( arrival_time ) AS count_source_date
		FROM `arrival_rate` a
		join incident b ON a.incident_id= b.incident_id
		WHERE (
	 b.shortname ='".mysql_real_escape_string($_GET['shortname'])."'
		)
		GROUP BY DATE( arrival_time )
		ORDER BY DATE( arrival_time )";

	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}

		while($row = $res->FetchRow());
		echo json_encode($count_source_date);
		echo json_encode($source_date);
		?>
<div id="container1"
	style="width: 300px; height: 200px; margin: 0 auto;">

	<form action="" method="post">
		<label><input type="radio" name="col[]" value="Status">Status</label><br>
		<label><input type="radio" name="col[]" value="Age">Age</label><br> <label><input
			type="radio" name="col[]" value="Gender">Gender</label><br> <input
			type="submit" name="submit" value="Submit"> <input type="submit"
			style="background-color: #fff; border: 0; text-decoration: underline; color: #00c;"
			name="submit" value=a
			href="index.php?mod=stat&act=test_arrival_rate\">

	</form>
</div>
;
<?php

$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);
echo json_encode($source_date);
echo json_encode($count_source_date);
echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "},\n" ;
echo "title: {\n" ;
echo "text: 'Arrival Rate by Date (new table) from $shortname'\n" ;
echo "},\n" ;
echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I: %M %p',\n" ;
echo "minute: '%I: %M %p',\n" ;
echo "hour: '%I',\n" ;
echo "day: '%e. %b',\n" ;
echo "week: '%e. %b',\n" ;
echo "month: '%b \'%y',\n" ;
echo "year: '%Y'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";
echo "title: {\n" ;
echo "text: 'People Count'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "tooltip: {\n" ;
//echo "enabled: true,\n" ;
//echo "formatter: function() {\n" ;
//echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
//echo "this.x +': '+ this.y;\n" ;
//echo "}\n" ;
echo "formatter: function() {\n" ;
echo "return ''+\n" ;
//echo "this.x +': years old'+ this.y +'count';\n" ;
echo "this.x + ': ' + this.y +'';\n" ;
echo "}\n" ;
echo "},\n" ;
echo "plotOptions: {\n" ;
echo "line: {\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true\n" ;
echo "},\n" ;
echo "enableMouseTracking: false\n" ;
echo "}\n" ;
echo "},\n" ;
echo "series: [{\n" ;
echo "name: '". $shortname;
echo "'";
echo ",\n";
echo "type: 'line',\n" ;
echo "data: data\n" ;
echo "}]\n" ;
echo "});\n" ;
echo "});\n" ;
//echo "</script>\n" ;
echo "Test area ";
}

/***************************************
 demographic charts
****************************************/
function shn_stat_pie_test() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	$groupID = $_SESSION['group_id'];
	//echo "Shortname: " .$shortname."";
	//echo "Group ID: " .$groupID."";

	//for starting date
	$q_start_date="SELECT arrival_time from arrival_rate a
					where ((source_triagepic >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
							ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	if($row === FALSE) {
    	//die(mysql_error());
		$startdate_has_data=false;
	}
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date
	$q_end_date="SELECT arrival_time from arrival_rate a
							where ((source_triagepic >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
							ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	if($row === FALSE) {
    	//die(mysql_error());
		$enddate_has_data=false;
	}
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));
	//for status
	/*
	$q_s="SELECT DISTINCT d.option_description as opt_status, count( opt_status ) as count_opt_status FROM person_status a
	join field_options d ON a.opt_status=d.option_code
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id where c.shortname = '".$shortname."'
	GROUP BY opt_status";
	*/
	//using status_count view
	$q_s="SELECT opt_status, count_opt_status, color as colors FROM status_count where shortname = '".mysql_real_escape_string($_GET['shortname'])."'";

	$res = $global['db']->Execute($q_s);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
		$status_has_data=false;
	}
	$status_has_data=true;
	$json_opt_status = array();
	$json_count_opt_status = array();
	$json_colors=array();
	do{
		$opt_status[] = $row['opt_status'];
		array_push($json_opt_status, $row['opt_status']);
		$count_opt_status[] = $row['count_opt_status'];
		array_push($json_count_opt_status, $row['count_opt_status']);
		$colors[] = $row['colors'];
		array_push($json_colors, $row['colors']);
		}
		while($row = $res->FetchRow());

		//for gender

		$q_g="SELECT DISTINCT d.option_description as opt_gender, count( opt_gender ) AS count_opt_gender
						FROM person_details a
						JOIN field_options d ON a.opt_gender = d.option_code
						JOIN person_uuid b ON a.p_uuid = b.p_uuid
						JOIN incident c ON c.incident_id = b.incident_id
						WHERE c.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
				GROUP BY option_description";

		//using view gender_count
		//$q_g="SELECT opt_gender, count_opt_gender from gender_count where shortname = '".$shortname."'";

		$res = $global['db']->Execute($q_g);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$gender_has_data=false;
	}
	$gender_has_data=true;
	$json_opt_gender = array();
	$json_count_opt_gender = array();
	do{
		$opt_gender[] = $row['opt_gender'];
		array_push($json_opt_gender, $row['opt_gender']);
		$count_opt_gender[] = $row['count_opt_gender'];
		array_push($json_count_opt_gender, $row['count_opt_gender']);
		}
		while($row = $res->FetchRow());

		//for pediatrics/adults

		$q_a="SELECT 'pediatrics' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
				join person_uuid b ON a.p_uuid= b.p_uuid
				JOIN incident c ON b.incident_id = c.incident_id
				where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 1 and a.years_old <= 17))
								UNION
								SELECT 'adult' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
								join person_uuid b ON a.p_uuid= b.p_uuid
								JOIN incident c ON b.incident_id = c.incident_id
								where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 18))";

		//using view 'age_group_age'
		//$q_a="select opt_age, count_opt_age from age_group_count where shortname = '".$shortname."'";

		$res = $global['db']->Execute($q_a);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$agegroup_has_data=false;
	}
	$agegroup_has_data=true;
	$json_opt_age = array();
	$json_count_opt_age = array();
	do{
		$opt_age[] = ucfirst($row['opt_age']);
		array_push($json_opt_age, $row['opt_age']);
		$count_opt_age[] =  $row['count_opt_age'];
		array_push($json_count_opt_age, $row['count_opt_age']);
		}
		while($row = $res->FetchRow());

		//for tp category
		/*
		$q_tp="SELECT distinct (triage_category) as opt_category, count(triage_category) as count_optcategory FROM `edxl_co_lpf` a
		join person_uuid b ON a.p_uuid= b.p_uuid
		JOIN incident c ON b.incident_id = c.incident_id
		where c.shortname = '".$shortname."'
		group by a.triage_category
		order by a.triage_category";
		*/

		//using view 'tp_zonecolor_count'
		$q_tp="SELECT opt_category, count_optcategory FROM `tp_zonecolor` where shortname = '".mysql_real_escape_string($_GET['shortname'])."'";

		$res = $global['db']->Execute($q_tp);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//echo 'No data available: ' . mysql_error();
     $TP_has_data=false;
	}
	$TP_has_data=true;
	$json_opt_category = array();
	$json_count_optcategory = array();
	do{
		$opt_category[] = $row['opt_category'];
		array_push($json_opt_category, $row['opt_category']);
		$count_optcategory[] = $row['count_optcategory'];
		array_push($json_count_optcategory, $row['count_optcategory']);
		}
		while($row = $res->FetchRow());

		?>
<div id="container" style="width: 300px; height: 400px;">
	<button id="button">Hide series</button>
	<button id="button">Export Chart</button>
</div>
;

<?php
$shortname = $_GET['shortname'];
echo "\n";

$json_opt_status = implode("','",$json_opt_status);
$json_count_opt_status = implode(",", $json_count_opt_status);
$json_colors = implode(",",$json_colors);

$json_opt_gender = implode("','",$json_opt_gender);
$json_count_opt_gender = implode(",", $json_count_opt_gender);

$json_opt_age = implode("','",$json_opt_age);
$json_count_opt_age = implode(",", $json_count_opt_age);

$json_opt_category = implode("','",$json_opt_category);
$json_count_optcategory = implode(",", $json_count_optcategory);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "colors = [$json_colors],\n";
echo "counts = [$json_count_opt_status],\n";
echo "names = " .json_encode($opt_status);

echo ",\n";
//echo "colors= ['#348017','#000000', '#990033','red','blue','#333333'],\n";
echo "j, data_status = [], chart;";
echo "\n";
echo "for(j=0; j<counts.length; j++) {\n";

echo "
					data_status.push({
					name: names[j],
					y: counts[j],
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_g = [$json_count_opt_gender],\n";
echo "names_g = " .json_encode($opt_gender);
echo ",\n";
echo "colors= ['#9900FF', '#0099FF','#CCFFCC'],\n";
echo "j, data_gender = [], chart;";
echo "\n";
echo "for(j=0; j<counts_g.length; j++) {\n";
//echo "data_gender.push([names_g[j], counts_g[j]]);\n";
echo "
					data_gender.push({
					name: names_g[j],
					y: counts_g[j],
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_a = [$json_count_opt_age],\n";
echo "names_a = " .json_encode($opt_age);
echo ",\n";
echo "colors= ['#FFCCCC', '#FFCC99'],\n";
echo "j, data_age = [], chart;";
echo "\n";
echo "for(j=0; j<counts_a.length; j++) {\n";
//echo "data_age.push([names_a[j], counts_a[j]]);\n";
echo "
					data_age.push({
					name: names_a[j],
					y: counts_a[j],
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_c = [$json_count_optcategory],\n";
echo "names_c = " .json_encode($opt_category);
echo ",\n";
//echo "colors: ['#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";
echo "j, data_category = [], chart;";
echo "\n";
echo "for(j=0; j<counts_c.length; j++) {\n";

//echo "data_category.push([names_c[j], counts_c[j]])\n";
echo "
				data_category.push({
				name: names_c[j],
				y: counts_c[j],
				color: names_c[j]
			});
				";
echo "}\n";


echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n";
/* add logo to the chart
 echo "
events: {
            load: function() {
                this.renderer.image('http://highsoft.com/images/media/Highsoft-Solutions-143px.png', 80, 40, 143, 57)
.add();
}
}\n" ;
*/
echo "},\n" ;
//echo "colors: ['pink', 'cyan', 'lime', 'cinnabar', 'orange', 'lilac', 'green', 'black', 'royal blue','blue','emerald', 'lime', 'yellow', 'red','gray','black'],\n";
//echo "colors: ['#FCDFFF', '#00FFFF', '#8AFB17', '#7E2217', '#F87217', '#D462FF', '#4CC417', '#000000', '#151B8D','#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";

echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "text: 'Arrivals During $name Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '20px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "y: 50,\n";
echo "text: 'From: $start_date to $end_date'\n" ;
echo "},\n" ;

echo "xAxis: {\n" ;
echo "type: 'datetime',\n" ;
echo "maxZoom:  3600000,\n";
echo "dateTimeLabelFormats: {\n" ;
echo "second: '%I:%M %p',\n" ;
echo "minute: '%I:%M %p',\n" ;
echo "hour: '%I:%M %p',\n" ;
echo "day: '%b %e',\n" ;
echo "week: '%b %e',\n" ;
echo "month: '%b %e',\n" ;
echo "year: '%b %e'\n" ;
echo "}\n" ;
echo "},\n" ;
echo "yAxis: {\n";
echo "allowDecimals: false,\n";
echo "title: {\n";
echo "text: 'Count of Persons Reported'\n";
echo "},\n";
echo "min: 0.6,\n";
echo "startOnTick: true,\n";
echo "showFirstLabel: true\n";
echo "},\n";
echo "tooltip: {\n";
echo "shared: true,\n";
echo "formatter: function() {\n";
echo "return '<b>'+ this.point.name +'</b>: '+ this.percentage +' %'\n";
echo "}";
echo "},\n";
echo "legend: {\n";

echo "pie: {\n";
echo "enabled: false,\n";
echo "align: 'left',\n";
echo "layout: 'horizontal',\n";
echo "verticalAlign: 'top',\n";
echo "floating: true,\n";
echo "backgroundColor: 'yellow'\n";
echo "}\n";
echo "},\n";

echo "plotOptions: {\n";
//display more details
echo "pie: {\n" ;
echo "allowPointSelect: true,\n" ;
echo "cursor: 'pointer',\n" ;
echo "dataLabels: {\n" ;
echo "enabled: true,\n" ;
echo "formatter: function() {\n" ;
echo "return '<b>'+ this.point.name +'</b><br/>'+\n" ;
echo "this.y;\n" ;
echo "this.percentage+' %';\n";
echo "}\n" ;
echo "}\n" ;
echo "},\n" ;

//test
echo "
				series: {
				events: {
				hide: function(event) {
				alert ('The series was just hidden');
                }
            }
        }
				";

echo "},\n";
//test
echo "series: [{\n" ;
//echo "name: '". $shortname;
echo "name: 'Gender";
echo "'";
echo ",\n";

//echo "{\n";
echo "type: 'pie',\n";
echo "data: data_gender,\n" ;
//echo "center: [200, 300],\n";
echo "center: ['15%', '50%'],\n";
echo "size: 200,\n";
echo "showInLegend: false,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";
echo "{\n";
echo "type: 'pie',\n";
echo "data: data_age,\n" ;
//echo "center: [550, 300],\n";
echo "center: ['35%', '50%'],\n";
echo "size: 200,\n";
echo "showInLegend: false,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";

echo "{\n";
echo "type: 'pie',\n";
echo "data: data_status,\n" ;
//echo "colors: ['#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";
//echo "colors: ['Green','Cyan', 'Yellow', 'Red', 'Grey', 'Black'],\n";
//echo "center: [900, 300],\n";
echo "center: ['60%', '50%'],\n";
echo "size: 200,\n";
echo "showInLegend: false,\n";
//echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "},\n";

//echo "{\n";
echo "{\n";
echo "name: 'Initial Triage Zones',\n";
echo "type: 'pie',\n";
echo "data: data_category,\n" ;
//echo "center: [1250, 300],\n";
echo "center: ['85%', '50%'],\n";
echo "size: 200,\n";
echo "showInLegend: false,\n";
echo "showLegend: true,\n";
echo "dataLabels: {\n";
echo "enabled: true\n";
echo "}\n";
echo "}],\n" ;


//add labels for each pie charts
//if ($has_data=true) then
echo "labels: {\n" ;
echo "items: [{\n" ;
if ($gender_has_data=='true'){
            echo "html: 'Gender',\n" ;
            echo "style: {\n" ;
            echo "left: '160px',\n" ;
            echo "top: '480px',\n" ;
            echo "fontSize: '16px',\n";
            echo "color: 'blue'\n" ;
            echo "}\n" ;
            echo "}\n";
			}
			if ($agegroup_has_data=='true'){
			echo ",{\n" ;
			echo "html: 'Age Group',\n" ;
			echo "style: {\n" ;
			echo "left: '510px',\n" ;
			echo "top: '480px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			echo "}\n" ;
			echo "}\n";
			}
			if ($status_has_data=='true'){
			echo ",{\n" ;
			echo "html: 'People Locator Status',\n" ;
			echo "style: {\n" ;
			echo "left: '830px',\n" ;
			echo "top: '480px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'blue'\n" ;
			echo "}\n" ;
			echo "}\n";
			}
			//if it's hospital-based
			if ($shortname=='cmax2010' or $shortname=='new') {
			echo ",{\n" ;
			echo "html:'Based on Initial Triage Zones ',\n" ;
			echo "style: {\n" ;
			echo "left: '1130px',\n" ;
			echo "top: '600px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'Blue'\n" ;
			echo "}\n" ;
			echo "}\n";
			}//end if
			//add button
			echo ",{\n" ;
			echo "html: '<li><a href=\"http://plstage/~lale/vesuvius/vesuvius/www/index.php\">Back to PS</a></li>',\n" ;
			echo "style: {\n" ;
			echo "left: '70px',\n" ;
			echo "top: '0px',\n" ;
			echo "fontSize: '16px',\n";
			echo "color: 'Red'\n" ;
			echo "}\n" ;
			echo "}\n";
			//the Export button
			echo ",{\n" ;
			echo "html: '<button id=\"button\">Export Chart</button>',\n" ;
			echo "style: {\n" ;
			echo "position:absolute,\n";
			echo "left: '70px',\n" ;
			echo "top: '20px',\n" ;
			echo "fontSize: '16px',\n";
			echo "z-index:2,\n";
			echo "color: 'Red'\n";
			echo "}\n" ;
			echo "}\n";

			echo "]},\n" ;
		 //for navigation
		 echo"
		navigation: {
		buttonOptions: {
		enabled: true
        }
		},
		exporting: {
		type: 'image/jpeg'
    }
		";
		 echo "})\n" ;//end chart
		 echo "})\n" ;//end document
		 // the button action
		 /*
		  echo "
		 var new_button = $('<button id="button">Click</button>');


		 $button = $('#button');
		 $button.click(function() {
    var series = chart.series[0];
		 		if (series.visible) {
        series.hide();
		 		$button.html('Show series');
		 		} else {
        series.show();
		 		$button.html('Hide series');
		 		}
		 		});
		 \n";
		 */
		 echo "
						</script>\n" ;
		 echo "Test area ";
}//end function
/***********************************************************
 arrivals rate- regular interval-from arrival rate table
***********************************************************/
function shn_stat_arrival_regular_interval() {
	global $global;
	shn_stat_menu();
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	//$item = $_GET['item'];

	//for starting date for all sources
	$q_start_date="SELECT arrival_time from arrival_rate a
									where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
									where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	//create a range dates

	$range = array();
	/*
	 if (is_string($start_date) === true) $start_date = strtotime($start_date);
	if (is_string($end_date) === true ) $end_date = strtotime($end_date);

	if ($start_date > $end_date) return createDateRangeArray($end_date, $start_date);

	do {
	$range[] = date('Y-m-d', $start_date);
	$start_date = strtotime("+ 1 day", $start_date);
	}
	while($start_date < $end_date);

	return $range;
	}
	echo $range;
	*/

	$q="SELECT (arrival_time) as source_date, count(*) as count_source_date from arrival_rate a
 				where ((source_all >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
			GROUP by date(arrival_time)";

	$q1="SELECT (arrival_time) as source_date1, count(*) as count_source_date1 from arrival_rate a
					where ((source_triagepic >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
								GROUP by date(arrival_time)";

	$q2="SELECT (arrival_time) as source_date2, count(*) as count_source_date2 from arrival_rate a
			where ((source_reunite >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
						GROUP by date(arrival_time)";

	$q3="SELECT (arrival_time) as source_date3, count(*) as count_source_date3 from arrival_rate a
						where ((source_website >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
    			GROUP by date(arrival_time)";

	$q4="SELECT (arrival_time) as source_date4, count(*) as count_source_date4 from arrival_rate a
			where ((source_pfif >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
				GROUP by date(arrival_time)";

	$q5="SELECT (arrival_time) as source_date5, count(*) as count_source_date5 from arrival_rate a
				where ((source_vanilla_email >= 1) and (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."')))
		GROUP by date(arrival_time)";

	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$res1 = $global['db']->Execute($q1);
	$row1 = $res1->FetchRow();

	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	$res5 = $global['db']->Execute($q5);
	$row5 = $res5->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date = array();
	$json_count_source_date = array();
	do{
		$source_date[] = (strtotime($row['source_date'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date, $row['source_date']);
		$count_source_date[] = $row['count_source_date'];
		array_push($json_count_source_date, $row['count_source_date']);
		}
		while($row = $res->FetchRow());


		if($row1 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date1 = array();
	$json_count_source_date1 = array();
	do{
		$source_date1[] = (strtotime($row1['source_date1'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date1, $row1['source_date1']);
		$count_source_date1[] = $row1['count_source_date1'];
		array_push($json_count_source_date1, $row1['count_source_date1']);
		}
		while($row1 = $res1->FetchRow());

		if($row2 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date2 = array();
	$json_count_source_date2 = array();
	do{
		$source_date2[] = (strtotime($row2['source_date2'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date2, $row2['source_date2']);
		$count_source_date2[] = $row2['count_source_date2'];
		array_push($json_count_source_date2, $row2['count_source_date2']);
		}
		while($row2 = $res2->FetchRow());

		if($row3 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date3 = array();
	$json_count_source_date3 = array();
	do{
		$source_date3[] = (strtotime($row3['source_date3'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date3, $row3['source_date3']);
		$count_source_date3[] = $row3['count_source_date3'];
		array_push($json_count_source_date3, $row3['count_source_date3']);
		}
		while($row3 = $res3->FetchRow());

		if($row4 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date4 = array();
	$json_count_source_date4 = array();
	do{
		$source_date4[] = (strtotime($row4['source_date4'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date4, $row4['source_date4']);
		$count_source_date4[] = $row4['count_source_date4'];
		array_push($json_count_source_date4, $row4['count_source_date4']);
		}
		while($row4 = $res4->FetchRow());

		if($row5 === FALSE) {
    	//die(mysql_error());
	}
	$json_source_date5 = array();
	$json_count_source_date5 = array();
	do{
		$source_date5[] = (strtotime($row5['source_date5'])*1000);
		date_default_timezone_set('UTC');
		array_push($json_source_date5, $row5['source_date5']);
		$count_source_date5[] = $row5['count_source_date5'];
		array_push($json_count_source_date5, $row5['count_source_date5']);
		}
		while($row5 = $res5->FetchRow());


		?>
<div
	id="container" style="width: 600px; height: 800px;"></div>
<button id="button">Remove first series</button>



<?php
$shortname = $_GET['shortname'];
echo "\n";
$json_source_date = implode("','",$json_source_date);
$json_count_source_date = implode(",", $json_count_source_date);

$json_source_date1 = implode("','",$json_source_date1);
$json_count_source_date1 = implode(",", $json_count_source_date1);

$json_source_date2 = implode("','",$json_source_date2);
$json_count_source_date2 = implode(",", $json_count_source_date2);

$json_source_date3 = implode("','",$json_source_date3);
$json_count_source_date3 = implode(",", $json_count_source_date3);

$json_source_date4 = implode("','",$json_source_date4);
$json_count_source_date4 = implode(",", $json_count_source_date4);

$json_source_date5 = implode("','",$json_source_date5);
$json_count_source_date5 = implode(",", $json_count_source_date5);

echo "\n";

echo "<script type=\"text/javascript\">\n";
echo "\n";
echo "var points = [$json_count_source_date],\n";
echo "dates = " .json_encode($source_date);
echo ",\n";
echo "i, data = [], chart;";
echo "\n";
echo "for(i=0; i<points.length; i++) {\n";
echo "data.push([dates[i], points[i]]);\n";
echo "}\n";

echo "\n";
echo "var points1 = [$json_count_source_date1],\n";
echo "dates1 = " .json_encode($source_date1);
echo ",\n";
echo "j, data1 = [], chart;";
echo "\n";
echo "for(j=0; j<points1.length; j++) {\n";
echo "data1.push([dates1[j], points1[j]]);\n";
echo "}\n";

echo "\n";
echo "var points2 = [$json_count_source_date2],\n";
echo "dates2 = " .json_encode($source_date2);
echo ",\n";
echo "k, data2 = [], chart;";
echo "\n";
echo "for(k=0; k<points2.length; k++) {\n";
echo "data2.push([dates2[k], points2[k]]);\n";
echo "}\n";

echo "\n";
echo "var points3 = [$json_count_source_date3],\n";
echo "dates3 = " .json_encode($source_date3);
echo ",\n";
echo "l, data3 = [], chart;";
echo "\n";
echo "for(l=0; l<points3.length; l++) {\n";
echo "data3.push([dates3[l], points3[l]]);\n";
echo "}\n";

echo "\n";
echo "var points4 = [$json_count_source_date4],\n";
echo "dates4 = " .json_encode($source_date4);
echo ",\n";
echo "m, data4 = [], chart;";
echo "\n";
echo "for(m=0; m<points4.length; m++) {\n";
echo "data4.push([dates4[m], points4[m]]);\n";
echo "}\n";

echo "\n";
echo "var points5 = [$json_count_source_date5],\n";
echo "dates5 = " .json_encode($source_date5);
echo ",\n";
echo "n, data5 = [], chart;";
echo "\n";
echo "for(n=0; n<points5.length; n++) {\n";
echo "data5.push([dates5[n], points5[n]]);\n";
echo "}\n";

echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {
renderTo: 'content',
zoomType: 'x',
spacingRight: 20
},
title: {
text: 'Arrival Rate for $name'
},
subtitle: {
text: document.ontouchstart === undefined ?
'Click and drag in the plot area to zoom in' :
'Drag your finger over the plot to zoom in'
},
xAxis: {
type: 'datetime',

title: {
text: null
}
},
yAxis: {
title: {
text: 'People Count'
},

min: 0.6,
startOnTick: false,
showFirstLabel: false
},
tooltip: {
shared: true
},
legend: {
enabled: false
},
plotOptions: {
series: {
pointStart: Date.UTC(2011, 11, 1),
pointInterval: 24 * 3600 * 1000 // one day
}
},

series: [{
type: 'area',
name: 'All Sources',

data:[points]
},{
type: 'area',
name: 'TriagePic',

data:[points1]
},{
type: 'area',
name: 'ReUnite',

data:[points2]
},{
type: 'area',
name: 'Website',

data:[points3]
},{
type: 'area',
name: 'PFIF',

data:[points4]
},{
type: 'area',
name: 'Vanilla Email',

data:[points5]
}\n";

echo "]\n" ;
echo "});\n" ;
echo "});\n" ;


echo "</script>\n" ;
}
/*****************************************/

function shn_stat_range_date() {

	global $global;

	//create a range dates

	$range = array();

	if (is_string($start_date) === true) $start_date = strtotime($start_date);
	if (is_string($end_date) === true ) $end_date = strtotime($end_date);
	if ($start_date > $end_date) return createDateRangeArray($end_date, $start_date);

	do {
	  $range[] = date('Y-m-d', $start_date);
	  $start_date = strtotime("+ 1 day", $start_date);
	}
	while($start_date < $end_date);

	return $range;
}



/***************************************
 status pie chart
****************************************/
function shn_stat_pie_status() {
global $global;
shn_stat_menu();

global $global;
require_once($global['approot']."/mod/lpf/lib_lpf.inc");

//shn_stat_menu();

$q = "
			SELECT *
			FROM incident
			WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
			";
$result = $global['db']->Execute($q);
if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}


	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$name=ucfirst($shortname);
	$groupID = $_SESSION['group_id'];
	//echo "Shortname: " .$shortname."";
	//echo "Group ID: " .$groupID."";

	//start and end date
	$q_start_date="SELECT arrival_time from arrival_rate a
						where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time asc limit 1";
	$res = $global['db']->Execute($q_start_date);
	$row = $res->FetchRow();
	$start_date= $row[0];
	$start_date = date('m/d/Y \a\t g:i A', strtotime($start_date));
	//for end date for all sources
	$q_end_date="SELECT arrival_time from arrival_rate a
						where (incident_id in (select incident_id from incident where shortname = '".mysql_real_escape_string($_GET['shortname'])."'))
			ORDER BY arrival_time desc limit 1";
	$res = $global['db']->Execute($q_end_date);
	$row = $res->FetchRow();
	$end_date= $row[0];
	$end_date = date('m/d/Y \a\t g:i A', strtotime($end_date));

	//for status

	//$q_s="SELECT DISTINCT d.option_description as opt_status, d.color as color, count( opt_status ) as count_opt_status FROM person_status a
	//join field_options d ON a.opt_status=d.option_code
	//join person_uuid b ON a.p_uuid= b.p_uuid
	//join incident c ON c.incident_id= b.incident_id where c.shortname = '".$shortname."'
	//GROUP BY opt_status";

	$q_s="SELECT DISTINCT f.option_description AS opt_status, COUNT( opt_status ) AS count_opt_status, g.option_description
				FROM person_status s
				LEFT JOIN field_options f ON s.opt_status = f.option_code
				LEFT JOIN field_options g ON f.option_code = g.option_code
				JOIN person_uuid p ON p.p_uuid= s.p_uuid
				JOIN incident i ON i.incident_id = p.incident_id
				WHERE i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
		AND g.field_name = 'opt_status_color'
		GROUP BY opt_status";


	//using status_count view
	//$q_s="SELECT opt_status, count_opt_status, color FROM status_count where incident_id = '".$shortname."'";

	$res = $global['db']->Execute($q_s);
	$row = $res->FetchRow();

	if($row === FALSE) {
    	//die(mysql_error());
		$status_has_data=false;
	}
	$status_has_data=true;
	$json_opt_status = array();
	$json_count_opt_status = array();
	//to match color
	$json_colors=array();
	do{
		$opt_status[] = $row['opt_status'];
		array_push($json_opt_status, $row['opt_status']);
		$count_opt_status[] = $row['count_opt_status'];
		array_push($json_count_opt_status, $row['count_opt_status']);
		//color
		//$color[] = $row['color'];
		//array_push($json_colors, $row['color']);

		$color[] =  $row['option_description'];

		array_push($json_colors, $row['option_description']);
		}
		while($row = $res->FetchRow());
		 
		//if ($shortname!=='testind') {
		//for gender
		$q_g="SELECT DISTINCT d.option_description as opt_gender, count( opt_gender ) AS count_opt_gender
		FROM person_details a
		JOIN field_options d ON a.opt_gender = d.option_code
		JOIN person_uuid b ON a.p_uuid = b.p_uuid
		JOIN incident c ON c.incident_id = b.incident_id
		WHERE c.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
		GROUP BY option_description";
		//using view gender_count
		//$q_g="SELECT opt_gender, count_opt_gender where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_g);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$gender_has_data=false;
	}
	$gender_has_data=true;
	$json_opt_gender = array();
	$json_count_opt_gender = array();
	do{
		$opt_gender[] = $row['opt_gender'];
		array_push($json_opt_gender, $row['opt_gender']);
		$count_opt_gender[] = $row['count_opt_gender'];
		array_push($json_count_opt_gender, $row['count_opt_gender']);
		}
		while($row = $res->FetchRow());


		//for pediatrics/adults
		$q_a="SELECT 'pediatrics' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			JOIN incident c ON b.incident_id = c.incident_id
			where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 1 and a.years_old <= 17))
			UNION
			SELECT 'adult' as opt_age, count(years_old) as count_opt_age FROM `person_details` a
			join person_uuid b ON a.p_uuid= b.p_uuid
			JOIN incident c ON b.incident_id = c.incident_id
			where (c.shortname = '".mysql_real_escape_string($_GET['shortname'])."' and (a.years_old IS NOT NULL and a.years_old >= 18))";
		//using view 'age_group_age'
		//$q_a="select opt_age, count_opt_age from age_group_count where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_a);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//die(mysql_error());
		$agegroup_has_data=false;
	}
	$agegroup_has_data=true;
	$json_opt_age = array();
	$json_count_opt_age = array();
	do{
		$opt_age[] = ucfirst($row['opt_age']);
		array_push($json_opt_age, $row['opt_age']);
		$count_opt_age[] =  $row['count_opt_age'];
		array_push($json_count_opt_age, $row['count_opt_age']);
		}
		while($row = $res->FetchRow());

		//for tp category
		$q_tp="SELECT distinct (triage_category) as opt_category, count(triage_category) as count_optcategory FROM `edxl_co_lpf` a
									join person_uuid b ON a.p_uuid= b.p_uuid
									JOIN incident c ON b.incident_id = c.incident_id
									where c.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
			group by a.triage_category
			order by a.triage_category";

		//using view 'tp_zonecolor_count'
		//$q_tp="SELECT opt_category, count_optcategory FROM `tp_zonecolor_count` where incident_id = '".$shortname."'";

		$res = $global['db']->Execute($q_tp);
		$row = $res->FetchRow();

		if($row === FALSE) {
    	//echo 'No data available: ' . mysql_error();
     $TP_has_data=false;
	}
	$TP_has_data=true;
	$json_opt_category = array();
	$json_count_optcategory = array();
	do{
		$opt_category[] = $row['opt_category'];
		array_push($json_opt_category, $row['opt_category']);
		$count_optcategory[] = $row['count_optcategory'];
		array_push($json_count_optcategory, $row['count_optcategory']);
		}
		while($row = $res->FetchRow());
		//}//end if event not=testIND
		?>


<div
	id="container" style="width: 100%; min-height: 100%;"></div>


<?php
$shortname = $_GET['shortname'];
echo "\n";

$json_opt_status = implode("','",$json_opt_status);
$json_count_opt_status = implode(",", $json_count_opt_status);
//color

$json_colors = implode("','",$json_colors);

$json_opt_gender = implode("','",$json_opt_gender);
$json_count_opt_gender = implode(",", $json_count_opt_gender);

$json_opt_age = implode("','",$json_opt_age);
$json_count_opt_age = implode(",", $json_count_opt_age);

$json_opt_category = implode("','",$json_opt_category);
$json_count_optcategory = implode(",", $json_count_optcategory);

echo "\n";

echo "<script type=\"text/javascript\">\n";

echo "var counts = [$json_count_opt_status],\n";
echo "names = " .json_encode($opt_status);
echo ",\n";
//echo "colors = [$json_colors],\n";
echo "colors = ['".$json_colors ;
echo "'], \n";


echo "j, data_status = [], chart;";
echo "\n";
echo "for(j=0; j<counts.length; j++) {\n";
echo "
					data_status.push({
					name: names[j],
					y: counts[j]/2,
					color: colors[j]
			});
					";
echo "}\n";

echo "var counts_g = [$json_count_opt_gender],\n";
echo "names_g = " .json_encode($opt_gender);
echo ",\n";
echo "colors_g= ['#9900FF', '#0099FF','#CCFFCC'],\n";
echo "j, data_gender = [], chart;";
echo "\n";
echo "for(j=0; j<counts_g.length; j++) {\n";
//echo "data_gender.push([names_g[j], counts_g[j]]);\n";

echo "
					data_gender.push({
					name: names_g[j],
					y: counts_g[j],
					color: colors_g[j]
			});
					";
echo "}\n";


echo "var counts_a = [$json_count_opt_age],\n";
echo "names_a = " .json_encode($opt_age);
echo ",\n";
echo "colors_a= ['#FFCCCC', '#FFCC99'],\n";
echo "j, data_age = [], chart;";
echo "\n";
echo "for(j=0; j<counts_a.length; j++) {\n";
//echo "data_age.push([names_a[j], counts_a[j]]);\n";
echo "
					data_age.push({
					name: names_a[j],
					y: counts_a[j],
					color: colors_a[j]
			});
					";
echo "}\n";

echo "var counts_c = [$json_count_optcategory],\n";
echo "names_c = " .json_encode($opt_category);
echo ",\n";
//echo "colors: ['#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";
echo "j, data_category = [], chart;";
echo "\n";
echo "for(j=0; j<counts_c.length; j++) {\n";

//echo "data_category.push([names_c[j], counts_c[j]])\n";
echo "
				data_category.push({
				name: names_c[j],
				y: counts_c[j],
				color: names_c[j]
			});
				";
echo "}\n";


echo "\$(document).ready(function() {\n" ;
echo "chart = new Highcharts.Chart({\n" ;
echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
//echo "backgroundColor: '#FCFFC5'\n";
echo "},\n" ;
//echo "colors: ['pink', 'cyan', 'lime', 'cinnabar', 'orange', 'lilac', 'green', 'black', 'royal blue','blue','emerald', 'lime', 'yellow', 'red','gray','black'],\n";
//echo "colors: ['#FCDFFF', '#00FFFF', '#8AFB17', '#7E2217', '#F87217', '#D462FF', '#4CC417', '#000000', '#151B8D','#348017','#54C571', '#FFFF00', '#FF0000', '#666362', '#000000'],\n";

echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "text: 'People Locator Status $description Event'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '20px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "y: 50,\n";
if ($startdate_has_data=true){
         echo "text: 'First Reported: $start_date, Last Reported: $end_date. The page refreshes every 120 seconds.'\n" ;
         //echo "text: ''\n" ;
		 }
		 echo "},\n" ;

	  echo "xAxis: {\n" ;
	  echo "type: 'datetime',\n" ;
		 echo "maxZoom:  3600000,\n";
		 echo "dateTimeLabelFormats: {\n" ;
		 echo "second: '%I:%M %p',\n" ;
		 echo "minute: '%I:%M %p',\n" ;
		 echo "hour: '%I:%M %p',\n" ;
		 echo "day: '%b %e',\n" ;
		 echo "week: '%b %e',\n" ;
		 echo "month: '%b %e',\n" ;
		 echo "year: '%b %e'\n" ;
		 echo "}\n" ;
		 echo "},\n" ;
		 echo "yAxis: {\n";
			echo "allowDecimals: false,\n";
			echo "title: {\n";
			echo "text: 'Count of Persons Reported'\n";
			echo "},\n";
			echo "min: 0.6,\n";
			echo "startOnTick: true,\n";
			echo "showFirstLabel: true\n";
			echo "},\n";
			echo "tooltip: {\n";
			echo "shared: true\n";
			echo "},\n";
			echo "legend: {\n";

			echo "pie: {\n";
			echo "enabled: false,\n";
			echo "align: 'left',\n";
			echo "layout: 'horizontal',\n";
			echo "verticalAlign: 'top',\n";
			echo "floating: true,\n";
			echo "backgroundColor: 'yellow'\n";
			echo "}\n";
			echo "},\n";

			echo "plotOptions: {\n";
			//display more details
		 echo "pie: {\n" ;
			echo "allowPointSelect: true,\n" ;
			echo "cursor: 'pointer',\n" ;
			echo "dataLabels: {\n" ;
			echo "enabled: true,\n" ;
			echo "formatter: function() {\n" ;
			echo "return '<b>'+ this.point.name +'</b><br/>'+\n" ;
			echo "this.y;\n" ;
			echo "}\n" ;
			echo "}\n" ;
			echo "},\n" ;

		 //test
		 echo "
				series: {
				events: {
				hide: function(event) {
				alert ('The series was just hidden');
                }
            }
        }
				";

		 echo "},\n";
	  //test
		 echo "series: [{\n" ;
		 //echo "name: '". $shortname;
		 echo "name: 'Status";
		 echo "'";
		 echo ",\n";

		 //echo "{\n";
		 echo "type: 'pie',\n";
		 echo "data: data_status,\n" ;
		 //echo "center: [200, 300],\n";
		 echo "center: ['50%', '50%'],\n";
		 echo "size: 200,\n";
		 echo "showInLegend: false,\n";
		 echo "showLegend: true,\n";
		 echo "dataLabels: {\n";
			echo "enabled: true\n";
			echo "}\n";
			//echo "}\n";

			echo "}],\n" ;


			//add labels for each pie charts
			//if ($has_data=true) then

			echo "labels: {\n" ;
			echo "items: [{\n" ;

			if ($gender_has_data=='true'){
            echo "html: '',\n" ;
            echo "style: {\n" ;
            echo "left: '160px',\n" ;
            echo "top: '600px',\n" ;
            echo "fontSize: '16px',\n";
            echo "color: 'blue'\n" ;
            echo "}\n" ;
            echo "}\n";
			}


			echo "]}\n" ;

			echo "});\n" ;


			echo "});\n" ;

			echo "</script>\n" ;
			//echo "Test area ";
}
/*************************
 Img stats
**************************/
function shn_stat_image() {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");


	//shn_stat_menu();

	$q = "
				SELECT *
				FROM incident
				WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
				";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}


	echo '
		<script src="res/js/sorttable.js"></script>
		';
	//path to directory to scan
	//$directory = "../../www/res/img/";
	$directory = "../mod/stat/pl_images/";
	//echo getcwd() . "\n";
	//get all image files with a .jpg extension.
	//$images = glob($directory . "*.jpg");
	$images = glob($directory . "{*.jpeg,*.gif,*.png}", GLOB_BRACE);
	$arr_listImages=array();
	$arr_filesz=array();
	foreach($images as $image){
        $listImages=$image;

        if($listImages != null){

			if (is_readable($listImages)) {
				$file_sz=filesize($listImages);
			}
			$res =substr_compare($listImages, "jpeg", -4, 4);
			$res1 =substr_compare($listImages, "png", -3, 3);
			//echo $res;
			if ($res==0){
			$listImages=substr($listImages, -15);
			}
			if($res1==0){
			$listImages=substr($listImages, -14);
			}

		}
		//echo $listImages;
		//echo ": ";
		//echo $file_sz;
		//echo " bytes";
		//echo '</br>';

		$arr_listImages[]=$listImages;
		$arr_filesz[]=$file_sz;
		}
		//print_r("images names: \n");
		//print_r($arr_listImages);
		//print_r("file size: \n");
		//print_r($arr_filesz);

		//$arr_listImages[] = $listImages;
		//array_push($arr_listImages, $listImages);
		//$arr_filesz[] = $file_sz;
		//array_push($arr_filesz, $file_sz);
		//}
		//echo "listImages array:\n";
		//echo $listImages;
		//echo "\n file_sz array:\n";
		//echo $file_sz;
		//$json_filename = array();
		//$json_filesz = array();
		//do{
		//$json_filename[] = $listImages;
		//array_push($json_filename, $listImages);
		//$json_filesz[] = $file_sz;
		//array_push($json_filesz, $file_sz);
		//}
		//while($listImages!==NULL);
		//}
			
		//$json_filename = implode("','",$json_filename);
		//$json_filesz = implode(",", $json_filesz);
		?>
<div
	id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>
;
<?php
$arr_listImages = implode("','",$arr_listImages);
$arr_filesz = implode(",", $arr_filesz);

//echo "\n";
//print_r($arr_listImages);
//echo "\n";
//print_r($arr_filesz);

//echo json_encode($arr_listImages);
//echo "\n";
//echo json_encode($arr_filesz);
//}

echo "\n";
echo "<script type=\"text/javascript\"> \n" ;




echo "var sz = $arr_filesz\n" ;
echo "name =  $arr_listImages\n" ;
echo "i, data = [], chart;\n" ;
//echo "for(i=0; i<sz.length; i++) {\n" ;
//echo "data.push([name[i], sz[i]])\n" ;
//echo"}\n";
	


echo "\$(document).ready(function() {\n";
echo "var chart = new Highcharts.Chart({\n" ;

echo "chart: {\n" ;
echo "renderTo: 'content'\n" ;
echo "defaultSeriesType: 'column'\n" ;
echo "},\n" ;

echo "title: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '28px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "text: 'Image Stats $description'\n" ;
echo "},\n" ;
echo "subtitle: {\n" ;
echo "style: {\n";
echo "color: 'Blue',\n";
echo "fontSize: '20px',\n";
echo "fontWeight: 'bold'\n";
echo "},\n";
echo "margin: 45,\n";
echo "y: 50,\n";
//if ($startdate_has_data=true){
//echo "text: 'First Reported: $start_date, Last Reported: $end_date. This page refreshes every 120 seconds'\n" ;
echo "text: 'Image Stats'\n" ;
echo "},\n";

echo "xAxis: {\n" ;
echo "title: {\n" ;
echo "text: 'Status'\n" ;
echo "},\n" ;
echo "categories: ['". $arr_listImages;
echo "']\n";
 
echo "},\n" ;
echo "yAxis: {\n" ;
echo "allowDecimals: false,\n";

echo "stackLabels: {\n";
echo "enabled: true,\n";
echo "style: {\n";
echo "fontWeight: 'bold',\n";
echo "color: (Highcharts.theme && Highcharts.theme.textColor) || 'black'\n";
echo "}\n";
echo "},\n";
echo "title: {\n" ;
echo "text: 'File Size'\n" ;
echo "}\n" ;
echo "},\n" ;

echo "
					tooltip: {
					shared: true
	},
					legend: {
					column: {
					align: 'right',
					backgroundColor: '#FCFFC5',
					enabled: true
	}
	},
					\n";
echo "plotOptions: {\n" ;
echo "pointPadding: 0,\n";
echo "column: {
					stacking: 'normal',
					dataLabels: {
					enabled: true,
					color: (Highcharts.theme && Highcharts.theme.dataLabelsColor) || 'black'
            }
         	}
           },\n" ;
echo "series: [{\n" ;
//echo "name: '". $shortname;
//echo "'";
//echo ",\n";
echo "data: [". $arr_filesz;
echo "]";
echo "\n}]\n" ;
echo "});\n";
echo "});\n";

/*
 echo "
chart: {
            renderTo: 'container',
defaultSeriesType: 'column'
},
title: {
            text: 'Statistics'
},
subtitle: {
            text: ''
},
xAxis: {
            categories: ['green','black', 'purple', 'blue', 'yellow'],
labels: {
                rotation: 0, align: 'center',
style: {
                    color: '#6D869F',
fontWeight: 'bold'
}
}
},
yAxis: {
            min: 0,
title: {
                text: 'count'
}
},
legend: {
            layout: 'vertical',
backgroundColor: '#FFFFFF',
align: 'left',
verticalAlign: 'top',
x: 0,
y: 50
},
plotOptions: {
            column: {
                pointPadding: 0.2,
borderWidth: 0,
events: {
                    show: function() {
                        var chart = this.chart,
series = chart.series,
i = series.length,
otherSeries;

while(i--) {
                            otherSeries = series[i];
if (otherSeries != this && otherSeries.visible) {
                                otherSeries.hide();
}
}
}
}
}
},
series: [{
            name: 'series 1',
data: [846290,10864,69,710,406652]
}]
});
});
";
*/
}


/***************************************/
function shn_stat_transit() {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	//shn_stat_menu();

	$q = "
			SELECT *
			FROM incident
			WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
			";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}
	echo '
 		<script src="res/js/sorttable.js"></script>

 		<style>
 		table thead td, table tr th {
 		text-align: center;
 		padding: .25em;
 		background: #AAA;
 		color: white;
 		font-size: 100%;
 		font-weight: bold;
 		border-radius: 5px;
 		box-shadow: inset 2px 2px 6px rgba(255,255,255,0.6), inset -2px -2px 6px rgba(192,191,191,0.1);
 		-webkit-touch-callout: none;
 		-webkit-user-select: none;
 		-khtml-user-select: none;
 		-moz-user-select: none;
 		-ms-user-select: none;
 		-o-user-select: none;
 		user-select: none;
 		cursor: default;
 		text-shadow: 1px 1px rgba(0, 0, 0, 0.5);
}

 		.odder {
 		background-color: #E0E0E7;
 		-webkit-border-radius: 5px;
 		-moz-border-radius: 5px;
 		border-radius: 5px;
 		box-shadow: inset 2px 2px 6px rgba(255,255,255,0.6), inset -2px -2px 6px rgba(192,191,191,0.1);
}


 		table { width: 100%; }

 		td { text-align: center; }

 		</style>
 		<div style="margin: 20px;">
 		<h1>Patient Transit Times '.$description.'</h1>

						<ul>
						<li>click on a column header to sort by that column</li>
						<li>only shows last 100 updated persons</li>
						<li>page refreshed every 120 seconds</li>
						<li><a href="index.php?mod=stat&act=transitCsv&stream=text">Download tabular data as a .csv file</a></li>
						<li>Age may be used to indicate Ambulance #</li>
						<li>Creation Time may denote Departure time</li>
						<li>Last Updated may denote Arrival time</li>
						</ul>
						<table id="regLog" class="sortable">
						<thead>	<tr>
						<th>Full Name</th>
						<th>Family Name</th>
						<th>Age</th>
						<th>Record ID</th>
						<th>Creation Time</th>
						<th>Last Updated</th>
						<th>Delta</th>
						</thead>
						<tbody>
						';

	$count = 1;
	$q = "
						SELECT *, TIMEDIFF(s.last_updated, s.creation_time)
						FROM `person_status` s, incident i, person_uuid p, person_details d
						WHERE s.opt_status = 'fnd'
						AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
			AND p.incident_id = i.incident_id
			AND s.p_uuid = p.p_uuid
			AND d.p_uuid = p.p_uuid
			ORDER BY s.last_updated DESC
			LIMIT 100;
			";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 1");
}
while(!$result == NULL && !$result->EOF) {

		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo '<tr>
			<td '.$odd.'>'.$result->fields["full_name"].'</td>
		<td '.$odd.'>'.$result->fields["family_name"].'</td>
		<td '.$odd.'>'.$result->fields["years_old"].'</td>
		<td '.$odd.'><a href="'.makePersonUrl($result->fields["p_uuid"]).'" target="_blank">'.$result->fields["p_uuid"].'</a></td>
		<td '.$odd.'>'.$result->fields["creation_time"].'</td>
		<td '.$odd.'>'.$result->fields["last_updated"].'</td>
		<td '.$odd.'>'.$result->fields["TIMEDIFF(s.last_updated, s.creation_time)"].'</td>
		</tr>';
		$result->MoveNext();
		$count++;
	}
	echo '
		</tbody>
		</table>
		</div>
		';
}




function shn_text_stat_transitCsv() {

	global $global;
	require_once($global['approot']."/mod/lpf/lib_lpf.inc");

	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."' ;
		";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 0");
}
if($result != NULL && !$result->EOF) {
		$row = $result->FetchRow();
		$description = $row["description"];
	} else {
	  $description = "";
	}

	$csv = "Full Name,Family Name,Age,Record ID,Departing Time,Arrival Time,Delta\n";

	$count = 1;
	$q = "
		SELECT *, TIMEDIFF(s.last_updated, s.creation_time)
		FROM `person_status` s, incident i, person_uuid p, person_details d
		WHERE s.opt_status = 'fnd'
		AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."'
		AND p.incident_id = i.incident_id
		AND s.p_uuid = p.p_uuid
		AND d.p_uuid = p.p_uuid
		ORDER BY s.last_updated DESC
		LIMIT 100;
		";
	$result = $global['db']->Execute($q);
	if($result === false) {
daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "transit table 1");
}
while(!$result == NULL && !$result->EOF) {

		$csv .= $result->fields["full_name"].",".$result->fields["family_name"].",".$result->fields["years_old"].",".$result->fields["p_uuid"].",".$result->fields["creation_time"].",".$result->fields["last_updated"].",".$result->fields["TIMEDIFF(s.last_updated, s.creation_time)"]."\n";

		$result->MoveNext();
		$count++;
	}
	header("Content-type: application/csv");
	header("Content-Disposition: attachment; filename=transit_times.csv");
	header("Pragma: no-cache");
	header("Expires: 0");
	echo $csv;
}


