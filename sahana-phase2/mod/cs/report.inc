<?php
/*
This is testing report.inc in catalogue system
*/
function shn_cs_rpt_default()
{
shn_cs_cat_item_pdf_report();
shn_cs_cat_item_ods_report();
shn_cs_cat_item_xhtml_report();
shn_cs_cat_item_excel_report();
}

function shn_cs_cat_item_pdf_report()
{
    global $global;
    $db=$global["db"];

    $table_header=array('name' =>'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query="SELECT * FROM ct_catalogue";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $table_row ["name"]= $res->fields["name"];
    $table_row ["desc"]= $res->fields["description"];
    array_push($table_data, $table_row);

    $res->MoveNext();
    }//end of while loop 
    
    $title='Catalogs and Items';
    $txt = 'These are the existing catalogues and items that are stored in sahana database';
    $cs_report1_keyword_arr = array('mod'=>'cs','report'=>'catalog','report1'=>'items','users'=>'all');

    shn_pdf_report_fopen("catalogs_items",$cs_report1_keyword_arr);
    shn_pdf_report_add_title($title);
    shn_pdf_report_add_summery($txt);
    shn_pdf_report_add_table($table_header,$table_data);
    shn_pdf_report_close();
}

function shn_cs_cat_item_ods_report()
{
    global $global;
    $db=$global["db"];

    $table_header=array('name' =>'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query="SELECT * FROM ct_catalogue";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $table_row ["name"]= $res->fields["name"];
    $table_row ["desc"]= $res->fields["description"];
    array_push($table_data, $table_row);

    $res->MoveNext();
    }//end of while loop 
    
    $title='Catalogs and Items';

    $cs_report_keyword_arr = array('mod'=>'cs','report'=>'catalog','report1'=>'items','users'=>'all');

     shn_ods_report_fopen('catalogs_items',$cs_report_keyword_arr );
     shn_ods_report_add_sheet('sheetone');
     shn_ods_report_add_title($title);
     shn_ods_report_add_table($table_header,$table_data);
     shn_ods_report_close();
}

function shn_cs_cat_item_xhtml_report()
{
    global $global;
    $db=$global["db"];

    $table_header=array('name' =>'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;

    $query="SELECT * FROM ct_catalogue";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $table_row ["name"]= $res->fields["name"];
    $table_row ["desc"]= $res->fields["description"];
    array_push($table_data, $table_row);

    $res->MoveNext();
    }//end of while loop 
    
    $title='Catalogs and Items';
    $txt = 'These are the existing catalogues and items that are stored in sahana database';
    $cs_report_keyword_arr = array('mod'=>'cs','report'=>'catalog','report1'=>'items','users'=>'all');

shn_xhtml_report_fopen('catalogs_items',$cs_report_keyword_arr);
shn_xhtml_report_add_title($title);
shn_xhtml_report_add_summary($txt);
shn_xhtml_report_add_table($table_header,$table_data);
shn_xhtml_report_close();
}

function shn_cs_cat_item_excel_report()
{ 
    global $global;
    $db=$global["db"];

    $table_header=array('name' =>'Name', 'desc' => 'description');
    $table_data = array();
    $row_count = 0;


    $query="SELECT * FROM ct_catalogue";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $table_row ["name"]= $res->fields["name"];
    $table_row ["desc"]= $res->fields["description"];
    array_push($table_data, $table_row);

    $res->MoveNext();
    }//end of while loop 
    
    $title='Catalogs and Items';
    $txt = 'These are the existing catalogues and items that are stored in sahana database';
    $cs_report1_keyword_arr = array('mod'=>'cs','report'=>'catalog','report1'=>'items','users'=>'all');

    shn_excel_report_fopen("catalogs_items",$cs_report1_keyword_arr);
    shn_excel_report_add_title($title);
    #shn_excel_report_add_summery($txt);
    shn_excel_report_add_table($table_header,$table_data);
    shn_excel_report_close();
}

?>