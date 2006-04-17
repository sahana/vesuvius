<?php  
/**
* Template helpers for generating menus
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

// Main menu template helper
/**
 * shn_mainmenuitem 
 * 
 * @param mixed $action 
 * @param mixed $desc 
 * @param mixed $module 
 * @access public
 * @return void
 */
function shn_mainmenuitem($action, $desc, $module = null ) 
{ 
    global $global;
    if ( null == $module ) $module = $global['module'];
?>
    <li><a href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a></li>
<?php
}


/**
 * shn_mainmenuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
function shn_mainmenuopen($desc ) 
{   
?>
    <div id="menuwrap">
        <h2>Sahana Main</h2>
        <ul id="menu">
<?php
}

/**
 * shn_mainmenuclose 
 * 
 * @access public
 * @return void
 */
function shn_mainmenuclose() 
{   
?>
        </ul>
    </div> <!-- /modmenuwrap -->
<?php
}

/**
 * shn_mod_menuitem 
 * 
 * @param mixed $action 
 * @param mixed $desc 
 * @param mixed $module 
 * @access public
 * @return void
 */
function shn_mod_menuitem($action, $desc, $module = null ) 
{ 
    global $global;
    if ( null == $module ) $module = $global['module'];
?>
    <li><a href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a></li>
<?php
}


/**
 * shn_mod_menuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
function shn_mod_menuopen($desc ) 
{   
?>
    <div id="modmenuwrap"> 
    <h2><?=$desc?></h2>
    <ul id="modmenu">
<?php
}

/**
 * shn_mod_menuclose 
 * 
 * @access public
 * @return void
 */
function shn_mod_menuclose() 
{   
?>
    </ul>
    </div> <!-- /modmenuwrap -->
<?php
}

/**
 * shn_sub_mod_menuitem 
 * 
 * @param mixed $action 
 * @param mixed $desc 
 * @param mixed $module 
 * @access public
 * @return void
 */
function shn_sub_mod_menuitem($action, $desc, $module = null )
{ 
    global $global;
    if ( null == $module ) $module = $global['module'];
?>
		<li><a href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a></li>
<?php
}

/**
 * shn_sub_mod_menuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
function shn_sub_mod_menuopen($desc) 
{   
?>
	<li><a href="#" onClick="expand('<?=$desc?>');"><?=$desc?></a>
		<ul id="<?=$desc?>">
<?php
}

/**
 * shn_sub_mod_menuclose 
 * 
 * @access public
 * @return void
 */
function shn_sub_mod_menuclose() 
{   
?>
		</ul>
	</li> <!-- /modmenuwrap -->
<?php
}

function shn_adm_menuopen($desc=null) 
{   
?>
    <div id="submenu_v">
<?php
}

function shn_adm_menuclose() 
{   
?>
    </div> 
<?php
}

function shn_adm_menuitem($action, $desc, $module = null ) 
{ 
    global $global;
    if ( null == $module ) $module = $global['module'];
?>
    <a <?=($global['action']==$action?'class="selected" ':'');?> href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a>
<?php
}

?>
