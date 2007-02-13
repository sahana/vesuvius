<?php
/**Admin controller of the Volunteer coordination System 
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

function _shn_vol_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=vol&act=adm_skills">Add Skills</a> 
<!--<a href="index.php?mod=or&act=adm_sector">Organization Sectors</a>
<a href="index.php?mod=or&act=adm_location_range">Set Location Range</a>
<a href="index.php?mod=or&act=adm_location">Set starting Location</a> -->
</div>

<br>
<?php
}
function shn_vol_adm_default()
{
    _shn_vol_adm_sub_menu();
?>
    <p><b> Welcome to the Volunteer Coordiantion admin page </b></p>
    <p> Use the Above Navigation to Administer</p>

    


<?php
}



function shn_vol_adm_skills()
{
    _shn_vol_adm_sub_menu();
    shn_vol_adm_skill_form();
}

function shn_vol_adm_skill_cr()
{
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    		$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="insert into field_options(field_name,option_code,option_description) values('opt_skill_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="delete from field_options where field_name='opt_skill_type' and option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
    	    $msg= "Skills were succesfully added ";
    add_confirmation($msg);
    shn_vol_adm_skills();
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
        $q="insert into field_options(field_name,option_code,option_description) values('opt_sector_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="delete from field_options where field_name='opt_sector_type' and option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
        	$msg= "Organization services were succesfully added/removed ";
     	add_confirmation($msg);
    shn_or_adm_sector();
}

function shn_or_adm_acl_install()
{
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='or' and confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        $msg="ACL Base for Organization Registry is already installed";
    }
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot'].'inc/lib_security/authenticate.inc';
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
         
    if($res_acl->EOF)
	 $q="insert into config values('or','acl_base','installed')";
    else
	 $q="update config set value='installed' where module_id='or' and confkey='acl_base'";
    $res=$db->Execute($q);
    $msg="ACL Base for Organization Registry was succesfully installed";

?>
    <div id="result_msg">
       <?php echo $msg;?>
    </div>
    </br>
<?php
}

?>
