<?PHP

function shn_admin_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];

     // display the list of modules on the menu bar
    $module_list = shn_get_modules_with_admin();
?>
    <div id="modmenuwrap">
        <h2>Administration</h2>
          <ul id="modmenu">
            <li><a href="#">Module Config </a></li>
              <ul id="modsubmenu">

<?php foreach ($module_list as $i) {  ?>

            <li><a href="index.php?mod=<?=$i?>&act=adm_default"><?=$conf['mod_'.$i.'_name']?></a></li><?php } ?> 
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

?>

