<?php

/**
* PHP version 5
* 
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    Sahana - http://sahana.lk/
* @library      GIS
* @version     $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class files implements layer{

    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('Files'));
        shn_form_fsopen(_t('INFO'));
        echo '<p>'._t("Enable access to locally-stored Files using the").' <a href="http://en.wikipedia.org/wiki/Keyhole_Markup_Language" target=_blank>KML</a>, <a href="http://wiki.openstreetmap.org/index.php/Protocol" target=_blank>OSM</a> '._t("or").' <a href="http://en.wikipedia.org/wiki/Geography_Markup_Language" target=_blank>GML</a> '._t("formats by selecting the checkbox option below").'.</p>';
        echo '<p>'._t("Files can be uploaded using the").' <a href="?mod=admin&act=gis_files">'._t("File Manager").'</a>.</p>';
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_files_enable']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Files layers'),'files_enable',$checked,array('value'=>1));
        shn_form_fsclose();
        if ($conf['gis_ol_files_enable']==1){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of File layers'),'gis_ol_files','size=2 maxlength=2',array('value'=>$conf['gis_ol_files']));
            shn_form_fsclose();
            $name_help=_t("Name displayed in Layer-Switcher (mandatory)");
            $description_help=_t("Only displayed in GIS Catalogue (optional)");
            $filename_help=_t("Filename (mandatory)");
            $visibility_help=_t("Whether the layer is visible by default");
            $enabled_help=_t("Whether the layer is selectable from the Map or not");
            for ($i=0; $i<$conf['gis_ol_files']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Name'),'gis_ol_files_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_files_'.$j.'_name'],"help"=>$name_help));
                shn_form_text(_t('Description'),'gis_ol_files_'.$j.'_description','size=60',array('value'=>$conf['gis_ol_files_'.$j.'_description'],"help"=>$description_help));
                shn_form_text(_t('File name'),'gis_ol_files_'.$j.'_filename','size=60',array('req'=>true,'value'=>$conf['gis_ol_files_'.$j.'_filename'],"help"=>$filename_help));
                $visibilities = array(_t('false'),_t('true'));
                $visibility_select = '0';
                if ('1'==$conf['gis_ol_files_'.$j.'_visibility']) {
                    $visibility_select = '1';
                }
                shn_form_select($visibilities,_t('Visible'),'gis_ol_files_'.$j.'_visibility',null,array('value'=>$visibility_select,"help"=>$visibility_help));
                $enableds = array(_t('false'),_t('true'));
                $enabled_select = '1';
                if ('0'==$conf['gis_ol_files_'.$j.'_enabled']) {
                    $enabled_select = '0';
                }
                shn_form_select($enableds,_t('Enabled'),'gis_ol_files_'.$j.'_enabled',null,array('value'=>$enabled_select,"help"=>$enabled_help));
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
        for ($i=0; $i<$conf['gis_ol_files']; $i++) {
            $j=$i+1;
            $description = 'gis_ol_files_'.$j.'_description';
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
            $name = 'gis_ol_files_'.$j.'_name';
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
            $filename = 'gis_ol_files_'.$j.'_filename';
            if(!null==$_POST[$filename]){
                $query = "SELECT * FROM config WHERE confkey='$filename' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '{$_POST[$filename]}' WHERE module_id = 'admin' AND confkey = '$filename'";
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','$filename','{$_POST[$filename]}')";
                    $db->Execute($insert);
                }
            }
            //In PHP 0 == NULL!
            $visibility = 'gis_ol_files_'.$j.'_visibility';
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
            $enabled = 'gis_ol_files_'.$j.'_enabled';
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
        if (null == $_POST['files_enable']){
            $gis_ol_files_enable=0;
        } else {
            $gis_ol_files_enable=1;
        }
        $query = "SELECT * FROM config WHERE confkey='gis_ol_files_enable' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_ol_files_enable' WHERE module_id = 'admin' AND confkey = 'gis_ol_files_enable'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_files_enable','$gis_ol_files_enable')";
            $db->Execute($insert);
        }
        if(!null==$_POST['gis_ol_files']){
            $gis_ol_files = $_POST['gis_ol_files'];
            $query = "SELECT * FROM config WHERE confkey='gis_ol_files' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$gis_ol_files' WHERE module_id = 'admin' AND confkey = 'gis_ol_files'";
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_files','$gis_ol_files')";
                $db->Execute($insert);
            }
        }
    }
}
 

