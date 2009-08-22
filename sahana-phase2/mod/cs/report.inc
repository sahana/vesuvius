<?php
/*
This is testing report.inc in catalog system
*/
function shn_cs_rpt_default()
{
	shn_cs_cat_itm_ods_report();
	shn_cs_cat_itm_pdf_report();
	shn_cs_cat_itm_xhtml_report();
	shn_cs_cat_itm_xls_report();
}


function shn_cs_cat_itm_xls_report()
{
    global $global;
    $db = $global["db"];

    $table_header = array('name' => 'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query = "SELECT * FROM ct_catalogue";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
	    $table_row = "row" . $row_coount++;
	    $table_row = array();
	    $table_row ["name"] = $res->fields["name"];
	    $table_row ["desc"] = $res->fields["description"];
	    array_push($table_data, $table_row);
	
	    $res->MoveNext();
    }//end of while loop 
    
    $title = _t('Catalogs and Items');
    $txt = _t('These are the existing catalogs and items that are stored in sahana database');
    $cs_report1_keyword_arr = array('mod' => 'cs','report' => 'catalog','report1' => 'items','users' => 'all');

    shn_report_fopen('xls',"catalogs_items",$cs_report1_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}

function shn_cs_cat_itm_xhtml_report()
{
    global $global;
    $db = $global["db"];

    $table_header = array('name' => 'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query = "SELECT * FROM ct_catalogue";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
	    $table_row = "row" . $row_coount++;
	    $table_row = array();
	    $table_row ["name"] = $res->fields["name"];
	    $table_row ["desc"] = $res->fields["description"];
	    array_push($table_data, $table_row);
	
	    $res->MoveNext();
    }//end of while loop 
    
    $title = _t('Catalogs and Items');
    $txt = _t('These are the existing catalogs and items that are stored in sahana database');
    $cs_report1_keyword_arr = array('mod' => 'cs','report' => 'catalog','report1' => 'items','users' => 'all');

    shn_report_fopen('xhtml',"catalogs_items",$cs_report1_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}

function shn_cs_cat_itm_pdf_report()
{
    global $global;
    $db = $global["db"];

    $table_header = array('name' =>'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query = "SELECT * FROM ct_catalogue";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
	    $table_row = "row" . $row_coount++;
	    $table_row = array();
	    $table_row ["name"] = $res->fields["name"];
	    $table_row ["desc"] = $res->fields["description"];
	    array_push($table_data, $table_row);
	
	    $res->MoveNext();
    }//end of while loop 
    
    $title = _t('Catalogs and Items');
    $txt = _t('These are the existing catalogs and items that are stored in sahana database');
    $cs_report1_keyword_arr = array('mod' => 'cs','report' => 'catalog','report1' => 'items','users' => 'all');

    shn_report_fopen('pdf',"catalogs_items",$cs_report1_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}

function shn_cs_cat_itm_ods_report()
{
    global $global;
    $db = $global["db"];

    $table_header = array('name' => 'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query = "SELECT * FROM ct_catalogue";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
	    $table_row = "row" . $row_coount++;
	    $table_row = array();
	    $table_row ["name"] = $res->fields["name"];
	    $table_row ["desc"] = $res->fields["description"];
	    array_push($table_data, $table_row);
	
	    $res->MoveNext();
    }//end of while loop 
    
    $title = _t('Catalogs and Items');
    $txt = _t('These are the existing catalogs and items that are stored in sahana database');
    $cs_report1_keyword_arr = array('mod' => 'cs','report' => 'catalog','report1' => 'items','users' => 'all');

    shn_report_fopen('ods',"catalogs_items",$cs_report1_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();
}
