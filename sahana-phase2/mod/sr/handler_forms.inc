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
	print "<br>display new report forms";
}

// Capture report details
function shn_sr_report_detail_form()
{
	print "<br>dsiplay report details";
	_shn_sr_form_summary();
	_shn_sr_form_event_dev();
	_shn_sr_form_action();
	_shn_sr_form_key_figures();
}

// Summary report form
function _shn_sr_form_summary()
{
	print "<br>Summary goes here";
}

// Event development report form
function _shn_sr_form_event_dev()
{
	print "<br>Event development goes here";
}

// Action report form
function _shn_sr_form_action()
{
	print "<br>Action goes here";
}

// Key-Figures report form
function _shn_sr_form_key_figures()
{
	print "<br>Key-Figures goes here";
}



?>