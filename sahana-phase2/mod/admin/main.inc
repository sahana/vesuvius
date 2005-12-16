<?PHP

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
* @author     Chamindra <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;

    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot']. 'inc/lib_security/authenticate.inc';
    include_once $global['approot'].'inc/lib_security/acl_form.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
    include_once $global['approot']."/inc/lib_errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";

function shn_admin_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
    $acl=shn_acl_get_state();
     // display the list of modules on the menu bar
    $module_list = shn_get_modules_with_admin();
    $db=$global["db"];
    $q="select value from config where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    if(!$res->EOF && $res->fields[0]=='installed'){
        $visible=true;
    }else {
        $visible=false;
    }
?>
    <div id="modmenuwrap">
        <h2>Administration</h2>
            <ul id="modmenu">
                <li><a href="#">Module Config </a></li>
                    <ul id="modsubmenu">
<?php foreach ($module_list as $i) {  ?>
                        <li><a href="index.php?mod=<?=$i?>&act=adm_default"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?> 
                    </ul>

                <li><a href="#">Security </a></li>
                    <ul id="modsubmenu">
                         <li><a href="index.php?mod=admin&act=add_user">Add an User</a></li>
                        <li><a href="index.php?mod=admin&act=del_user">Delete User</a></li>
                        <li><a href="index.php?mod=admin&act=ch_pwd">ChangePassword</a></li>
                   </ul>
                <li><a href="#">ACL Config </a></li>
                    <ul id="modsubmenu">
<li><a href="index.php?mod=admin&act=acl_system">ACL System Config</a></li> 
<li><a href="index.php?mod=admin&act=acl_module">ACL Module Config</a></li> 
                   </ul>
         </ul>
        </dd>
        </dt>
    </div> <!-- /modmenuwrap -->    
<?php 
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	
function shn_admin_view()
{ 
    global $global;
?>

        <p><b>You called the admin view </b></p>
        <p> on module </p>
<?php
        
}

function shn_admin_default()
{ ?>
        <p><b>Welcome to the Sahana admin page</b></p>
        <p> This is the default  of admin</p>

<?php
}

function shn_admin_modadmin() 
{
    global $global;
    include $global['approot']."/mod/".$global['module']."/admin.inc";
    // compose and call the relevant module function 
    $module_function = "shn_".$global['module']."_".$global['action'];
    if (!function_exists($module_function)) {
        $module_function="shn_".$module."_default";
    } 
    $module_function(); 
}


function shn_admin_acl_default()
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
         echo "<a href='index.php?mod=".$module."&act=adm_acl_install'>ACL for the Module is not Installed! You need to Install Module Default ACL </a>";
        return;
    }   
?>

        <h2>Welcome to the Sahana ACL page</h2>
        <h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>

<?php
	_shn_admin_acl_sub_menu($module);
     shn_acl_form_existing_perms_grid($module,false);
}

function shn_admin_acl_system()
{
?>
         <h2>Welcome to the Sahana ACL System Configuration page</h2>

<?php
	_shn_admin_acl_system_menu();
}
function shn_admin_acl_module()
{
?>
         <h2>Welcome to the Sahana ACL Module Configuration page</h2>

<?php
	_shn_admin_acl_module_menu();
}

function shn_admin_acl_existing_perms_tab()
{
    $module=$_GET['sel'];    
    shn_acl_form_existing_perms_tabular($module,false);
}


function _shn_admin_acl_module_menu(){
global $conf;
$module_list = shn_get_modules_with_admin();
?>
<div id="submenu_v">
<?php
foreach ($module_list as $i) {
                 echo"<a href='index.php?mod=admin&act=acl_default&sel=".$i."'>".$conf['mod_'.$i.'_name']."</a>"; } ?> 
</div>
<?php
}
function _shn_admin_acl_system_menu()
{
?>
<div id="submenu_v">
<?php
global $global;
$db=$global["db"];
    $q="select value from config where module_id='admin' and confkey='acl_base'";
    $res=$db->Execute($q);
    if(!$res->EOF && $res->fields[0]=='installed'){
        $visible=true;
    }else {
        $visible=false;
    }
if($visible==true){
if ($acl==true){
	echo "<a href='index.php?mod=admin&act=acl_state&do=disable'><b>D</b>isable ACL</a>";
}else {
	echo "<a href='index.php?mod=admin&act=acl_state&do=enable'><b>E</b>nable ACL</a>" ;
}
}
?>
<a href="index.php?mod=admin&act=acl_install"><b>A</b>CL Base Install</a>
</div>
<br>
<?php
}

function _shn_admin_acl_sub_menu($module)
{
?>
<div id="submenu_v">
<a href="index.php?mod=<?php echo $module?>&act=adm_acl_install"><b>Install Default ACL</b></a>
<a href="index.php?mod=admin&act=acl_default&sel=<?php echo $module?>">Existing Permissions</a>
<a href="index.php?mod=admin&act=acl_usr_role&sel=<?php echo $module?>">Add User to Role</a>
<a href="index.php?mod=admin&act=acl_role&sel=<?php echo $module?>">Role Permissions</a>
<a href="index.php?mod=admin&act=acl_user&sel=<?php echo $module?>">User Permissions</a>
<a href="index.php?mod=admin&act=acl_adv&sel=<?php echo $module?>">Advanced Permissions</a>
</div>
<br>
<?php
}


function shn_admin_acl_install(){
    global $global;
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
    $guest=shn_add_user("Guest User","guest","pass","guest",1); 
    //add a"guest" user to ACL users and add to 'guest' role
    $q="insert into org_users(org_id,user_id) values(0,1)";
    $res=$db->Execute($q);
    $root=shn_add_user("Root User","root","rootpwd","admin",0); 
    //add a "root" user to ACL users and add to 'admin' role
    $q="insert into org_users(org_id,user_id) values(0,0)";
    $res=$db->Execute($q);
    /************************************/
    //give permission for the guest user to sahana home
    // add a module named "home"
    $res=shn_acl_add_module("home","Sahana Home");
     // add an action group named "view" under the module "home"
    $res=shn_acl_add_action_group("home","view","view group");
    $res=shn_acl_add_action("home","view","shn_home_default","View function");
    //give permission for 'view' action group with in 'home' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','home','view');
  //give permission for 'view' action group with in 'home' to 'user' role
    $res=shn_acl_add_perms_action_group_role('user','home','view');
  //give permission for 'view' action group with in 'home' to 'admin' role
    $res=shn_acl_add_perms_action_group_role('admin','home','view');
    
    $q="update config set value='installed' where module_id='admin' and confkey='acl_base'";
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

function shn_admin_acl_usr_role($module=NULL,$error=false)
{

if(is_null($module)){
$module=$_GET['sel'];   
}

global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php
    _shn_admin_acl_sub_menu($module);

    shn_acl_form_user_role($module,$error);
}

function shn_admin_acl_usr_role_cr()
{
    global $global;
    $module=$_GET['sel'];  
//$acl=new SahanaACL(NULL);

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
if ($res){
?>
<div id="save">
Users were succesfully added to Roles
</div>
<?php
}
shn_admin_acl_usr_role($module,false);
}

function shn_admin_acl_role()
{
     $module=$_GET['sel'];  
global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php
    _shn_admin_acl_sub_menu($module);
    shn_acl_form_role_perms($module,false);
}

function shn_admin_acl_role_cr()
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



function shn_admin_acl_user()
{
    $module=$_GET['sel']; 
    global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_sub_menu($module);
    shn_acl_form_user_perms($module,false);
}

function shn_admin_acl_user_cr()
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


shn_admin_acl_user($module,false);
}

function shn_admin_acl_adv()
{
     $module=$_GET['sel']; 
global $conf;
?>
<h3>Configure ACL for <?php echo $conf['mod_'.$module.'_name']?></h3>
<?php 
    _shn_admin_acl_sub_menu($module);;
    shn_acl_form_advanced_perms($module,false);
}

function shn_admin_acl_adv_cr()
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
}

function shn_admin_add_user($error=false){
    shn_acl_form_user_add($error);
}

function shn_admin_add_user_cr(){
   global $global;
 $db=$global["db"];
$VARCHAR=100;
   list($error,$user_name)=(shn_validate_user_name($_POST{"user_name"}))?array($error,$_POST{"user_name"}):array(true,NULL);
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_WRONG);
    }
	 if (trim(strlen($_POST{"account_name"})) > $VARCHAR){
        $error=true;
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
        $account_name=$_POST{"account_name"};
    }
    if (is_null($_POST{"org"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $org_id=trim($_POST{"org"});
    }
$pid=shn_add_user($account_name,$user_name,$password,"guest",-1);
             $q="insert into org_users(org_id,user_id) values($org_id,$pid)";
                $res=$db->Execute($q);
          

shn_admin_add_user($error);
}

function shn_admin_ch_pwd($error=false){
    shn_acl_form_ch_pwd($error);
}

function shn_admin_ch_pwd_cr(){
    global $global;
    $db=$global["db"];
    $VARCHAR=100;
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_WRONG);
    }
        $old_password=trim($_POST{"old_password"});
        $user_id=trim($_POST{"user"});
    $error=shn_change_password($user_id,$old_password,$password);
    shn_admin_ch_pwd($error);
}

?>
