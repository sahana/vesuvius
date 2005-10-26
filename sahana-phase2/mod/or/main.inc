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
* @author 	  Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/handler_form.inc";
include_once ("reg.inc"); // call form generator
include_once("view.inc");

function shn_or_acl_setup(){
 	global $global;
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
    include_once $global['approot'].'inc/lib_security/acl.inc';
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
  
 /*****************************************************************/
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
    //add an action name 'shn_or_reg_org"  under the above action group
    $res=shn_acl_add_action("or","create","shn_or_reg_org","Register function");
    $res=shn_acl_add_action("or","create","shn_or_reg_org_cr","Register function");
    $res=shn_acl_add_action("or","create","shn_or__reg_branch_cr","Register function");
    $res=shn_acl_add_action("or","create","shn_or_reg_vol","Register function");
    $res=shn_acl_add_action("or","create","shn_or_reg_vol_cr","Register function");
    $res=shn_acl_add_action("or","view","shn_or_view_org","View function");
    $res=shn_acl_add_action("or","view","shn_or_default","View function");
    // add an action case name "view_all"  under the above case
    $res=shn_acl_add_action_case("or","view","shn_or_view_org","all","action case");
    
    
    //give permission for 'create' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','or','create');
    
    //add a user named "ravids"
    $res=shn_acl_add_user("ravids","ravindra");
    // add "ravids" to the "guest" role
    $res=shn_acl_add_to_role("ravids","guest");
   
    //check whether permission was added as expected. should return true
    $res=shn_acl_check_perms_action('ravids','shn_or_reg_org');
    echo "res1".$res;
   
   $res=shn_acl_check_perms_action('ravids','shn_or_default');
    echo "res2".$res;
    
   //give permission for 'create' action group with in 'or' to 'guest' role
    $res=shn_acl_add_perms_action_group_role('guest','or','view');
    
   $res=shn_acl_check_perms_action('ravids','shn_or_default');
    echo "res2".$res;
 

   
}

function shn_or_mainmenu() 
{
    global $global;
    $module = $global['module'];
    include $global['approot']."/inc/handler_mainmenu.inc";
?>
    
   <div id="modmenuwrap"> 
        <h2>OR Module Actions</h2>
            <ul id="modulemenu">
                <li id="modactive"><a href="index.php?mod=<?=$module?>&act=reg_org">Register a Organization</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Register as a Volunteer</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=view_org">View all Organizations</a></li>
            </ul>
    </div>
<?php 
} 

// register a OR
function shn_or_reg_org()
{
    shn_or_regform_org();
}

function shn_or_reg_org_cr()
{
    $org_name=$_POST{"org_name"};
    $org_type=$_POST{"org_type"};
    $org_sector=$_POST{"org_sector"};
    $bsd_village=$_POST{"bsd_village"};
    $reg_no=$_POST{"reg_no"};
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};
    $contact_mail=$_POST{"contact_mail"};

    $man_power=$_POST{"man_power"};
    $resources=$_POST{"resources"};

    $user_name=$_POST{"user_name"};
    $password=$_POST{"password"};
    $re_password=$_POST{"re_password"};

    $chk_avail=(isset ($_POST{"chk_avail"}))?1:0;
    $chk_branch=$_POST{"chk_branch"};

    global $global;
    $db=$global['db'];
    
    $org_id = $db->GenID('org_seq',1);
//Double check the ACL ID was generated.
    if (empty($org_id)){
    //("add_org(): ORG_ID generation failed!");
        return false;
    }
    
    $q="insert into org_main(o_uuid,parent_id,name,opt_org_type,reg_no,man_power,resources,privacy)values($org_id,0,'{$org_name}','{$org_type}','{$reg_no}','{$man_power}','{$resources}',$chk_avail)";
    $res=$db->Execute($q);

    $i=0;
    while($i<count($org_sector)){
        $q="insert into org_sector(org_id,opt_org_sector) values($org_id,'{$org_sector[$i]}')";
        $res=$db->Execute($q);
        $i=$i+1;
    }
    
    $pid=time();
    $q="insert into person_uuid(p_uuid,name) values($pid,'{$contact_name}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgc_uuid,opt_contact_type,contact_value) values($org_id,'home','{$contact_address}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgc_uuid,opt_contact_type,contact_value) values($org_id,'curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgc_uuid,opt_contact_type,contact_value) values($org_id,'fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgc_uuid,opt_contact_type,contact_value) values($org_id,'email','{$contact_mail}')";
    $res=$db->Execute($q);
    $q="insert into users(p_uuid,username,password) values($pid,'{$user_name}','{$password}')";
    $res=$db->Execute($q);
    $q="insert into org_users(org_id,user_id) values($org_id,$pid)";
    $res=$db->Execute($q);

    $q="insert into org_location(org_id,location_id) values($org_id,'{$bsd_village}')";
    $res=$db->Execute($q);
    var_dump($q);
    
    if($res==false){
        return false;
    }else {
      //  shn_or_branch_reg();
    }

    //n_or_branch_reg();
}


function shn_or_branch_reg_cr(){
}

// register a volunteer
function shn_or_reg_vol(){
	shn_or_vol_reg();
}

// register a volunteer
function shn_or_reg_vol_cr(){
	shn_or_vol_reg();
}

// view all OR
function shn_or_view_org()
{
    shn_or_viewform_org();
}

// default page, welcome page ;-)
function shn_or_default()
{
?>
    <center><h3><b> Welcome to Organization Registry</p><br></b></h3></center>
    <?php
       include_once ("home.inc");



}

?>
