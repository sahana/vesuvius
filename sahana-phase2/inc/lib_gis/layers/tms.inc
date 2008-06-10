<?php
/**
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @package    	Sahana - http://sahana.lk/
* @library      GIS
* @version     	$Id: tms.inc,v 1.3 2008-06-10 10:18:38 mifanc Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* 
* @todo: handle available layer options of TMS
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class tms implements layer{

    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('TMS'));
        shn_form_fsopen(_t('INFO'));
        echo '<p>'._t("Enable access to maps from servers using the").' <a href="http://wiki.osgeo.org/wiki/Tile_Map_Service_Specification" target=_blank>TMS (Tile Map Service)</a> '._t("by selecting the checkbox option below").'.</p>';
		echo '<p>'._t("These servers could be local or accessed over the Internet").'.</p>';
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if (1==$conf['gis_ol_tms_enable']){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable TMS layers'),'tms_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if (1==$conf['gis_ol_tms_enable']){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of TMS layers'),'gis_ol_tms','size=2 maxlength=2',array('value'=>$conf['gis_ol_tms']));
            shn_form_fsclose();
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $url_help=_t("Address of the tms service - without Options (mandatory)");
            $type_help=_t("Only one 'Base' layer can be displayed at a time").'.<br />'._t("Multiple 'Overlay' layers can be displayed over the top.");
            $layers_help=_t("Comma-separated list of layer(s) at this tms URL to enable (mandatory").')<br />'._t("NB If you wish to be able to switch layers on/off independently then you should define a separate tms layer for each one.");
            $format_help=_t("Image format (optional)").'.<br />'._t("e.g.").' \'png OR jpg\'';
            $visibility_help=_t("Whether the layer is visible by default (only applicable for overlays)");
            $enabled_help=_t("Whether the layer is selectable from the Map or not");
            for ($i=0; $i<$conf['gis_ol_tms']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Name'),'gis_ol_tms_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_tms_'.$j.'_name'],"help"=>$name_help));
                shn_form_text(_t('Description'),'gis_ol_tms_'.$j.'_description','size=60',array('value'=>$conf['gis_ol_tms_'.$j.'_description'],"help"=>$description_help));
                shn_form_text(_t('URL'),'gis_ol_tms_'.$j.'_url','size=60',array('req'=>true,'value'=>$conf['gis_ol_tms_'.$j.'_url'],"help"=>$url_help));
                
                shn_form_text(_t('Layers'),'gis_ol_tms_'.$j.'_layers','size=40',array('req'=>true,'value'=>$conf['gis_ol_tms_'.$j.'_layers'],"help"=>$layers_help));
                shn_form_text(_t('Format'),'gis_ol_tms_'.$j.'_format','size=20',array('value'=>$conf['gis_ol_tms_'.$j.'_format'],"help"=>$format_help));
                if ('1'==$conf['gis_ol_tms_'.$j.'_type']) {
                    $visibilities = array(_t('false'),_t('true'));
                    $visibility_select = '0';
                    if ('1'==$conf['gis_ol_tms_'.$j.'_visibility']) {
                        $visibility_select = '1';
                    }
                    shn_form_select($visibilities,_t('Visible'),'gis_ol_tms_'.$j.'_visibility',null,array('value'=>$visibility_select,"help"=>$visibility_help));
                }
                $enableds = array(_t('false'),_t('true'));
                $enabled_select = '1';
                if ('0'==$conf['gis_ol_tms_'.$j.'_enabled']) {
                    $enabled_select = '0';
                }
                shn_form_select($enableds,_t('Enabled'),'gis_ol_tms_'.$j.'_enabled',null,array('value'=>$enabled_select,"help"=>$enabled_help));
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
        for ($i=0; $i<$conf['gis_ol_tms']; $i++) {
            $j=$i+1;
            $description = 'gis_ol_tms_'.$j.'_description';
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
            $name = 'gis_ol_tms_'.$j.'_name';
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
            
            $url = 'gis_ol_tms_'.$j.'_url';
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
            
            $layers = 'gis_ol_tms_'.$j.'_layers';
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
            $format = 'gis_ol_tms_'.$j.'_format';
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
            
            $visibility = 'gis_ol_tms_'.$j.'_visibility';
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
            $enabled = 'gis_ol_tms_'.$j.'_enabled';
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
        if (null == $_POST['tms_enable']){
            $gis_ol_tms_enable=0;
        } else {
            $gis_ol_tms_enable=1;
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_tms_enable' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_ol_tms_enable' WHERE module_id = 'admin' AND confkey = 'gis_ol_tms_enable'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_tms_enable','$gis_ol_tms_enable')";
            $db->Execute($insert);
        }
        if(!null==$_POST['gis_ol_tms']){
            $gis_ol_tms = $_POST['gis_ol_tms'];
            $query = "SELECT * FROM config WHERE confkey='gis_ol_tms' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$gis_ol_tms' WHERE module_id = 'admin' AND confkey = 'gis_ol_tms'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_tms','$gis_ol_tms')";
                $db->Execute($insert);
            }
        }
    }
}

?>

