<?php
/**
* Sahana Inventory Management System Item transfer page
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
global $global;
include_once $global['approot'].'/mod/cs/lib_cs.inc';
include_once $global['approot']."/inc/lib_errors.inc";
include_once ("errors.inc");
include_once ('lib_ims.inc');

function _shn_ims_send_main()
{
?>
    <h1 align="center"><?php print _t("Send Items between Inventories"); ?> </h1>
    <h1 align="center"><?php print _t("Please select the Item to be sent"); ?></h1>
    <div id="result">
<?php
    $form_opts['name']='subcat';
    shn_form_fopen("send_item_page",null,$form_opts);
    $depth=get_max_depth();
    shn_sub_cat($depth,'subcat',null);
    //shn_sub_cat(6,'subcat');


    shn_form_fclose();
}

/**
**Function For Send Item table view page
**/
function _shn_ims_send_item_table_view_t($catalog_id,$Limit,$page_number)
{
    
    $depth=get_max_depth();

    if($catalog_id==NULL)
    {
        $parent_id = trim($_POST['0']);
        for($i=1;$i<$depth;$i++)
        {
            $parent_id = trim($_POST[$i]);
    
            if($parent_id==null)
            {
                $parent_id = $_POST[$i-1];
                break;
            }
        }
    }
    else
    {
        $parent_id=$catalog_id;
    }
    
    $_SESSION['catalog_id']=$parent_id;
   
    if($page_number!=0)
    {
	$page_temp=$page_number;
	$page_number=($page_number-1)*$Limit;
    }
    else 
    {
	$page_number=0;
	$page_temp=1;
    }
    print '<b>';
    print (_t('Page Number : ').$page_temp);
    print '</b>';
?>
    <h1 align="center"><?php print _t("Send Item between Inventories") ?></h1>
<?php
    global $global;
        $state_des="destroyed";
        $db=$global["db"];
    $form_opts['name']='send_item_table_form';
    shn_form_fopen('send_item_paging',null,$form_opts);
   // shn_form_hidden(array('catalog_id'=>$parent_id));
     print '<b>';
    shn_form_text(_t("Records Per Page : "),'records','onChange="submit(this);"',array('value'=>$Limit));
     print '</b>';
    shn_form_fclose();
    $sql = "SELECT item_id,inv_id,item_name,amount,unit,manufactured_date,expire_date,state FROM ims_item_records WHERE catalog_id='$parent_id' AND amount!=0 AND state!='$state_des';";

    $SearchResult=mysql_query($sql) or die(mysql_error()); 
	$NumberOfResults=mysql_num_rows($SearchResult); 
	
	$NumberOfPages=ceil($NumberOfResults/$Limit); 
	 print '<b>';
	print(_t("Go to Page : "));
	
	for($i=1;$i<$NumberOfPages+1;$i++)
	{
		
	    ?><a href="index.php?mod=ims&act=send_item_paging&$i=<?php echo $i;?>&$Limit=<?php echo $Limit;?>"><?php print ($i." ");?></a><?php
	    print "\n";
	}
	 print '</b>';
?>
    <div id="result">
    <table>
    <thead>
            <td><?=_t("Item")?></td>
            <td><?=_t("Amount");?></td>
            <td><?=_t("Unit");?></td>
            <td><?=_t("Manufactured Date")?></td>
                <td><?=_t("Expire Date")?></td>
            <td><?=_t("Available Inventory")?></td>
                <td><?=_t("state")?></td>
        <td><?=_t("Action")?></td>
        </thead>
    <tbody>
<?php
        
                
        $sql1 = "SELECT item_id,inv_id,item_name,amount,unit,manufactured_date,expire_date,state FROM ims_item_records WHERE catalog_id='$parent_id' AND amount!=0 AND state!='$state_des' LIMIT $page_number,$Limit;";

        
        $ims1 = $db->Execute($sql1);

        while (!$ims1==NULL && !$ims1->EOF)
        {
            $item_id=$ims1->fields["item_id"];
            $inv_id=$ims1->fields["inv_id"];
            $item_name=$ims1->fields["item_name"];
            $amount=$ims1->fields["amount"];
            $unit=$ims1->fields["unit"];
            $manufactured_date=$ims1->fields["manufactured_date"];
            $expire_date=$ims1->fields["expire_date"];
            $state=$ims1->fields["state"];

            $unit_name=get_unit_name($unit);
            
            
        
        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims2= $db->Execute($sql2);
       
        $inventory_name = $ims2->fields["inventory_name"];            

?>
        <tr>
        <td><?php print ($item_name);?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date);?></td>
        <td><?php print ($inventory_name);?></td>
        <td><?php print ($state); ?></td>
        <td><a href="index.php?mod=ims&act=send_item_data_collectpage&item_id=<?php echo $item_id;?>&parent_id=<?php echo $parent_id; ?>&unit_id=<?php echo $unit;?>"><?php print ("Send");?></a></td>        
        </tr>

<?php
        $ims1->MoveNext();
        //$ims2->MoveNext();
        }
?>
            
    </tbody>
    </table>
</div>

    <div><b><em><h3><?php print("Alternate Items Table");?></h3></em></b></div>
    
    <div id="result">
    <table>
    <thead>
            <td><?=_t("Item")?></td>
	    <td><?=_t("Amount");?></td>
            <td><?=_t("Unit");?></td>
            <td><?=_t("Manufactured Date")?></td>
                <td><?=_t("Expire Date")?></td>
            <td><?=_t("Available Inventory")?></td>
                <td><?=_t("state")?></td>
        <td><?=_t("Action")?></td>
        </thead>
    <tbody>
<?php
	$sql3="SELECT * FROM ims_alternate WHERE catalog_id='$parent_id';";
	$ims3=$db->Execute($sql3);
	while(!$ims3==NULL && !$ims3->EOF)
	{
		$inv_alternate=$ims3->fields['inv_id'];
		$alternate=$ims3->fields['alternate'];

		if($inv_alternate==0)
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND state!='$state_des' LIMIT $page_number,$Limit;";
		}
		else
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND inv_id='$inv_alternate' AND state!='$state_des' LIMIT $page_number,$Limit;";
		}
		$ims4=$db->Execute($sql4);
		
		while(!$ims4==NULL && !$ims4->EOF)
		{
			$item_id=$ims4->fields["item_id"];
            		$inv_id=$ims4->fields["inv_id"];
            		$item_name=$ims4->fields["item_name"];
            		$amount=$ims4->fields["amount"];
            		$unit=$ims4->fields["unit"];
            		$manufactured_date=$ims4->fields["manufactured_date"];
            		$expire_date=$ims4->fields["expire_date"];
            		$state=$ims4->fields["state"];

            		$unit_name=get_unit_name($unit);
            
            
        
        $sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims5= $db->Execute($sql5);
       
        $inventory_name = $ims5->fields["inventory_name"];            

?>
        <tr>
        <td><?php print ($item_name);?></td>
        <td><?php print ($amount); ?></td>
        <td><?php print ($unit_name); ?></td>
        <td><?php print ($manufactured_date); ?></td>
        <td><?php print ($expire_date);?></td>
        <td><?php print ($inventory_name);?></td>
        <td><?php print ($state); ?></td>
        <td><a href="index.php?mod=ims&act=send_item_data_collectpage&item_id=<?php echo $item_id;?>&parent_id=<?php echo $parent_id; ?>&unit_id=<?php echo $unit;?>"><?php print ("Send");?></a></td>        
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
<?php    

}

function _shn_ims_send($item_id,$parent_id,$unit_id_send)
{
    
    global $global;
    $db=$global["db"];
    $sql1="SELECT item_name,inv_id,suplier_id,amount,unit,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims1=$db->Execute($sql1);
    $item_name=$ims1->fields['item_name'];
    $inv_id_from=$ims1->fields['inv_id'];
    $suplier_id=$ims1->fields['suplier_id'];
    $amount=$ims1->fields['amount'];
    $unit=$ims1->fields['unit'];
    $cost_per_unit=$ims1->fields['cost_per_unit'];

    $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
    $ims2=$db->Execute($sql2);
    $inv_from=$ims2->fields['inventory_name'];
    
        
?>
<h1 align="center"><?php print _t("Send Item between Inventories")?> </h1>
<div id="result2">
<?php
    $form_opts['name']='send_item_page';
    shn_form_fopen("send_item_db",null,$form_opts);
    //$extra_opts['req']=true;
    shn_form_fsopen("Item Transfer");
    
    $extra_opts['value']=$item_name;
    shn_form_text(_t("Item Send : "),'item_name','size="50" readonly=true',$extra_opts);
    //$extra_opts['req']=true;
    shn_form_text(_t("Amount Send: "),'amount','size="50"',array('req'=>true,'value'=>$amount));

//-------------------------------------------------------------------------------------------------------------

    $cq="SELECT name FROM ct_unit WHERE unit_uuid='$unit_id_send';";
    $cms=$db->Execute($cq);
    
    $unit_select_array[$unit_id_send]=$cms->fields['name'];
    
    $query="select * from ct_cat_unit where ct_uuid='$parent_id'";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {



    $temp2=$res->fields['unit_uuid'];
    $query1="select name from ct_unit where unit_uuid ='$temp2'";
    $res2=$db->Execute($query1);
    
    $unit_select_array[$res->fields['unit_uuid']]=$res2->fields['name'];
    $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_t("Unit : "),'unit_select','size="1"',array('req'=>true,'help'=>_t('Select the Measurement unit for entered amount. If this box does not contain the desired measurement unit please go back to the catalogue system and add')));
    

//-------------------------------------------------------------------------------------------------------------    

    
    
    $extra_opts['value']=$inv_from;
    $extra_opts = false;
    shn_form_text(_t("Inventory From : "),'inv_from','size="50" readonly=true',$extra_opts);

//******************
    echo "<br />";
    $destination_array=array('inventory'=>'Inventory','shelter'=>'Shelter','organization'=>'Organization','victim'=>'Victim');
    shn_form_radio($destination_array,_t('Destination : '),'destination','onClick="change_action_des(this.value)"',$extra_opts);
  
    $opt = _shn_admin_set_option_javascript();
    
    echo "<br />";
	

//************ Destination Inventory Display *********************
	
	echo "<div class='hide' id='des_inventory'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
    	//$extra_opts['value'] = $_POST['staff_oper'];
	 $inventory_array=array();
    $sql3="SELECT inv_uuid,inventory_name FROM ims_inventory_records WHERE inv_uuid!='$inv_id_from';";
    $ims3=$db->Execute($sql3);
    $inventory_array['']='';
    while($ims3!=NULL && !$ims3->EOF)
    {
        $inventory_array[$ims3->fields['inv_uuid']]=$ims3->fields['inventory_name'];
        $ims3->MoveNext();
    }
    shn_form_select($inventory_array,_t("Destination Inventory : "),'inv_to','size="1"',array('req'=>true,'help'=>_t('Select the Inventory which items to be sent')));
    $destination_type='inventory';
    	//$option_type=array('availability'=>'Availability','confirmation'=>'Confirmation');
    	//shn_form_radio($option_type,_t('Status : '),'file_type',$select_opts,$extra_opts);
    	echo "<br />";
	echo "</div>";
//********************* Destination Inventory display End ***********
//********************* Destination Shelter Display Begin ***********

	echo "<div class='hide' id='des_shelter'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
    	
    shn_form_select(_shn_ims_get_shelter_name(),_t("Destination Shelter : "),'shelter_to','size="1"',array('req'=>true,'help'=>_t('Select the Inventory which items to be sent')));
    $destination_type='shelter';
    	//$option_type=array('availability'=>'Availability','confirmation'=>'Confirmation');
    	//shn_form_radio($option_type,_t('Status : '),'file_type',$select_opts,$extra_opts);
    	echo "<br />";
	echo "</div>";
//********************* Destination Shelter display End *************
//********************* Destination Organization Display Begin ******

	echo "<div class='hide' id='des_organization'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
    	
    shn_form_select(_shn_ims_get_organization_name(),_t("Destination Organization : "),'organization_to','size="1"',array('req'=>true,'help'=>_t('Select the Inventory which items to be sent')));
    
    	echo "<br />";
	echo "</div>";

//********************* Destination Organization Display End ********
//********************* Destination Victim display Begin ************

	echo "<div class='hide' id='des_victim'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
	$form_opts['name']="victim_item";
        shn_form_fopen("victim_item_send",null,$form_opts);
    	shn_form_text(_t("Search by Name/Card Number :"),'head_name','size="50"',array('help'=>_t('Search the Victims by their names or their Identity card Number')));
	shn_form_button(_t("Search & Add"),"onClick='add_evacuees()'");
	shn_form_fclose();
	

	shn_form_select(array(),_t("Victim : "),'victim_to','size="1"',array('req'=>true));
    	echo "<br />";
	echo "</div>";

//********************* Destination Victim display End **************

   

    $date=date("Y-m-d");

    shn_form_date(_t("Date : "),'date',array('value'=>$date,'req'=>true,'help'=>_t('Year-Month-Date. Only - separator is accepted')));
    //shn_form_text(_t("Date : "),'date','size="50"',array('value'=>$date,'req'=>true,'help'=>_t('Year-Month-Date. Only - seperater is accepted')));
	
    //shn_form_text(_t("Date (YYYY-mm-dd): "),'date','size="50"',array('value'=>$date,."hello"'req'=>true,'help'=>_t('Year-Month-Date. Only - seperater is accepted')));
    $extra_opts['value']=$cost_per_unit;
    shn_form_text(_t("Cost Per Unit : "),'cost_per_unit','size="50"',$extra_opts);

    shn_form_fsclose();

    shn_form_fsopen("Contacts");
    shn_form_text(_t("Authorized by : "),'authorized_person','size="50"',array('req'=>true,'help'=>_t('Person who is sending Item')));
    shn_form_text(_t("Requested by : "),'requested_person','size="50"',array('req'=>true));
    shn_form_text(_t("Destribution Method : "),'destribution','size="50"',null);
    shn_form_textarea(_t("Cause : "),'cause','size="40"',null);
    
    shn_form_fsclose();

    shn_form_fsopen(_t("Transport/Transporter Details"));
    shn_form_text(_t("Vehicle Number : "),'vehicle_number','size="50"',array('help'=>_t('Registered Number of Your ')));
    shn_form_text(_t("Driver Name : "),'driver_name','size="50"',array('help'=>_t('Name of the Driver who is going to carry the vehicle')));
    shn_form_text(_t("Driver Mobile : "),'driver_mobile','size="50"',array('help'=>_t('Contact Details of the Driver')));
    shn_form_text(_t("Driver Address : "),'driver_address','size="50"',array('help'=>_t('Contact Details of the Driver')));
    shn_form_text(_t("Driving Licence Number : "),'driving_licence','size="50"',array('help'=>_t('Driving Licence Number')));
    shn_form_fsclose();

    shn_form_hidden(array('item_id'=>$item_id));
    shn_form_hidden(array('inv_id_from'=>$inv_id_from));
    shn_form_hidden(array('parent_id'=>$parent_id));
    shn_form_hidden(array('suplier_id'=>$suplier_id));
    shn_form_hidden(array('destination_type'=>$destination_type));
    shn_form_submit(_t("Send"));
    shn_form_fclose();
}


function _shn_ims_send_db()
{
    $item_id = trim($_POST['item_id']);
    $inv_id_from = trim($_POST['inv_id_from']);
    $suplier_id = trim($_POST['suplier_id']);
    $amount = trim($_POST['amount']);
    $unit = trim($_POST['unit_select']);
    $parent_id=trim($_POST['parent_id']);
    $person_send = trim($_POST['authorized_person']);
    $date_send = trim($_POST['date']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    
    //$inv_from = $_POST['inv_from'];
    $inv_from = trim($_POST['inv_from']);
    $inv_to = trim($_POST['inv_to']);
    $organization_to = trim($_POST['organization_to']);
    $shelter_to = trim($_POST['shelter_to']);
    $victim_to = trim($_POST['victim_to']);
    
	
    if($inv_to!='')
    {
	$destination_type='inventory';
    }
    if($organization_to!='')
    {
	$inv_to=$organization_to;
	$destination_type='organization';
    }
    if($shelter_to!='')
    {
	$inv_to=$shelter_to;
	$destination_type='shelter';
    }
    if($victim_to!='')
    {
	$inv_to=$victim_to;
	$destination_type='victim';
    }
    
    $authorized_person=trim($_POST['authorized_person']);
    $requested_person=trim($_POST['requested_person']);
    $destribution=trim($_POST['destribution']);
    $cause=trim($_POST['cause']);

    $vehicle_number=trim($_POST['vehicle_number']);
    $driver_name=trim($_POST['driver_name']);
    $driver_mobile=trim($_POST['driver_mobile']);
    $driver_address=trim($_POST['driver_address']);
    $driving_licence=trim($_POST['driving_licence']);
    
    $state=-1;
    
    global $global;
    $db=$global["db"];

    $sql = "SELECT catalog_id,amount,unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims = $db->Execute($sql);
    $catalog_id = $ims->fields["catalog_id"];
    $current_amount = $ims->fields["amount"];
    $current_unit = $ims->fields['unit'];

    
    $multiplier=unit_converter($unit,$current_unit);
    
    $current_amount_convert=$current_amount*$multiplier;

    $remaining_amount=$current_amount_convert-$amount;
    
    $remaining_amount_new=$remaining_amount/$multiplier;
    
    
    $q="SELECT * FROM ims_transfer_item;";
    $ims=$db->Execute($q);
    
    if($ims==NULL)
    {
	//$error=true;
        add_error(SHN_ERR_IMS_TRANSFER_TABLE_EXISTS);
        //return false;
    }
    else
    {

    $sql1 = "INSERT INTO ims_transfer_item (item_id,catalog_id,amount_send,unit,inv_id_from,inv_id_to,destination_type,person_send,date_send,destribution_method ,requested_person,received_item_id,amount_received,person_received,date_received,cause,vehicle_number,driver_name,driver_mobile,driver_address,driving_licence) VALUES ('$item_id','$parent_id','$amount','$unit','$inv_id_from','$inv_to','$destination_type','$person_send','$date_send','$destribution','$requested_person','$state','$state','$state','$state','$cause','$vehicle_number','$driver_name','$driver_mobile','$driver_address','$driving_licence');";  
    $ims1 = $db->Execute($sql1);

    $sql2="UPDATE ims_item_records SET amount='$remaining_amount_new',cost_per_unit='$cost_per_unit' WHERE item_id='$item_id';";
    $ims2 = $db->Execute($sql2);

    add_confirmation(_t('Item sent successfully'));

    shn_ims_send_item_page($catalog_id);
    }
    
    
    
    
    
}
/***********************************************************************************************************************************                  **************************  Receive Item              ********************************************
***************************************************************************************************************
*/
/**
***Function to Receive item
**/
function _shn_ims_receive($Limit,$page_number=null)
{
$state=-1;
    global $global;
    $db=$global["db"];
    print '<b>';
    if($page_number==0)
    {
	$page=$page_number+1;
        print (_t("Page Number  ").$page);
    }
    else
    {
	print (_t('Page Number  ').$page_number);
    }
    print '</b>';
?>
<h1 align="center"><?php print _t("Items in Transsition state")?> </h1>

<div id="result">

<?php
 $form_opts['name']="edit_item";
shn_form_fopen('receive_item_paging',null,$form_opts);
//$Limit=20;
shn_form_text(_t("Records Per Page : "),'records','onChange="submit(this);"',array('value'=>$Limit));
shn_form_fclose();
$sql="SELECT transit_id,item_id,amount_send,unit,inv_id_to,person_send,date_send FROM ims_transfer_item WHERE received_item_id='$state';";

    $SearchResult=mysql_query($sql) or die(mysql_error()); 
	$NumberOfResults=mysql_num_rows($SearchResult); 
	$NumberOfPages=ceil($NumberOfResults/$Limit); 
	
	print(_t("Go to Page : "));
	
	for($i=1;$i<$NumberOfPages+1;$i++)
	{
		
	    ?><a href="index.php?mod=ims&amp;act=receive_item_paging&amp;$i=<?php echo $i;?>&amp;$Limit=<?php echo $Limit;?>"><?php print ($i." ");?></a><?php
	    print "\n";
	}
    
    if($page_number!=0)
    {
	$page_number=($page_number-1)*$Limit;
    }
    else 
    {
	$page_number=0;
    }
    $sql1="SELECT transit_id,item_id,amount_send,unit,inv_id_to,destination_type,person_send,date_send FROM ims_transfer_item WHERE received_item_id='$state' and destination_type='inventory' LIMIT $page_number,$Limit;";
    $ims1 = $db->Execute($sql1);
   // print $sql1;
?>
    <table>
        <thead>
        <td><?=_t("Item")?></td>
        <td><?=_t("Amount Sent");?></td>
        <td><?=_t("Unit");?></td>
        <td><?=_t("Inventory From")?></td>
        <td><?=_t("To")?></td>
            <td><?=_t("Date Sent")?></td>
            <td><?=_t("Authorized Person")?></td>
        <td><?=_t("Transit Item")?></td>
            
        </thead>
    <tbody>
<?php
    
    
    while (!$ims1==NULL && !$ims1->EOF)
    {    
        $transit_id=$ims1->fields['transit_id'];
        $item_id=$ims1->fields['item_id'];
        $amount_send=$ims1->fields['amount_send'];
        $unit_id=$ims1->fields['unit'];
        $unit_name=get_unit_name($unit_id);
        $inv_id_to=$ims1->fields['inv_id_to'];
	$destination_type=$ims1->fields['destination_type'];
        $person_send=$ims1->fields['person_send'];
        $date_send=$ims1->fields['date_send'];

        
	if($destination_type=='inventory')
	{

        $sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
        $ims3=$db->Execute($sql3);
        $inventory_to=$ims3->fields['inventory_name'];
	}
	else if($destination_type=='organization')
	{
		$sql3="SELECT * FROM org_main WHERE o_uuid='$inv_id_to';";
		$ims3=$db->Execute($sql3);
        	$inventory_to=$ims3->fields['name'];
	}
	else if($destination_type=='shelter')
	{
		$sql3="SELECT * FROM camp_general WHERE c_uuid='$inv_id_to';";
		$ims3=$db->Execute($sql3);
        	$inventory_to=$ims3->fields['name'];
	}
	else if($destination_type=='victim')
	{
		$sql3="select pg.g_uuid as g_uuid,pu.p_uuid as p_uuid,pg.opt_group_type as group_name,pu.full_name as full_name,pu.family_name as family_name,pu.l10n_name as l10n_name,pu.custom_name as custom_name from pgroup pg,person_to_pgroup ptg,person_uuid pu where pg.g_uuid=ptg.g_uuid and ptg.p_uuid=pu.p_uuid and pg.g_uuid='$inv_id_to';";
    		$ims3=$db->Execute($sql3);
        	$inventory_to=$ims3->fields['full_name']." ".$ims3->fields['family_name'];
	}

        $sql4="SELECT item_name,inv_id,suplier_id FROM ims_item_records WHERE item_id='$item_id';";
        $ims4=$db->Execute($sql4);
        $item_name=$ims4->fields['item_name'];
        $inv_id_from=$ims4->fields['inv_id'];
        $suplier_id=$ims4->fields['suplier_id'];

        $sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
        $ims5=$db->Execute($sql5);
        $inventory_from=$ims5->fields['inventory_name'];
    
?>
        <tr>
        <td><?php print($item_name);?></td>
        <td><?php print($amount_send);?></td>
        <td><?php print($unit_name);?></td>
        <td><?php print($inventory_from);?></td>
        <td><?php print($destination_type);?><br><?php print($inventory_to);?></td>
        <td><?php print($date_send);?></td>
        <td><?php print($person_send);?></td>
        <td><a href="index.php?mod=ims&act=receive_item_page&transit_id=<?php echo $transit_id;?>&suplier_id=<?php echo $suplier_id;?>"><?php print("Received");?></a></td>
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

function _shn_ims_receive_item_page($transit_id,$suplier_id)
{
?>
<h1 align="center"><?php print _t("Items in Transsition state ")?> </h1>
<div id="result">
</div>

<?php
    
    global $global;
    $db=$global["db"];
    $state=-1;
    $sql = "SELECT item_id,amount_send,unit,inv_id_to,destination_type,vehicle_number,driver_name,driver_mobile,driver_address,driving_licence FROM ims_transfer_item WHERE transit_id='$transit_id';";
    $ims = $db->Execute($sql);
    $item_id=$ims->fields['item_id'];
    $amount=$ims->fields['amount_send'];
    $unit=$ims->fields['unit'];
    $unit_name=get_unit_name($unit);
    //$inv_id_from=$ims->fields['inv_id_from'];
    $inv_id_to=$ims->fields['inv_id_to'];
    $destination_type=$ims->fields['destination_type'];
    $vehicle_number=$ims->fields['vehicle_number'];
    $driver_name=$ims->fields['driver_name'];
    $driver_mobile=$ims->fields['driver_mobile'];
    $driver_address=$ims->fields['driver_address'];
    $driving_licence=$ims->fields['driving_licence'];
    
    

    $sql3="SELECT catalog_id,item_name,inv_id,cost_per_unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims3=$db->Execute($sql3);
    $parent_id=$ims3->fields['catalog_id'];
    $item_name=$ims3->fields['item_name'];
    $inv_id_from=$ims3->fields['inv_id'];
    $cost_per_unit=$ims3->fields['cost_per_unit'];

    $sql1="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_from';";
    $ims1=$db->Execute($sql1);
    $inventory_from=$ims1->fields['inventory_name'];

    $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
    $ims2=$db->Execute($sql2);
    $inventory_to=$ims2->fields['inventory_name'];

	if($destination_type=='inventory')
	{

        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_to';";
        $ims2=$db->Execute($sql2);
        $inventory_to=$ims2->fields['inventory_name'];
	}
	else if($destination_type=='organization')
	{
		$sql2="SELECT * FROM org_main WHERE o_uuid='$inv_id_to';";
		$ims2=$db->Execute($sql2);
        	$inventory_to=$ims2->fields['name'];
	}
	else if($destination_type=='shelter')
	{
		$sql2="SELECT * FROM camp_general WHERE c_uuid='$inv_id_to';";
		$ims2=$db->Execute($sql2);
        	$inventory_to=$ims2->fields['name'];
	}
	else if($destination_type=='victim')
	{
		$sql2="SELECT pg.g_uuid as g_uuid,pu.p_uuid as p_uuid,pg.opt_group_type as group_name,pu.full_name as full_name,pu.family_name as family_name,pu.l10n_name as l10n_name,pu.custom_name as custom_name FROM pgroup pg,person_to_pgroup ptg,person_uuid pu WHERE pg.g_uuid=ptg.g_uuid and ptg.p_uuid=pu.p_uuid and pg.g_uuid='$inv_id_to';";
		$ims2=$db->Execute($sql2);
        	$inventory_to=$ims2->fields['full_name']." ".$ims2->fields['family_name'];
	}

    
        
    shn_form_fopen('receive_item_db');
    shn_form_fsopen(_t("Received Item"));
    $extra_opts['value'] = $item_name;
    shn_form_text(_t("Item Name : "),'item_name','size="50" readonly=true',$extra_opts);
    //$extra_opts['value'] = $received_amount;
    shn_form_text(_t("Received Amount : "),'received_amount','size="50"',array('req'=>true,'value'=>$amount));

    $unit_select_array=array();
    
    $cq="SELECT name FROM ct_unit WHERE unit_uuid='$unit';";
    $cms=$db->Execute($cq);
    $unit_select_array[$unit]=$cms->fields['name'];
    
    $query="SELECT * FROM ct_cat_unit WHERE ct_uuid='$parent_id'";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {

        $temp2=$res->fields['unit_uuid'];
        $query1="SELECT name FROM ct_unit WHERE unit_uuid ='$temp2'";
        $res2=$db->Execute($query1);
    
        $unit_select_array[$res->fields['unit_uuid']]=$res2->fields['name'];
        $res->MoveNext();
    }    

    shn_form_select($unit_select_array,_t("Unit : "),'unit_received','size="1"',array('req'=>true));
    //shn_form_text(_t("Unit : "),'unit','size="50" readonly=true',array('value'=>$unit_name));
    $extra_opts['value'] = $cost_per_unit;
    shn_form_text(_t("Cost per Unit : "),'cost_per_unit','size="50"',$extra_opts);
    $extra_opts['value']=$inventory_from;
    shn_form_text(_t("From : "),'inventory_from','size="50" readonly=true',$extra_opts);
    $extra_opts['value']=$inventory_to;
    shn_form_text(_t("To : "),'inventory_to','size="50" readonly=true',$extra_opts);
    $date=date("Y-m-d");
    shn_form_date(_t("Date :"),'received_date',array('value'=>$date,'req'=>true,'help'=>_t('Year-Month-Date. Only - separator is accepted')));
    
    shn_form_text(_t("Authorized Person : "),'authorized_person','size="50"',array('req'=>true,'help'=>_t('Person who received Item')));

    shn_form_fsclose();

    shn_form_fsopen(_t("Transport/Transporter Details"));
    shn_form_text(_t("Vehicle Number : "),'vehicle_number','size="50"',array('value'=>$vehicle_number,'help'=>_t('Registered Number of Your ')));
    shn_form_text(_t("Driver Name : "),'driver_name','size="50"',array('value'=>$driver_name,'help'=>_t('Name of the Driver who is going to carry the vehicle')));
    shn_form_text(_t("Driver Mobile : "),'driver_mobile','size="50"',array('value'=>$driver_mobile,'help'=>_t('Contact Details of the Driver')));
    shn_form_text(_t("Driver Address : "),'driver_address','size="50"',array('value'=>$driver_address,'help'=>_t('Contact Details of the Driver')));
    shn_form_text(_t("Driving Licence Number : "),'driving_licence','size="50"',array('value'=>$driving_licence,'help'=>_t('Driving Licence Number')));
    shn_form_fsclose();

    shn_form_hidden(array('item_id'=>$item_id));
    shn_form_hidden(array('inv_id_from'=>$inv_id_from));
    shn_form_hidden(array('inv_id_to'=>$inv_id_to));
    shn_form_hidden(array('transit_id'=>$transit_id));
    shn_form_hidden(array('suplier_id'=>$suplier_id));

    shn_form_hidden(array('unit'=>$unit));
    shn_form_hidden(array('amount'=>$amount));

    shn_form_submit(_t("Received"));
    shn_form_fclose();
}

function _shn_ims_receive_item_db()
{
    $item_id=trim($_POST['item_id']);
    //$item_name=$_POST['item_name'];
    $received_amount=trim($_POST['received_amount']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $inventory_from=trim($_POST['inventory_from']);
    $inventory_to=trim($_POST['inventory_to']);
    $received_date=trim($_POST['received_date']);
    $authorized_person=trim($_POST['authorized_person']);
    $unit=trim($_POST['unit_received']);

    

    $inv_id_from=trim($_POST['inv_id_from']);
    $inv_id_to=trim($_POST['inv_id_to']);
    $transit_id=trim($_POST['transit_id']);
    $suplier_id=trim($_POST['suplier_id']);

    global $global;
    $db=$global["db"];
    
    

    $sql2="SELECT catalog_id,item_name,manufactured_date,expire_date,state FROM ims_item_records WHERE item_id='$item_id';";
    $ims2=$db->Execute($sql2);

    $catlog_id=$ims2->fields['catalog_id'];
    $item_name=$ims2->fields['item_name'];
    //$unit=$ims2->fields['unit'];
    $manufactured_date=$ims2->fields['manufactured_date'];
    $expire_date=$ims2->fields['expire_date'];
    $state=$ims2->fields['state'];
    
    $date = date('Y-m-d');
    $sql3="INSERT INTO ims_item_records(catalog_id,inv_id,transit_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date,cost_per_unit,state,inserted_date) VALUES('$catlog_id','$inv_id_to','$transit_id','$suplier_id','$item_name','$received_amount','$unit','$manufactured_date','$expire_date','$cost_per_unit','$state','$date');";
    //print $sql3;
    $ims3=$db->Execute($sql3);

    $sql4="SELECT item_id FROM ims_item_records WHERE transit_id='$transit_id';";
    $ims4=$db->Execute($sql4);
    $item_id_new=$ims4->fields['item_id'];

    $sql1="UPDATE ims_transfer_item SET received_item_id='$item_id_new',amount_received='$received_amount',person_received='$authorized_person',date_received='$received_date' WHERE transit_id='$transit_id';";
    $ims1=$db->Execute($sql1);
    
    $q="INSERT INTO ims_item_amount_history(item_id, first_amount, unit) VALUES ('{$item_id_new}', '{$received_amount}', '{$unit}')";
    $r = $db->Execute($q);

    add_confirmation(_t('Item Received successfully'));

    shn_ims_receive_item();
    
}

function _shn_ims_validate_send_item_page()
{
    global $global;
    $error_flag=false;
    clean_errors();

    $amount=trim($_POST['amount']);
    $item_id = trim($_POST['item_id']);
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $date=trim($_POST['date']);
    $unit=trim($_POST['unit_select']);

    $inv_to = trim($_POST['inv_to']);
    $organization_to = trim($_POST['organization_to']);
    $shelter_to = trim($_POST['shelter_to']);
    $victim_to = trim($_POST['victim_to']);
   	
    if($inv_to!='')
    {
	$destination_type='inventory';
    }
    if($organization_to!='')
    {
	$inv_to=$organization_to;
	$destination_type='organization';
    }
    if($shelter_to!='')
    {
	$inv_to=$shelter_to;
	$destination_type='shelter';
    }
    if($victim_to!='')
    {
	$inv_to=$victim_to;
	$destination_type='victim';
    }

    if($destination_type=='')
    {
        add_error(_t('Destination is essential. Please complete and submit again'));
        $error_flag=true;
    }
    
    if($amount==null)
    {
        add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
        $error_flag=true;
    }
    if(!is_numeric($amount))
    {
        add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
        $error_flag=true;
    }
    if($unit==null)
    {
	add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
	$error_flag=true;
    }
    if($cost_per_unit!=null)
    {
        if(!is_numeric($cost_per_unit))
        {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
            $error_flag=true;
        }
    }

    if (!shn_valid_date($date))
    {
        $error_flag=true;
    
        }

    if($date==null)
    {
        add_error(SHN_ERR_IMS_DATE_INCOMPLETE);
        $error_flag=true;
    }

    if($date!=null)
    {
        if(_shn_ims_date_validate($date))
        {
            $error_flag=true;
        }
    }
    
    
    if(trim($_POST['authorized_person'])==null)
    {
        add_error(SHN_ERR_IMS_AUTHORIZED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
    if(trim($_POST['requested_person'])==null)
    {
        add_error(SHN_ERR_IMS_REQUESTED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
   /* if(trim($_POST['destribution'])==null)
    {
        add_error(SHN_ERR_IMS_DESTRIBUTION_METHOD_INCOMPLETE);
        $error_flag=true;
    }*/

    global $global;
    $db=$global["db"];

    $sql = "SELECT catalog_id,amount,unit FROM ims_item_records WHERE item_id='$item_id';";
    $ims = $db->Execute($sql);
    $catalog_id = $ims->fields["catalog_id"];
    $current_amount = $ims->fields["amount"];
    $current_unit = $ims->fields['unit'];

    
    $multiplier=unit_converter($unit,$current_unit);
    
    $current_amount_convert=$current_amount*$multiplier;
    
    
    

    if($current_amount_convert<$amount)
    {
        add_error(SHN_ERR_IMS_INVALID_AMOUNT);
        $error_flag=true;
    }

    
    
    if($cost_per_unit<0)
    {
        add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
        $error_flag=true;
    }

    return $error_flag;
}

/*****************************************************************************************************************
*****         Validate Receive_item page                                             *****************************
*****************************************************************************************************************/

function _shn_ims_validate_receive_item_page()
{
    global $global;
    $error_flag=false;
    
    clean_errors();

    $unit_send=trim($_POST['unit']);
    $amount_send=trim($_POST['amount']);
    
    
    $received_amount=trim($_POST['received_amount']);
    $unit_received=trim($_POST['unit_received']);
    
    $cost_per_unit=trim($_POST['cost_per_unit']);
    $received_date=trim($_POST['received_date']);
    
    $convert_amount_send=$amount_send*unit_converter($unit_received,$unit_send);
    
    
    //if($convert_amount_send>$received_amount || $convert_amount_send==$received_amount)
    

    if($convert_amount_send<$received_amount)
    {
        add_error(SHN_ERR_IMS_INVALID_RECEIVED_AMOUNT);
        $error_flag=true;
    }

    if($received_amount==null)
    {
        add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
        $error_flag=true;
    }
    if(!is_numeric($received_amount))
    {
        add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
        $error_flag=true;
    }
    if($unit_received==null)
    {
	add_error(SHN_ERR_IMS_UNIT_INCOMPLETE);
	$error_flag=true;
    }
    if($received_date==null)
    {
        add_error(SHN_ERR_IMS_INVALID_DATE);
        $error_flag=true;
    }
    if (!shn_valid_date($received_date))
    {
        $error_flag=true;
    
        }

    if($received_date!=null)
    {
        if(_shn_ims_date_validate($received_date))
        {
            $error_flag=true;
        }
    }

    if(trim($_POST['authorized_person'])==null)
    {
        add_error(SHN_ERR_IMS_AUTHORIZED_PERSON_INCOMPLETE);
        $error_flag=true;
    }
    if($received_amount<0)
    {
        add_error(SHN_ERR_IMS_INVALID_RECEIVED_AMOUNT);
        $error_flag=true;
    }
    if($cost_per_unit<0)
    {
        add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
        $error_flag=true;
    }
    if($cost_per_unit!=null)
    {
        if(!is_numeric($cost_per_unit))
        {
            add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
            $error_flag=true;
        }
    }
    
    return $error_flag;
}


function _shn_admin_set_option_javascript()
{
?>
<script type="text/javascript">
    
	
	var url = "index.php?"; 
    var start = 1;
 var http;
    function getHTTPObject() 
    {
        var xmlhttp;
        
        

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();

            } catch (e) {
            xmlhttp = false;
            }
        }

    return xmlhttp;
    }



function handleHttpResponse(){
        if (http.readyState == 4) 
    { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
		
                if (results[0]!="null")
            	{ 
                var x=document.getElementsByName('victim_to');
		
                    for (i=0; i<=x[0].options.length+1; i++)
                    {
                            x[0].options[0]=null;
				
                            }
 		

                j=0;
                for (i=1; i<results.length-1; i=i+2, j++)
                    {
                    
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                            }
                    }
        } 
    }


    function change_action_des(value){
        alert
	
         if(value=='inventory'){         	
         	document.getElementById("des_inventory").style.display='block';
		//document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		document.getElementById("des_victim").style.display='none';     	
         }
	 else if(value=='shelter'){         	
         	document.getElementById("des_shelter").style.display='block';  
		document.getElementById("des_inventory").style.display='none';
		//document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		document.getElementById("des_victim").style.display='none';   	
         }
	 else if(value=='organization'){         	
         	document.getElementById("des_organization").style.display='block'; 
		document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		//document.getElementById("des_organization").style.display='none';
		document.getElementById("des_victim").style.display='none';    	
         }
	  else if(value=='victim'){         	
         	document.getElementById("des_victim").style.display='block'; 
		document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';    	
         }
         else
	{
             document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		document.getElementById("des_victim").style.display='none';
	}	
         }

	function add_evacuees(){
		
        	var y=document.getElementsByName("head_name");
		
       		http = getHTTPObject();
        	var url2=url + "act=victims&mod=xst&stream=text&head_name="+y[0].value;
        	//var url2=url + "act=sub_cat&cat=" + selection+"&flag="+item_flag;
        	http.open("GET", url2, true); 
//        	http.onreadystatechange = null; 
        	http.onreadystatechange = function(){}; 
        	http.onreadystatechange = handleHttpResponse; 
        	http.send(null);
        }
</script>

		
<?php
}
?>
