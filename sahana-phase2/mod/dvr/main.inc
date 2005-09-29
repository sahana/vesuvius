<?php


include_once $global['approot']."/inc/lib_modules.inc";

function shn_dvr_mainmenu() 
{
    global $global;
    $module = $global['module'];
    include $global['approot']."/inc/handler_mainmenu.inc";
?>
    
        <h2>DVR Module Actions</h2>
        <dl>
       <dt><a href="index.php?mod="></a></dt>
        <dd>
            <ul>
                <li><a href="index.php?mod=<?=$module?>&act=default">Add Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=view">Find Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=admin">Edit Person</a></li>
                <li><a href="index.php?mod=<?=$module?>&act=admin">Statistics</a></li>
            </ul>
        </dd>
       </dt>
    <?php 
} 
	
function shn_dvr_view()
{?>
    <p><b> DVR View Action </b></p> 
    <p> You made a call to the view action of the DVR module</p>
<?php
}

function shn_dvr_default()
{
?>
    <p><b> Welcome to the DVR home </b></p>
    <p> This is the default view</p>


<?php
}
?>

