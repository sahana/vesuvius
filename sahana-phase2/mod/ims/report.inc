<?php
/** View ,Edit forms for Inventories of the Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ims
*/

global $global;
include_once $global['approot']."/inc/reporting/lib_reporting.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once("lib_ims.inc");
include_once $global['approot'].'/mod/cs/lib_cs.inc';

function shn_ims_rpt_default()
{
    shn_ims_expired_item_report();
    shn_ims_destroyed_item();
    shn_ims_reorder_level_report_pdf();
    shn_ims_expired_item_ods();
    shn_ims_destroyed_item_ods();
    shn_ims_reorder_level_report_ods();
    shn_ims_expired_item_xhtml();
    shn_ims_destroyed_item_xhtml();
    shn_ims_reorder_level_report_xhtml();
    
}

function shn_ims_expired_item_report()
{
  
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Supplier');
	$table_data=array();
	$table_data=_shn_ims_expired_item_report();
	
	$title="Expired Items Report-pdf";
	$text="These Are the records about items that are already expired";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    	
   	shn_report_fopen('pdf',"expired_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();

	//report_download_link("shn_ims_expired_item_report");

	

    
}

function shn_ims_expired_item_ods()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Supplier');
    $table_data=array();
    $table_data=_shn_ims_expired_item_report();
    $title="Expired Items Report-ods";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');


    
    shn_report_fopen('ods',"expired_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();

    

}

function shn_ims_expired_item_xhtml()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Supplier');
    $table_data=array();
    $table_data=_shn_ims_expired_item_report();
    $title="Expired Items Report-xhtml";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    shn_report_fopen('xhtml',"expired_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();    
}

function shn_ims_destroyed_item()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Suplier');
	$table_data=array();
	$table_data=_shn_ims_destroyed_item_report();
	    
	$title="Destroyed Items Report-pdf";
	$text="These Are the records about items that are already destroyed";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');
    	
   	shn_report_fopen('pdf',"destroyed_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();  

	//report_download_link('shn_ims_expired_item_report');
}

function shn_ims_destroyed_item_ods()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Suplier');
    $table_data=array();
    $table_data=_shn_ims_destroyed_item_report();
    $title="Destroyed Items Report-ods";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    
    shn_report_fopen('ods',"destroyed_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close();  

    //report_download_link('shn_ims_destroyed_item_ods');

}

function shn_ims_destroyed_item_xhtml()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Suplier');
    $table_data=array();
    $table_data=_shn_ims_destroyed_item_report();
    $title="Destroyed Items Report-xhtml";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');
    
    shn_report_fopen('xhtml',"destroyed_items",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close(); 

    //report_download_link('shn_ims_destroyed_item_xhtml');
}

function shn_ims_reorder_level_report_pdf()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'inventory'=>'Inventory');
	$table_data=array();
	$table_data=_shn_ims_reorder_level_report();

	$title="Items Re-Order Level Report-pdf";
	$text="These Are the records about items that are already gone below the re-order level of particular inventory";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');


    shn_report_fopen('pdf',"reorder_level",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close(); 

	//report_download_link('shn_ims_reorder_level_report_pdf');	
}

function shn_ims_reorder_level_report_ods()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'inventory'=>'Inventory');
    $table_data=array();
    $table_data=_shn_ims_reorder_level_report();
    $title="Item Re-Order Level Report-ods";
    $text="These Are the records about items that are already gone below the re-order level of particular inventory";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');
    
    shn_report_fopen('ods',"reorder_level",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close(); 

    //report_download_link('shn_ims_reorder_level_report_ods');	
}

function shn_ims_reorder_level_report_xhtml()
{
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'inventory'=>'Inventory');
    $table_data=array();
    $table_data=_shn_ims_reorder_level_report();
    $title="Item Re-Order Level Report-xhtml";
    $text="These Are the records about items that are already gone below the re-order level of particular inventory";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');
    
    shn_report_fopen('xhtml',"reorder_level",$ims_report_keyword_arr);
    shn_report_add_title($title);
    //shn_report_add_summary($txt);
    shn_report_add_table($table_header,$table_data);
    shn_report_close(); 

    report_download_link('shn_ims_reorder_level_report_xhtml');
}

?>
