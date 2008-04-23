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
* @version		$Id: virtualearth.inc,v 1.6 2008-04-23 14:13:33 franboon Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class virtualearth implements layer{

    function print_form()
    {	
        global $conf;
        shn_form_fsopen(_t('MS Virtual Earth'));
        shn_form_fsopen('MS Virtual Earth');
        shn_form_fsopen('INFO');
        echo _t("<p>Enable <a href='http://maps.live.com/'>Microsoft Virtual Earth</a> &trade; Mapping Service" .
        " by selecting the checkbox option below.</p>");
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
        global $conf;
        $db = $global['db'];
        if(!null==$_POST['ol_virtualearth']){
            $query = "SELECT * FROM config WHERE confkey='gis_ol_virtualearth' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['ol_virtualearth']}' WHERE module_id = 'admin' AND confkey = 'gis_ol_virtualearth'";       
                $db->Execute($q);
            }
            else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_ol_virtualearth','{$_POST['ol_virtualearth']}')";
                $db->Execute($insert);
            }
        }
    }

}
 
?>

