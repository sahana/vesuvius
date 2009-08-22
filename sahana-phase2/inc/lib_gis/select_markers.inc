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
    $dir=$conf['gis_marker_folder'];
    $marker=$conf['gis_marker'];
    $georss_marker=$conf['gis_ol_georss_marker'];
    $marker_path="$dir$marker";
    $georss_path="$dir$georss_marker";
    
    print '<h2>'._t("Default Markers").'</h2>';
    shn_form_fopen("gis_markers_commit",null,array('req_message'=>false));

    shn_form_fsopen(_t("Default Marker Icon"));
    print '<p>'._t("The current default icon to use for Markers is: ") . "<img src='$marker_path' />('$marker')</p>";
    print '<p>'._t("To select a new default icon to use for Markers, enter the filename below:").'</p>';
    $select_help=_t("Select which icon to use as default for Markers. Include subfolders, if necessary.");
    shn_form_text(_t('Select new Marker Icon: '),"gis_marker",'size=70',array('value'=>$marker,"help"=>$select_help));
    shn_form_fsclose();

    shn_form_fsopen(_t("Default GeoRSS Icon"));
    print '<p>' . _t("The current default icon to use for GeoRSS feeds is: ") . "<img src='$georss_path' />('$georss_marker')</p>";
    print '<p>' . _t("To select a new default icon to use for GeoRSS feeds, enter the filename below:") . '</p>';
    $georss_help=_t("Select which icon to use as default for GeoRSS feeds. Include subfolders, if necessary.");
    shn_form_text(_t('Select new GeoRSS Icon: '),"gis_ol_georss_marker",'size=70',array('value'=>$georss_marker,"help"=>$georss_help));
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


