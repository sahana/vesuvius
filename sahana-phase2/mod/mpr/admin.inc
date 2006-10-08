<?php
/* $Id: admin.inc,v 1.6 2006-10-08 18:36:39 isurunishan Exp $ */

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
    shn_adm_menuitem("adm_opt_age_group",_("Manage Age Groups"));
    shn_adm_menuitem("adm_opt_race",_("Manage Race"));
    shn_adm_menuitem("adm_opt_religion",_("Manage Religion"));
    shn_adm_menuitem("adm_opt_blood_type",_("Manage Blood Group"));
    shn_adm_menuitem("adm_opt_eye_color",_("Manage Eye Colors"));
    shn_adm_menuitem("adm_opt_hair_color",_("Manage Hair Colors"));
    shn_adm_menuitem("adm_opt_skin_color",_("Manage Skin Colors"));

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
    <p><?=_("Please use the Security Config menu to Install the Access Control");?> </p>
<?php
shn_mpr_adm_gen();
}
/* }}} */

//temporary fix
function _shn_mpr_adm_gen_validate()
{
	return true;
}
/* {{{ shn_mpr_adm_gen */
function shn_mpr_adm_gen()
{
    shn_mpr_adminmenu();
    if($_POST['seq']=='general'){
        if(_shn_mpr_adm_gen_validate()){
            _shn_mpr_adm_gen(false,true);
        }else{
            _shn_mpr_adm_gen(true);
        }
    }else{
        _shn_mpr_adm_gen();
    }
?><br /><h2><?=_("General Configuration"); ?></h2>
<?php
}
/* }}} */

/* {{{ shn_mpr_adm_images */
function shn_mpr_adm_images()
{
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Images"); ?></h2>
<?php
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_age_group()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Age Groups"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_age_group');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_race()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Race"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_race');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_religion()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Religion"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_religion');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_blood_type()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Blood Groups"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_blood_type');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_eye_color()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Eye Color"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_eye_color');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_hair_color()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Hair Color"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_hair_color');
}   
/* }}} */

/* {{{ shn_mpr_adm_age */
function shn_mpr_adm_opt_skin_color()
{       
    shn_mpr_adminmenu();
?><br /><h2><?=_("Manage Skin Color"); ?></h2>
<?php
    _shn_mpr_adm_field_options_controller('opt_skin_color');
}   
/* }}} */


/* {{{ */
function _shn_mpr_adm_gen($errors=false,$updated=false)
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
    
    shn_form_hidden(array('seq'=>'general'));
    
    shn_form_fsopen(_('Name'));
    if(!isset($_POST['name']))
        $val = array('value'=>$conf['mod_mpr_name']);
    else
        $val = null;
    shn_form_text(_('Module Name'),'name','size="15"',$val);
    shn_form_fsclose();

    shn_form_fsopen(_('Search'));
    if(!isset($_POST['search_limit']))
        $val = array('value'=>$conf['mod_mpr_search_limit']);
    else
        $val = null;
    shn_form_text(_('Search results display limit'),'search_limit','size="15"',$val);
    shn_form_fsclose();

#    shn_form_fsopen(_('Upload Pictures'));
#    shn_form_select(array('database'=>_('To Database'),
#                        'file'=>_('To File')), _('Image save handler'), 'upload_pic_handler');
#    shn_form_fsclose();

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
//temporary fix


function _shn_mpr_adm_field_options_controller($type){
    switch ($_POST['seq']) {
        case 'update':
            if(_shn_mpr_adm_field_options_validate($type)){
                _shn_mpr_adm_field_options_form($type,false);
            }else{
                _shn_mpr_adm_field_options_form($type,true);
            }
        break;

        default:
            _shn_mpr_adm_field_options_form($type);
        break;
    }
}

function _shn_mpr_adm_field_options_form($type)
{
    global $global;
    global $conf;

    if($errors)
        display_errors();

    $sql = "SELECT field_name, option_code, option_description  FROM field_options WHERE field_name = '$type'";
    $arr = $global['db']->GetAll($sql);
    if(! empty($arr)){
        shn_form_fopen('adm_'.$type,null);
        shn_form_fsopen(_('Update'));
        shn_form_hidden(array('seq'=>'update'));
?>
<table>
<thead>
    <td><strong><?=_('Code');?></strong></td>
    <td width="100%"><strong><?=_('Description');?></strong></td>
    <td width="100%"><strong><?=_('Delete');?></strong></td>
</thead>
<?php
        foreach($arr as $row){
?>
<tr>
    <td><input type="text" name="code[<?=$row['option_code'];?>]" 
            value="<?=$row['option_code'];?>" />
    </td>
    <td><input type="text" name="description[<?=$row['option_description'];?>]" 
            value="<?=$row['option_description'];?>" />
    </td>
    <td><input type="checkbox" name="delete[<?=$row['option_code'];?>]" />
    </td>
</tr>
<?php
        }
?>
</table>
<?php
        shn_form_submit(_('Update'));
        shn_form_fsclose();
    }
    shn_form_fsopen(_('Add New '));
    shn_form_text(_("Code"),'new_code');
    shn_form_text(_("Description"),'new_desc');
    shn_form_submit(_('Add New'));
    shn_form_fclose(); 
}

function _shn_mpr_adm_field_options_validate($type,$error=false)
{

}
?>
