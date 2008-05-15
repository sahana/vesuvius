<?php

/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    Sahana - http://sahana.lk/
* @library      GIS
* @version     $Id: georss.inc,v 1.12 2008-05-15 13:24:41 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class georss implements layer{

    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('GeoRSS'));
        shn_form_fsopen(_t('INFO'));
        print '<p>' . _t("Sahana can make use of Feeds from servers using the <a href='http://en.wikipedia.org/wiki/GeoRSS' target=_blank>GeoRSS</a> standard.") . '</p>';
        print '<p>' . _t("Enable GeoRSS Layers by selecting the checkbox option below.") . '</p>';
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_georss_enable']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable GeoRSS layers'),'georss_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if ($conf['gis_ol_georss_enable']==1){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of GeoRSS layers'),'gis_ol_georss','size=2 maxlength=2',array('value'=>$conf['gis_ol_georss']));
            shn_form_fsclose();
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $url_help=_t("Address of the GeoRSS service (mandatory)");
            $icon_help=_t("Which icon to use to display the markers for this GeoRSS feed. Icons can be uploaded via the").'<a href="index.php?mod=admin&act=gis_markers" target=_blank>'._t("GIS Markers Management").'</a>'._t(" (optional). Defaults to")." 'marker-red.png'";
            $iconsize_help=_t("Size of the icon as 'Width, Height' (optional). Defaults to")." '20,34'";
            $projection_help=_t("Coordinate system used to display the data, as defined by ").'<a href="http://www.epsg.org" target=_blank>'._t("European Petroleum Survey Group").'</a>'._t(" (mandatory). If left blank, then ").'EPSG:4326'._t(" is assumed as this is the default ").'WGS84.';
            $visibility_help=_t("Whether the layer is visible by default");
            $enabled_help=_t("Whether the layer is selectable from the Map or not");
            for ($i=0; $i<$conf['gis_ol_georss']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Name'),'gis_ol_georss_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_georss_'.$j.'_name'],"help"=>$name_help));
                shn_form_text(_t('Description'),'gis_ol_georss_'.$j.'_description','size=60',array('value'=>$conf['gis_ol_georss_'.$j.'_description'],"help"=>$description_help));
                shn_form_text(_t('URL'),'gis_ol_georss_'.$j.'_url','size=60',array('req'=>true,'value'=>$conf['gis_ol_georss_'.$j.'_url'],"help"=>$url_help));
                shn_form_text(_t('Icon'),'gis_ol_georss_'.$j.'_icon',null,array('value'=>$conf['gis_ol_georss_'.$j.'_icon'],"help"=>$icon_help));
                shn_form_text(_t('Icon Size'),'gis_ol_georss_'.$j.'_icon_size',null,array('value'=>$conf['gis_ol_georss_'.$j.'_icon_size'],"help"=>$iconsize_help));
                $projection = "EPSG:4326";
                if (!null == $conf['gis_ol_georss_'.$j.'_projection']) {
                    $projection = $conf['gis_ol_georss_'.$j.'_projection'];
                }
                shn_form_text(_t('Projection'),'gis_ol_georss_'.$j.'_projection',null,array('req'=>true,'value'=>$projection,"help"=>$projection_help));
                $visibilities = array(_t('false'),_t('true'));
                $visibility_select = '0';
                if ('1'==$conf['gis_ol_georss_'.$j.'_visibility']) {
                    $visibility_select = '1';
                }
                shn_form_select($visibilities,_t('Visible'),'gis_ol_georss_'.$j.'_visibility',null,array('value'=>$visibility_select,"help"=>$visibility_help));
                $enableds = array(_t('false'),_t('true'));
                $enabled_select = '1';
                if ('0'==$conf['gis_ol_georss_'.$j.'_enabled']) {
                    $enabled_select = '0';
                }
                shn_form_select($enableds,_t('Enabled'),'gis_ol_georss_'.$j.'_enabled',null,array('value'=>$enabled_select,"help"=>$enabled_help));
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
        for ($i=0; $i<$conf['gis_ol_georss']; $i++) {
            $j=$i+1;
            $name = 'gis_ol_georss_'.$j.'_name';
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
            $description = 'gis_ol_georss_'.$j.'_description';
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
            $url = 'gis_ol_georss_'.$j.'_url';
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
            $icon = 'gis_ol_georss_'.$j.'_icon';
            if(!null==$_POST[$icon]){
                $query = "SELECT * FROM config WHERE confkey='$icon' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$icon]}' WHERE module_id = 'admin' AND confkey = '$icon'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$icon','{$_POST[$icon]}')";
                    $db->Execute($insert);
                }
            } else if (null==$conf['$icon']){
                $icon_default='marker-red.png';
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$icon','$icon_default')";
                $db->Execute($insert);
            }
            $iconsize = 'gis_ol_georss_'.$j.'_icon_size';
            if(!null==$_POST[$iconsize]){
                $query = "SELECT * FROM config WHERE confkey='$iconsize' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$iconsize]}' WHERE module_id = 'admin' AND confkey = '$iconsize'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$iconsize','{$_POST[$iconsize]}')";
                    $db->Execute($insert);
                }
            } else if (null==$conf['$iconsize']){
                $iconsize_default='21,25';
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$iconsize','$iconsize_default')";
                $db->Execute($insert);
            }
            $projection = 'gis_ol_georss_'.$j.'_projection';
            if(!null==$_POST[$projection]){
                $query = "SELECT * FROM config WHERE confkey='$projection' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$projection]}' WHERE module_id = 'admin' AND confkey = '$projection'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$projection','{$_POST[$projection]}')";
                    $db->Execute($insert);
                }
            } else if (null==$conf['$projection']){
                $projection_default='EPSG:4326';
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$projection','$projection_default')";
                $db->Execute($insert);
            }
            //In PHP 0 == NULL!
            $visibility = 'gis_ol_georss_'.$j.'_visibility';
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
            $enabled = 'gis_ol_georss_'.$j.'_enabled';
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
        if (null == $_POST['georss_enable']){
            $gis_ol_georss_enable=0;
        } else {
            $gis_ol_georss_enable=1;
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_georss_enable' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_ol_georss_enable' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss_enable'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss_enable','$gis_ol_georss_enable')";
            $db->Execute($insert);
        }
        if(!null==$_POST['gis_ol_georss']){
            $gis_ol_georss = $_POST['gis_ol_georss'];
            $query = "SELECT * FROM config WHERE confkey='gis_ol_georss' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$gis_ol_georss' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss','$gis_ol_georss')";
                $db->Execute($insert);
            }
        }
    }
}
 
?>
