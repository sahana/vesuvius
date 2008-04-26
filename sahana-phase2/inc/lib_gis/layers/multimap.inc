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
* @version		$Id: multimap.inc,v 1.13 2008-04-26 13:32:00 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class multimap implements layer{
	
    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('Multimap'));
        shn_form_fsopen('Multimap');
        shn_form_fsopen('INFO');
        echo _t("<p>Enable <a href='http://multimap.com/' target=_blank>Multimap</a> &trade; Mapping Service" .
            " by selecting the checkbox option below.</p>");
        echo _t("<p>The Multimap mapping API requires Internet connectivity and a valid Multimap key</p>");
        echo _t("<p><b>NB The Multimap layer currently doesn't work well! (OpenLayers-2.6 limitation with this projection)</b></p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_multimap']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Multimap'),'ol_multimap',$checked,array('value'=>1));	
        shn_form_fsclose();
        shn_form_fsclose();
        if ($conf['gis_ol_multimap']==1){
            shn_form_fsopen('API Key');
            shn_form_fsopen('INFO');
            echo _t("<p>Multimap requires a  key for operation</p>");
            echo _t("<p>Register a multimap key, and enter it below</p>");
            echo _t("<p>You can register your own Multimap key at: <a href='http://multimap.com/' target=_blank>Multimap</a></p>");
            shn_form_fsclose();
            shn_form_fsopen('Enter API Key');
            shn_form_text(_t("Enter Multimap Key"),"gis_multimap_key",'size="100"',array('value'=>$conf['gis_multimap_key']));
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
        // Checkboxes return nothing if unticked!
        if (null == $_POST['ol_multimap']){
            $ol_multimap=0;
        }
        if (1 == $_POST['ol_multimap']){
            $ol_multimap=1;
        }
        if (!$ol_multimap == $conf['gis_ol_multimap']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_multimap' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$ol_multimap' WHERE module_id = 'admin' AND confkey = 'gis_ol_multimap'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_multimap','$ol_multimap')";
                $db->Execute($insert);
            }
        }
        if (!null==$_POST['gis_multimap_key']) {
            $query = "SELECT * FROM config WHERE confkey='gis_multimap_key' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['gis_multimap_key']}' WHERE module_id = 'admin' AND confkey = 'gis_multimap_key'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_multimap_key','{$_POST['gis_multimap_key']}')";
                $db->Execute($insert);
            }
        }
    }

}
 
?>

