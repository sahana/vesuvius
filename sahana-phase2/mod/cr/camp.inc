<?php
/* $Id; */

/**Camp library for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_cr_cadd_start(){
	global $global;

	shn_form_fopen(acmp);
	shn_form_fsopen("General Details");
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text("Camp Name","camp_name",'size="60"');
	shn_form_opt_select("opt_camp_type","Camp Type");
	shn_form_opt_select("opt_location_type","Division");
	shn_form_text("Area","camp_area",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen("Contact Person Details");
	shn_form_text("Full Name","camp_contact_name",'size="60"');
	shn_form_text("Phone Number","camp_contact_number",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen("Other Details");
	shn_form_text("Accessibility","access",'size="60"');
	shn_form_text("Capability","capable",'size="60"');
	shn_form_text("Comments","comment",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen("Camp Population");
	shn_form_text("Family Count","family",'size="10"');
	shn_form_text("Total Count","capable",'size="10"');
	shn_form_text("Men","men",'size="10"');
	shn_form_text("Women","women",'size="10"');
	shn_form_text("Children","children",'size="10"');
	shn_form_fsclose();
	shn_form_fclose();
}

?>

