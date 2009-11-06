<?php
/** API of the IMS 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ishan Liyanage <ishanul@gmail.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ims
*/

/**
 * This returns the list items in an all or a particular inventory 
 * with associated quantities 
 * @param 
 * @access public
 * @return array
 */
function shn_ims_list_item_by_inventory($inventory=NULL){
    global $global;
    $db=$global['db'];
    $item_list=array();
    if(NULL!=$inventory){
        $query='SELECT item_name,amount FROM ims_item_records WHERE inv_id="'.$inventory.'"';	
    }    
    else{
    	$query='SELECT item_name,amount FROM ims_item_records';	
    }
    $res=$db->Execute($query);
    while(!$res==NULL && !$res->EOF){
    	$item_list[] = array('item' => $res->fields["item_name"], 'amount' => $res->fields["amount"]);
        $res->MoveNext();
    }
   
    return $item_list;
}
/**
 * This returns the list of organizations
 * @param 
 * @access public
 * @return array
 */
function shn_ims_get_item_details($item=NULL){
	global $global;
    $db=$global['db'];
    $item_list=array();
    if(NULL!=$item){
    	$query='SELECT ct_catalogue.name as name,amount,expire_date,inventory_name FROM ims_item_records,ims_inventory_records,ct_catalogue WHERE ims_item_records.inv_id=ims_inventory_records.inv_uuid AND ct_catalogue.ct_uuid=ims_item_records.catalog_id AND ct_catalogue.name="'.$item.'"';	
    }
    else
    {
        $query='SELECT ct_catalogue.name as name,amount,expire_date,inventory_name FROM ims_item_records,ims_inventory_records,ct_catalogue WHERE ims_item_records.inv_id=ims_inventory_records.inv_uuid AND ct_catalogue.ct_uuid=ims_item_records.catalog_id';
    }
	$res=$db->Execute($query);
    while(!$res==NULL && !$res->EOF){
    	$item_list[] = array('name' => $res->fields["name"], 'amount' => $res->fields["amount"], 'expire_date' => $res->fields["expire_date"], 'inventory' => $res->fields["inventory_name"]);
        $res->MoveNext();
    }
   
    return $item_list;
}




?>