<?php

/*
*
* Sahana Admin & ACL section
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

global $global;

    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot']. 'inc/lib_security/authenticate.inc';
    include_once $global['approot'].'inc/lib_security/acl_user_form.inc';
    include_once $global['approot'].'inc/lib_security/acl_role_form.inc';
	include_once $global['approot'].'inc/lib_security/acl_action_form.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot']."/inc/lib_errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
    include_once "menu.inc";

function _shn_admin_acl_default()
{
    global $conf;
    global $global;
    $db=$global["db"];
    $q="select value from config where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    if($res->fields[0]!='installed'){
         echo "<a href='index.php?mod=admin&act=acl_install'>ACL is not Installed! You need to Install ACL Base and then Module Default ACL </a>";
        return;
    }
    $module=$_GET['sel']; 
    $q="select value from config where module_id='{$module}' and confkey='acl_base'";
    $res=$db->Execute($q);
    
    if($res->EOF || $res->fields[0]!='installed'){
         echo "ACL for the Module is not Installed! You need to Install Module Default ACL<br /> ";
         echo "<a href='index.php?mod=admin&act=acl_mod_install&script=true&sel=".$module."'>Click here if you have ACL install script in your module</a><br />";
         echo "<a href='index.php?mod=admin&act=acl_mod_install&sel=".$module."'>Otherwise Click here to install Sytem defaults</a><br />";
    return;
    }  
   	//_shn_admin_acl_module_sub_menu($module);
?>

        <h2 align="center">Welcome to the Sahana ACL page for <?php echo $conf['mod_'.$module.'_name']?></h2>

<?php
 echo _("ACL is Installed,choose below to reinstall")."<br />";
 echo "<a href='index.php?mod=admin&act=acl_mod_install&script=true&sel=".$module."'>Click here if you have ACL install script in your module</a><br />";
 echo "<a href='index.php?mod=admin&act=acl_mod_install&sel=".$module."'>Otherwise Click here to install Sytem defaults</a><br />";
}

function _shn_admin_acl_system()
{

	_shn_admin_acl_system_menu();

        


}
function _shn_admin_acl_module()
{

	_shn_admin_acl_module_menu();
        

}

function _shn_admin_acl_module_cr()
{
	global $global;
    $db=$global['db'];
	$q="update config set value=false where confkey='acl_enabled'";
	$db->Execute($q); 
	foreach ($_POST as $name=>$val){
		$q="update config set value=true where module_id='{$name}' and confkey='acl_enabled'";
		$db->Execute($q); 
	}
	_shn_admin_acl_module();
}

function _shn_admin_acl_state(){
      if("enable"==$_GET['do']){
            shn_acl_set_state();
	        
        }
    if("disable"==$_GET['do']){
	    if (shn_acl_check_perms_action($_SESSION["user_id"],"shn_acl_set_state")){
            shn_acl_set_state();
	        
        }
     }	
_shn_admin_acl_system_menu();
?>
         <h2 align="center">Welcome to the Sahana ACL System Configuration page</h2>

<?php
}

function _shn_admin_acl_existing_perms_tab()
{

    $module=$_GET['sel'];    
    shn_acl_form_existing_perms_tabular($module,false);
}

function _shn_admin_acl_action()
{
    global $conf;
 	$module=$_GET['sel'];
_shn_admin_acl_module_sub_menu($module);
?>

<h2 align="center">Configure ACL actions for <?php echo $conf['mod_'.$module.'_name']?></h2>

<?php
    shn_acl_form_add_action($module);
}

function _shn_admin_acl_action_cr()
{
    global $conf;
 	$module=$_GET['sel'];


   global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
   	$remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
        if($temp[2]=='none'){
	        $res=shn_acl_add_action($module,NULL,$temp[0],$temp[1]);
        }else{
	        $res=shn_acl_add_action_id($temp[2],$temp[0],$temp[1]);
	}

    }
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        shn_rem_action($temp[0]);
        $res=$db->Execute($q);
    }
_shn_admin_acl_action();
}

function _shn_admin_acl_action_group()
{
    global $conf;
 	$module=$_GET['sel'];
_shn_admin_acl_module_sub_menu($module);

?>

<h2 align="center">Configure ACL actions for <?php echo $conf['mod_'.$module.'_name']?></h2>

<?php
    shn_acl_form_add_action_group($module);
}

function _shn_admin_acl_action_group_cr()
{
    global $conf;
 	$module=$_GET['sel'];

    shn_acl_add_module($module,$module);
   global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
   	$remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
$res=shn_acl_add_action_group($module,$temp[0],$temp[1]);
}
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        shn_rem_action_group($temp[0]);
        
    }
_shn_admin_acl_action_group();
}

function _shn_admin_acl_user()
{
global $conf;
 	$module=$_GET['sel'];

	_shn_admin_acl_user_menu($module);
if($module=='admin'){
?>
<h2 align="center">Configure ACL User Permissions for all Modules</h2>
<?php
} else{
?>
<h2 align="center">Configure ACL User Permissions for <?php echo $conf['mod_'.$module.'_name']?></h2>

<?php

//     shn_acl_form_existing_perms_grid($module,false);
}
}

function _shn_admin_acl_user_perms()
{

 	$module=$_GET['sel'];
_shn_admin_acl_module_sub_menu($module);
	shn_acl_form_user_perms_grid($module,false);
}

function _shn_admin_acl_role_perms()
{

 	$module=$_GET['sel'];
_shn_admin_acl_role_menu($module);
	shn_acl_form_role_perms_grid($module,false);
}

function _shn_admin_acl_role_edit_perms()
{

 	$module=$_GET['sel'];
_shn_admin_acl_role_menu($module);
	shn_acl_form_role_edit_perms($module,false);
}


function _shn_admin_acl_role_edit_perms_cr($module=NULL,$error=false){
$perm_string=$_POST{"perms"};
$perms=explode(";",$perm_string);
_shn_admin_acl_role_menu($module);
if(!shn_rem_perms_action_group($module))
    return false;
for ($i=0;$i<count($perms)-1;$i++){
    $rule=explode(":",$perms[$i]);
    $role=$rule[0];
    $action_group=$rule[1];
   $name=$role."_".$action_group;
   if(isset($_POST{trim($name)})){
         $res=shn_acl_add_perms_action_group_id_role_id($role,$module,$action_group);
    }
}

}


function _shn_admin_acl_mod_install(){
	global $global;
	$global['approot']."/inc/lib_errors.inc";
	$db=$global["db"];
   	$module=$_GET{"sel"};
   	if($_GET{"script"}==true){
   		$module_function='shn_'.$module.'_adm_acl_install';
   		 // include the correct module file based on action and module
    	$module_file = $global['approot'].'/mod/'.$module.'/admin.inc';
    	if (file_exists($module_file)) {
	    	include_once($module_file);
	    	if (function_exists($module_function)) {
        		$module_function();
        		$q = "SELECT value FROM config WHERE module_id='{$module}' AND confkey='acl_enabled'";
    			$res_acl = $db->Execute($q);
				if(($res_acl!=NULL) && (!$res_acl->EOF))
      				$q="update config set value=true where confkey='acl_enabled' and module_id='{$module}'";
      			else
        			$q="insert into config values('{$module}','acl_enabled',true)";
				$db->Execute($q);
        		return;
        	}else {
        		echo  _("Sorry ! It seems you do not have an ACL script");
            	return;
        	}
    	} else {
        	echo  _("Sorry ! It seems you do not have an ACL script");
            return;
   		}
   	   
   }
   
    $acl=new SahanaACL(NULL);
    $res=shn_acl_add_module($module,$module);
     // add an action group named "view" under the module "home"
    $res=shn_acl_add_action_group($module,"none","default group");
    $q="select value from config where module_id='{$module}' and confkey='acl_base'";
    $res_acl=$db->Execute($q);
    if(!$res_acl->EOF && $res_acl->fields[0]=='installed'){
        echo "ACL Base for ".$module." is already installed";
        return;
    }
    if($res_acl->EOF){
    	$q="insert into config values('{$module}','acl_enabled',true)";
		$db->Execute($q);
        $q="insert into config values('$module','acl_base','installed')";
    }else
         $q="update config set value='installed' where module_id='$module' and confkey='acl_base'";
    $res=$db->Execute($q);
    echo  _("Default ACL was succesfully installed");

}

function _shn_admin_acl_install(){
    global $global;
    global $conf;
    $db=$global["db"];
    $q="select value from config where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    if($res->fields[0]=='installed'){
        $msg="ACL Base is already installed";
    }else {
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot'].'inc/lib_security/authenticate.inc';
    $acl=new SahanaACL(NULL);

/*****************************************************************/
/** ACL common to all modules ,this piece of code will be removed from
or_acl_setup to sahana setup script once its avaliable
**/
    /**
    add a section to categorize sahana users in ARO table.
    used is a function in acl.inc which you need not call
    as module writers. "users" section needs to be added only
    once per sahana and will be done at the installation
    */
    $acl->_shn_add_section("users","users of sahana","ARO");
    /**
    add a section to categorize sahana acions in AXO table.
    used is a function in acl.inc which you need not call
    as module writers. "actions" section needs to be added only
    once per sahana and will be done at the installation
    */
    $acl->_shn_add_section("actions","actions avaliable in sahana","ARO");
    //add a group to contain Sahana AROs(root group)
    $acl->_shn_add_aro_group("sahana","Sahana ARO root",0);
     // add a role named guest
    $res=shn_acl_add_role("guest","guest role");
   // add a role named user
    $res=shn_acl_add_role("user","Normal user role");
   // add a role named guest
    $res=shn_acl_add_role("admin","Administrator role");
    //add a group to contain Sahana AXOs(root group)
    $acl->_shn_add_axo_group("sahana","Sahana AXO root",0);
    /** add a ACO , not neccesary to protect actions, but when  we go to
    table and field level protection need to seperate "read","write"
    permissions , hence requires ACO
    */
   	$res=shn_acl_add_perm_type("execute","execute permission");
    // adds guest user with password and add the user to ACL users and add to 'guest' role
    $guest=shn_add_user("Guest User","guest",$conf['guest_pwd'],"guest",$conf['guest_id']); 
    //add a"guest" user to ACL users and add to 'guest' role
    $q="insert into org_users(org_id,user_id) values(0,{$conf['guest_id']})";
    $res=$db->Execute($q);
     // adds sahana user with password and add the user to ACL users and add to 'user' role
    $guest=shn_add_user("Sahana User","sahana",$conf['user_pwd'],"user",$conf['user_id']); 
    //add a"guest" user to ACL users and add to 'guest' role
    $q="insert into org_users(org_id,user_id) values(0,{$conf['user_id']})";
    $res=$db->Execute($q);
    $root=shn_add_user("Root User","root",$conf['root_pwd'],"admin",$conf['root_id']); 
    //add a "root" user to ACL users and add to 'admin' role
    $q="insert into org_users(org_id,user_id) values(0,{$conf['root_id']})";
    $res=$db->Execute($q);
    /************************************/
    //give permission for the guest user to sahana home
    // add a module named "admin"
    $res=shn_acl_add_module("admin","Sahana Admin");
     // add an action group named "view" under the module "home"
    $res=shn_acl_add_action_group("admin","deny_admin","admin group");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_default","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_add_loc","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_loc_lvl","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_edit_loc_cr","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_edit_loc_cr","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_acl_system","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_acl_module","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_lc_set","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_lc_db","admin function");
    $res=shn_acl_add_action("admin","deny_admin","shn_admin_lc_trns","admin function");
    //give permission for 'view' action group with in 'home' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','admin','deny_admin');
  //give permission for 'view' action group with in 'home' to 'user' role
    $res=shn_acl_add_perms_action_group_role('user','admin','deny_admin');
    $q="update config set value='installed' where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    $q="insert into config values('admin','acl_enabled',false)";
	$db->Execute($q);
	// add a module named "home"
    $res=shn_acl_add_module("home","Sahana Home");
    $q="insert into config values('home','acl_enabled',false)";
	$db->Execute($q);
    $q="insert into config values('home','acl_base','installed')";
    $res=$db->Execute($q);
    $msg="ACL Base was succesfully installed";
    }

?>
    <div id="result_msg">
        <?php echo $msg; ?>
    </div>
    </br>
<?php
}

function _shn_admin_acl_user_edit_roles($module=NULL,$error=false){

	_shn_admin_acl_user_menu($module);
shn_acl_form_user_edit_roles($module,$error);
}

function _shn_admin_acl_user_edit_roles_cr($module=NULL,$error=false){
$perm_string=$_POST{"perms"};
$perms=explode(";",$perm_string);

if(!shn_acl_rem_user_role_map())
    return false;
for ($i=0;$i<count($perms)-1;$i++){
    $rule=explode(":",$perms[$i]);
    $user=$rule[0];
    $role=$rule[1];
    //echo $user;
    //echo $role;
    $name=$user.$role;
   if(isset($_POST{trim($name)})){
         shn_acl_add_to_role($user,$role);
    }
}

_shn_admin_acl_user_menu($module);

}
function _shn_admin_acl_user_add_roles($module=NULL,$error=false)
{

if(is_null($module)){
$module=$_GET['sel'];   
}

    _shn_admin_acl_user_menu($module);
global $conf;
?>
<h2 align="center">Configure ACL user permissions for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php

    shn_acl_form_user_add_roles($module,$error);
}


function _shn_admin_acl_user_add_roles_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"users"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $user=$_POST{"users"};
    }

    if (is_null($_POST{"roles"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $role=$_POST{"roles"};
    }
    $i=0;
    while($i<count($user)){
	$j=0;
    	while($j<count($role)){
		$res=shn_acl_add_to_role($user[$i],$role[$j]);
		$j=$j+1;
	}
	$i=$i+1;
}

shn_admin_acl_user_add_roles($module,false);
if ($res){
?>
<div id="save">
Users were succesfully added to Roles
</div>
<?php
}
}

function _shn_admin_acl_role()
{
     $module=$_GET['sel'];  
global $conf;

    _shn_admin_acl_role_menu($module);
?>

<h2 align="center">Configure ACL Role permissions</h2>
<?php
}

function _shn_admin_acl_role_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"action_groups"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $action_group=$_POST{"action_groups"};
    }

if (is_null($_POST{"roles"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $role=$_POST{"roles"};
    }
$i=0;
    while($i<count($role)){
	$j=0;
    	while($j<count($action_group)){
            $res=shn_acl_add_perms_action_group_role($role[$i],$module,$action_group[$j]);
              
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Roles were succesfully given permission to action groups
</div>
<?php
}
shn_admin_acl_role($module,false);
}
function _shn_admin_acl_user_add_perms()
{
    $module=$_GET['sel']; 
    global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_user_menu($module);
    shn_acl_form_user_add_perms($module,false);
}


function _shn_admin_acl_user_edit_perms_cr(){
$perm_string=$_POST{"perms"};
$perms=explode(";",$perm_string);
var_dump($perms);
}
function _shn_admin_acl_user_edit_perms()
{
    $module=$_GET['sel']; 
    global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_user_menu($module);
    shn_acl_form_user_edit_perms($module,false);
}

function _shn_admin_acl_user_cr()
{
    global $global;
    $module=$_GET['sel'];  

    if (is_null($_POST{"action_groups"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $action_group=$_POST{"action_groups"};
    }

    if (is_null($_POST{"users"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $user=$_POST{"users"};
    }
    $i=0;
    while($i<count($user)){
	$j=0;
    	while($j<count($action_group)){
            $res=shn_acl_add_perms_action_group_user($user[$i],$module,$action_group[$j]);
              
		$j=$j+1;
	}
	$i=$i+1;
}
if ($res){
?>
<div id="save">
Roles were succesfully given permission to action groups
</div>
<?php
}


_shn_admin_acl_user($module,false);
}




?>
