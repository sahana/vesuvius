<?php
/**
 * 
 * UNSTABLE CODE...
* Sahana GIS XML Export
* 
* Based on Jo's lib_rss, but for GIS related RSS feed exports
* 
* @todo Make functions generic in OOP so XML exporting can be made generic
* @todo currently handle Atom: support RSS 2.0, RDF...
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library		GIS
* @version		$Id: georss.inc,v 1.2 2009-08-22 17:17:27 ravithb Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_georss_open(){
    // GeoRSS Simple
    echo '<?xml version="1.0" encoding="utf-8"?>';
    echo '<feed xmlns="http://www.w3.org/2005/Atom" xmlns:georss="http://www.georss.org/georss">';
}

function shn_georss_channel_open($title,$subtitle,$desc){
    global $conf;
    echo "<title>$title</title>\n";
    echo "<subtitle>$title</subtitle>\n";
    echo "<link>http://".$_SERVER[HTTP_HOST].htmlspecialchars($_SERVER['REQUEST_URI'])."</link>\n";
    echo "<updated>$desc</updated>\n";
    echo "<description>$desc</description>\n";
    echo "<language>{$conf['locale']}</language>\n";
    echo "<category>Sahana</category>\n";
    echo "<generator>"._t("Sahana FOSS Disaster Management System")."</generator>\n";
    echo "<webMaster>{$conf['root_email']}</webMaster>\n";
}

function shn_georss_channel_close(){
    echo "</channel>\n";
}

function shn_georss_item($title,$link,$description,$extra_opt=array()){
    echo "<item>\n";
    echo "<title>$title</title>\n";
    echo "<link>$link</link>\n";
    echo "<description>$description</description>\n";
    foreach($extra_opt as $tag=>$val){
        echo "<$tag>$val</$tag>\n";
    }
    echo "</item>\n";
}

function shn_georss_close(){
    echo "</rss>\n";
}

function shn_rss_add_feed($act,$title,$desc=null){
    global $global;
?>
    <div class='rssfeed'>
    <a href="index.php?mod=<?php echo $global['module']?>&amp;act=<?php echo $act?>&amp;stream=xml">
    <img src="res/img/RSS-Feed.png"/>
    </a>
    <strong><?php echo $title?></strong>
<?php if(isset($desc)){ ?>
    <br />
    <p><?php echo $desc ?></p>
<?php
    }
    echo "</div>";
}

