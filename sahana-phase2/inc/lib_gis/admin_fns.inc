<?php

/**Admin Module for GIS
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@opensource.lk>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @library      GIS
* @version      $Id: admin_fns.inc,v 1.17 2009-08-22 17:17:25 ravithb Exp $;
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

/**
 * Main default GIS configuration settings
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
    shn_form_fsopen(_t("Default Plugin"));
?>
	<ul>
	 <li><?php echo _t("Sahana supports a modular GIS plugin architecture ");?> </li>
         <li><?php echo _t("Select the default plugin from those detected below:");?> </li>
	</ul>
<?php
	$gis_plugins_dir=$global['approot'].'/inc/lib_gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include($global['approot'].'/inc/lib_gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			$options_array[$file] = $name;
		}
	}
	$mod_name = $conf['gis_dflt'];
    shn_form_radio($options_array,_t("Select GIS Plugin: "),"mod_gis",null,((isset($mod_name))?array("value"=>$mod_name):null));
    shn_form_fsclose();
	shn_form_fsopen(_t("Default Map Location"));
?>
	<ul>
	 <li><?php echo _t("Visual Maps are displayed within certain modules in Sahana");?> </li>
	 <li><?php echo _t("In order to set the map to display a default region, you can set this below:");?></li>
	</ul>
<?php
	$lat_help=_t("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
	$lon_help=_t("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
	$zoom_help=_t("How much detail is seen. A high Zoom level means lot of detail, but not a wide area. A low Zoom level means seeing a wide area, but not a high level of detail.");
	shn_form_text(_t("Center Latitude"),"y_center",null,array("value"=>$conf['gis_center_y'],"help"=>$lat_help));
	shn_form_text(_t("Center Longitude "),"x_center",null,array("value"=>$conf['gis_center_x'],"help"=>$lon_help));
	shn_form_text(_t("Zoom "),"zoom",null,array("value"=>$conf['gis_zoom'],"help"=>$zoom_help));
	shn_form_fsclose();
    
    shn_form_submit(_t('Save As Defaults'));
    shn_form_close();

    // call GIS API
	include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_gis_map_select("y_center","x_center","zoom");

}

/**
 * Google Plugin configuration settings
 * - enter host Key
 */
function shn_admin_gis_google_settings()
{
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_form.inc');
?>
	<h2><?php echo _t("Google Maps Configuration");?></h2>
<?php
	shn_form_fopen('gis_google_commit',null,array('req_message'=>false));
	shn_form_fsopen(_t("Host Key"));
?>
	<ul>
	 <li><?php echo _t("<p>The <a href='http://maps.google.com/'>GoogleMaps</a> &trade; mapping API requires Internet connectivity and a valid Google Maps key</p>");?></li>
	 <li><?php echo _t("<p>Register a google maps key for the url you host sahana in, and enter it below</p>");?></li>
	 <li><?php echo _t("<p>Register your Google Maps key at: </p> <a href='http://www.google.com/apis/maps/' target=_blank>Google Maps</a>");?></li>
	</ul>
<?php
	shn_form_text(_t("Enter Google Maps Key"),"gmap_key",'size="100"',array('value'=>$conf['gis_google_key']));
	shn_form_fsclose();
	shn_form_submit(_t('Save'));
	shn_form_close();
}

/**
 * Commit default values: Lat/Lon/Zoom/Plugin
 * @access private
 */
function shn_admin_gis_commit_main()
{
	global $global;
	$db = $global['db'];                  
	if(!null==$_POST['x_center']){
		if (shn_valid_x_coordinate($_POST['x_center'])) {
            $query = "SELECT * FROM config WHERE confkey='gis_center_x' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '{$_POST['x_center']}' WHERE module_id = 'admin' AND confkey = 'gis_center_x'";       
                $db->Execute($q);
            } else{
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_center_x','{$_POST['x_center']}')";
                $db->Execute($insert);
            }
            add_confirmation(_("Longitude saved"));
        } else {
            add_error(_("Longitude Coordinate invalid"));
        }
	}
	if(!null==$_POST['y_center']){
		if (shn_valid_y_coordinate($_POST['y_center'])) {
            $query = "SELECT * FROM config WHERE confkey='gis_center_y' AND module_id='admin'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q="UPDATE config SET value = '{$_POST['y_center']}' WHERE module_id = 'admin' AND confkey = 'gis_center_y'";       
                $db->Execute($q);
            } else {
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_center_y','{$_POST['y_center']}')";
                $db->Execute($insert);
            }
            add_confirmation(_("Latitude saved"));
        } else {
            add_error(_("Latitude Coordinate invalid"));
        }
	}
	if(!null==$_POST['zoom']){
        $query = "SELECT * FROM config WHERE confkey='gis_zoom' AND module_id='admin'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q="UPDATE config SET value = '{$_POST['zoom']}' WHERE module_id = 'admin' AND confkey = 'gis_zoom'";       
			$db->Execute($q);
		}
		else{
			$insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_zoom','{$_POST['zoom']}')";
			$db->Execute($insert);
		}
		add_confirmation(_("Zoom saved"));
	}
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
        add_confirmation(_("Plugin saved"));
	}
}
						
/**
 * Commit Google Maps plugin config: Key
 * @access private
 */
function shn_admin_gis_commit_google()
{
    global $global;
    $db = $global['db'];                  
    if(!null==$_POST['gmap_key']){
        $query = "SELECT * FROM config WHERE confkey='gis_google_key' AND module_id='admin'";
        $res = $db->Execute($query);
        if(!$res->EOF){
            $q = "UPDATE config SET value = '{$_POST['gmap_key']}' WHERE module_id = 'admin' AND confkey = 'gis_google_key'";       
            $db->Execute($q);
        }
        else{
            $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('admin','gis_google_key','{$_POST['gmap_key']}')";
            $db->Execute($insert);
        }
    }
}


//Deprecated -------


/**
 * Include relevant plugin
 * Handle file check for plugin availability and kidnapped plugins
 * Deprecated
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
 * Deprecated
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
 * Deprecated
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
		<a href="index.php?mod=admin&act=gis_plugin"><?php echo _t("Plugin Management")?></a>
<?php
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include_once ($global['approot'].'/inc/lib_gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
?>
		<a href="index.php?mod=admin&act=gis_plugin&seq=view&plugin=<?php echo $file?>"><?php echo _t($name)?></a>
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
 * Deprecated 
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
			include($global['approot'].'/inc/lib_gis/plugins/'."$file".'/conf.inc');
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


