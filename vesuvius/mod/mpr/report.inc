<?php
/*
not very much documentation in this file? --greg
*/



function shn_mpr_rpt_default() {
	// ::::::: missing people :::::::
	//shn_mpr_mis_ppl_ods_report();
	shn_mpr_mis_ppl_pdf_report();
	//shn_mpr_mis_ppl_xhtml_report();
	//shn_mpr_mis_ppl_xls_report();
	
	// :::::: found people ::::::
	//shn_mpr_fnd_ppl_ods_report();
	shn_mpr_fnd_ppl_pdf_report();
	//shn_mpr_fnd_ppl_xhtml_report();
	//shn_mpr_fnd_ppl_xls_report();
}



// :: missing people :::::::::::::::::::::::::::::::::::::::::::::::::::
function shn_mpr_mis_ppl_pdf_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Missing People');
	$txt = _t('This is the list of missing people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'missing list','report1' => 'name','users' => 'all');

	shn_report_fopen('pdf',"missing_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_mis_ppl_ods_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Missing People');
	$txt = _t('This is the list of missing people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'missing list','report1' => 'name','users' => 'all');

	shn_report_fopen('ods',"missing_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_mis_ppl_xhtml_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Missing People');
	$txt = _t('This is the list of missing people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'missing list','report1' => 'name','users' => 'all');

	shn_report_fopen('xhtml',"missing_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_mis_ppl_xls_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Missing People');
	$txt = _t('This is the list of missing people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'missing list','report1' => 'name','users' => 'all');

	shn_report_fopen('xls',"missing_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



// :: found people ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
function shn_mpr_fnd_ppl_pdf_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Found People');
	$txt = _t('This is the list of found people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'found list','report1' => 'name','users' => 'all');

	shn_report_fopen('pdf',"found_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_fnd_ppl_xhtml_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	
	$title = _t('List of Found People');
	$txt = _t('This is the list of found people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'found list','report1' => 'name','users' => 'all');

	shn_report_fopen('xhtml',"found_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_fnd_ppl_ods_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	$title = _t('List of Found People');
	$txt = _t('This is the list of found people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'found list','report1' => 'name','users' => 'all');

	shn_report_fopen('ods',"found_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	//shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}



function shn_mpr_fnd_ppl_xls_report() {
	global $global;
	$db = $global["db"];

	$table_header = array('name' =>'Surename', 'fname' => 'First Name');
	$table_data = array();
	$row_count = 0;

	$query = "SELECT DISTINCT full_name, family_name FROM person_uuid, person_status WHERE person_uuid.p_uuid = person_status.p_uuid";
	$res = $db->Execute($query);

	while(!$res == NULL && !$res->EOF) {
		$table_row = "row".$row_coount++;
		$table_row = array();
		$table_row ["name"] = $res->fields["full_name"];
		$table_row ["fname"] = $res->fields["family_name"];
		array_push($table_data, $table_row);
		$res->MoveNext();
	}
	$title = _t('List of Found People');
	$txt = _t('This is the list of found people');
	$mpr_report1_keyword_arr = array('mod' => 'mpr','report' => 'found list','report1' => 'name','users' => 'all');

	shn_report_fopen('xls',"found_list",$mpr_report1_keyword_arr);
	shn_report_add_title($title);
	#shn_report_add_summary($txt);
	shn_report_add_table($table_header,$table_data);
	shn_report_close();
}