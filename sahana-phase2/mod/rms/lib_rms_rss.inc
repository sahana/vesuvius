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

    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_rms_new_requests(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_('Newly made Requests'),_('This List contains the newly made requests in Request Aid Management system'));
    $sql='SELECT r.req_uuid, r.req_date , r.status , r.reqstr_uuid, l.name FROM rms_request AS r LEFT JOIN location AS l ON l.loc_uuid=r.loc_uuid ORDER BY  r.req_date DESC';

    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->SelectLimit($sql,30);

    if (!$res){add_error($global['db']->ErrorMsg());}
    foreach($res as $record){
        $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=rms&amp;act=req_ls&amp;seq=view_req&amp;req_id=".$record['req_uuid'];
        $desc=_("This is a ").$record['option_description']._(" organization located in ").$loc._(". And it provides the following services - ");
        shn_rss_item(_("Req Id ").$record['req_uuid'],$url,$desc);
    }
    shn_rss_channel_close();
    shn_rss_close();
}

?>