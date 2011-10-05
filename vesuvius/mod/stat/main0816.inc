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
		
	
		/* echo "
		<script>".file_get_contents($global['approot']."res/js/stat/")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/dark-blue.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/dark-green.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/excanvas.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/gray.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/grid.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/exporting.js")."</script>
		<script>".file_get_contents($global['approot']."res/js/stat/highcharts.js")."</script> 
		";*/
		/* echo "<script type=\"text/javascript\" src=\"res/js/jquery-1.4.4.min.js\" ></script>  */
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
		echo "
		<ul>
			<li><a href=\"index.php?mod=stat&world\">World</a></li>
			<li><a href=\"index.php?mod=stat&act=galaxy\">Galaxy</a></li>
			<li><a href=\"index.php?mod=stat&act=universe\">Universe</a></li>
			<li><a href=\"index.php?mod=stat&act=status\">Status</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
		";
		}
/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_stat_default() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
}	

/**
 * the status action...
 * @access public
 * @return void
 */
function shn_stat_status() {
	global $global;
	shn_stat_menu();
	echo "People Statistics for  ";
	echo $_GET['shortname'];
	
	/* display status */
	$shortname = $_GET['shortname'];
	$q="SELECT DISTINCT (opt_status), count( opt_status ) as count_opt_status FROM person_status a
	join person_uuid b ON a.p_uuid= b.p_uuid
	join incident c ON c.incident_id= b.incident_id where c.shortname like '".$shortname."'
	GROUP BY opt_status";
	
	//$res=mysql_query($q);	
	$res = $global['db']->Execute($q);
	//$row = mysql_fetch_array($res);
	$row = $res->FetchRow();
	/*check result */
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
	//while($row = mysql_fetch_array($res));
	while($row = $res->FetchRow());
	/* mysql_close($link); */	
	echo json_encode($opt_status);
	echo json_encode($count_opt_status);

	/*echo "<script type="text/javascript"> */
	echo "
	<script type=\"text/javascript\" 
	var chart;
	$(document).ready(function() {
	chart = new Highcharts.Chart({
		chart: {
			renderTo: 'container',
			defaultSeriesType: 'column'
				},
		title: {
			text: 'PL Status Statistics'
			},
		subtitle: {
			text: 'Source: Google Person Finder, Event: Christchurch Earthquake'
					},
		xAxis: {
			categories: ['alive','deceased', 'found', 'missing', 'unknown'], labels: {rotation: 0, align: 'center',
			style: {
                    color: '#6D869F',
                    fontWeight: 'bold'
                  }	
				}
			},
		yAxis: {
			min: 0,
			title: {
				text: 'Total People count'
					}
				},
		legend: {
			layout: 'vertical',
			backgroundColor: '#FFFFFF',
			align: 'left',
			verticalAlign: 'top',
			x: 0,
			y: 50,
               },
		tooltip: {
			formatter: function() {
            return ''+
				this.x +': '+ this.y +'';
								}
				},
		plotOptions: {
			column: {
            pointPadding: 0.2,
            borderWidth: 0
					}
					},
        series: {
            events: {
                show: (function() {
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
						})
                   }
                }, 
		series: [{
			name: 'Christchurch',          
			
			data: ['846290','10864','69','710','406652']
				}]  
			});  
	});
    });          
	</script>
	";
	?>
	<!-- Add the container -->
	<div id="container" style="width: 600px; height: 800px; margin: 0 auto;"></div>;
	<?php
	
	echo "<script";
	echo "function renderHScharts(){";
	echo "chart = new Highcharts.Chart({";
		echo "chart: {";
			echo "renderTo: 'container',";
			echo "defaultSeriesType: 'column'";
				echo "},";
		echo "title: {";
			echo "text: 'PL Status Statistics'";
			echo "},:";
		echo "subtitle: {";
			echo "text: 'Source: Google Person Finder, Event: Christchurch Earthquake'";
					echo "},";
		echo "xAxis: {";
			echo "categories: ['alive','deceased', 'found', 'missing', 'unknown'], labels: {rotation: 0, align: 'center',";
			echo "style: {";
                    echo "color: '#6D869F',";
                    echo "fontWeight: 'bold'";
                  echo "}";	
				echo "}";
			echo "},:";
		echo "yAxis: {";
			echo "min: 0,";
			echo "title: {";
				echo "text: 'Total People count'";
					echo "}";
				echo "},";
		echo "legend: {";
			echo "layout: 'vertical',";
			echo "backgroundColor: '#FFFFFF',";
			echo "align: 'left',";
			echo "verticalAlign: 'top',";
			echo "x: 0,";
			echo "y: 50,";
               echo "},:";
		echo "tooltip: {";
			echo "formatter: function() {";
            echo "return ''+";
				echo "this.x +': '+ this.y +'';";
								echo "}";
				echo "},";
		echo " plotOptions: {";
			echo "column: {";
            echo "pointPadding: 0.2,";
            echo "borderWidth: 0";
					echo "}";
					echo "},";
        echo "series: {:";
            echo "events: {";
                echo " show: (function() {";
                    echo "var chart = this.chart,";
                    echo "series = chart.series,";
                    echo "i = series.length,";
                    echo "otherSeries;";
                    echo "while(i--) {";
                        echo "otherSeries = series[i];";
                        echo " if (otherSeries != this && otherSeries.visible) {";
                            echo "otherSeries.hide();";
                              echo "}";
							echo "}";                        
						echo "})";
                   echo "}";
                echo "},";
		echo "series: [{";
			echo "name: 'Christchurch',";         
			
			echo "data: ['846290','10864','69','710','406652']";
				echo "}]";
			echo "});"; 
	echo "});";
    echo "});";         
	echo "</script>";
	
	<br/><br/>
	<?php
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
