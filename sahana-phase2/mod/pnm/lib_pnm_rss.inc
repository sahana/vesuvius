<?php
function shn_xml_ims_rss_expired_list() {
global $global;
   // _shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_t('press release'),_t('Following are a list of items which have been released recently in SAHANA press and media.'));
    $query = "select link, headline, description from `pnm_headlines` limit 15";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->Execute($query);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=pnm&amp;act=pnm_released";
    foreach($res as $record){
        $desc=_t("This item is released on ").$record['headline']._t(" and is about  ").$record['description']."."._t(" as the headline.");
        shn_rss_item($record['headline'],$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();



}

?>
