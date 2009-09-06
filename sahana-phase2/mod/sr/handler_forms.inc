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
	// creates a date in the YYYYMMDD format,
	// ready to be inserted into the form as a default name
	$date = getdate();
	$date = $date['year'].sprintf("%02d",$date['mon']).sprintf("%02d",$date['mday']);
	
	shn_form_fopen("form_submit", null,array('req_message' => true));
		shn_form_fsopen(_t("Report Information"));
			shn_form_hidden(array("key"=>"reg"));
			shn_form_text(_t('Report Name'), 'name',null,array('req'=>true,'value'=>$date));
			shn_form_textarea(_t('Description'),'desc',$text_opt, $extra_opts = null);
			// this function has not been implemented yet
			// shn_sr_alert(); 
		shn_form_fsclose();	
		shn_form_submit(_t("Register"),$submit_opts = null);
	shn_form_fclose();
	
	unset($date);
}

function shn_sr_alert()
{
    # create the ability to make a message an alert.
    # This alert will be able to be picked up by JQuery and turned into
    # <div id="alert_head">
    
    # checkbox, to select alert status
    shn_form_opt_checkbox('alert_status');
    $label = _t('Alert?');
    $name = 'alert_head';
    #$extra_opts[help] = 'Click to create a global alert.' 
    
    shn_form_checkbox($label, $name, $text_opts = null, $extra_opts = null); 
}

function shn_sr_template_generator($template, $array_of_fields){

}

function shn_sr_report_skeleton($rpt_template = 'default') {
//for each row in sections
}

// Capture report details
function shn_sr_report_detail_form($rpt_id, $rpt_name)
{
	//_shn_sr_check_editor(); // working on right now
	print '<h1>'._t("Report Information").'</h1>';
	// pull latest existing reports
	$values = shn_sr_pull_report_content($rpt_id);
	//print_r($values);
	
	shn_form_fopen("form_submit",null,array ('req_message' => false,'tab'=>'float'));
		
		print _t("Report Name")." : <b>$rpt_name</b><br /><br />";
		
		shn_form_hidden(array("key"=>"reports"));
		shn_form_hidden(array("id"=>"$rpt_id"));
		shn_form_hidden(array("name"=>"$rpt_name"));
		shn_form_fsopen(_t('Summary'));
			_shn_sr_form_summary($values[2]);
		shn_form_fsclose();
		shn_form_fsopen(_t('Event'));
			_shn_sr_form_event_dev($values[3]);
		shn_form_fsclose();	
		shn_form_fsopen(_t('Actions'));
			_shn_sr_form_action($values[4]);
		shn_form_fsclose();
		shn_form_fsopen(_t('Figures'));
			_shn_sr_form_key_figures($values[5]);
		shn_form_fsclose();
		shn_form_drawtab();
		//$date = date("D dS  M, Y  -  h:i a",$values[0]);
		$date = date_create($values[0]);
		$date = date_format($date, 'jS, F Y - g:i a');
		
		//print "<font color=silver>Last updated : $values[0] by $values[1]</font><br><br>";
		print "<font color=\"silver\">"._t('Last updated')." : $date by $values[1]</font><br /><br />";
		
		shn_form_submit(_t("Save"),"name='chk'");
		shn_form_submit(_t("Cancel"),"name='chk'");
	shn_form_fclose();
	
}

// Check for editor (ie. Fckeditor or )
function _shn_sr_check_editor()
{
	// Accessing conf editor value
	global $conf;
	
	$dir_name = "res/fckeditor";
	
	// if it's fckeditor
	if ($conf['wysiwyg']=='fckeditor'){
		print "fckeditor";
		if(is_dir($dir_name)){
			print ' '._t("is the directory.");
		} else {
			print ' '._t("but can not find the directory.");
		}
	
	// if it's tiny_mce	
	} elseif ($conf['wysiwyg']=='tiny_mce'){
		print "tiny_mce";
	} else {
	print  $conf['wysiwyg'];
	}
	
	
}

// Summary report form
function _shn_sr_form_summary($val)
{
	shn_form_wysiwyg(_t('Summary of Events Report'),'summary',array('value'=>$val));
}

// Event development report form
function _shn_sr_form_event_dev($val)
{
	shn_form_wysiwyg(_t('Predicted Event Development Report'),'event',array('value'=>$val));
	//shn_form_fckeditor(_t('Event Development Report'),'event',null,array('value'=>$res['event']));
}

// Action report form
function _shn_sr_form_action($val)
{
	shn_form_wysiwyg(_t('Actions Taken Report'),'action',array('value'=>$val));
	//shn_form_fckeditor(_t('Action Report'),'action',null,array('value'=>$res['action']));
}

// Key-Figures report form
function _shn_sr_form_key_figures($val)
{
	shn_form_wysiwyg(_t('Key Figures Report'),'figure',array('value'=>$val));
	//shn_form_fckeditor(_t('Key Figure Report'),'figure',null,array('value'=>$res['figure']));
}

// Display requested sitrep
function shn_sr_view_report($rpt_id, $rpt_name, $author, $summary, $event, $action, $figure, $status, $update_date)
{
	print '<h1>'._t('Report Information').'</h1>';
	
	shn_form_fopen("",null,array ('req_message' => false));
		print _t('Report Name')." : <b>$rpt_name</b><br /><br />";
		shn_form_fsopen(_t('Summary of Events'));
			print $summary;
		shn_form_fsclose();
		shn_form_fsopen(_t('Predicted Event Development'));
			print $event;
		shn_form_fsclose();	
		shn_form_fsopen(_t('Actions Taken'));
			print $action;
		shn_form_fsclose();
		shn_form_fsopen(_t('Key Figures'));
			print $figure;
		shn_form_fsclose();
		
		// display last update date/time
		$date = date_create($update_date);
		$date = date_format($date, 'jS, F Y - g:i a');
		
		print "<font color=\"silver\">"._t('Last updated')." : $date by $values[1]</font><br /><br />";
		
		print _t("Select").":&nbsp;&nbsp;&nbsp;<a href='index.php?mod=sr&act=view'>".
		_t('Back')."</a>&nbsp;&nbsp;&nbsp; 
		<a href='index.php?mod=sr&act=report_update&id=$rpt_id&rpt=$rpt_name'>".
		_t('Update')."</a>&nbsp;&nbsp;";
	shn_form_fclose();	
		
}


