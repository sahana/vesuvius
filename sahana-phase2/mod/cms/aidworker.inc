<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Chathra <chathra@opensource.lk>
* @author     Mifan <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function shn_cms_reg_aidworker(){
  echo "<h2>" . _("Aid Worker Registration") . "</h2>";
	if($errors)
	  display_errors();
  global $global;
	$db=$global['db'];
	//show add camp form
	shn_form_fopen(cadd);
	shn_form_fsopen(_("Individual Information"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_("Name"),"name",'size="50"',array('req'=>true));
	shn_form_text(_("ID/SSN/Passport"),"id_no",'size="50"',array('req'=>true));
	shn_form_opt_select("opt_race",_("Race"));
	shn_form_opt_select("opt_religion",_("Religion"));
	shn_form_opt_select("opt_marital_status",_("Marital Status"));
	shn_form_text(_("Phone Number"),"phone",'size="50"');
	shn_form_text(_("Email"),"email",'size="50"');
	shn_form_opt_select("opt_contact_type",_("Contact Type"));
	shn_form_textarea(_("Contact"),"contact",'size="200"');
	shn_form_fsclose();
	shn_form_fsopen(_("Service Information"));
	shn_form_text(_("Organization Name"),"org_name",'size="50"');
	shn_form_text(_("Proffesion"),"job",'size="50"');
	shn_form_textarea(_("Services Offered"),"service",'size="200"');
	shn_form_fsclose();
	shn_form_submit(_("Register"));
	shn_form_fclose();
}


function shn_cms_edit_aidworker(){
   
    echo "<h2><center>" . _("Edit Aid Worker Information") . "</center></h2>";
}                                                                              
?>
