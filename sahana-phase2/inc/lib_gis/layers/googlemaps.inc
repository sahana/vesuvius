<?php

/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: googlemaps.inc,v 1.16 2008-04-23 23:52:57 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class googlemaps implements layer{
	
	function print_form()
	{
        global $conf;
        shn_form_fsopen(_t('Google Maps'));
        shn_form_fsopen(_t('Google Maps'));
        shn_form_fsopen(_t('INFO'));
        echo _t("<p>Enable <a href='http://maps.google.com/' target=_blank>GoogleMaps</a> &trade; Mapping Service" .
        " by selecting the checkbox option below.</p>");
        echo _t("<p>The GoogleMaps mapping API requires Internet connectivity and a valid Google Maps key</p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_google']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Google Layer'),'ol_google',$checked,array('value'=>1));	
        shn_form_fsclose();
        shn_form_fsclose();
        if ($conf['gis_ol_google']==1){
            shn_form_fsopen('Viewport Settings');
            echo _t("<p>Google supports 3 types of layer which can each be enabled separately</p>");
            echo _t("<p>(If none are selected then no Google layer will appear)</p>");
            $checked='';
            if ($conf['gis_ol_google_maps']==1){
                $checked='checked';
            }
            $maps_help=_t("A layer with just Maps shown");
            shn_form_checkbox(_t('Map view enabled?'),'ol_google_maps',$checked,array('value'=>1,"help"=>$maps_help));
            $checked='';
            if ($conf['gis_ol_google_sat']==1){
                $checked='checked';
            }
            $sat_help=_t("A layer with just Satellite Photos shown");
            shn_form_checkbox(_t('Satellite view enabled?'),'ol_google_sat',$checked,array('value'=>1,"help"=>$sat_help));
            $checked='';
            if ($conf['gis_ol_google_hybrid']==1){
                $checked='checked';
            }
            $hybrid_help=_t("A layer with Maps & Satellite Photos shown together");
            shn_form_checkbox(_t('Hybrid view enabled?'),'ol_google_hybrid',$checked,array('value'=>1,"help"=>$hybrid_help));
            shn_form_fsclose();
            shn_form_fsopen(_t('API Key'));
            shn_form_fsopen(_t('INFO'));
            echo _t("<p>Google Maps requires a unique key pointing to where Sahana is hosted</p>");
            echo _t("<p>Register a key for the URL you host Sahana in, and enter it below</p>");
            echo _t("<p>(You can register your own Google Maps key at: <a href='http://www.google.com/apis/maps/' target=_blank>Google Maps</a>)</p>");
            shn_form_fsclose();
            shn_form_fsopen(_t('Enter API Key'));
            shn_form_text(_t("Enter Google Maps Key"),"gis_google_key",'size="100"',array('value'=>$conf['gis_google_key']));
            shn_form_fsclose();
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
        if (1 == $conf['gis_ol_google']){
            // Checkboxes return nothing if unticked!
            if (null == $_POST['ol_google_maps']){
                $ol_google_maps=0;
            }
            if (1 == $_POST['ol_google_maps']){
                $ol_google_maps=1;
            }
            if (!$ol_google_maps == $conf['gis_ol_google_maps']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_google_maps' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_google_maps' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_maps'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_maps','$ol_google_maps')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_google_sat']){
                $ol_google_sat=0;
            }
            if (1 == $_POST['ol_google_sat']){
                $ol_google_sat=1;
            }
            if (!$ol_google_sat == $conf['gis_ol_google_sat']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_google_sat' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_google_sat' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_sat'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_sat','$ol_google_sat')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_google_hybrid']){
                $ol_google_hybrid=0;
            }
            if (1 == $_POST['ol_google_hybrid']){
                $ol_google_hybrid=1;
            }
            if (!$ol_google_hybrid == $conf['gis_ol_google_hybrid']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_google_hybrid' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_google_hybrid' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_hybrid'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_hybrid','$ol_google_hybrid')";
                    $db->Execute($insert);
                }
            }
        }
        if (null == $_POST['ol_google']){
            $ol_google=0;
        }
        if (1 == $_POST['ol_google']){
            $ol_google=1;
        }
        if (!$ol_google == $conf['gis_ol_google']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_google' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$ol_google' WHERE module_id = 'admin' AND confkey = 'gis_ol_google'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google','$ol_google')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['gis_google_key']){
            $query = "SELECT * FROM config WHERE confkey='gis_google_key' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['gis_google_key']}' WHERE module_id = 'admin' AND confkey = 'gis_google_key'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_google_key','{$_POST['gis_google_key']}')";
                $db->Execute($insert);
            }
        }
    }
}

?>
