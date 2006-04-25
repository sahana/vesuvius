<?php
/* $Id: admin.inc,v 1.2 2006-04-25 06:03:59 janakawicks Exp $ */

/**
 * Administration of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once($global['approot'].'/inc/lib_form.inc');

/* {{{ Sub Menus */
/**
 * shn_mpr_adminmenu 
 * 
 * @access public
 * @return void
 */
function shn_mpr_adminmenu(){
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_adm_menuopen(_("Missing Person Registry"));

    shn_adm_menuitem("adm_gen",_("General Configuration"));
    shn_adm_menuitem("adm_images",_("Manage Images"));

    shn_adm_menuclose();

}
/* }}} */

/* {{{ Default */
/**
 * shn_mpr_adm_default 
 * 
 * @access public
 * @return void
 */
function shn_mpr_adm_default()
{
?>
    <p><b><?=_("Welcome to the Missing Person Registry admin page");?> </b></p>
    <p><?=_("TODO: Something should go here");?> </p>

    


<?php
}
/* }}} */

function shn_mpr_adm_gen()
{
?><br /><h2><?=_("General Configuration"); ?></h2>
<?php
    _shn_mpr_adm_gen_form();

}
/* {{{ General Configuration Form */
/**
 * shn_mpr_adm_gen
 * 
 * @access public
 * @return void
 */
function _shn_mpr_adm_gen_form($errors=false,$updated=false)
{
    global $conf;

    if($errors)
        display_errors();
   
    if($updated){
?>
    <p align="center">Updated. </p> 
<?php
    }

    shn_form_fopen("adm_gen",null);
    
    shn_form_hidden(array('seq'=>'entry'));
    
    shn_form_fsopen(_('Search'));
    if(!isset($_POST['search_limit']))
        $val = array('value'=>$conf['mod_mpr_search_limit']);
    else
        $val = null;
    shn_form_text(_('Search results display limit'),'search_limit','size="15"',$val);
    shn_form_fsclose();

    shn_form_fsopen(_('Upload Pictures'));
    shn_form_select(array('database'=>_('To Database'),
                        'file'=>_('To File')), _('Image save handler'), 'upload_pic_handler');
    shn_form_fsclose();

    shn_form_submit(_('Update'));

    shn_form_fclose();
}
/* }}} */

/* {{{ ACL Install */
/**
 * shn_mpr_adm_acl_install 
 * 
 * @access public
 * @return void
 */
function shn_mpr_adm_acl_install(){
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='mpr' and confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        $msg=_("ACL Base for Missing Person Registry is already installed, This is a reinstall");
    }
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot'].'inc/lib_security/authenticate.inc';
    $acl=new SahanaACL(NULL);

 /* start of or specifc ACL entries
 */
     
    $res=shn_acl_add_module("mpr",_("Missing Person Registry"));
    
    $res = shn_acl_add_action_group("mpr","deny_admin",_("Deny admin group"));

    $res = shn_acl_add_action("mpr","deny_admin","shn_mpr_adm_default",_("Display Admin page"));


    ## Deny permission for 'deny_admin' action group with in 'or' to 'guest' role
    $res = shn_acl_add_perms_action_group_role('guest','mpr','deny_admin');
    $res = shn_acl_add_perms_action_group_role('user','mpr','deny_admin');

    $res = shn_acl_add_action_group("mpr","deny_user","Deny user group");

    $res = shn_acl_add_action("mpr","deny_user","shn_mpr_addmp", _("Add Person"));
    $res = shn_acl_add_action("mpr","deny_user","shn_mpr_editmp",_("Edit Person"));
    $res = shn_acl_add_action("mpr","deny_user","shn_mpr_add_tracker",_("Add Tracker"));

    $res = shn_acl_add_perms_action_group_role('guest','mpr','deny_user');

    if($res_acl->EOF)
	 $q="insert into config values('mpr','acl_base','installed')";
    else
	 $q="update config set value='installed' where module_id='mpr' and confkey='acl_base'";
    $res=$db->Execute($q);
    $msg=_("ACL Base for Missing Person Registry was succesfully installed");

?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}
/* }}} */
?>
