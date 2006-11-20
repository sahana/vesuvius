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
    //shn_ims_cat_item_pdf_report();
    //shn_cs_cat_item_ods_report();
    //shn_cs_cat_item_xhtml_report();
}

function shn_ims_expired_item_report()
{
   /* global $global;
    $db=$global['db'];
    $state="expired";

    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Suplier', 'action'=>'Action');
    $table_data = array();
    $row_count = 0;

    $sql="SELECT item_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state';";
    //$ims = $db->Execute($sql1);
    $ims = $db->Execute($sql);

     $suplier_array=array();

    while (!$ims==NULL && !$ims->EOF)
    {
	$table_row = "row".$row_coount++;
        $table_row = array();

	$item_id=$ims->fields["item_id"];
        $inv_id=$ims->fields["inv_id"];
        $suplier_id=$ims->fields["suplier_id"];

        $suplier_array=_shn_or_get_suplier_name($suplier_id);
        $suplier_name=$suplier_array[$suplier_id];
        //$category=$ims->fields["category"];

	$table_row ["name"]= $ims->fields["item_name"];
	$table_row ["amount"]= $ims->fields["amount"];
        $unit=$ims->fields["unit"];
        $unit_name=get_unit_name($unit);
	$table_row ["unit"]= $unit_name;
	$table_row ["manu_date"]= $ims->fields["manufactured_date"];
	$table_row ["exp_date"]= $ims->fields["expire_date"];

        $sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims3=$db->Execute($sql3);

	$table_row ["inventory"]=  $ims3->fields['inventory_name'];
	$ims3->fields['suplier']=$suplier_name;

	array_push($table_data,$table_row);

        $ims->MoveNext();

    }*/
    //global $global;
    //$db=$global["db"];

	$table_data=array();
	$table_data=_shn_ims_expired_item_report();
	$title="Expired Items Report";
	$text="These Are the records about items that are already expired";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    	shn_pdf_report_fopen('expired_items',$ims_report_keyword_arr );
   	shn_pdf_report_add_page('pageone');
    	shn_pdf_report_add_title($title);
   	shn_pdf_report_add_table($table_header,$table_data);
    	shn_pdf_report_close();

	report_download_link('shn_ims_expired_item_report');

    
}

function _shn_ims_expired_item_ods()
{
    $table_data=array();
    $table_data=_shn_ims_expired_item_report();
    $title="Expired Items Report";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    shn_ods_report_fopen('expired_items',$ims_report_keyword_arr );
    shn_ods_report_add_sheet('pageone');
    shn_ods_report_add_title($title);
    shn_ods_report_add_table($table_header,$table_data);
    shn_ods_report_close();

}

function shn_ims_destroyed_item()
{
    /*global $global;
    $db=$global['db'];
    $state="destroyed";

    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'manu_date'=>'Manufactured Date', 'exp_date'=>'Expire Date', 'inventory'=>'Inventory', 'suplier'=>'Suplier');
    $table_data = array();
    $row_count = 0;

    $sql1="SELECT inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state_des';";
    $ims1=$db->Execute($sql1);

    $suplier_array=array();

    while (!$ims1==NULL && !$ims1->EOF)
    {
	$table_row = "row".$row_coount++;
        $table_row = array();

	$inv_id=$ims1->fields['inv_id'];
        $suplier_id=$ims1->fields['suplier_id'];
        $suplier_array=_shn_or_get_suplier_name($suplier_id);
        $suplier_name=$suplier_array[$suplier_id];
        $item_name=$ims1->fields['item_name'];
        $amount=$ims1->fields['amount'];
        $unit=$ims1->fields['unit'];
        $unit_name=get_unit_name($unit);
        $manufactured_date=$ims1->fields['manufactured_date'];
        $expire_date=$ims1->fields['expire_date'];

        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims2=$db->Execute($sql2);
            
        $inventory_name=$ims2->fields['inventory_name'];

	$table_row['name']=$item_name;
	$table_row['amount']=$amount;
	$table_row['unit']=$unit_name;
	$table_row['manu_date']=$manufactured_date;
	$table_row['exp_date']=$expire_date;
	$table_row['inventory']=$inventory_name;
	$table_row['suplier']=$suplier_name;

	array_push($table_data,$table_row);

	$ims1->MoveNext();
    }*/

	$table_data=array();
	$table_data=_shn_ims_destroyed_item_report();
	//print("Mahesh");
	//print_r($table_data);
    
	$title="Destroyed Items Report";
	$text="These Are the records about items that are already destroyed";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    	shn_pdf_report_fopen('destroyed_items',$ims_report_keyword_arr );
   	shn_pdf_report_add_page('pageone');
    	shn_pdf_report_add_title($title);
   	shn_pdf_report_add_table($table_header,$table_data);
    	shn_pdf_report_close();

	report_download_link('shn_ims_expired_item_report');

        

}

function _shn_ims_destroyed_item_ods()
{
    $table_data=array();
    $table_data=_shn_ims_destroyed_item_report();
    $title="Destroyed Items Report";
    $text="These Are the records about items that are already expired";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    shn_ods_report_fopen('destroyed_items',$ims_report_keyword_arr );
    shn_ods_report_add_sheet('pageone');
    shn_ods_report_add_title($title);
    shn_ods_report_add_table($table_header,$table_data);
    shn_ods_report_close();

}

function _shn_ims_reorder_level_report_pdf()
{



    /*global $global;
    $db=$global["db"];
    $table_header=array('name' =>'Item Name', 'amount' => 'Amount', 'unit'=>'Unit', 'inventory'=>'Inventory');
    $table_data = array();
    $row_count = 0;
        //$item_search=$_POST['item_name_search'];
        //$category_search=$_POST['itemcat'];
        //print ($item_search);
    $sql1="SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level;";
    $ims1=$db->Execute($sql1);
    
    
    $state = "destroyed";
        //$state_des="destroyed";
    $sum_amount=0;
        //print time();
        //print ("\n");
        
     while (!$ims1==NULL && !$ims1->EOF)
        {
	    $table_row = "row".$row_coount++;
            $table_row = array();

            $catalog_id_min=$ims1->fields['catalog_id'];
            //print $item_id_min;
            $inv_id_min=$ims1->fields['inv_id'];
            //print $inv_id_min;
            $minimum_quantity=$ims1->fields['minimum_quantity'];
            
            //print $minimum_quantity;
            $unit=$ims1->fields['unit'];
            
            $unit_name=get_unit_name($unit);

            $sql2 = "SELECT unit,amount FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min'AND state!='$state';";
            $ims2 =$db->Execute($sql2);
            //print $sql2;
            //print $sql2;
            //print $sql2;
            while(!$ims2==NULL && !$ims2->EOF)
            {
            //$sum_amount = $ims2->fields['SUM(amount)'];
            $current_unit=$ims2->fields['unit'];
            $current_amount=$ims2->fields['amount'];
                        
            
    $multiplier=unit_converter($unit,$current_unit);
    
    
    $current_amount_convert=$current_amount*$multiplier;
    
    $sum_amount=$sum_amount+$current_amount_convert;
    
    //$total_amount=$sum_amount;
    
            $ims2->MoveNext();
            }
    
//$sum_amount=0;
        if($sum_amount<$minimum_quantity)
            {
                $total_amount=$sum_amount;
                $sum_amount=0;
                $sql3 = "SELECT item_id,item_name,unit FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min';";
                $ims3 = $db->Execute($sql3);
    
            
                //print $sql3;

                $sql4 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_min';";
                $ims4 = $db->Execute($sql4);
                $inventory_name=$ims4->fields['inventory_name'];
                //print $sql2;
                //print $sql4;

                $item_id=$ims3->fields["item_id"];

            if($item_id!=null)
            {
                   
                //$category=$ims2->fields["category"];
                $item_name=$ims3->fields["item_name"];
                //$amount=$ims2->fields["amount"];
                //$amount=$current_amount + $amount;
                $unit=$ims3->fields["unit"];
                //$manufactured_date=$ims->fields["manufactured_date"];
                //$expire_date=$ims3->fields["expire_date"];

		$table_row['name']=$item_name;
		$table_row['amount']=$total_amount;
		$table_row['unit']=$unit_name;
		$table_row['inventory']=$inventory_name;
		
    	    }
    }
    else if($sum_amount>=$minimum_quantity)
    {
        $sum_amount=0;
    }
	array_push($table_data,$table_row);
        $ims1->MoveNext();
    }*/

	$table_data=array();
	$table_data=_shn_ims_reorder_level_report();

	$title="Items Re-Order Level Report";
	$text="These Are the records about items that are already gone below the re-order level of particular inventory";
	
	$ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    	shn_pdf_report_fopen('reorder_level',$ims_report_keyword_arr );
   	shn_pdf_report_add_page('pageone');
    	shn_pdf_report_add_title($title);
   	shn_pdf_report_add_table($table_header,$table_data);
    	shn_pdf_report_close();

	report_download_link('shn_ims_expired_item_report');	


}

function _shn_ims_reorder_level_report_ods()
{
    $table_data=array();
    $table_data=_shn_ims_destroyed_item_report();
    $title="Item Re-Order Level Report";
    $text="These Are the records about items that are already gone below the re-order level of particular inventory";
	
    $ims_report_keyword_arr = array('mod'=>'ims','report'=>'inventory','report1'=>'items','users'=>'all');

    shn_ods_report_fopen('reorder_level',$ims_report_keyword_arr );
    shn_ods_report_add_sheet('pageone');
    shn_ods_report_add_title($title);
    shn_ods_report_add_table($table_header,$table_data);
    shn_ods_report_close();
}





?>
