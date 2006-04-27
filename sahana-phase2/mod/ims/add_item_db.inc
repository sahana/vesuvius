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


function _shn_ims_add_item_db()
	{
				//shn_ims_add_item();	
		global $global;
		$db=$global["db"];
		$cate=$_POST['cat'];
		$item=$_POST['item_name'];
		//print ($item);
		$parent_id=$_POST['parent_id'];
		//print ($cate);
		$amou=$_POST['amount'];
		$unit=$_POST['itemunit'];
		$inv_id=$_POST['inv_id'];
		$manufactured_date=$_POST['manufactured_date'];
		$expire_date=$_POST['expire_date'];
		$suply_person_name=$_POST['suplier_name'];
		$suply_person_address=$_POST['suplier_address'];
		$suply_person_telephone=$_POST['suplier_telephone'];
		$suply_person_email=$_POST['suplier_email'];
		$state="available";

		//print ($inv_id);
		
    		$sql = " insert into ims_item_records (category,catalog_id,inv_id,item_name,amount,unit,manufactured_date,expire_date,state) values ('$cate','$parent_id','$inv_id','$item','$amou','$unit','$manufactured_date','$expire_date','$state');";
		$ims = $db->Execute($sql);
		
		$_POST['item_name']="";	
		$_POST['amount']="";
		$_POST['manudate']="";
		$_POST['expdate']="";
		$_POST['suplier_name']="";
		$_POST['suplier_address']="";
		$_POST['suplier_telephone']="";
		$_POST['suplier_email']="";

		shn_ims_add_item_main_page();
		
		
	}

/**function _shn_ims_search_database()
	{
		global $global;
		$db=$global["db"];
		$item_search=$_POST['item_name_search'];
		
		$sql = "select 'item_id','amount','manufactured_date','expire_date','suplier_name','suplier_address','suplier_telephone','suplier_email' from medical_drugs where item_name='$item_search';";
		$ims = $db->Execute($sql);

		//_shn_ims_search_item();
	}	
*/
?>
