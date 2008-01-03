<?php

/* $Id: admin_bk.inc,v 1.3 2008-01-03 10:21:26 isurunishan Exp $ */

/* $Id: admin_bk.inc,v 1.3 2008-01-03 10:21:26 isurunishan Exp $ */


/**Admin Module for GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    admin
* @subpackage gis
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_errors.inc');


function shn_gis_adm_default()
{
	global $conf;
	if(isset($_REQUEST['submod']) && isset($_REQUEST['seq'])){
		global $global;
		include_once ($global['approot'].'/mod/gis/plugins/'.$_REQUEST['submod'].'/admin.inc');
		switch($_REQUEST['seq']){
			case 'commit':
									shn_plugin_commit();
									break;
		}
		shn_gis_adm_show_mod_menu();
		echo "<h2>"._("GIS / Mapping Admin Page")."</h2>";
		//shn_gis_adm_showform();
		shn_gis_adm_show_mods();
		shn_gis_adm_find_mods();
	}
	else if(isset($_REQUEST['submod']))
	{
		global $global;
		shn_gis_adm_show_mod_menu();
		include_once ($global['approot'].'/mod/gis/plugins/'.$_REQUEST['submod'].'/admin.inc');
		shn_plugin_default();
	}
	else
	{
    	shn_gis_adm_show_mod_menu();
		echo "<h2>".$conf['mod_gis_name']._(" Admin Page")."</h2>";
		//shn_gis_adm_showform();
		shn_gis_adm_show_mods();
		shn_gis_adm_find_mods();
	}
}

/**
 * Find and show GIS plugin configuration links
 * Auto-detects plugins 
 * @access public
 * @return void
 */
function shn_gis_adm_find_mods()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	shn_form_fopen(adm_gis_conf,null,array('req_message'=>false));
	shn_form_fsopen("GIS Plugin Configuration");
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			echo "$count.	<a href='index.php?mod=gis&act=admin&submod=$file'>"."$name"."</a><br>";
			//echo "$count.	<a href='index.php?mod=gis/plugins/"."$file"."&act=dd'>"."$name"."</a><br>";
			$count++;
		}
	}
	shn_form_fsclose();
	shn_form_fclose();	
}

/**
 * Find and show GIS plugin configuration links at top
 * Auto-detects plugins 
 * @access public
 * @return void
 */
function shn_gis_adm_show_mod_menu()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
?>
	<div id="submenu_v">
		<a href="index.php?mod=gis&act=admin"><?=_("General Mapping")?></a>
<?php
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
?>
<a href="index.php?mod=gis&act=admin&submod=<?=$file?>"><?=_($name)?></a>
<?php
			$count++;
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
function shn_gis_adm_show_mods()
{
	global $global;
	global $conf;
	$db=$global['db'];
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
?>
	<br /><h3><?php echo _("Main Configuration");?></h3>
<?php	
	shn_form_fopen(null,null,array('req_message'=>false));
?>
	<ul>

	<li><?php echo _("GIS Maps in Sahana can be set to display a default region");?> </li>
	<li><?php echo _("In order to set the map display for a particular region, you should know the Longitude and the Latitude of that region");?></li>
    <li><?php echo _("If these values are known, you can set them below:");?> </li>
	</ul>
<?php
	shn_form_fclose();
	shn_form_fopen(adm_commit,null,array('req_message'=>false));
	
	shn_form_fsopen(_("Default Center Coordinates"));
	
	$lat_help=_("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
	$lon_help=_("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
	shn_form_text(_("Center Longitude "),"x_center",null,array("value"=>$conf['mod_gis_center_x'],"help"=>$lat_help));
	shn_form_text(_("Center Latitude"),"y_center",null,array("value"=>$conf['mod_gis_center_y'],"help"=>$lon_help));
	shn_form_fsclose();
?>
	<ul>
	<li><?php echo _("Sahana supports a modular GIS plugin architecture ");?> </li>
	<li><?php echo _("You can select which GIS plugin to use as your default GIS");?></li>
    <li><?php echo _("Select the default GIS plugin from the detected plugins below:");?> </li>
    <li><?php echo _("For more information on adding custom plugins, refer to the documentation within the mod/gis subdirectory");?> </li>
	</ul>
<?php
	//shn_form_fclose();
	
	$query_mod="select value from config where module_id='gis' and confkey='dflt'";
	$result=$db->Execute($query_mod);
	if(!$res->EOF){
		$mod_name=$result->fields['value'];
	}
	
	
	
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include($global['approot'].'/mod/gis/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			$options_array[$file] = $name;
			//echo "$count.	<a href='index.php?mod=gis/plugins/"."$file"."&act=adm'>$file</a><br>";
			//$count++;
			
		}
	}
	$extra_opts_form['req_message'] = 'false';
	//shn_form_fopen(adm_mod,null,array('req_message'=>false));
	shn_form_fsopen(_("Detected GIS module plugins"));
	
	//$extra_opts['br']='true';
	//echo "module: $mod_name";
	shn_form_radio($options_array,_("Select GIS module"),"mod_gis",null,((isset($mod_name))?array("value"=>$mod_name):null));
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();	
}

/**
 * Show form to set default Northing/Easting Values
 * @access private
 */
function shn_gis_adm_showform(){
	global $conf;
	shn_form_fopen(null,null,array('req_message'=>false));
?>
	<ul>

	<li><?php echo _("GIS Maps in Sahana can be set to display a default region");?> </li>
	<li><?php echo _("In order to set the map display for a particular region, you should know the Longitude and the Latitude of that region");?></li>
    <li><?php echo _("If these values are known, you can set them below:");?> </li>
	</ul>
<?php
	shn_form_fclose();
	shn_form_fopen(adm_commit,null,array('req_message'=>false));
	
	shn_form_fsopen(_("Default Center Coordinates"));
	
	$lat_help=_("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
	$lon_help=_("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
	shn_form_text(_("Center Longitude "),"x_center",null,array("value"=>$conf['mod_gis_center_x'],"help"=>$lat_help));
	shn_form_text(_("Center Latitude"),"y_center",null,array("value"=>$conf['mod_gis_center_y'],"help"=>$lon_help));
	shn_form_fsclose();
	shn_form_submit(_("Done"));
	shn_form_fclose();
}

/**
 * Enter default GIS plugin to database
 */
function shn_gis_adm_mod()
{
	global $global;
	$db = $global['db'];
	if(!null==$_POST['mod_gis']){
		$query = "select * from config where confkey='dflt' and module_id='gis'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q = "UPDATE config SET value  = '{$_POST['mod_gis']}' WHERE module_id = 'gis' AND confkey='mod_gis_dflt'";
			$db->Execute($q);
		}
		else{
			$insert = "insert into config(module_id,confkey,value) values ('gis','mod_gis_dflt','{$_POST['mod_gis']}')";
			$db->Execute($insert);
		}
		
	}
	add_confirmation(_("Changes were saved"));
	shn_gis_adm_default();	
}
/**
 * Commit default Northing/Easting values
 * @access private
 */
function shn_gis_adm_commit(){

	add_confirmation(_("Changes were saved"));
	global $global;
	$db = $global['db'];
	//$gm="UPDATE config SET value = '{$_POST['key']}' WHERE module_id = 'gis' AND confkey = 'google_key'";                  
	if(!null==$_POST['x_center'])
	{
		$query = "select * from config where confkey='mod_gis_center_x' and module_id='gis'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q="UPDATE config SET value = '{$_POST['x_center']}' WHERE module_id = 'gis' AND confkey = 'mod_gis_center_x'";       
			$db->Execute($q);
		}
		else{
			$insert = "insert into config(module_id,confkey,value) values ('gis','mod_gis_center_x','{$_POST['x_center']}')";
			$db->Execute($insert);
		}
	}
	if(!null==$_POST['y_center'])
	{
		$query = "select * from config where confkey='mod_gis_center_y' and module_id='gis'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$r="UPDATE config SET value = '{$_POST['y_center']}' WHERE module_id = 'gis' AND confkey = 'mod_gis_center_y'";       
			$db->Execute($r);
		}
		else{
			$insert = "insert into config(module_id,confkey,value) values ('gis','mod_gis_center_y','{$_POST['y_center']}')";
			$db->Execute($insert);
		}
	}
	if(!null==$_POST['mod_gis']){
		$query = "select * from config where confkey='mod_gis_dflt' and module_id='gis'";
		$res = $db->Execute($query);
		if(!$res->EOF){
			$q = "UPDATE config SET value  = '{$_POST['mod_gis']}' WHERE module_id = 'gis' AND confkey='mod_gis_dflt'";
			$db->Execute($q);
		}
		else{
			$insert = "insert into config(module_id,confkey,value) values ('gis','mod_gis_dflt','{$_POST['mod_gis']}')";
			$db->Execute($insert);
		}
		
	}
	shn_gis_adm_default();	
}
						
?>
