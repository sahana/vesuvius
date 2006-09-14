<?php
/*
This is testing report.inc in catalogue system
*/
function shn_mpr_rpt_default()
{
shn_mpr_incidentpermissing();
shn_mpr_totalmissing();
shn_mpr_incidentmissing();
}

/* {{{ shn_mpr_totalmissing() */
function shn_mpr_totalmissing()
{
    global $global;

    $count_mis = $global['db']->GetRow("SELECT count(1) FROM person_status WHERE opt_status = 'mis'");
    $count_ali = $global['db']->GetRow("SELECT count(1) FROM person_status WHERE opt_status != 'mis'");
/**/
$data = array(
			array("Missing",$count_mis[0],0),
			array("Found",0,$count_ali[0])
			);

$keyword_arr = array('chart'=>'pie chart','mod'=>'mpr');
generate_piechart("mprfound","Total Missing People","","",$data,$keyword_arr);

}
/* }}} */

/* {{{ shn_mpr_incidentmissing() */
function shn_mpr_incidentmissing()
{
    global $global;
    
    $all_incident = "'".implode(shn_db_get_all_incidents($_SESSION['user_pref_ims_incident_id']),"','")."'";
    $count_mis = $global['db']->GetRow("SELECT count(1) FROM person_status INNER JOIN resource_to_incident ON person_status.p_uuid = resource_to_incident.x_uuid WHERE opt_status = 'mis' AND incident_id IN ($all_incident) ");
    $count_ali = $global['db']->GetRow("SELECT count(1) FROM person_status INNER JOIN resource_to_incident ON person_status.p_uuid = resource_to_incident.x_uuid WHERE opt_status != 'mis' AND incident_id IN ($all_incident) ");
/**/
$data = array(
			array("Missing",$count_mis[0],0),
			array("Found",0,$count_ali[0])
			);

$keyword_arr = array('chart'=>'pie chart','mod'=>'mpr');
generate_piechart("mprfoundincident","Missing People of This Incident","","",$data,$keyword_arr);

}
/* }}} */

/* {{{ */
function shn_mpr_incidentpermissing()
{

$data = array(
    array(  'Incident 1', 1000,300 ),
    array(  'Incident 2', 2010,1000),
    array(  'Incident 3', 3014,1500 ),
    array(  'Incident 4', 2010,1000)

);

$data = array(
    array(  "", 2000,     750),
    array(  "", 2010,    1700),
    array(  "", 2015,    2000),
    array(  "", 2020,    1800),
    array(  "", 2025,    1300),
    array(  "", 2030,     400)
);


/*
$data = array(
			array("sanjeewa",100),
			array("mahesh",90),
			array("ajith",70),
			array("saranga",110)
			);*/

$keyword_arr = array('chart'=>'bar chart','mod'=>'catalogue');
generate_barchart("mprincidentpermissing","Missing People Per Incident","Incident","Number of People", $data,$keyword_arr);
}
/* }}} */

/* {{{ */
function shn_mpr_areachart()
{

$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);
/*
$data = array(
			array("sanjeewa",100),
			array("mahesh",90),
			array("ajith",70),
			array("saranga",110)
			);*/

$keyword_arr = array('chart'=>'area chart','mod'=>'catalogue');
generate_areachart("mprBarchart","This is a testing area chart","x axis","y axis",$data,$keyword_arr);
}
/* }}} */

/* {{{ */
function shn_mpr_report1()
{
$table_header=array('1' =>'aaaaaaaa', '2' => 'bbbbbbb' , '3' => 'cccccccccc');
$table_data = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

$title='Project of the Month';

$txt = 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrimpr, PDA support, and availability in the form of a live CD.';

$mpr_report1_keyword_arr = array('mod'=>'mpr','report'=>'report1','user'=>'sanjeewa');

shn_pdf_report_fopen("mpr_report1",$mpr_report1_keyword_arr);
shn_pdf_report_add_title($title);
shn_pdf_report_add_table($table_header,$table_data);
shn_pdf_report_add_summery($txt);
#shn_pdf_report_add_image('cartoon001.jpg');
shn_pdf_report_close();
}

function shn_mpr_report2()
{
$datasR1 = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

$headerarray=array( 'ss'	=> 'sssssssssss', 'dd' => 'dddddddddd', 'sd' => 'sdsdsdsdsd');

$mpr_report2_keyword_arr = array('mod'=>'mpr','report'=>'report2','users'=>'mahesh');

shn_ods_report_fopen('mpr_report2',$mpr_report2_keyword_arr );
shn_ods_report_add_sheet('mysheetone');
shn_ods_report_add_title('Project of the Month');
shn_ods_report_add_table($headerarray,$datasR1);
shn_ods_report_add_summery( 'Sahana is a secure Web portal that provides applications for coordination and collaboration in the aftermath of disasters. Applications include finding missing people, connecting organizations, reporting on the distribution of aid and services, matching donations to requests, tracking temporary shelters, and, overall, providing transparency and visibility to groups working in a disaster. Key features include GIS, biometrimpr, PDA support, and availability in the form of a live CD.' ,'5','15','5','0.75','middle','center');
#shn_ods_report_add_image('cartoon001.jpg');
shn_ods_report_add_sheet('mysheettwo');
shn_ods_report_close();
}

function shn_mpr_report3()
{
$datasR1 = array(
	array(
		'ingredient'	=> 'aaaa',
		'qte'			=> 150,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'bbbbb',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'ccccc',
		'qte'			=> 50,
		'unite'			=> 'g'
	),
	array(
		'ingredient'	=> 'dddddddd',
		'qte'			=> 2,
		'unite'			=> 'kg'
	),
	array(
		'ingredient'	=> 'eeeeeee',
		'qte'			=> 1,
		'unite'			=> 'kg'
	),
);

$headerarray=array( 'ss'	=> 'sssssssssssxxxx', 'dd' => 'dddddddddd', 'sd' => 'sdsdsdsdsd');
$mpr_report3_keyword_arr = array('mod'=>'mpr','report'=>'report2','users'=>'mahesh');

shn_xhtml_report_fopen('mpr_report3',$mpr_report3_keyword_arr);
shn_xhtml_report_add_title('Sanjeewa Jayasinghe');
shn_xhtml_report_add_summary('This is catalogue system test report in xhtml format...');
shn_xhtml_report_add_table($headerarray,$datasR1);
#shn_xhtml_report_add_image("cartoon001.jpg");
shn_xhtml_report_close();
}
/* }}} */
?>
