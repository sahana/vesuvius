<?php
/**
* Sahana Inventory Management System view and edit item page
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

/**
**function for view edit header 
**/
include_once $global['approot'].'/mod/or/lib_or.inc';
include_once ('lib_ims.inc');

function _shn_ims_view_edit_header()
{
?>

    <h1 align="center"><?php print _("View and Edit Items");?><br></h1>
    <dev id="result">

    </dev>
<?php

}

/**
**GUI for View edit form
**/

function _shn_ims_view_edit()
{


    global $global;
    $module = $global['module'];

    shn_form_fsopen();
    
?>
    <div id ="result">
    <table>
        <thead>
        <td><?=_("Item");?></td>
        <td><?=_("Amount");?></td>
        <td><?=_("Unit");?></td>
        <td><?=_("Manufactured Date")?></td>
            <td><?=_("Expire Date")?></td>
        <td><?=_("Available Inventory")?></td>
            <td><?=_("Suplier Name")?></td>
        <td><?=_("Edit")?></td>
        <td><?=_("Delete")?></td>
            
        </thead>
    <tbody>
<?php
        global $global;
        $db=$global["db"];
        $state_des="destroyed";
        //$item_search=$_POST['item_name_search'];
        //print ($item_search);
        
        $sql = "select item_id,catalog_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date from ims_item_records WHERE state!='$state_des' order by item_name ;";
        //$sql1 = "SELECT name FROM ct_catalogue WHERE (SELECT catalog_id FROM ims_item_records );";
        $ims = $db->Execute($sql);

        while (!$ims==NULL && !$ims->EOF)
        {
            $item_id=$ims->fields["item_id"];
            $catalog_id=$ims->fields["catalog_id"];
            $inv_id=$ims->fields["inv_id"];
            $suplier_id=$ims->fields['suplier_id'];
            //$category=$ims->fields["category"];
            $item_name=$ims->fields["item_name"];
            $amount=$ims->fields["amount"];
            $unit=$ims->fields["unit"];
            $unit_name=get_unit_name($unit);
            $manufactured_date=$ims->fields["manufactured_date"];
            $expire_date=$ims->fields["expire_date"];
            

        $sql1="SELECT name FROM ct_catalogue WHERE ct_uuid='$catalog_id';";
        $ims1 = $db->Execute($sql1);
            $category=$ims1->fields["name"];

        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims2= $db->Execute($sql2);
        $inventory_name = $ims2->fields["inventory_name"];
            //$parent_id=$ims1->fields["parentid"];

        $org_list_array=shn_or_org_list();
        $suplier_name=$org_list_array[$suplier_id];

    
            
?>
        <tr>
        
        <td><?php print ($item_name); ?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date);?></td>
        <td><?php print ($inventory_name);?></td>
        <td><?php print ($suplier_name);?></td>
        <td><a href="index.php?mod=ims&act=add_item1&item_id=<?php echo $item_id;?>&parent_id=<?php echo $catalog_id;?>"><?php print ("Edit");?></a></td>
        <td><a href="index.php?mod=ims&act=delete_item_db&item_id=<?php echo $item_id;?>&parent_id=<?php echo $catalog_id;?>"><?php print ("Delete");?></a></td>
        
        </tr>

    
<?php
    
    $ims->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>
<?php
    shn_form_fclose();
}

function _shn_ims_edit_item_db()
{
    global $global;
        include_once ("add_item.inc");
        
        $db=$global["db"];
        $temp=trim($_POST['temp']);
        //print ($temp);
        $cate=trim($_POST['cat']);
        $item=trim($_POST['item_name']);
        //print ($temp);
        
        //print ($cate);
        $amou=trim($_POST['amount']);
        $unit=trim($_POST['unit_select']);
        $manufactured_date=trim($_POST['manufactured_date']);
        $expire_date=trim($_POST['expire_date']);
        $inv_id=trim($_POST['inv_id']);
        $cost_per_unit=trim($_POST['cost_per_unit']);
        $suplier_id=trim($_POST['suplier_id']);


        //print ($expire_date);
        
            $sql = "UPDATE ims_item_records SET item_name='{$item}',suplier_id='{$suplier_id}',amount='{$amou}',unit='{$unit}', manufactured_date='{$manufactured_date}',expire_date='{$expire_date}',inv_id='{$inv_id}',cost_per_unit='{$cost_per_unit}' WHERE item_id=$temp;";
//echo $sql;
        $ims = $db->Execute($sql);
        
        
        _shn_ims_expire_date_check();
?>
    <div id="result_msg">
       <?php echo $item?> Item was succesfully Saved
    </div>
    <br />    

<?php
        $_POST['item_name']="";    
        $_POST['amount']="";
        $_POST['manufactured_date']="";
        $_POST['expire_date']="";
        $_POST['cost_per_unit']="";
        shn_ims_view_edit_item();
}
?>
