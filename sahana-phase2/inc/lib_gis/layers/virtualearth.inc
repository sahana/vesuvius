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
* @version      $Id: virtualearth.inc,v 1.10 2008-04-23 23:52:57 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class virtualearth implements layer{

    // To avoid parent constructor being called
    //function virtualearth(){
    //}

    function print_form()
    {	
        global $conf;
        shn_form_fsopen(_t('MS Virtual Earth'));
        shn_form_fsopen(_t('MS Virtual Earth'));
        shn_form_fsopen(_t('INFO'));
        echo _t("<p>Enable <a href='http://maps.live.com/ target=_blank'>Microsoft Virtual Earth</a> &trade; Mapping Service by selecting the checkbox option below.</p>");
        echo _t("<p>The Virtual Earth mapping API requires Internet connectivity</p>");
        shn_form_fsclose();
        shn_form_fsopen(_t('ENABLE'));
        $checked='';
        if ($conf['gis_ol_virtualearth']==1){
            $checked='checked';
        }
        shn_form_checkbox(_t('Enable Microsoft Virtual Earth'),'ol_virtualearth',$checked,array('value'=>1));	
        shn_form_fsclose();
        shn_form_fsclose();
        shn_form_fsclose();
    }

    function commit_values()
    {
        global $global;
        global $conf;
        $db = $global['db'];
        // Checkboxes return nothing if unticked!
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
