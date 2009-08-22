<?php
/**
* Sahana Messaging module Feeds
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        J P Fonseka <jo@respere.lk>
* @copyright     Respere http://respere.com
* @package       Sahana
* @subpackage    msg
* @license       http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
require_once('class_cap_alert.inc');
// require_once('class_cap_info.inc');
// require_once('class_cap_resource.inc');
// require_once('class_cap_area.inc');

function shn_xml_msg_rss_alert(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_t('CAP Alerts'),_t('Cap messages issued by the sahana system.'));
    
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=msg&amp;act=cap_download&amp;stream=text&amp;type=messages";

    $MSG_DIR = '../res/msg';
    $files = scandir($MSG_DIR.'/cap/messages');
    
    $messages=array();
    $time=array();
    foreach ($files as $file)
    {
        $message=array();
        if(strstr($file,'.xml') || strstr($file,'.XML')){
            $msg = new Msg_CapAlert($MSG_DIR.'/cap/messages/' . $file);
            $info = $msg->getInfo();
            $message['title']= $info->getHeadline()." : ".$msg->getSent();
            $message['desc'] = $info->getDescription();
            $message['url']= $url. '&amp;file='.$file;
            array_push($time,$msg->getSent());
            array_push($messages , $message);
        }
    }
    
    arsort($time);
    
    $i=20; //max links 
    foreach ($time as $key=>$t){
        if($i<1)break;
        --$i;
        $message=$messages[$key];
        shn_rss_item($message['title'],$message['url'],$message['desc']);
    }

    shn_rss_channel_close();
    shn_rss_close();
}

