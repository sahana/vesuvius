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
    $global['shn_'.$module.'_'.$action.'_nicename'] = $desc;
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
    $global['shn_'.$module.'_'.$action.'_nicename'] = $desc;
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
	<li><a href="#" onClick="expand('<?=$desc?>',this);" class="smopen"><?=$desc?></a>
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
    $global['shn_'.$module.'_'.$action.'_nicename'] = $desc;
?>
    <a <?=($global['action']==$action?'class="selected" ':'');?> href="index.php?mod=<?=$module?>&act=<?=$action?>"><?=$desc?></a>
<?php
}

// BREAD CRUMB functions

// pushes a link onto the breadcrumb stack
function shn_breadcrumb_push($nicename, $action = null, $module = null)
{
    global $global;
    if ( null == $module ) $module = $global['module'];
    if ( null == $action ) $action = $global['action'];

    if ( !array_key_exists('shn_breadcrumb', $_SESSION ))
        $_SESSION['shn_breadcrumb'] = array();

    array_push($_SESSION['shn_breadcrumb'], array($nicename, $action, $module));

    if (count($_SESSION['shn_breadcrumb']) > 3)
        array_shift($_SESSION['shn_breadcrumb']);
}

// pops a breadcrumb item off the top of the stack
function shn_breadcrumb_pop()
{
    return array_pop($_SESSION['shn_breadcrumb']);
}

// displays the breadcrumb within the navigation section
function shn_breadcrumb_display()
{
    global $conf;
    $current_mod = '';

    echo '<p>';

    foreach ($_SESSION['shn_breadcrumb'] as $i ) {

        // only prefix the module name if the next item is different
        if ($current_mod != $i[2]) {
            $module_name = $conf['mod_'.$i[2].'_name'];
            echo $module_name.":";
            $current_mod = $i[2];
        }
        echo '<a href="?mod='.$i[2].'&act='.$i[1].'">'.$i[0].'</a> > ';
    }

    echo '</p>';

}
?>
