<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once("errors.inc");

//ravindra
function shn_setup_sample_acl(){
 	global $global;
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
}
