<?php
/**
* Sahana Inventory Management System Add item page
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

/**include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";*/
include_once ('view_edit_item.inc');
include_once $global['approot'] . '/mod/cs/lib_cs.inc';
include_once $global['approot'] . '/mod/or/lib_or.inc';

//$category=$_POST['itemcat'];


/**
*form for Add blankets to the inventory

function add_item_without_expire_date($category)
{
?>
*/

function _shn_ims_add_item_header()
{

    ?>


    <h1 align="center"><?php print _t("Add Item"); ?> </h1>
    



<?php

}

/**
**First page for Add item Page
**/

function _shn_ims_add_item_main_page($inventory_id) 
{    
    global $global;
    $db = $global['db'];

     //$tables = array('ims_item_records' => 'c' , 'ims_inventory_records' => 'c' , 'ct_catalogue' => 'r');
 
   
?>

    <h1 align="center"><?php print _t("Add items to the Inventory"); ?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("add_item",null,$form_opts);
    $depth = get_max_depth();
    shn_sub_cat($depth,'subcat',$inventory_id);
    shn_form_fclose();
    
}




/**
*Form for Add medical drugs to the inventory
*/

function add_item($temp,$parent_id) 
{
    $form_opts['name'] = 'additemform';
    $inv_id = $_POST['inventory_id'];
    
    $parent_id1 = $parent_id;
    
    if ($temp != null || $parent_id != null) {
        
        global $global;
        $db = $global["db"];
        $sql = "SELECT item_name,inv_id,suplier_id,amount,unit,manufactured_date,expire_date,cost_per_unit FROM ims_item_records WHERE item_id ='$temp' ;";
        $ims = $db->Execute($sql);
        $item_name = $ims->fields["item_name"];
        $inv_id = $ims->fields['inv_id'];
        $suplier_id = $ims->fields['suplier_id'];
        $amount = $ims->fields["amount"];
        $unit = $ims->fields['unit'];
        $manufactured_date = $ims->fields["manufactured_date"];
        $expire_date = $ims->fields["expire_date"];
        $cost_per_unit = $ims->fields['cost_per_unit'];
        
    } else {
        $depth = get_max_depth();
        $parent_id = trim($_POST['0']);
    
        for ($i = 1; $i < $depth; $i++) {
            $parent_id = trim($_POST[$i]);
    
            if ($parent_id == null) {
                $parent_id = trim($_POST[$i - 1]);
                break;
            }
        }
  
        global $global;
        $db = $global["db"];
        $sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$parent_id';";
        $ims = $db->Execute($sql);
        $item_name = $ims->fields["name"];
        $amount = "";
        $manufactured_date = "";
        $cost_per_unit = "";
        $expire_date = "";
        $suplier_id = "";
        
    }


    
    shn_form_fsopen(_t('Primary Details'));
    shn_form_text(_t("* Item : "),'item_name','size="50" readonly=true',array('value'=>$item_name,'req'=>true));
    shn_form_text(_t("*  Amount : "),'amount','size="50"',array('value'=>$amount,'req'=>true));

    
    global $global;
    $db = $global["db"];
    
    $cq = "SELECT name FROM ct_unit WHERE unit_uuid='$unit';";
    $cms = $db->Execute($cq);
    
    $unit_select_array[$unit] = $cms->fields['name'];
    
    $query = "SELECT * FROM ct_cat_unit WHERE ct_uuid='$parent_id'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
    $temp2 = $res->fields['unit_uuid'];
    $query1 = "SELECT name FROM ct_unit WHERE unit_uuid ='$temp2'";
    $res2 = $db->Execute($query1);
    
    $unit_select_array[$res->fields['unit_uuid']] = $res2->fields['name'];
    $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_t("Unit : "),'unit_select','size="1"',array('req'=>true));

    
    shn_form_text(_t("Cost per Unit : "),'cost_per_unit','size="50"',array('value'=>$cost_per_unit,'help'=>_t('Cost of a unit which you are going to select below ')));
    
    global $global;
    $db = $global["db"];
    $inventory_array = array();
    $q0 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
    $ims0 = $db->Execute($q0);
    $inventory_array[$inv_id] = $ims0->fields['inventory_name'];
    $q = "SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
    $ims = $db->Execute($q);
    
    while ($ims != NULL && !$ims->EOF) {
        
        $inventory_array[$ims->fields['inv_uuid']] = $ims->fields['inventory_name'];
        $ims->MoveNext();
        
    }

    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_t('If this box does not contain preferred inventory name  please go through the List Inventories Menu and add an Inventory first')));

    shn_form_fsclose();

    shn_form_fsopen(_t('Secondary details'));
    //$extra_opts['value'] = $manufactured_date;
    shn_form_date(_t("Manufactured Date : "),'manufactured_date',array('value'=>$manufactured_date,'help'=>_t('Date Should be entered as year-month-date. Only - separator is accepted')));
   
    shn_form_date(_t("Expire Date :"),'expire_date',array('value'=>$expire_date,'help'=>_t('Date Should be entered as year-month-date. Only - separator is accepted')));
    
        
    shn_form_fsclose();

    

    shn_form_fsopen('Supply details');
//----------------------------------------------------------------------------------------------------------------
    
    $suplier_name_array = array();
    $suplier_name_array = _shn_or_get_suplier_name($suplier_id);
   
    shn_form_select($suplier_name_array,_t("Supplier Organization : "),'suplier_id','size="1"',array('help'=>_t('If this box does not contain the organization name please go to the Organization Registry module and get your organization Registered ')));
//----------------------------------------------------------------------------------------------------------------
    

    shn_form_fsclose();

    

   
    shn_form_hidden(array('parent_id'=>$parent_id));
    if ($temp == NULL) {
       
        shn_form_hidden(array('parent_id'=>$parent_id));
        shn_form_submit(_t("Submit"));
    } else {
       
        shn_form_hidden(array('temp' => $temp));
        shn_form_hidden(array('parent_id' => $parent_id));
        shn_form_submit(_t("Save"));
     
    }

    }

?>


    


