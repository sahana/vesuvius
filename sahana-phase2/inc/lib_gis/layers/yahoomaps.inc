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
* @version		$Id: yahoomaps.inc,v 1.14 2008-06-02 13:35:43 franboon Exp $
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
		echo '<p>'._t("Enable").' <a href="http://maps.yahoo.com" target=_blank>Yahoo Maps</a> &trade; '._t("Mapping Service by selecting the checkbox option below").'.</p>';
		echo '<p>'._t("The Yahoo Maps mapping API requires Internet connectivity and a valid Yahoo Maps key").'.</p>';
        if (!0==$conf['gis_ol_projections']) {
            echo '<h1>'._t("Yahoo Maps base layer(s) are currently DISABLED due to use of a").' <a href="index.php?mod=admin&act=gis_projections" target=_blank>'._t("non-SphericalMercator Projection").'</a>!</h1>';
        }
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
            shn_form_fsopen('Viewport Settings');
            echo '<p>' . _t("Yahoo supports 3 types of layer which can each be enabled separately")  . '</p>';
            echo '<p>(' . _t("If none are selected then no Yahoo layer will appear")  . ')</p>';
            echo '<br />';
            $checked='';
            if ($conf['gis_ol_yahoo_maps']==1){
                $checked='checked';
            }
            $maps_help=_t("A layer with just Maps shown");
            shn_form_checkbox(_t('Map view enabled?'),'ol_yahoo_maps',$checked,array('value'=>1,"help"=>$maps_help));
            $checked='';
            if ($conf['gis_ol_yahoo_sat']==1){
                $checked='checked';
            }
            $sat_help=_t("A layer with just Satellite Photos shown");
            shn_form_checkbox(_t('Satellite view enabled?'),'ol_yahoo_sat',$checked,array('value'=>1,"help"=>$sat_help));
            $checked='';
            if ($conf['gis_ol_yahoo_hybrid']==1){
                $checked='checked';
            }
            $hybrid_help=_t("A layer with Maps & Satellite Photos shown together");
            shn_form_checkbox(_t('Hybrid view enabled?'),'ol_yahoo_hybrid',$checked,array('value'=>1,"help"=>$hybrid_help));
            shn_form_fsclose();
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
        // Only consider the inner-checkboxes if they are visible
        if (1 == $conf['gis_ol_yahoo']){
            // Checkboxes return nothing if unticked!
            if (null == $_POST['ol_yahoo_maps']){
                $ol_yahoo_maps=0;
            }
            if (1 == $_POST['ol_yahoo_maps']){
                $ol_yahoo_maps=1;
            }
            if (!$ol_yahoo_maps == $conf['gis_ol_yahoo_maps']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_maps' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_yahoo_maps' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_maps'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_maps','$ol_yahoo_maps')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_yahoo_sat']){
                $ol_yahoo_sat=0;
            }
            if (1 == $_POST['ol_yahoo_sat']){
                $ol_yahoo_sat=1;
            }
            if (!$ol_yahoo_sat == $conf['gis_ol_yahoo_sat']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_sat' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_yahoo_sat' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_sat'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_sat','$ol_yahoo_sat')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_yahoo_hybrid']){
                $ol_yahoo_hybrid=0;
            }
            if (1 == $_POST['ol_yahoo_hybrid']){
                $ol_yahoo_hybrid=1;
            }
            if (!$ol_yahoo_hybrid == $conf['gis_ol_yahoo_hybrid']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo_hybrid' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_yahoo_hybrid' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo_hybrid'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo_hybrid','$ol_yahoo_hybrid')";
                    $db->Execute($insert);
                }
            }
        }
        if (null == $_POST['ol_yahoo']){
            $ol_yahoo=0;
        }
        if (1 == $_POST['ol_yahoo']){
            $ol_yahoo=1;
        }
        if (!$ol_yahoo == $conf['gis_ol_yahoo']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_yahoo' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$ol_yahoo' WHERE module_id = 'admin' AND confkey = 'gis_ol_yahoo'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_yahoo','$ol_yahoo')";
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

