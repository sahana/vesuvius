<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once "admin_forms.inc";

function _shn_or_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=or&act=adm_or_type">Organization Types</a> 
<a href="index.php?mod=or&act=adm_sector">Organization Sectors</a>
<a href="index.php?mod=or&act=adm_location">Set starting Location</a>
</div>

<br>
<?php
}
function shn_or_adm_default()
{
    _shn_or_adm_sub_menu();
?>
    <p><b> Welcome to the OR admin page </b></p>
    <p> Use the Above Navigation to Administer Org Registry</p>

    


<?php
}

function shn_or_adm_location()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_location_form();
}
function shn_or_adm_location_cr()
{
    global $global;
    $db=$global['db'];
    if (isset($_POST{"chk_start"})){
        $loc=0;
    }else {
        $level=$_POST{"level"};
        $loc=$_POST{$level};
    }
    $q="update config set value={$loc} where module_id='or' and confkey='loc_start'";
    $db->Execute($q);
    shn_or_adm_location();
}
function shn_or_adm_or_type()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_type_form();
}

function shn_or_adm_type_cr(){
    global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
    $remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
        $q="insert into field_options(field_name,option_code,option_description) values('opt_org_type','{$temp[0]}','{$temp[1]}')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        $q="delete from field_options where field_name='opt_org_type' and option_code='".$temp[0]."'";
        $res=$db->Execute($q);
    }
    shn_or_adm_or_type();
}

function shn_or_adm_sector()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_sector_form();
}

function shn_or_adm_sector_cr(){
    global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
    $remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
        $q="insert into field_options(field_name,option_code,option_description) values('opt_sector_type','{$temp[0]}','{$temp[1]}')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        $q="delete from field_options where field_name='opt_sector_type' and option_code='".$temp[0]."'";
        $res=$db->Execute($q);
    }
    shn_or_adm_sector();
}

function shn_or_adm_acl_install(){
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='or' and confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        $msg="ACL Base for Organization Registry is already installed";
    }else {
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot'].'inc/lib_security/authenticate.inc';
    $acl=new SahanaACL(NULL);

 /** start of or specifc ACL entries
 **/
     
     // add a module named "or"
    $res=shn_acl_add_module("or","organization reg");
    
    /** action groups **/
    // add an action group named "create" under the module "or"
    $res=shn_acl_add_action_group("or","create","create group");
    // add an action group named "delete" under the module "or"
    $res=shn_acl_add_action_group("or","delete","delete group");
    // add an action group named "update" under the module "or"
    $res=shn_acl_add_action_group("or","update","update group");
    // add an action group named "view" under the module "or"
    $res=shn_acl_add_action_group("or","view","view group");
    // add an action group named "admin" under the module "or"
    $res=shn_acl_add_action_group("or","acl","ACL group");
 
   //add an action name 'shn_or_reg_org"  under above action groups
    $res=shn_acl_add_action("or","create","shn_or_reg_org","Display Organization Registration form");
    $res=shn_acl_add_action("or","create","shn_or_reg_org_cr","Save Organization Registration info");
    $res=shn_acl_add_action("or","create","shn_or_reg_operation_cr","Save Operation Registration form");
    $res=shn_acl_add_action("or","create","shn_or_reg_vol","Display Volunteer Registration form");
    $res=shn_acl_add_action("or","create","shn_or_reg_vol_cr","Save Volunteer Registration info");

    $res=shn_acl_add_action("or","view","shn_or_view_org","View Organization Registration info");
    $res=shn_acl_add_action("or","view","shn_or_view_vol","View Volunteer Registration info");
    $res=shn_acl_add_action("or","view","shn_or_default","Organization Registry Home");
    // add an action case name "view_all"  under the above case
    $res=shn_acl_add_action_case("or","view","shn_or_view_org","all","action case");
    $res=shn_acl_add_action("or","acl","shn_or_acl_setup","Display ACL configuration info");
    
    //give permission for 'create' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','or','create');
    //give permission for 'create' action group with in 'or' to 'user' role
    $res=shn_acl_add_perms_action_group_role('user','or','create');
    //give permission for 'create' action group with in 'or' to 'admin' role
    $res=shn_acl_add_perms_action_group_role('admin','or','create');

    //give permission for 'view' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','or','view');
    //give permission for 'view' action group with in 'or' to 'user' role
    $res=shn_acl_add_perms_action_group_role('user','or','view');
    //give permission for 'view' action group with in 'or' to 'admin' role
    $res=shn_acl_add_perms_action_group_role('admin','or','view');

    //give permission for 'admin' action group with in 'or' to 'admin' role
    $res=shn_acl_add_perms_action_group_role('admin','or','acl');
    if($res_acl->EOF)
	 $q="insert into config values('or','acl_base','installed')";
    else
	 $q="update config set value='installed' where module_id='or' and confkey='acl_base'";
    $res=$db->Execute($q);
    $msg="ACL Base for Organization Registry was succesfully installed";
}
?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}

?>
