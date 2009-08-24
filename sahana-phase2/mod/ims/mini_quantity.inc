<?php
/**
* Sahana Inventory Management System Re-Order level  page
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
include_once 'errors.inc';

function _shn_ims_mini_quantity_item_select()
{
    global $global;
    //global $conf;
    $db = $global['db'];

     $tables = array('ims_item_records'=>'c', 'ims_inventory_records'=>'c', 'ct_catalogue'=>'r', 'ims_reorder_level'=>'c');
 /*$tables= array(
'field_options'=>'4',
'org_main'=>'8'
);*/
   /*
    * Commented this to fix bug id : [ 1914083 ] ims-->add re-order level
    if (shn_acl_check_table_only_perms($tables) == DENIED) {
        return false;
   }*/
?>

    <h1 align="center"><?php print _t("Item Selection for Re-Order Level"); ?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("minimum_quantity",null,$form_opts);
    $depth = get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    //shn_sub_cat(6,'subcat');
    shn_form_fclose();
    
}

function _shn_ims_mini_quantity($catalog_id, $inv_id)
{

?>
    <h1 align="center"><?php print _t("Re-Order Level"); ?> </h1>
    
<?php
    if ($catalog_id != null && $inv_id != null) {
        global $global;
        $db = $global["db"];
        $query = "SELECT minimum_quantity,unit FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
        $ims = $db->Execute($query);
        
        $minimum_quantity = $ims->fields['minimum_quantity'];
        $unit = $ims->fields['unit'];
        $unit_name = get_unit_name($unit);

        $query1 = "SELECT item_name FROM ims_item_records WHERE catalog_id='$catalog_id';";
        $ims_q1 = $db->Execute($query1);
        $item_name = $ims_q1->fields['item_name'];

        $parent_id = $catalog_id;
        $flag = true;
        //$next_action="";
    
    } else {
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
        $minimum_quantity = "";
        $unit = "";
        $flag = false;
    //$parent_id=$catalog_id;
        //$next_action="mini_quantity_db";

    }
    

    shn_form_fopen("mini_quantity_db");

    shn_form_fsopen(_t("Item Name"));
    shn_form_text(_t("Item Name : "),'item_name','size="50" readonly=true',array('value'=>$item_name));
    shn_form_fsclose();

    shn_form_fsopen("Inventory Selection");
    
    global $global;
    $db = $global["db"];
    $inventory_array = array();
    if ($flag == true) {
        //$inv_id_edit=$inv_id;
        $q1 = "SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $imsq1 = $db->Execute($q1);
        //$inventory_array=array();
        $inventory_array[$imsq1->fields['inv_uuid']] = $imsq1->fields['inventory_name'];
        shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',null);

    }

   if ($flag == false) {
    

        $sql2 = "SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
        $ims2 = $db->Execute($sql2);

        while ($ims2 != NULL && !$ims2->EOF) {
        $inventory_array[$ims2->fields['inv_uuid']] = $ims2->fields['inventory_name']; //}
        $ims2->MoveNext();
        }
        
    //}    
    
    shn_form_select($inventory_array,_t("Inventory : "),'inv_id','size="1"',array('req'=>true));
    $catalog_id = $parent_id;
    }

    shn_form_fsclose();

    shn_form_fsopen(_t("Item Quantity "));
    shn_form_text(_t("Re-Order Level : "),'mini_quantity','size="50"',array('req'=>true,'value'=>$minimum_quantity));
    
//-----------------------------------------------------------------------------------------------------------------------------------------------------


    $unit_array = array();
    
    $cq = "SELECT name FROM ct_unit WHERE unit_uuid='$unit';";
    $cms = $db->Execute($cq);
    $unit_array[$unit] = $cms->fields['name'];
    
    $query = "SELECT * FROM ct_cat_unit WHERE ct_uuid='$parent_id'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {

    $temp2 = $res->fields['unit_uuid'];
    $query1 = "SELECT name FROM ct_unit WHERE unit_uuid ='$temp2'";
    $res2 = $db->Execute($query1);
    
    $unit_array[$res->fields['unit_uuid']] = $res2->fields['name'];
    $res->MoveNext();
    }    

    shn_form_select($unit_array,_t("Unit : "),'unit_select','size="1"',array('req'=>true,'help'=>_t('Select the Measurement unit for entered amount. If this box does not contain your prefered unit go back to the catalogue system and add a measurement unit')));

    //$unit_array=_shn_cs_get_units($parent_id);
    //shn_form_select($unit_array,_t("Unit : "),'unit_select','size="1"',array('help'=>_t('Select the Measurement unit for entered amount. If this box does not contain your prefered unit go back to the catalogue system and add a measurement unit')));
    shn_form_fsclose();
    //shn_form_hidden(array('item_id'=>$item_id));
    
    shn_form_hidden(array('catalog_id'=>$catalog_id));
    shn_form_hidden(array('flag'=>$flag));
    shn_form_hidden(array('parent_id'=>$parent_id));
    //shn_form_hidden(array('inv_id'=>$inv_id));
    shn_form_submit(_t("Submit"));
    
    shn_form_fclose();
}

function _shn_ims_mini_quantity_db()
{
    global $global;
    $db = $global["db"];

    //$item_id=$_POST['item_id'];
    $flag = trim($_POST['flag']);
    $catalog_id = trim($_POST['catalog_id']);
    $inv_id = trim($_POST['inv_id']);
    $mini_quantity = trim($_POST['mini_quantity']);
    $unit = trim($_POST['unit_select']);

    $q = "SELECT * FROM ims_reorder_level;";
    $ims = $db->Execute($q);
    if ($ims == NULL) {
        //$error=true;
        add_error(SHN_ERR_IMS_REORDER_TABLE_EXISTS);
        //return false;

    } else {

        if ($flag == false) {

        $sql = "INSERT INTO ims_reorder_level (catalog_id,inv_id,minimum_quantity,unit) VALUES ('$catalog_id','$inv_id','$mini_quantity','$unit');";
        $ims = $db->Execute($sql);
        add_confirmation('Re-Order level was succesfully added');
        shn_ims_minimum_quantity_item();
    }
    if ($flag == true) {
        $sql = "UPDATE ims_reorder_level SET minimum_quantity='{$mini_quantity}',unit='{$unit}' WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
        $ims = $db->Execute($sql);

    add_confirmation('Re-Order level was succesfully added');
   
    $flag = "";
    $catalog_id = "";
    $inv_id = "";
    $mini_quantity = "";
    $unit = "";

    $inventory_id = "";
        shn_ims_reorder_level_edit();
    }
    }


        
    //shn_ims_minimum_quantity_item();


    
}

function _shn_ims_view_edit_reorder()
{
?>

    <h1 align="center"><?php print _t("Item Selection for Re-Order Level"); ?><br></h1>
    <dev id="result">

    </dev>

<?php
    $form_opts['name'] = 'subcat';
    shn_form_fopen("view_edit_reorder_page",null,$form_opts);
    shn_sub_cat(6,'subcat');
    shn_form_fclose();
    

}

function _shn_ims_view_edit_reorder_page($page_number,$Limit = null)
{
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for ($i = 1; $i < 5; $i++) {
    $parent_id = trim($_POST[$i]);
    
        if ($parent_id == null) {
            $parent_id = $_POST[$i - 1];
            break;
        }
    }
?>
<h1 align="center"><?php print _t("Re-Order Level"); ?><br></h1>
<div id="result1">
<?php
    global $global;
    $db = $global["db"];
    $form_opts['name'] = 'reorder_form';
    shn_form_fopen("minimum_quantity_action",null,$form_opts);
    shn_form_fsopen(_t("Add Re-Order Level"));
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    shn_form_button(_t("Add Re-Order Level"),"onClick='change_action(\"reorder\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    //shn_form_submit(_t("Add Re-Order level"));
    shn_form_fsclose();
    //shn_form_fsopen();

    //$Limit=20;
    print '<b>';
    shn_form_text(_t("Records per Page"),'records','onChange="submit(this);"',array('value'=>$Limit));

    if ($page_number != 0) {
        $page_number = ($page_number - 1) * $Limit;
    } else {
        $page_number = 0;
        }
    
    $sql1 = "SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level LIMIT $page_number,$Limit;";  
    $ims1 = $db->Execute($sql1);

    $sql = "SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level;";

    $SearchResult = mysql_query($sql) or die(mysql_error()); 
    $NumberOfResults = mysql_num_rows($SearchResult); 
   
    $NumberOfPages = ceil($NumberOfResults / $Limit); 
    
    
    print(_t("Go to Page : "));

    for ($i = 1; $i < $NumberOfPages + 1; $i++) {
        
        ?><a href="index.php?mod=ims&act=reorder_level_paging&$i=<?php echo $i; ?>&$Limit=<?php echo $Limit; ?>"><?php print ($i . " "); ?></a><?php
        print "\n";
    }
    print '</b>';
?>
    </div>
    <div id="result">
    <table>
        <thead>
        <td><?=_t("Item"); ?></td>
        <td><?=_t("Amount"); ?></td>
        <td><?=_t("Unit"); ?></td>
        <td><?=_t("Inventory"); ?></td>
        <td><?=_t("Edit"); ?></td>
        <td><?=_t("Delete"); ?></td>
            
            
        </thead>
    <tbody>
<?php
        
       while (!$ims1 == NULL && !$ims1->EOF) {
            $catalog_id = $ims1->fields["catalog_id"];
            $inv_id = $ims1->fields["inv_id"];
            $minimum_quantity = $ims1->fields['minimum_quantity'];
            $unit = $ims1->fields["unit"];
            $unit_name = get_unit_name($unit);
            
        $sql2 = "SELECT item_id,item_name FROM ims_item_records WHERE catalog_id='$catalog_id' ORDER BY(item_name);";    
        $ims2 = $db->Execute($sql2);
        $item_id = $ims2->fields['item_id'];
        $item_name = $ims2->fields['item_name'];
        if ($item_name != null) {

            $sql3 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
            $ims3 = $db->Execute($sql3);
            $inventory_name = $ims3->fields["inventory_name"];
        
    
            
?>
        <tr>
        <td><?php print ($item_name); ?></td>
        <td><?php print ($minimum_quantity); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($inventory_name); ?></td>
        <td><a href="index.php?mod=ims&act=reorder_level_edit&inv_id=<?php echo $inv_id; ?>&catalog_id=<?php echo $catalog_id; ?>"><?php print ("Edit"); ?></a></td>
        <td><a href="index.php?mod=ims&act=reorder_level_delete_confirm&inv_id=<?php echo $inv_id; ?>&catalog_id=<?php echo $catalog_id; ?>"><?php print ("Delete"); ?></a></td>
        
        
        
        </tr>

    
<?php

    }
    $ims1->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>
<?php
    //shn_form_fsclose();
    shn_form_fclose();
    
}

function _shn_ims_validate_minimum_quantity()
{
    //$flag=trim($_POST['flag']);
    $error_flag = false;
    clean_errors();
    $minimum_quantity = trim($_POST['mini_quantity']);
   // $inventory_id=trim($_POST['inventory_id']);
  //  print $inventory_id;

    if (trim($_POST['item_name']) == null) {
        add_error(SHN_ERR_IMS_ITEM_NAME_INCOMPLETE);
        $error_flag = true;
    }
    //if(trim($_POST['inventory_id'])==null)
    //{
//add_error(SHN_ERR_IMS_INVENTORY_INCOMPLETE);
   //     $error_flag=true;
   // }
    if (trim($_POST['inv_id']) == null) {
        add_error(SHN_ERR_IMS_INVENTORY_INCOMPLETE);
        $error_flag = true;
    }
    if ($minimum_quantity == null) {
        add_error(SHN_ERR_IMS_REORDER_VALUE_NUMERIC);
        $error_flag = true;
    }
    if ($minimum_quantity < 0) {
        add_error(SHN_ERR_IMS_AMOUNT_NEGATIVE);
        $error_flag = true;
    }
    if (!is_numeric($minimum_quantity)) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        $error_flag = true;
    }
    if (trim($_POST['unit_select']) == null) {
        add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
        $error_flag = true;
    }

    return $error_flag;
}

function _shn_ims_minimum_quantity_action()
{
    global $global;
    $db = $global["db"];

    $action = trim($_POST['action']);
    $Limit = trim($_POST['records']);
    

    if ($action == 'reorder') {
        shn_ims_minimum_quantity_item();
    }
    if ($action == '0') {
        

    if (!is_numeric($Limit)) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        shn_ims_reorder_level_paging($Limit = 20);
    } else if ($Limit == '0' || $Limit < 0) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        shn_ims_reorder_level_paging($Limit = 20);
    } else {
        shn_ims_reorder_level_paging($Limit);
    }

    }
}

?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.reorder_form.submit();
         return;
    }
</script>
<?php

?>