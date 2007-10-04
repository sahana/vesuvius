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
<h1 align="center"><?= _("Inventory Management System Home")?> </h1>
<?php

?>
<div id="home">
    <p><?= (_("The Sahana Inventory Management System is a database to keep track of all aid items and supplies kept in your organization's inventories. It not only keeps track of the location and quantaties of items available, but it also tracks expiry dates, re-order levels and items in transit. The system is designed to be simple to a diverse groups of users to interact and manage stocks in inventories located around the region")) ?></p>
    <br/>
    <strong><?= (_("Features Include:")) ?></strong>
      
    <ul>
        <li><b><a href="index.php?mod=ims&act=search_item"><?= (_("Find Items:"))?> </a></b><br><?= (_(" Enables end user to search items available in ware houses. End-User is also allowed to search available items, expired items and already destroyed items. "))?></li>
        <li><b><a href="index.php?mod=ims&act=view_inv"><?= (_("List Inventories:"))?></a></b><br><?= (_(" Facilitates to manage multiple Inventories and enables end-user to add,edit or delete Inventories."))?></li>
        <li><b><a href="index.php?mod=ims&act=view_edit_item"><?= (_("List Items:"))?></a></b><br><?= (_(" Enables end-user to add,edit or delete item for inventories and also enables to transfer items between two inventories"))?></li>
        <li><b><a href="index.php?mod=ims&act=view_edit_reorder_page"><?= (_("Re-Order Level:"))?></a></b><br><?= (_(" Enables end-user to add,edit or delete defined Re-Order Level for an inventory for  particular items "))?></li>
        <li><b><a href="index.php?mod=ims&act=report_expired"><?= (_("Reports:"))?></a></b><br><?= (_(" Generate reports about expired items, destroyed items and also generates report about the items in which the total amount is lower than the Re-Order Level ")) ?></li>
        <li><b><a href="index.php?mod=ims&act=optim_inventory"><?= (_("Optimization:"))?></a></b><br><?= (_(" Forecasts the amount of items which have been sent to another inventory, received from another inventory and also forecasts already available item amounts in a particular inventory. On the other hand under this section, the end user is allowed to set relationships among items and track items which can be used as alternatives for particular items")) ?></li>
        
    </ul>
    
</div>
<h2 align="center"><?php print _("Recently added items ")?></h2>
<div id="result"> 

<?php
    //shn_form_fopen(null);
    shn_form_fsopen();
/*$name1="Mahesh";
$name2="Kalu";

$name=$name1."-".$name2;
print $name;*/
//print dateDiff1("-","01-10-2006","01-01-2006");
//print dateDiff("01-10-2006","01-01-2006");
?>    
    <table>
    <thead>
        <td><?=_("Item")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit")?></td>
        <td><?=_("Manufactured Date")?></td>
        <td><?=_("Expire Date")?></td>
        <td><?=_("Inventory")?></td>
            <td><?=_("Supplier")?></td>
            
            
    </thead>
    <tbody>
    <?php
        

        global $global;
        $db = $global["db"];
        $state_des = "destroyed";
        //$item_search=$_POST['item_name_search'];
        //print ($item_search);
        
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
    shn_rss_add_feed('rss_expired_list',_('Expired item List'));
    shn_rss_add_feed('rss_reorder_list',_('Items bellow Re-order Level'),'This RSS feed gives a list of items that are bellow re-order level.');
    shn_rss_add_feed('rss_transit',_('Transit Item List'),'This RSS feed gives a list of items which have been transferd to other locations or inventories.');
}
?>






