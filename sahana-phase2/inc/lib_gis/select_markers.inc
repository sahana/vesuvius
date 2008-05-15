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

global $global;
global $conf;

function _shn_admin_gis_markers_form() {
    global $global;
    global $conf;
    include_once $global['approot']."/inc/lib_form.inc";

    print '<center><h2>' . _t("Select Marker image") . '</h2></center>';
    print '<p>' . _t("Please select the default icon to use for Markers") . '</p>';

    $select_help=_t("Select which icon to use for Markers");
    shn_form_fopen("gis_markers_commit",null,array('req_message'=>false));
    shn_form_fsopen(_t("Select Marker Image File"));
    shn_form_text(_t('Select Marker'),"gis_marker",'size=70',array('req'=>true,'value'=>$conf['gis_marker'],"help"=>$select_help));
    shn_form_fsclose();

    print "<br />";
    shn_form_submit(_t("Select"));
    shn_form_fclose();
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
}

?>
