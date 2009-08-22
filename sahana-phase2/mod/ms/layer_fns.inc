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

// Add a new layer to a map
function shn_ms_add_layer()
{
    global $conf;
    if (0 == $conf['ms_configured']){
        add_error ('<b>'._t("MapServer module is not configured properly, please").' <a href="index.php?mod=ms&act=adm_default">'._t("Configure").'</a> '._t("before using").'</b>');
        return;
    }
    if ($_POST['form_status'] != 1) {
            _shn_ms_layer_form(NULL);
    } else {
        if ("" == $_POST['layerName']) {
            add_error ('<b>'._t("Layer Name cannot be blank").'</b>');
            _shn_ms_layer_form(NULL);
        } else {
            _shn_ms_add_layer ($_POST, $_FILES);
            global $global;
            global $conf;
            $map_name = $_POST['mapName'];
            $mod_root = $global['approot']."mod/ms";
            $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$map_name.".map";
            $map = ms_newMapObj($file_name);
            if ($map != NULL) {
                $img_url = _shn_ms_img_url($map);
            } else {
                $img_url = NULL;
            }
            if ($img_url == NULL) {
                $img_url = "";
            }
            echo "<table><tr><td valign='center' align='center'><img src=\"$img_url\" width='400' height='200' /></td></tr>";
            print '</table>';
            //echo "<tr><td>";
            //_shn_ms_layer_form($val);
            //echo "</td></tr></table>";
        }
    }
}


function _shn_ms_layer_form($val)
{
    $layer = $val;
    $map_name = $_POST['mapName'];
    if ($layer != NULL) {
        $_POST = NULL;
    }
    print '<h2>Add Layer to Map</h2>';
    print '<p>Here you can add a Shapefile as a Layer on the map.</p>';
    shn_form_fopen('add_layer',null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_t("Layer Details")); 
    print '<p><em><strong>'._t("Important").': </strong></em>'._t("System will only accept a .Zip file. This should contain .shp, .shx & .dbx files with the same filename as the .zip file.").'</p>';
    shn_form_hidden(array('form_status'=>1));
    $maps = _shn_ms_maps_array();
    shn_form_select($maps, _t("Select Map"), 'mapName', '', array("value"=>$map_name));
    if ($layer != NULL) {
        shn_form_hidden(array('edit'=>1));
    }
    shn_form_text(_t("Layer Name"), 'layerName', '"size=20"', array('req'=>true,'value'=>($layer->name)));
    shn_form_upload(_t("Upload Shapefile (Zip Archive)"),'shapeZip');
    // Default status should be ON
    $status = "1";
    if ($layer != NULL) {
        switch($layer->status) {
            case MS_ON:
                $status = "1";
                break;
            case MS_OFF:
                $status = "0";
                break;
        }
    }
    shn_form_select(array("1"=>_('ON'),"0"=>_('OFF')), 'Layer Status', 'status','', array("value"=>$status));
    $types = array("POLYGON"=>_('POLYGON'), "POINT"=>_('POINT'), "LINE"=>_('LINE'));
    $type = '';
    if ($layer != NULL) {
        switch($layer->type) {
            case MS_LAYER_POLYGON:
                $type = "POLYGON";
                break;
            case MS_LAYER_POINT:
                $type = "POINT";
                break;
            case MS_LAYER_LINE:
                $type = "LINE";
                break;
        }
    }
    shn_form_select($types, _t("Select Layer Type"), 'type', '', array("value"=>$type));
    
    if ($layer != NULL) {
        $projection = $layer->getProjection();
    }
    shn_form_text(_t("Projection"), 'projection', '"size=10"', array('value'=>$projection));
    
    $r = array();
    $g = array();
    $b = array();
    for ($i=0; $i<256; $i++) {
        $r[$i] = $i;
        $g[$i] = $i;
        $b[$i] = $i;
    }
    shn_form_label(_t("Set Foreground Color"));
    $fgc = NULL;
    $olc = NULL;
    //$bgc = NULL;
    if ($layer != NULL) {
        $class = $layer->getClass(0);
        $style = $class->getStyle(0);
        $fgc = $style->color;
        $olc = $style->outlinecolor;
        //$bgc = $style->backgroundcolor;
    }
    shn_form_select($r, 'Red', 'FGR', '', array("value"=>$fgc->red));
    shn_form_select($g, 'Green', 'FGG', '', array("value"=>$fgc->green));
    shn_form_select($b, 'Blue', 'FGB', '', array("value"=>$fgc->blue));

    shn_form_label(_("Set Outline Color"));
    shn_form_select($r, 'Red', 'OLR', '', array("value"=>$olc->red));
    shn_form_select($g, 'Green', 'OLG', '', array("value"=>$olc->green));
    shn_form_select($b, 'Blue', 'OLB', '', array("value"=>$olc->blue));
     
    //shn_form_label(_("Set Background Color"));
    //shn_form_select($r, 'Red', 'BGR', '', array("value"=>$bgc->red));
    //shn_form_select($g, 'Green', 'BGG', '', array("value"=>$bgc->green));
    //shn_form_select($b, 'Blue', 'BGB', '', array("value"=>$bgc->blue));
     
    shn_form_submit(_('Save'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_ms_add_layer($_var, $_file)
{
    //var_dump($_var);
    global $global;
    global $conf;
    // Initialize Layer Data
    $map_name = $_var['mapName'];
    if ($map_name == NULL) {
        add_error('<b>'._t("Map file name incorrect").'</b>');
    } else {
        $mod_root = $global['approot']."mod/ms";
        $shp_path = $mod_root."/".$conf['ms_SHAPE_PATH'];
        $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$map_name.".map";
        $layer_name = $_var['layerName'];
        $shp_zip = $shp_path."/".$_file['shapeZip']['name'];
        $data = rtrim($_file['shapeZip']['name'], ".zip");
        $shp_path_mod = $shp_path;
        if ($_var['status'] == 1) {
            $status = MS_ON;
        } else {
            $status = MS_OFF;
        }
        $type = -1;
        switch ($_var['type']) {
            case "POLYGON":
                $type = MS_LAYER_POLYGON;
                break;
            case "POINT":
                $type = MS_LAYER_POINT;
                break;
            case "LINE":
                $type = MS_LAYER_LINE;
                break;
        }
        $fgR = $_var['FGR'];
        $fgG = $_var['FGG'];
        $fgB = $_var['FGB'];
        $olR = $_var['OLR'];
        $olG = $_var['OLG'];
        $olB = $_var['OLB'];
        //$bgR = $_var['BAR'];
        //$bgG = $_var['BAG'];
        //$bgB = $_var['BAB'];
        
        $projection = $_var['projection'];

        // Create/Open Layer
        $map = ms_newMapObj($file_name);
        if ($map == NULL) {
            add_error('<b>'._t("Unable to open Map file").'</b>');
            return NULL;
        }
        if ($data != NULL) {
            $map->set("shapepath", $shp_path_mod);
        }
        $layer = $map->getLayerByName($layer_name);
        $class = NULL;
        $style = NULL;
        $new_layer = 0;
        if($layer != NULL && $_var['edit'] != 1) {
            add_error('<b>'._t("Layer already exists").'</b>');
            return $layer;
        } else if ($layer != NULL && $_var['edit'] == 1) {
            add_error('<b>'._t("Layer already exists").'</b>');
            return $layer;
        } else if ($layer == NULL) {
            $layer = ms_newLayerObj($map);
            $class = ms_newClassObj($layer);
            $style = ms_newStyleObj($class);
            $new_layer = 1;
        }
        $layer->set("name", $layer_name);
        if($data != NULL) {
            $layer->set("data", $data);
        }
        $layer->set("status", $status);
        $layer->set("type", $type);
        $class = $layer->getClass(0);
        $style = $class->getStyle(0); 
        $style->color->setRGB($fgR,$fgG,$fgB);
        $style->outlinecolor->setRGB($olR,$olG,$olB);
        //$style->backgroundcolor->setRGB($bgR,$bgG,$bgB);

        // Set Projection
        $layer->setProjection($projection);
                
        if(($_var['edit'] == 1 && $_file['shapeZip']['name'] != NULL) || $new_layer == 1) {
            switch($_file['shapeZip']['error']) {
                case 1:
                case 2:
                    add_error('<b>'._t("The uploaded file exceeds maximum upload size. Increase the value of upload_max_filesize in php.ini").'</b>');
                    return NULL;
                    break;
                case 3:
                    add_error('<b>'._t("The uploaded file was partially uploaded").'</b>');
                    return NULL;
                    break;
                case 4:
                    add_error('<b>'._t("No file was uploaded, you need a Zip file containing .shp, .shx and .dbx files").'</b>');
                    return NULL;
            }
            // Get the extension of the file
            $extensions=array('zip');
            $ext=end(explode('.',$_FILES['shapeZip']['name']));
            // Check for correct extension
            if(!in_array($ext,$extensions)){
                add_error('<b>.'.strtolower($ext).'</b> : '._t("Please upload a file with this extension").': ".zip"');
                _shn_ms_layer_form(NULL);
                return;
            }
            if (move_uploaded_file($_file['shapeZip']['tmp_name'],$shp_zip)) {
                _shn_ms_unzip($shp_zip, $shp_path);
                unlink($shp_zip) ;
            } else {
                add_error('<b>'._t("Unable to move the uploaded file to")." $shp_path</b>. "._t("Check Permissions."));
                unlink($_file['shapeZip']['tmp_name']);
                return NULL;
            }
        }
        $map->save($file_name);
        add_confirmation(_("Layer Added"));
        return NULL;
    }
    return NULL;
}

// Toggle to Enable/Disable display of a layer
function _shn_ms_toggle_layer($layer_name, $map_obj, $tog_stat)
{
    if ($map_obj != NULL) {
        $layer = $map_obj->getLayerByName($layer_name);
        $layer->set("status", $tog_stat);
        return $map_obj;
    } else {
        return NULL;
    }
}

function _shn_ms_get_layers($map)
{
    $nlayers = $map->numlayers;
    $layer = NULL;
    for($i=0; $i<$nlayers; $i++) {
        $layer[] = $map->getLayer($i);
    }
    return $layer;
}


function shn_ms_edit_layer()
{
    //var_dump($_POST);
    global $conf;
    if (0 == $conf['ms_configured']){
        add_error ('<b>'._t("MapServer module is not configured properly, please").' <a href="index.php?mod=ms&act=adm_default">'._t("Configure").'</a> '._t("before using").'</b>');
        return;
    }
    if (!isset($_POST['save'])) {
        _shn_ms_edit_layer_form();
    } else {
        if ($_POST['save'] == 1) {
            _shn_ms_edit_layer($_POST, $_FILE);
            _shn_ms_edit_layer_form();
        } else {
            _shn_ms_edit_layer_form();
        }
    }
}

function _shn_ms_edit_layer_form()
{
    global $global;
    global $conf;

    if (!isset($_POST['mapName'])) {
        shn_form_fopen("edit_layer",null,array('enctype'=>'enctype="multipart/form-data"'));
        shn_form_fsopen(_('Edit Layers'));
        $maps = _shn_ms_maps_array();
        shn_form_select($maps, _t("Select Map"), 'mapName', NULL, NULL);
        shn_form_submit(_('Next'));
        shn_form_fsclose();
        shn_form_fclose(); 
    } else if ($_POST['mapName'] != NULL && $_POST['layerName'] == NULL) {
        $mod_root = $global['approot']."mod/ms";
        $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$_POST['mapName'].".map";
        $img_url = NULL;
        $map = ms_newMapObj($file_name);
        shn_form_fopen("edit_layer",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'edit_layer'));
        shn_form_fsopen(_('Edit Layers'));
        _shn_ms_form_hidden(array('value'=>$_POST['mapName'], 'name'=>'mapName', 'id'=>'mapName'));
        if ($map != NULL) {
            $layers = _shn_ms_get_layers($map);
            if ($layers == NULL) {
                add_warning(_t("This map file does not contain layers."));
            }
            $layers_list;
            for ($i = 0; $i < sizeof($layers); $i++) {
                $layer = $layers[$i];
                $layers_list[$layer->name] = $layer->name;
                $layers_list[$layer->name]['id'] = $layer->name;
            }
            shn_form_select($layers_list, _t("Select Layer"), 'layerName', NULL, array('id'=>'layerName'));
            $img_url = _shn_ms_img_url($map);
        } else {
            add_error('<b>'._t("This is not a map file or it is corrupted.").'</b>');
        }
        echo "<table>";
        echo "<tr><td colspan='2'>";
        echo "<img  src='$img_url' width='400' height='200'/>";
        echo "</td></tr>";
        echo "<tr><td align='left'>";
        $val = NULL;
        $javascript = "window.location='index.php?mod=ms&act=edit_layer'";
        shn_form_button(_('Prev'), "onclick=\"$javascript\"");
        echo "</td><td align='right'>";
        shn_form_button(_('Next'), "onclick='document.edit_layer.submit()'");
        echo "</td></tr>";
        echo "</table>";
        shn_form_fsclose();
        shn_form_fclose();
    } else if ($_POST['mapName'] != NULL && $_POST['layerName'] != NULL) {
        $mod_root = $global['approot']."mod/ms";
        $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$_POST['mapName'].".map";
        $img_url = NULL;
        $map = ms_newMapObj($file_name);
        $layer = NULL;
        shn_form_fopen("edit_layer",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'edit_layer'));
        shn_form_fsopen(_t("Edit Layers")); 
        _shn_ms_form_hidden(array('value'=>$_POST['mapName'], 'name'=>'mapName', 'id'=>'mapName'));
        $img_url = NULL;
        $layerX = NULL;
        $statArr = NULL;
        $baseStat = MS_ON;
        if ($map != NULL) {
            $layers = _shn_ms_get_layers($map);
            if ($layers == NULL) {
                add_warning('<b>'._t("This map file does not contain any layers.").'</b>');
            }
            for ($i = 0; $i < sizeof($layers); $i++) {
                $layer = $layers[$i];
                if($layer->name != $_POST['layerName']) {
                    $statArr[] = $layer->status;
                    $layer->set("status", MS_OFF);
                } else {
                    $baseStat = $layer->status;
                    $layer->set("status", MS_ON);
                }
            }
            for ($i = 0; $i < sizeof($layers); $i++) {
                $layer = $layers[$i];
                if($layer->name != $_POST['layerName']) {
                    $layer->set("status", $statArr[$i]);
                } else {
                    $layer->set("status", $baseStat);
                }
            }
            $layerX = $map->getLayerByName($_POST['layerName']);
            $img_url = _shn_ms_img_url($map);
        } else {
            add_error('<b>'._t("This is not a map file or it is corrupted.").'</b>');
        }
        echo "<table>";
        echo "<tr><td valign='center' align='center' colspan='2'>";
        echo "<img  src='$img_url' width='400' height='200'/>";
        echo "</td></tr>";
        echo "<tr><td colspan='2'>";
        shn_form_text(_('Layer Name'), 'layerName', '"size=20"', array("value"=>($layerX->name))); 
        _shn_ms_form_hidden(array('value'=>1, 'name'=>'save', 'id'=>'save'));
        shn_form_upload(_t('Upload Shape File (Zip Archive)'),"shapeZip");
        
        if ($layerX != NULL) {
            switch($layerX->status) {
                case MS_ON:
                    $status = "1";
                    break;
                case MS_OFF:
                    $status = "0";
                    break;
            }
        }
        shn_form_select(array("1"=>_('ON'),"0"=>_('OFF')), 'Layer Status', 'status','', array("value"=>$status));
        
        $types = array("POLYGON"=>_('POLYGON'),"POINT"=>_('POINT'), "LINE"=>_('LINE'));
        $type = '';
        if ($layerX != NULL) {
            switch($layerX->type) {
                case MS_LAYER_POLYGON:
                    $type = "POLYGON";
                    break;
                case MS_LAYER_POINT:
                    $type = "POINT";
                    break;
                case MS_LAYER_LINE:
                    $type = "LINE";
                    break;
            }
        }
        shn_form_select($types, _t("Select Layer Type"), 'type', '', array("value"=>$type));
        
        if ($layerX != NULL) {
            $projection = $layerX->getProjection();
        }
        shn_form_text(_t("Projection"), 'projection', '"size=10"', array('value'=>$projection));
        
        $r = array();
        $g = array();
        $b = array();
        for ($i=0; $i<256; $i++) {
            $r[$i] = $i;
            $g[$i] = $i;
            $b[$i] = $i;
        }
        shn_form_label(_t("Set Foreground Color"));
        $fgc = NULL;
        $olc = NULL;
        //$bgc = NULL;
        if ($layerX != NULL) {
            $class = $layerX->getClass(0);
            $style = $class->getStyle(0);
            $fgc = $style->color;
            $olc = $style->outlinecolor;
            //$bgc = $style->backgroundcolor;
        }
        shn_form_select($r, 'Red', 'FGR', '', array("value"=>$fgc->red));
        shn_form_select($g, 'Green', 'FGG', '', array("value"=>$fgc->green));
        shn_form_select($b, 'Blue', 'FGB', '', array("value"=>$fgc->blue));

        shn_form_label(_("Set Outline Color"));
        shn_form_select($r, 'Red', 'OLR', '', array("value"=>$olc->red));
        shn_form_select($g, 'Green', 'OLG', '', array("value"=>$olc->green));
        shn_form_select($b, 'Blue', 'OLB', '', array("value"=>$olc->blue));

        //shn_form_label(_("Set Background Color"));
        //shn_form_select($r, 'Red', 'BGR', '', array("value"=>$bgc->red));
        //shn_form_select($g, 'Green', 'BGG', '', array("value"=>$bgc->green));
        //shn_form_select($b, 'Blue', 'BGB', '', array("value"=>$bgc->blue));
     
        echo "</td></tr>";
        echo "<tr><td align='left'>";
        $val = NULL;
        $javascript = "document.getElementById('layerName').setAttribute('value','$val');
        document.getElementById('save').setAttribute('value','$val');
        document.edit_layer.submit();";
        shn_form_button(_('Prev'), "onclick=\"$javascript\"");
        echo "</td><td align='right'>";
        shn_form_button(_('Save'), "onclick='document.edit_layer.submit()'");
        echo "</td></tr>";
        echo "</table>";
        shn_form_fsclose();
        shn_form_fclose();
    }
}

function _shn_ms_edit_layer($_var, $_file)
{
    global $global;
    global $conf;

    $map_name = $_var['mapName'];
    if ($map_name == NULL) {
        add_error('<b>'._t("Map file name incorrect").'</b>');
    } else {
        $mod_root = $global['approot']."mod/ms";
        $shp_path = $mod_root."/".$conf['ms_SHAPE_PATH'];
        $file_name = $mod_root."/".$conf['ms_MAP_PATH']."/".$map_name.".map";
        $layer_name = $_var['layerName'];
        $shp_zip = $shp_path."/".$_file['shapeZip']['name'];
        $data = rtrim($_file['shapeZip']['name'], ".zip");
        if ($data != NULL) {
            //$shp_path_mod = $shp_path."/".$data;
            $shp_path_mod = $shp_path;
        } else {
            $shp_path_mod = NULL;
        }
        if ($_var['status'] == 1) {
            $status = MS_ON;
        } else {
            $status = MS_OFF;
        }
        $type = -1;
        switch ($_var['type']) {
            case "POLYGON":
                $type = MS_LAYER_POLYGON;
                break;
            case "POINT":
                $type = MS_LAYER_POINT;
                break;
            case "LINE":
                $type = MS_LAYER_LINE;
                break;
        }
        $fgR = $_var['FGR'];
        $fgG = $_var['FGG'];
        $fgB = $_var['FGB'];
        $olR = $_var['OLR'];
        $olG = $_var['OLG'];
        $olB = $_var['OLB'];
        //$bgR = $_var['BAR'];
        //$bgG = $_var['BAG'];
        //$bgB = $_var['BAB'];
        
        $projection = $_var['projection'];

        // Create/Open Layer
        $map = ms_newMapObj($file_name);
        if ($map == NULL) { 
            add_error('<b>'._t("This is not a map file or it is corrupted.").'</b>');
            return;
        }
        if ($shape_path_mod != NULL) {
            $map->set("shapepath", $shp_path_mod);
        }
        $layer = $map->getLayerByName($layer_name);
        $layer->set("name", $layer_name);
        if($data != NULL) {
            $layer->set("data", $data);
        }
        $layer->set("status", $status);
        $layer->set("type", $type);
        $class = $layer->getClass(0);
        $style = $class->getStyle(0); 
        $style->color->setRGB($fgR,$fgG,$fgB);
        $style->outlinecolor->setRGB($olR,$olG,$olB);
        //$style->backgroundcolor->setRGB($bgR,$bgG,$bgB);
      
        // Set Projection
        $layer->setProjection($projection);

        if($_file['shapeZip']['name'] != NULL) {
            switch($_file['shapeZip']['error']) {
                case 1:
                case 2:
                    add_error('<b>'._t("The uploaded file exceeds maximum upload size. Increase the value of upload_max_filesize in php.ini").'</b>');
                    _shn_ms_layer_form(NULL);
                    return;
                    break;
                case 3:
                    add_error('<b>'._t("The uploaded file was partially uploaded").'</b>');
                    _shn_ms_layer_form(NULL);
                    return;
                    break;
                case 4:
                    add_error('<b>'._t("No file was uploaded, you need a .Zip file containing .shp, .shx and .dbx files").'</b>');
                    _shn_ms_layer_form(NULL);
                    return;
            }
            // Get the extension of the file
            $extensions=array('zip');
            $ext=end(explode('.',$_FILES['shapeZip']['name']));
            // Check for correct extension
            if(!in_array($ext,$extensions)){
                add_error('<b>'.strtoupper($ext)."</b> : "._t("Please upload a file with this extension").': ".zip"');
                _shn_ms_layer_form(NULL);
                return;
            }
            //if ($_file['shapeZip']['type'] != "application/zip") {
            //    add_error(_("The uploaded file was not a Zip file"));
            //    _shn_ms_layer_form(NULL);
            //    return;
            //}
            if (move_uploaded_file($_file['shapeZip']['tmp_name'],$shp_zip)) {
                _shn_ms_unzip($shp_zip, $shp_path);
                unlink($shp_zip);
            } else {
                add_error('<b>'._t("Unable to move the uploaded file to")." $shp_path</b>. "._t("Check Permissions."));
                unlink($_file['shapeZip']['tmp_name']);
                _shn_ms_layer_form(NULL);
                return;
            }
        }
        $map->save($file_name);
        return;
    }
    return NULL;
}


