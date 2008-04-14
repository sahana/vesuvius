<?php

/**
 * Administration of the Situation Awareness module 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Fran Boon <fboon@oxfam.org.uk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');


/* {{{ Sub Menus */
/**
 * shn_sm_adminmenu 
 * 
 * @access public
 * @return void
 */
function shn_sm_adminmenu() {
	global $global;
	$module = $global['module'];

	// Create the module menu
	shn_adm_menuopen(_t("Situation Awareness"));
	shn_adm_menuitem("adm_gen", _t("General Configuration"));
	shn_adm_menuclose();

}
/* }}} */

/* {{{ Default */
/**
 * shn_sm_adm_default 
 * 
 * @access public
 * @return void
 */
function shn_sm_adm_default() 
{
    shn_sm_adminmenu();
    ?> <br></br> 
    <p><b><?=_("Welcome to the Situation Awareness admin page");?> </b></p>
    <p><?=_("Please use the navigation menu above to configure each field.");?> </p>
<?php

}
/* }}} */

/* {{{ ACL Install */
/**
 * shn_sm_adm_acl_install 
 * 
 * @access public
 * @return void
 */

function shn_sm_adm_acl_install() {
	global $global;
	$db = $global["db"];
	$q = "select value from config where module_id='sm' and confkey='acl_base'";
	$res_acl = $db->Execute($q);
	if (!$res_acl->EOF && $res_acl->fields[0] == 'installed') {
		$msg = _t("ACL Base for Situation Awareness is already installed, This is a reinstall");
	}
	include_once $global['approot'] . 'inc/lib_security/acl_api.inc';
	include_once $global['approot'] . 'inc/lib_security/acl.inc';
	include_once $global['approot'] . 'inc/lib_security/authenticate.inc';
	$acl = new SahanaACL(NULL);

	/* start of sm specific ACL entries
	*/

	$res = shn_acl_add_module("sm", _t("Situation Awareness"));

	$res=shn_acl_add_action_group("sm","create","create group");
	$res=shn_acl_add_action_group("sm","view","view group");

	$res=shn_acl_add_action("sm","view","shn_sm_swik","View Situation Map");
	$res=shn_acl_add_action("sm","create","shn_sm_awik","Add New Situation");

	$res=shn_acl_add_perms_action_group_role('guest','sm','view');
	$res=shn_acl_add_perms_action_group_role('user','sm','create');

	// Deny access to Admin page unless an Admin
	//$res = shn_acl_add_action_group("sm", "deny_admin", _t("Deny admin group"));
	//$res = shn_acl_add_action("sm", "deny_admin", "shn_sm_adm_default", _t("Display Admin page"));

	if ($res_acl->EOF)
		$q = "insert into config values('sm','acl_base','installed')";
	else
		$q = "update config set value='installed' where module_id='sm' and confkey='acl_base'";
	$res = $db->Execute($q);
	$msg = _t("ACL Base for Situation Awareness was successfully installed");
?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php

}
/* }}} */

?>
