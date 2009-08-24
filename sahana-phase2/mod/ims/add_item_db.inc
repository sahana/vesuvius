<?php
/**
* Sahana Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage    
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;

include_once ("add_item.inc");    
include_once ("errors.inc");
include_once ('lib_ims.inc');


function _shn_ims_add_item_db()
{
        
    global $global;
    $db = $global["db"];
    $item = trim($_POST['item_name']);
    $suplier_id = trim($_POST['suplier_id']);
    $parent_id = trim($_POST['parent_id']);
    $amou = trim($_POST['amount']);
    $cost_per_unit = trim($_POST['cost_per_unit']);
    $unit = trim($_POST['unit_select']);
    $inv_id = trim($_POST['inv_id']);
    $manufactured_date = trim($_POST['manufactured_date']);
    $expire_date = trim($_POST['expire_date']);

    
    $date = date("Y-m-d");
    $total_amount = _shn_ims_sum_amount($parent_id,$inv_id);
    $base_unit = convert_to_base_unit($unit);
    $converted_amount = $amou*unit_converter($base_unit,$unit);
    $total_amount = $total_amount + $converted_amount;
    $predict_amount = 0;

        
    $state = "available";

    $q = "SELECT * FROM ims_item_records;";
    $ims = $db->Execute($q);
    if ($ims == NULL) {
        add_error(SHN_ERR_IMS_ITEM_TABLE_EXISTS);
        
    } else {
        $sql = " INSERT INTO ims_item_records (catalog_id,inv_id,suplier_id,item_name,amount,cost_per_unit,unit,manufactured_date,expire_date,state,inserted_date,total_amount,predict_amount) VALUES ('$parent_id','$inv_id','$suplier_id','$item','$amou','$cost_per_unit','$unit','$manufactured_date','$expire_date','$state','$date','$total_amount','$predeict_amount');";
        $ims = $db->Execute($sql);
        
        $sql = "SELECT item_id FROM ims_item_records ORDER BY item_id DESC";
        $ims2 = $db->Execute($sql);
        $item_id = $ims2->fields['item_id'];
        
        $sql = "INSERT INTO ims_item_amount_history (item_id, first_amount, unit) VALUES ('{$item_id}', '{$amou}', '{$unit}');";
        $ims3 = $db->Execute($sql);
      
    _shn_ims_expire_date_check();
    add_confirmation($item . _t(' Item was successfully added'));

    $_POST['item_name'] = "";
    $_POST['amount'] = "";
    $_POST['cost_per_unit'] = "";
    $_POST['manufactured_date'] = "";
    $_POST['expire_date'] = "";
    }
    shn_ims_add_item_main_page();
    
        
}

function _shn_ims_validate_additemform()
{
    global $global;
    $error_flag = false;
    //clean_errors();
    $item_name = trim($_POST['item_name']);
    $parent_id = trim($_POST['parent_id']);
    $amount = trim($_POST['amount']);
    $manufactured_date = trim($_POST['manufactured_date']);
    $expire_date = trim($_POST['expire_date']);
    $cost_per_unit = trim($_POST['cost_per_unit']);
    $unit = trim($_POST['unit_select']);

      
    //this checks whether name entered in the add main form
    if ($item_name == null) {
        add_error(SHN_ERR_IMS_ITEM_NAME_INCOMPLETE);
        $error_flag = true;
    }
    if ($amount == null || $amount < 0) {
        add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
        $error_flag = true;
    }
    if ($amount != NULL) {
        if (!is_numeric($amount)) {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
            $error_flag = true;
        }
    }

    if ($unit == null) {
        add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
        $error_flag = true;
    }

    if (trim($_POST['inv_id']) == null) {
        add_error(SHN_ERR_IMS_INVENTORY_INCOMPLETE);
        $error_flag = true;
    }
    
    $cost_per_unit = trim($_POST['cost_per_unit']);
    
    if ($cost_per_unit != null) {
        if (!is_numeric($cost_per_unit)) {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
            $error_flag = true;
        }
    }
    
    if ($cost_per_unit < 0) {
        add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
        $error_flag = true;
    }
    
    if (!shn_valid_date($manufactured_date) || !shn_valid_date($expire_date)) {
        $error_flag = true;
    }

    if ($manufactured_date != null || $expire_date != null) {
        if (_shn_ims_date_validate($manufactured_date)) {
            $error_flag = true;
        }
    
        if (_shn_ims_date_validate($expire_date)) {
            $error_flag = true;
        }
        $date_diff = _shn_ims_count_days($manufactured_date,$expire_date);
        if ($date_diff < 0) {
            add_error(SHN_ERR_IMS_MANUFACTURED_DATE_INVALID);
            $error_flag = true;
        }
    }
    

    return $error_flag;
}
?>
