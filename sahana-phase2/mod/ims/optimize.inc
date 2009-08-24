<?php
/**
* Sahana Inventory Management System main page
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright        Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage        ims
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

//include_once $global['approot']."/inc/lib_form.inc";
//include_once $global['approot']."/inc/lib_errors.inc";
include_once "lib_ims.inc";
include_once "errors.inc";

/**
****************************************************************************************************************
*******************************            Relation Item            ********************************************
****************************************************************************************************************
**/

function _shn_ims_relation_item()
{
?>

    <h1 align="center"><?php print _t("Select Relative Item/Items"); ?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("relation_item_page",null,$form_opts);
    $depth = get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();
}

function _shn_ims_relation_item_page()
{
    $depth = get_max_depth();
    $parent_id = trim($_POST['0']);
    
    for ($i = 1; $i < $depth; $i++) {
        $parent_id = trim($_POST[$i]);
    
        if ($parent_id == null) {
            $parent_id = $_POST[$i - 1];
            break;
        }
    }
    global $global;
    $db = $global["db"];
    shn_form_fopen("relation_item_table");
    shn_form_fsopen(_t("Inventory Selection"));

    $inventory_array = array();
    $inventory_array['all'] = "All Inventories";
    $q0 = "SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0 = $db->Execute($q0);
    
    while ($ims0 != NULL && !$ims0->EOF) {
        
        $inventory_array[$ims0->fields['inv_uuid']] = $ims0->fields['inventory_name']; //}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_t('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
    shn_form_fsclose();

    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_submit("Submit");
    shn_form_fclose();

}

function _shn_ims_relation_item_table()
{
    global $global;
    $db = $global["db"];

    $parent_id = trim($_POST['parent_id']);
    $inv_id = trim($_POST['inv_id']);
    
?>
<h1 align="center"><?php print(_t("Relative Items Selection")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
    <td><?=_t("Item") ?></td>
    <td><?=_t("Inventory") ?></td>
    <td><?=_t("Unit") ?></td>
    <td><?=_t("Available amount") ?></td>
    <td><?=_t("Action ") ?></td>
        
        
            
    </tr>
    </thead>
    <tbody>
<?php

        if ($inv_id == "all") {
            $sql1 = "SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id';";
            $ims1 = $db->Execute($sql1);
            //$inventory_name1="All Inventories";

        } else {
            $query = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
            $ims_query = $db->Execute($query);
            $inventory_name1 = $ims_query->fields['inventory_name'];
            $sql1 = "SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id' AND inv_id='$inv_id';";
            $ims1 = $db->Execute($sql1);
            
        }
        
        while (!$ims1 == NULL && !$ims1->EOF) {

        if ($inv_id == "all") {
             $inv_id_temp = $ims1->fields['inv_id'];
             $query = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id_temp';";
             $ims_query = $db->Execute($query);
             $inventory_name1 = $ims_query->fields['inventory_name'];
        } else {
            $inv_id_temp = $inv_id;
        }

    $catalog_id = $ims1->fields['catalog_id'];
    $item_name = $ims1->fields['item_name'];
    $amount = $ims1->fields['amount'];
    $unit = $ims1->fields['unit'];
    $base_unit = convert_to_base_unit($unit);
    $unit_name = get_unit_name($base_unit);

    $sum_amount = _shn_ims_sum_amount($catalog_id,$inv_id);


?>
    <tr>
    <td><?php print $item_name; ?></td>
    <td><?php print $inventory_name1; ?></td>
    <td><?php print $unit_name; ?></td>
    <td><?php print $sum_amount; ?></td>
    <td><!--<a href="index.php?mod=ims&act=alternate_item_db&catalog_id=<?php echo $catalog_id; ?>&parent_id=<?php echo $parent_id; ?>&inv_id=<?php echo $inv_id; ?>"><?php print ("Alternate"); ?></a>--><a href="index.php?mod=ims&act=relation_item_db&catalog_id=<?php echo $catalog_id; ?>&parent_id=<?php echo $parent_id; ?>&inv_id=<?php echo $inv_id; ?>"><?php print ("Relation"); ?></a></td>
    </tr>
<?php
    $ims1->MoveNext();
    }
?>
</tbody>
</table>
<?php
}

function _shn_ims_relation_item_db($parent_id,$catalog_id,$inv_id)
{
    global $global;
    $db = $global["db"];

    $relation = $catalog_id;

//-------------------------------- Validation ----------------------------


    if ($inv_id == 'all') {
        $sql = "SELECT * FROM ims_relation WHERE catalog_id='$parent_id' AND relation='$relation';";
        $ims = $db->Execute($sql);
        
        if ($ims->fields['catalog_id'] != null) {
        add_error(SHN_ERR_IMS_RELATION_ITEM_EXISTS);
        shn_ims_relation_item();
        return false;
        }
        }
        if ($inv_id != 'all') {
            $sql = "SELECT * FROM ims_relation WHERE catalog_id='$parent_id' AND relation='$relation' AND inv_id='$inv_id';";
            $ims = $db->Execute($sql);
            
           if ($ims->fields['catalog_id'] != null) {
               add_error(SHN_ERR_IMS_RELATION_ITEM_EXISTS);
               shn_ims_relation_item();
               return false;
           }
        }

//-------------------------------- Validation End ------------------------

        $q = "SELECT * FROM ims_relation;";
        $ims = $db->Execute($q);
        if ($ims == NULL) {
            //$error=true;
            add_error(SHN_ERR_IMS_RELATION_TABLE_EXISTS);
            //return false;

        } else {
        if ($inv_id == "all") {
            $sql1 = "SELECT * FROM ims_inventory_records;";
            $ims1 = $db->Execute($sql1);
            while (!$ims1 == NULL && !$ims1->EOF) {
                $inv_id_all = $ims1->fields['inv_uuid'];
                $sql2 = "INSERT INTO ims_relation (catalog_id,inv_id,relation) VALUES ('$parent_id','$inv_id_all','$relation');";
                $ims2 = $db->Execute($sql2);

                $ims1->MoveNext();
            }
        //$inv_id=-1;

        } else {
            $sql3 = "INSERT INTO ims_relation (catalog_id,inv_id,relation) VALUES ('$parent_id','$inv_id','$relation');";
            $ims3 = $db->Execute($sql3);

        }
        add_confirmation(_t("Relative item successfully set"));
        shn_ims_relation_item();
    }
}

/**
****************************************************************************************************************
********************************* Alternate Item ***************************************************************
****************************************************************************************************************
**/
function _shn_ims_alternate_item()
{
    ?>

    <h1 align="center"><?php print _t("Select Alternative Item/Items"); ?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("alternate_item_page",null,$form_opts);
    $depth = get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();

}

function _shn_ims_alternate_item_page()
{
    $depth = get_max_depth();
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for ($i = 1; $i < $depth; $i++) {
        $parent_id = trim($_POST[$i]);
    
        if ($parent_id == null) {
            $parent_id = $_POST[$i - 1];
            break;
        }
    }
    global $global;
    $db = $global["db"];
    shn_form_fopen("alternate_item_table");
    shn_form_fsopen(_t("Inventory Selection"));

    $inventory_array = array();
    $inventory_array['all'] = "All Inventories";
    $q0 = "SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0 = $db->Execute($q0);
    
    while ($ims0 != NULL && !$ims0->EOF) {
        
        $inventory_array[$ims0->fields['inv_uuid']] = $ims0->fields['inventory_name']; //}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_t('If this box does not contain preferred inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
    shn_form_fsclose();
    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_submit(_t("Submit"));
    shn_form_fclose();

}

function _shn_ims_alternate_item_table()
{
    global $global;
    $db = $global["db"];

    $parent_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];
    
?>
<h1 align="center"><?php print(_t("Alternative Items Selection")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
    <td><?=_t("Item") ?></td>
    <td><?=_t("Inventory") ?></td>
    <td><?=_t("Unit") ?></td>
    <td><?=_t("Available amount") ?></td>
    <td><?=_t("Action ") ?></td>
        
        
            
    </tr>
    </thead>
    <tbody>
<?php

    if ($inv_id == "all") {
        $sql1 = "SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id';";
        $ims1 = $db->Execute($sql1);
        $inventory_name1 = "All Inventories";
    } else {
        $sql1 = "SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id' AND inv_id='$inv_id';";
        $ims1 = $db->Execute($sql1);
        
        $query = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims_query = $db->Execute($query);
        $inventory_name1 = $ims_query->fields['inventory_name'];
    }
    while (!$ims1 == NULL && !$ims1->EOF) {
        $catalog_id = $ims1->fields['catalog_id'];
        $item_name = $ims1->fields['item_name'];
        $amount = $ims1->fields['amount'];
        $unit = $ims1->fields['unit'];
        $base_unit = convert_to_base_unit($unit);
        $unit_name = get_unit_name($base_unit);
        $sum_amount = _shn_ims_sum_amount($catalog_id,$inv_id);
?>
    <tr>
    <td><?php print $item_name; ?></td>
    <td><?php print $inventory_name1; ?></td>
    <td><?php print $unit_name; ?></td>
    <td><?php print $sum_amount; ?></td>
    <td><a href="index.php?mod=ims&act=alternate_item_db&catalog_id=<?php echo $catalog_id; ?>&parent_id=<?php echo $parent_id; ?>&inv_id=<?php echo $inv_id; ?>"><?php print ("Alternate"); ?></a><!--<?php print (" , "); ?><a href="index.php?mod=ims&act=relation_item_db&catalog_id=<?php echo $catalog_id; ?>&parent_id=<?php echo $parent_id; ?>&inv_id=<?php echo $inv_id; ?>"><?php print ("Relation"); ?></a></td>-->
    </tr>
<?php
    $ims1->MoveNext();
        }
?>
</tbody>
</table>
<?php
}

function _shn_ims_alternate_item_db($parent_id,$catalog_id,$inv_id)
{
    global $global;
    $db = $global["db"];
    $alternate = $catalog_id;

    $q = "SELECT unit FROM ims_item_records WHERE catalog_id='$parent_id';";
    $i = $db->Execute($q);

    $q1 = "SELECT unit FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $i1 = $db->Execute($q1);

    if (convert_to_base_unit($i->fields['unit']) != convert_to_base_unit($i1->fields['unit'])) {
       add_error(SHN_ERR_IMS_UNIT_MISMATCH);
       shn_ims_alternate_item();
            return false;
      }

    if ($inv_id == 'all') {
        $sql = "SELECT * FROM ims_alternate WHERE catalog_id='$parent_id' AND alternate='$alternate';";
        $ims = $db->Execute($sql);
        
            if ($ims->fields['catalog_id'] != null) {
                add_error(SHN_ERR_IMS_ALTERNATE_ITEM_EXISTS);
                shn_ims_alternate_item();
                return false;
          }
        }
    if ($inv_id != 'all') {
            $sql = "SELECT * FROM ims_alternate WHERE catalog_id='$parent_id' AND alternate='$alternate' AND inv_id='$inv_id';";
            $ims = $db->Execute($sql);
            
            if ($ims->fields['catalog_id'] != null) {
                add_error(SHN_ERR_IMS_ALTERNATE_ITEM_EXISTS);
                shn_ims_alternate_item();
                return false;
            }
        }

        $q = "SELECT * FROM ims_alternate;";
        $ims = $db->Execute($q);
        if ($ims == NULL) {
            $error = true;
            add_error(SHN_ERR_IMS_ALTERNATE_TABLE_EXISTS);
            return false;
        } else {
            $sql1 = "INSERT INTO ims_alternate (catalog_id,inv_id,alternate) VALUES ('$parent_id','$inv_id','$alternate');";
            $ims1 = $db->Execute($sql1);
            add_confirmation(_t('Alternate item successfully set'));
            shn_ims_alternate_item();
        }
}



/**
****************************************************************************************************************
**********************************     Optimize Inventory  *****************************************************
****************************************************************************************************************
**/

function _shn_ims_optim_inventory()
{
    global $global;
    $db = $global["db"];
    $form_opts['name'] = "optim_inventory";
    shn_form_fopen("prediction_inv",null,$form_opts);
    shn_form_fsopen(_t("Inventory Selection"));
    $inventory_array = array();
    $q0 = "SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0 = $db->Execute($q0);
    
    while ($ims0 != NULL && !$ims0->EOF) {
        
        $inventory_array[$ims0->fields['inv_uuid']] = $ims0->fields['inventory_name']; //}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_t('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
    shn_form_fsclose();

    shn_form_fsopen(_t("Prediction Type"));
    $prediction_array = array();
    $prediction_array["send"] = "Sent";
    $prediction_array["receive"] = "Receive";
    $prediction_array["available"] = "Available";
    shn_form_select($prediction_array,_t("Prediction Type : "),'prediction_type','size="1"',null);
    shn_form_fsclose();

    shn_form_fsopen("Algorithm Selection");
    $algorithm_array = array();
    $algorithm_array["single"] = "Single Exponential Smoothing";
    $algorithm_array["double"] = "Double Exponential Smoothing";
    shn_form_select($algorithm_array,_t("Algorithm Selection : "),'algorithm','size="1"',null);
    shn_form_fsclose();
    

    shn_form_fsopen(_t("Time Period to make Prediction"));
    //shn_form_text();
    shn_form_text(_t("Time Period : "),'time_amount','size="20"',array('help'=>_t('Time period which you are going to make prediction')));
    $time_period_array = array();
    $time_period_array["day"] = "day/days";
    $time_period_array["week"] = "week/weeks";
    $time_period_array["month"] = "month/months";
    shn_form_select($time_period_array,_t("Time Period : "),'time_period','size="1"',null);
    shn_form_fsclose();
    shn_form_button(_t("Customized Report"),"onClick='change_action_inventory(\"customizedreport\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    //shn_form_submit("Predict");

?>
<center>
<?php
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    shn_form_button(_t("Daily Report"),"onClick='change_action_inventory(\"dailyreport\")'",$extra_opts);
    shn_form_button(_t("Weekly Report"),"onClick='change_action_inventory(\"weeklyreport\")'",$extra_opts);
    shn_form_button(_t("Monthly Report"),"onClick='change_action_inventory(\"monthlyreport\")'",$extra_opts);
    
    
    //shn_form_hidden(array('parent_id'=>$parent_id));
    
?>
</center>
<?php
    shn_form_fclose();
}

function _shn_ims_prediction_inv_actions()
{
    global $global;
    $db = $global["db"];
    $inv_id = trim($_POST['inv_id']);
    $time_amount = trim($_POST['time_amount']);
    $time = trim($_POST['time_period']);
    $action = trim($_POST['action']);
    $prediction_type = trim($_POST['prediction_type']);
    $algorithm = trim($_POST['algorithm']);

    if ($action == "dailyreport") {
        $time_period = 1;

    }
    if ($action == "weeklyreport") {
         $time_period = 7;
    }
    if ($action == "monthlyreport") {
        $time_period = 30;
    }
    if ($action == "customizedreports") {
        if ($time == "day") {
            $time_period = $time_amount;
        }
        if ($time == "week") {
             $time_period = $time_amount * 7;
        }
        if ($time == "month") {
            $time_period = $time_amount * 30;
        }

    }

    _shn_ims_optim_inventory_db($inv_id,$time_period,$prediction_type,$algorithm);
}

function _shn_ims_optim_inventory_db($inv_id,$time_period,$prediction_type,$algorithm)
{
    global $global;
    $db = $global["db"];
    //$inv_id=$_POST['inv_id'];
    $form_opts['name'] = "optim_inventory_relation";

    $sql0 = "DELETE FROM ims_optimization;";
    $ims0 = $db->Execute($sql0);

    $sql1 = "SELECT * FROM ims_item_records WHERE inv_id='$inv_id';";
    $ims1 = $db->Execute($sql1);
    //$time_period=1;
    while (!$ims1 == NULL && !$ims1->EOF) {
        $catalog_id = $ims1->fields['catalog_id'];
       //_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
//-------test
    if ($prediction_type == "send") {
        _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period);
        /*if ($algorithm == "double") {
            $double_forecasted_value=_shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
       }*/
    }
    if ($prediction_type == "receive") {
        _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period);
        /*if($algorithm=="double") {
            $double_forecasted_value=_shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        }*/
    }
    if ($prediction_type == "available") {
        _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
        /*if ($algorithm == "double") {
            $double_forecasted_value=_shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        }*/
        }
       
//-------
        $ims1->MoveNext();
        }

?>
    <h1 align="center"><?php print _t("Forecasting by Inventory"); ?></h1>
<?php
    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $date_after = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string = "Prediction Report Since " . $current_date . " " . "To" . " " . $date_after;
?>
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
    <div id="result">
<?php
    shn_form_fopen("optim_inventory_relation",null,$form_opts);
    //shn_form_fsopen();
?>
    <table>
    <thead>
    <td><?php print (_t("Item name")); ?></td>
    <td><?php print (_t("Inventory")); ?></td>
    <td><?php print (_t("Forecasted Value")); ?></td>
    <td><?php print (_t("Re-Order Level")); ?></td>
    <td><?php print (_t("Unit")); ?></td>
    <td><?php print (_t("Actions")); ?></td>
    </thead>
    <tbody>
<?php
    $sql2 = "SELECT * FROM ims_optimization GROUP BY catalog_id;";
    $ims2 = $db->Execute($sql2);
    
    while (!$ims2 == NULL && !$ims2->EOF) {
        $catalog_id = $ims2->fields['catalog_id'];
        $q1 = "SELECT * from ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
        $ims_q1 = $db->Execute($q1);
        $minimum_quantity = $ims_q1->fields['minimum_quantity'];
        $minimum_unit = $ims_q1->fields['unit'];
        $multiplier = unit_converter($minimum_unit,convert_to_base_unit($minimum_unit));
        $minimum_quantity = $minimum_quantity*$multiplier;
        $sql3 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims3 = $db->Execute($sql3);
        $actual_value = $ims3->fields['actual_value'];
        $forecasted_value = $ims3->fields['forecasted_value'];
        $unit = $ims3->fields['unit'];
        $unit_name = get_unit_name($unit);
        $week = $ims3->fields['week'];
        if ($algorithm == "single") {
            $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
            $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
        }
        if ($algorithm == "double") {
            _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
            $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
        }

        $sql4 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
        $ims4 = $db->Execute($sql4);
        $item_name = $ims4->fields['item_name'];

        $sql5 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims5 = $db->Execute($sql5);
        
        $inventory_name = $ims5->fields['inventory_name'];
?>
    <tr>
    <td><?php print $item_name; ?></td>
    <td><?php print $inventory_name; ?></td>
<?php
    if ($algorithm == "double") {
?>
    <td><?php print $double_forecasted_value; ?></td>
<?php

    } else {
?>
    <td><?php print $forecast; ?></td>
<?php

    }
    if ($minimum_quantity == 0) {
?>
        <td><a href="index.php?mod=ims&act=view_edit_reorder_page&catalog_id=<?php echo $catalog_id; ?>&inv_id=<?php echo $inv_id; ?>"><?php print ("Not Set"); ?></a></td>
<?php

    } else {
?>
        <td><?php print $minimum_quantity; ?></td>
<?php

    }
?>
    <td><?php print $unit_name; ?></td>
    <td><a href="index.php?mod=ims&act=optim_relation_inventories&catalog_id=<?php echo $catalog_id; ?>&inv_id=<?php echo $inv_id; ?>&time_period=<?php echo $time_period; ?>&algorithm=<?php echo $algorithm; ?>"><?php print ("Relative Items"); ?></a></td>
    </tr>
<?php
    //$ims3->MoveNext();
    //}
    $ims2->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>
<?php
//----Pie Chart Creation

    shn_form_fclose();
    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $date_after = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string = _t("Pie Chart to forecasting Since ") . $current_date . " " . _t("To") . " " . $date_after;
?>	
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
<?php
    $sql9 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims9 = $db->Execute($sql9);
    $j = 0;
    while (!$ims9 == NULL && !$ims9->EOF) {
        $j = $j + 1;
        $ims9->MoveNext();
    }
//Prediction by inventory Pie chart Creation
    $temp = array();
    $catalog_array = array();
    $data = array();
    $data_array = array();
    $temp_array = array();
    $temp_array1 = array();
    $forecast = 0;
    //$temp[0]="a";
    $i = 1;

    $actual_value_max = 0;
    $sql6 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims6 = $db->Execute($sql6);
    while (!$ims6 == NULL && !$ims6->EOF) {
        $catalog_id = $ims6->fields['catalog_id'];
        $temp[0] = $catalog_id;
        $temp_array[0] = "next Period";
        $temp_array1[0] = "Present Period";
        $sql8 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
        $ims8 = $db->Execute($sql8);
        $catalog_array[$i] = $ims8->fields['item_name'];

        $sql7 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims7 = $db->Execute($sql7);
        $actual_value = $ims7->fields['actual_value'];
        $forecasted_value = $ims7->fields['forecasted_value'];
        $week = $ims7->fields['week'];
        $unit = $ims7->fields['unit'];
        $unit_name = get_unit_name($unit);

//finding the maximum value
        if ($actual_value > $actual_value_max) {
            $actual_value_max = $actual_value;
        } else {
            ;
        }

//end of finding the maximum value
    //$temp = array($forecast);
    if ($algorithm == "single") {
        $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
        $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
    }
    if ($algorithm == "double") {
        _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);

    }

    array_push($temp_array,$forecast);
    array_push($temp_array1,$actual_value);
    //array_push($temp,$forecast);
    for ($a = 1; $a < $j + 1; $a++) {
        if ($a == $i) {
            $temp[$a] = $forecast;
        } else {
            $temp[$a] = 0;
        }
    }

    $i = $i + 1;
    //$data=array($temp);
    array_push($data,$temp);
    //$data[0][$i]=$temp;
    $ims6->MoveNext();
    }
    array_push($data_array,$temp_array1);
    array_push($data_array,$temp_array);
    _shn_ims_pie_chart($data,$catalog_array);
    print "<br>";
    $i = 3;
    _shn_ims_bar_chart_inventory($data_array,$catalog_array,$i,$actual_value_max);
?>
    <image src="tmp/pieChart.png"></image>
    <br>
    <br>
<?php
    print "<br>";
    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $date_after = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string = _t("Bar Chart to forecasting Since "). $current_date . " " . _t("To") . " " . $date_after;
?>	
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
<?php
?>
    <image src="tmp/barChart.png"></image>
<?php	

}

function _shn_ims_optim_relation_inventories($catalog_id,$inv_id,$time_period,$algorithm)
{
    global $global;
    $db = $global["db"];
    $sql = "DELETE FROM ims_optimization;";
    $ims = $db->Execute($sql);
?>
    <h1 align="center"><?php print(_t("Prediction Report for Relative items")); ?></h1>
<?php
    $sql1 = "SELECT * FROM ims_relation WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims1 = $db->Execute($sql1);
    while (!$ims1 == NULL && !$ims1->EOF) {
        $relation = $ims1->fields['relation'];
        _shn_ims_insert_data_to_predict($relation,$inv_id,$time_period);
        $ims1->MoveNext();
    }
    //$catalog_id_relation_to=$catalog_id;
    $sql7 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $ims7 = $db->Execute($sql7);
    $item_name_relation_to = $ims7->fields['item_name'];
?>
    <div id="result">
    <table>
    <thead>
    <td><?php print(_t("Item Name")); ?></td>
    <td><?php print(_t("Inventory")); ?></td>
    <td><?php print(_t("Forecasted Amount")); ?></td>
    <td><?php print(_t("Re-Order Level")); ?></td>
    <td><?php print(_t("Unit")); ?></td>
    <td><?php print(_t("Relation to")); ?></td>
    </thead>
<?php
    $sql2 = "SELECT * FROM ims_optimization GROUP BY catalog_id;";
    $ims2 = $db->Execute($sql2);
    while (!$ims2 == NULL && !$ims2->EOF) {
        $catalog_id = $ims2->fields['catalog_id'];
        $sql3 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims3 = $db->Execute($sql3);
        $actual_value = $ims3->fields['actual_value'];
        $forecasted_value = $ims3->fields['forecasted_value'];
        $unit = $ims3->fields['unit'];
        $week = $ims3->fields['week'];
        if ($algorithm == "single") {
             $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
             $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
        }
        if ($algorithm == "double") {
            _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
            $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
        }
        
        $sql4 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
        $ims4 = $db->Execute($sql4);
        $item_name = $ims4->fields['item_name'];
       
        $sql5 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims5 = $db->Execute($sql5);
        $inventory_name = $ims5->fields['inventory_name'];
        
        $unit_name = get_unit_name($unit);
        //shn_form_label(_t("Unit :"),$unit_name,null);
        $sql6 = "SELECT * FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
        $ims6 = $db->Execute($sql6);
        $minimum_quantity = $ims6->fields['minimum_quantity'];
        $minimum_unit = $ims6->fields['unit'];
        $multiplier = unit_converter($minimum_unit,convert_to_base_unit($minimum_unit));
        $minimum_quantity = $minimum_quantity*$multiplier;
        if ($minimum_quantity == 0) {
            $minimum_quantity = "Not Set";
        } else {
            ;
        }
?>
    <br>
    <tr>
    <td><?php print $item_name; ?></td>
    <td><?php print $inventory_name; ?></td>
    <td><?php print $forecast; ?></td>
    <td><?php print $minimum_quantity; ?></td>
    <td><?php print $unit_name; ?></td>
    <td><?php print ($item_name_relation_to); ?></td>
    </tr>
<?php

    $ims2->MoveNext();
    }

?>	
    <tbody></tbody></table></div>
<?php

//****************
//Chart Generation
//******************
    $sql9 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims9 = $db->Execute($sql9);
    $j = 0;
    while (!$ims9 == NULL && !$ims9->EOF) {
        $j = $j + 1;
        $ims9->MoveNext();
    }
//Prediction by inventory Pie chart Creation
    $temp = array();
    $catalog_array = array();
    $data = array();
    $data_array = array();
    $temp_array = array();
    $temp_array1 = array();
    $forecast = 0;
    //$temp[0]="a";
    $i = 1;
    $sql6 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims6 = $db->Execute($sql6);
    $actual_value_max = 0;
    while (!$ims6 == NULL && !$ims6->EOF) {
        $catalog_id = $ims6->fields['catalog_id'];
        $temp[0] = $catalog_id;
        $temp_array[0] = "next Period";
        $temp_array1[0] = "Present Period";
        $sql8 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
        $ims8 = $db->Execute($sql8);
        $catalog_array[$i] = $ims8->fields['item_name'];
        $sql7 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims7 = $db->Execute($sql7);
        //while(!$ims3==NULL && !$ims3->EOF)
        //{
        $actual_value = $ims7->fields['actual_value'];
        $forecasted_value = $ims7->fields['forecasted_value'];
        $week = $ims7->fields['week'];
        $unit = $ims7->fields['unit'];
        $unit_name = get_unit_name($unit);

//Finding the maximum actual value to set the Y coardinate
    if ($actual_value > $actual_value_max) {
        $actual_value_max = $actual_value;
     } else {
        ;
     }
//end of Finding the maximum value
//$temp = array($forecast);
    if ($algorithm == "single") {
        $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
        $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
    }
    if ($algorithm == "double") {
        _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
    }
    array_push($temp_array,$forecast);
    array_push($temp_array1,$actual_value);
    //array_push($temp,$forecast);
    for ($a = 1; $a < $j + 1; $a++) {
        if ($a == $i) {
            $temp[$a] = $forecast;
        } else {
            $temp[$a] = 0;
        }
    }

    $i = $i + 1;
    //$data=array($temp);
    array_push($data,$temp);
    //$data[0][$i]=$temp;
    $ims6->MoveNext();
    }
    array_push($data_array,$temp_array1);
    array_push($data_array,$temp_array);
    
    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $date_after = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string = _t("Bar Chart to forecasting Since ") . $current_date . " " . _t("To") . " " . $date_after;
?>
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
<?php
    _shn_ims_pie_chart($data,$catalog_array);
    print "<br>";
    $i = 3;
    _shn_ims_bar_chart_inventory($data_array,$catalog_array,$i,$actual_value_max);

?>
    <image src="tmp/pieChart.png"></image>
<?php
    print "<br>";
    $string = _t("Bar Chart to forecasting Since ") . $current_date . " " . _t("To") . " " . $date_after;
?>
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
    <image src="tmp/barChart.png"></image>
<?php
//********************
//Chart Generation End
//********************

}

/**
****************************************************************************************************************
*********************************    optimize item *************************************************************
****************************************************************************************************************
**/

function _shn_ims_optim_item_main_page()
{
?>

    <h1 align="center"><?php print _t("Select Item to Predict"); ?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("prediction_page",null,$form_opts);
    $depth = get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();
}

function _shn_ims_prediction_page()
{
    $depth = get_max_depth();
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for ($i = 1; $i < $depth; $i++) {
        $parent_id = trim($_POST[$i]);
        if ($parent_id == null) {
            $parent_id = $_POST[$i - 1];
            break;
        }
    }
?>
<h1 align="center"><?php print _t("Item Prediction"); ?><br></h1>
    <dev id="report1">

    </dev>
<?php
    $form_opts['name'] = "optim_item";
    shn_form_fopen("prediction_report",null,$form_opts);
    shn_form_fsopen(_t("Selected Item"));
    shn_form_text(_t("* Item : "),'item_name','size="50" readonly=true',array('value'=>$item_name,'req'=>true));
    shn_form_fsclose();
    
    shn_form_fsopen(_t("Inventory Selection"));
    global $global;
    $db = $global["db"];
    $inventory_array = array();
    $q0 = "SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0 = $db->Execute($q0);
    
    while ($ims0 != NULL && !$ims0->EOF) {
        $inventory_array[$ims0->fields['inv_uuid']] = $ims0->fields['inventory_name']; //}
        $ims0->MoveNext();
        //$j=$j+1;

    }
    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_t('If this box does not contain preferred inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
    shn_form_fsclose();

    shn_form_fsopen("Prediction Type");
    $prediction_array = array();
    $prediction_array["send"] = "Sent";
    $prediction_array["receive"] = "Received";
    $prediction_array["available"] = "Available";
    shn_form_select($prediction_array,_t("Prediction Type : "),'prediction_type','size="1"',null);
    shn_form_fsclose();

    shn_form_fsopen(_t("Algorithm Selection"));
    $algorithm_array = array();
    //$algorithm_array["moving_average"]="Simple Moving Average";
    $algorithm_array["single"] = "Single Exponential Smoothing";
    $algorithm_array["double"] = "Double Exponential Smoothing";
    shn_form_select($algorithm_array,_t("Algorithm Selection : "),'algorithm','size="1"',null);
    shn_form_fsclose();

    shn_form_fsopen(_t("Time Period one to predict"));
    //shn_form_text();
    shn_form_text(_t("Time Period : "),'time_amount','size="20"',array('help'=>_t('Time period which you are going to make prediction')));
    $time_period_array = array();
    $time_period_array["day"] = "day/days";
    $time_period_array["week"] = "week/weeks";
    $time_period_array["month"] = "month/months";
    shn_form_select($time_period_array,_t("Time Period : "),'time_period','size="1"',null);
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    shn_form_button(_t("Customized Report"),"onClick='change_action(\"customizedreport\")'",$extra_opts);
    shn_form_fsclose();
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
?>
<center>
<?php
    //shn_form_hidden(array('parent_id'=>$parent_id));	
    shn_form_button(_t("Daily Report"),"onClick='change_action(\"dailyreport\")'",$extra_opts);
    shn_form_button(_t("Weekly Report"),"onClick='change_action(\"weeklyreport\")'",$extra_opts);
    shn_form_button(_t("Monthly Report"),"onClick='change_action(\"monthlyreport\")'",$extra_opts);
?>
</center>
<?php
    shn_form_hidden(array('action'=>'0'));
    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_fclose();
}

function _shn_ims_optim_item_actions()
{
    global $global;
    $db = $global["db"];

    $form_opts['name'] = "optim_item_actions";
    $q1 = "DELETE FROM ims_optimization;";
    $ims_q1 = $db->Execute($q1);

    $action = trim($_POST['action']);
    $prediction_type = trim($_POST['prediction_type']);
    $algorithm = trim($_POST['algorithm']);
    

    if ($action == 'dailyreport') {
?>
    <h1 align="center"><?php print(_t("Daily Report")); ?></h1>
        
<?php
    global $global;
    $db = $global["db"];

    $catalog_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];
    $time_period = 1;
    if ($prediction_type == "send") {
        _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "receive") {
        _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "available") {
        _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
?>
<?php

    }
    if ($action == 'weeklyreport') {
?>
    <h1 align="center"><?php print(_t("Weekly Report")); ?></h1> 
<?php
    global $global;
    $db = $global["db"];
    $catalog_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];
    $time_period = 7;
    if ($prediction_type == "send") {
        _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "receive") {
        _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "available") {
        _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
    }
    if ($action == 'monthlyreport') {
?>
    <h1 align="center"><?php print(_t("Monthly Report")); ?></h1>
<?php
    global $global;
    $db = $global["db"];
    $catalog_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];
    $time_period = 30;
    if ($prediction_type == "send") {
        _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "receive") {
        _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "available") {
        _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
    }
    if ($action == 'customizedreport') {
?>
    <h1 align="center"><?php print(_t("Customized Report")); ?></h1>
<?php
    global $global;
    $db = $global["db"];
    $catalog_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];
    $time_amount = trim($_POST['time_amount']);
    $time = trim($_POST['time_period']);
    if ($time == "day") {
        $time_period = $time_amount;
    }
    if ($time == "week") {
        $time_period = $time_amount * 7;
    }
    if ($time == "month") {
        $time_period = $time_amount * 30;
    }
    if ($prediction_type == "send") {
        _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "receive") {
        _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period);
    }
    if ($prediction_type == "available") {
         _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
    }

    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $date_after = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string = _t("Prediction Report Since ") . $current_date . " " . _t("To") . " " . $date_after;
?>
    <div><h3><b><em><?php print $string; ?></em></b></h3></div>
<?php
    
    shn_form_fopen("optimize_relation_items",null,$form_opts);
    shn_form_fsopen(_t("Prediction Records"));
    $sql1 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' ORDER BY week DESC;";
    $ims1 = $db->Execute($sql1);
    $actual_value = $ims1->fields['actual_value'];
    $forecasted_value = $ims1->fields['forecasted_value'];
    $unit = $ims1->fields['unit'];
    $week = $ims1->fields['week'];
    if ($algorithm == "single") {
        $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
        $forecasted_value = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
    }
    if ($algorithm == "double") {
        _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        $forecasted_value = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
    }
    $sql2 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $ims2 = $db->Execute($sql2);
    $item_name = $ims2->fields['item_name'];
    $sql3 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $ims3 = $db->Execute($sql3);
    $inventory_name = $ims3->fields['inventory_name'];
    $unit_name = get_unit_name($unit);
    $date = date("Y-m-d");
    shn_form_label(_t("Item Name :"),$item_name,null);
    
?>
    <br>
<?php
    shn_form_label(_t("Inventory Name :"),$inventory_name,null);
?>
    <br>
<?php
    shn_form_label(_t("Forecasted Value :"),$forecasted_value,null);
?>
    <br>
<?php
    shn_form_label(_t("Unit :"),$unit_name,null);
    
    shn_form_fsclose();
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    shn_form_button(_t("Relative Items"),"onClick='change_action_relation(\"relation\")'",$extra_opts);
    shn_form_button(_t("Re-Order level"),"onClick='change_action_relation(\"reorderlevel\")'",$extra_opts);
    //shn_form_button(_t("Monthly Report"),"onClick='change_action(\"monthlyreport\")'",$extra_opts);

?>
</center>
<?php
    shn_form_hidden(array('action'=>'0'));
    shn_form_hidden(array('catalog_id'=>$catalog_id));
    shn_form_hidden(array('inv_id'=>$inv_id));
    shn_form_hidden(array('time_period'=>$time_period));
    shn_form_hidden(array('forecated_value'=>$forecasted_value));
    shn_form_hidden(array('algorithm'=>$algorithm));
?>
<?php

//****************************
//*** Bar Chart Generation ***
//****************************

    $data = array();
    $temp = array();
    //push($inventory_array,$temp);

    $sql4 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims4 = $db->Execute($sql4);
    $j = 0;
    $actual_value_temp = 0;
    while (!$ims4 == NULL && !$ims4->EOF) {
         $week_chart = $ims4->fields['week'];
         $actual_value_chart = $ims4->fields['actual_value'];
         $forecasted_value_chart = $ims4->fields['forecasted_value'];
         $double_forecasted_value = $ims4->fields['double_forecasted_value'];

//Finding the maximum value
    if ($actual_value_chart > $actual_value_temp) {
        $actual_value_temp = $actual_value_chart;
    } else {
         ;
    }

     if ($algorithm == "single") {
         $alpha_temp = $week_chart + 1;
         $alpha_chart = 2 / $alpha_temp;
         $forecast_chart = _shn_ims_smoothing($forecasted_value_chart,$actual_value_chart,$alpha_chart);
         $temp = array($week_chart,$actual_value_chart,$forecasted_value_chart);
     }
     if ($algorithm == "double") {
          $forecast_chart = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
          $temp = array($week_chart,$actual_value_chart,$double_forecasted_value);
     }
    
    array_push($data,$temp);
    $j = $j + 1;
    $ims4->MoveNext();
    }
    $temp = array($week_chart + 1,0,$forecast_chart);
    array_push($data,$temp);
    shn_form_fclose();

    $j = $j + 2;
    
?>
     <br>
<?php
     _shn_ims_bar_chart($data,$j,$actual_value_temp);
   
    
?>
    <image src="tmp/barChart.png"></image>
<br>
     <!--<image src="tmp/lineChart.png"></image>-->
<?php
    
}

/**
***************************************** Validate Prediction Page ****************************************************
*/

function _shn_ims_validate_prediction_page()
{
    global $global;
    $db = $global["db"];

    $error_flag = false;

    $time_amount = trim($_POST['time_amount']);

    if ($time_amount == null) {
        add_error(SHN_ERR_IMS_TIME_AMOUNT_INCOMPLETE);
        $error_flag = true;
    }

    return $error_flag;

}

function _shn_ims_optimize_relation_items()
{
    global $global;
    $db = $global["db"];
    $catalog_id = trim($_POST['catalog_id']);
    $action = trim($_POST['action']);
    $inv_id = trim($_POST['inv_id']);
    $time_period = trim($_POST['time_period']);
    $forecasted_value = trim($_POST['forecast_chart']);
    $algorithm = trim($_POST['algorithm']);
    $sql4 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $ims4 = $db->Execute($sql4);
    $item_name_relation_to = $ims4->fields['item_name'];
    if ($action == "relation") {
         $sql = "DELETE FROM ims_optimization;";
         $ims = $db->Execute($sql);
         $sql1 = "SELECT * FROM ims_relation WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
         $ims1 = $db->Execute($sql1);
         while (!$ims1 == NULL && !$ims1->EOF) {
             $relation = $ims1->fields['relation'];
             _shn_ims_insert_data_to_predict($relation,$inv_id,$time_period);
             $ims1->MoveNext();
         }

    $string = "Relative item forecast for item " . $item_name_relation_to;
    $current_date = date("Y-m-d");
    list($year,$month,$day) = split("-",$current_date);
    $time_after_date = _shn_ims_timeafter($year, $month, $day, $time_period);
    $string1 = "Forecast since " . $current_date . "" . "To" . " " . $time_after_date;

?>
    <h1 align="center"><?php print $string; ?></h1>
    <h1 align="center"><?php print $string1; ?></h1>
    <div id="result">
    <table>
    <thead>
    <td><?php print (_t("Relational Item")); ?></td>
    <td><?php print (_t("Inventory")); ?></td>
    <td><?php print (_t("Relation to")); ?></td>
    <td><?php print (_t("Forecast")); ?></td>
    <td><?php print (_t("Unit")); ?></td>
    </thead>
    <tbody>
<?php

    $sql2 = "SELECT * FROM ims_optimization GROUP BY catalog_id;";
    $ims2 = $db->Execute($sql2);
    while (!$ims2 == NULL && !$ims2->EOF) {
        $catalog_id = $ims2->fields['catalog_id'];
        $sql3 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims3 = $db->Execute($sql3);
        $actual_value = $ims3->fields['actual_value'];
        $forecasted_value = $ims3->fields['forecasted_value'];
        $unit = $ims3->fields['unit'];
        $week = $ims3->fields['week'];
        if ($algorithm == "single") {
            $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
            $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
        }
        if ($algorithm == "double") {
            _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
            $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
        }
    $q1 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $i1 = $db->Execute($q1);
    $item_name = $i1->fields['item_name'];
    
    $q2 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $i2 = $db->Execute($q2);
    $inventory_name = $i2->fields['inventory_name'];
    
    $unit_name1 = get_unit_name($unit);
    
?>
<tr>
<td><?php print $item_name; ?></td>
<td><?php print $inventory_name; ?></td>
<td><?php print $item_name_relation_to; ?></td>
<td><?php print $forecast; ?></td>
<td><?php print $unit_name1; ?></td>
</tr>
<?php
    $ims2->MoveNext();
    }
?>
</tbody>
</table>
</div>
<?php
//}
//Chart Generation
    $sql9 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims9 = $db->Execute($sql9);
    $j = 0;
    while (!$ims9 == NULL && !$ims9->EOF) {
        $j = $j + 1;
        $ims9->MoveNext();
    }
//Prediction by inventory Pie chart Creation
    $temp = array();
    $catalog_array = array();
    $data = array();

    $data_array = array();
    $temp_array = array();
    $temp_array1 = array();
    $forecast = 0;
    //$temp[0]="a";
    $i = 1;
    $actual_value_max = 0;
    $sql6 = "SELECT * FROM ims_optimization GROUP BY catalog_id";
    $ims6 = $db->Execute($sql6);
    while (!$ims6 == NULL && !$ims6->EOF) {
        $catalog_id = $ims6->fields['catalog_id'];
        $temp[0] = $catalog_id;
        $temp_array[0] = "next Period";
        $temp_array1[0] = "Present Period";
        $sql8 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
        $ims8 = $db->Execute($sql8);
        $catalog_array[$i] = $ims8->fields['item_name'];
        $sql7 = "SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
        $ims7 = $db->Execute($sql7);
        $xcoardination = 0;
        //while(!$ims3==NULL && !$ims3->EOF)
        //{
        $actual_value = $ims7->fields['actual_value'];
        $forecasted_value = $ims7->fields['forecasted_value'];
        $week = $ims7->fields['week'];
        $unit = $ims7->fields['unit'];
        $unit_name = get_unit_name($unit);

//Finding the maximum actual value

    if ($actual_value > $actual_value_max) {
        $actual_value_max = $actual_value;
    } else {
        ;
    }
//end of finding the maximum actual value
//$temp = array($forecast);
    if ($algorithm == "single") {
        $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
        $forecast = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
    }
    if ($algorithm == "double") {
        _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period);
        $forecast = _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week);
    }
    array_push($temp_array,0,$forecast);
    array_push($temp_array1,$actual_value,$forecasted_value);
    //array_push($temp,$forecast);
    for ($a = 1; $a < $j + 1; $a++) {
        if ($a == $i) {
            $temp[$a] = $forecast;
        } else {
            $temp[$a] = 0;
        }
     }
    $i = $i + 1;
    //$data=array($temp);
    array_push($data,$temp);
    //$data[0][$i]=$temp;
    $xcoardination = $xcoardination + 1;
    $ims6->MoveNext();
    }
    //}
    array_push($data_array,$temp_array1);
    array_push($data_array,$temp_array);
    
    _shn_ims_pie_chart($data,$catalog_array);
    print "<br>";
    $i = $xcoardination + 1;
    _shn_ims_bar_chart_inventory($data_array,$catalog_array,$i,$actual_value_max);

?>
    <image src="tmp/pieChart.png"></image>
<?php
    print "<br>";
?>
    <image src="tmp/barChart.png"></image>
<?php
 
   }
    if ($action == "reorderlevel") {
?>
    <h1 align="center"><?php print(_t("Re-Order Level")); ?></h1> 
<?php
//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************
    
    global $global;
    $db = $global["db"];
    $sql5 = "SELECT * FROM ims_optimization ORDER BY week DESC;";
    $ims5 = $db->Execute($sql5);
    $actual_value = $ims5->fields['actual_value'];
    $forecasted_value = $ims5->fields['forecasted_value'];
    $unit = $ims5->fields['unit'];
    $alpha = _shn_ims_smoothing_constant($catalog_id,$inv_id);
    $forecasted_value = _shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
    $sql1 = "SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims1 = $db->Execute($sql1);
    
    $minimum_quantity = $ims1->fields['minimum_quantity'];
    $minimum_unit = $ims1->fields['unit'];
    $base_unit = convert_to_base_unit($minimum_unit);
    $converted_minimum_quantity = $minimum_quantity * unit_converter($base_unit,$minimum_unit);
    $unit_name = get_unit_name($base_unit);
    $q1 = "SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $i1 = $db->Execute($q1);
    $item_name = $i1->fields['item_name'];
    $q2 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $i2 = $db->Execute($q2);
    $inventory_name = $i2->fields['inventory_name'];
    shn_form_fopen(null);
    shn_form_fsopen("Re-Order Level");
    if ($forecasted_value < $converted_minimum_quantity) {
        shn_form_label(_t("Item_name :"),$item_name,null);
        shn_form_label(_t("Inventory :"),$inventory_name,null);
        shn_form_label(_t("Forecasted Value :"),$forecasted_value,null);
        shn_form_label(_t("Unit :"),$unit_name,null);
        
    } else {
?>
    <div><h3><b><?php print _t("Re-order level will not be exceeded in given time period"); ?></b></h3></div>
<?php

    }

    shn_form_fsclose();
    shn_form_fclose();

//Line Chart Generation
    if ($converted_minimum_quantity != 0 || $converted_minimum_quantity != NULL) {
        $array1 = array();
        $data_array_line = array();
        $forecasted_value_max = 0;
        $sql2 = "SELECT * FROM ims_optimization;";
        $ims2 = $db->Execute($sql2);
    while (!$ims2 == NULL && !$ims2->EOF) {
        if ($algorithm == "single") {
            $forecasted_value = $ims2->fields['forecasted_value'];
        }
        if ($algorithm == "double") {
            $forecasted_value = $ims2->fields['forecasted_value'];
        }
        $week = $ims2->fields['week'];
        $array1[0] = "week";
        $array1[1] = $converted_minimum_quantity;
        $array1[2] = $forecasted_value;

//Finding maximum forecasted value

    if ($forecasted_value > $forecasted_value_max) {
        $forecasted_value_max = $forecasted_value;
    } else {
        ;
    }
//end of finding maximum forecasted value

    array_push($data_array_line,$array1);
    $ims2->MoveNext();
    }
    
    $x = $week + 2;
    $ycoardinate = 0;
    if ($forecasted_value_max < $converted_minimum_quantity) {
        $ycoardinate = $converted_minimum_quantity;
    } else {
        $ycoardinate = $forecasted_value_max;
    }
    _shn_ims_line_chart($data_array_line,$x,$ycoardinate);
?>
    <br>
    <br>
    <image src="tmp/lineChart.png">
    </image>
<?php

    }


}

}

function _shn_ims_optim_item_db()
{
    global $global;
    $db = $global["db"];

    $catalog_id = $_POST['parent_id'];
    $inv_id = $_POST['inv_id'];

    $sql1 = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $ims1 = $db->Execute($sql1);
    $date_inv = $ims1->fields['added_date'];

    $current_date = date("Y-m-d");
    $date_diff = _shn_ims_count_days($date_inv,$current_date);

    _shn_ims_insert_data_to_predict($catalog_id,$inv_id);
    _shn_ims_chart_test();

?>
<image src="tmp/Barchart.png"></image>
<?php

}

?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_item.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_inventory(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_inventory.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_relation(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_item_actions.submit();
         return;
    }
</script>
<?php

?>
