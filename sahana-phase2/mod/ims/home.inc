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
* @author        Mahesh Kaluarachchi. <mahesh@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage    
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
include_once $global['approot'] . '/mod/cs/lib_cs.inc';
//function shn_ims_home(){
function _shn_ims_default() 
{

?>
<h1 align="center"><?= _t("Inventory Management System Home")?> </h1>
<?php

?>
<div id="home">
    <p><?= (_t("The Sahana Inventory Management System is a database to keep track of all aid items and supplies kept in your organization's inventories. It not only keeps track of the location and quantities of items available, but it also tracks expiry dates, re-order levels and items in transit. The system is designed to be simple to a diverse groups of users to interact and manage stocks in inventories located around the region")) ?></p>
    <br/>
    <strong><?= (_t("Features Include:")) ?></strong>
      
    <ul>
        <li><b><a href="index.php?mod=ims&act=search_item"><?= (_t("Find Items:"))?> </a></b><br><?= (_t(" Enables end user to search items available in ware houses. End-User is also allowed to search available items, expired items and already destroyed items. "))?></li>
        <li><b><a href="index.php?mod=ims&act=view_inv"><?= (_t("List Inventories:"))?></a></b><br><?= (_t(" Facilitates to manage multiple Inventories and enables end-user to add,edit or delete Inventories."))?></li>
        <li><b><a href="index.php?mod=ims&act=view_edit_item"><?= (_t("List Items:"))?></a></b><br><?= (_t(" Enables end-user to add,edit or delete item for inventories and also enables to transfer items between two inventories"))?></li>
        <li><b><a href="index.php?mod=ims&act=view_edit_reorder_page"><?= (_t("Re-Order Level:"))?></a></b><br><?= (_t(" Enables end-user to add or modify Re-Order Level for an inventory for  particular items "))?></li>
        <li><b><a href="index.php?mod=ims&act=report_expired"><?= (_t("Reports:"))?></a></b><br><?= (_t(" Generate reports about expired items, destroyed items and also generates report about the items in which the total amount is lower than the Re-Order Level ")) ?></li>
        <li><b><a href="index.php?mod=ims&act=optim_inventory"><?= (_t("Optimization:"))?></a></b><br><?= (_t(" Forecasts the amount of items which have been sent to another inventory, received from another inventory and also forecasts already available item amounts in a particular inventory. On the other hand under this section, the end user is allowed to set relationships among items and track items which can be used as alternatives for particular items")) ?></li>
        
    </ul>
    
</div>
<h2 align="center"><?php print _t("Recently added items ")?></h2>
<div id="result"> 

<?php
    //shn_form_fopen(null);
    shn_form_fsopen();

?>    
    <table>
    <thead>
        <td><?=_t("Item")?></td>
        <td><?=_t("Amount")?></td>
        <td><?=_t("Unit")?></td>
        <td><?=_t("Manufactured Date")?></td>
        <td><?=_t("Expire Date")?></td>
        <td><?=_t("Inventory")?></td>
            <td><?=_t("Supplier")?></td>
            
            
    </thead>
    <tbody>
    <?php
        

        global $global;
        $db = $global["db"];
        $state_des = "destroyed";
        
        $sql = "SELECT item_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state!='$state_des' AND amount!=0 ORDER BY item_id DESC ;";
        $ims = $db->Execute($sql);

        $i = 0;

        while (!$ims == NULL && !$ims->EOF && $i < 10) {
            $i++;
            $item_id = $ims->fields["item_id"];
            $inv_id = $ims->fields["inv_id"];
            $suplier_id = $ims->fields['suplier_id'];
            $suplier_name_array = array();
            $suplier_name_array = _shn_or_get_suplier_name($suplier_id);
            $suplier_name = $suplier_name_array[$suplier_id];
            $item_name = $ims->fields["item_name"];
            $amount = $ims->fields["amount"];
            $unit = $ims->fields["unit"];
            $manufactured_date = $ims->fields["manufactured_date"];
            $expire_date = $ims->fields["expire_date"];
            //$suplier_name=$ims->fields["suplier_name"];
            //$suplier_address=$ims->fields["suplier_address"];
            //$suplier_telephone=$ims->fields["suplier_telephone"];
            //$suplier_email=$ims->fields["suplier_email"];

        $sql1 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims1 = $db->Execute($sql1);

        $inventory_name = $ims1->fields["inventory_name"];
        $unit_name = get_unit_name($unit);

?>
        <tr>
        <td><?php print ($item_name); ?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date); ?></td>
        <td><?php print ($inventory_name); ?></td>
        <td><?php print ($suplier_name); ?></td>
        
        </tr>

<?php

            $ims->MoveNext();
        }


    ?>
    
    </tbody>
    </table>
</div>

<?php
    shn_form_fsclose();
    //shn_form_fclose();
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('rss_expired_list',_t('Expired item List'));
    shn_rss_add_feed('rss_reorder_list',_t('Items bellow Re-order Level'),_t('This RSS feed gives a list of items that are bellow re-order level.'));
    shn_rss_add_feed('rss_transit',_t('Transit Item List'),_t('This RSS feed gives a list of items which have been transfered to other locations or inventories.'));
}
?>






