<?php
/**
 * @name         Statistics
 * @version      0.3
 * @package      stat
 * @author       Lan Ngoc Le <lale@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1027
 */


// testing script....


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
	//$res=mysql_query($q);
	$res = $global['db']->Execute($q);
	//$row = mysql_fetch_array($res);
	$row = $res->FetchRow();
	/*check result */
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
	/* mysql_close($link); 	*/
	echo json_encode($expiry_date);
	echo json_encode($count_puuid);

?>
  <script type="text/javascript" src="exporting.js"></script>
  <script type='text/javascript'>
  var points = <?php echo json_encode($count_puuid);?>,
  dates = <?php echo json_encode($expiry_date);?>,
  i, data = [], chart;
  for(i=0; i<points.length; i++) {
    data.push([dates[i], points[i]]);
								}
	//$(function(){
	$(document).ready(function() {
	chart = new Highcharts.Chart({
		chart: {
			renderTo: 'container',
			zoomType: 'x'
			},
		title: {
			text: 'PL Expiry Date Count for Japan Earthquake and Tsunami in 2011'
				},
		xAxis: {
			type: 'datetime',
			dateTimeLabelFormats: {
				second: '%e. %b %H %M %S',
				minute: '%e. %b %H %M',
				hour: '%e. %b %H',
				day: '%e. %b',
				week: '%e. %b',
				month: '%b \'%y',
				year: '%Y'
				},
			maxZoom: 24 * 3600 * 1000
				},
		yAxis: {
			title: {
            text: 'Expiry Date Count'
					}
				},
		tooltip: {
			enabled: true,
			//formatter: function() {
				//return '<b>'+ this.series.name +'</b><br/>'+
				//this.x +': '+ this.y;
									//}
			formatter: function() {
			return 'Time of day: '+ Highcharts.dateFormat('%H:%M', this.x);
				}
				},
		plotOptions: {
			line: {
				dataLabels: {
				enabled: true
							},
				enableMouseTracking: false
					}
					},
		series: [{
			name: 'Japan Earthquake and Tsunami',
			type: 'line',
			data: data,
			pointInterval: 24 * 3600 * 1000//one day
				}]
	});
});
</script>
<!-- Add the container -->
<div id="container" style="height: 400px;"></div>

