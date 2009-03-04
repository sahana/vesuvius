<?php
//pichart generation function for by disease
function shn_image_dsm_generate_pichart_by_disease(){
	global $global;
	$db = $global['db'];

	require_once ($global['approot']."3rd/phplot/phplot.php");

	$query_count_by_dis="SELECT dd.dis_name,dd.med_name, COUNT(dc.dis_id) AS c FROM dsm_case_count dc JOIN dsm_diseases dd on dc.dis_id=dd.dis_id GROUP BY  dd.dis_id";
	$res_count_by_dis = $db->Execute($query_count_by_dis);

	$data = array();
	while($row=$res_count_by_dis->FetchRow()){
		$dis_name = $row['dis_name'];
		$med_name = $row['med_name'];
		$com_name = $dis_name.((isset($med_name))?" (".$med_name.")":"");
		$count=$row['c'];
		array_push(&$data,array($com_name,$count));

	}

	$plot = new PHPlot(900,700);
	$plot->SetImageBorderType('plain');

	$plot->SetPlotType('pie');
	$plot->SetDataType('text-data-single');
	$plot->SetDataValues($data);

	# Set enough different colors;
	/*$plot->SetDataColors(array('red', 'green', 'blue', 'yellow', 'cyan',
	'magenta', 'brown', 'lavender', 'pink',
	'gray', 'orange'));*/

	# Main plot title:
	$plot->SetTitle(_t("Case Count By Disease"));

	# Build a legend from our data array.
	# Each call to SetLegend makes one line as "label: value".
	foreach ($data as $row)
	$plot->SetLegend(implode(': ', $row));

	$plot->DrawGraph();
}

//linechart generation function for per disease
function shn_image_dsm_generate_linechart_per_disease(){
	global $global;
	$db = $global['db'];

	$dis_id = $_REQUEST['dis_id'];
	$start_date=$_REQUEST['start_date'];
	$end_date=$_REQUEST['end_date'];
	//    var_dump($_REQUEST);
	$dis_ids = "";
	foreach($dis_id as $v){
		$dis_ids .="'".$v."',";
	}
	$dis_ids .= "''";

	require_once ($global['approot']."3rd/phplot/phplot.php");

	$query_count_per_dis = "SELECT dd.dis_name,dd.med_name,COUNT(cc.dis_id) as c FROM dsm_case_count cc JOIN dsm_diseases dd ON dd.dis_id=cc.dis_id WHERE cc.date BETWEEN ? AND ? AND cc.dis_id IN ($dis_ids) GROUP BY cc.dis_id ORDER BY dd.dis_name";
	$res_count_per_dis = $db->Execute($query_count_per_dis,array($start_date,$end_date));
	
	$data = array();
	$max_c = 0;
	
	while($row=$res_count_per_dis->FetchRow()){
		$name = $row['dis_name'].((strlen(trim($row['med_name']))==0)?'':(" (".$row['med_name'].")"));
		$data[] = array("$name",($row['c']*1));
		if($row['c']>$max_c){
			$max_c = $row['c'];
		}
	}
	
	$tick_increment = 1;
	if($max_c>10){
		$tick_increment = ceil($max_c/10);
	}
	$plot = new PHPlot(1100, 600);
	$plot->SetImageBorderType('plain');

	$plot->SetPlotType('bars');
	$plot->SetDataType('text-data');
	$plot->SetDataValues($data);

	# Let's use a new color for these bars:
	$plot->SetDataColors('magenta');

	# Force bottom to Y=0 and set reasonable tick interval:
	$plot->SetPlotAreaWorld(NULL, 0, NULL, NULL);
	$plot->SetYTickIncrement($tick_increment);
	# Format the Y tick labels as numerics to get thousands separators:
	$plot->SetYLabelType('data');
	$plot->SetPrecisionY(0);

	# Main plot title:
	$plot->SetTitle('Chronological Case pre Disease');
	# Y Axis title:
	$plot->SetYTitle('Number of Case');

	# Turn off X tick labels and ticks because they don't apply here:
	$plot->SetXTickLabelPos('none');
	$plot->SetXTickPos('none');

	$plot->DrawGraph();

	 
}
