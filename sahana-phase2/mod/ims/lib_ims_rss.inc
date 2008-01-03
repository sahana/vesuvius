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
* @author        J P Fonseka <jo@opensource.lk>
* @copyright     Lanka Software Foundation - http://www.opensource.lk
* @package       Sahana
* @subpackage    ims
* @license       http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


function shn_xml_ims_rss_expired_list(){
    global $global;
    _shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Expired item List'),_('Following are a list of items which have been expired recently in SAHANA inventory.'));

    //get a list of expired item list limit it to 30 
    $sql="SELECT item_id,inv_id,item_name,amount,ct_unit.name as unit,manufactured_date,expire_date FROM ims_item_records as i INNER JOIN ct_unit ON ct_unit.unit_uuid = i.unit WHERE state='expired' ORDER BY expire_date LIMIT 0, 30;";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->Execute($sql);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=ims&amp;act=report_expired";
    foreach($res as $record){
        $desc=_("This item is manufactured on ").$record['manufactured_date']._(" and expired on ").$record['expire_date']."."._(" And Currently there are ").$record['amount']." ".$record['unit']._(" left in the inventory.");
        shn_rss_item($record['item_name'],$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_ims_rss_reorder_list(){
    global $global;
    _shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Items below reorder level'),_('Following are a list of items which are below reorder level'));

    $sql="SELECT i.item_id,i.item_name,i.amount,r.minimum_quantity FROM ims_item_records as i INNER JOIN ims_reorder_level as r ON (r.catalog_id=i.catalog_id AND r.inv_id=i.inv_id) LIMIT 0, 30;";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->Execute($sql);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=ims&amp;act=view_edit_reorder_page";
    foreach($res as $record){
        $desc=_("Minimum Quantity ").$record['minimum_quantity']._(" required").$record['expire_date']."."._(" And Currently there are ").$record['amount']." ".$record['unit']._(" left in the inventory.");
        shn_rss_item($record['item_name'],$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_ims_rss_transit(){
    global $global;
    _shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Transit item List'),_('Items which are in transit.'));

    $sql="SELECT t.transit_id,t.item_id,item_name,amount_send,c.name,inventory_name,destination_type,person_send,date_send FROM ims_transfer_item as t INNER JOIN ims_item_records as i on i.item_id=t.item_id INNER JOIN ct_unit as c ON c.unit_uuid = i.unit INNER JOIN ims_inventory_records as n ON t.inv_id_to=n.inv_uuid  ORDER BY date_send LIMIT 0, 30";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->Execute($sql);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=ims&amp;act=report_transit_item";
    foreach($res as $record){
        $desc=_("An amount of ").$record['amount_send']." ".$record['name']._("  has been transfered ")._(" to ").$record['inventory_name']." ".$record['destination_type']._(" on ").$record['date_send']._(" by ").$record['person_send'];
        shn_rss_item($record['item_name'],$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
}
?>