<?php
/**
 * REG Module
 *
 * PHP version >=5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 * @package    module reg
 * @version    1.0
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */



/**
 * Default Admin function
 *
 * @access public
 * @return void
 */
function shn_reg_default() {
	shn_reg_log();
}



/**
 * Show all device/user registrations.
 *
 * @access public
 * @return void
 */
function shn_reg_log() {
	global $global;
	echo "<div id=\"home\">";
	echo "<h2>Device Manager</h2><br>";
	$query  = "SELECT * FROM reg ORDER BY last_attempt DESC;";
	$result = $global['db']->Execute($query);
	$count = 0;
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Registered Devices</legend>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>UUID</b></td>
		<td class=\"evener\"><b>Name</b></td>
		<td class=\"evener\"><b>Email</b></td>
		<td class=\"evener\"><b>Time</b></td>
	<td class=\"evener\"><b>Activated</b></td>
		<td class=\"evener\"><b>Edit This Registration</b></td>
	</tr>";
	while($row = $result->FetchRow()) {
		$active = $row['is_active'] == 1 ? "YES" : "NO";
		$u = base64_encode($row['p_uuid']);
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
			<td ".$odd.">".$row['p_uuid']."</td><td ".$odd.">".$row['FULL_NAME']."</td><td ".$odd.">".$row['EMAIL_ADDRESS']."</td>
			<td ".$odd.">".$row['last_attempt']."</td><td ".$odd.">".$active."</td><td ".$odd."><a href=\"index.php?mod=reg&act=edit&uuid=".$u."\">Edit</a>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Registrations Yet.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}



/**
 * Edit a registered device/user.
 *
 * @access public
 * @return void
 */
function shn_reg_edit() {
	global $global;
	$uuid = base64_decode($_GET['uuid']);
	echo "<div id=\"home\">";
	echo "<h2>Device Registration ~ Edit a Registration</h2><br>";
	$query  = "SELECT * FROM reg WHERE p_uuid = '".mysql_real_escape_string($uuid)."' LIMIT 1;";
	$result = $global['db']->Execute($query);
	$row = $result->FetchRow();
	$active = $row['is_active'] == 1 ? "YES" : "NO";
	if($active=="YES") {
		$d1 = "DISABLED";
		$d2 = "This registration is already active.";
	} else {
		$d1 = "";
		$d2 = "Press this to activate the user registration. This is equivalent to the user confirming their registration request.";
	}
	echo "
		<script>
			function activate() {
				window.location = 'index.php?mod=reg&act=activate&uuid=".base64_encode($uuid)."';
			}
			function confirmDelete() {
				var answer = confirm('Are you sure you want to delete this registration? This action cannot be undone.');
				if(answer) {
					window.location = 'index.php?mod=reg&act=delete&uuid=".base64_encode($uuid)."';
				}
			}
		</script>
	";
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>Edit</legend>";
	echo "<table id=\"regLog\">
		<tr><td style=\"width: 250px;\"  class=\"odder\"><b>UUID</b></td><td class=\"odder\">".$row['p_uuid']."</td></tr>
		<tr><td style=\"width: 250px;\" class=\"evener\"><b>Email</b></td><td class=\"evener\">".$row['EMAIL_ADDRESS']."</td></tr>
		<tr><td style=\"width: 250px;\"  class=\"odder\"><b>Full Name</b></td><td class=\"odder\">".$row['FULL_NAME']."</td></tr>
		<tr><td style=\"width: 250px;\" class=\"evener\"><b>Registration Time</b></td><td class=\"evener\">".$row['last_attempt']."</td></tr>
		<tr><td style=\"width: 250px;\"  class=\"odder\"><b>Active Status</b></td><td class=\"odder\">".$active."</td></tr>
		<tr>
			<td style=\"width: 250px;\" class=\"evener\">
				<input id=\"activateButton\" type=\"button\" value=\"Activate\" onclick=\"activate();\" ".$d1.">
			</td>
			<td class=\"evener\">".$d2."</td>
		</tr>
		<tr>
			<td style=\"width: 250px;\" class=\"odder\">
				<input id=\"deleteButton\" type=\"button\" value=\"Delete\" onclick=\"confirmDelete();\">
			</td>
			<td class=\"odder\">Press this to delete the device registration.</td>
		</tr>
		<tr>
			<td colspan=2 class=\"evener\"><br><br>
			<b>Note</b>: Deleting a registration will only revoke the web service keys and registration information for the device.<br>
			If already activated, the Sahana 'user' associated with this registration will remain in the system after the deletion.<br>
			This is to ensure that other modular data associated with the Sahana user is not stranded without an associated user.<br>
			ie. Reported missing persons will still list them as the reporter. This user and associated data can be removed via other tools.
			</td>
		</tr>
	</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}



/**
 * Deletes a Registration
 */
function shn_reg_delete() {
	global $global;
	$uuid = base64_decode($_GET['uuid']);
	$q1 = "DELETE FROM reg WHERE p_uuid = '".mysql_real_escape_string($uuid)."';";
	$r1 = $global['db']->Execute($q1);
	$q2 = "DELETE FROM ws_keys WHERE p_uuid = '".mysql_real_escape_string($uuid)."';";
	$r2 = $global['db']->Execute($q2);
	add_confirmation("Registration for uuid: <b>".$uuid."</b> deleted.");
	shn_reg_log();
}



/**
 * Activates a Registration
 */
function shn_reg_activate($uuid) {
	global $global;
	$uuid = base64_decode($_GET['uuid']);

	$query  = "SELECT * FROM reg WHERE p_uuid = '".mysql_real_escape_string($uuid)."';";
	$result = $global['db']->Execute($query);
	$row    = $result->FetchRow();

	addUser($row['EMAIL_ADDRESS'], $row['PASSWORD'], $row['FULL_NAME'], $row['p_uuid']);
	addDevice($row['p_uuid'], $row['API_KEY'], $row['PASSWORD'], $row['SECRET_CODE']);
	changeStatus($row['API_KEY']);

	add_confirmation("Registration for uuid: <b>".$new_uuid."</b> activated.");
	shn_reg_log();
}



/**
 * Add newly confimred user to Sahana.
 */
function addUser($email, $password, $name, $p_uuid) {
	global $global;
	require_once($global['approot']."/inc/lib_security/lib_auth.inc");
	$ret = shn_auth_add_user($name, $email, $password, $role=REGISTERED, $p_uuid);
}



/**
 * Add newly confimred user to Sahana.
 */
function addDevice($uuid, $api, $password, $secret) {
	global $global;
	// $sql="insert into ws_keys(p_uuid,domain,api_key,password,secret) values('{$user}','{$domain}','{$key}','{$pwd}','{$secret}')";
	$query = "insert into ws_keys(
		`p_uuid`,
		`domain`,
		`api_key`,
		`password`,
		`secret`
	) values(
		'".$uuid."',
		'DEVICE',
		'".$api."',
		'".$password."',
		'".$secret."'
	)";
	$result = $global['db']->Execute($query);
}



/**
 * change reg status to active
 */
function changeStatus($api) {
	global $global;
	$query = "UPDATE reg SET is_active = 1 WHERE API_KEY = '".$api."';";
	$result = $global['db']->Execute($query);
}

