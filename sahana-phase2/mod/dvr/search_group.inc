<?php
/* $Id: search_group.inc,v 1.1 2006-12-04 06:37:37 isurunishan Exp $ */
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
     shn_form_fopen("search_group",null,array('req_message'=>true));
    ?>
    <?php
    
    shn_form_hidden(array('seq'=>'chk'));
    shn_form_fsopen(_("General Search"));
    print '<div class="info">';
    print _("Please select a Group that describes you well");
    print '<br />';
  
    print '<br />';
    print '</div>';
    print '<br />';
    
    
    $typ_of_grp = array();
    
    
    array_push($typ_of_grp,'-- Select Category --');
    array_reverse($typ_of_grp);
    $typ_of_grp[1] = "Families";
    $typ_of_grp[2] = "Passengers";
    $typ_of_grp[3] = "Tourists";
    $typ_of_grp[4] = "Other";
    
    
    $extra_opts['value']= $typ_of_grp;
    $extra_opts['help']=_("Enter the National Identity Card Number if available. (Optional)");
    $extra_opts['req']=true;
    
    
    shn_form_select($typ_of_grp, _("Type Of Group"),'typ_of_grp',"onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", $extra_opts);    
    
   
   // shn_form_fclose();


    //shn_form_fopen("hd_of_grp",null,array('req_message'=>false));
   // shn_form_hidden(array('seq'=>'add_reqstr'));
     
    shn_form_text(_('Any Card Number'),'card','size="30"');
    shn_form_text(_('Any Name'),'name','size="30"');
 shn_form_submit(_('Next'));
      shn_form_fsclose();
      shn_form_fclose();
}

//advanced search to be completed

function shn_mpr_search_advanced()
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