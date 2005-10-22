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

function shn_or_mainmenu() 
{
    global $global;
    $module = $global['module'];
    include $global['approot']."/inc/handler_mainmenu.inc";
?>
    
   <div id="modmenuwrap"> 
        <h2>OR Module Actions</h2>
            <ul id="modmenu">
                <li><a href="index.php?mod=<?=$module?>&act=reg_org">Register a ORG</a></li>
<!--                <li><a href="index.php?mod=<?=$module?>&act=add_user">Register a user</a></li>
-->                <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Register as a Volunteer</a></li>
               
               <li><a href="index.php?mod=<?=$module?>&act=view_all_org">View all ORG</a></li>
<!--
                <li><a href="index.php?mod=<?=$module?>&act=reports">Reports</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=mng_con">Management Console</a></li>
-->                
                <!--The following part of sub menus should be visible based on the ACL information, by default it will be invisible.*/-->
<!--
                 	<ul>
                		<li><a href="index.php?mod=<?=$module?>&act=add_branch">Add a Branch</a></li>
                		<li><a href="index.php?mod=<?=$module?>&act=edit_branch">Edit Branch Information</a></li>
                		<li><a href="index.php?mod=<?=$module?>&act=add_branch">Add a User</a></li>
                	</ul>
-->
            </ul>
    </div> <!-- /modmainwrap -->
<?php 
} 

// register a OR
function shn_or_reg_org()
{
shn_or_org_reg();
}

function shn_or_reg_org_cr()
{
$org_name=$_POST{"org_name"};
$org_type=$_POST{"org_type"};
$org_sector=$_POST{"org_sector"};
//$bsd_country=$_POST{"bsd_country"};
echo "reg_or_create";
//$bsd_province=$_POST{"bsd_province"};
//$bsd_district=$_POST{"bsd_district"};
$bsd_village=$_POST{"bsd_village"};
$reg_no=$_POST{"reg_no"};

$contact_name=$_POST{"contact_name"};
$contact_add=$_POST{"contact_add"};
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
$q="insert into org_main(id,parent_id,name,or_type,reg_no,man_power,resources,privacy)values($org_id,0,'{$org_name}','{$org_type}','{$reg_no}','{$man_power}','{$resources}',$chk_avail)";
$res=$db->Execute($q);

$i=0;
var_dump($org_sector);
while($i<count($org_sector)){
    $q="insert into org_sector(org_id,sector_id) values($org_id,$org_sector[$i])";
    $res=$db->Execute($q);
    var_dump($q);
    $i=$i+1;
}
if($res==false){
    return false;
}else {
    shn_or_branch_reg();
}
/*
$i=0;
echo "count".count($or_sector);
while($i<count($or_sector)){
echo $or_sector[$i];
$i=$i+1;
*/




//Save to database
//echo "<h2><b>" . _("Organization Registration") . "</b></h2>";

    // Start OR registration form
  //  $header = array (
    //                    array('method'=>"POST",'action'=>"index.php?mod=or&act=reg_org_cr")
//                    );
                    
    //shn_show_form($header);

}

function shn_or_reg_branch(){
}

function shn_or_reg_branch_cr(){
}

// register a OR
function shn_or_add_user()
{?> 
    <center><h3><b>Organization Registry</p><br></b></h3></center>
<?php
include_once ("handler_or_usr_add.inc"); // call form generator

}

// register a volunteer
function shn_or_reg_vol(){
shn_or_vol_reg();
}

// view all OR
function shn_or_view_all_org()
{?>
    <center><h3><b>Organization Registry</p><br></b></h3></center>
    <p>view all OR </p> 
<?php
}

// reports
function shn_or_reports()
{
?>
    <center><h3><b>Organization Regisry</p><br></b></h3></center>
    <p>Reports</p>
<?php

}

// default page, welcome page ;-)
function shn_or_default()
{
?>
    <center><h3><b> Welcome to Organization Registry</p><br></b></h3></center>
    <?php
       include_once ("home.inc");



}

// OR admin console
function shn_or_mng_con()
{
?>
    <center><h3><b>Organization Regisry</p><br></b></h3></center>
    <p> Admin</p>


<?php
	include_once ("handler_or_mng_con.inc");
}
?>
