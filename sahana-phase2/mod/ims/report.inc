<?php
/**Reports of the Inventory Management System 
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
* @subpackage ims
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once("lib_ims.inc");
//include_once("optimize.inc");

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
    $sql1="SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level;";
    $ims1=$db->Execute($sql1);
    
    //$amount=0;
    //print $sql1;    
    
    /*$sql = "SELECT item_id,category,item_name,amount,unit,expire_date,suplier_name,suplier_address,suplier_telephone,suplier_email FROM ims_item_records WHERE amount<200 ;";
    $ims = $db->Execute($sql);*/
?>
<h1 align="center"><?php print _("Re-Order Level"); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
        <td><?=_("Item")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit")?></td>
        <td><?=_("Inventory")?></td>
        
            
    </tr>
    </thead>
    <tbody>
        
<?php
        $state = "destroyed";
        //$state_des="destroyed";
        $sum_amount=0;
        //print time();
        //print ("\n");
        
        while (!$ims1==NULL && !$ims1->EOF)
        {
            $catalog_id_min=$ims1->fields['catalog_id'];
            //print $item_id_min;
            $inv_id_min=$ims1->fields['inv_id'];
            //print $inv_id_min;
            $minimum_quantity=$ims1->fields['minimum_quantity'];
            
            //print $minimum_quantity;
            $unit=$ims1->fields['unit'];
            
            $unit_name=get_unit_name($unit);

            $sql2 = "SELECT unit,amount FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min'AND state!='$state';";
            $ims2 =$db->Execute($sql2);
            //print $sql2;
            //print $sql2;
            //print $sql2;
            while(!$ims2==NULL && !$ims2->EOF)
            {
            //$sum_amount = $ims2->fields['SUM(amount)'];
            $current_unit=$ims2->fields['unit'];
            $current_amount=$ims2->fields['amount'];
                        
            
    $multiplier=unit_converter($unit,$current_unit);
    
    
    $current_amount_convert=$current_amount*$multiplier;
    
    $sum_amount=$sum_amount+$current_amount_convert;
    
    //$total_amount=$sum_amount;
    
            $ims2->MoveNext();
            }
    
//$sum_amount=0;
        if($sum_amount<$minimum_quantity)
            {
                $total_amount=$sum_amount;
                $sum_amount=0;
                $sql3 = "SELECT item_id,item_name,unit FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min';";
                $ims3 = $db->Execute($sql3);
    
            
                //print $sql3;

                $sql4 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_min';";
                $ims4 = $db->Execute($sql4);
                $inventory_name=$ims4->fields['inventory_name'];
                //print $sql2;
                //print $sql4;

                $item_id=$ims3->fields["item_id"];

            if($item_id!=null)
            {
                   
                //$category=$ims2->fields["category"];
                $item_name=$ims3->fields["item_name"];
                //$amount=$ims2->fields["amount"];
                //$amount=$current_amount + $amount;
                $unit=$ims3->fields["unit"];
                //$manufactured_date=$ims->fields["manufactured_date"];
                //$expire_date=$ims3->fields["expire_date"];
            

?>
    		<tr>    
    		<td><?php print ($item_name); ?></td>

    		<td><?php print ($total_amount); ?></td>
    		<td><?php print ($unit_name); ?></td>
    		<td><?php print ($inventory_name); ?></td>
        
    		</tr>
    
<?php
    }
    }
    else if($sum_amount>=$minimum_quantity)
    {
        $sum_amount=0;
    }
        $ims1->MoveNext();
    }    
            
            
?>
    </tbody>
    </table>
    </div>

    
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
    
    $sql="SELECT item_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state';";
    //$ims = $db->Execute($sql1);
    $ims = $db->Execute($sql);
?>
<h1 align="center"><?php print _("Expired Item"); ?></h1>
<div id="result">
<?php
    
?>
    <table>
    <thead>
    <tr>
        <td><?=_("Item")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit")?></td>
        <td><?=_("Manufactured Date")?></td>
        <td><?=_("Expire Date")?></td>
        <td><?=_("Inventory")?></td>
        <td><?=_("Suplier")?></td>
        <td><?=_("Action")?></td>
            
    </tr>
    </thead>
    <tbody>
    
        
<?php
        $suplier_array=array();

        while (!$ims==NULL && !$ims->EOF)
        {
            $item_id=$ims->fields["item_id"];
            $inv_id=$ims->fields["inv_id"];
            $suplier_id=$ims->fields["suplier_id"];

            $suplier_array=_shn_or_get_suplier_name($suplier_id);
            $suplier_name=$suplier_array[$suplier_id];
            //$category=$ims->fields["category"];
            $item_name=$ims->fields["item_name"];
            $amount=$ims->fields["amount"];
            $unit=$ims->fields["unit"];
            $unit_name=get_unit_name($unit);
            $manufactured_date=$ims->fields["manufactured_date"];
            $expire_date=$ims->fields["expire_date"];

        $sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims3=$db->Execute($sql3);

            $inventory_name=$ims3->fields['inventory_name'];
            

?>
    
    <tr>
    <td><?php print ($item_name); ?></td>
    <td><?php print ($amount); ?></td>
    <td><?php print ($unit_name); ?></td>
    <td><?php print ($manufactured_date); ?></td>
    <td><?php print ($expire_date); ?></td>
    <td><?php print ($inventory_name); ?></td>
    <td><?php print ($suplier_name); ?></td>
    <td><a href="index.php?mod=ims&act=destroy_item&item_id=<?php echo $item_id;?>"><?php print ("Destroy Item");?></a></td>    
    </tr>
    
<?php
    $ims->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>
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
    $sql1="SELECT inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state_des';";
    $ims1=$db->Execute($sql1);

?>
<h1 align="center"><?php print _("Destroyed Item"); ?></h1>
<div id="result">

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
            $suplier_id=$ims1->fields['suplier_id'];
            $suplier_array=_shn_or_get_suplier_name($suplier_id);
            $suplier_name=$suplier_array[$suplier_id];
        
            $item_name=$ims1->fields['item_name'];
            $amount=$ims1->fields['amount'];
            $unit=$ims1->fields['unit'];
            $unit_name=get_unit_name($unit);
            $manufactured_date=$ims1->fields['manufactured_date'];
            $expire_date=$ims1->fields['expire_date'];

            $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
            $ims2=$db->Execute($sql2);
            
            $inventory_name=$ims2->fields['inventory_name'];
            
?>
            <tr>
            <td><?php print($item_name);?></td>
            <td><?php print($amount);?></td>
            <td><?php print($unit_name);?></td>
            <td><?php print($inventory_name);?></td>
            <td><?php print($manufactured_date);?></td>
            <td><?php print($expire_date);?></td>
            <td><?php print($suplier_name);?></td>
            </tr>
<?php
            $ims1->MoveNext();
        }
?>
        </tbody>
    </table>
    </div>
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

//************************************** Report Prediction ****************************************************

function _shn_ims_report_prediction()
{

$catalog_id=$_POST['parent_id'];
$inv_id=$_POST['inv_id'];
$time_amount=$_POST['time_amount'];
$time_period1=$_POST['time_period1'];
$time_period2=$_POST['time_period2'];
$time_period3=$_POST['time_period3'];

print $catalog_id;
print $inv_id;
print $time_amount;
print $time_period1;
?>
<h1 align="center"><?php print(_("Item Prediction Report")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
        <td><?=_("Item")?></td>
	<td><?=_("Inventory")?></td>
	<td><?=_("Unit")?></td>
        <td><?=_("Prediction-1")?></td>
        <td><?=_("Prediction-2")?></td>
        <td><?=_("Prediction-3")?></td>
        
            
    </tr>
    </thead>
    <tbody>
<?php
    	global $global;
	$db=$global["db"];

	$current_date=date("d-m-Y");
	print $current_date;
	$week=date("d-m-Y",time() - 604800);
	print "\n";
	//print $week;
	$next_date="01-06-2006";
	// ".";
	//print dateDiff("-",$current_date,$next_date);
	
//------------------------------------------------------------------------------------------------

	
		$state="destroyed";
        	$sql0="SELECT item_id,item_name,amount,unit,inserted_date FROM ims_item_records WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' AND state!='$state' AND (TO_DAYS(CURRENT_DATE())-TO_DAYS(inserted_date))<8;";    
    		$ims0 = $db->Execute($sql0);
print $sql0;
		//print $sql0;
		//print $sql0;
		$sum_amount=0;
		$sum_amount2=0;

		/*list($year,$month,$date) = split('-', $inserted_date);
		//$inserted_date=$day+$month+$year;
		$inserted_date=unixtojd();
		//print $inserted_date;

		$jd = gregoriantojd(12,12,2006);
		print ("HI");
		$unix = jdtounix($jd);
		//echo($unix);

		print (unixtojd($inserteddate-$unix));*/

		while(!$ims0==NULL && !$ims0->EOF )
		{
		$item_id=$ims0->fields["item_id"];
		$item_name=$ims0->fields["item_name"];
		$amount=$ims0->fields["amount"];
		$unit=$ims0->fields["unit"];
		$inserted_date=$ims0->fields["inserted_date"];

		//$inserted_date=strrev($inserted_date);
		
// Delimiters may be slash, dot, or hyphen
//$date = "04/30/1973";
		
//echo "Month: $month; Day: $day; Year: $year<br />\n";

		
		

		$base_unit=convert_to_base_unit($unit);
		$previous_sum_amount=0;

		//if(dateDiff("-",$current_date,$inserted_date)<$time_period1)
		//{
            
            $converted_amount=$amount*unit_converter($base_unit,$unit);
            //print $converted_amount;
            $sum_amount=$sum_amount + $converted_amount;
		//}
		//if(dateDiff("-",$current_date,$inserted_date)<$time_period2)
		//{
		//$converted_amount2=$amount*unit_converter($base_unit,$unit);
            //print $converted_amount;
            	$sum_amount2=$sum_amount2 + $converted_amount2;
		//}
		
        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims2=$db->Execute($sql2);
	$inventory_name=$ims2->fields["inventory_name"];

	$unit_name=get_unit_name($base_unit);
?>
    
<?php
	//$ims0->MoveNext();
	//}
	$sum_amount2=_shn_ims_smoothing(0,$sum_amount);
?>
	
    <tr>
    <td><?php print $item_name;?></td>
    <td><?php print $inventory_name; ?></td>
    <td><?php print $unit_name; ?></td>
    <td><?php print $sum_amount; ?></td>
    <td><?php print $sum_amount2; ?></td>
    </tr>
    	
<?php
	$ims0->MoveNext();
	}
?>
</tbody>
</table>
</div>
<?php 
	}

function _shn_ims_prediction_inv()
{
global $global;
$db=$global["db"];
$inv_id=$_POST['inv_id'];

?>
<h1 align="center"><?php print(_("Inventory Prediction Report")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
        <td><?=_("Item")?></td>
	<td><?=_("Inventory")?></td>
	<td><?=_("Unit")?></td>
	<td><?=_("Available amount")?></td>
        <td><?=_("Prediction-1")?></td>
        <td><?=_("Prediction-2")?></td>
        <td><?=_("Prediction-3")?></td>
        
            
    </tr>
    </thead>
    <tbody>
<?php
	$sql2="SELECT * FROM ims_optimization WHERE inv_id='$inv_id';";
	$ims2=$db->Execute($sql2);
	$optim_id=$ims2->fields['optim_id'];
	
	

	$sql="SELECT added_date FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims=$db->Execute($sql);
	$inv_date=$ims->fields['added_date'];
	$inv_date=_shn_ims_date_conversion($inv_date);	
	print $inv_date;
	$week=date("d-m-Y",time() + 604800);
	print $week;

	$state="destroyed";
	//$sql0="SELECT item_id,catalog_id,item_name,amount,unit,inserted_date FROM ims_item_records WHERE  inv_id='$inv_id' AND state!='$state' AND (TO_DAYS(CURRENT_DATE())-TO_DAYS(inserted_date))<8;";
	$sql0="SELECT item_id,catalog_id,item_name,amount,unit,inserted_date FROM ims_item_records WHERE  inv_id='$inv_id' AND state!='$state';";
	$ims0=$db->Execute($sql0);
	print $sql0;
	

	while(!$ims0==NULL && !$ims0->EOF)
	{
		$item_id=$ims0->fields['item_id'];
		$item_name=$ims0->fields['item_name'];
		$catalog_id=$ims0->fields['catalog_id'];
		$amount=$ims0->fields['amount'];
		//$unit=$ims0->fields['unit'];
		$inserted_date=$ims0->fields['inserted_date'];
		$inserted_date=_shn_ims_date_conversion($inserted_date );
		print $inserted_date;
		$sum_amount=0;

		if(_shn_ims_datediff('-',$inserted_date,$inv_date)<8)
		{
			$sql1="SELECT item_name,amount,unit FROM ims_item_records WHERE catalog_id='$catalog_id';";
		$ims1=$db->Execute($sql1);
		print $sql1;
		while(!$ims1==NULL && !$ims1->EOF)
		{
			$item_name=$ims1->fields['item_name'];
			//$item=$item_name;
			$amount=$ims1->fields['amount'];
			$unit=$ims1->fields['unit'];
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
		
            		//$sum_amount2=$sum_amount2 + $converted_amount2;
			$ims1->MoveNext();
		}


		}

		
		
?>
		<tr>
		<td><?php print $item_name?></td>
		<td><?php print ("Inventory");?></td>
		<td><?php print ("Unit");?></td>
		<td><?php print $sum_amount;?></td>
		<td><?php ?></td>
		<td><?php ?></td>
		<td><?php ?></td>
		</tr>
		
<?php
		
		$ims0->MoveNext();
	}
?>
	</tbody>
	</table>
<?php
}
?>
