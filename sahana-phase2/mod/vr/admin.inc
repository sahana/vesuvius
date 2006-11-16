<?php
/* $Id: [sahana_home]/mod/vr/admin.inc,v 1.0 2006/07/25  */
/**
*
* Admin controller of the Volunteer Registry (PHP version 4 and 5)
*
* <p>LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html</p>
*
* @package    Trinity_College_VR_Module
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @author     Jonathan Damon <jonathan.damon@trincoll.edu>
* @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
*/

/** Contains library functions for creating forms. */
include_once($global['approot'].'/inc/lib_form.inc');
/** Contains library functions for VM and VR forms. */
include_once($global['approot'].'/mod/vr/lib_vr.inc');
//include_once "admin_forms.inc";

function shn_vr_adm_default()
{
?>
    <p><b> Welcome to the VR admin page </b></p>
    <p> Using the form below you can edit the Skill Types</p>
<?php
	shn_vr_adm_type_form();
}


function shn_vr_adm_type_form()
{
?>
<h2><?=_("Skill Types")?></h2>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("adm_type_cr");
    _shn_vm_admin_javascript("opt_skill_type");
    shn_form_fsopen("Add New Type Information");
    shn_form_text(_("Skill Description : "),'type','size="50"',null); 
    shn_form_text(_("Abbrevation [3 letter unique abbr. to store in the database] : "),'type_abbr','size="50"',null); 
    shn_form_hidden(array("added"=>'0'));
    shn_form_hidden(array("removed"=>'0'));
    shn_form_button(_("Add"),"onClick='add_types()'");
    shn_form_fsclose();
 ?>
</center>
<?php
    shn_form_fsopen("Remove Types");
    _shn_vm_display_skill_types($error,true);
     shn_form_button(_("Remove"),"onClick='remove_types()'");
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
   shn_form_submit(_("Save"))
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
}//shn_vm_adm_type_form()

function shn_vr_adm_type_cr()
{
    global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
    $remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
        $q="insert into field_options(field_name,option_code,option_description) values('opt_skill_type','{$temp[0]}','{$temp[1]}')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        $q="delete from field_options where field_name='opt_skill_type' and option_code='".$temp[0]."'";
        $res=$db->Execute($q);
    }
    shn_vm_adm_type_form();
}

function shn_vr_adm_acl_install()
{
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='vr' and confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        $msg="ACL Base for Volunteer Registry Module is already installed";
    }
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot'].'inc/lib_security/authenticate.inc';
    $acl=new SahanaACL(NULL);

 /** start of or specifc ACL entries
 **/
    // add a module named "or"
    $res=shn_acl_add_module("vr","volunteer registry");
    
    
    /** action groups **/
    // add an action group named "deny_admin" under the module "or"
    $res=shn_acl_add_action_group("vr","deny_admin","Administrative Action Group");
    $res=shn_acl_add_action("vr","deny_admin","shn_vr_adm_type_cr","Edit Skill Sets");
    $res=shn_acl_add_action("vr","deny_admin","shn_vr_adm_type_form","Edit Skill Sets");
    //deny permission for 'deny_admin' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','vr','deny_admin');
    $res=shn_acl_add_perms_action_group_role('user','vr','deny_admin');
    
    // add an action group named "deny_user" under the module "or"
    $res=shn_acl_add_action_group("vr","deny_user","deny user group");
    //add an action name 'shn_or_reg_org"  under above action groups
    $res=shn_acl_add_action("vr","deny_user","shn_vr_vol_edit","Assign Volunteers to Projects");
    $res=shn_acl_add_action("vr","deny_user","shn_vr_ch_pwd","Display all Volunteers");
    $res=shn_acl_add_action("vr","deny_user","shn_vr_home","Add a new Project");

	$res=shn_acl_add_perms_action_group_role('guest','vr','deny_user');

    if($res_acl->EOF)
	 $q="insert into config values('vr','acl_base','installed')";
    else
	 $q="update config set value='installed' where module_id='vr' and confkey='acl_base'";
    $res=$db->Execute($q);
    $msg="ACL Base for Volunteer Registry Module was succesfully installed";

?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}



?>
