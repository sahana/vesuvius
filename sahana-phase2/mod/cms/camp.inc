<?php
/* $Id; */

/**Camp library for  CMS
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
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_cms_cadd_form($errors=false){
	echo "<h2>"._("Add New Camp - Details")."</h2>";
	
	if($errors)
		display_errors();
		
	global $global;
	$db=$global['db'];
		
	//show add camp form
	shn_form_fopen(cadd);
	shn_form_fsopen(_("Name and Type"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_("Camp Name"),"camp_name",'size="50"',array('req'=>true));
	shn_form_opt_select("opt_camp_type",_("Camp Type"));
	shn_form_fsclose();
	shn_form_fsopen(_("Camp Administrator"));
	shn_form_text(_("Camp Admin Name"),"admin_name",'size="50"');
	shn_form_text(_("Contact Number"),"admin_no",'size="50"');
	shn_form_text(_("Organization Name"),"org_name",'size="50"');
	shn_form_fsclose();
	shn_form_fsopen(_("General Details"));
	shn_form_text(_("Distance from City [km]"),"city_dis",'size="50"');
	shn_form_text(_("Distance from Disaster [km]"),"disas_dis",'size="50"');
	shn_form_text(_("Approximate Capacity [people]"),"capacity",'size="50"');
	shn_form_text(_("Number of Shelters"),"shelters",'size="50"');
	shn_form_text(_("Approximate Area Size [square metres]"),"camp_size",'size="50"');
	shn_form_fsclose();
	shn_form_submit(_("Create Camp"));
	shn_form_fclose();
			



}

function _shn_cms_cadd_guide(){
	global $global;
	//attach guidelines;
	
?>
	<h2>New Camp Guidlines</h2>
	<div id="home">
<?php
	include($global['approot'].'/mod/cms/guide.inc');
?>
	</div>
<?php
	shn_form_fopen(cadd);
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_submit(_("Accept"));
}

function _shn_cms_cadd_chk(){
	global $global;
	echo "<h2>"._("Camp Checklist")."</h2>";
	shn_form_fopen(cadd);
	shn_form_fsopen(_("Facilities / Services"));
	shn_form_hidden(array('seq'=>'form'));
	shn_form_opt_checkbox("opt_camp_service");
	shn_form_fsclose();
	shn_form_submit(_("Done"));
	shn_form_fclose();
			
}

function _shn_cms_cedt(){
	global $global;
?>
<h2>Edit Existing Camp</h2>
<?
}

function _shn_cms_exit(){
	global $global;
?>
<h2>Camp Exit Procedure</h2>
<?
}
?>
