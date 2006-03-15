<?php
/* $Id: admin.inc,v 1.4 2006-03-15 12:21:52 mifanc Exp $ */

/**Admin Module for GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_gis_adm_sub_menu(){
?>
<div id="submenu_v">
<!--<a href="index.php?mod=cr&act=adm_forms">Configure Form Display</a>-->
</div>
<br>
<?php
}
function shn_gis_adm_default()
{
    _shn_gis_adm_sub_menu();
		?>
		    <h2> GIS / Mapping Admin Page </h2>
				    <p> Use the Above Navigation to Administer GIS / Mapping</p>

<?php
	shn_gis_adm_showform();
	shn_gis_adm_show_mods();
	shn_gis_adm_find_mods();
}

function shn_gis_adm_find_mods()
{
?>
<?php
	global $global;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	shn_form_fopen(adm_gis_conf,null,array('req_message'=>false));
	shn_form_fsopen("GIS Plugin Configuration");
	while($file = readdir($dir)){
		if(!is_dir($file)){
			echo "$count.	<a href='index.php?mod=gis/plugins/"."$file"."&act=adm'>$file</a><br>";
			$count++;
		}
	}
	shn_form_fsclose();
	shn_form_fclose();	
}

function shn_gis_adm_show_mods()
{
?>
	<br/><h3>GIS Plugins Detected</h3>
<?php
	global $global;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			$options_array[$file] = $file			;
			//echo "$count.	<a href='index.php?mod=gis/plugins/"."$file"."&act=adm'>$file</a><br>";
			//$count++;
			
		}
	}
	$extra_opts_form['req_message'] = 'false';
	shn_form_fopen(adm_mod,null,array('req_message'=>false));
	shn_form_fsopen("Detected GIS module plugins");
	
	$extra_opts['br']='true';
	shn_form_radio($options_array,"Select GIS module","mod_gis",null,$extra_opts);
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();	
}

function shn_gis_adm_showform(){
	shn_form_fopen(adm_commit,null,array('req_message'=>false));
	shn_form_fsopen("General Configuration");
	//shn_form_select();
	shn_form_text("Center Northing Value[coordinates of center point]","x_center");
	shn_form_text("Center Easting Value[coordinates of center point]","y_center");
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();
}

function shn_gis_adm_commit(){
	echo "<h3>Changes Made</h3>";
	global $global;
	$db = $global['db'];
	//$gm="UPDATE config SET value = '{$_POST['key']}' WHERE module_id = 'gis' AND confkey = 'google_key'";                  
	if(!null==$_POST['x_center'])
	{
		$q="UPDATE config SET value = '{$_POST['x_center']}' WHERE module_id = 'gis' AND confkey = 'center_x'";       $db->Execute($q);
	}
	if(!null==$_POST['y_center'])
	{
		$r="UPDATE config SET value = '{$_POST['y_center']}' WHERE module_id = 'gis' AND confkey = 'center_y'";       $db->Execute($r);
	}
	shn_gis_adm_default();	
}
						
?>
