<?php
/**
 * This library generates all the forms required to add,modify and remove
 * user ACL settings.
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @author     Greg Miernicki <g@iernicki.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']. 'inc/lib_security/lib_acl.inc';
include_once $global['approot']. 'inc/lib_security/lib_auth.inc';


/**
 * Generates a form to enable/disable ACL
 * @access public
 * @return void
 */

function shn_acl_form_enable_acl() {
	global $global;
	$db=$global['db'];
	echo "
		<h3>Enable / Disable ACL</h3>
		<br>
		<h2 style=\"color: red; font-weight: bold;\">WARNING! ITS A VERY BAD IDEA TO DISABLE ACL! ARE YOU SURE YOU KNOW WHAT YOU ARE DOING???</h2>
		<br>
	";
	shn_form_fopen("acl_enable_acl_cr", "admin", null);
	$acl = shn_acl_is_enabled();
	if($acl == true) {
		shn_form_hidden(array("action"=>'disable'));
		shn_form_submit(_t("Disable ACL"), "class=\"styleTehButton\"");
	} else {
		shn_form_hidden(array("action"=>'enable'));
		shn_form_submit(_t("Enable ACL"), "class=\"styleTehButton\"");
	}
	shn_form_fclose();
}



/**
 * Generates a form to enable/disable self signup
 * @access public
 * @return void
 */

function shn_acl_form_enable_signup() {
	global $global;
	$db=$global['db'];
	echo "
		<h3>Enable / Disable Account Signup</h3>
		<br>
		<h2 style=\"color: red; font-weight: bold;\">WARNING! Disabling this will prevent new users from signing up!</h2>
		<br>
	";
	shn_form_fopen("acl_enable_signup_cr","admin", null);
	$acl=shn_acl_is_signup_enabled();
	if($acl==true){
		shn_form_hidden(array("action"=>'disable'));
		shn_form_submit(_t("Disable Self Signup"), "class=\"styleTehButton\"");
	}else{
		shn_form_hidden(array("action"=>'enable'));
		shn_form_submit(_t("Enable Self Signup"), "class=\"styleTehButton\"");
	}
	shn_form_fclose();
}



/**
 * Generates a form to enable/disable password locking
 * @access public
 * @return void
 */

function shn_acl_form_enable_locking() {
	global $global;
	$db=$global['db'];
		echo "
		<h3>Enable / Disable Password Locking</h3>
		<br>
		<h2 style=\"color: red; font-weight: bold;\">If enabled, a user account will be locked out with 3 invalid password attempts.</h2>
		<br>
	";
	shn_form_fopen("acl_enable_locking_cr","admin", null);
	$acl=shn_acl_is_locking_enabled();
	if($acl==true){
		shn_form_hidden(array("action"=>'disable'));
		shn_form_submit(_t("Disable Password Locking"), "class=\"styleTehButton\"");
	}else{
		shn_form_hidden(array("action"=>'enable'));
		shn_form_submit(_t("Enable Password Locking"), "class=\"styleTehButton\"");
	}
	shn_form_fclose();
}



/**
 * Generates a form to enable/disable modules
 * @access public
 * @return void
 */

function shn_acl_form_enable_mods() {
	global $global;
	$db=$global['db'];
	$perms = "";
	?><h3><?php echo _t("Enable/Disable Modules") ?></h3>
	<div id="home"><strong>
	<?php echo _t("Rows are Modules, Columns are Roles, Intersection shows whether the module is enabled for that role or not") ?></strong></div>
	<div id="formcontainer"><?php
	shn_form_fopen("acl_enable_mods_cr","admin",array('req_message'=>false));
	?><div id="result"><table>
	<thead>
		<td><strong><?php echo _t("Role"); ?></strong></td>
		<?php

		$roles=_shn_acl_get_roles();
		foreach ($roles as $role=>$role_name){
			echo "<td>".$role_name."</td>";
		}
		?>
	</thead>
	<tbody>
	<?php

	$mods=shn_get_all_modules();

	foreach($mods as $mod=>$mod_arr){

		?>
		<tr>
			<td><?php echo $mod_arr[1];?></td>
			<?php

			foreach ($roles as $role=>$role_name){

				$perms = $perms.$mod_arr[0].":".$role.";";
				$name=trim($mod_arr[0].$role);
				$allow=false;
				if ( _shn_acl_is_module_role( $mod_arr[0],$role)==true) {
					$allow=true;
				}else{
					$allow=false;
				}
				?>
			<td><input type="checkbox" name="<?php echo $name?>"
			<?php if (($role==ADMIN)&&($mod_arr[0]=="admin")) echo "disabled=true";?>
			<?php if ($allow==true) echo "checked=true";?> align="right" /></td>
			<?php
			}
	?>
			</tr>
			<?php

	}
	?>
		</tbody>
	</table>
	</div>
	<br />

	<center><?php
	shn_form_hidden(array("perms"=>$perms));

	shn_form_submit(_t("Save"), "class=\"styleTehButton\"");
	?></center>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



/**
 * Generates a form to edit roles of a user
 * @access public
 * @return void
 */

function shn_acl_form_user_edit_roles() {
	global $global;
	$db = $global['db'];

	echo "
		<br>
		<div id=\"home\">Designate which group each use is apart of by clicking assign to change it to the desired group. The box colored <span style=\"color: orange; font-weight: bold;\">orange</span> denotes which group the user is currently apart of.</div><br>
		<div id=\"formcontainer\">
	";

	shn_form_fopen("acl_user_edit_roles_cr", "admin", array('req_message' => false));

	echo "
		<div id=\"result\">
		<table>
		<thead>
		<td><strong><center>UserID</center></strong></td>
		<td><strong>Username</strong></td>
		<td><strong>Real Name</strong></td>
	";

	$roles = _shn_acl_get_roles();
	foreach($roles as $role=>$role_name){
		echo "<td>".$role_name."</td>";
	}


	echo "
		</thead>
		<tbody>
	";

	// switched this to list2 because it wasn't handling uuid's with /'s in them correctly,
	// to we use the user_id and then find the p_uuid of the user when adding the role to the user
	$users = shn_auth_user_list2();

	//echo "<pre>".print_r($users, true)."</pre>";
	//echo "---------------------------------------<br>";
	//echo "<pre>".print_r($roles, true)."</pre>";

	foreach($users as $user) {

		echo "<td>".$user['user_id']."</td><td>".$user['user_name']."</td><td>".$user['full_name']."</td>";



		foreach($roles as $role => $role_name) {
			if($user['group_id'] == $role) {
				echo "<td style=\"background-color: orange;\"><center>".$role_name."</center></td>";
			} else if($user['user_id'] == 1) {
				echo "<td>&nbsp;</td>";
			} else {
				echo "<td><center><a href=\"index.php?mod=admin&act=changeClass&tabid=2&p_uuid=".base64_encode($user['p_uuid'])."&group_id=".$role."\">assign</a></center></td>";
			}
		}
		echo "</tr>";
	}
	echo "
		</tbody>
		</table>
		</div>
	";
	shn_form_fclose();
	echo "</div>";
}



function shn_acl_form_role_select() {
	global $global;
	$db=$global['db'];
	?>
	<div id="home"><?php echo _t("Select the Role you want to edit permissions of") ?></div>

	<div id="formcontainer"><?php
	shn_form_fopen("acl_role_edit_perms","admin");
	$extra_opts['req']=true;
	$roles=_shn_acl_get_roles();
	shn_form_fsopen(_t("Select Role"));
	shn_form_select($roles,_t("Roles"),'roles',null,$extra_opts);
	shn_form_fsclose();
	shn_form_submit(_t("Continue"), "class=\"styleTehButton\"");
	?>
	</center>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



function shn_acl_form_role_perms_grid($role) {
	global $global;
	$db=$global['db'];
	?>
	<div id="home"><strong><?php echo _t("Rows are Data Classificatons, Columns are
	Create,Read,Update,Delete. Intersection shows whether the Role has
	Create,Read,Update,Delete permissions to the Data Classificatons"); ?></strong></div>

	<div id="formcontainer"><?php
	shn_form_fopen("acl_role_edit_perms_cr","admin",array('req_message'=>false));

	echo "<br/><p>"._t(sprintf("The selected role is <em>%s</em>",shn_acl_get_group_name($role)))."</p><br/>";
	?>
	<div id="result">
	<table>
		<thead>
			<td><strong><?php echo _("Data Classificatons") ?></strong></td>
			<?php
			$cruds=array(
				"create"=>_t("Create"),
				"read"=>_t("Read"),
				"update"=>_t("Update"),
				"delete"=>_t("Delete")
				);

				foreach($cruds as $crud=>$crud_name){
					echo "<td>".$crud_name."</td>";
				}
				?>

		</thead>
		<tbody>
		<?php

		$levels=shn_acl_data_classifications_list();


		foreach ($levels as $level=>$level_name){
			//this will be used in a hidden field to identify all the checkboxes

			$levels=$level.":".$levels;
			$perms=$perms.";".$level;
			?>
			<tr>
				<td><?php echo $level_name?></td>
				<?php
				$crud_value=_shn_acl_get_role_data_classification_crud($role,$level);
				foreach($cruds as $crud=>$crud_name){
					$perms=$perms.":".$crud;
					$name=trim($level.$crud);

					if ( _shn_acl_is_crud_group($crud,$crud_value)) {

						$allow=true;
					}else{
						$allow=false;
					}

					?>
				<td><input type="checkbox" name="<?php echo $name?>"
				<?php if ($allow==true) echo "checked=true";?> algin="right" /></td>
				<?php


	}

	?>
			</tr>
			<?php
			//$perms=$perms.";";
	}
	?>
		</tbody>
	</table>
	</div>
	<br />

	<center><?php
	shn_form_hidden(array("perms"=>$perms));
	shn_form_hidden(array("role"=>$role));
	shn_form_submit(_t("Save"), "class=\"styleTehButton\"");
	?></center>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



function shn_acl_form_classifications_to_data() {
	global $global;
	$db=$global['db'];
	?>
	<div id="home"><?php echo _t("Edit the Data Classification for each table") ?></div>

	<div id="formcontainer"><?php
	shn_form_fopen("acl_data_classifications_tables_cr","admin",array('req_message'=>false));
	//$extra_opts['req']=true;
	$levels=shn_acl_data_classifications_list();
	$tables=shn_acl_sys_data_tables();
	foreach ($tables as $table=>$level){
		shn_form_fsopen();

		$extra_opts["value"]=$level;
		$extra_opts['br'] = false;
		shn_form_select($levels,$table,$table,null,$extra_opts);
		shn_form_submit(_t("Save"), "class=\"styleTehButton\"");

		shn_form_fsclose();
	}


	?>
	</center>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



function shn_acl_form_change_user_status() {
	global $global;
	$db = $global['db'];
	$perms = "";
	?>
	<br>
	<div id="home"><?php echo _t("Rows are Users ,Columns are the possible status values"); ?>
	<br><br>
	<ul>
	<li><?php echo _t("<strong>Active</strong> - The user can login and perform operations."); ?></li>
	<li><?php echo _t("<strong>Locked</strong> - The user is withheld from performing operations on the system temporarily."); ?></li>
	<li><?php echo _t("<strong>Banned</strong> - The user is not allowed to perform any operation on the system permanently."); ?></li>
	</ul>
	</div>

	<div id="formcontainer"><?php
	shn_form_fopen("acl_change_user_status_cr","admin",array('req_message'=>false));
	?>
	<div id="result">
	<table>
	<thead>
		<td><strong><?php echo _t("User"); ?></strong></td>
		<td><?php echo _t("Active") ?></td>
		<td><?php echo _t("Locked") ?></td>
		<td><?php echo _t("Banned") ?></td>
	</thead>
	<tbody>
	<?php

	$users=shn_auth_user_list_and_status();
	$locked = shn_auth_locked_user_list();
	// check if locking is disabled and the users are locked.
	if(count($locked)>0 && shn_acl_is_locking_enabled()==false){
		add_warning(_t("Password locking is disabled system wide. Locks will not take any effect until it is enabled.").
    	"<br/><a href='index.php?mod=admin&act=acl_enable_locking'>"._t("Click here to enable locking")."</a>");
	}

	foreach ($users as $user=>$uarray){
		//this will be used in a hidden field to identify all the checkboxes
		$user=$user;

		$uname=$uarray[0];
		?>
		<tr>
			<td><?php echo $uname;?></td>
			<td><?php
			$options=array("active"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("locked"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("banned"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
		</tr>
		<?php
	}
	?>
		</tbody>
	</table>
	</div>
	<br />

	<center><?php
	shn_form_hidden(array("perms"=>$perms));
	shn_form_hidden(array("users"=>$users));
	shn_form_submit(_t("Save"), "class=\"styleTehButton\"");
	?></center><br><br>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



function shn_acl_form_unlock_user() {
	global $global;
	$db=$global['db'];
	?>
	<div id="home"><strong><?php echo _t("Rows are Locked Users, Columns are the possible status
	values") ?></strong></div>

	<div id="formcontainer"><?php
	shn_form_fopen("acl_unlock_user_cr","admin");
	?>
	<div id="result">
	<table>
	<thead>
		<td><strong><?php echo _t("Locked User")?></strong></td>
		<td><?php echo _t("Active")?></td>
		<td><?php echo _t("Locked")?></td>
		<td><?php echo _t("Banned")?></td>
	</thead>
	<tbody>
	<?php

	$users=shn_auth_locked_user_list();

	// check if locking is disabled and the users are locked.
	if(count($users)>0 && shn_acl_is_locking_enabled()==false){
		add_warning(_t("Password locking is disabled system wide. Locks will not take any effect until it is enabled.").
    	"<br/><a href='index.php?mod=admin&act=acl_enable_locking'>"._t("Click here to enable locking")."</a>");
	}

	foreach ($users as $user=>$uarray){
		//this will be used in a hidden field to identify all the checkboxes
		$user=$user;

		$uname=$uarray[0];
		?>
		<tr>
			<td><?php echo $uname;?></td>
			<td><?php
			$options=array("active"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("locked"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
			<td><?php
			$options=array("banned"=>"");
			shn_form_radio($options,"", $user,$select_opts = "", array('value'=>$uarray[1]));?>
			</td>
		</tr>
		<?php
	}
	?>
		</tbody>
	</table>
	</div>
	<br />

	<center><?php
	shn_form_hidden(array("perms"=>$perms));
	shn_form_hidden(array("users"=>$users));
	shn_form_submit(_t("Save"), "class=\"styleTehButton\"");
	?></center>
	<?php
	//close the form
	shn_form_fclose();
	?></div>
	<?php
}



function shn_acl_form_event_log() {
	global $global;
	$db=$global['db'];
	?>

	<div id="result">
	<table>
	<thead>
		<td><strong><?php echo _t("Date") ?></strong></td>
		<td><strong><?php echo _t("Time") ?></strong></td>
		<td><strong><?php echo _t("User Name") ?></strong></td>
		<td><strong><?php echo _t("Full Name") ?></strong></td>
		<td><strong><?php echo _t("Event Type") ?></strong></td>
		<td><strong><?php echo _t("Event") ?></strong></td>
	</thead>
	<tbody>
	<?php

	$sql="SELECT * FROM password_event_log ORDER BY changed_timestamp DESC";
	$res=$db->Execute($sql);
	while(($res!=null) &&(!$res->EOF)){
		$timestamp=$res->fields["changed_timestamp"];
		$full_name=shn_get_user_details($res->fields["p_uuid"]);
		$date=date("m.d.y",$timestamp);
		$time=date("H:m:s",$timestamp);
		$type=($res->fields["event_type"]==null)?1:$res->fields["event_type"];
		$sql="SELECT option_description FROM field_options WHERE option_code='{$type}' AND field_name='opt_acl_event_type'";
		$res2=$db->Execute($sql);
		$type=$res2->fields["option_description"];
		?>
		<tr>
			<td><?php echo $date;?></td>
			<td><?php echo $time;?></td>
			<td><?php echo $res->fields["user_name"];?></td>
			<td><?php echo $full_name;?></td>
			<td style="color: red; font-weight: bold;"><?php echo $type;?></td>
			<td><?php echo $res->fields["comment"];?></td>
		</tr>
		<?php
		$res->MoveNext();
	}
	?>
		</tbody>
	</table>
	</div>
	<br />
	<?php
}



