<?php
/**
* RSS Feeds for Request/Aid Management 
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
* @subpackage    rms
* @license       http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_xml_rms_new_pledges(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Newly made Pledges'),_('This List contains newly made pledges in sahana Request Aid Management system'));
    $sql='SELECT pl.plg_uuid, pl.plg_date , pl.status , p.full_name FROM rms_pledge AS pl left join person_uuid AS p ON p.p_uuid=pl.donor_uuid ORDER BY  pl.plg_date DESC';

    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->SelectLimit($sql,30);

    if (!$res){add_error($global['db']->ErrorMsg());}
    foreach($res as $record){
        $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=rms&amp;act=plg_ls&amp;seq=view_plg&amp;plg_id=".$record['plg_uuid'];
        $desc=_("This pledge was made on ").$record['plg_date']._(" by ").$record['full_name'].".";
        $desc.=_("And the pledged items are");
        $sql="select name from rms_plg_item as r inner join ct_catalogue as c on c.ct_uuid = r.item_uuid  where plg_uuid='{$record['plg_uuid']}';";
        $res = $global['db']->GetAll($sql);
        foreach($res as $item)
            $desc.=", ".$item['name'];
        shn_rss_item(_("Plg Id ").$record['plg_uuid'],$url,"$desc.");
    }
    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_rms_new_requests(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Newly made Requests'),_('This List contains the newly made requests in Request Aid Management system'));
    $sql='SELECT r.req_uuid, r.req_date , r.status , p.full_name , l.name as l_name FROM rms_request AS r LEFT JOIN location AS l ON l.loc_uuid=r.loc_uuid left join person_uuid AS p ON p.p_uuid=r.reqstr_uuid ORDER BY  r.req_date DESC';

    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->SelectLimit($sql,30);

    if (!$res){add_error($global['db']->ErrorMsg());}
    foreach($res as $record){
        $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=rms&amp;act=req_ls&amp;seq=view_req&amp;req_id=".$record['req_uuid'];
        $desc=_("This request was made on ").$record['req_date']._(" by ").$record['full_name'].".";
        $desc.=_("And the requested items are");
        $sql="select name from rms_req_item as r inner join ct_catalogue as c on c.ct_uuid = r.item_uuid  where req_uuid='{$record['req_uuid']}';";
        $res = $global['db']->GetAll($sql);
        foreach($res as $item)
            $desc.=", ".$item['name'];
        shn_rss_item(_("Req Id ").$record['req_uuid'],$url,"$desc.");
    }
    shn_rss_channel_close();
    shn_rss_close();
}

?>