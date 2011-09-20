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
		<script type=\"text/javascript\" src=\"res/js/stat/jquery-1.5.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/highcharts.src.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/highcharts.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/dark-green.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/grid.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/gray.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/excanvas.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/exporting.js\"></script>
		<script type=\"text/javascript\" src=\"res/js/stat/dark-blue.js\"></script>
		";
		$shortname = $_GET['shortname'];
		echo "People Statistics for $shortname:\n";
		echo "\n";
		echo "Please select from the links below for avalailable statistics:\n";				
		
		if ($shortname=="cmax2010"){
		echo "
		<ul>				
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>
			<li><a href=\"index.php?mod=stat&act=gender\">Gender</a></li>
			<li><a href=\"index.php?mod=stat&act=age\">Age</a></li>						
			<li><a href=\"index.php?mod=stat&act=TP_sub_byhour\">TP-Arrival Rate by Hour at Suburban Hospital</a></li>	
			<li><a href=\"index.php?mod=stat&act=TP_sub_byminute\">TP-Arrival Rate by Minute at Suburban Hospital</a></li>			
			<li><a href=\"index.php?mod=stat&act=TP_sub_stacked_status_byhour\">TP-Status by Hour at Suburban Hospital</a></li>		
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		};
		if ($shortname=="sendai2011"){
		echo "
		<ul>					
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>
			<li><a href=\"index.php?mod=stat&act=gender\">Gender</a></li>
			<li><a href=\"index.php?mod=stat&act=age\">Age</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_bydate\">Arrival Rate by Date</a></li>	
			<li><a href=\"index.php?mod=stat&act=arrival_byhour\">Arrival Rate by Hour (zoomable)</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_bydate_status\">Arrival Rate by Date Combined with Status</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_byhour_status\">Arrival Rate by Hour  Combined with with Status</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		};
		if ($shortname=="hepl"){
		echo "
		<ul>					
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>
			<li><a href=\"index.php?mod=stat&act=gender\">Gender</a></li>
			<li><a href=\"index.php?mod=stat&act=age\">Age</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_bydate\">Arrival by Date</a></li>			
			<li><a href=\"index.php?mod=stat&act=arrival_byhour\">Arrival by Hour (zoomable) </a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_bydate_status\">Arrival Rate by Date Combined with Status</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_byhour_status\">Arrival Rate by Hour Combined with with Status</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		};
		if($shortname=="joplin"){
		echo "
		<ul>					
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>
			<li><a href=\"index.php?mod=stat&act=gender\">Gender</a></li>
			<li><a href=\"index.php?mod=stat&act=age\">Age</a></li>				
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		};
		if($shortname=="christchurch"){
		echo "
		<ul>					
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>	
			<li><a href=\"index.php?mod=stat&act=arrival_bydate\">Arrival Rate by Date</a></li>			
			<li><a href=\"index.php?mod=stat&act=arrival_byhour\">Arrival Rate by Hour (zoomable)</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_bydate_status\">Arrival Rate by Date Combined with Status</a></li>
			<li><a href=\"index.php?mod=stat&act=arrival_byhour_status\">Arrival Rate by Hour  Combined with with Status</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		};
		}
/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_stat_default() {
	global $global;
	shn_stat_menu();
	//echo "People Statistics for  ";
	//echo $_GET['shortname'];
}	

/**********************
 * the status action...
 * @access public
 * @return void
 *********************/
function shn_stat_status() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	
	$shortname = $_GET['shortname'];
	$q="SELECT DISTINCT (opt_status), count( opt_status ) as count_opt_status FROM person_status a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id where c.shortname like '".$shortname."'
	GROUP BY opt_status";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	
	if($row === FALSE) {
    	die(mysql_error()); 
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
	?>
	<div id="content" style=" height:100%;"></div>;
	<?php
	$shortname = $_GET['shortname'];
	$json_opt_status = implode("','",$json_opt_status);
	$json_count_opt_status = implode(",", $json_count_opt_status);		
	echo "\n";
	echo "<script type=\"text/javascript\">\n" ;
	echo "\$(document).ready(function() {\n" ; 	
	echo "chart = new Highcharts.Chart({\n" ;
		echo "chart: {";
			echo "renderTo: 'content',\n" ;
			echo "defaultSeriesType: 'column'\n" ;
				echo "},\n" ;
		echo "title: {\n" ;
			echo "text: 'PL Status Statistics'\n" ;
			echo "},\n" ;
		echo "subtitle: {\n" ;
			echo "text: ''\n" ;
					echo "},\n" ;
		echo "xAxis: {\n" ;			
			echo "categories: ['". $json_opt_status;	
			echo "'], \n";			
			echo "style: {\n" ;
                    echo "color: '#6D869F',\n" ;
                    echo "fontWeight: 'bold'\n" ;
                  echo "}\n" ;	
				echo "}\n" ;				
			echo ",\n" ;
		echo "yAxis: {\n" ;
			echo "min: 0,\n" ;
			echo "title: {\n" ;
				echo "text: 'People Count'\n" ;
					echo "}\n" ;
				echo "},\n" ;
		echo "legend: {\n" ;
			echo "layout: 'vertical',\n" ;
			echo "backgroundColor: '#FFFFFF',\n" ;
			echo "align: 'left',\n" ;
			echo "verticalAlign: 'top',\n" ;
			echo "x: 0,\n" ;
			echo "y: 50,\n" ;
            echo "},\n" ;
		/*
		echo "tooltip {\n" ;
			echo "formatter: function() {\n" ;
            echo "return ''+\n" ;
				echo "this.x +': '+ this.y +'';\n" ;
								echo "}\n" ;
				echo "},\n" ;
		*/
		echo " plotOptions: {\n" ;
			echo "column: {\n" ;
            echo "pointPadding: 0.2,\n" ;
            echo "borderWidth: 0\n" ;
					echo "}\n" ;
					echo "},\n" ;
        echo "series: {\n" ;
            echo "events: {\n" ;
                echo " show: (function() {\n" ;
                    echo "var chart = this.chart,\n" ;
                    echo "series = chart.series,\n" ;
                    echo "i = series.length,\n" ;
                    echo "otherSeries;\n" ;
                    echo "while(i--) {\n" ;
                        echo "otherSeries = series[i];\n" ;
                        echo " if (otherSeries != this && otherSeries.visible) {\n" ;
                            echo "otherSeries.hide();\n" ;
                              echo "}\n" ;
							echo "}\n" ;                        
						echo "})\n" ;
                   echo "}\n" ;
				
            echo "},\n" ;
		echo "series: [{\n" ;
			echo "name: '". $shortname; 
			echo "'";
			echo ",\n"; 							
			echo "data: [". $json_count_opt_status;		
			echo "]";
			echo "\n}]\n" ;
			echo "});\n" ; 
	echo "});\n" ;             
	echo "</script>\n" ;	
}
/*******************
* The gender action
*******************/ 
function shn_stat_gender() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	$q="SELECT DISTINCT (opt_gender), count(opt_gender) as count_gender FROM person_details a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id 
	where c.shortname like '".$shortname."'
	GROUP BY opt_gender";	
		
	$res = $global['db']->Execute($q);	
	$row = $res->FetchRow();	
	if($row === FALSE) {
    	die(mysql_error()); 
	}
	$json_opt_gender = array();
	$json_count_gender = array();
	do{
		$opt_gender[] = $row['opt_gender'];
		array_push($json_opt_gender, $row['opt_gender']);
		$count_gender[] = $row['count_gender'];
		array_push($json_count_gender, $row['count_gender']);
		}	
	while($row = $res->FetchRow());			
	?>		
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php
	$shortname = $_GET['shortname'];	
	$json_opt_gender = implode("','",$json_opt_gender);
	$json_count_gender = implode(",", $json_count_gender);
	echo $json_count_gender; 
	echo "<script type=\"text/javascript\"> \n" ;
	echo "\$(document).ready(function() {\n" ; 	
	echo "chart = new Highcharts.Chart({\n" ;
		echo "chart: {";
			echo "renderTo: 'content',\n" ;
			echo "defaultSeriesType: 'column'\n" ;
				echo "},\n" ;
		echo "title: {\n" ;
			echo "text: 'PL Gender Statistics'\n" ;
			echo "},\n" ;
		echo "subtitle: {\n" ;
			echo "text: ''\n" ;
					echo "},\n" ;
		echo "xAxis: {\n" ;			
			echo "categories: ['". $json_opt_gender;	
			echo "'], \n";
			echo "style: {\n" ;
                    echo "color: '#6D869F',\n" ;
                    echo "fontWeight: 'bold'\n" ;
                  echo "}\n" ;	
				echo "}\n" ;
			echo ",\n" ;
		echo "yAxis: {\n" ;
			echo "min: 0,\n" ;
			echo "title: {\n" ;
				echo "text: 'People Count'\n" ;
					echo "}\n" ;
				echo "},\n" ;
		echo "legend: {\n" ;
			echo "layout: 'vertical',\n" ;
			echo "backgroundColor: '#FFFFFF',\n" ;
			echo "align: 'left',\n" ;
			echo "verticalAlign: 'top',\n" ;
			echo "x: 0,\n" ;
			echo "y: 50,\n" ;
            echo "},\n" ;
		
		/*echo "tooltip {\n" ;
			echo "formatter: function() {\n" ;
            echo "return ''+\n" ;
				echo "this.x +': '+ this.y +'';\n" ;
								echo "}\n" ;
				echo "},\n" ; 
		*/
		echo " plotOptions: {\n" ;
			echo "column: {\n" ;
            echo "pointPadding: 0.2,\n" ;
            echo "borderWidth: 0\n" ;
					echo "}\n" ;
					echo "},\n" ;
        echo "series: {\n" ;
            echo "events: {\n" ;
                echo " show: (function() {\n" ;
                    echo "var chart = this.chart,\n" ;
                    echo "series = chart.series,\n" ;
                    echo "i = series.length,\n" ;
                    echo "otherSeries;\n" ;
                    echo "while(i--) {\n" ;
                        echo "otherSeries = series[i];\n" ;
                        echo " if (otherSeries != this && otherSeries.visible) {\n" ;
                            echo "otherSeries.hide();\n" ;
                              echo "}\n" ;
							echo "}\n" ;                        
						echo "})\n" ;
                   echo "}\n" ;
                echo "},\n" ;
		echo "series: [{\n" ;
			echo "name: '". $shortname; 
			echo "'";
			echo ",\n"; 						
			echo "data: [". $json_count_gender;		
			echo "]";
			echo "\n}]\n" ;
			echo "});\n" ; 
	echo "});\n" ;             
	echo "</script>\n" ;
}
/***********************************************************
The report rate by date for sendai, christchurch & hepl only
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
	where (c.shortname like '".$shortname."' and a.source_date >'2011-01-01')
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
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
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
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Date'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b',\n" ;
            echo "hour: '%e. %b',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
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
* For sendai2011, hepl and christchurch event
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
	where (c.shortname like '".$shortname."' and a.source_date >'2011-01-01')
	GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date)";	
	}
	//for hepl
	if($shortname=="hepl") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id 
	where (c.shortname like '".$shortname."' and a.source_date >'2010-01-11')
	GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date)";	
	}
	//for christchurch
	if($shortname=="christchurch") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id 
	where (c.shortname like '".$shortname."' and a.source_date >'2011-02-20')
	GROUP BY DATE(source_date),HOUR(source_date) order by DATE(source_date),HOUR(source_date)";	
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
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
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
         echo "renderTo: 'content',\n" ;   
		 echo "zoomType: 'x',\n";
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Hour'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
		 echo "maxZoom:  3600000,\n";
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b',\n" ;
            echo "hour: '%e. %b',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
    echo "yAxis: {\n";
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
	?>	
	<div id="content" style="width: 500 px; height: 300px; margin: 0 auto; background-image:url('ajax-loader2.gif');background-repeat:no-repeat;"></div>
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
			echo "renderTo: 'content',\n";
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
/** The Age-range function
 * @access public
 * @return void
 */
function shn_stat_age() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	
	$q="SELECT '1-10 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 1 and a.years_old <= 10))
	UNION
	SELECT '11-20 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 11 and a.years_old <= 20))
	UNION
	SELECT '21-30 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 21 and a.years_old <= 30))
	UNION
	SELECT '31-40 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 31 and a.years_old <= 40))
	UNION
	SELECT '41-50 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 41 and a.years_old <= 50))
	UNION
	SELECT '51-60 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id	
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 51 and a.years_old <= 60))
	UNION
	SELECT '61-70 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 61 and a.years_old <= 70))
	UNION
	SELECT '71-10 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 71 and a.years_old <= 80))
	UNION
	SELECT '81-90 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid 
	JOIN incident c ON b.incident_id = c.incident_id
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 81 and a.years_old <= 90))
	UNION
	SELECT '91-100 yrs old' as age_range, count(years_old) as count_age FROM `person_details` a
	join person_uuid b ON a.p_uuid= b.p_uuid
	JOIN incident c ON b.incident_id = c.incident_id	
	where (c.shortname like '".$shortname."' and (a.years_old IS NOT NULL and a.years_old >= 91 and a.years_old <= 100))";
		
	$res = $global['db']->Execute($q);
	
	$row = $res->FetchRow();
	 
	if($row === FALSE) {
    	die(mysql_error()); 
	}
	$json_age_range = array();
	$json_count_age	= array();
	do{
		$age_range[] = $row['age_range'];
		array_push($json_age_range, $row['age_range']);
		$count_age[] = $row['count_age'];
		array_push($json_count_age, $row['count_age']);
		}	
	while($row = $res->FetchRow());
	// mysql_close($link); 	
	?>	
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php	
	$shortname = $_GET['shortname'];
	echo "\n";	
	$json_age_range = implode("','",$json_age_range);
	$json_count_age = implode(",", $json_count_age);
	
	echo "<script type=\"text/javascript\">\n";

	echo "\$(document).ready(function() {\n" ; 
	echo "chart = new Highcharts.Chart({\n" ;
      echo "chart: {\n" ;
         echo "renderTo: 'container',\n" ;
         echo "defaultSeriesType: 'column'\n" ;
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Age Statistics'\n" ;
      echo "},\n" ;
      echo "subtitle: {\n" ;
         echo "text: ''\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
        echo "title: {\n" ;
            echo "text: 'Age Range'\n" ;
         echo "},\n" ;        
		echo "categories: ['". $json_age_range;	
			echo "'], \n";
      	echo "style: {\n" ;
                              echo "color: '#6D869F',\n" ;
                              echo "fontWeight: 'bold'\n" ;
                  echo "}\n" ;	
	echo "},\n" ;
      echo "yAxis: {\n" ;
         echo "min: 0,\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "},\n" ;
	echo "minPadding: 0.01,\n" ;
        echo "maxPadding: 0.01\n" ;
      echo "},\n" ;
      echo "legend: {\n" ;
         echo "layout: 'vertical',\n" ;
         echo "backgroundColor: '#FFFFFF',\n" ;
         echo "align: 'left',\n" ;
         echo "verticalAlign: 'top',\n" ;
         echo "x: 0,\n" ;
         echo "y: 50,\n" ;
         
      echo "},\n" ;
      echo "tooltip: {\n" ;
         echo "formatter: function() {\n" ;
            echo "return ''+\n" ;
               //echo "this.x +': years old'+ this.y +'count';\n" ;
			   echo "this.x + ': ' + this.y +'';\n" ;
         echo "}\n" ;
      echo "},\n" ;
      echo "plotOptions: {\n" ;
         echo "column: {\n" ;
            echo "pointPadding: 0.1,\n" ;
            echo "borderWidth: 0\n" ;
         echo "}\n" ;
      echo "},\n" ;    
	echo "series: [{\n" ;         
		echo "name: '". $shortname;
		echo "'";
		echo ",\n"; 		
		echo "data: [". $json_count_age;
		 echo "]";
      	    echo "\n}]\n" ;  
         echo "});\n" ; 
   echo "});\n" ;
echo "</script>\n" ;
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
function shn_stat_test() {
	global $global;
	shn_stat_menu();
	echo "test using php & js combined";
	//include('test.php'); 
	echo file_get_contents("test.php");
}
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
	$q="SELECT when_sent as update_time, count(when_sent) as count_update_time FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent)
	ORDER BY DATE( when_sent ) , HOUR(when_sent)";
		
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
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
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
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Hour'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b %H %M',\n" ;
            echo "minute: '%e. %b %H %M',\n" ;
            echo "hour: '%e. %b %H',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "}\n" ;
     echo "},\n" ;
     /*echo "tooltip: {\n" ;
         echo "enabled: false,\n" ;
         echo "formatter: function() {\n" ;
            echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
               echo "this.x +': '+ this.y;\n" ;
         echo "}\n" ;
      echo "},\n" ;
	  
	*/
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
function shn_stat_TP_nnmc_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	//old table
	//$q="SELECT update_time, count(update_time) as count_update_time 
	//FROM `mpres_log` where email_subject like 'New Disaster Patient%nnmc%' 
	//GROUP BY DATE(update_time), HOUR(update_time) order by DATE(update_time), HOUR(update_time)";
	$q="SELECT when_sent as update_time, count(when_sent) as count_update_time FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent) 
	ORDER BY DATE( when_sent ) , HOUR(when_sent)";
		
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
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
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
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Hour'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b %H %M',\n" ;
            echo "minute: '%e. %b %H %M',\n" ;
            echo "hour: '%e. %b %H',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "}\n" ;
     echo "},\n" ;
     /*
	 echo "tooltip: {\n" ;
         echo "enabled: false,\n" ;
         echo "formatter: function() {\n" ;
            echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
               echo "this.x +': '+ this.y;\n" ;
         echo "}\n" ;
      echo "},\n" ;
	  */
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
		echo "',";
		//echo ",";
		echo "\n";
		echo "type: 'areaspline',";
		echo "\n";
        echo "data: data\n" ;         
        echo "}]\n" ;
   echo "});\n" ; 
echo "});\n" ; 
echo "</script>\n" ;	
}
function shn_stat_TP_sub_byminute() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	//from newer table
	$q="SELECT when_sent as update_time, count(when_sent) as count_update_time FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent), MINUTE( when_sent ) 
	ORDER BY DATE( when_sent ) , HOUR(when_sent), MINUTE( when_sent )";
		
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
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
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
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Minute'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b %H %M',\n" ;
            echo "hour: '%e. %b %H',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "}\n" ;
     echo "},\n" ;
     /*echo "tooltip: {\n" ;
         echo "enabled: false,\n" ;
         echo "formatter: function() {\n" ;
            echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
               echo "this.x +': '+ this.y;\n" ;
         echo "}\n" ;
      echo "},\n" ;*/
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
		echo "'";
		echo ",\n";
		echo "type: 'areaspline',";
		echo "\n";
        echo "data: data\n" ;         
        echo "}]\n" ;
   echo "});\n" ; 
echo "});\n" ; 
echo "</script>\n" ;	
}
/*
function shn_stat_TP_sub_byminute() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];
	//new table
	$q="SELECT when_sent, count(when_sent) as count_when_sent FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent), MINUTE( when_sent ) 
	ORDER BY DATE( when_sent ) , HOUR(when_sent), MINUTE( when_sent )";
	//$res=mysql_query($q);	
	$res = $global['db']->Execute($q);
	//$row = mysql_fetch_array($res);
	$row = $res->FetchRow();
	/*check result 
	if($row === FALSE) {
    	die(mysql_error()); 
	}	
	$json_update_time = array();
	$json_count_update_time = array();
	do{
		//$source_date[] = $row['source_date'];
		$update_time[] = (strtotime($row['update_time'])*1000);		
		date_default_timezone_set('UTC');
		array_push($json_update_time, $row['update_time']);
		$count_update_time[] = $row['count_update_time'];
		array_push($json_count_update_time, $row['count_update_time']);
		}		
	//while($row = mysql_fetch_array($res));
	while($row = $res->FetchRow());
	echo json_encode($count_update_time);
	echo json_encode($update_time);
	/* mysql_close($link); 	*/	
	/*echo "<script type="text/javascript"> 
	?>	
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php	
	$shortname = $_GET['shortname'];
	echo "\n";	
	$json_update_time = implode("','",$json_update_time);
	$json_count_source_date = implode(",", $json_count_update_time);
	echo json_encode($update_time);
	echo json_encode($count_update_time);
	echo "\n";
	// Empty string when using an empty array:
	//var_dump(implode('hello', $json_count_source_date())); // string(0) ""		
	echo "<script type=\"text/javascript\">\n";	
		//echo json_encode($source_date);
		echo "\n";
		echo "var points = [$json_count_update_time],\n";  
		//echo "var dates = json_encode($update_time),\n";
		echo "dates = " .json_encode($update_time);
		//echo json_encode($count_source_date);
		echo ",\n";
		echo "i, data = [], chart;";
		echo "\n";
		echo "for(i=0; i<points.length; i++) {\n";   
			echo "data.push([dates[i], points[i]]);\n";
			echo "}\n";
	echo "\$(document).ready(function() {\n" ; 
	//$(document).ready(function() {
   echo "chart = new Highcharts.Chart({\n" ;
      echo "chart: {\n" ;
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by hour'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b',\n" ;
            echo "hour: '%e. %b',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'Expiry Date Count'\n" ;
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
         echo "name: 'Japan Earthquake and Tsunami',\n" ;
     echo "type: 'line',\n" ;
         echo "data: data\n" ;         
        echo "}]\n" ;
   echo "});\n" ; 
echo "});\n" ; 
echo "</script>\n" ;	
}
*/
/******************
* TP_sub_stacked_status_byhour function
*******************/
function shn_stat_TP_sub_stacked_status_byhour() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	$shortname = $_GET['shortname'];

$queryR="SELECT count( triage_category ) AS count_statusR, '10-11 am' AS time_rangeR
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
	WHERE (triage_category = 'Red' AND HOUR( when_sent ) BETWEEN '12'AND '12')";

	$rR=mysql_query($queryR);
	$rowR = mysql_fetch_array($rR);
	//check result
	if($rowR === FALSE) {
    	die(mysql_error()); // TODO: better error handling
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
	echo json_encode($count_statusR);
	echo json_encode($time_rangeR);
	
	//green
	$queryG="SELECT count( triage_category ) AS count_statusG, '10-11 am' AS time_rangeG
	FROM `edxl_co_lpf` a
	LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id ) 
	WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '10'AND '10')
	UNION 
	SELECT count( triage_category ) AS count_statusR, '11-12 am' AS time_rangeG
	FROM `edxl_co_lpf` a
	LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id ) 
	WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '11'AND '11')
	UNION 
	SELECT count( triage_category ) AS count_statusR, '12-1 pm' AS time_rangeG
	FROM `edxl_co_lpf` a
	LEFT JOIN edxl_de_header b ON ( a.co_id = b.de_id ) 
	WHERE (triage_category = 'Green' AND HOUR( when_sent ) BETWEEN '12'AND '12')";
		
	$rG=mysql_query($queryG);
	$rowG = mysql_fetch_array($rG);
	//check result
	if($rowG === FALSE) {
    	die(mysql_error()); // TODO: better error handling
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
	echo json_encode($count_statusG);
	echo json_encode($time_rangeG);
	
	//yellow
	$queryY="SELECT count( triage_category ) AS count_statusY, '10-11 am' AS time_rangeY
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
	WHERE (triage_category = 'Yellow' AND HOUR( when_sent ) BETWEEN '12'AND '12')";
		
	$rY=mysql_query($queryY);
	$rowY = mysql_fetch_array($rY);
	
	if($rowY === FALSE) {
    	die(mysql_error()); // TODO: better error handling
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
	?>
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php
	$shortname = $_GET['shortname'];
	//to do
	$json_time_rangeR = implode("','",$json_time_rangeR);
	$json_count_statusR = implode(",", $json_count_statusR);
	
	$json_time_rangeG = implode("','",$json_time_rangeG);
	$json_count_statusG = implode(",", $json_count_statusG);
	
	$json_time_rangeY = implode("','",$json_time_rangeY);
	$json_count_statusY = implode(",", $json_count_statusY);	 
		
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
	//yellow
	echo "var pointsY = [$json_count_statusY],\n" ;  
		echo "datesY = ".json_encode($time_rangeY);
		echo ",\n" ;
		echo "k, dataY = [], chart;\n" ;
		echo "for(k=0; k<pointsY.length; k++) {\n" ;    
			echo "dataY.push([datesY[k], pointsY[k]]);\n" ;
									echo"}\n" ;
	
echo "\$(document).ready(function() {\n";	
echo "var chart = new Highcharts.Chart({\n" ;
    echo "chart: {\n" ;
        echo "renderTo: 'container',\n" ;
        echo "defaultSeriesType: 'column'\n" ;
    echo "},\n" ;
	echo "title: {\n" ;
			echo "text: 'PL Status per Hour'\n" ;
			echo "},\n" ;
		echo "subtitle: {\n" ;
			echo "text: 'Event: CMAX2010 at Suburban Hospital'\n" ;
					echo "},\n" ;
    echo "xAxis: {\n" ;
        echo "title: {\n" ;
            echo "text: 'Time range'\n" ;
			echo "},\n";        
		echo "categories: ['10-11 AM','11-12 PM','12-1 PM']\n" ; 		
			echo "},\n" ;
    echo "yAxis: {\n" ;
		echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
			echo "},\n" ;
		echo "},\n" ;    
    echo "plotOptions: {\n" ;
        echo "column: {\n" ;
               echo "stacking: 'true'\n" ;
				echo "}\n" ;
			echo "},\n" ;
    echo "series: [\n" ;
        echo "{\n" ;
            echo "name: 'Red Zone',\n" ;
			echo "color:'#CC0066',\n" ;            
			echo "data: pointsR\n" ;
        echo "},\n" ;
         echo "{\n" ;
            echo "name: 'Green Zone',\n" ;
			echo "color:'#339900',\n" ;            
			echo "data: pointsG\n" ;
        echo "},\n" ;
        echo "{\n" ;
            echo "name: 'Yellow Zone',\n" ;
			echo "color: '#FFCC66',\n" ;            
			echo "data: pointsY\n" ;
        echo "}\n" ;       
    echo "]\n" ;
echo "});\n";
echo "});\n";
echo "</script>\n" ;
}
/**************************
* arrival_bydate_status
* for sendai, hepl and christchurch only
**************************/
function shn_stat_arrival_bydate_status() {
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
	where (c.shortname like '".$shortname."' and a.source_date >'2011-01-01')
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
	//for CMAX2010
	$q="SELECT when_sent as source_update, count(when_sent) as count_source_update FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent)
	ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	
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
	//for status
	$q1="SELECT DISTINCT (opt_status), count( opt_status ) as count_opt_status FROM person_status a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id where c.shortname like '".$shortname."'
	GROUP BY opt_status";
	$res = $global['db']->Execute($q1);
	$row = $res->FetchRow();
	
	if($row === FALSE) {
    	die(mysql_error()); 
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
	
	?>	
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php	
	$shortname = $_GET['shortname'];
	echo "\n";	
	$json_source_date = implode("','",$json_source_date);
	$json_count_source_date = implode(",", $json_count_source_date);
	echo json_encode($source_date);
	echo json_encode($count_source_date);
	echo "\n";
	
	$json_opt_status = implode("','",$json_opt_status);
	$json_count_opt_status = implode(",", $json_count_opt_status);
	echo json_encode($json_opt_status);
	echo json_encode($json_count_opt_status);
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
		//status
		echo "\n";
		echo "var counts = [$json_count_opt_status],\n";		
		echo "names = " .json_encode($opt_status);		
		echo ",\n";
		echo "i, data_status = [], chart;";
		echo "\n";
		echo "for(i=0; i<counts.length; i++) {\n";   
			echo "data_status.push([names[i], counts[i]]);\n";
			echo "}\n";

	echo "\$(document).ready(function() {\n" ; 
	echo "chart = new Highcharts.Chart({\n" ;
      echo "chart: {\n" ;
         echo "renderTo: 'content',\n" ;         
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Date'\n" ;
      echo "},\n" ;
      echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b',\n" ;
            echo "hour: '%e. %b',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "}\n" ;
     echo "},\n" ;
     echo "tooltip: {\n" ;
         echo "enabled: false,\n" ;
         echo "formatter: function() {\n" ;
		 echo "line:{\n";
            echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
               echo "this.x +': '+ this.y;\n" ;
			echo "}\n";
		echo "pie: {\n";
			echo "return '<b>'+ this.point.name +'</b>: '+ this.percentage +' %'\n";
			echo "}\n";
         echo "}\n" ;
      echo "},\n" ;
      echo "plotOptions: {\n" ;
        echo "line: {\n" ;
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
      echo "},\n" ;
	  
     echo "series: [{\n" ;		
        echo "name: '". $shortname; 
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
        echo "data: data\n" ; 
		echo "},\n";
		echo "{\n";
		echo "type: 'pie',\n";
		echo "data: data_status,\n" ; 			
		echo "center: [150, 150],\n";
		echo "size: 150,\n";
		echo "showInLegend: true,\n";
		echo "showLegend: true,\n";
		echo "dataLabels: {\n";
        echo "enabled: true\n";
		echo "}\n";
	
      echo "}]\n";
   echo "})\n"; 
   
echo "})\n";
echo "</script>\n";	
}
/**************************
* arrival_byhour_status
* for sendai, hepl and christchurch only
**************************/
function shn_stat_arrival_byhour_status() {
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
	where (c.shortname like '".$shortname."' and a.source_date >'2011-01-01')
	GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date)";	
	}
	//for hepl
	if($shortname=="hepl") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id 
	where (c.shortname like '".$shortname."' and a.source_date >'2010-01-11')
	GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date)";	
	}
	//for christchurch
	if($shortname=="christchurch") {
	$q="SELECT source_date, count(source_date) AS count_source_date  FROM `pfif_person` a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id 
	where (c.shortname like '".$shortname."' and a.source_date >'2011-02-20')
	GROUP BY DATE(source_date), HOUR(source_date) order by DATE(source_date), HOUR(source_date)";	
	}
	//for CMAX2010
	$q="SELECT when_sent as source_update, count(when_sent) as count_source_update FROM `edxl_de_header` a
	JOIN edxl_co_header b ON b.de_id = a.de_id
	JOIN edxl_co_lpf c ON c.co_id = b.co_id 
	GROUP BY DATE( when_sent ) , HOUR(when_sent)
	ORDER BY DATE( when_sent ) , HOUR(when_sent)";
	
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
	//for status
	$q1="SELECT DISTINCT (opt_status), count( opt_status ) as count_opt_status FROM person_status a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id where c.shortname like '".$shortname."'
	GROUP BY opt_status";
	$res = $global['db']->Execute($q1);
	$row = $res->FetchRow();
	
	if($row === FALSE) {
    	die(mysql_error()); 
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
	
	?>	
	<div id="content" style="width: 400px; height: 600px; margin: 0 auto;"></div>;
	<?php	
	$shortname = $_GET['shortname'];
	echo "\n";	
	$json_source_date = implode("','",$json_source_date);
	$json_count_source_date = implode(",", $json_count_source_date);
	echo json_encode($source_date);
	echo json_encode($count_source_date);
	echo "\n";
	
	$json_opt_status = implode("','",$json_opt_status);
	$json_count_opt_status = implode(",", $json_count_opt_status);
	echo json_encode($json_opt_status);
	echo json_encode($json_count_opt_status);
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
		//status
		echo "\n";
		echo "var counts = [$json_count_opt_status],\n";		
		echo "names = " .json_encode($opt_status);		
		echo ",\n";
		echo "i, data_status = [], chart;";
		echo "\n";
		echo "for(i=0; i<counts.length; i++) {\n";   
			echo "data_status.push([names[i], counts[i]]);\n";
			echo "}\n";

	echo "\$(document).ready(function() {\n" ; 
	echo "chart = new Highcharts.Chart({\n" ;
      echo "chart: {\n" ;
        echo "renderTo: 'content',\n" ;   
		echo "zoomType: 'x',\n";
      echo "},\n" ;
      echo "title: {\n" ;
         echo "text: 'PL Arrival Rate by Hour'\n" ;
      echo "},\n" ;
	  //
	  echo "xAxis: {\n" ;
         echo "type: 'datetime',\n" ;
         echo "dateTimeLabelFormats: {\n" ;
            echo "second: '%e. %b',\n" ;
            echo "minute: '%e. %b',\n" ;
            echo "hour: '%e. %b',\n" ;
            echo "day: '%e. %b',\n" ;
            echo "week: '%e. %b',\n" ;
            echo "month: '%b \'%y',\n" ;
            echo "year: '%Y'\n" ;     
         echo "}\n" ;
     echo "},\n" ;
     echo "yAxis: {\n" ;
         echo "title: {\n" ;
            echo "text: 'People Count'\n" ;
         echo "}\n" ;
     echo "},\n" ;
     echo "tooltip: {\n" ;
         echo "enabled: false,\n" ;
         echo "formatter: function() {\n" ;
		 echo "line:{\n";
            echo "return '<b>'+ this.series.name +'</b><br/>'+\n" ;
               echo "this.x +': '+ this.y;\n" ;
			echo "}\n";
		echo "pie: {\n";
			echo "return '<b>'+ this.point.name +'</b>: '+ this.percentage +' %'\n";
			echo "}\n";
         echo "}\n" ;
      echo "},\n" ;
      echo "plotOptions: {\n" ;
        echo "line: {\n" ;
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
      echo "},\n" ;
	  
     echo "series: [{\n" ;		
        echo "name: '". $shortname; 
		echo "'";
		echo ",\n";
		echo "type: 'line',\n" ;
        echo "data: data\n" ; 
		echo "},\n";
		echo "{\n";
		echo "type: 'pie',\n";
		echo "data: data_status,\n" ; 			
		echo "center: [150, 150],\n";
		echo "size: 150,\n";
		echo "showInLegend: true,\n";
		echo "showLegend: true,\n";
		echo "dataLabels: {\n";
        echo "enabled: true\n";
		echo "}\n";
	
      echo "}]\n";
   echo "})\n"; 
   
echo "})\n";
echo "</script>\n";	
}