<?
/**
 * @name         ACL Form Library
 * @version      11
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']. 'inc/lib_security/lib_acl.inc';
include_once $global['approot']. 'inc/lib_security/lib_auth.inc';


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


