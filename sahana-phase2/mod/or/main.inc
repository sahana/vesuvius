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
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once ("reg.inc"); // call form generator
include_once("view.inc");
include_once("report.inc");
include_once("errors.inc");
include_once ("search.inc");

//ravindra
function shn_or_acl_setup(){
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
}

//ravindra,chathra,pradeeper
function shn_or_mainmenu() 
{
    global $global;
    $module = $global['module'];
?>
    
   <div id="modmenuwrap"> 
        <h2>Organization Registry</h2>
            <ul id="modulemenu">
	        	<li><a href="index.php?mod=<?=$module?>&act=default">Home</a></li>
                <li><a href="#">Register </a></li>
              	    <ul id="modsubmenu">
                        <li id="modactive"><a href="index.php?mod=<?=$module?>&act=reg_org">Organization</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Volunteer</a></li>
                    </ul>
                 <li><a href="#">View </a></li>
              	    <ul id="modsubmenu">
                         <li><a href="index.php?mod=<?=$module?>&act=view_org">Organizations</a></li>
	        	        <li><a href="index.php?mod=<?=$module?>&act=view_vol">Volunteers</a></li>
                    </ul> 
		        <li><a href="#">Reports </a></li>
              	    <ul id="modsubmenu">
			        <li><a href="index.php?mod=or&act=report_province">Drill down by Location</a></li>
    	                <li><a href="index.php?mod=or&act=org_sector"> Organizations by Sector</a></li>
                    </ul>   
		        <li><a href="index.php?mod=or&act=search">Search </a></li>
	</ul>
    </div>
<?php 

    include $global['approot']."/inc/handler_mainmenu.inc";
} 

//author ravindra
// register a OR

function shn_acl_config(){

}

//author ravindra
// register a OR

function shn_acl_config_cr(){

}

//author ravindra
// register a OR
function shn_or_reg_org($error=false)
{
    shn_or_regform_org($error);
}

//author ravindra
function shn_or_reg_org_cr()
{
    global $global;
    include_once $global['approot']."/inc/lib_security/authenticate.inc"; 
    $error=false;
    $VARCHAR=100;
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
        
    list($error,$org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"org_type"}):array(true,NULL);
   
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"sector"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"sector"}):array(true,NULL);

    if (is_null($_POST{"bsd_village"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"bsd_village"});
    }

    if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $reg_no=$_POST{"reg_no"};
    }
    if (trim(strlen($_POST{"contact_name"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_name=$_POST{"contact_name"};
    }
/*
    if (trim(strlen($_POST{"contact_add"})) > $CONTACT_ADDRESS){
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
       $contact_address=$_POST{"contact_add"};
    }
*/
    $contact_address=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_phone=$_POST{"contact_phone"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
         $contact_fax=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
    }
    if (trim(strlen($_POST{"man_power"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $man_power=$_POST{"man_power"};
    }
    $resources=$_POST{"resources"};
     if (trim(strlen($_POST{"account_name"})) > $VARCHAR){
        $error=true;
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
        $account_name=$_POST{"account_name"};
    }
   
    /* 
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
*/
    $chk_avail=(isset ($_POST{"chk_avail"}))?1:0;
    $chk_branch=(isset ($_POST{"chk_branch"}))?1:0;

    global $global;
    $db=$global['db'];
    if($error!=true){
        $org_id = $db->GenID('org_seq',1);
        //Double check the ACL ID was generated.
        if (empty($org_id)){
            $error=true;
            //("add_org(): ORG_ID generation failed!");
            return false;
        }
        $q="select o_uuid from org_main where o_uuid='{$org_id}'";
        $res=$db->Execute($q);
        if(!$res->EOF){
            $error=true;
            add_error(SHN_ERR_OR_ORG_EXISTS);
            return false;
        }
        if($error!=true){
            //no validation done on other fields as they are not unique
            $q="insert into org_main(o_uuid,parent_id,name,opt_org_type,reg_no,man_power,resources,privacy)values($org_id,0,'{$org_name}','{$org_type}','{$reg_no}','{$man_power}','{$resources}',$chk_avail)";
            $res=$db->Execute($q);
            $i=0;
            while($i<count($sector)){
                $q="insert into sector(pgoc_uuid,opt_sector) values($org_id,'{$sector[$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            $q="insert into location_details(poc_uuid,location_id,address) values($org_id,'{$bsd_village}','{$contact_address}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'curr','{$contact_phone}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'name','{$contact_name}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'fax','{$contact_fax}')";
            $res=$db->Execute($q);
            $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'email','{$contact_mail}')";
            $res=$db->Execute($q);
          /*
            $pid=shn_add_user($account_name,$user_name,$password,"admin",NULL);
            if($res){
                $q="insert into org_users(org_id,user_id) values($org_id,$pid)";
                $res=$db->Execute($q);
            }
            */
            //no validation as organization can have multiple locations
            $q="insert into org_location(org_id,location_id) values($org_id,'{$bsd_village}')";
            $res=$db->Execute($q);
    }
}
    if((!$chk_branch) or $error){
        if($error!=true){
?>
    <div id="result_msg">
       <?php echo $org_name?> Organization was succesfully registered
    </div>
    </br>
<?php
        }
        shn_or_reg_org($error);
        //return false;
    }else {
         $_SESSION["parent_name"]=$org_name;
         $_SESSION["parent_id"]=$org_id;
         $_SESSION["org_type"]=$org_type;
         $_SESSION["contact_name"]=$contact_name;
         $_SESSION["contact_address"]=$contact_address;
         $_SESSION["contact_phone"]=$contact_phone;
         $_SESSION["contact_fax"]=$contact_fax;
         $_SESSION["contact_email"]=$contact_mail;
         $_SESSION["man_power"]=$man_power;
         $_SESSION["resources"]=$resources;
         shn_or_regform_operation($error=false);
    }
}

//author ravindra
function shn_or_reg_operation_cr(){
    $error=false;
    if (is_null($_POST{"opr_name"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $org_name=$_POST{"opr_name"};
    }
    
    if (is_null($_POST{"sector"})){
        $error=true;
        add_error(SHN_ERR_OR_SECTOR_INCOMPLETE);
    }else {    
        $sector=$_POST{"sector"};
    }
    if (is_null($_POST{"bsd_village"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"bsd_village"};
    }
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};
    $contact_mail=$_POST{"contact_mail"};

    $man_power=$_POST{"man_power"};
    $resources=$_POST{"resources"};

    $chk_branch=(isset ($_POST{"chk_branch"}))?1:0;

    global $global;
    $db=$global['db'];
    //$=$_POST{"operation"}; 
    $org_id = $db->GenID('org_seq',1);
//Double check the ACL ID was generated.
    if (empty($org_id)){
    //("add_org(): ORG_ID generation failed!");
        return false;
    }
    $q="select o_uuid from org_main where o_uuid={$org_id}";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_OR_ORG_EXISTS);
    }
    if(!$error){
        $parent_id=$operation["parent_id"];
    //no validation done on other fields as they are not unique
        $q="insert into org_main(o_uuid,parent_id,name,opt_org_type,man_power,resources)values($org_id,{$_SESSION["parent_id"]},'{$org_name}','{$_SESSION["org_type"]}','{$man_power}','{$resources}')";
        $res=$db->Execute($q);
        $i=0;
        while($i<count($sector)){
            $q="insert into sector(pgoc_uuid,opt_sector) values($org_id,'{$sector[$i]}')";
            $res=$db->Execute($q);
            $i=$i+1;
        }
    }

    $q="insert into location_details(poc_uuid,location_id,address) values($org_id,'{$bsd_village}','{$contact_address}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'email','{$contact_mail}')";
    $res=$db->Execute($q);
    if($error){
        shn_or_regform_operation($error);
    } else {
        if($chk_branch){
            ?>
            <div id="add">
               <h3> <?php echo $org_name ?> was succesfully registered</h3><hr></br>
            </div>
            <?
            shn_or_regform_operation($error);
        }else {
            shn_or_regform_org($error=false);
        }
    }
    
}

//author ravindra
// register a volunteer
function shn_or_reg_vol(){
	shn_or_regform_vol();
}

//author ravindra
// register a volunteer
function shn_or_reg_vol_cr(){
    $error=false;
    if (is_null($_POST{"name"})){
        $error=true;
        add_error(SHN_ERR_PERSON_NAME_INCOMPLETE);
    }else {    
        $name=$_POST{"name"};
    }
    $dob=$_POST{"dob_yyyy"}."-".$_POST{"dob_mm"}."-".$_POST{"dob_dd"};
    /*
    if (!shn_valid_date($_POST{"dob"})){
        $error=true;
        add_error(SHN_ERR_DOB_INCORRECT);
    }else {    
        $dob=$_POST{"dob"};
    }
    */

$male=trim($_POST{"sex"});
$job=$_POST{"job"};
$nic=trim($_POST{"nic"});
$pas=trim($_POST{"pas"});
$dln=trim($_POST{"dln"});

//if ('m'==trim($_POST{"sex"})){
//$male=true;
//} else{
//$male=false;
//}

    if (is_null($_POST{"sector"})){
        $error=true;
        add_error(SHN_ERR_OR_SECTOR_INCOMPLETE);
    }else {    
        $sector=$_POST{"sector"};
    }
    if (is_null($_POST{"bsd_country"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=$_POST{"bsd_country"};
    }
    if (is_null($_POST{"bsd_village"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"bsd_village"};
    }
    $contact_name=$_POST{"contact_name"};
    $contact_address=$_POST{"contact_add"};
    $contact_phone=$_POST{"contact_phone"};
    $contact_fax=$_POST{"contact_fax"};
    $contact_mail=$_POST{"contact_mail"};



    global $global;
    $db=$global['db'];
   
    $pid = $db->GenID('person_seq',1);
    $q="select p_uuid from person_uuid where p_uuid='{$pid}'";
    $res=$db->Execute($q);
    if(!$res->EOF){
        $error=true;
        add_error(SHN_ERR_OR_PERSON_EXISTS);
    }
    if(!$error){
        $q="insert into person_uuid(p_uuid,full_name) values($pid,'{$name}')";
        $res=$db->Execute($q);
	
	$q="insert into person_details(p_uuid,birth_date,opt_country,opt_gender,occupation) values($pid,'{$dob}','{$bsd_country}','{$male}','{$job}')";
        $res=$db->Execute($q);
	$q="insert into person_status(p_uuid,isReliefWorker) values($pid,1)";
        $res=$db->Execute($q);

	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$nic}','nic')";
   $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$pas}','pas')";
        $res=$db->Execute($q);
	$q="insert into identity_to_person(p_uuid,serial,opt_id_type) values($pid,'{$dln}','dln')";
        $res=$db->Execute($q);

        $i=0;
        while($i<count($sector)){
            $q="insert into sector(pgoc_uuid,opt_sector) values($pid,'{$sector[$i]}')";
           $res=$db->Execute($q);
           $i=$i+1;
        }
    }

    $q="insert into location_details(poc_uuid,location_id,opt_person_loc_type,address) values($pid,'{$bsd_village}','hom','{$contact_address}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'curr','{$contact_phone}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'fax','{$contact_fax}')";
    $res=$db->Execute($q);
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($pid,'email','{$contact_mail}')";
    $res=$db->Execute($q);
    if($error!=true){
?>
    <div id="result_msg">
       <?php echo $name?> was succesfully registered
    </div>
    </br>
<?php
    }
    shn_or_regform_vol($error);
}

//author ravindra
// view all OR
function shn_or_view_org()
{
if(NULL == $_REQUEST['id']){
    shn_or_viewform_allorg();
}else{
    shn_or_viewform_org($_REQUEST['id']);
}
}


//author ravindra
// view all Volunteers
function shn_or_view_vol()
{
if(NULL == $_REQUEST['id']){
    shn_or_viewform_allvol();
}else{
    shn_or_viewform_vol($_REQUEST['id']);
}
}
//author ravindra
// view all orgs group by sector
function shn_or_report_village()
{
    $district=$_GET["id"];
    shn_or_village($district);
}

//author ravindra
// view all orgs group by sector
function shn_or_report_district()
{
    $prov=$_GET["id"];
    shn_or_district($prov);
}

//author ravindra
// view all orgs group by sector
function shn_or_report_province()
{
    shn_or_province();
}

//author ravindra
// view all orgs group by sector
function shn_or_org_sector()
{
    shn_or_report_org_sector();
}


//author ravindra,pradeeper,chathra
// default page, welcome page 
function shn_or_default()
{
       include_once ("home.inc");



}
function shn_or_search()
{
       
       shn_or_form_search();
}
function shn_or_search_cr(){
 $VARCHAR=100;
global $global;
$db=$global["db"];
 list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"sector"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"sector"}):array(true,NULL);

if (is_null($_POST{"bsd_country"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=trim($_POST{"bsd_country"});
    }

if (is_null($_POST{"bsd_province"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_province=trim($_POST{"bsd_province"});
    }

if (is_null($_POST{"bsd_district"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_district=trim($_POST{"bsd_district"});
    }
    if (is_null($_POST{"bsd_village"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"bsd_village"});
    }
switch ($_POST{"loc_option"}){
	case "province":
	break;
	case "district":
	break;
	case "village":
	$loc="($bsd_village)";
	break;

}

$i=0;
$org=array();
//$loc=array(10,13);
var_dump($loc);
while($i<count($sector)){
            $q="select o_uuid from location_details,sector,org_main where location_details.location_id in $loc and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector[$i]}' and org_main.o_uuid=sector.pgoc_uuid";
echo $q;
            $res_org=$db->Execute($q);
while(!$res_org==NULL && !$res_org->EOF){
            array_push($org,$res_org->fields[0]);
            
            $res_org->MoveNext();
        }
$i=$i+1;
}

?>

<div id ="result">
    <h2>Search Result</h2>
    <table>
        <thead>
            <td>Organization Name</td>
            <td>Services Offered</td>
            <td>Organization Type</td>
            <td>Country of Origin</td>
            <td>Contact Address</td>
            <td>Contact Number</td>
            <td>Contact Email</td>
            <td>Man Power</td>
            <td>Facilities</td>
        </thead>
        <tbody>
<?php
$i=0;

$org=array_unique($org);
$i=0;

while($i<count($org)){
           
            _shn_display_org($org[$i],false);
         
$i=$i+1;
}
?>
</tbody>
  </table>
</div>

<?php
}
?>
