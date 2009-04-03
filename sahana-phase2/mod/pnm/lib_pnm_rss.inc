<?php
/** RSS Library of the Press and Media Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
* @copyright Respective Authors
* @package    sahana
* @subpackage pnm
* 
* Developed during Sahana 2009 as a tribute.
*/
function shn_xml_pnm_rss_news_list() {
	global $global;
	// _shn_ims_expire_date_check();
	require_once($global['approot']."inc/lib_rss.inc");
	shn_rss_open();
	shn_rss_channel_open(_t('Press Releases'),_t('Following are a list of items which have been released recently in SAHANA press and media.'));
	$query = "SELECT link, headline, description FROM `pnm_headlines`";
	//define('ADODB_FETCH_ASSOC',2);
	//$global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
	$res = $global['db']->SelectLimit($query,15);
	//if (!$res){add_error($global['db']->ErrorMsg());}
	$prot = isset($_SERVER['HTTPS'])?"https://":"http://";
	$url=$prot.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF']."?mod=pnm&amp;act=pnm_released";
	while($record = $res->FetchRow()){
		$desc=$record['description'];
		shn_rss_item($record['headline'],$url,$desc);
	}

	shn_rss_channel_close();
	shn_rss_close();
}

function shn_xml_pnm_rss_video_list(){
	global $global;
	require_once ($global['approot']."inc/lib_rss.inc");
	shn_rss_open();
    shn_rss_channel_open(_t('Video Releases'),_t('Following are a list of videos which have been released recently in SAHANA press and media.'));
    $query = "SELECT media_title, media_description, media_path, mime_type FROM `pnm_media`";
    //define('ADODB_FETCH_ASSOC',2);
    //$global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = $global['db']->SelectLimit($query,15);
    //if (!$res){add_error($global['db']->ErrorMsg());}
    $prot = isset($_SERVER['HTTPS'])?"https://":"http://";
    while($row = $res->FetchRow()){
    	$url=$prot.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF']."/".$row['media_path'];
        $desc=$row['media_description'];
        shn_rss_item($row['media_title'],$url,$desc,array('mime'=>$row['mime_type']));
    }
    shn_rss_channel_close();
    shn_rss_close();
}

