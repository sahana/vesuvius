<?php


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
                <li><a href="index.php?mod=<?=$module?>&act=add_branch">Add a Branch</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=edit_branch">Edit an Branch</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=reports">Reports</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=admin">Admin</a></li>
            </ul>
        </dd>
       </dt>
    <?php 
} 
	
function shn_or_add_branch()
{?>
    <p><b> OR add branch </b></p> 
    <p> You made a call to the add branch action of the OR module</p>
<?php
}

function shn_or_reports()
{

}

function shn_or_default()
{
?>
    <p><b> Welcome to the OR  home </b></p>
    <p> This is the default view</p>


<?php
}

?>


