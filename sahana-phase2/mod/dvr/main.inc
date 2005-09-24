<?php


include $global['approot']."/inc/lib_modules.inc";

function shn_dvr_mainmenu() 
{
?>
<div id="nav_bar">
 <div id="menu">
  <div id="menu_header"></div>
   <h3 class="menu_title">DVR Menu</h3>
   <ul>
    <li><a href="index.php?mod=dvr&act=view">view</a></li>
    <li><a href="index.php?mod=dvr&act=home">default</a></li>
   </ul>
  <div id="menu_header"></div>
   <h3 class="menu_title">Modules</h3>
    <ul> 
    <?php 
    // display the list of modules on the menu bar
    $module_list = shn_get_module_names();

    foreach ($module_list as $i) {  

        echo '<li><a href="index.php?mod='.$i.'">'.$i.'</a></li>';
    }
    ?>

    </ul>
 </div>
</div>
	
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

