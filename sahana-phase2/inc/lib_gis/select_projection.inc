<?php

/**
* Sahana GIS Select Projection
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

function _shn_admin_gis_projection_form() {
    global $global;
    global $conf;
    include_once $global['approot']."/inc/lib_form.inc";
    
    print '<h2>'._t("Map Projection").'</h2>';
    print '<div class="information message"><p>'._t("A").' <a href="http://en.wikipedia.org/wiki/Map_projection" target=_blank>'._t("Projection").'</a> '._t("is a representation of the earth's 3D surface on a 2D plane. Sahana uses the definitions created by the") . ' <a href="http://www.epsg.org" target=_blank>European Petroleum Survey Group</a>.</p>';
    print '<p> Sahana ' . _t("is capable of supporting multiple simultaneous projections for feature overlays (GeoRSS & File layers) but only a single Projection for the Base layers at a time") . '.</p></div>';
    shn_form_fopen("gis_projection_commit",null,array('req_message'=>false));
    shn_form_fsopen(_t('Base Projection'));
    print '<p><a href="http://trac.openlayers.org/wiki/SphericalMercator" target=_blank>SphericalMercator</a> (EPSG:900913) ' . _t("is the default Base Projection as this provides full compatibility with non-WMS base layers.").'</p>';
    print '<p>' . _t("Some WMS servers may not support this & hence need a different value (such as").' EPSG:4326 '._t("for").' WGS84).<br />';
    print _t("If this is the case then").' <b>'._t("all other base layers are disabled").'</b> '._t("to avoid problems when moving between different layer types") . '!</p>';
    print '<p>' . _t("To select a new projection to use for the Base layer, select from the drop-down below:") . '</p>';
    print '<br />';
    $projections_help='SphericalMercator (EPSG:900913) '._t("provides maximum base layer compatibility").'.<br />WGS84 '._t("is").' EPSG:4326.<br />'._t("Custom layers need extra information to be defined.");
    $projections = array('SphericalMercator','EPSG:4326',_t('Custom'));
    $projections_select = '0';
    if ("1"==$conf["gis_ol_projections"]) {
        $projections_select = '1';
    } else if ("2"==$conf["gis_ol_projections"]) {
        $projections_select = '2';
    }
    shn_form_select($projections,_t('Projection'),'gis_ol_projections',null,array('value'=>$projections_select,"help"=>$projections_help));
    if (2==$conf["gis_ol_projections"]){
        $projection_help=_t("Format should be").' EPSG:xxxx.<br />'._t("A definition file also needs uploading").'.<br />'._t("NB Because a Custom projection is being used").' <b>'._t("all other base layers are disabled").'</b> '._t("to avoid problems when moving between different layer types!");
        $maxExtent_help=_t("The number of units required to reach: Left, Bottom, Right, Top");
        $maxResolution_help=_t("How many units per pixel");
        $units_help=_t("The units in which the measurements apply (e.g. 'm', 'degrees' or 'usfeet')");
        shn_form_text(_t('Projection'),'gis_ol_projection',null,array('req'=>true,'value'=>$conf['gis_ol_projection'],"help"=>$projection_help));
        shn_form_text(_t('maxExtent'),'gis_ol_maxExtent',null,array('req'=>true,'value'=>$conf['gis_ol_maxExtent'],"help"=>$maxExtent_help));
        shn_form_text(_t('maxResolution'),'gis_ol_maxResolution',null,array('req'=>true,'value'=>$conf['gis_ol_maxResolution'],"help"=>$maxResolution_help));
        shn_form_text(_t('units'),'gis_ol_units',null,array('req'=>true,'value'=>$conf['gis_ol_units'],"help"=>$units_help));
    }
    shn_form_fsclose();
    shn_form_submit(_t("Select"));
    shn_form_fclose();
    print '<br />';
}

function _shn_admin_gis_commit_projection() {
    global $global;
    global $conf;
    $db = $global['db'];                  
    if (null==$_POST['gis_ol_projections'] || "0"==$_POST['gis_ol_projections']) {
        $projection = 'EPSG:900913';
        $maxExtent = '-20037508, -20037508, 20037508, 20037508.34';
        $maxResolution = '156543.0339';
        $units = 'm';
    } else if ("1"==$_POST['gis_ol_projections']) {
        $projection = 'EPSG:4326';
        $maxExtent = '-180,-90,180,90';
        $maxResolution = '1.40625';
        $units = 'degrees';
    } else if (!null==$_POST['gis_ol_projections']){
        $projection = $_POST['gis_ol_projection'];
        $maxExtent = $_POST['gis_ol_maxExtent'];
        $maxResolution = $_POST['gis_ol_maxResolution'];
        $units = $_POST['gis_ol_units'];
    }
    $query = "SELECT * FROM config WHERE confkey='gis_ol_projection' AND module_id='admin'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '$projection' WHERE module_id = 'admin' AND confkey = 'gis_ol_projection'";
        $db->Execute($q);
    }
    else{
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_projection','$projection')";
        $db->Execute($insert);
    }
    $query = "SELECT * FROM config WHERE confkey='gis_ol_projections' AND module_id='admin'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '{$_POST['gis_ol_projections']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_projections'";
        $db->Execute($q);
    }
    else{
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_projections','{$_POST['gis_ol_projections']}')";
        $db->Execute($insert);
    }
    $query = "SELECT * FROM config WHERE confkey='gis_ol_maxExtent' AND module_id='admin'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '$maxExtent' WHERE module_id = 'admin' AND confkey = 'gis_ol_maxExtent'";
        $db->Execute($q);
    }
    else{
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_maxExtent','$maxExtent')";
        $db->Execute($insert);
    }
    $query = "SELECT * FROM config WHERE confkey='gis_ol_maxResolution' AND module_id='admin'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '$maxResolution' WHERE module_id = 'admin' AND confkey = 'gis_ol_maxResolution'";
        $db->Execute($q);
    }
    else{
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_maxResolution','$maxResolution')";
        $db->Execute($insert);
    }
    $query = "SELECT * FROM config WHERE confkey='gis_ol_units' AND module_id='admin'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '$units' WHERE module_id = 'admin' AND confkey = 'gis_ol_units'";
        $db->Execute($q);
    }
    else{
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_units','$units')";
        $db->Execute($insert);
    }
}


