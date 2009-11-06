<?php

/**Admin Module for MapServer
*
* PHP version 5
* 
* @author       Hasitha Anjana <hasianjana@gmail.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @module      MapServer
* @version     $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

// PHP 5.2.0+ or PECL:
function _shn_ms_unzip($src, $dst)
{

    $zip = new ZipArchive;
    if ($zip->open($src) == TRUE) {
        $zip->extractTo($dst);
        $zip->close();
        return TRUE;
    } else {
        return FALSE;
    }
}

function _shn_ms_draw_map($map)
{
    $imgObj = $map->draw();
    $img_url = $imgObj->saveWebImage();
    echo "<img src='$img_url'/>";
}

function _shn_ms_img_url($map)
{
    if ($map == NULL) {
        return NULL;
    }
    $imgObj = $map->draw();
    if ($imgObj == NULL) {
        add_error(_t("Map file seems to be corrupted"));
        return NULL;
    }
    $img_url = $imgObj->saveWebImage();
    return $img_url;
}

function _shn_ms_remove_file($file)
{
    unlink($file);
}

function _shn_ms_form_hidden($hidden)
{
    echo "<input type=\"hidden\" ";
    foreach ($hidden as $name=>$value) {
        echo $name."=\"".$value."\" ";
    }
    echo " />";
}

function _shn_ms_maps_array()
{
    global $global;
    global $conf;
    $map_dir = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH'];
    $d = dir($map_dir);
    $maps = NULL;
    while (false !== ($entry = $d->read())) {
        if ($entry != "TEMPLATE0.map" && $entry != "." && $entry != ".." && $entry[0] != '.') {
            $maps[substr($entry, 0, -4)] = substr($entry, 0, -4);
        }
    }
    return $maps;
}


function _shn_ms_map_scripts_array($offset, $len, &$count, &$has_more)
{
    global $global;
    global $conf;
    $map_dir = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH'];
    $d = dir($map_dir);
    $maps = NULL;
    $i = 0;
    while (FALSE !== ($has_more=($entry = $d->read()))) {
        if ($i>=$offset && $i<$len+$offset) {
            if ($entry != "TEMPLATE0.map" && $entry != "." && $entry != ".." && $entry[0] != '.') {
                $maps[] = $entry;
                $count++;
                $i++;
            }
        } else if($i >= $len+$offset) {
            $has_more = TRUE;
            break;
        } else {
            $i++;
        }
    }
    return $maps;
}

function _shn_ms_search_map($file)
{
    global $global;
    global $conf;
    $map_dir = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH'];
    $d = dir($map_dir);
    while (false !== ($entry = $d->read())) {
        if ($entry == $file) {
            return TRUE;
        }
    }
    return FALSE;
}

function _shn_ms_regsearch_map($file_patern)
{
    global $global;
    global $conf;
    $map_dir = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH'];
    $d = dir($map_dir);
    $inout = NULL;
    while (false !== ($entry = $d->read())) {
        $input .= $entry." ";
    }
    $stat = preg_match_all($file_patern, $input, $matches);
    return $matches;
}

?>

