<?php
/**
 *
 * A Simple Library to generate RSS feeds
 *
 * PHP version 4 and 5
 * 
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


function shn_rss_open(){
    echo '<rss version="2.0">';
}

function shn_rss_channel_open($title,$desc){
    global $conf;
    echo "<channel>\n";
    echo "<title>$title</title>\n";
    echo "<link>http://".$_SERVER[HTTP_HOST].htmlspecialchars($_SERVER['REQUEST_URI'])."</link>\n";
    echo "<description>$desc</description>\n";
    echo "<language>{$conf['locale']}</language>\n";
    echo "<category>Sahana</category>\n";
    echo "<generator>"._t("Sahana FOSS Disaster Management System")."</generator>\n";
    echo "<webMaster>{$conf['root_email']}</webMaster>\n";
}

function shn_rss_channel_close(){
    echo "</channel>\n";
}

function shn_rss_item($title,$link,$description,$extra_opt=array()){
    echo "<item>\n";
    echo "<title>$title</title>\n";
    echo "<link>$link</link>\n";
    echo "<description>$description</description>\n";
    foreach($extra_opt as $tag=>$val){
        echo "<$tag>$val</$tag>\n";
    }
    echo "</item>\n";
}

function shn_rss_close(){
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
