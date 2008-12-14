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
* @version		$Id: multimap.inc,v 1.19 2008-12-14 00:24:08 franboon Exp $
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
        echo '<p>'._t("Enable").' <a href="http://multimap.com/" target=_blank>Multimap</a> &trade; '._t("Mapping Service by selecting the checkbox option below.").'</p>';
        echo '<p>'._t("The Multimap mapping API requires Internet connectivity and a valid Multimap key").'.</p>';
        echo '<p><b>'._t("NB The Multimap layer currently doesn't work well due to an").' <a href="http://trac.openlayers.org/ticket/953" target=_blank>OpenLayers-2.7</a> '._t("limitation").' '._t("with this projection").'!</b></p>';
        if (!0==$conf['gis_ol_projections']) {
            echo '<h1>'._t("MultiMap base layer is currently DISABLED due to use of a").' <a href="index.php?mod=admin&act=gis_projections" target=_blank>'._t("non-SphericalMercator Projection").'</a>!</h1>';
        }
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
            echo '<p>'._t("Multimap requires a  key for operation").'</p>';
            echo '<p>'._t("Register a multimap key, and enter it below").'</p>';
            echo '<p>('._t("You can register your own Multimap key at").': <a href="http://multimap.com" target=_blank>Multimap</a>)</p>';
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

