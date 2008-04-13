<?php
/**Admin Module for GIS
*
* PHP version 5
* 
* @author   	Mifan Careem <mifan@opensource.lk>
* @copyright  	Lanka Software Foundation - http://www.opensource.lk
* @package	Sahana - http://sahana.lk/    	
* @library 	GIS
* @version	$id$;
* @license  	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_errors.inc');


/**
 * Main default GIS configuration settings
 * Mostly common across plugins
 * @todo: handle a topsy-turvy world!!
 * @todo: provide a map based center input selection before the revolution comes >;)
 * @todo: cite source URI for lat-lon help content
 */
function shn_admin_gis_main_settings()
{
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_form.inc');
?>
	<h2><?php echo _t("GIS Defaults Configuration");?></h2>
<?php
	shn_form_fopen('gis_main_defaults',null,array('req_message'=>false));
	shn_form_fsopen(_t('INFO'));
?>
	<ul>
		<li><?php echo _t("Visual Maps are displayed within certain modules in Sahana");?> </li>
		<li><?php echo _t("GIS Maps in Sahana can be set to display a default region");?> </li>
		<li><?php echo _t("In order to set the map display for a particular region, you should know the Latitude and the Longitude of that region");?></li>
    	<li><?php echo _t("If these values are known, you can set them below:");?> </li>
	</ul>
<?php
	shn_form_fsclose();
	shn_form_fsopen(_t("Default Center Coordinates"));
	$lat_help=_t("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
	$lon_help=_t("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
	shn_form_text(_t("Center Latitude"),"y_center",null,array("value"=>$conf['gis_center_y'],"help"=>$lat_help));
	shn_form_text(_t("Center Longitude "),"x_center",null,array("value"=>$conf['gis_center_x'],"help"=>$lon_help));
	shn_form_fsclose();
	shn_form_submit(_t('Save As Defaults'));
	shn_form_close();
}

/**
 * Include relevant plugin
 * Handle file check for plugin availability and kidnapped plugins
 */
function shn_admin_gis_plugin_include_file($plugin,$file='admin.inc')
{
	global $conf;
	global $global;
	
	if(file_exists($global['approot'].'/inc/lib_gis/plugins/'.$plugin.'/'.$file)){
		include_once $global['approot'].'/inc/lib_gis/plugins/'.$plugin.'/'.$file;
		return true;		
	}
	else{
		//File doesn't exits: Missing in Action, literally
		add_warning(_t('The requested plugin has been accidentally removed. Please notify the administrator'));
		return false;
	}
}

/**
 * Plugin Front-controller
 * Mini front controller to handle dynamically added plugins within GIS
 * @todo: does a front-controller within a front-controller become a rear controller? :)
 * 
 */
function shn_admin_gis_plugin_controller()
{
	switch($_REQUEST['seq']){
		case 'view':
			shn_admin_gis_show_mod_menu();
			shn_admin_gis_plugin_include_file($_REQUEST['plugin'],'admin.inc');
			shn_plugin_default();
			break;
		case 'commit':
			shn_admin_gis_plugin_include_file($_REQUEST['plugin'],'admin.inc');
			shn_plugin_commit();
			//Do not break
		default:
			shn_admin_gis_show_mod_menu();
			echo "<h2>"._t("GIS Admin Page")."</h2>";
			_shn_admin_gis_show_mods_select();
			break;
	}
}



/**
 * Find and show GIS plugin configuration links at top
 * Auto-detects plugins 
 * @access public
 * @return void
 */
function shn_admin_gis_show_mod_menu()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	
	$gis_plugins_dir=$global['approot'].'/inc/lib_gis/plugins/';
	$dir = opendir($gis_plugins_dir);
?>
	<div id="submenu_v">
		<a href="index.php?mod=admin&act=gis_plugin"><?=_t("Plugin Management")?></a>
<?php
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include_once ($global['approot'].'/inc/lib_gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
?>
		<a href="index.php?mod=admin&act=gis_plugin&seq=view&plugin=<?=$file?>"><?=_t($name)?></a>
<?php
		}
	}
?>
	</div><!--/div id=submenu_v-->
<?php
}


/**
 * Show radio button selection of available GIS plugins
 * Enter Selected values 
 * @access private
 * @return void  
 */
function _shn_admin_gis_show_mods_select()
{
	global $global;
	global $conf;
	$db=$global['db'];
	
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	shn_form_fopen('gis_plugin_default',null,array('req'=>false));
	shn_form_fsopen(_t('INFO'));
?>
	<ul>
		<li><?php echo _t("Sahana supports a modular GIS plugin architecture ");?> </li>
		<li><?php echo _t("You can select which GIS plugin to use as your default GIS");?></li>
	    <li><?php echo _t("Select the default GIS plugin from the detected plugins below:");?> </li>
	    <li><?php echo _t("For more information on adding custom plugins, refer to the documentation within the inc/lib_gis subdirectory");?> </li>
	</ul>
<?php
	
	$gis_plugins_dir=$global['approot'].'/inc/lib_gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include($global['approot'].'/mod/gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			$options_array[$file] = $name;			
		}
	}
	shn_form_fsclose();
	shn_form_fsopen(_t("Detected GIS Module Plugins"));
	shn_form_radio($options_array,_t("Select GIS Module: "),"mod_gis",null,((isset($mod_name))?array("value"=>$mod_name):null));
	shn_form_fsclose();
	shn_form_submit(_t("Done"));
	shn_form_fclose();	
}


/**
 * Commit default Northing/Easting values
 * @access private
 */
function shn_admin_gis_commit_main()
{
	global $global;
	$db = $global['db'];                  
	if(!null==$_POST['x_center']){
		$query = "SELECT * FROM config WHERE confkey='gis_center_x' AND module_id='admin'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q = "UPDATE config SET value = '{$_POST['x_center']}' WHERE module_id = 'admin' AND confkey = 'gis_center_x'";       
			$db->Execute($q);
		}
		else{
			$insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_center_x','{$_POST['x_center']}')";
			$db->Execute($insert);
		}
	}
	if(!null==$_POST['y_center']){
		$query = "SELECT * FROM config WHERE confkey='gis_center_y' AND module_id='admin'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$r="UPDATE config SET value = '{$_POST['y_center']}' WHERE module_id = 'admin' AND confkey = 'gis_center_y'";       
			$db->Execute($r);
		}
		else{
			$insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_center_y','{$_POST['y_center']}')";
			$db->Execute($insert);
		}
	}
}

function shn_admin_gis_plugin_default_commit()
{
	global $global;
	$db = $global['db'];
	if(!null==$_POST['mod_gis']){
		$query = "SELECT * FROM config WHERE confkey='gis_dflt' AND module_id='admin'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q = "UPDATE config SET value  = '{$_POST['mod_gis']}' WHERE module_id = 'admin' AND confkey='gis_dflt'";
			$db->Execute($q);
		}
		else{
			$insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_dflt','{$_POST['mod_gis']}')";
			$db->Execute($insert);
		}
		
	}
}


						
?>
