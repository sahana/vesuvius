<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    Sahana - http://sahana.lk/
* @library      GIS
* @version     $Id: wms.inc,v 1.17 2008-05-01 20:05:01 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class wms implements layer{

    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('WMS'));
        shn_form_fsopen(_t('INFO'));
        echo _t("<p>Sahana can make use of Maps from servers using the <a href='http://www.opengeospatial.org/standards/wms' target=_blank>WMS (Web Map Service)</a> standard </p>");
        echo _t("<p>Enable WMS Layers by selecting the checkbox option below.</p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_wms_enable']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable WMS layers'),'wms_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if ($conf['gis_ol_wms_enable']==1){
            $projections_help=_t("Coordinate system used to display the data, as defined by <a href=\"http://www.epsg.org\" target=_blank>European Petroleum Survey Group</a>.<br><a href=\"http://trac.openlayers.org/wiki/SphericalMercator\">EPSG:900913</a> is the default as this provides full compatibility with the other layers.<br>Some WMS servers may not support this & hence need a different value (such as EPSG:4326 for WGS84).<br>If this is the case then <b>all other base layers are disabled</b> to avoid problems when moving between different layer types!");
            $projections = array('EPSG:900913','EPSG:4326',_t('Custom'));
            shn_form_fsopen(_t('PROJECTION'));
            $projections_select = '0';
            if ("1"==$conf["gis_ol_wms_projections"]) {
                $projections_select = '1';
            } else if ("2"==$conf["gis_ol_wms_projections"]) {
                $projections_select = '2';
            }
            shn_form_select($projections,_t('Projection'),'gis_ol_wms_projections',null,array('value'=>$projections_select,"help"=>$projections_help));
            if (2==$conf["gis_ol_wms_projections"]){
                $projection_help=_t("Coordinate system used to display the data, as defined by <a href=\"http://www.epsg.org\" target=_blank>European Petroleum Survey Group</a>.<br>Format should be EPSG:xxxx.<br>A custom EPSGxxxx.js file also needs uploading to www/res/OpenLayers/defs. Contents for this can be found from <a href=\"http://spatialreference.org\" target=_blank>spatialreference.org</a><br>NB Because a Custom projection is being used <b>all other base layers are disabled</b> to avoid problems when moving between different layer types!");
                $maxExtent_help=_t("The number of units required to reach: Left, Bottom, Right, Top");
                $maxResolution_help=_t("How many units per pixel");
                $units_help=_t("The units in which the measurements apply (e.g. 'm', 'degrees' or 'usfeet')");
                shn_form_text(_t('Projection'),'gis_ol_wms_projection',null,array('req'=>true,'value'=>$conf['gis_ol_wms_projection'],"help"=>$projection_help));
                shn_form_text(_t('maxExtent'),'gis_ol_wms_maxExtent',null,array('req'=>true,'value'=>$conf['gis_ol_wms_maxExtent'],"help"=>$maxExtent_help));
                shn_form_text(_t('maxResolution'),'gis_ol_wms_maxResolution',null,array('req'=>true,'value'=>$conf['gis_ol_wms_maxResolution'],"help"=>$maxResolution_help));
                shn_form_text(_t('units'),'gis_ol_wms_units',null,array('req'=>true,'value'=>$conf['gis_ol_wms_units'],"help"=>$units_help));
            }
            shn_form_fsclose();
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of WMS layers'),'gis_ol_wms','size=2 maxlength=2',array('value'=>$conf['gis_ol_wms']));
            shn_form_fsclose();
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $url_help=_t("Address of the WMS service - without Options (mandatory)");
            $type_help=_t("Only one 'Base' layer can be displayed at a time.<br>Multiple 'Overlay' layers can be displayed over the top.");
            $map_help=_t("Mapfile to use with MapServer<br>e.g. '/var/www/maps/maps/example.map' (optional)");
            $layers_help=_t("Comma-separated list of layer(s) at this WMS URL to enable (mandatory).<br>NB If you wish to be able to switch layers on/off independently then you should define a separate WMS layer for each one.");
            $format_help=_t("Image format (optional).<br>e.g. 'image/png'");
            $transparency_help=_t("usually 'false' for a Base layer & 'true' for an overlay layer");
            for ($i=0; $i<$conf['gis_ol_wms']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Name'),'gis_ol_wms_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_name'],"help"=>$name_help));
                shn_form_text(_t('Description'),'gis_ol_wms_'.$j.'_description','size=60',array('value'=>$conf['gis_ol_wms_'.$j.'_description'],"help"=>$description_help));
                shn_form_text(_t('URL'),'gis_ol_wms_'.$j.'_url','size=60',array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_url'],"help"=>$url_help));
                $types = array(_t('base'),_t('overlay'));
                $type_select = '0';
                if ('1'==$conf['gis_ol_wms_'.$j.'_type']) {
                    $type_select = '1';
                }
                shn_form_select($types,_t('Type'),'gis_ol_wms_'.$j.'_type',null,array('value'=>$type_select,"help"=>$type_help));
                shn_form_text(_t('Map'),'gis_ol_wms_'.$j.'_map',null,array('value'=>$conf['gis_ol_wms_'.$j.'_map'],"help"=>$map_help));
                shn_form_text(_t('Layers'),'gis_ol_wms_'.$j.'_layers',null,array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_layers'],"help"=>$layers_help));
                shn_form_text(_t('Format'),'gis_ol_wms_'.$j.'_format',null,array('value'=>$conf['gis_ol_wms_'.$j.'_format'],"help"=>$format_help));
                $transparencies = array(_t('false'),_t('true'));
                $transparency_select = '0';
                if ('1'==$conf['gis_ol_wms_'.$j.'_type']) {
                    $transparency_select = '1';
                }
                shn_form_select($transparencies,_t('Transparency'),'gis_ol_wms_'.$j.'_transparency',null,array('value'=>$transparency_select));
                shn_form_fsclose();
            }
        }
        shn_form_fsclose();
    }

    function commit_values()
    {
        global $global;
        global $conf;
        $db = $global['db'];                  
        if ("0"==$_POST['gis_ol_wms_projections']) {
            $projection = 'EPSG:900913';
            $maxExtent = '-20037508, -20037508, 20037508, 20037508.34';
            $maxResolution = '156543.0339';
            $units = 'm';
        } else if ("1"==$_POST['gis_ol_wms_projections']) {
            $projection = 'EPSG:4326';
            $maxExtent = '-180,-90,180,90';
            $maxResolution = '1.40625';
            $units = 'degrees';
        } else {
            $projection = $_POST['gis_ol_wms_projection'];
            $maxExtent = $_POST['gis_ol_wms_maxExtent'];
            $maxResolution = $_POST['gis_ol_wms_maxResolution'];
            $units = $_POST['gis_ol_wms_units'];
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_projection' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$projection' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_projection'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_projection','$projection')";
            $db->Execute($insert);
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_projections' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '{$_POST['gis_ol_wms_projections']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_projections'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_projections','{$_POST['gis_ol_wms_projections']}')";
            $db->Execute($insert);
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_maxExtent' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$maxExtent' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_maxExtent'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_maxExtent','$maxExtent')";
            $db->Execute($insert);
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_maxResolution' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$maxResolution' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_maxResolution'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_maxResolution','$maxResolution')";
            $db->Execute($insert);
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_units' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$units' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_units'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_units','$units')";
            $db->Execute($insert);
        }
        for ($i=0; $i<$conf['gis_ol_wms']; $i++) {
            $j=$i+1;
            $description = 'gis_ol_wms_'.$j.'_description';
            if(!null==$_POST[$description]){
                $query = "SELECT * FROM config WHERE confkey='$description' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$description]}' WHERE module_id = 'admin' AND confkey = '$description'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$description','{$_POST[$description]}')";
                    $db->Execute($insert);
                }
            }
            $name = 'gis_ol_wms_'.$j.'_name';
            if(!null==$_POST[$name]){
                $query = "SELECT * FROM config WHERE confkey='$name' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$name]}' WHERE module_id = 'admin' AND confkey = '$name'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$name','{$_POST[$name]}')";
                    $db->Execute($insert);
                }
            }
            $type = 'gis_ol_wms_'.$j.'_type';
            $query = "SELECT * FROM config WHERE confkey='$type' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$type]}' WHERE module_id = 'admin' AND confkey = '$type'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$type','{$_POST[$type]}')";
                $db->Execute($insert);
            }
            $url = 'gis_ol_wms_'.$j.'_url';
            if(!null==$_POST[$url]){
                $query = "SELECT * FROM config WHERE confkey='$url' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$url]}' WHERE module_id = 'admin' AND confkey = '$url'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$url','{$_POST[$url]}')";
                    $db->Execute($insert);
                }
            }
            $map = 'gis_ol_wms_'.$j.'_map';
            if(!null==$_POST[$map]){
                $query = "SELECT * FROM config WHERE confkey='$map' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$map]}' WHERE module_id = 'admin' AND confkey = '$map'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$map','{$_POST[$map]}')";
                    $db->Execute($insert);
                }
            }
            $layers = 'gis_ol_wms_'.$j.'_layers';
            if(!null==$_POST[$layers]){
                $query = "SELECT * FROM config WHERE confkey='$layers' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$layers]}' WHERE module_id = 'admin' AND confkey = '$layers'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$layers','{$_POST[$layers]}')";
                    $db->Execute($insert);
                }
            }
            $format = 'gis_ol_wms_'.$j.'_format';
            if(!null==$_POST[$format]){
                $query = "SELECT * FROM config WHERE confkey='$format' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$format]}' WHERE module_id = 'admin' AND confkey = '$format'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$format','{$_POST[$format]}')";
                    $db->Execute($insert);
                }
            }
            $transparency = 'gis_ol_wms_'.$j.'_transparency';
            if(!null==$_POST[$transparency]){
                $query = "SELECT * FROM config WHERE confkey='$transparency' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$transparency]}' WHERE module_id = 'admin' AND confkey = '$transparency'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$transparency','{$_POST[$transparency]}')";
                    $db->Execute($insert);
                }
            }
        }
        // Checkboxes return nothing if unticked!
        if (null == $_POST['wms_enable']){
            $gis_ol_wms_enable=0;
        } else {
            $gis_ol_wms_enable=1;
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_wms_enable' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_ol_wms_enable' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms_enable'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms_enable','$gis_ol_wms_enable')";
            $db->Execute($insert);
        }
        if(!null==$_POST['gis_ol_wms']){
            $gis_ol_wms = $_POST['gis_ol_wms'];
            $query = "SELECT * FROM config WHERE confkey='gis_ol_wms' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$gis_ol_wms' WHERE module_id = 'admin' AND confkey = 'gis_ol_wms'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_wms','$gis_ol_wms')";
                $db->Execute($insert);
            }
        }
    }
}
 
?>
