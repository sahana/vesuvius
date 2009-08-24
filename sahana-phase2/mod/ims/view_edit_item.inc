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

    <h1 align="center"><?php print _t("Item Registry");?><br></h1>
    <dev id="result">

    </dev>
<?php

}

/**
**GUI for View edit form
**/

function _shn_ims_view_edit($i,$Limit=null)
{
    global $global;
    $module = $global['module'];
    $form_opts['name']="edit_item";
    shn_form_fopen("view_edit_item_actions",null,$form_opts);
    shn_form_fsopen(_t("Add Item"));
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_t("Add Item"),"onClick='change_action(\"additem\")'",$extra_opts);
   // shn_form_submit(_t("Add Item"));
    shn_form_fsclose();
    
    //shn_form_fsopen(null);
    print '<b>';
    shn_form_text(_t("Records Per Page : "),'status','onChange="submit(this);"',array('value'=>$Limit));
    //shn_form_select($stat, _t("Status"), 'status', 'onChange="submit(this);"',null);
?>

    <div id ="result">
    <table>
        <thead>
        <td><?=_t("Item");?></td>
        <td><?=_t("Amount");?></td>
        <td><?=_t("Unit");?></td>
        <td><?=_t("Manufactured Date")?></td>
            <td><?=_t("Expire Date")?></td>
        <td><?=_t("Available Inventory")?></td>
            <td><?=_t("Supplier Name")?></td>
        <td><?=_t("Edit")?></td>
        <td><?=_t("Delete")?></td>
            
        </thead>
    <tbody>
<?php
        global $global;
        $db=$global["db"];
        $state_des="destroyed";
        

	//$Limit=20;
	
	if($i!=0)
        {
	    $i=($i-1)*$Limit;
        }
        else 
        {
	    $i=0;
        }

	$sql1="SELECT item_id,catalog_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date from ims_item_records WHERE state!='$state_des' AND amount!=0 order by item_name LIMIT $i,$Limit;";
	$ims = $db->Execute($sql1);
        

	$sql="SELECT item_id,catalog_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date from ims_item_records WHERE state!='$state_des' AND amount!=0 order by item_name;";

	$SearchResult=mysql_query($sql) or die(mysql_error()); 
	$NumberOfResults=mysql_num_rows($SearchResult); 
		
	$NumberOfPages=ceil($NumberOfResults/$Limit); 
	
	
	print(_t("Go to Page : "));
	
	for($i=1;$i<$NumberOfPages+1;$i++)
	{

	    ?><a href="index.php?mod=ims&act=list_items_paging&$i=<?php echo $i;?>&Limit=<?php echo $Limit;?>"><?php print ($i." ");?></a><?php
	    print "\n";
	}
	 print '</b>';

        while (!$ims==NULL && !$ims->EOF)
        {
	    $numberofresults=$numberofresults+1;

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
           

	$suplier_name_array=array();
    $suplier_name_array=_shn_or_get_suplier_name($suplier_id);
	$suplier_name=$suplier_name_array[$suplier_id];
    
            
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
        <!--<td><a href="index.php?mod=ims&act=delete_item_db&item_id=<?php echo $item_id;?>&parent_id=<?php echo $catalog_id;?>"><?php print ("Delete");?></a></td>-->
        <td><a href="index.php?mod=ims&act=delete_item_confirm&item_id=<?php echo $item_id;?>&parent_id=<?php echo $catalog_id;?>"><?php print ("Delete");?></a></td>
        
        </tr>

    
<?php
    
    $ims->MoveNext();
    }

	
?>
    </tbody>
    </table>
    </div>
<?php
//shn_form_fsclose();
shn_form_fsopen(_t("Inventory Transfer"));
 $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_t("Close"),"onClick='change_action(\"close\")'",$extra_opts);
    shn_form_button(_t("Send Item"),"onClick='change_action(\"send\")'",$extra_opts);
    shn_form_button(_t("Clear sent Items"),"onClick='change_action(\"transit\")'",$extra_opts);
    //shn_form_button(_t("Add Item"),"onClick='change_action(\"additem\")'",$extra_opts);
?>
</center>
<?php

    shn_form_hidden(array('action'=>'0'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_ims_edit_item_db()
{
    global $global;
        include_once ("add_item.inc");
        
        $db=$global["db"];
        $temp=trim($_POST['temp']);
        
        $cate=trim($_POST['cat']);
        $item=trim($_POST['item_name']);
        
        $amou=trim($_POST['amount']);
        $unit=trim($_POST['unit_select']);
        $manufactured_date=trim($_POST['manufactured_date']);
        $expire_date=trim($_POST['expire_date']);
        $inv_id=trim($_POST['inv_id']);
        $cost_per_unit=trim($_POST['cost_per_unit']);
        $suplier_id=trim($_POST['suplier_id']);
        
            $sql = "UPDATE ims_item_records SET item_name='{$item}',suplier_id='{$suplier_id}',amount='{$amou}',unit='{$unit}', manufactured_date='{$manufactured_date}',expire_date='{$expire_date}',inv_id='{$inv_id}',cost_per_unit='{$cost_per_unit}' WHERE item_id=$temp;";

        $ims = $db->Execute($sql);
        
        
        _shn_ims_expire_date_check();
	add_confirmation($item._t(' Item was successfully updated'));

        $_POST['item_name']="";    
        $_POST['amount']="";
        $_POST['manufactured_date']="";
        $_POST['expire_date']="";
        $_POST['cost_per_unit']="";
        shn_ims_view_edit_item();
}

function _shn_ims_view_edit_item_actions()
{
    global $global;
    $db=$global["db"];

    $action=trim($_POST['action']);


    $stat=$_POST['status'];

    if($action=='0')
    {
	if(!is_numeric($stat))
	{
	    add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
	    display_errors();
	    shn_ims_list_items_paging($stat=20);
	}
	if($stat=='0' || $stat<0)
	{
	    add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
	    display_errors();
	    shn_ims_list_items_paging($stat=20);
	}
	shn_ims_list_items_paging($stat);
    }
    if($action=='close')
    {
        shn_ims_default();
    }
    if($action=='send')
    {
	shn_ims_send_item();
    }
    if($action=='transit')
    {
	shn_ims_receive_item();
    }
    if($action=='additem')
    {
	shn_ims_add_item_main_page();
    }
}




?>

<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.edit_item.submit();
         return;
    }
</script>
<?php

?>