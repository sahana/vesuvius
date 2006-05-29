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

global $global;

//include_once ("add_item_main_page.inc");
//include_once ("search.inc");
include_once ("add_item.inc");	
include_once ("errors.inc");
include_once ('lib_ims.inc');


function _shn_ims_add_item_db()
	{
		
		//shn_ims_add_item();	
		global $global;
		$db=$global["db"];
		//$cate=$_POST['cat'];
		$item=trim($_POST['item_name']);
		$suplier_id=trim($_POST['suplier_id']);
		//print ($item);
		$parent_id=trim($_POST['parent_id']);
		//print ($cate);
		$amou=trim($_POST['amount']);
		$cost_per_unit=trim($_POST['cost_per_unit']);
		$unit=trim($_POST['unit_select']);
		$inv_id=trim($_POST['inv_id']);
		$manufactured_date=trim($_POST['manufactured_date']);
		$expire_date=trim($_POST['expire_date']);
		
		$state="available";

		//print ($suplier_id);
		//print $unit;
		
    		$sql = " insert into ims_item_records (catalog_id,inv_id,suplier_id,item_name,amount,cost_per_unit,unit,manufactured_date,expire_date,state) values ('$parent_id','$inv_id','$suplier_id','$item','$amou','$cost_per_unit','$unit','$manufactured_date','$expire_date','$state');";
		$ims = $db->Execute($sql);
		
		$_POST['item_name']="";
		$_POST['amount']="";
		$_POST['cost_per_unit']="";
		$_POST['manufactured_date']="";
		$_POST['expire_date']="";
		//$_POST['unit_select']=""
		

		_shn_ims_expire_date_check();
		shn_ims_add_item_main_page();
		
		
	}



function _shn_ims_validate_additemform()
{
//include_once 'errors.inc';
	global $global;
	$error_flag=false;
	clean_errors();
	$parent_id=trim($_POST['parent_id']);
	$amount=trim($_POST['amount']);
	$manufactured_date=trim($_POST['manufactured_date']);
	$expire_date=trim($_POST['expire_date']);
	$cost_per_unit=trim($_POST['cost_per_unit']);
	$unit=trim($_POST['unit_select']);
	
	//this checks whether name entered in the add main form
	if($amount==null || $amount<0)
	{
	add_error(SHN_ERR_IMS_AMOUNT_INCOMPLETE);
	$error_flag=true;
	}
	if(!is_numeric($amount))
	{
	add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE);
	$error_flag=true;
	}
	if(trim($_POST['inv_id'])==null)
	{
	add_error(SHN_ERR_IMS_INVENTORY_INCOMPLETE);
	$error_flag=true;
	}
	$cost_per_unit=trim($_POST['cost_per_unit']);
	if(!is_numeric($cost_per_unit))
	{
	add_error(SHN_ERR_IMS_ENTER_NUMERIC_VALUE_COST);
	$error_flag=true;
	}
	if($cost_per_unit<0)
	{
	add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
	$error_flag=true;
	}
	
	if (!shn_valid_date($manufactured_date) || !shn_valid_date($expire_date))
	{
	$error_flag=true;
    	}

	if($manufactured_date!=null || $expire_date!=null)
	{
		if(_shn_ims_date_validate($manufactured_date))
		{
		//add_error(INVALID_DATE);
		$error_flag=true;
		}
	
		if(_shn_ims_date_validate($expire_date))
		{
		$error_flag=true;
		}
	}
	//_shn_ims_date_validate($expire_date);
	/*if(($manufactured_date=trim($_POST['manufactured_date']))!=null)
	{
	list($year_m,$month_m,$date_m)=split('[/.-]', $manufactured_date);
	//list($year_e,$month_e,$date_e)=split('[/.-]', $expire_date);
		if($month_m<0 || $month_m>12 || $month_e<0 || $month_e>12)
		{
		add_error(SHN_ERR_IMS_DATE_INCOMPLETE);
		$error_flag=true;
		}
	}*/
	//$manudate=$_POST['manudate'];
	/*if (!shn_valid_number($amount))
	{
	add_error(SHN_ERR_IMS_INVALID);
	$error_flag=true;
	}
	if(!shn_valid_number($cost_per_unit))
	{
	add_error(SHN_ERR_IMS_INVALID_COST_PER_UNIT);
	$error_flag=true;
	}*/

	return $error_flag;
}
?>
