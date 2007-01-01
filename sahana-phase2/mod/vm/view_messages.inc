<?php
/* $Id: [sahana_home]/mod/vm/view_messages.inc,v 1.0 2006/07/25  */
/**
 *
 *  Volunteer Registry Module -- displays messages to a volunteer.
 *
 *  <p>This file is part of the Volunteer Registry module.  It
 *  generates the messages window with all of the messages for 
 *  a volunteer.</p>
 *
 * @package    Trinity_College_vm_demo
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 *
 */
 
 /**
 *  Generates the Message Boxes page.
 *
 *  This function queries the database for messages to a specific user.
 *
 *  @access public
 *  @return void
 */
function _shn_vm_view_messages(){
global $global;
global $conf;
include_once $global['approot']."/mod/vm/utility_functions.inc";
$db=$global['db'];
$user_id=$_SESSION["user_id"];

?>
    <div id="home">
       <h2><?=_("Messages")?></h2>
       <table width="100%">
        <thead>
         <td><?=_("Sent")?></td>
         <td><?=_("From")?></td>
         <td><?=_("Message")?></td>
        </thead>
        <tbody>
<?php

	$q = "select message_id from vm_courier where to_id='{$user_id}'";
	$result=$db->Execute($q);
	while(!$result==NULL && !$result->EOF){
		$q = "select message from vm_messages where message_id='{$result->fields[0]}'";
		$res_message=$db->Execute($q);
		$message = $res_message->fields[0];
		$q = "select from_id, time from vm_courier where message_id='{$result->fields[0]}'";
		$res_message=$db->Execute($q);
		$from_id = $res_message->fields[0];
		$time = $res_message->fields[1];
		$q = "select full_name from person_uuid where p_uuid='{$from_id}'";
		$res_message=$db->Execute($q);
		$name = $res_message->fields[0];
?>
         <tr>
          <td align=center><?php echo $time?></td>
          <td align=center><?php echo $name?></td>
          <td align=center><?php echo $message?></td>
         </tr>
<?php
 	$result->MoveNext();
	} // while loop
?>
        </tbody>
       </table>
     </div>
<?php
} // _shn_vm_view_messages()

