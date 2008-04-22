<?php

/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: googlemaps.inc,v 1.12 2008-04-22 23:35:32 franboon Exp $
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
        echo _t("<p>Enable <a href='http://maps.google.com/'>GoogleMaps</a> &trade; Mapping Service" .
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
            shn_form_checkbox(_t('Google Map view Layer enabled?'),'ol_google_maps');
            shn_form_checkbox(_t('Google Satellite view Layer enabled?'),'ol_google_sat');
            shn_form_checkbox(_t('Google Hybrid view Layer enabled?'),'ol_google_hybrid');
            shn_form_fsclose();
            shn_form_fsopen(_t('API Key'));
            shn_form_fsopen(_t('INFO'));
            echo _t("<p>Google Maps requires a unique key pointing to where Sahana is hosted</p>");
            echo _t("<p>Register a key for the URL you host Sahana in, and enter it below</p>");
            echo _t("<p>Register your Google Maps key at: </p> <a href='http://www.google.com/apis/maps/' target=_blank>Google Maps</a>");
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
        global $conf;
        $db = $global['db'];                  
        if(!null==$_POST['ol_google']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_google' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_google']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_google'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google','{$_POST['ol_google']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_google_maps']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_google_maps' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_google_maps']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_maps'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_maps','{$_POST['ol_google_maps']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_google_sat']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_google_sat' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_google_sat']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_sat'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_sat','{$_POST['ol_google_sat']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_google_hybrid']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_google_hybrid' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_google_hybrid']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_google_hybrid'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_google_hybrid','{$_POST['ol_google_hybrid']}')";
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
