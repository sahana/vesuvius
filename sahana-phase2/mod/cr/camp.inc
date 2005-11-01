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
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_text("Camp Name","camp_name",'size="60"');
	shn_form_opt_select("opt_camp_type","Camp Type");
	shn_form_opt_select("opt_location_type","Division");
	shn_form_textarea("Address","camp_address");
	shn_form_fsclose();
	shn_form_fsopen("Contact Person Details");
	shn_form_text("Full Name","camp_contact_name",'size="60"');
	shn_form_text("Phone Number","camp_contact_number",'size="60"');
	shn_form_fsclose();
	shn_form_fsopen("Camp Population");
	shn_form_text("Family Count","family",'size="10"');
	shn_form_text("Total Count","total",'size="10"');
	shn_form_text("Men","men",'size="10"');
	shn_form_text("Women","women",'size="10"');
	shn_form_text("Children","children",'size="10"');
	shn_form_fsclose();
	shn_form_submit("Next");
	shn_form_fclose();
}

function _shn_cr_cadd_chk(){
	global $global;
	$_SESSION['camp_name']=$_POST['camp_name'];
	$_SESSION['opt_camp_type']=$_POST['opt_camp_type'];
	$_SESSION['opt_location_type']=$_POST['opt_location_type'];
	$_SESSION['camp_address']=$_POST['camp_address'];
	$_SESSION['camp_contact_name']=$_POST['camp_contact_name'];
	$_SESSION['camp_contact_number']=$_POST['camp_contact_number'];
	$_SESSION['camp_family']=$_POST['family'];
	$_SESSION['camp_men']=$_POST['men'];
	$_SESSION['camp_women']=$_POST['women'];
	$_SESSION['camp_children']=$_POST['children'];
	$_SESSION['camp_total']=$_POST['total'];
	//var_dump($_SESSION);
	
	shn_form_fopen(acmp);
  shn_form_fsopen("Services / Facilities Available");
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_opt_checkbox("opt_camp_service");
	shn_form_textarea("Other Facilities","comments");
	shn_form_fsclose();
	shn_form_submit("Next");
	shn_form_fclose();
		
}

function _shn_cr_cadd_commit(){
	global $global;
	//write to database
	$_SESSION['camp_children']=$_POST['children'];
	
	var_dump($_SESSION);
}

function _shn_cr_create_cid(){
	//create unique camp id
}

?>

