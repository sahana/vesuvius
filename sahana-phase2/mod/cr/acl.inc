<?php
/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the wcrld-wide-web at the following URI:
* http://www.gnu.crg/copyleft/lesser.html
*
* @authcr     Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_cr_adm_acl_install()
{
    global $global;
    $db = $global["db"];
    $q = "SELECT value FROM config WHERE module_id='cr' AND confkey='acl_base'";
    $res_acl = $db->Execute($q);

    if(!$res_acl->EOF && $res_acl->fields[0] == 'installed')
        $msg = _("ACL Base for Camps Registry is already installed");
    else
    {
        include_once $global['approot']. 'inc/lib_security/acl_api.inc';
        include_once $global['approot']. 'inc/lib_security/acl.inc';
        include_once $global['approot']. 'inc/lib_security/authenticate.inc';

        $acl = new SahanaACL(NULL);

        /***
        * CR specifc ACL entries
        */

        $res = shn_acl_add_module("cr",_("Camp Registry"));

        ## Action groups ##
        ## Add an action group named "deny_admin" under the module "cr"
        $res = shn_acl_add_action_group("cr","deny_admin",_("Deny admin group"));

        //$res = shn_acl_add_action("cr","deny_admin","shn_cr_acl_setup",_("Display ACL configuration info"));
        $res = shn_acl_add_action("cr","deny_admin","shn_cr_adm_default",_("Display Admin page"));

        ## Deny permission for 'deny_admin' action group with in 'cr' to 'guest' role
        $res = shn_acl_add_perms_action_group_role('guest','cr','deny_admin');
        $res = shn_acl_add_perms_action_group_role('user','cr','deny_admin');

        ## Add an action group named "deny_user" under the module "cr"
        $res = shn_acl_add_action_group("cr","deny_user",_("Deny user group"));

        $res = shn_acl_add_action("cr","deny_user","shn_cr_acmp", _("Add Camp"));
        $res = shn_acl_add_action("cr","deny_user","shn_cr_ecmp",_("Edit Camp"));

        $res = shn_acl_add_perms_action_group_role('guest','cr','deny_user');

        if($res_acl->EOF)
            $q = "INSERT INTO config VALUES('cr','acl_base','installed')";
        else
            $q = "UPDATE config SET value='installed' WHERE module_id='cr' AND confkey='acl_base'";

        $res = $db->Execute($q);
        $msg = _("ACL Base for Request Management System was succesfully installed");
    }
?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}
?>
