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
$bsd_country=$_POST{"bsd_country"};
echo "reg_or_create";
$or_sector=$_POST{"or_sector"};
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
function shn_or_reg_vol()
{?> 
    <center><h3><b>Organization Registry</p><br></b></h3></center>
<?php

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
