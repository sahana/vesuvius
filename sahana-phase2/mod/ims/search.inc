<?php
/** search form for the Inventory Management system 
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
include_once $global['approot']."/inc/lib_errors.inc";

include_once $global['approot'].'/mod/or/lib_or.inc';
//include_once ('view_inv.inc');
/**
** Function for searching items
**/



function _shn_ims_search_item()
{
    
?>

<h1 align="center"><?php print _("Search an inventory item"); ?></h1>
<div id="search">

</div>

<?php
    $form_opts['name']='subcat';
    shn_form_fopen("search_item_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat',null);


    shn_form_fclose();
}

function _shn_ims_search_item_page()
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
    //print ("test");    
    //echo $parent_id;
?>

<h1 align="center"><?php print _("Search an inventory item"); ?></h1>
<div id="search">

<?php
    $extra_opts['req']=true;

    shn_form_fopen("search_item_db");
    shn_form_fsopen(_('Search items '));
    shn_form_text(_("Search by Item name   : "),'item_name','size="50" readonly=true',$extra_opts);

    $item_state_array=array();
    $item_state_array["available"]=_("Item available");
    $item_state_array["expired"]=_("Item to be destroyed");
    $item_state_array["destroyed"]=_("Item already destroyed");
    shn_form_select($item_state_array,_("  State  : "),'item_state','size="1"',$extra_opts);


    global $global;
    $db=$global["db"];
    $inventory_array=array();
    $inv_id=0;
    $inventory_name="All Inventories";
    $inventory_array[$inv_id]=$inventory_name;
    //$inventory_array['0']="None";
    $q="SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
    $ims=$db->Execute($q);
    //$j=0;
    while($ims!=NULL && !$ims->EOF)
    {
        
        $inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];
        $ims->MoveNext();
        //$j=$j+1;
        //print ($j);
    }    
    
    shn_form_select($inventory_array,_("Inventory : "),'inventory','size="1"',$extra_opts);
    

    shn_form_fsclose();

    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_submit(_("Submit"));
    
    
    
    

    //shn_form_fsopen();    
    //$extra_opts['req']=false;
?>

        
</div>
    
<?php
    //shn_form_fsclose();
    shn_form_fclose();
}

function _shn_ims_search_item_db()
{
?>
        <h1 align="center"><?php print _("Search Results"); ?></h1>
<?php
	$catalog_id=trim($_POST['parent_id']);
	//print $catalog_id;

        $item_name=$_POST['item_name'];
        $item_state=$_POST['item_state'];
        $inv_id=$_POST['inventory'];
        
        global $global;
        $db=$global["db"];

	//print ($item_search);
	if($inv_id==0)
	{
		$sql="SELECT item_id,suplier_id,unit,state,amount,inv_id FROM ims_item_records WHERE item_name='$item_name' AND state='$item_state';";
	}
	else
	{
        
        	$sql = "SELECT item_id,suplier_id,unit,state,amount,inv_id FROM ims_item_records WHERE item_name='$item_name' AND state='$item_state' AND inv_id='$inv_id';";
	}
        $ims = $db->Execute($sql);
        //print $sql;
?>

        <div id ="result">
    <table>
        <thead>
        <td><?=_("Item Name")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit") ?></td>
        <td><?=_("Inventory") ?></td>
        <td><?=_("State") ?></td>
        <td><?=_("Suplier") ?></td> 
        
            
            
        </thead>
    <tbody>
    
<?php
        //$sum_amount=0;
        $suplier_name_array=array();

        while (!$ims==NULL && !$ims->EOF)
        {
            $item_id=$ims->fields["item_id"];
            $suplier_id=$ims->fields["suplier_id"];
            $suplier_name_array=_shn_or_get_suplier_name($suplier_id);
            $suplier_name=$suplier_name_array[$suplier_id];

	    $inventory_id=$ims->fields['inv_id'];
            
            //print $suplier_name;
            //print $suplier_id;
            //print $suplier_name;
            //$inv_id=$ims->fields['inv_id'];
            //$item_name=$ims->fields["item_name"];
            //$sum_amount=$ims->fields["SUM(amount)"];
            $amount=$ims->fields["amount"];
            
            
            $unit=$ims->fields["unit"];
            $base_unit=convert_to_base_unit($unit);
            
            $converted_amount=$amount*unit_converter($base_unit,$unit);
            //print $converted_amount;
            $sum_amount=$sum_amount + $converted_amount;
            //print $sum_amount;
            $unit_name=get_unit_name($unit);
            $base_unit_name=get_unit_name($base_unit);
            $state=$ims->fields['state'];
            //$manufactured_date=$ims->fields["manufactured_date"];
            //$expire_date=$ims->fields["expire_date"];
	/*if($inv_id==0)
	{
		$query="SELECT inv_id FROM ims_item_records WHERE item_id='$item_id';";
		$ims_query=$db->Execute($query);
		$inventory_id=$ims_query->fields['inv_id'];
		
	}*/
	
		$sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inventory_id';";
        	$ims2=$db->Execute($sql2);
               	$inventory_name=$ims2->fields['inventory_name'];
	

        
            

?>
    
    <tr>
    
    <td><?php print ($item_name); ?></td>
    <td><?php print ($amount); ?></td>
    <td><?php print ($unit_name); ?></td>
    <td><?php print ($inventory_name); ?></td>
    <td><?php print ($state); ?></td>
    <td><?php print ($suplier_name); ?></td> 
        
    </tr>

<?php
    $ims->MoveNext();
            
        }
?>
    </tbody>
    </table>

    </div>
<div id="result">
<h3 align="center"><?php print _("Total Amount");
            print "\n";
            print $sum_amount;
            print "\n";
            print $base_unit_name;?> </h3>
</div>
<?php
	//if($inv_id!=0)
	//{
?>
	<div><h3><b><em><?= (_("Alternate Items:")) ?></em></b></h3></div>
	<div id="result">
	<table>
	<thead>
	<td><?=_("Item Name")?></td>
        <td><?=_("Amount")?></td>
        <td><?=_("Unit") ?></td>
        <td><?=_("Inventory") ?></td>
        <td><?=_("State") ?></td>
        <td><?=_("Suplier") ?></td> 
	</thead>
	<tbody>
<?php
	//$alternate_sum_amount=0;
	//print $inv_id;
	if($inv_id==0)
	{
		$inv_id='all';
	}
	else
	{
		;
	}
	$sql3="SELECT * FROM ims_alternate WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims3=$db->Execute($sql3);
	//print $sql3;
	while(!$ims3==NULL && !$ims3->EOF)
	{
		$alternate=$ims3->fields['alternate'];
		
		if($inv_id=='all')
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND state='$item_state';";
		}
		else
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND inv_id='$inv_id' AND state='$item_state';";
		}
		$ims4=$db->Execute($sql4);
		//print $sql4;
		while(!$ims4==NULL && !$ims4->EOF)
		{
			 $item_id=$ims4->fields["item_id"];
            $suplier_id=$ims4->fields["suplier_id"];
            $suplier_name_array=_shn_or_get_suplier_name($suplier_id);
            $suplier_name=$suplier_name_array[$suplier_id];
	    $item_name=$ims4->fields['item_name'];

	    $inventory_id=$ims4->fields['inv_id'];
            
            
            $amount=$ims4->fields["amount"];
            
            
            $unit=$ims4->fields["unit"];
            $base_unit=convert_to_base_unit($unit);
            
            $converted_amount=$amount*unit_converter($base_unit,$unit);
            //print $converted_amount;
            $sum_amount=$sum_amount + $converted_amount;
	    $alternate_sum_amount=$alternate_sum_amount + $converted_amount;
            //print $sum_amount;
            $unit_name=get_unit_name($unit);
            $base_unit_name=get_unit_name($base_unit);
            $state=$ims->fields['state'];
            //$manufactured_date=$ims->fields["manufactured_date"];
            //$expire_date=$ims->fields["expire_date"];
	/*if($inv_id==0)
	{
		$query="SELECT inv_id FROM ims_item_records WHERE item_id='$item_id';";
		$ims_query=$db->Execute($query);
		$inventory_id=$ims_query->fields['inv_id'];
		
	}*/
	
		$sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inventory_id';";
        	$ims5=$db->Execute($sql5);
               	$inventory_name=$ims5->fields['inventory_name'];

		
	

        
            

?>
    
    <tr>
    
    <td><?php print ($item_name); ?></td>
    <td><?php print ($amount); ?></td>
    <td><?php print ($unit_name); ?></td>
    <td><?php print ($inventory_name); ?></td>
    <td><?php print ($item_state); ?></td>
    <td><?php print ($suplier_name); ?></td> 
        
    </tr>

<?php
    $ims4->MoveNext();
			
			
		}

		
		$ims3->MoveNext();
	}
?>
	</tbody>
	</table>
	</div>
	<div id="result">
<h3 align="center"><?php print _("Total Alternate Items Amount");
            print "\n";
            print $alternate_sum_amount;
            print "\n";
            print $base_unit_name;?> </h3>
</div>
	<div id="result">
<h3 align="center"><?php print _("Total Amount");
            print "\n";
            print $sum_amount;
            print "\n";
            print $base_unit_name;?> </h3>
</div>
<?php
	//}
}
/**
** Function for searching inventories
**/

function _shn_ims_form_search()
{
    global $global;
    $db=$global['db'];

    //global $global;
    $module = $global['module'];
?>
<h2 align="center"><?= _("Search for Inventories by name and by Location")?></h2>
    <div id="formcontainer">
<?php
    $form_opts['name']="search_inventory";
    shn_form_fopen('search_inventory_db',null,$form_opts);
    shn_form_fsopen('Inventiry Name');
    shn_form_text(_("Search by Inventory name   : "),'inventory_name','size="50"',array('help'=>_("Enter either the name of the inventory or the location of the inventory or both Inventory name and location and click on the search button below")));
    shn_form_fsclose();
    $range=array("start"=>1,"end"=>5);
    //shn_location_form_org(1,5);
    shn_form_fsopen(_("Search by Location"));
    shn_location($range,$value=null,$parent=null,$extra_opts=null);
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    //shn_form_submit('Search');
    shn_form_button(_("Search"),"onClick='change_action(\"search_name\")'",$extra_opts);
?>
<br>
<br>
<?php
    shn_form_fsopen("Search by Inventory Owner's Details");
    shn_form_textarea(_("Any of the Details of Inventory Owner : "),'address','size="20"',array('req'=>true,'help'=>_("Enter any of the details of the Inventory Owner and click on the Search button below. Name of the Inventory Owner, Address of the Inventory Owner, Contact Numbers of the Inventory Owner, e-mail address of the Inventory Owner or web site of the inventory are accepted to the search")));
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_("Search"),"onClick='change_action(\"search_address\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    //shn_form_button("Search")
    shn_form_fclose();

}

function _shn_ims_search_inventory_db()
{
    global $global;
    $db=$global['db'];

    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];

    $bsd_village=_shn_ims_get_locid();
    //print $bsd_village;

   // print $bsd_village;

    $loc=array();
    $loc=_shn_ims_get_parent_locations($bsd_village);
    //print(count($loc));

    $name_temp=trim($_POST['inventory_name']);
    $name=soundex($name_temp);

?>
<div id='result'>
    <table>
    <thead>
    <td><?=_("Inventory Name")?></td>
    <td><?=_("Country of Origin/GIS")?></td> 
    <td><?=_("Address")?></td>
    <td><?=_("Contact Numbers")?></td>
    <td><?=_("Man Power")?></td>
    <td><?=_("Equipment")?></td>
    <td><?=_("Other <br /> Facilities")?></td>
    <td><?=_("Inventory Space")?></td>
    </thead>
    <tbody>

<?php

    if($name_temp!=NULL && $bsd_village==0)
    {
	$sql="SELECT * FROM ims_inventory_records;";
        $ims=$db->Execute($sql);
	$temp_flag=-1;
    }
    if($name_temp==NULL && $bsd_village!=NULL)
    {
	//print ("Hello");
	$sql="SELECT * FROM location_details;";
        $ims=$db->Execute($sql);
	$temp_flag=0;
    }
    if($name_temp!=NULL && !$bsd_village==0)
    {
	$sql="SELECT * FROM ims_inventory_records;";
        $ims=$db->Execute($sql);
	$temp_flag=1;
    }

    include_once ('view_inv.inc');
    while(!$ims==NULL && !$ims->EOF)
    {
	//print $temp_flag;
	if($temp_flag==-1)
	{
	
	 $inventory_name=$ims->fields['inventory_name'];
	 $inventory_name=soundex($inventory_name);   
	if($inventory_name==$name)
	{
	    $inv_uuid=$ims->fields['inv_uuid'];
	    if($inv_uuid!=NULL)
	    {
	        _shn_display_org($flag=false,$inv_uuid);
	    }	 
	    
	}
	
	}
	if($temp_flag==0)
	{
	    
	    $location_id=$ims->fields['location_id'];
//print $location_id;

	    for($i=0;$i<count($loc);$i++)
	    {
		$temp=$loc[$i];
		//print($temp.'='.$location_id."\n");
		if($temp==$location_id)
		{
		    $poc_uuid=$ims->fields['poc_uuid'];
		    _shn_display_org($flag=false,$poc_uuid);
		    //print $poc_uuid;
		    break;
		}
		
		
	    }
		
		//print $ims1;
	}

	if($temp_flag==1)
	{
	    $inventory_name=$ims->fields['inventory_name'];
	    $inventory_name=soundex($inventory_name);
	    if($inventory_name==$name)
	    {
		$inv_uuid=$ims->fields['inv_uuid'];
		
		$sql1="SELECT * FROM location_details WHERE poc_uuid='$inv_uuid';";
		$ims1=$db->Execute($sql1);
		$location_id=$ims1->fields['location_id'];

	    for($i=0;$i<count($loc);$i++)
	    {
		$temp=$loc[$i];
		//print($temp.'='.$location_id."\n");
		if($temp==$location_id)
		{
		    //$poc_uuid=$ims->fields['poc_uuid'];
		    _shn_display_org($flag=false,$inv_uuid);
		    //print $poc_uuid;
		    break;
		}
		
	    }
	    
		
	    }		
	}
	
	   // $sql1="SELECT * FROM ";
	//}
	$ims->MoveNext();
    }
?>
    </tbody>
    </table>
</div>
<?php
    
}

function _shn_ims_validate_search_inventories()
{
    $error_flag=false;

    $action=$_POST['action'];
    if($action=='search_name')
    {
    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];

    $bsd_village=_shn_ims_get_locid();
    $name=trim($_POST['inventory_name']);
    //print $name;
    //print $bsd_village;
    //if ($name==null)
    //{
	if($bsd_village=='0' && $name==null)
	{
	    $error_flag=true;
	}
    }
    if($action=='search_address')
    {
	$address=trim($_POST['address']);
	if($address==null)
	{
	    $error_flag=true;
	}
    }
    //}
    //print $error_flag;
    return $error_flag;
    
	
}

function _shn_ims_search_address()
{
    global $global;
    $db=$global['db'];
    $address=trim($_POST['address']);

?>
<div id='result'>
    <table>
    <thead>
    <td><?=_("Inventory Name")?></td>
    <td><?=_("Country of Origin/GIS")?></td> 
    <td><?=_("Address")?></td>
    <td><?=_("Contact Numbers")?></td>
    <td><?=_("Man Power")?></td>
    <td><?=_("Equipment")?></td>
    <td><?=_("Other <br /> Facilities")?></td>
    <td><?=_("Inventory Space")?></td>
    </thead>
    <tbody>

<?php
    include_once ('view_inv.inc');

    $sql="SELECT * FROM ims_inventory_records;";
    $ims=$db->Execute($sql);
    while(!$ims==NULL && !$ims->EOF)
    {
	$inv_uuid=$ims->fields['inv_uuid'];

        $q = "select * from location_details where address like '%{$address}%' AND poc_uuid='{$inv_uuid}' order by address";	
	//$q = "select * from location_details where (address like '%{$address}%' AND poc_uuid='{$inv_uuid}') OR ";
        $ims1 =$db->Execute($q);
	$poc_uuid=$ims1->fields['poc_uuid'];
	//print $poc_uuid;
	$org_id=$poc_uuid;
	//print $ims1;
	if($org_id==NULL)
	{
		$q="SELECT * FROM contact WHERE contact_value LIKE '%{$address}%' AND pgoc_uuid='{$inv_uuid}' ORDER BY contact_value;";
		$ims1=$db->Execute($q);
		$poc_uuid=$ims1->fields['pgoc_uuid'];
		$org_id=$poc_uuid;
	}
	//print $q;
	

	 _shn_display_org($flag=false,$org_id);
	
        $ims->MoveNext();
    }
?>
    </tbody>
    </table>
<?php
    
}

function _shn_ims_form_search_old()
{
    global $global;
    global $conf;
    $db=$global["db"];
?>
<h2><?= _("Search for Inventories by Location")?></h2>
    <div id="formcontainer">
<?php
    shn_form_fopen("search_cr");
    _shn_ims_update_loc();
    shn_form_fsopen(_("Selected Location"));
    $extra_options['value']="All Locations";
    shn_form_text(_("location"),'loc',NULL,$extra_options);
    shn_form_label(_("Select location and then select the level(province,district,etc)"),NULL);
    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();
 // base location
    
//-------------------------------------------
$range=array("start"=>1,"end"=>3);
     shn_form_fsopen("Base Location");
     shn_location($range,$_POST[$range["end"]],null,true); 
    shn_form_fsclose();

/*shn_form_fsopen(" Location");
       $parent=_shn_ims_get_start_loc();
       $range= shn_ims_get_loc_range();
      shn_location($range,null,$parent); 
    shn_form_fsclose();*/
//-------------------------------------------


    

    ?><fieldset><?
    shn_form_opt_select('opt_location_type','Location Level',$select_opts,null,null);
    ?></fieldset><?
?>
</br>
    <center>
<?php
//create the submit button
    shn_form_submit(_("Search"));
?>
</center>
    </br>
<?php
        //close the form
    shn_form_fclose();
?>                     
</div>
<?php
}

function _shn_ims_update_loc(){
?>
<script type="text/javascript">
    function update_loc(action,desc){
        var x=document.getElementsByName(action);
        var loc_val=x[0].options[x[0].selectedIndex].value;
        var loc_desc=x[0].options[x[0].selectedIndex].text;
        var x=document.getElementsByName('loc_sel');
        x[0].value=loc_val;
        loc_desc=desc+"->"+loc_desc;
        var x=document.getElementsByName('loc');
        x[0].value=loc_desc;
        return;
    }
</script>


<?php
}
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.search_inventory.submit();
         return;
    }
</script>