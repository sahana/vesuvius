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
* @package    moduleAPI
* @subpackage menu 
* @author     http://www.linux.lk/~chamindra
* @author     Greg Miernicki <g@miernicki.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


/**
 * shn_mainmenuitem 
 * 
 * @param mixed $action 
 * @param mixed $desc 
 * @param mixed $module 
 * @access public
 * @return void
 */
function shn_mainmenuitem($action, $desc, $module = null ) {
	global $global;
	if (null==$module) {
		$module = $global['module'];
	}

	// if this menu item is the current module displayed, add a css class to allow proper styling
	if ($_REQUEST['mod'] == $module) {
		?><li class="currentMainMenuItem"><a href="index.php?mod=<?php echo $module;?>&amp;act=<?php echo $action;?>"><?php echo $desc;?></a></li><?php

	// else display menu item normally
	} else {
		?><li><a href="index.php?mod=<?php echo $module;?>&amp;act=<?php echo $action;?>"><?php echo $desc;?></a></li><?php
	}
}



/**
 * shn_mainmenuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
function shn_mainmenuopen($desc) {   
	?>
	<div id="menuwrap">
		<h2><?php echo _t('Modules')?></h2>
		<ul id="menu">
	<?php
}



/**
 * shn_mainmenuclose 
 * 
 * @access public
 * @return void
 */
function shn_mainmenuclose() {   
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
function shn_mod_menuitem($action, $desc, $module = null ) { 
	global $global;
	if ( null == $module ) { 
		$module = $global['module'];
	}
	shn_breadcrumb_set_nicename($module, $action, $desc);

	// if this mod menu item is the current action, add a css class to allow proper styling
	if ($_SERVER['REQUEST_URI'] == "/index.php?mod=".$module."&act=".$action) {
		echo "<li class=\"currentModMenuItem\"><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";

	// else display menu item normally
	} else {
		echo "<li><a href=\"index.php?mod=".$module."&amp;act=".$action."\">".$desc."</a></li>";
	}
}



/**
 * shn_mod_menuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
function shn_mod_menuopen($desc)  {   
	?>
	<div id="modmenuwrap"> 
	<h2><?php echo $desc?></h2>
	<ul id="modmenu">
	<?php
}



/**
 * shn_mod_menuclose 
 * 
 * @access public
 * @return void
 */
function shn_mod_menuclose() {   
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
function shn_sub_mod_menuitem($action, $desc, $module = null ) { 
	global $global;
	if ( null == $module ) {
		$module = $global['module'];
	}
	shn_breadcrumb_set_nicename($module, $action, $desc);
	?><li><a href="index.php?mod=<?php echo $module;?>&amp;act=<?php echo $action;?>"><?php echo $desc;?></a></li><?php
	global $sub_menu_id;
	$sub_menu_id=$action;
}



/**
 * shn_sub_mod_menuopen 
 * 
 * @param mixed $desc 
 * @access public
 * @return void
 */
$sub_menu_id='sub';
function shn_sub_mod_menuopen($desc) {
	global $sub_menu_id;
	static $num=0;
	$id='sub'.$sub_menu_id.$num;
	$num++;
	?><li><a href="#" onclick="expand('<?php echo $id;?>',this);" class="smopen"><?php echo $desc;?></a><ul id="<?php echo $id;?>"><?php
}



/**
 * shn_sub_mod_menuclose 
 * 
 * @access public
 * @return void
 */
function shn_sub_mod_menuclose() {   
	?>
	</ul>
	</li> <!-- /modmenuwrap -->
	<?php
}



function shn_adm_menuopen($desc=null) {   
	?>
	<div id="submenu_v">
	<?php
}



function shn_adm_menuclose() {   
	?>
	</div> 
	<?php
}



function shn_adm_menuitem($action, $desc, $module = null ) { 
	global $global;
	if ( null == $module ) $module = $global['module'];
	shn_breadcrumb_set_nicename($module, $action, $desc);
	?><a <?php echo ($global['action']==$action?'class="selected" ':'');?> href="index.php?mod=<?php echo $module?>&amp;act=<?php echo $action?>"><?php echo $desc?></a><?php
}



// BREAD CRUMB functions

// set a nicename
function shn_breadcrumb_set_nicename($module, $action, $desc) {
	global $global;
	$global['shn_q_mod='.$module.'&act='.$action.'_nicename'] = $desc;
}



function shn_breadcrumb_get_nicename($module, $action) {
	global $global;
	return $global['shn_q_mod='.$module.'&act='.$action.'_nicename'];
}



// pushes a link onto the breadcrumb stack
function shn_breadcrumb_push($nicename, $action = null, $module = null) {
	global $global;

	if ( null == $module ) $module = $global['module'];
	if ( null == $action ) $action = $global['action'];

	if ( !array_key_exists('shn_breadcrumb', $_SESSION ))
		$_SESSION['shn_breadcrumb'] = array();

	$last_crumb = end($_SESSION['shn_breadcrumb']); 
	$last_module = $last_crumb[2]; 

	// create the query string. $action might have more appended
	$query_string = 'mod='.$module.'&amp;act='.$action;
	
	// only push the breadcrumb if it is not the home page and
	// if it is not the immidiately previous page in the history
	if ( $last_module == $module) { 
		array_pop($_SESSION['shn_breadcrumb']);
	}
	array_push($_SESSION['shn_breadcrumb'], array($nicename, $query_string, $module));

	if (count($_SESSION['shn_breadcrumb']) > 3)
		array_shift($_SESSION['shn_breadcrumb']);
}



// pops a breadcrumb item off the top of the stack
function shn_breadcrumb_pop() {
    return array_pop($_SESSION['shn_breadcrumb']);
}



// displays the breadcrumb within the navigation section
function shn_breadcrumb_display() {
	global $conf;
	$current_mod = '';
	$breadcrumb = '';


	// create the breadcrumb array if it does not exist 
	if ( !array_key_exists('shn_breadcrumb', $_SESSION )) {
		$_SESSION['shn_breadcrumb'] = array();
	}

	// clear the breadcrumb array if the user has logged out
	if ( $_SESSION['logged_in'] != true ) {
		$_SESSION['shn_breadcrumb'] = array();
	}

	//foreach ($_SESSION['shn_breadcrumb'] as $i ) {
	for ($j=0 ; $j < sizeof($_SESSION['shn_breadcrumb'])-1 ; $j++) { 

		$i = $_SESSION['shn_breadcrumb'][$j];

		// check if this is an admin function, else report it under administration
		$pos = strpos($i[1], 'act=adm_');
		if ( false === $pos ) {
		$module_name = $conf['mod_'.$i[2].'_name'];
		} else {
		$module_name = $conf['mod_admin_name'];
		}

		// only prefix the module name if the next item is different
		if ($current_mod != $module_name) {
		$breadcrumb .= '<a href="?mod='.$i[2].'"><b>'.$module_name.'</b></a>: ';
		$current_mod = $module_name;
		}
		$breadcrumb .= '<a href="?'.$i[1].'">'.$i[0].'</a> > ';

	}
	
	// Display the breadcrumb
	if ( $breadcrumb != '' ) {
		// @TODO: Remove the space hack and make this a proper list for CSS
		echo '<div id="breadcrumbs">&nbsp;&nbsp;&nbsp;&nbsp;<b>';
		echo _t('Switch back to').' </b>'.$breadcrumb.'</div>';
	}
}



/**
 * Open tab menu
 * 
 * @access public
 * @return void
 */
function shn_tabmenu_open() {
	?>
	<ul id="tabmenu">
	<?php
}



/**
 * Close tab menu
 * 
 * @access public
 * @return void
 */
function shn_tabmenu_close() {
	?>
	</ul>
	<?php
}



/**
 * Add an tab menu item 
 * 
 * @param mixed $action
 * @param mixed $desc 
 * @param mixed $module
 * @access public
 * @return void
 */
function shn_tabmenu_item($action, $desc, $module = null) {
	global $global;
	if ( null == $module ) $module = $global['module'];
	static $count=0;
	$active=($count == $_REQUEST['tabid'])?"id='active'":'';
	$tabid='&tabid='.$count++;
	shn_breadcrumb_set_nicename($module, $action, $desc);
	?><li <?php echo $active ?>><a href="index.php?mod=<?php echo $module?>&amp;act=<?php echo $action.$tabid?>"><span><?php echo $desc?></span></a></li><?php
}
