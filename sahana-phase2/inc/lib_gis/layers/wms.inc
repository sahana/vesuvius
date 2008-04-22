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
* @version      $Id: wms.inc,v 1.4 2008-04-22 14:14:44 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class wms implements layer{

    function wms()
    {

    }

    /**
     * @ToDo Change to an Add/Edit/Delete mode to avoid 1 long form
     */
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
                shn_form_text(_t('Description'),'gis_ol_wms_'.$j.'_description','size=40',array('value'=>$conf['gis_ol_wms_'.$j.'_description']));
                shn_form_text(_t('Name'),'gis_ol_wms_'.$j.'_name',null,array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_name']));
                $types = array(_t('base'),_t('overlay'));
                $type_select = _t('base');
                if ($conf['gis_ol_wms_'.$j.'_type']=='overlay') {
                    $type_select = _t('overlay');
                }
                shn_form_select($types,_t('Type'),'gis_ol_wms_'.$j.'_type',null,array('value'=>$type_select));
                shn_form_text(_t('URL'),'gis_ol_wms_'.$j.'_url','size=40',array('req'=>true,'value'=>$conf['gis_ol_wms_'.$j.'_url']));
                shn_form_text(_t('Layers'),'gis_ol_wms_'.$j.'_layers',null,array('value'=>$conf['gis_ol_wms_'.$j.'_layers']));
                shn_form_text(_t('IMG'),'gis_ol_wms_'.$j.'_img',null,array('value'=>$conf['gis_ol_wms_'.$j.'_img']));
                shn_form_text(_t('Transparency'),'gis_ol_wms_'.$j.'_transparency',null,array('value'=>$conf['gis_ol_wms_'.$j.'_transparency']));
                shn_form_text(_t('Min'),'gis_ol_wms_'.$j.'_min',null,array('value'=>$conf['gis_ol_wms_'.$j.'_min']));
                shn_form_text(_t('Max'),'gis_ol_wms_'.$j.'_max',null,array('value'=>$conf['gis_ol_wms_'.$j.'_max']));
                shn_form_fsclose();
            }
        }
        shn_form_fsclose();
    }
}
 
?>
