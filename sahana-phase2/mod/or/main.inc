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
include_once ("lib_or.inc");

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
                <li><a href="#">Organizations </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=or&act=search">Search </a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=reg_org">Register</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=view_org">View and Edit</a></li>
			            <li><a href="index.php?mod=or&act=report_province">Drill down by Location</a></li>
    	                <li><a href="index.php?mod=or&act=org_sector"> Organizations by Sector</a></li>
                    </ul>
               <!--  <li><a href="#">Update </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=<?=$module?>&act=search&edit=true">Organizations</a></li>
                        <li><a href="index.php?mod=<?=$module?>&act=view_vol&edit=true">Volunteers</a></li>
                    </ul> -->
		        <li><a href="#">Volunteers </a></li>
              	    <ul id="modsubmenu">
                        <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Add</a></li>
	        	        <li><a href="index.php?mod=<?=$module?>&act=view_vol">View and Edit</a></li>
                    </ul>   
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

    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"4"});
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
    if (is_null($_POST{"org_name"})){
        $error=true;
        add_error(SHN_ERR_OR_NAME_INCOMPLETE);
    }else {    
        $org_name=$_POST{"org_name"};
    }
    
    if (is_null($_POST{"sector"})){
        $error=true;
        add_error(SHN_ERR_OR_SECTOR_INCOMPLETE);
    }else {    
        $sector=$_POST{"sector"};
    }
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"4"};
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
    $org_id = $db->GenID('org_seq',1);
    if (empty($org_id)){
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
    $q="insert into contact(pgoc_uuid,opt_contact_type,contact_value) values($org_id,'name','{$contact_name}')";
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
?>
    <div id="result_msg">
       <?php echo $org_name?> Operation was succesfully registered
    </div>
    </br>
<?php
        if($chk_branch){
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

    if (is_null($_POST{"sector"})){
        $error=true;
        add_error(SHN_ERR_OR_SECTOR_INCOMPLETE);
    }else {    
        $sector=$_POST{"sector"};
    }
    if (is_null($_POST{"1"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=$_POST{"1"};
    }
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=$_POST{"4"};
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
function shn_or_edit_org()
{
if(NULL == $_REQUEST['id']){
    ?>
    <h2> Organization Registry</h2>
<?php
    shn_or_viewform_allorg(true);
}else{
    shn_or_viewform_org($_REQUEST['id'],true);
}
}
function shn_or_view_org_submit(){
$act=$_POST{"action"};
//var_dump($_POST);
switch ($act) {
    case "edit":
        _shn_or_edit_org();
        shn_or_view_org();
        break;
    case "del":
        _shn_or_del_org();
        shn_or_view_org();
        break;
    default:
        shn_or_view_org();
        break;
}
}

//author ravindra
// view all OR
function shn_or_view_org()
{
?>
<?php
if(NULL == $_REQUEST['id']){
    ?>
    <h2> Organization Registry</h2>
<?php
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

if (is_null($_POST{"1"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_country=trim($_POST{"1"});
    }

if (is_null($_POST{"2"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_province=trim($_POST{"2"});
    }

if (is_null($_POST{"3"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_district=trim($_POST{"3"});
    }
    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"4"});
    }
$post_loc=$_POST{"loc_option"};
switch ($post_loc){
	case "2":
       $loc=shn_or_province_villages($bsd_province);
	break;
	case "3":
	   $loc=shn_or_district_villages($bsd_district);
              
    break;
	case "4":
    	$loc="($bsd_village)";
	break;

}
$loc="($loc)";
$i=0;
$org=array();


while($i<count($sector)){
            $q="select o_uuid from location_details,sector,org_main where location_details.location_id in $loc and location_details.poc_uuid=sector.pgoc_uuid and sector.opt_sector='{$sector[$i]}' and org_main.o_uuid=sector.pgoc_uuid";

            $res_org=$db->Execute($q);
while(!$res_org==NULL && !$res_org->EOF){
            array_push($org,$res_org->fields[0]);
            
            $res_org->MoveNext();
        }
$i=$i+1;
}

?>

    <h1 align="center">Search Result</h1>
	
<div id ="result">
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
           
            _shn_display_org($org[$i],false,true);
         
$i=$i+1;
}
?>
</tbody>
  </table>
</div>

<?php
}
?>
