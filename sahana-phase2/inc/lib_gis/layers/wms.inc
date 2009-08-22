<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    Sahana - http://sahana.lk/
* @library      GIS
* @version     $Id: wms.inc,v 1.26 2009-08-22 17:17:23 ravithb Exp $
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
        echo '<p>'._t("Enable access to maps from servers using the").' <a href="http://www.opengeospatial.org/standards/wms" target=_blank>WMS (Web Map Service)</a> '._t("standard by selecting the checkbox option below").'.</p>';
		echo '<p>'._t("These servers could be local or accessed over the Internet").'.</p>';
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if (1==$conf['gis_ol_wms_enable']){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable WMS layers'),'wms_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if (1==$conf['gis_ol_wms_enable']){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of WMS layers'),'gis_ol_wms','size=2 maxlength=2',array('value'=>$conf['gis_ol_wms']));
            shn_form_fsclose();
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $url_help=_t("Address of the WMS service - without Options (mandatory)");
            $type_help=_t("Only one 'Base' layer can be displayed at a time").'.<br />'._t("Multiple 'Overlay' layers can be displayed over the top.");
            $map_help=_t("Mapfile to use with MapServer").'.<br />'._t("e.g.").' \'/var/www/maps/maps/example.map\' ('._t("optional)");
            $layers_help=_t("Comma-separated list of layer(s) at this WMS URL to enable (mandatory").')<br />'._t("NB If you wish to be able to switch layers on/off independently then you should define a separate WMS layer for each one.");
            $format_help=_t("Image format (optional)").'.<br />'._t("e.g.").' \'image/png\'';
            $transparency_help=_t("usually 'false' for a Base layer & 'true' for an overlay layer");
            $visibility_help=_t("Whether the layer is visible by default (only applicable for overlays)");
            $enabled_help=_t("Whether the layer is selectable from the Map or not");
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
                $transparencies = array(_t('false'),_t('true'));
                $transparency_select = '0';
                if ('1'==$conf['gis_ol_wms_'.$j.'_transparency']) {
                    $transparency_select = '1';
                }
                shn_form_select($transparencies,_t('Transparency'),'gis_ol_wms_'.$j.'_transparency',null,array('value'=>$transparency_select,"help"=>$transparency_help));
                shn_form_text(_t('Map'),'gis_ol_wms_'.$j.'_map','size=40',array('value'=>$conf['gis_ol_wms_'.$j.'_map'],"help"=>$map_help));
                shn_form_text(_t('Layers'),'gis_ol_wms_'.$j.'_layers','size=40',array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_layers'],"help"=>$layers_help));
                shn_form_text(_t('Format'),'gis_ol_wms_'.$j.'_format','size=20',array('value'=>$conf['gis_ol_wms_'.$j.'_format'],"help"=>$format_help));
                if ('1'==$conf['gis_ol_wms_'.$j.'_type']) {
                    $visibilities = array(_t('false'),_t('true'));
                    $visibility_select = '0';
                    if ('1'==$conf['gis_ol_wms_'.$j.'_visibility']) {
                        $visibility_select = '1';
                    }
                    shn_form_select($visibilities,_t('Visible'),'gis_ol_wms_'.$j.'_visibility',null,array('value'=>$visibility_select,"help"=>$visibility_help));
                }
                $enableds = array(_t('false'),_t('true'));
                $enabled_select = '1';
                if ('0'==$conf['gis_ol_wms_'.$j.'_enabled']) {
                    $enabled_select = '0';
                }
                shn_form_select($enableds,_t('Enabled'),'gis_ol_wms_'.$j.'_enabled',null,array('value'=>$enabled_select,"help"=>$enabled_help));
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
            //In PHP 0 == NULL!
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
            $visibility = 'gis_ol_wms_'.$j.'_visibility';
            $query = "SELECT * FROM config WHERE confkey='$visibility' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$visibility]}' WHERE module_id = 'admin' AND confkey = '$visibility'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$visibility','{$_POST[$visibility]}')";
                $db->Execute($insert);
            }
            $enabled = 'gis_ol_wms_'.$j.'_enabled';
            $query = "SELECT * FROM config WHERE confkey='$enabled' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST[$enabled]}' WHERE module_id = 'admin' AND confkey = '$enabled'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$enabled','{$_POST[$enabled]}')";
                $db->Execute($insert);
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


