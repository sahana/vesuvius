<?php
/**
* Sahana Messaging Module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @author   	Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage   Messaging
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_msg_adm_default()
{
	global $global;
    global $conf;
    $module = $global['module'];
    
    //Admin plugin front-controller
	
	if(isset($_REQUEST['submod']) && isset($_REQUEST['seq'])){
		global $global;
		include_once ($global['approot'].'/mod/msg/plugins/'.$_REQUEST['submod'].'/admin.inc');
		switch($_REQUEST['seq']){
			case 'commit':
						shn_plugin_commit();
						break;
		}
		shn_msg_adm_show_mod_menu();
		echo "<h2>"._("Messaging:SMS Admin Page")."</h2>";
		shn_msg_adm_show_mods();
		shn_msg_adm_find_mods();
	}
	else if(isset($_REQUEST['submod']))
	{
		global $global;
		shn_msg_adm_show_mod_menu();
		include_once ($global['approot'].'/mod/msg/plugins/'.$_REQUEST['submod'].'/admin.inc');
		shn_plugin_default();
	}
	else
	{
    	//General Messaging
    	shn_msg_adm_show_mod_menu();
		echo "<h2>"._lc($conf['mod_msg_name'])." "._("Administraion")."</h2>";
		shn_msg_adm_plugin_conf();
		
		include_once ($global['approot'].'/mod/msg/handler_admin.inc');
		shn_msg_adm_email_configuration();
		//shn_gis_adm_showform();
		//shn_msg_adm_show_mods();
		//shn_msg_adm_find_mods();
	}
}


/**
 * Find and show Messaging plugin configuration links
 * Auto-detects plugins 
 * Uses same plugin architecture as in GIS subsystem
 * @access public
 * @return void
 */
function shn_msg_adm_find_mods()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
	shn_form_fopen(adm_gis_conf,null,array('req_message'=>false));
	shn_form_fsopen(_("SMS Plugin Configuration"));
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			echo "$count.	<a href='index.php?mod=msg&act=admin&submod=$file'>"."$name"."</a><br>";
			$count++;
		}
	}
	shn_form_fsclose();
	shn_form_fclose();	
}

/**
 * Find and allow of selection of messaging plugin
 * @access public
 * @return void
 */
function shn_msg_adm_plugin_conf()
{
	global $global;
	global $conf;
	$db=$global['db'];
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	
	$query_mod="select value from config where module_id='msg' and confkey='plugin'";
	$result=$db->Execute($query_mod);
	if(!$res->EOF){
		$mod_name=$result->fields['value'];
	}
	
	
	
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			$options_array[$file] = $name;
		}
	}
	$extra_opts_form['req_message'] = 'false';
	
	shn_form_fopen(adm_commit,null,array('req_message'=>false));
	shn_form_fsopen(_("Messaging Module SMS Gateway plugins"));
?>
	<ul>
	<li><?php echo _("Sahana supports a modular messaging SMS gateway plugin architecture ");?> </li>
	<li><?php echo _("You can select which SMS gateway to use as your default");?></li>
    <li><?php echo _("Select the default SMS gateway plugin from the detected plugins below:");?> </li>
    <li><?php echo _("For more information on adding custom plugins, refer to the documentation within the mod/msg subdirectory");?> </li>
	</ul>
<?php
	shn_form_fsclose();
	shn_form_fsopen(_("Detected messaging module SMS plugins"));
	shn_form_radio($options_array,_("Select Messaging SMS plugin"),"mod_msg",null,((isset($mod_name))?array("value"=>$mod_name):null));
	shn_form_fsclose();
	shn_form_submit(_("Done"));
	shn_form_fclose();	
}

/**
 * Find and show message plugin configuration links at top
 * Auto-detects plugins 
 * @access public
 * @return void
 */
function shn_msg_adm_show_mod_menu()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
?>
	<div id="submenu_v">
		<a href="index.php?mod=msg&act=admin"><?php echo _("General Messaging")?></a>
<?php
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
?>
<a href="index.php?mod=msg&act=admin&submod=<?php echo $file?>"><?php echo _($name)?></a>
<?php
			$count++;
		}
	}
?>
	</div><!--/div id=submenu_v-->
<?php
}


