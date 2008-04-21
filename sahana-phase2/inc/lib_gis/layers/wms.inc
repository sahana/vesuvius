<?php

/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id: wms.inc,v 1.1 2008-04-21 23:49:03 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class wms implements layer{

    function wms()
    {

    }

    function print_form()
    {
        global $conf;
        shn_form_fsopen(_t('WMS'));
        shn_form_fsopen(_t('INFO'));
        echo _t("<p>Sahana can make use of Maps from servers using the <a href='http://www.opengeospatial.org/standards/wms'>WMS (Web Map Service)</a> standard </p>");
        echo _t("<p>Enable WMS Layers by selecting the checkbox option below.</p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if (!$conf['gis_ol_wms']==0){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable WMS layers'),'wms_enable',$checked);
        shn_form_fsclose();
	if (!$conf['gis_ol_wms']==0){
            shn_form_fsopen(_t('NUMBER'));
            shn_form_text(_t('Number of WMS layers'),'gis_ol_wms','size=2 maxlength=2',array('value'=>$conf['gis_ol_wms']));
            shn_form_fsclose();
            for ($i=0; $i<$conf['gis_ol_wms']; $i++) {
                $j=$i+1;
                shn_form_fsopen(_t('LAYER '.$j));
                shn_form_text(_t('Description'),'gis_ol_wms_1_description','size=40',array('value'=>$conf['gis_ol_wms_1_description']));
                shn_form_text(_t('Name'),'gis_ol_wms_1_name',null,array('value'=>$conf['gis_ol_wms_1_name']));
                shn_form_text(_t('Type'),'gis_ol_wms_1_type',null,array('value'=>$conf['gis_ol_wms_1_type']));
                shn_form_text(_t('URL'),'gis_ol_wms_1_url','size=40',array('value'=>$conf['gis_ol_wms_1_url']));
                shn_form_text(_t('Layers'),'gis_ol_wms_1_layers',null,array('value'=>$conf['gis_ol_wms_1_layers']));
                shn_form_text(_t('IMG'),'gis_ol_wms_1_img',null,array('value'=>$conf['gis_ol_wms_1_img']));
                shn_form_text(_t('Transparency'),'gis_ol_wms_1_transparency',null,array('value'=>$conf['gis_ol_wms_1_transparency']));
                shn_form_text(_t('Min'),'gis_ol_wms_1_min',null,array('value'=>$conf['gis_ol_wms_1_min']));
                shn_form_text(_t('Max'),'gis_ol_wms_1_max',null,array('value'=>$conf['gis_ol_wms_1_max']));
                shn_form_fsclose();
            }
        }
        shn_form_fsclose();
    }
}
 
?>
