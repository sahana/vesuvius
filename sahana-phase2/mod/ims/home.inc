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
include_once $global['approot'].'/mod/cs/lib_cs.inc';
//function shn_ims_home(){
function _shn_ims_default() {
?>
<h1 align="center"><?= _("Inventory Management System Home")?> </h1>
<div id="home">
    <div>
    <p><?= (_("The Inventory Management system is a system to manage Inventories. It not only keep the track of items available in warehouses but also all of the inventories which are related to relief works in disaster region.")) ?></p></div>
    <br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
      
    <ul>
        <li><b><?= (_("Find Items:"))?></b><?= (_(" Enables end user to search items available in ware houses. End-User is also allowed to search available items, expired items and already destroyed items. "))?></li>
        <li><b><?= (_("List Inventories:"))?></b><?= (_(" Facilitates to manage multiple Inventories and enables end-user to add,edit or delete Inventories."))?></li>
        <li><b><?= (_("List Items:"))?></b><?= (_(" Enables end-user to add,edit or delete item for inventories and also enables to transfer items between two inventories"))?></li>
        <li><b><?= (_("Re-Order Level:"))?></b><?= (_(" Enables end-user to add,edit or delete defined Re-Order Level for an inventory for  perticular items "))?></li>
        <li><b><?= (_("Reports:"))?></b><?= (_(" Generate reports about expired items, destroyed items and also generates report about the items in which the total amount is lower than the Re-Order Level ")) ?></li>
        
        
    </ul>
    
</div>
<h2 align="center"><?php print _("Recently added items ")?></h2>
<div id="result">

<?php
    //shn_form_fopen(null);
    shn_form_fsopen();
?>    
    <table>
    <thead>
        <td><?=_("Item")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit")?></td>
        <td><?=_("Manufactured Date")?></td>
        <td><?=_("Expire Date")?></td>
        <td><?=_("Inventory")?></td>
            <td><?=_("Suplier")?></td>
            
            
    </thead>
    <tbody>
    <?php
        

        global $global;
        $db=$global["db"];
        $state_des="destroyed";
        //$item_search=$_POST['item_name_search'];
        //print ($item_search);
        
        $sql = "select item_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date from ims_item_records WHERE state!='$state_des' order by item_id desc ;";
        $ims = $db->Execute($sql);

        $i=0;

        while (!$ims==NULL && !$ims->EOF && $i<10)
        {
            $i++;
            $item_id=$ims->fields["item_id"];
            $inv_id=$ims->fields["inv_id"];
            $suplier_id=$ims->fields['suplier_id'];
            $suplier_name_array=array();
            $suplier_name_array=_shn_or_get_suplier_name($suplier_id);
            $suplier_name=$suplier_name_array[$suplier_id];
            $item_name=$ims->fields["item_name"];
            $amount=$ims->fields["amount"];
            $unit=$ims->fields["unit"];
            $manufactured_date=$ims->fields["manufactured_date"];
            $expire_date=$ims->fields["expire_date"];
            //$suplier_name=$ims->fields["suplier_name"];
            //$suplier_address=$ims->fields["suplier_address"];
            //$suplier_telephone=$ims->fields["suplier_telephone"];
            //$suplier_email=$ims->fields["suplier_email"];

        $sql1="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims1 = $db->Execute($sql1);

            $inventory_name=$ims1->fields["inventory_name"];
        $unit_name=get_unit_name($unit);            

?>
        <tr>
        <td><?php print ($item_name); ?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date);?></td>
        <td><?php print ($inventory_name);?></td>
        <td><?php print ($suplier_name);?></td>
        
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
}
?>






