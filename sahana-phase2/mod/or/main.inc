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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/


include_once $global['approot']."/inc/lib_modules.inc";

function shn_or_mainmenu() 
{
    global $global;
    $module = $global['module'];
    include $global['approot']."/inc/handler_mainmenu.inc";
?>
    
        <h2>OR Module Actions</h2>
        <dl>
       <dt><a href="index.php?mod="></a></dt>
        <dd>
            <ul>
                <li><a href="index.php?mod=<?=$module?>&act=reg_org">Register a ORG</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=add_user">Register a user</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=reg_vol">Register as a Volunteer</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=view_all_org">View all ORG</a></li>
					 <li><a href="index.php?mod=<?=$module?>&act=reports">Reports</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=mng_con">Management Console</a></li>
             
            </ul>
        </dd>
       </dt>
    <?php 
} 

// register a OR
function shn_or_reg_org()
{?> 
    <center><h3><b>Organization Registry</p><br></b></h3></center>
<?php
include_once ("handler_or_registration.inc"); // call form generator

}

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
include_once ("handler_or_vol_registration.inc"); // call form generator

}

// view all OR
function shn_or_view_all_org()
{?>
    <center><h3><b>Organization Registry</p><br></b></h3></center>
    <p>view all OR </p> 
<?php
}

// add branch
function shn_or_add_branch()
{?>
    <center><h3><b>Organization Registry</p><br></b></h3></center>
   <?php
include_once ("handler_or_brn_add.inc"); // call form generator 
}

// edit branch
function shn_or_edit_branch()
{?>
    <center><h3><b>Organization Regisry</p><br></b></h3></center>
    <p>edit branch </p> <?php
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


