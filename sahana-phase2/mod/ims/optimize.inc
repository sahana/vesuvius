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
* @copyright        Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage        ims
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

//include_once $global['approot']."/inc/lib_form.inc";
//include_once $global['approot']."/inc/lib_errors.inc";
include_once "lib_ims.inc";

function _shn_ims_relation_item()
{
?>

    <h1 align="center"><?php print _("Select Relation Item/Items");?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name']='subcat';
    shn_form_fopen("relation_item_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();
}

function _shn_ims_relation_item_page()
{
	$depth=get_max_depth();
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for($i=1;$i<$depth;$i++)
    {
        $parent_id = trim($_POST[$i]);
    
        if($parent_id==null)
        {
            $parent_id = $_POST[$i-1];
            break;
        }
    }
	global $global;
	$db=$global["db"];
	print $parent_id;
	shn_form_fopen("relation_item_table");
	shn_form_fsopen("Inventory Selection");

	$inventory_array=array();
	$inventory_array['all']="All Inventories";
    $q0="SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0=$db->Execute($q0);
    
    while($ims0!=NULL && !$ims0->EOF)
    {
        
        $inventory_array[$ims0->fields['inv_uuid']]=$ims0->fields['inventory_name'];//}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
	shn_form_fsclose();
	shn_form_hidden(array('parent_id'=>$parent_id));
	shn_form_submit("Submit");
	shn_form_fclose();
	
}

function _shn_ims_relation_item_table()
{
	global $global;
	$db=$global["db"];

	$parent_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	print $inv_id;
?>
<h1 align="center"><?php print(_("Relational Item Selection")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
        <td><?=_("Item")?></td>
	<td><?=_("Inventory")?></td>
	<td><?=_("Unit")?></td>
	<td><?=_("Available amount")?></td>
        <td><?=_("Action ")?></td>
        
        
            
    </tr>
    </thead>
    <tbody>
<?php

	if($inv_id=="all")
	{
		$sql1="SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id';";
		$ims1=$db->Execute($sql1);
		$inventory_name1="All Inventories";
	}
	else
	{
		$query="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims_query=$db->Execute($query);
		$inventory_name1=$ims_query->fields['inventory_name'];
		$sql1="SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id' AND inv_id='$inv_id';";
		$ims1=$db->Execute($sql1);
		//print $sql1;
	}
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$catalog_id=$ims1->fields['catalog_id'];
		$item_name=$ims1->fields['item_name'];
		$amount=$ims1->fields['amount'];
		$unit=$ims1->fields['unit'];
		$base_unit=convert_to_base_unit($unit);
		$unit_name=get_unit_name($base_unit);

		$sum_amount=_shn_ims_sum_amount($catalog_id,$inv_id);

		
?>
	<tr>
	<td><?php print $item_name; ?></td>
	<td><?php print $inventory_name1; ?></td>
	<td><?php print $unit_name;?></td>
	<td><?php print $sum_amount;?></td>
	<td><!--<a href="index.php?mod=ims&act=alternate_item_db&catalog_id=<?php echo $catalog_id;?>&parent_id=<?php echo $parent_id;?>&inv_id=<?php echo $inv_id;?>"><?php print ("Alternate");?></a>--><?php print (" , ");?><a href="index.php?mod=ims&act=relation_item_db&catalog_id=<?php echo $catalog_id;?>&parent_id=<?php echo $parent_id;?>&inv_id=<?php echo $inv_id;?>"><?php print ("Relation");?></a></td>
	</tr>
<?php
	$ims1->MoveNext();	
	}
?>
</tbody>
</table>
<?php
}

function _shn_ims_relation_item_db($parent_id,$catalog_id,$inv_id)
{
	global $global;
	$db=$global["db"];
	
	$relation=$catalog_id;

	$sql1="INSERT INTO ims_relation (catalog_id,inv_id,relation) VALUES ('$parent_id','$inv_id','$relation');";
	$ims1=$db->Execute($sql1);
	print $sql1;
}

//*********************************** Alternate Item ***************************************************************

function _shn_ims_alternate_item()
{
    ?>

    <h1 align="center"><?php print _("Select Alternate Item/Items");?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name']='subcat';
    shn_form_fopen("alternate_item_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();

}

function _shn_ims_alternate_item_page()
{
    $depth=get_max_depth();
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for($i=1;$i<$depth;$i++)
    {
        $parent_id = trim($_POST[$i]);
    
        if($parent_id==null)
        {
            $parent_id = $_POST[$i-1];
            break;
        }
    }
	global $global;
	$db=$global["db"];
	print $parent_id;
	shn_form_fopen("alternate_item_table");
	shn_form_fsopen("Inventory Selection");

	$inventory_array=array();
	$inventory_array['all']="All Inventories";
    $q0="SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0=$db->Execute($q0);
    
    while($ims0!=NULL && !$ims0->EOF)
    {
        
        $inventory_array[$ims0->fields['inv_uuid']]=$ims0->fields['inventory_name'];//}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
	shn_form_fsclose();
	shn_form_hidden(array('parent_id'=>$parent_id));
	shn_form_submit("Submit");
	shn_form_fclose();
	
}

function _shn_ims_alternate_item_table()
{
	global $global;
	$db=$global["db"];

	$parent_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	print $inv_id;
?>
<h1 align="center"><?php print(_("Alternate Item Selection")); ?></h1>
<div id="result">

    <table>
    <thead>
    <tr>
        
        <td><?=_("Item")?></td>
	<td><?=_("Inventory")?></td>
	<td><?=_("Unit")?></td>
	<td><?=_("Available amount")?></td>
        <td><?=_("Action ")?></td>
        
        
            
    </tr>
    </thead>
    <tbody>
<?php

	if($inv_id=="all")
	{
		$sql1="SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id';";
		$ims1=$db->Execute($sql1);
		$inventory_name1="All Inventories";
	}
	else
	{
		$sql1="SELECT * FROM ims_item_records WHERE catalog_id!='$parent_id' AND inv_id='$inv_id';";
		$ims1=$db->Execute($sql1);
		//print $sql1;
		$query="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims_query=$db->Execute($query);
		$inventory_name1=$ims_query->fields['inventory_name'];
	}
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$catalog_id=$ims1->fields['catalog_id'];
		$item_name=$ims1->fields['item_name'];
		$amount=$ims1->fields['amount'];
		$unit=$ims1->fields['unit'];
		$base_unit=convert_to_base_unit($unit);
		$unit_name=get_unit_name($base_unit);

		$sum_amount=_shn_ims_sum_amount($catalog_id,$inv_id);
?>
	<tr>
	<td><?php print $item_name; ?></td>
	<td><?php print $inventory_name1; ?></td>
	<td><?php print $unit_name;?></td>
	<td><?php print $sum_amount;?></td>
	<td><a href="index.php?mod=ims&act=alternate_item_db&catalog_id=<?php echo $catalog_id;?>&parent_id=<?php echo $parent_id;?>&inv_id=<?php echo $inv_id;?>"><?php print ("Alternate");?></a><!--<?php print (" , ");?><a href="index.php?mod=ims&act=relation_item_db&catalog_id=<?php echo $catalog_id;?>&parent_id=<?php echo $parent_id;?>&inv_id=<?php echo $inv_id;?>"><?php print ("Relation");?></a></td>-->
	</tr>
<?php
	$ims1->MoveNext();	
	}
?>
</tbody>
</table>
<?php
}

function _shn_ims_alternate_item_db($parent_id,$catalog_id,$inv_id)
{
	global $global;
	$db=$global["db"];
	
	$alternate=$catalog_id;

	$sql1="INSERT INTO ims_alternate (catalog_id,inv_id,alternate) VALUES ('$parent_id','$inv_id','$alternate');";
	$ims1=$db->Execute($sql1);
	print $sql1;
}



//*******************************************************************************************************************//***********************************      Optimize Inventory ******************************************************
//******************************************************************************************************************

function _shn_ims_optim_inventory()
{
    global $global;
    $db=$global["db"];
    $form_opts['name']="optim_inventory";
    shn_form_fopen("prediction_inv",null,$form_opts);
    shn_form_fsopen("Inventory Selection");
    $inventory_array=array();
    $q0="SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0=$db->Execute($q0);
    
    while($ims0!=NULL && !$ims0->EOF)
    {
        
        $inventory_array[$ims0->fields['inv_uuid']]=$ims0->fields['inventory_name'];//}
        $ims0->MoveNext();
        
    }    
    
    shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
    shn_form_fsclose();
?>
<center>
<?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_("Daily Report"),"onClick='change_action_inventory(\"dailyreport\")'",$extra_opts);
    shn_form_button(_("Weekly Report"),"onClick='change_action_inventory(\"weeklyreport\")'",$extra_opts);
    shn_form_button(_("Monthly Report"),"onClick='change_action_inventory(\"monthlyreport\")'",$extra_opts);
    
    
    //shn_form_hidden(array('parent_id'=>$parent_id));
    
?>
</center>
<?php
shn_form_fsopen("Time Period to make Prediction");
	//shn_form_text();
	
	shn_form_text(_("Time Period : "),'time_amount','size="20"',array('help'=>_('Time period which you are going to make prediction')));
	$time_period_array=array();
	$time_period_array["day"]="day/days";
	$time_period_array["week"]="week";
	$time_period_array["month"]="month";
	shn_form_select($time_period_array,_("Time Period : "),'time_period','size="1"',null);
	shn_form_fsclose();
	shn_form_button(_("Customized Report"),"onClick='change_action_inventory(\"customizedreport\")'",$extra_opts);
	shn_form_hidden(array('action'=>'0'));
    //shn_form_submit("Predict");
	shn_form_fclose();
}

function _shn_ims_prediction_inv_actions()
{
	global $global;
	$db=$global["db"];
	
	$inv_id=trim($_POST['inv_id']);
	$time_amount=trim($_POST['time_amount']);
	$time=trim($_POST['time_period']);
	$action=trim($_POST['action']);

	if($action=="dailyreport")
	{
		$time_period=1;
		//_shn_ims_optim_inventory_db($inv_id,$time_period);
	}
	if($action=="weeklyreport")
	{
		$time_period=7;
	}
	if($action=="monthlyreport")
	{
		$time_period=30;
	}
	if($action=="customizedreports")
	{
		if($time=="day")
		{
			$time_period=$time_amount;
		}
		if($time=="week")
		{
			$time_period=$time_amount*7;
		}
		if($time=="month")
		{
			$time_period=$time_amount*30;
		}

	}

	_shn_ims_optim_inventory_db($inv_id,$time_period);
}

function _shn_ims_optim_inventory_db($inv_id,$time_period)
{
	global $global;
	$db=$global["db"];
	//$inv_id=$_POST['inv_id'];
	
	$form_opts['name']="optim_inventory_relation";

	$sql0="DELETE FROM ims_optimization;";
	$ims0=$db->Execute($sql0);

	$sql1="SELECT * FROM ims_item_records WHERE inv_id='$inv_id';";
	$ims1=$db->Execute($sql1);
	//$time_period=1;
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$catalog_id=$ims1->fields['catalog_id'];
		_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
		$ims1->MoveNext();	
	}
	
?>
	<h1 align="center"><?php print _("Forecasting by Inventory"); ?></h1>
<?php
	$current_date=date("Y-m-d");
	list($year,$month,$day) = split("-",$current_date);
	$date_after=_shn_ims_timeafter($year, $month, $day, $time_period);
	$string="Prediction Report Since ".$current_date." "."To"." ".$date_after;
?>
	
	<div><h3><b><em><?php print $string;?></em></b></h3></div>
	<div id="result">
<?php
	shn_form_fopen("optim_inventory_relation",null,$form_opts);
	//shn_form_fsopen();
?>
	<table>
	<thead>
	<td><?php print (_("Item name"));?></td>
	<td><?php print (_("Inventory"));?></td>
	<td><?php print (_("Forecasted Value"));?></td>
	<td><?php print (_("Unit"));?></td>
	<td><?php print (_("Actions"));?></td>
	</thead>
	<tbody>
<?php
	$sql2="SELECT * FROM ims_optimization GROUP BY catalog_id;";
	$ims2=$db->Execute($sql2);
	//print $sql2;
	while(!$ims2==NULL && !$ims2->EOF)
	{
		$catalog_id=$ims2->fields['catalog_id'];

		$sql3="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
		$ims3=$db->Execute($sql3);
		//while(!$ims3==NULL && !$ims3->EOF)
		//{
		$actual_value=$ims3->fields['actual_value'];
		$forecasted_value=$ims3->fields['forecasted_value'];
		$unit=$ims3->fields['unit'];
		$unit_name=get_unit_name($unit);

		$alpha=_shn_ims_smoothing_constant($catalog_id,$inv_id);

		$forecast=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);

		$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
		$ims4=$db->Execute($sql4);
		$item_name=$ims4->fields['item_name'];

		$sql5="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
		$ims5=$db->Execute($sql5);
		//print $sql4;
		$inventory_name=$ims5->fields['inventory_name'];
?>
	<tr>
	<td><?php print $item_name; ?></td>
	<td><?php print $inventory_name; ?></td>
	<td><?php print $forecast; ?></td>
	<td><?php print $unit_name;?></td>
	<td><a href="index.php?mod=ims&act=optim_relation_inventories&catalog_id=<?php echo $catalog_id;?>&inv_id=<?php echo $inv_id;?>&time_period=<?php echo $time_period;?>"><?php print ("Relative Items");?></a></td>
	</tr>
	
<?php
		//$ims3->MoveNext();
		//}
		$ims2->MoveNext();
	}
?>
	</tbody>
	</table>
	</div>
<?php

	//$sql6="SELECT * FROM ims_optimization WHERE ";
	//shn_form_button(_("View Charts"),"onClick='change_action(\"dailyreport\")'",$extra_opts);
	shn_form_fclose();
}

function _shn_ims_optim_relation_inventories($catalog_id,$inv_id,$time_period)
{
	global $global;
	$db=$global["db"];
	
	$sql="DELETE FROM ims_optimization;";
	$ims=$db->Execute($sql);

	$sql1="SELECT * FROM ims_relation WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims1=$db->Execute($sql1);
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$relation=$ims1->fields['relation'];
		_shn_ims_insert_data_to_predict($relation,$inv_id,$time_period);
		$ims1->MoveNext();
	}

	$sql2="SELECT * FROM ims_optimization GROUP BY catalog_id;";
	$ims2=$db->Execute($sql2);
	while(!$ims2==NULL && !$ims2->EOF)
	{
		$catalog_id=$ims2->fields['catalog_id'];
	
		$sql3="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
		$ims3=$db->Execute($sql3);
		$actual_value=$ims3->fields['actual_value'];
		$forecasted_value=$ims3->fields['forecasted_value'];
		$unit=$ims3->fields['unit'];

		$alpha=_shn_ims_smoothing_constant($catalog_id,$inv_id);
		$forecast=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);

		print $catalog_id;
?>
	<br>
<?php
		print $inv_id;
?>
	<br>
<?php
		print $forecast;
?>
	<br>
<?php
		print $unit;

		$ims2->MoveNext();
	}

	
}

//}
//******************************************************************************************************************
//*********************************      optimize item ************************************************************
//******************************************************************************************************************

function _shn_ims_optim_item_main_page()
{
?>

    <h1 align="center"><?php print _("Select Item to Predict");?><br></h1>
    <dev id="report">

    </dev>

<?php
    $form_opts['name']='subcat';
    shn_form_fopen("prediction_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    shn_form_fclose();
}

function _shn_ims_prediction_page()
{
$depth=get_max_depth();
    $parent_id = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
    for($i=1;$i<$depth;$i++)
    {
        $parent_id = trim($_POST[$i]);
    
        if($parent_id==null)
        {
            $parent_id = $_POST[$i-1];
            break;
        }
    }
?>
<h1 align="center"><?php print _("Item Prediction");?><br></h1>
    <dev id="report1">

    </dev>
<?php
	$form_opts['name']="optim_item";
	shn_form_fopen("prediction_report",null,$form_opts);
	shn_form_fsopen("Selected Item");
	shn_form_text(_("* Item : "),'item_name','size="50" readonly=true',array('value'=>$item_name,'req'=>true));
	shn_form_fsclose();
	//print $parent_id;
	shn_form_fsopen("Inventory Selection");
	global $global;
    $db=$global["db"];
    $inventory_array=array();
    $q0="SELECT inventory_name,inv_uuid FROM ims_inventory_records;";
    $ims0=$db->Execute($q0);
    //$inventory_array[$ims0->fields['inv_uuid']]=$ims0->fields['inventory_name'];
    //$q="SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
    //$ims=$db->Execute($q);
    //$j=0;
    while($ims0!=NULL && !$ims0->EOF)
    {
        
        $inventory_array[$ims0->fields['inv_uuid']]=$ims0->fields['inventory_name'];//}
        $ims0->MoveNext();
        //$j=$j+1;
        //print ($j);
    }    
    
    shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',array('req'=>true,'help'=>_('If this box does not contain prefered inventory name  please go through the Multiple Inventory Management Menu and add an Inventory first')));
	shn_form_fsclose();

	shn_form_fsopen("Time Period one to predict");
	//shn_form_text();
	
	shn_form_text(_("Time Period : "),'time_amount','size="20"',array('help'=>_('Time period which you are going to make prediction')));
	$time_period_array=array();
	$time_period_array["day"]="day/days";
	$time_period_array["week"]="week";
	$time_period_array["month"]="month";
	shn_form_select($time_period_array,_("Time Period : "),'time_period','size="1"',null);
	$extra_opts['br']=false;
    	$extra_opts['req']=false;
    	shn_form_button(_("Customized Report"),"onClick='change_action(\"customizedreport\")'",$extra_opts);
	shn_form_fsclose();
	
	
	$extra_opts['br']=false;
    	$extra_opts['req']=false;
?>
<center>
<?php
	//shn_form_hidden(array('parent_id'=>$parent_id));	
	shn_form_button(_("Daily Report"),"onClick='change_action(\"dailyreport\")'",$extra_opts);
	shn_form_button(_("Weekly Report"),"onClick='change_action(\"weeklyreport\")'",$extra_opts);
	shn_form_button(_("Monthly Report"),"onClick='change_action(\"monthlyreport\")'",$extra_opts);
	
?>
</center>
<?php
	shn_form_hidden(array('action'=>'0'));
	shn_form_hidden(array('parent_id'=>$parent_id));
	shn_form_fclose();


    //shn_form_fopen("view_edit_item_actions",null,$form_opts);
    //shn_form_fsopen("Add Item");
    
   // shn_form_button(_("Add Item"),"onClick='change_action(\"additem\")'",$extra_opts);
}

function _shn_ims_optim_item_actions()
{
    global $global;
    $db=$global["db"];

    $form_opts['name']="optim_item_actions";
    $q1="DELETE FROM ims_optimization;";
    $ims_q1=$db->Execute($q1);

    $action=trim($_POST['action']);

    if($action=='dailyreport')
    {
?>
	<h1 align="center"><?php print(_("Daily Report")); ?></h1>
        
<?php
	global $global;
	$db=$global["db"];

	$catalog_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	$time_period=1;
	
	_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);

	

	//print ("Mahesh");
	//_shn_ims_chart_test();
?>
	<!--<image src="tmp/Barchart.png"></image>-->
<?php

    }
    if($action=='weeklyreport')
    {
?>
	<h1 align="center"><?php print(_("Weekly Report")); ?></h1> 
<?php
	global $global;
	$db=$global["db"];

	$catalog_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	$time_period=7;
	
	_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
    if($action=='monthlyreport')
    {
?>
	<h1 align="center"><?php print(_("Monthly Report")); ?></h1>
<?php
	global $global;
	$db=$global["db"];

	$catalog_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	$time_period=30;
	
	_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }
    if($action=='customizedreport')
    {
?>
	<h1 align="center"><?php print(_("Customized Report")); ?></h1>
<?php
	global $global;
	$db=$global["db"];

	$catalog_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	$time_amount=trim($_POST['time_amount']);
	$time=trim($_POST['time_period']);
	if($time=="day")
	{
		$time_period=$time_amount;
	}
	if($time=="week")
	{
		$time_period=$time_amount*7;
	}
	if($time=="month")
	{
		$time_period=$time_amount*30;
	}
	
	
	_shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period);
    }

	$current_date=date("Y-m-d");
	list($year,$month,$day) = split("-",$current_date);
	$date_after=_shn_ims_timeafter($year, $month, $day, $time_period);
	$string="Prediction Report Since ".$current_date." "."To"." ".$date_after;
?>
	
	<div><h3><b><em><?php print $string;?></em></b></h3></div>
<?php
    
	shn_form_fopen("optimize_relation_items",null,$form_opts);
	shn_form_fsopen("Prediction Records");
	$sql1="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' ORDER BY week DESC;";
	$ims1=$db->Execute($sql1);
	$actual_value=$ims1->fields['actual_value'];
	$forecasted_value=$ims1->fields['forecasted_value'];
	$unit=$ims1->fields['unit'];

	$alpha=_shn_ims_smoothing_constant($catalog_id,$inv_id);

	$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);

	$sql2="SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
	$ims2=$db->Execute($sql2);
	$item_name=$ims2->fields['item_name'];

	$sql3="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims3=$db->Execute($sql3);
	$inventory_name=$ims3->fields['inventory_name'];

	$unit_name=get_unit_name($unit);

	$date=date("Y-m-d");

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
	//print ("Item Name    ");
	//print $item_name;
	shn_form_label(_("Item Name :"),$item_name,null);
?>
	<br>
<?php
	shn_form_label(_("Inventory Name :"),$inventory_name,null);
?>
	<br>
<?php
	shn_form_label(_("Forecasted Value :"),$forecasted_value,null);
?>
	<br>
<?php
	shn_form_label(_("Unit :"),$unit_name,null);
	
	shn_form_fsclose();
	$extra_opts['br']=false;
    	$extra_opts['req']=false;
	shn_form_button(_("Relative Items"),"onClick='change_action_relation(\"relation\")'",$extra_opts);
	shn_form_button(_("Re-Order level"),"onClick='change_action_relation(\"reorderlevel\")'",$extra_opts);
	//shn_form_button(_("Monthly Report"),"onClick='change_action(\"monthlyreport\")'",$extra_opts);

?>
</center>
<?php
	shn_form_hidden(array('action'=>'0'));
	shn_form_hidden(array('catalog_id'=>$catalog_id));
	shn_form_hidden(array('inv_id'=>$inv_id));
	shn_form_hidden(array('time_period'=>$time_period));
	shn_form_hidden(array('forecated_value'=>$forecasted_value));
?>
<?php

	$data = array();
	$temp = array();
	//push($inventory_array,$temp);

	$sql4="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims4=$db->Execute($sql4);
	//print $sql4;
	while(!$ims4==NULL && !$ims4->EOF)
	{
		$week_chart=$ims4->fields['week'];
		$actual_value_chart=$ims4->fields['actual_value'];
		$forecasted_value_chart=$ims4->fields['forecasted_value'];

		$alpha_temp=$week_chart+1;
		$alpha_chart=2/$alpha_temp;

		$forecast_chart=_shn_ims_smoothing($forecasted_value_chart,$actual_value_chart,$alpha_chart);

		$temp = array($week_chart,$actual_value_chart,$forecast_chart);
		array_push($data,$temp);

		//$inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];
		$ims4->MoveNext();
	}
	
	_shn_ims_bar_chart($data);
	_shn_ims_line_chart($data);
?>
	<image src="tmp/barChart.png"></image>
<br>
	<image src="tmp/lineChart.png"></image>
<?php
	shn_form_fclose();
}

function _shn_ims_optimize_relation_items()
{
	global $global;
	$db=$global["db"];
	
	$catalog_id=trim($_POST['catalog_id']);
	$action=trim($_POST['action']);
	$inv_id=trim($_POST['inv_id']);
	$time_period=trim($_POST['time_period']);
	$forecasted_value=trim($_POST['forecasted_value']);

	if($action=="relation")
	{

	$sql="DELETE FROM ims_optimization;";
	$ims=$db->Execute($sql);

	$sql1="SELECT * FROM ims_relation WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims1=$db->Execute($sql1);
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$relation=$ims1->fields['relation'];
		_shn_ims_insert_data_to_predict($relation,$inv_id,$time_period);
		$ims1->MoveNext();
	}

	$sql2="SELECT * FROM ims_optimization GROUP BY catalog_id;";
	$ims2=$db->Execute($sql2);
	while(!$ims2==NULL && !$ims2->EOF)
	{
		$catalog_id=$ims2->fields['catalog_id'];
	
		$sql3="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' ORDER BY week DESC;";
		$ims3=$db->Execute($sql3);
		$actual_value=$ims3->fields['actual_value'];
		$forecasted_value=$ims3->fields['forecasted_value'];
		$unit=$ims3->fields['unit'];

		$alpha=_shn_ims_smoothing_constant($catalog_id,$inv_id);

		$forecast=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);

		print $catalog_id;
?>
	<br>
<?php
		print $inv_id;
?>
	<br>
<?php
		print $forecast;
?>
	<br>
<?php
		print $unit;

		$ims2->MoveNext();
	}
	}

	if($action=="reorderlevel")
	{
?>
		<h1 align="center"><?php print(_("Re-Order Level")); ?></h1> 
<?php
//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************

	global $global;
    $db=$global["db"];
        //$item_search=$_POST['item_name_search'];
        //$category_search=$_POST['itemcat'];
        //print ($item_search);
    $sql1="SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims1=$db->Execute($sql1);
    
    $minimum_quantity=$ims1->fields['minimum_quantity'];
    $minimum_unit=$ims1->fields['unit'];
    $minimum_quantity=$minimum_quantity*convert_to_base_unit($minimum_unit);

    if($forecasted_value<$minimum_quantity)
    {
	print ("Hi");
    }

    

	//print ("Hi");
}
}

function _shn_ims_optim_item_db()
{
	global $global;
	$db=$global["db"];

	$catalog_id=$_POST['parent_id'];
	$inv_id=$_POST['inv_id'];
	//$current_date=date("Y-m-d");
	//$current_date_convert=_shn_ims_date_conversion($current_date);

	//global $global;
	//$db=$global["db"];
	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	//$date_inv_convert=_shn_ims_date_conversion($date_inv);
	$current_date=date("Y-m-d");

	$date_diff=_shn_ims_count_days($date_inv,$current_date);
	print $date_diff;
	//if($date_diff<8 && $date_diff>0)
	//{
	_shn_ims_insert_data_to_predict($catalog_id,$inv_id);
	_shn_ims_chart_test();

	print ("Mahesh");
?>
	<image src="tmp/Barchart.png"></image>
<?php

			
}

?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_item.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_inventory(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_inventory.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_relation(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.optim_item_actions.submit();
         return;
    }
</script>
<?php

?>
