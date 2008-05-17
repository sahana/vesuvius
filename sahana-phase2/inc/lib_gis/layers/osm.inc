<?php
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version      $Id: osm.inc,v 1.2 2008-05-17 16:11:49 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class osm implements layer{
	
	function print_form()
	{
		global $conf;
        shn_form_fsopen(_t('OpenStreetMap'));
        shn_form_fsopen(_t('OpenStreetMap'));
		shn_form_fsopen('INFO');
        echo '<p>' . _t("Enable ") . '<a href="http://openstreetmap.org/" target=_blank>OpenStreetMap</a>' . _t(" Mapping Service by selecting the checkbox option below.")  . '</p>';
        echo '<p>' . _t("The OpenStreetMap mapping API requires Internet connectivity")  . '</p>';
        echo '<p>' . _t("However data can be taken offline as an .osm File layer (The ") . '<a href="http://wiki.openstreetmap.org/index.php/JOSM" target=_blank>JOSM</a>' . _t(" Editor is recommended).")  . '</p>';
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_osm']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable OpenStreetMap Maps'),'ol_osm',$checked,array('value'=>1));	
		shn_form_fsclose();
		shn_form_fsclose();
        if ($conf['gis_ol_osm']==1){
            shn_form_fsopen('Viewport Settings');
            echo _t("<p>OpenStreetMap supports 2 types of layer which can each be enabled separately</p>");
            echo _t("<p>(If none are selected then no OpenStreetMap layer will appear)</p>");
            $checked='';
            if ($conf['gis_ol_osm_mapnik']==1){
                $checked='checked';
            }
            $mapnik_help=_t("A layer rendered using Mapnik: http://mapnik.org");
            shn_form_checkbox(_t('Mapnik view enabled?'),'ol_osm_mapnik',$checked,array('value'=>1,"help"=>$mapnik_help));
            $checked='';
            if ($conf['gis_ol_osm_tiles']==1){
                $checked='checked';
            }
            $tiles_help=_t("A layer rendered using Osmarender: http://wiki.openstreetmap.org/index.php/Osmarender");
            shn_form_checkbox(_t('Osmarender view enabled?'),'ol_osm_tiles',$checked,array('value'=>1,"help"=>$tiles_help));
            shn_form_fsclose();
        }
        shn_form_fsclose();
	}

    function commit_values()
    {
        global $global;
        global $conf;
        $db = $global['db'];                  
        // Only consider the inner-checkboxes if they are visible
        if (1 == $conf['gis_ol_osm']){
            // Checkboxes return nothing if unticked!
            if (null == $_POST['ol_osm_mapnik']){
                $ol_osm_mapnik=0;
            }
            if (1 == $_POST['ol_osm_mapnik']){
                $ol_osm_mapnik=1;
            }
            if (!$ol_osm_mapnik == $conf['gis_ol_osm_mapnik']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_osm_mapnik' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_osm_mapnik' WHERE module_id = 'admin' AND confkey = 'gis_ol_osm_mapnik'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_osm_mapnik','$ol_osm_mapnik')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_osm_tiles']){
                $ol_osm_tiles=0;
            }
            if (1 == $_POST['ol_osm_tiles']){
                $ol_osm_tiles=1;
            }
            if (!$ol_osm_tiles == $conf['gis_ol_osm_tiles']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_osm_tiles' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_osm_tiles' WHERE module_id = 'admin' AND confkey = 'gis_ol_osm_tiles'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_osm_tiles','$ol_osm_tiles')";
                    $db->Execute($insert);
                }
            }
        }
        if (null == $_POST['ol_osm']){
            $ol_osm=0;
        }
        if (1 == $_POST['ol_osm']){
            $ol_osm=1;
        }
        if (!$ol_osm == $conf['gis_ol_osm']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_osm' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$ol_osm' WHERE module_id = 'admin' AND confkey = 'gis_ol_osm'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_osm','$ol_osm')";
                $db->Execute($insert);
            }
        }
    }

}
 
?>

