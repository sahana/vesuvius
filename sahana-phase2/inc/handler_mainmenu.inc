<?php  
/**
* This handler displays the mainmenu dynamically based on action  
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";

?>
        <p><a href="#content" class="mini">Skip Navigation</a></p>
        <h2>Sahana Main</h2>
        <dl>
     <?php 
    // display the list of modules on the menu bar
    $module_list = shn_get_module_names();

    foreach ($module_list as $i) {  ?>

       <dt><a href="index.php?mod=<?=$i?>"><?=$i?></a></dt>
        <dd>
            <ul>
                <li><a href="index.php?mod=<?=$i?>&act=default">Default</a></li>
                <li><a href="index.php?mod=<?=$i?>&act=view">View</a></li>
                <li><a href="index.php?mod=<?=$i?>&act=admin">Admin</a></li>
            </ul>
        </dd>
       </dt>
    <?php 
    } ?>
	

