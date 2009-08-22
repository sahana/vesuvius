<?php
/** AJAX for  CR
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
include($global['approot'].'/mod/cr/camp.inc');

array_push($global['xajax_functions'],'cr_check_shelter_name');

function cr_check_shelter_name($shetler_name){
   global $global;

    if(shn_cr_shelter_name_exist($shetler_name)){
        $global['xajax_res']->addAssign('check','innerHTML','<span style=\'color:red\'>'.$shetler_name. ' ' . _t('is already registered').'</span>');
    }
    else{
        $global['xajax_res']->addAssign('check','innerHTML','<span style=\'color:green\'>' . $shetler_name .' '._t('is available to register').'</span>');
    }
    return $global['xajax_res']->getXML();
}

