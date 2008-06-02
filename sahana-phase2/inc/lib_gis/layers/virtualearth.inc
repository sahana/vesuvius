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
* @version      $Id: virtualearth.inc,v 1.15 2008-06-02 13:35:43 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class virtualearth implements layer{
	
	function print_form()
	{
		global $conf;
        shn_form_fsopen(_t('MS Virtual Earth'));
        shn_form_fsopen(_t('MS Virtual Earth'));
		shn_form_fsopen('INFO');
        echo '<p>'._t("Enable").' <a href="http://maps.live.com" target=_blank>Microsoft Virtual Earth</a> &trade; '._t("Mapping Service by selecting the checkbox option below").'.</p>';
        echo '<p>'._t("The Virtual Earth mapping API requires Internet connectivity").'.</p>';
        if (!0==$conf['gis_ol_projections']) {
            echo '<h1>'._t("Virtual Earth base layer(s) are currently DISABLED due to use of a").' <a href="index.php?mod=admin&act=gis_projections" target=_blank>'._t("non-SphericalMercator Projection").'</a>!</h1>';
        }
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_virtualearth']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Virtual Earth Maps'),'ol_virtualearth',$checked,array('value'=>1));	
		shn_form_fsclose();
		shn_form_fsclose();
        if ($conf['gis_ol_virtualearth']==1){
            shn_form_fsopen('Viewport Settings');
            echo '<p>'._t("Virtual Earth supports 3 types of layer which can each be enabled separately").'</p>';
            echo '<p>('._t("If none are selected then no Virtual Earth layer will appear").')</p>';
            echo '<br />';
            $checked='';
            if ($conf['gis_ol_virtualearth_maps']==1){
                $checked='checked';
            }
            $maps_help=_t("A layer with just Maps shown");
            shn_form_checkbox(_t('Map view enabled?'),'ol_virtualearth_maps',$checked,array('value'=>1,"help"=>$maps_help));
            $checked='';
            if ($conf['gis_ol_virtualearth_aerial']==1){
                $checked='checked';
            }
            $aerial_help=_t("A layer with just Aerial Photos shown");
            shn_form_checkbox(_t('Aerial view enabled?'),'ol_virtualearth_aerial',$checked,array('value'=>1,"help"=>$aerial_help));
            $checked='';
            if ($conf['gis_ol_virtualearth_hybrid']==1){
                $checked='checked';
            }
            $hybrid_help=_t("A layer with Maps & Satellite Photos shown together");
            shn_form_checkbox(_t('Hybrid view enabled?'),'ol_virtualearth_hybrid',$checked,array('value'=>1,"help"=>$hybrid_help));
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
        if (1 == $conf['gis_ol_virtualearth']){
            // Checkboxes return nothing if unticked!
            if (null == $_POST['ol_virtualearth_maps']){
                $ol_virtualearth_maps=0;
            }
            if (1 == $_POST['ol_virtualearth_maps']){
                $ol_virtualearth_maps=1;
            }
            if (!$ol_virtualearth_maps == $conf['gis_ol_virtualearth_maps']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_virtualearth_maps' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_virtualearth_maps' WHERE module_id = 'admin' AND confkey = 'gis_ol_virtualearth_maps'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_virtualearth_maps','$ol_virtualearth_maps')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_virtualearth_aerial']){
                $ol_virtualearth_aerial=0;
            }
            if (1 == $_POST['ol_virtualearth_aerial']){
                $ol_virtualearth_aerial=1;
            }
            if (!$ol_virtualearth_aerial == $conf['gis_ol_virtualearth_aerial']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_virtualearth_aerial' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_virtualearth_aerial' WHERE module_id = 'admin' AND confkey = 'gis_ol_virtualearth_aerial'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_virtualearth_aerial','$ol_virtualearth_aerial')";
                    $db->Execute($insert);
                }
            }
            if (null == $_POST['ol_virtualearth_hybrid']){
                $ol_virtualearth_hybrid=0;
            }
            if (1 == $_POST['ol_virtualearth_hybrid']){
                $ol_virtualearth_hybrid=1;
            }
            if (!$ol_virtualearth_hybrid == $conf['gis_ol_virtualearth_hybrid']) {
                $query = "SELECT * FROM config WHERE confkey='gis_ol_virtualearth_hybrid' AND module_id='admin'";
                $res = $db->Execute($query);
                if(!$res->EOF){
                    $q = "UPDATE config SET value = '$ol_virtualearth_hybrid' WHERE module_id = 'admin' AND confkey = 'gis_ol_virtualearth_hybrid'";       
                    $db->Execute($q);
                }
                else{
                    $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_virtualearth_hybrid','$ol_virtualearth_hybrid')";
                    $db->Execute($insert);
                }
            }
        }
        if (null == $_POST['ol_virtualearth']){
            $ol_virtualearth=0;
        }
        if (1 == $_POST['ol_virtualearth']){
            $ol_virtualearth=1;
        }
        if (!$ol_virtualearth == $conf['gis_ol_virtualearth']) {
            $query = "SELECT * FROM config WHERE confkey='gis_ol_virtualearth' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$ol_virtualearth' WHERE module_id = 'admin' AND confkey = 'gis_ol_virtualearth'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_virtualearth','$ol_virtualearth')";
                $db->Execute($insert);
            }
        }
    }

}
 
?>

