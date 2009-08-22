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

include_once $global['approot']."/mod/ms/common_fns.inc";

function _shn_ms_create_map ($_var, $map_name)
{
    //var_dump($_var);
    global $conf;
    global $global;
    if ($_var != NULL) {
        $map_name = $_var['mapName'];    
        $mod_root = $global['approot'].'/mod/ms';
        $img_path = $global['approot'].'/www/'.$conf['ms_IMG_PATH'];
        $shp_path = $mod_root.'/'.$conf['ms_SHAPE_PATH'];
        $file_name = $mod_root.'/'.$conf['ms_MAP_PATH']."/".$map_name.'.map';
        $template_file =  $mod_root.'/'.$conf['ms_BASE_MAP'];
        $file_name = $mod_root.'/'.$conf['ms_MAP_PATH']."/".$map_name.'.map';
        if (isset($_var['oldName'])) {
            if ($_var['oldName'] != $_var['mapName']) {
                $old_file_name = $mod_root.'/'.$conf['ms_MAP_PATH'].'/'.$_var['oldName'].'.map';
            } else {
                $old_file_name = NULL;
            }
        } else {
            $old_file_name = NULL;
        }
        $size_x = $_var['sizeX'];
        $size_y = $_var['sizeY'];
        $projection = $_var['projection'];
        $img_clr_r = $_var['clrR'];
        $img_clr_g = $_var['clrG'];
        $img_clr_b = $_var['clrB'];
        $img_type = $_var['imgType']; 
        $img_mimetype = "image/".$img_type;
        $img_driver = "GD/".strtoupper($img_type);
        //$img_trans = isset($_var['imgTrans'])?TRUE:FALSE;
        $img_minX = $_var['imgExtMinX'];
        $img_minY = $_var['imgExtMinY'];
        $img_maxX = $_var['imgExtMaxX'];
        $img_maxY = $_var['imgExtMaxY'];
    
        $map = ms_newMapObj($file_name);
        $old_map = ms_newMapObj($old_file_name);
        if ($map == NULL) {
            $map = ms_newMapObj($template_file);
            $map->set("shapepath", $shp_path);
        }
        $map->set("name", $map_name);
        $map->setSize($size_x,$size_y);
        if (($img_minX > $img_maxX) || ($img_minY > $img_maxY) || ($img_minX == $img_maxX) || ($img_minY == $img_maxY)) {
            add_error(_t('<b>'."Invalid extents provided, unable to create a Map file".'.</b>'));
            return;
        }
        $map->setExtent($img_minX, $img_minY, $img_maxX, $img_maxY);
        // Set image color
        $map->imagecolor->setRGB($img_clr_r, $img_clr_g, $img_clr_b);
        // Set output parameters
        $map->outputformat->set("name", $map_name);
        $map->outputformat->set("extension", $img_type);
        $map->outputformat->set("mimetype", $img_mimetype);
        $map->outputformat->setOption("OUTPUT_TYPE", "RASTER");
        $map->outputformat->set("driver", $img_driver);
        //$map->outputformat->set("transparent", $img_trans);
        
        // Set Projection
        $map->setProjection($projection);
        
        if ($_var['layerSave'] == 1) {
            //nlayers is 0 if map is being renamed, then we have to copy
            //layers of the original map
            $layers = _shn_ms_get_layers($map);
            $nlayers = $map->numlayers;
            if ($nlayers == 0) {
                $old_nlayers = $old_map->numlayers;
                $old_layers = _shn_ms_get_layers($old_map);
                for($i=0; $i<$old_nlayers; $i++) {
                    $layer = ms_newLayerObj($map, $old_layers[$i]);
                    (isset($_var[$layer->name]))?$layer->set("status", 1):$layer->set("status", 0);
                }
            }
            for ($i=0; $i<$nlayers; $i++) {
                $layer = $layers[$i];
                (isset($_var[$layer->name]))?$layer->set("status", 1):$layer->set("status", 0);
            }
        }
        /** Prepare webObj **/
        $map->web->set("imagepath", $img_path);
        $map->web->set("imageurl", $conf['ms_IMG_PATH']);
        $map->save($file_name);
        add_confirmation(_t("Map created/modified"));
        return $map;
    } else {
        $mod_root = $global['approot']."/mod/ms";
        $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$map_name.".map";
        $map = ms_newMapObj($file_name);
        return $map;
    }
}

function shn_ms_create_map()
{
    //var_dump($_POST);
    global $conf;
    if (0 == $conf['ms_configured']){
        add_error ('<b>'._t("MapServer module is not configured properly, please").' <a href="index.php?mod=ms&act=adm_default">'._t("Configure").'</a> '._t("before using").'</b>');
        return;
    }
    if (isset($_GET['mapName'])) {
        $map = _shn_ms_create_map (NULL, $_GET['mapName']);
        if ($map != NULL) {
            _shn_ms_create_map_form($map);
        } else {
            add_error(_t("Requested map does not exist or is corrupted"));
        }
    } else if(isset($_POST['mapName'])) {
        if ($_POST['save'] == 1) {
            if (_shn_ms_search_map($_POST['mapName'].".map") == TRUE) {
                $map = _shn_ms_create_map (NULL, $_POST['mapName']);
                if ($map != NULL) {
                    if ($_POST['forceSave'] != 1) {
                        add_confirmation("Map already exists, you may Edit it.");
                        _shn_ms_create_map_form($map);
                    } else {
                        $map = _shn_ms_create_map ($_POST, NULL);
                        _shn_ms_create_map_form($map);
                    }
                } else {
                    _shn_ms_create_map_form(NULL);
                }
            } else {
                $map = _shn_ms_create_map ($_POST, NULL);
                _shn_ms_create_map_form($map);
            }
        } else {
            _shn_ms_create_map_form (NULL);
        }
    } else {
        _shn_ms_create_map_form(NULL);
    }
}

function _shn_ms_create_map_form($map)
{
    $map_name = NULL;
    $size_x = 100;
    $size_y = 100;
    $img_type = NULL;
    //$img_trans = 0;
    $mr=0;$mg=0;$mb=0;
    $min_x=0; $min_y=0; $max_x=100; $max_y=100;
    $layer_arr = NULL;
    $img_url = NULL;
    if ($map != NULL) {
        $map_name = $map->name;
        $size_x = $map->width;
        $size_y = $map->height;
        $projection = $map->getProjection();
        $img_type = $map->outputformat->extension;
        //$img_trans = $map->outputformat->transparent;
        $mr = $map->imagecolor->red;
        $mg = $map->imagecolor->green;
        $mb = $map->imagecolor->blue;
        $min_x = $map->extent->minx;
        $min_y = $map->extent->miny;
        $max_x = $map->extent->maxx;
        $max_y = $map->extent->maxy;
        $layer_arr = _shn_ms_get_layers($map);
        $img_url = _shn_ms_img_url($map);
    }
    if ($_POST['save'] == 1) {
        $fc = array('forceSave'=>1);
    } else {
        if (isset($_GET['mapName'])) {
            $fc = array('forceSave'=>1);
        } else {
            $fc = NULL;
        }
    }
    if (isset($_GET['mapName'])) {
        $om = array('oldName'=>$_GET['mapName']);
    } else if (isset($_POST['mapName'])) {
        $om = array('oldName'=>$_POST['mapName']);
    } else {
        $om = NULL;
    }
    $_POST = NULL;
    $_GET = NULL;
    shn_form_fopen("create_map",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_t("Map Details"));
    echo "<table>";
    echo "<tr><td valign='center' align='center' colspan='2'>";
    echo "<img  src='$img_url' width='400' height='200'/>";
    echo "</td></tr>";
    echo "<tr><td>";
    shn_form_hidden(array('save'=>1));
    if ($fc != NULL) {
        shn_form_hidden($fc);
    }
    if ($om != NULL) {
        shn_form_hidden(array('oldName'=>$map_name));
    }
    shn_form_text(_t("Map Name"), 'mapName', '"size=20"', array('req'=>true,'value'=>$map_name));
    shn_form_text(_t("Map Width"), 'sizeX', '"size=8"', array('value'=>$size_x));
    shn_form_text(_t("Map Height"), 'sizeY', '"size=8"', array('value'=>$size_y));
    shn_form_select(array("png"=>_('PNG'),"jpeg"=>_('JPG')),'Select Map Image Type',"imgType",'',array('value'=>$img_type));
    if ($img_trans) {
        $text_opts = "checked";
    } else {
        $text_opts = NULL;
    }
    //shn_form_checkbox("Set Transparent", "imgTrans", $text_opts, $extra_opts=NULL);
    shn_form_text(_t("Projection"), 'projection', '"size=10"', array('value'=>$projection));
    shn_form_label(_t("Set Map Background Color"));
    $r = array();
    $g = array();
    $b = array();
    for ($i=0; $i<256; $i++) {
        $r[$i] = $i;
        $g[$i] = $i;
        $b[$i] = $i;
    }
    shn_form_select($r, 'Red', 'clrR', '', array("value"=>$mr)); 
    shn_form_select($g, 'Green', 'clrG', '', array('value'=>$mg));
    shn_form_select($b, 'Blue', 'clrB', '', array('value'=>$mb));
    shn_form_label(_t("Set Extent"));
    shn_form_text(_t("Min X"), 'imgExtMinX', '"10"', array('value'=>$min_x));
    shn_form_text(_t("Min Y"), 'imgExtMinY', '"10"', array('value'=>$min_y));    
    shn_form_text(_t("Max X"), 'imgExtMaxX', '"10"', array('value'=>$max_x));  
    shn_form_text(_t("Max Y"), 'imgExtMaxY', '"10"', array('value'=>$max_y));
    if ($layer_arr != NULL) {
        shn_form_label(_t("Enable/Disable Layers"));	
        shn_form_hidden(array("layerSave"=>1));
        $arr_size = sizeof($layer_arr);
        for ($i=0; $i<$arr_size; $i++) {
            $layer = $layer_arr[$i];
            if ($layer->status == 1) {
                $text_opts = "checked";
            } else {
                $text_opts = NULL;
            }
            shn_form_checkbox($layer->name, $layer->name, $text_opts, array("value"=>$layer->status));
        }
    }
    shn_form_submit(_t("Save"));
    echo "</td></tr>";
    echo "</table>";
    shn_form_fsclose();    
    shn_form_fclose();
}

function shn_ms_list_maps($_var)
{
    global $global;
    global $conf;
    if (0 == $conf['ms_configured']){
        add_error ('<b>'._t("MapServer module is not configured properly, please").' <a href="index.php?mod=ms&act=adm_default">'._t("Configure").'</a> '._t("before using").'</b>');
        return;
    }
    if (isset($_POST['delete'])) {
        if ($_POST['delete'] != NULL) {
            $map_file = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH']."/".$_POST['delete'];
            unlink($map_file);
        }
    }
    if (isset($_POST['view'])) {
        if ($_POST['view'] != NULL) {
            $map_file = $global['approot']."/mod/ms/".$conf['ms_MAP_PATH']."/".$_POST['view'];
            $map = ms_newMapObj($map_file);
            if ($map != NULL) {
                $img_url = _shn_ms_img_url($map);
                if ($img_url == NULL) {
                    $img_url = $conf['ms_IMG_PATH']."/white.png";
                }
            } else {
                $img_url = $conf['ms_IMG_PATH']."/white.png";
            }
        } else {
            $img_url = $conf['ms_IMG_PATH']."/white.png";
        }
    } else {
        $img_url = $conf['ms_IMG_PATH']."/white.png";
    }
    shn_form_fopen("list_maps", NULL, array('enctype'=>'enctype="multipart/form-data"','id'=>'list_maps'));
    shn_form_fsopen(_('Manage Maps'));
    $has_more = TRUE;
    $offset = 0;
    $view_map = 0;
    if (isset($_POST['length'])) {
        $length = $_POST['length'];
    } else {
        $length = 5;
    }
    if (isset($_POST['offset'])) {
        $offset = $_POST['offset'];
        $poffset = $offset - $length;
        if ($poffset < 0) {
            $poffset = 0;
        }
        $noffset = $offset + $length;
    } else {
        $poffset = 0;
        $noffset = $length;
    }
    for ($i=5; $i<50; $i++) {
        $plen[$i] = $i;  
    }
    _shn_ms_form_hidden(array('name'=>'offset', 'value'=>$offset, 'id'=>'offset')); 
    _shn_ms_form_hidden(array('name'=>'delete', 'value'=>NULL, 'id'=>'delete'));
    _shn_ms_form_hidden(array('name'=>'view', 'value'=>NULL, 'id'=>'view'));
    print '<table>';
    print '<tr><td><b>#<b/></td><td><b>'._t("Map Name").'</b></td><td><b>'._t("edit").' | '._t("view").' | '._t("delete").'</b></td>';
    $map_scripts = _shn_ms_map_scripts_array($offset, $length, $count, $has_more);
    $row_span = $count + 2;
    echo "<td id='imgBox' rowspan='".$row_span."'><img width='400' height='200' src='$img_url'/></td></tr>";
    _shn_ms_gen_maps_table($map_scripts, $offset); 
    if ($has_more) {
        echo "<tr>";
        echo "<td colspan='2' align='left'>";
        echo "<a href=\"javascript:document.getElementById('offset').setAttribute('value','$poffset');document.list_maps.submit()\">Prev</a>";
        echo "</td>";
        //echo "<td></td>";
        echo "<td align='right'>";
        echo "<a href=\"javascript:document.getElementById('offset').setAttribute('value','$noffset');document.list_maps.submit()\">Next</a>";
        echo "</td></tr>";
    } else {
        $noffset = $offset;
        echo "<tr>";
        echo "<td colspan='2' align='left'>";
        echo "<a href=\"javascript:document.getElementById('offset').setAttribute('value','$poffset');document.list_maps.submit()\">Prev</a>";
        //echo "</td>";
        //echo "<td>";
        echo "</td>";
        echo "<td align='right'>";
        echo "<a href=\"javascript:document.getElementById('offset').setAttribute('value','$noffset');document.list_maps.submit()\">Next</a>";
        echo "</td></tr>";
    }
    echo "<tr><td align='left' colspan='4'>";
    shn_form_select($plen, 'Set List Length', 'length', NULL, NULL);
    echo "</td><tr>";
    echo "</table>";

    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_ms_gen_maps_table($list, $offset)
{
    $edit_href = "index.php?mod=ms&act=create_map";
    $count = $offset;
    for ($i=0; $i<sizeof($list); $i++) {
        $entry = $list[$i];
        $count ++;
        $mName = substr($entry, 0, -4);
        echo "<tr><td>$count</td><td>$mName</td><td align='center'><a id='$mName' href='$edit_href&mapName=$mName'>edit</a>
        | <a id='$mName' href=\"javascript:document.getElementById('view').setAttribute('value','$entry');document.list_maps.submit()\">view</a> 
        | <a id='$mName' href=\"javascript:document.getElementById('delete').setAttribute('value', '$entry');document.list_maps.submit()\">delete</a></td></tr>";
    }
}

// Currently unused
function shn_ms_search_map()
{
    //var_dump($_POST);
    global $global;
    global $conf;
    if (0 == $conf['ms_configured']){
        add_error ('<b>'._t("MapServer module is not configured properly, please").' <a href="index.php?mod=ms&act=adm_default">'._t("Configure").'</a> '._t("before using").'</b>');
        return;
    }
    $name = $_POST['mapName'];
    $mod_root = $global['approot']."/mod/ms";
    $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$name.".map";
    $edit_href = "index.php?mod=ms&act=create_map";
    $delete_href = "index.php?mpd=ms&act=search_map";
    $view_href = "index.php?mod=ms&act=search_map";
  
    shn_form_fopen("search_map", NULL, array('enctype'=>'enctype="multipart/form-data"','id'=>'search_map'));
    shn_form_fsopen(_('Search Map'));
    echo "<table><tr><td colspan='2'>";
    shn_form_text(_t("Map Name"), "mapName", "23");
    _shn_ms_form_hidden(array('id'=>'delete', 'value'=>'', 'name'=>'delete'));
    echo "</td><td>";
    shn_form_submit(_t("Search"));
    echo "</td></tr>";
    //echo "</table>";
    shn_form_hidden(array('doSearch'=>'1'));
    if ($_POST['doSearch'] == 1) {
        if ($_POST['delete'] != NULL) {
            _shn_ms_remove_file($file_name);
        }
        if (_shn_ms_search_map($_POST['mapName'].".map") == TRUE) {
            $map = ms_newMapObj($file_name);
            if ($map != NULL) {
                $img_url = _shn_ms_img_url($map);
            } else {
                $img_url = NULL;
            }
            echo "<tr><td align='center' colspan='3'><img  src='$img_url' width='400' height='200'/></td></tr>";
            echo "<tr><td><b>Map Name</b></td><td align='center'><b>edit</b></td><td align='center'><b>delete</b></td></tr>";
            echo "<tr><td>$name</td>";
            echo "<td align='center'>";
            echo "<a id='$name' href='$edit_href&mapName=$name'>edit</a></td>";
            $entry = $name.'.map';
            echo "<td align='center'><a href=\"javascript:document.getElementById('delete').setAttribute('value','$entry');document.search_map.submit()\">delete</a></td>";
            echo "</tr>";
        } else if($_POST['delete'] != NULL) {
            echo "<tr><td colspan='3'><b>Deleted ".$_POST['delete']."</b><br/></td></tr>";
        } else {
            echo "<tr><td colspan='3'><b>Map file not found</b></td></tr>";
        }
    }
    echo "</table>";
    shn_form_fsclose();
    shn_form_fclose();
}


