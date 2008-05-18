<?php

/**
* Sahana GIS Select Markers
*
* PHP version 5
* 
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function _shn_admin_gis_markers_form() {
    global $global;
    global $conf;
    include_once $global['approot']."/inc/lib_form.inc";

    print '<center><h2>' . _t("Default Markers") . '</h2></center>';
    shn_form_fopen("gis_markers_commit",null,array('req_message'=>false));

    shn_form_fsopen(_t("Select Marker Icon"));
    print '<p>' . _t("Please select the default icon to use for Markers") . '</p>';
    $select_help=_t("Select which icon to use as default for Markers. Include subfolders, if necessary.");
    shn_form_text(_t('Default Marker Icon: '),"gis_marker",'size=70',array('req'=>true,'value'=>$conf['gis_marker'],"help"=>$select_help));
    shn_form_fsclose();

    shn_form_fsopen(_t("Select GeoRSS Icon"));
    print '<p>' . _t("Please select the default icon to use for GeoRSS feeds") . '</p>';
    $georss_help=_t("Select which icon to use as default for GeoRSS feeds. Include subfolders, if necessary.");
    shn_form_text(_t('Default GeoRSS Icon: '),"gis_ol_georss_marker",'size=70',array('req'=>true,'value'=>$conf['gis_ol_georss_marker'],"help"=>$georss_help));
    shn_form_fsclose();

    shn_form_submit(_t("Select"));
    shn_form_fclose();
    print '<br />';
}

function _shn_admin_gis_commit_markers() {
    global $global;
    global $conf;
    $db = $global['db'];                  
    if(!null==$_POST['gis_marker']){
        $gis_marker = $_POST['gis_marker'];
        $query = "SELECT * FROM config WHERE confkey='gis_marker' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_marker' WHERE module_id = 'admin' AND confkey = 'gis_marker'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_marker','$gis_marker')";
            $db->Execute($insert);
        }
        $file=$global['approot']."www/".$conf['gis_marker_folder'].$gis_marker;
        list($width,$height)=getimagesize("$file");
        $markersize="$width,$height";
        $query = "SELECT * FROM config WHERE confkey='gis_marker_size' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$markersize' WHERE module_id = 'admin' AND confkey = 'gis_marker_size'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_marker_size','$markersize')";
            $db->Execute($insert);
        }
    }
    if(!null==$_POST['gis_ol_georss_marker']){
        $gis_ol_georss_marker = $_POST['gis_ol_georss_marker'];
        $query = "SELECT * FROM config WHERE confkey='gis_ol_georss_marker' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$gis_ol_georss_marker' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss_marker'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss_marker','$gis_ol_georss_marker')";
            $db->Execute($insert);
        }
        $file=$global['approot']."www/".$conf['gis_marker_folder'].$gis_ol_georss_marker;
        list($width,$height)=getimagesize("$file");
        $markersize="$width,$height";
        $query = "SELECT * FROM config WHERE confkey='gis_ol_georss_marker_size' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '$markersize' WHERE module_id = 'admin' AND confkey = 'gis_ol_georss_marker_size'";
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_georss_marker_size','$markersize')";
            $db->Execute($insert);
        }
    }
}

?>
