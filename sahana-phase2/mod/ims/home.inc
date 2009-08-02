<?php
/**
* Sahana Inventory Management System main page
*
* PHP version 5
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
<h1><center><?php echo  _t("Inventory Management System Home")?></center></h1>

<div id="home">
    <p>
      <?php echo  (_t("The Sahana Inventory Management System is a database to keep track of all aid items and supplies kept in your Organization's inventories. It not only keeps track of the location and quantities of items available, but it also tracks expiry dates, re-order levels and items in transit. The system is designed to be simple to a diverse groups of users to interact and manage stocks in inventories located around the region.")) ?>
    </p>
    
    <h2><?php echo  (_t("Features Include:")) ?></h2>    
      
    <ul>
        <li>
          <b><a href="index.php?mod=ims&act=search_item">
            <?php echo  (_t("Find Items").':')?>
          </a></b><br />
		<?php echo  (_t('Search for items available in warehouses.').' '.
		_t('Users may also search for items listed as available, expired and items that have been recorded as destroyed.'))?>
		</li>
		
        <li>
          <b><a href="index.php?mod=ims&act=view_inv">
            <?php echo  (_t("Manage Inventories").':')?>
          </a></b><br />
          <?php echo  (_t("List storage facilities through this function.").' '.
           _t('You are able to add, edit or delete storage facilities.'))?>
        </li>
        
        <li>
          <b><a href="index.php?mod=ims&act=view_edit_item">
            <?php echo  (_t("Manage Items").':')?>
          </a></b><br />
           <?php echo  (_t("Users can add, edit or delete items that can be stored in inventories.").' '.
           _t("You are also able to ransfer items between two inventories and locations."))?>
        </li>
        
        <li>
          <b><a href="index.php?mod=ims&act=view_edit_reorder_page">
          <?php echo  (_t("Re-Order Level").':')?></a></b><br />
          <?php echo  (_t("Enables users to set and modify re-order levels.").' '.
          _t('Items that are below this level are viewable through the reporting function.'))?>
        </li>
        
        <li>
          <b><a href="index.php?mod=ims&act=report_expired">
            <?php echo  (_t("Reports").':')?>
          </a></b><br />
          <?php echo  (_t("The reporting function generates reports about items that are expired or destroyed.").' '.
           _t("It also generates reports about which items require repurchase.")) ?>
        </li>
        
        <li>
          <b><a href="index.php?mod=ims&act=optim_inventory">
            <?php echo  (_t("Optimization").':')?>
          </a></b><br />
          <?php echo  (_t("Forecasts the amount of items which have been sent to another inventory, received from another inventory and also forecasts already available item amounts in a particular inventory. On the other hand under this section, the end user is allowed to set relationships among items and track items which can be used as alternatives for particular items")) ?>
        </li>
    </ul>
</div>

<h2><?php print _t("Recently added items ")?></h2>

<div id="result"> 

<?php
    //shn_form_fopen(null);
    shn_form_fsopen();

?>    
    <table>
    <thead>
        <td><?php echo _t("Item")?></td>
        <td><?php echo _t("Amount")?></td>
        <td><?php echo _t("Unit")?></td>
        <td><?php echo _t("Manufactured Date")?></td>
        <td><?php echo _t("Expire Date")?></td>
        <td><?php echo _t("Inventory")?></td>
        <td><?php echo _t("Supplier")?></td>    
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
        <td><?php echo ($item_name); ?></td>
        <td><?php echo ($amount); ?></td>
        <td><?php echo ($unit_name); ?></td>
        <td><?php echo ($manufactured_date); ?></td>
        <td><?php echo ($expire_date); ?></td>
        <td><?php echo ($inventory_name); ?></td>
        <td><?php echo ($suplier_name); ?></td>
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
    shn_rss_add_feed('rss_reorder_list',_t('Items below Re-order Level'),_t('This RSS feed gives a list of items that are below re-order level.'));
    shn_rss_add_feed('rss_transit',_t('Transit Item List'),_t('This RSS feed gives a list of items which have been transferred to other locations or inventories.'));
}
