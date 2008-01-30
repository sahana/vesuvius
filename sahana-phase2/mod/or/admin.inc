<?php
/**Admin controller of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once "admin_forms.inc";

function _shn_or_adm_sub_menu()
{
?>
<div id="submenu_v">
<a href="index.php?mod=or&act=adm_or_type"><?php echo _t("Organization Types")?></a> 
<a href="index.php?mod=or&act=adm_sector"><?php echo _t("Organization Sectors")?></a>
<!--<a href="index.php?mod=or&act=adm_location_range">Set Location Range</a>
<a href="index.php?mod=or&act=adm_location">Set starting Location</a> -->
</div>

<br>
<?php
}
function shn_or_adm_default()
{
    _shn_or_adm_sub_menu();
?>
    <p><b> <?php echo _t("Welcome to the OR admin page")?> </b></p>
    <p> <?php echo _t("Use the Above Navigation to Administer Org Registry")?></p>

    


<?php
}



function shn_or_adm_or_type()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_type_form();
}

function shn_or_adm_type_cr()
{
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    	$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_org_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="DELETE FROM field_options WHERE field_name='opt_org_type' AND option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
    $msg= "Organization types were succesfully added/removed ";
    add_confirmation($msg);
    shn_or_adm_or_type();
}

function shn_or_adm_sector()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_sector_form();
}

function shn_or_adm_sector_cr(){
	
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    	$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_sector_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="DELETE FROM field_options WHERE field_name='opt_sector_type' AND option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
        	$msg= _t("Organization services were succesfully added/removed ");
     	add_confirmation($msg);
    shn_or_adm_sector();
}

function shn_or_adm_acl_install()
{
    global $global;
    $db=$global["db"];
    $q="SELECT value FROM config WHERE module_id='or' AND confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        $msg="ACL Base for Organization Registry is already installed";
    }
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
  //  include_once $global['approot'].'inc/lib_security/authenticate.inc';
    $acl=new SahanaACL(NULL);

 /** start of or specifc ACL entries
 **/
     
     // add a module named "or"
    $res=shn_acl_add_module("or","organization reg");
    
    /** action groups **/
    // add an action group named "deny_admin" under the module "or"
    $res=shn_acl_add_action_group("or","deny_admin","deny admin group");
    $res=shn_acl_add_action("or","deny_admin","shn_or_acl_setup","Display ACL configuration info");
    $res=shn_acl_add_action("or","deny_admin","shn_or_adm_default","Display Admin page");
    $res=shn_acl_add_action("or","deny_admin","shn_or_adm_or_type","Display Admin Or type page");
    $res=shn_acl_add_action("or","deny_admin","shn_or_adm_sector","Display Admin Or sector page");
    $res=shn_acl_add_action("or","deny_admin","shn_or_adm_location_range","Display Admin Or location range page");
    $res=shn_acl_add_action("or","deny_admin","shn_or_adm_location","Display Admin Or location page");
     //deny permission for 'deny_admin' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','or','deny_admin');
    $res=shn_acl_add_perms_action_group_role('user','or','deny_admin');
    
    // add an action group named "deny_user" under the module "or"
    $res=shn_acl_add_action_group("or","deny_user","deny user group");
    //add an action name 'shn_or_reg_org"  under above action groups
    $res=shn_acl_add_action("or","deny_user","shn_or_reg_org","Display Organization Registration form");
    $res=shn_acl_add_action("or","deny_user","shn_or_reg_org_cr","Save Organization Registration info");
    $res=shn_acl_add_action("or","deny_user","shn_or_reg_operation","Save Operation Registration form");
    $res=shn_acl_add_action("or","deny_user","shn_or_reg_operation_cr","Save Operation Registration form");
    $res=shn_acl_add_action("or","deny_user","_shn_or_edit_org","edit Org Registration form");
    $res=shn_acl_add_action("or","deny_user","_shn_or_del_org","delete Org Registration form");
 

	$res=shn_acl_add_perms_action_group_role('guest','or','deny_user');
         
    if($res_acl->EOF) {
	 $q="INSERT INTO config VALUES('or','acl_base','installed')";
    }else {
	$q="UPDATE config set value='installed' WHERE module_id='or' AND confkey='acl_base'";
    }
    $res=$db->Execute($q);
    $msg=_t("ACL Base for Organization Registry was succesfully installed");

?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}

?>
