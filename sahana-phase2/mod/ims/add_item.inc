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
* @author		Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright	Lanka Software Foundation - http://www.opensource.lk
* @package		Sahana
* @subpackage	
* @tutorial		
* @license	  	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";*/
include_once ('view_edit_item.inc');
include_once $global['approot'].'/mod/cs/lib_cs.inc';

$category=$_POST['itemcat'];


/**
*form for Add blankets to the inventory

function add_item_without_expire_date($category)
{
?>
*/

function _shn_ims_add_item_header()
{
?>


<h1 align="center"><?php print _("Add Item"); ?> </h1>
<div id="add_item_medicaldrugs">

</div>



<?php

}

/**
**First page for Add item Page
**/

function _shn_ims_add_item_main_page() 
{	
	
?>

<h1 align="center"><?php print _("Add items to the Inventory");?><br></h1>
<dev id="report">

</dev>

<?php
	$form_opts['name']='subcat';
	shn_form_fopen("add_item",null,$form_opts);
	shn_sub_cat(6,'subcat');
	shn_form_fclose();
	
}

/** Function
**
**/
/*function _shn_ims_add_item_category_selection()
{
	$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id==null)
		{
		$parent_id = $_POST[$i-1];
		break;
		}
	}
	//print ("test");	
	echo $parent_id;
	global $global;
	$db=$global["db"];

	$sql = " insert into ims_item_records (catalog_id) values ('{$parent_id}');";
	$ims = $db->Execute($sql);
	//add_item($temp);
	
}*/

/**
*Form for Add medical drugs to the inventory
*/

function add_item($temp) 
{
	
	//print ($temp);
	//print ($cat);
	if ($temp!=NULL)
	{
		global $global;
		$db=$global["db"];
		$sql="SELECT item_name,amount,manufactured_date,expire_date,suplier_name,suplier_address,suplier_telephone,suplier_email FROM ims_item_records WHERE item_id='$temp' ;";
		$ims = $db->Execute($sql);
		$item_name=$ims->fields["item_name"];
		$amount=$ims->fields["amount"];
		$manufactured_date=$ims->fields["manufactured_date"];
		$expire_date=$ims->fields["expire_date"];
		$suplier_name=$ims->fields["suplier_name"];
		$suplier_address=$ims->fields["suplier_address"];
		$suplier_telephone=$ims->fields["suplier_telephone"];
		$suplier_email=$ims->fields["suplier_email"];
		//$extra_opts['value'] = $item_name;
		//$extra_opts['value']=$amount;
	}
	else
	{
	$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id==null)
		{
		$parent_id = $_POST[$i-1];
		break;
		}
	}
	//print ("test");	
	echo $parent_id;

		global $global;
		$db=$global["db"];
		$sql="SELECT name FROM ct_catalogue WHERE ct_uuid='$parent_id';";
		$ims = $db->Execute($sql);
		$item_name=$ims->fields["name"];
		$amount="";
		$manufactured_date="";
		$expire_date="";
		$suplier_name="";
		$suplier_address="";
		$suplier_telephone="";
		$suplier_email="";
	}

	
	

	//$extra_opts['req']=true;
	$cat=$category;
	
	//print ($cat);
	//$category=$_POST['itemcat'];
	shn_form_fsopen('Primary Details');
	$extra_opts['value'] = $item_name;
	shn_form_text(_("* Item : "),'item_name','size="50"',$extra_opts);
	$extra_opts['value']=$amount;
	shn_form_text(_("*  Amount : "),'amount','size="50"',$extra_opts);
	
/*------------------*/

	global $global;
	$db=$global["db"];
	$myoptions=array();
	$query="select * from ct_cat_unit where ct_uuid='$parent_id'";
	$res=$db->Execute($query);

	while(!$res==NULL && !$res->EOF)
	{
	$temp2=$res->fields['unit_uuid'];
	$query="select name from ct_unit where unit_uuid ='$temp2'";
	$res2=$db->Execute($query);	
	$myoptions[$res->fields['ct_uuid']]=$res2->fields['name'];;
	$res->MoveNext();
	}

	
	shn_form_multi_select('unit_select',$myoptions, _("Unit"),'size=5 multiple="multiple"' );

	
/*------------------*/
	
	global $global;
	$db=$global["db"];
	$inventory_array=array();
	//$inventory_array['0']="None";
	$q="SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
	$ims=$db->Execute($q);
	//$j=0;
	while($ims!=NULL && !$ims->EOF)
	{
		
		$inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];//}
		$ims->MoveNext();
		//$j=$j+1;
		//print ($j);
	}	
	
	shn_form_select($inventory_array,_("Inventory : "),'inv_id','size="1"',$extra_opts);

	shn_form_fsclose();

	shn_form_fsopen(_('Secondry details'));
	$extra_opts['value'] = $manufactured_date;
	shn_form_text(_("Manufactured Date : "),'manufactured_date','size="25"',$extra_opts);
	$extra_opts['value'] = $expire_date;
	shn_form_text(_("Expire Date (YYYY-mm-dd) :"),'expire_date','size="25"',$extra_opts);
		
	shn_form_fsclose();

	

	shn_form_fsopen('Supply details');
	//shn_form_text(_("Organization Name"),'org_name','size="50"',null);
	$extra_opts['value']=$suplier_name;
	shn_form_text(_("Suply Person Name   : "),'suplier_name','size="50"',$extra_opts);
	$extra_opts['value']=$suplier_address;
	shn_form_text(_("Suply Person Address   : "),'suplier_address','size="50"',$extra_opts);
	$extra_opts['value']=$suplier_telephone;
	shn_form_text(_("Contact Number   : "),'suplier_telephone','size="50"',$extra_opts);
	$extra_opts['value']=$suplier_email;
	shn_form_text(_("e-mail address   : "),'suplier_email','size="50"',$extra_opts);

	shn_form_fsclose();

	shn_form_hidden(array('cat'=>$category));
	
	if ($temp==NULL)
	{
		/*$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id==null)
		{
		$parent_id = $_POST[$i-1];
		break;
		}
	}
	//print ("test");	
	echo $parent_id;*/
	
		shn_form_hidden(array('parent_id'=>$parent_id));
		shn_form_submit(_("Submit"));
	}
	else
	{
		shn_form_hidden(array('temp'=>$temp));
		shn_form_submit(_("Save"));
		//shn_form_button("Delete");
		//shn_form_button("Destroy");	
	}


	//shn_form_fclose();
	
	}




	


