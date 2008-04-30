<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		Sahana - http://sahana.lk/
* @subpackage   msg
* @tutorial
* @version		$Id: lib_survey.inc,v 1.2 2008-04-30 06:16:51 mifanc Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* @contribution	This code was developed and contributed to the project 
* by Respere Lanka (Pvt) Ltd. 
*/

include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';

/*
@author		Pradeeper <pradeeper@respere.com>
@function	display the forms for survey
*/
function shn_msg_send_survey_form()
{
	Print "<h2>Send Survey Message.</h2>";
	shn_form_fopen("contact_submit", null,array('req_message'=>true));
		shn_form_hidden(array("target"=>"send_survey"));
		shn_form_fsopen("Survey Information");
                        _shn_msg_contact_dropdown('to');
			shn_form_text("Survey Name : ","name",null,array("req"=>true));
			shn_form_text("Key : ","key","size='6'",array("req"=>true));
                        shn_form_textarea('To','to');
                        _shn_msg_message_ui();
		shn_form_fsclose();
	shn_form_submit("Next", $submit_opts = null);	
	shn_form_fclose();	
}

/*
@author		Pradeeper <pradeeper@respere.com>
@function	capture the user submistion for shn_msg_send_survey_form
*/
function _shn_msg_send_survey_submistion()
{
	$survey_name=$_POST['name'];
	$key=$_POST['key'];
	$message=$_POST['message'];
	
	// check the submistion
	if(($survey_name!="") && ($key!="")){
		
		// db connection
		global $global;
		global $conf;
		$db = $global['db'];
	        
	    $survey_msg_id=shn_create_uuid('msg');
	    
	    // store person information
		$q="insert into msg_survey (msg_id, survey_name, survey_key, message) values ('$survey_msg_id','$survey_name','$key','$message');";
		$res = $db->Execute($q);
		if($res){
			include "handler_survey.inc";
		} else {
			add_error('Survey can not be submitted!');
		}
		
	} else {
		add_error('Please fill the required fields and resubmit again!');
		shn_msg_send_survey_form();
	}
}
?>
