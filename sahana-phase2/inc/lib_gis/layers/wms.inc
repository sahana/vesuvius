<?php

/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    Sahana - http://sahana.lk/
* @library      GIS
* @version     $Id: wms.inc,v 1.11 2008-04-25 20:08:21 franboon Exp $
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
        if (!$conf['gis_ol_wms']==0){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable WMS layers'),'wms_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if (!$conf['gis_ol_wms']==0){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of WMS layers'),'gis_ol_wms','size=2 maxlength=2',array('value'=>$conf['gis_ol_wms']));
            shn_form_fsclose();
            $layers_help=_t("Which layer(s) at this WMS URL to enable (mandatory)");
            $img_help=_t("Image format (optional)");
            for ($i=0; $i<$conf['gis_ol_wms']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Description'),'gis_ol_wms_'.$j.'_description','size=40',array('value'=>$conf['gis_ol_wms_'.$j.'_description']));
                shn_form_text(_t('Name'),'gis_ol_wms_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_name']));
                $types = array(_t('base'),_t('overlay'));
                $type_select = _t('base');
                if ($conf['gis_ol_wms_'.$j.'_type']==1) {
                    $type_select = _t('overlay');
                }
                shn_form_select($types,_t('Type'),'gis_ol_wms_'.$j.'_type',null,array('value'=>$type_select));
                shn_form_text(_t('URL'),'gis_ol_wms_'.$j.'_url','size=40',array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_url']));
                shn_form_text(_t('Layers'),'gis_ol_wms_'.$j.'_layers',null,array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_layers'],"help"=>$layers_help));
                shn_form_text(_t('IMG'),'gis_ol_wms_'.$j.'_img',null,array('value'=>$conf['gis_ol_wms_'.$j.'_img'],"help"=>$img_help));
                shn_form_text(_t('Transparency'),'gis_ol_wms_'.$j.'_transparency',null,array('value'=>$conf['gis_ol_wms_'.$j.'_transparency']));
                shn_form_text(_t('Min'),'gis_ol_wms_'.$j.'_min',null,array('value'=>$conf['gis_ol_wms_'.$j.'_min']));
                shn_form_text(_t('Max'),'gis_ol_wms_'.$j.'_max',null,array('value'=>$conf['gis_ol_wms_'.$j.'_max']));
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
            $img = 'gis_ol_wms_'.$j.'_img';
            if(!null==$_POST[$img]){
                $query = "SELECT * FROM config WHERE confkey='$img' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$img]}' WHERE module_id = 'admin' AND confkey = '$img'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$img','{$_POST[$img]}')";
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
            $min = 'gis_ol_wms_'.$j.'_min';
            if(!null==$_POST[$min]){
                $query = "SELECT * FROM config WHERE confkey='$min' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$min]}' WHERE module_id = 'admin' AND confkey = '$min'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$min','{$_POST[$min]}')";
                    $db->Execute($insert);
                }
            }
            $max = 'gis_ol_wms_'.$j.'_max';
            if(!null==$_POST[$max]){
                $query = "SELECT * FROM config WHERE confkey='$max' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$max]}' WHERE module_id = 'admin' AND confkey = '$max'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$max','{$_POST[$max]}')";
                    $db->Execute($insert);
                }
            }
        }
            // Checkboxes return nothing if unticked!
        if (null == $_POST['wms_enable']){
            $gis_ol_wms=0;
        } else {
            if (!null == $_POST['gis_ol_wms']){
                $gis_ol_wms=$_POST['gis_ol_wms'];
            } else {
                $gis_ol_wms=1;
            }
        }
        if (!$gis_ol_wms == $conf['gis_ol_wms']) {
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
    /**
     * @ToDo Change to an Add/Edit/Delete mode to avoid 1 long form
     */
    //function edit_item() {
    //}
    //function edit_item() {
    //}
}
 
?>
