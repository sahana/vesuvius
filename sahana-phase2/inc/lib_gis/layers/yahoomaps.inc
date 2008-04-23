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
* @version		$Id: yahoomaps.inc,v 1.8 2008-04-23 22:17:48 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;

include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class yahoomaps implements layer{
	
	function print_form()
	{
		global $conf;
		shn_form_fsopen(_t('Yahoo Maps'));
			shn_form_fsopen('Yahoo Maps');
				shn_form_fsopen('INFO');
					echo _t("<p>Enable <a href='http://maps.yahoo.com/' target=_blank>Yahoo Maps</a> &trade; Mapping Service" .
							" by selecting the checkbox option below.</p>");
					echo _t("<p>The Yahoo Maps mapping API requires Internet connectivity and a valid Yahoo Maps key</p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_yahoo']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Yahoo Maps'),'ol_yahoo',$checked,array('value'=>1));	
		shn_form_fsclose();
		shn_form_fsclose();
        if ($conf['gis_ol_yahoo']==1){
            //Don't know how to access this functionality yet via OpenLayers. Yahoo API here: http://developer.yahoo.com/maps/ajax/index.html#ex1
            //shn_form_fsopen('Viewport Settings');
            //shn_form_checkbox(_t('Yahoo Map View'),'ol_yahoo_maps');
            //shn_form_checkbox(_t('Yahoo Satellite View'),'ol_yahoo_sat');
            //shn_form_checkbox(_t('Yahoo Hybrid View'),'ol_yahoo_map_hybrid');
            //shn_form_fsclose();
            shn_form_fsopen('API Key');
            shn_form_fsopen('INFO');
            echo _t("<p>Yahoo Maps requires a key for operation</p>");
            echo _t("<p>Register a Yahoo Map key, and enter it below</p>");
            echo _t("<p>(You can register your own Yahoo Maps key at: <a href='http://developer.yahoo.com/wsregapp/' target=_blank>Yahoo Maps</a>)</p>");
            shn_form_fsclose();
            shn_form_fsopen('Enter API Key');
            shn_form_text(_t("Enter Yahoo Maps Key"),"gis_yahoo_key",'size="100"',array('value'=>$conf['gis_yahoo_key']));
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
        if(!null==$_POST['ol_yahoo']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_yahoo']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo','{$_POST['ol_yahoo']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_yahoo_maps']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_maps' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_yahoo_maps']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_maps'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_maps','{$_POST['ol_yahoo_maps']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_yahoo_sat']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_sat' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_yahoo_sat']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_sat'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_sat','{$_POST['ol_yahoo_sat']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['ol_yahoo_hybrid']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_hybrid' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_yahoo_hybrid']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_hybrid'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_hybrid','{$_POST['ol_yahoo_hybrid']}')";
                $db->Execute($insert);
            }
        }
        if(!null==$_POST['gis_yahoo_key']){
            $query = "SELECT * FROM config WHERE confkey='gis_yahoo_key' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['gis_yahoo_key']}' WHERE module_id = 'admin' AND confkey = 'gis_yahoo_key'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_yahoo_key','{$_POST['gis_yahoo_key']}')";
                $db->Execute($insert);
            }
        }
    }

}
 
?>

