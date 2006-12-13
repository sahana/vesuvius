<?php                             
/* $Id: home.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Registry Module -- includes files from the inc directory.
 *
 *  <p>This file is part of the Volunteer Registry module. It
 *  includes all of the files from the inc directory that are 
 *  used by the VR module.</p>
 *
 * @package    Trinity_College_vm_demo
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Jonathan Damon 
 *
 */
 
global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
require_once $global['approot']."/mod/vm/utility_functions.inc";
//error_reporting(E_ALL);
//include_once "lib_vm.inc";
global $global;
$db=$global["db"]; 

	$p_uuid = get_current_user_id();
	$q="select name, mgr_id from vm_projects, vm_proj_vol where p_uuid ='{$p_uuid}' and vm_proj_vol.proj_id = vm_projects.proj_id";
	$res=$db->Execute($q);
	$name=$res->fields[0];
	$mgr_id=$res->fields[1];
	$q="select count(message_id) from vm_courier where to_id = '{$p_uuid}'";
	$res=$db->Execute($q);
	$message_num=$res->fields[0];
	
	if($_POST['message']!=NULL){
		$q="select max(message_id) from vm_messages";
		$res=$db->Execute($q);
		$message_id=$res->fields[0] + 1;
		$q="insert into vm_messages(message_id,message) values('{$message_id}','{$_POST['message']}')";
		$res=$db->Execute($q);
		$q="insert into vm_courier(message_id,to_id,from_id) values('{$message_id}','{$mgr_id}','{$p_uuid}')";
		$res=$db->Execute($q);
		echo "<div id=\"error\"><p>Your message has been successfully sent.<p></div>";
	}


?>

<!-- 
 This section of HTML code displays a summary for the Volunteer Management Module. Its style is defined
 in the CSS document: /usr/share/sahana/www/theme/default/sahana.css. 
-->

<div id="home">
    <h2><?=_("Volunteer Portal")?></h2>

<table width="99%">
	<colgroup>
	<col width="50%">
	<col width="50%">
    <thead>
        <td><strong><?=_("Projects")?></strong></td>
        <td><strong><?=_("Messages")?></strong></td>
    </thead>
    <tbody>
        <tr>
		<td align=center>
			<div>
                	  <?=_("You are assigned to ")?><strong> <?php if($name){echo $name;}else{echo "no";}?></strong><?=_(" Project.")?>
	                </a>	
			</div>
		</td>
		<td align=center>
			<div>
                	  <?=_("You have ")?><strong> <?php echo $message_num ?></strong><?=_(" message(s).")?>
	                </a>	
			</div>
		</td>
        </tr>
    </tbody>
    </table>
</div>
<br />

<?php

if($message_num > 0){
include_once $global['approot']."/mod/vm/view_messages.inc";
_shn_vm_view_messages();
}

if($name){
	$form_opts = array('req_message'=>false);
	shn_form_fopen(shn_vm_default, vm, $form_opts);
	shn_form_fsopen(_("Send a Message to your Project Leader"));
	shn_form_textarea(_("Message : "),"message");
	shn_form_fsclose();
	shn_form_submit(_("Submit"));
	shn_form_fclose();
}

/*
	$q = "select message_id from vm_courier where to_id='{$user_id}'";
	$result=$db->Execute($q);
	while(!$result==NULL && !$result->EOF){
		$q = "select message from vm_messages where message_id='{$result->fields[0]}'";
		$res_message=$db->Execute($q);
		$message = $res_message->fields[0];
		$q = "select from_id, time, from vm_courier where message_id='{$result->fields[0]}'";
		$res_message=$db->Execute($q);
		$from_id = $res_message->fields[0];
		$time = $res_message->fields[1];
		$q = "select full_name from person_uuid where p_uuid='{$from_id}'";
		$res_message=$db->Execute($q);
		$name = $res_message->fields[0];
*/
 	//$result->MoveNext();
	// } // while loop


