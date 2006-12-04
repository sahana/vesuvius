<?php
/* $Id: search_individual.inc,v 1.1 2006-12-04 06:38:01 isurunishan Exp $ */
/**
 * 
 * Search groups and individuals in disaster victims registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


function _shn_dvr_search_default()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen(_('General Search'));
    shn_form_text(_('Any Card Number'),'card','size="30"');
    shn_form_text(_('Any Name'),'name','size="30"');
 
    shn_form_checkbox(_('All incidents'),'all_incidents');
    shn_form_submit(_('Next'));
//advanced search link
    shn_form_fsclose();
    shn_form_fclose();
}

//advanced search to be completed

function shn_mpr_search_advance()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen(_('Advanced Search'));

    shn_form_fsopen(_('Identity'));
    shn_form_text(_('Identity'),'idcard','size="30"');
    shn_form_checkbox('Identity Card','idcard_chk');
    shn_form_checkbox('Passport Number','pass_chk');
    shn_form_checkbox('Driving License','drv_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Name'));
    shn_form_text(_('Name'),'name','size="30"');
    shn_form_checkbox('Full Name','fullname_chk');
    shn_form_checkbox('Family Name','familyname_chk');
    shn_form_checkbox('Local Name','localname_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Basic Details'));
    shn_form_fsclose();

    shn_form_submit(_('Next'));
    shn_form_fsclose();
    shn_form_fclose();

}

?>