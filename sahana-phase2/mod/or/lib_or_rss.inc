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

function shn_xml_or_new_org_list(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_t('Newly registered organizations'),_t('This List contains the newly registered organizations to the organization module of the Sahana System.'));

    $sql = "select o_uuid,name,f.option_description from org_main as o inner join field_options as f on f.option_code=o.opt_org_type AND f.field_name='opt_org_type'  where parent_id is NULL and privacy=false order by created desc";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->SelectLimit($sql,30);

    if (!$res){add_error($global['db']->ErrorMsg());}
    foreach($res as $record){
        $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=or&amp;act=edit_org&amp;org_id=".$record['o_uuid'];
        $org_id=$record['o_uuid'];
        $db=$global["db"];
        $q="select name from location,location_details where poc_uuid='{$org_id}' and location_details.location_id=location.loc_uuid";
        $res_temp=$db->Execute($q);
        $loc=$res_temp->fields["name"];
        $q = "select option_description from field_options,sector where pgoc_uuid='{$org_id}' and field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
        $res_sector=$db->Execute($q);
//         $location=_shn_org_location_string($loc);

        $desc=_t("This is a ").$record['option_description']._t(" organization located in ").$loc._t(". And it provides the following services - ");
        foreach($res_sector as $s)
            $desc.=$s['option_description']." , ";
        shn_rss_item($record['name'],$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
}


