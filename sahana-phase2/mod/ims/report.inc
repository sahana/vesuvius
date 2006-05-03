<?php
/**Reports of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once("lib_ims.inc");

/**
**Report Item
**/


function _shn_ims_report_minimum()
{
	global $global;
	$db=$global["db"];
		//$item_search=$_POST['item_name_search'];
		//$category_search=$_POST['itemcat'];
		//print ($item_search);
		
	$sql = "SELECT item_id,category,item_name,amount,unit,expire_date,suplier_name,suplier_address,suplier_telephone,suplier_email FROM ims_item_records WHERE amount<200 ;";
	$ims = $db->Execute($sql);
?>
<h1 align="center"><?php print _("Low quantity item available"); ?></h1>
<div id="reports_minimum">

</div>
	<table>
	<thead>
	<tr>
	    <td><?=_("Item ID")?></td>
	    <td><?=_("Category")?></td>
	    <td><?=_("Item")?></td>
	    <td><?=_("Amount")?></td>
	    <td><?=_("Unit")?></td>
	    <td><?=_("Expire Date")?></td>
            <td><?=_("Suplier Name")?></td>
            <td><?=_("Suplier Address")?></td>
            <td><?=_("Suplier Contact Number")?></td>
            <td><?=_("Suplier e-mail")?></td>
	</tr>
	</thead>
	<tbody>
		
<?php
		

		while (!$ims==NULL && !$ims->EOF)
		{
			$item_id=$ims->fields["item_id"];
			$category=$ims->fields["category"];
			$item_name=$ims->fields["item_name"];
			$amount=$ims->fields["amount"];
			$unit=$ims->fields["unit"];
			//$manufactured_date=$ims->fields["manufactured_date"];
			$expire_date=$ims->fields["expire_date"];
			$suplier_name=$ims->fields["suplier_name"];
			$suplier_address=$ims->fields["suplier_address"];
			$suplier_telephone=$ims->fields["suplier_telephone"];
			$suplier_email=$ims->fields["suplier_email"];	

?>
	<tr>
	<td><?php print ($item_id); ?></td>
	<td><?php print ($category); ?></td>
	<td><?php print ($item_name); ?></td>
	<td><?php print ($amount); ?></td>
	<td><?php print ($unit); ?></td>
	<td><?php print ($expire_date); ?></td>
	<td><?php print ($suplier_name); ?></td>
	<td><?php print ($suplier_address); ?></td>
	<td><?php print ($suplier_telephone); ?></td>
	<td><?php print ($suplier_email); ?></td>
	</tr>
	
<?php
	$ims->MoveNext();
	}
?>
	</tbody>
	</table>
<?php

}

//****************************************************************************************************************

/**
**function for expired item
********/
function _shn_ims_report_expired()
{

	_shn_ims_expire_date_check();
	global $global;
	$db=$global["db"];
	$state="expired";
	//$state1="destroyed";
		//$item_search=$_POST['item_name_search'];
		//$category_search=$_POST['itemcat'];
		//print ($item_search);
	//$sql1="UPDATE ims_item_records SET state='$state' WHERE ((TO_DAYS(expire_date) - TO_DAYS(CURRENT_DATE()))<0 and state!='$state1');";	
	//$sql = "SELECT item_id,category,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE ((TO_DAYS(expire_date) - TO_DAYS(CURRENT_DATE()))<0);";
	$sql="SELECT item_id,inv_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state';";
	//$ims = $db->Execute($sql1);
	$ims = $db->Execute($sql);
?>
<h1 align="center"><?php print _("Expired Item"); ?></h1>
<div id="reports_expire">
</div>
<?php
	
?>
	<table>
	<thead>
	<tr>
	    <td><?=_("Item ID")?></td>
	    <td><?=_("Item")?></td>
	    <td><?=_("Amount")?></td>
	    <td><?=_("Unit")?></td>
	    <td><?=_("Manufactured Date")?></td>
	    <td><?=_("Expire Date")?></td>
	    <td><?=_("Inventory")?></td>
	    <td><?=_("Action")?></td>
            
	</tr>
	</thead>
	<tbody>
	
		
<?php
		

		while (!$ims==NULL && !$ims->EOF)
		{
			$item_id=$ims->fields["item_id"];
			$inv_id=$ims->fields["inv_id"];
			//$category=$ims->fields["category"];
			$item_name=$ims->fields["item_name"];
			$amount=$ims->fields["amount"];
			$unit=$ims->fields["unit"];
			$manufactured_date=$ims->fields["manufactured_date"];
			$expire_date=$ims->fields["expire_date"];

		$sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims3=$db->Execute($sql3);

			$inventory_name=$ims3->fields['inventory_name'];
			

?>
	
	<tr>
	<td><?php print ($item_id); ?></td>
	<td><?php print ($item_name); ?></td>
	<td><?php print ($amount); ?></td>
	<td><?php print ($unit); ?></td>
	<td><?php print ($manufactured_date); ?></td>
	<td><?php print ($expire_date); ?></td>
	<td><?php print ($inventory_name); ?></td>
	<td><a href="index.php?mod=ims&act=destroy_item&item_id=<?php echo $item_id;?>"><?php print ("Destroy Item");?></a></td>	
	</tr>
	
<?php
	$ims->MoveNext();
	}
?>
	</tbody>
	</table>
<?php
	//shn_form_submit("Destroy");
	//shn_form_fclose();
}


//-----------------------------------------------------------------------------------------------------------------
function _shn_ims_report_destroyed()
{
	global $global;
	$state_des="destroyed";
	$db=$global["db"];
	$sql1="SELECT inv_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state_des';";
	$ims1=$db->Execute($sql1);

?>
<h1 align="center"><?php print _("Destroyed Item"); ?></h1>
<div id="report">
</div>
	<table>
		<thead>
		<tr>
		<td><?=_("Item Name")?></td>
		<td><?=_("Amount")?></td>
		<td><?=_("Unit")?></td>
		<td><?=_("Inventory")?></td>
		<td><?=_("Manufactured Date")?></td>
		<td><?=_("Expire_Date")?></td>
		<td><?=_("Suplier")?></td>
		</tr>
		</thead>
		<tbody>
<?php
		while (!$ims1==NULL && !$ims1->EOF)
		{
			//$item_id=$ims1->fields['item_id'];
			$inv_id=$ims1->fields['inv_id'];
			$item_name=$ims1->fields['item_name'];
			$amount=$ims1->fields['amount'];
			$unit=$ims1->fields['unit'];
			$manufactured_date=$ims1->fields['manufactured_date'];
			$expire_date=$ims1->fields['expire_date'];

			$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
			$ims2=$db->Execute($sql2);
			
			$inventory_name=$ims2->fields['inventory_name'];
			
?>
		<tr>
		<td><?php print($item_name);?></td>
		<td><?php print($amount);?></td>
		<td><?php print($unit);?></td>
		<td><?php print($inventory_name);?></td>
		<td><?php print($manufactured_date);?></td>
		<td><?php print($expire_date);?></td>
		</tr>
<?php
		$ims1->MoveNext();
		}
?>
		</tbody>
	</table>
<?php	
}

/**
**Report Inventory
**/

function _shn_ims_level($parent)
{
    global $global;
    $db=$global['db'];
    if($parent<0){
    	$parent=NULL;
    }
    $q="select option_description,option_code,name from field_options,location where field_options.option_code=location.opt_location_type and location.location_id=$parent and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    if($res_label!=NULL && !$res_label->EOF){
        $parent_type="For  ".$res_label->fields[2];
    }
    $child=$res_label->fields[1]+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $child_type=$res_label->fields[0];
    $child=$child+1;
    $q="select option_description from field_options where field_options.option_code=$child and field_name='opt_location_type'"; 
    $res_label=$db->Execute($q);
    $grand_child_type=$res_label->fields[0];
?>
<h2><?=_("Organization Report By ". $child_type." ".$parent_type) ?></h2>
    <div id="note">
<?=_("Each Row is a ".$child_type." ,Column is a  Service.")?><br />
<?php 
    $last=shn_get_last_level();
    if ($last[0]!=$child-1){
        echo _("Intersection shows the precentage of Sub-divisions Covered per each service.")."<br />";
        echo _("For this report Sub-division is a  ".$grand_child_type.".");
        echo _("If atleast one ".$last[1]. " in the Sub-division has an organization providing the service then that Sub-division is considered as covered for that service.");
    }else {
        echo _("Intersection shows whether each ".$child_type." has atleast one organization providing the service.")."<br />";
    }
?>
</div>
<div id ="result">
    <table>
        <thead>
        <td>
<?php
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
       echo "<td>".$res_sector->fields[1]."</td>";
       $res_sector->MoveNext();
    }
       $res_sector->MoveFirst();
?>       
        </thead>
    <tbody>
<?php
	if($parent==NULL){
		$q = "select location_id,name from location where parent_id is NULL order by name";
	}else {
		$q = "select location_id,name from location where parent_id=$parent order by name";
	}
    $res_loc=$db->Execute($q);
    while(!$res_loc==NULL && !$res_loc->EOF){
?>
    <tr>
        <td>
<?php if(shn_is_last_level($res_loc->fields[0])){
        echo $res_loc->fields[1];
      }else {
        echo "<a href='index.php?mod=or&act=drill_report&id=".$res_loc->fields[0]."'>".$res_loc->fields[1]."</a>";
      }
?>
        </td>
<?php
        while(!$res_sector==NULL && !$res_sector->EOF){
            if(shn_is_last_level($res_loc->fields[0])){
                echo ($res["active"]);
               if(_shn_is_covered($res_loc->fields[0],$res_sector->fields[0])){
                    $active=_("Covered");
		            echo "<td><b><font color=#2E8B57>".$active."</font></b></td>";
                }else {
                    $active=_("Not Covered");
		            echo "<td><b><font color=#FF0000>".$active."</font></b></td>";
                }
            }else {
                $res=_shn_coverage_loc($res_loc->fields[0],$res_sector->fields[0]);
                $precent=0;
                if($res["total"]>0){
                    $precent=round($res["active"]/$res["total"] *100,2);
                }
                echo "<td><b><font color=#2E8B57>".$res["active"]."/".$res["total"]."</font> (<font color=#FF0000>".$precent."%</font>)</b></td>";
            }
            $res_sector->MoveNext();
        }
        $res_sector->MoveFirst();
        $res_loc->MoveNext();
?>
    </tr>
<?php
    }
?>    
       </tbody>
  </table>
</div>

<?php
}

function _shn_coverage_loc($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $result=array();
    $result["total"]=0;
    $result["active"]=0;
    $q="select location_id,name from location where parent_id={$loc}";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $result["total"]=$result["total"]+1;
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($res_tmp->fields[0],$sector)){    
            $result["active"]=$result["active"]+1;
        }
        $res_tmp->MoveNext();
    }
   return $result; 
}

function _shn_is_covered($loc,$sector)
{
    global $global;
    $db=$global["db"];
    $q="select location_id from location_details,sector where location_details.location_id={$loc} and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector}'";
    $res_village=$db->Execute($q);
     if(!$res_village==NULL && !$res_village->EOF){
            return true;
    }
    $q="select location_id,name from location where parent_id={$loc}";
    $res_tmp=$db->Execute($q);
    while(!$res_tmp==NULL && !$res_tmp->EOF){
        $next_lvl=$res_tmp->fields[0];
        if(_shn_is_covered($next_lvl,$sector)){
            return true;
        }
        $res_tmp->MoveNext();
    }
   return false; 
}

function _shn_ims_report_org_sector()
{
    include_once("view_inv.inc");
    global $global;
    $db=$global['db'];
    
?>
<h2><?=_("Organization Report by Sector")?></h2>
<div id ="result">
    <table>
        <thead>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Services Offered")?></td>
            <td><?=_("Organization Type")?></td>
            <td><?=_("Country of Origin")?></td>
            <td><?=_("Address")?></td>
            <td><?=_("Contact Number")?></td>
            <td><?=_("Man Power")?></td>
            <td><?=_("Equipment")?></td>
            <td><?=_("Facilities")?></td>
        </thead>
        <tbody>
<?php    
    $q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res_sector=$db->Execute($q);
    while(!$res_sector==NULL && !$res_sector->EOF){
        $option_code=$res_sector->fields[0];
        $q = "select inv_uuid,parent_id,inventory_name,man_power,equipment,resources from  ims_inventory_records,sector where sector.opt_sector='{$option_code}' and sector.pgoc_uuid=ims_inventory_records.inv_uuid order by name";
        $res_org=$db->Execute($q);
	    if(!$res_org->EOF){
	    ?>
	    <tr>
		    <td>
	            <b><?=_($res_sector->fields[1])?></b>
		    </td>
	    </tr>
	    <?php
        }
        while(!$res_org==NULL && !$res_org->EOF){
            $org_id=$res_org->fields[0];
            _shn_display_org($org_id,false);
            $res_org->MoveNext();
        }
        $res_sector->MoveNext();
    }
?>
   </tbody>
  </table>
</div>

<?php
}

function _shn_ims_destroy_item($item_id)
{
	$old_state = "expired";
	$new_state = "destroyed";
	global $global;
    	$db=$global["db"];
	$sql="UPDATE ims_item_records SET state='$new_state' WHERE item_id='$item_id';";
	$ims = $db->Execute($sql);
	//print ($sql);
	shn_ims_report_expired();
}
