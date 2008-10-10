<?php

/** AJAX for  Admin
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Kethees <ks@respere.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

global $global;

array_push($global['xajax_functions'],'admin_get_field_options');

include_once 'lib_fo_config.inc';


function admin_get_field_options($field_name){	
    global $global;
    $res = shn_admin_field_options_xajax($field_name);
    foreach ($res as $rs){
       $html .= "<option value =". $rs['option_code'].">" . $rs['option_description'] . "</option>";
    }
    $global['xajax_res']->addAssign('opt_data','innerHTML',$html);

    return $global['xajax_res']->getXML();
}
?>