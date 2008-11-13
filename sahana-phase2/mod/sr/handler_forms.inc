<?php
/**
* The Situation Report (SITRep) Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   sr
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';

// Regsiter new report
function shn_sr_report_register()
{
	shn_form_fopen("form_submit", null,array('req_message' => true));
		shn_form_fsopen(_t("Report Information"));
			shn_form_hidden(array("key"=>"reg"));
			shn_form_text(_t('Report Name'), 'name',null,array('req'=>true));
			shn_form_textarea(_t('Description'),'desc',$text_opt, $extra_opts = null);
		shn_form_fsclose();	
		shn_form_submit(_t("Register"),$submit_opts = null);
	shn_form_fclose();
	
}

// Capture report details
function shn_sr_report_detail_form($rpt_id)
{
	print "<h1>Report Information</h1>";
	
	// pull latest existing reports
	$values = shn_sr_pull_report_content($rpt_id);
	//print_r($values);
	//print $values[2];
	
	shn_form_fopen("form_submit",null,array ('req_message' => false,'tab'=>'float'));
		shn_form_hidden(array("key"=>"reports"));
		shn_form_hidden(array("id"=>"$rpt_id"));
		shn_form_fsopen('Summary');
			_shn_sr_form_summary($values[2]);
		shn_form_fsclose();
		shn_form_fsopen('Event');
			_shn_sr_form_event_dev($values[3]);
		shn_form_fsclose();	
		shn_form_fsopen('Action');
			_shn_sr_form_action($values[4]);
		shn_form_fsclose();
		shn_form_fsopen('Figures');
			_shn_sr_form_key_figures($values[5]);
		shn_form_fsclose();
		shn_form_drawtab();
		shn_form_submit(_t("Update"),$submit_opts = null);
	shn_form_fclose();
}

// Summary report form
function _shn_sr_form_summary($val)
{
	shn_form_wysiwyg(_t('Summary Report'),'summary',array('value'=>$val));
}

// Event development report form
function _shn_sr_form_event_dev($val)
{
	shn_form_wysiwyg(_t('Event Development Report'),'event',array('value'=>$val));
	//shn_form_fckeditor(_t('Event Development Report'),'event',null,array('value'=>$res['event']));
}

// Action report form
function _shn_sr_form_action($val)
{
	shn_form_wysiwyg(_t('Action Report'),'action',array('value'=>$val));
	//shn_form_fckeditor(_t('Action Report'),'action',null,array('value'=>$res['action']));
}

// Key-Figures report form
function _shn_sr_form_key_figures($val)
{
	shn_form_wysiwyg(_t('Key Figure Report'),'figure',array('value'=>$val));
	//shn_form_fckeditor(_t('Key Figure Report'),'figure',null,array('value'=>$res['figure']));
}



?>