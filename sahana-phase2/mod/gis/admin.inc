<?php
/* $Id: admin.inc,v 1.5 2006-03-16 10:11:45 mifanc Exp $ */

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
		 <?php echo "<h2>"._("GIS / Mapping Admin Page")."</h2>"?>
		<?php //echo _(" <p> Use the below forms to Administer GIS / Mapping</p>");?>

<?php
	shn_gis_adm_showform();
	shn_gis_adm_show_mods();
	shn_gis_adm_find_mods();
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
			echo "$count.	<a href='index.php?mod=gis/plugins/"."$file"."&act=adm'>"."$name"."</a><br>";
			$count++;
		}
	}
	shn_form_fsclose();
	shn_form_fclose();	
}

/**
 * Show radio button selection of available GIS plugins
 * Enter Selected values 
 * @access private
 * @return void  
 */
function shn_gis_adm_show_mods()
{
?>
	<br/><h3><?php echo _("GIS Plugins Detected");?></h3>
<?php	
	shn_form_fopen(null,null,array('req_message'=>false));
?>
	<ul>
	<li><?php echo _("Sahana supports a modular GIS plugin architecture ");?> </li>
	<li><?php echo _("You can select which GIS plugin to use as your default GIS");?></li>
    <li><?php echo _("Select the default GIS plugin from the detected plugins below:");?> </li>
	</ul>
<?php
	shn_form_fclose();
	global $global;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
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
	shn_form_fopen(adm_mod,null,array('req_message'=>false));
	shn_form_fsopen("Detected GIS module plugins");
	
	$extra_opts['br']='true';
	shn_form_radio($options_array,"Select GIS module","mod_gis",null,$extra_opts);
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();	
}

/**
 * Show form to set default Northing/Easting Values
 * @access private
 */
function shn_gis_adm_showform(){
	shn_form_fopen(null,null,array('req_message'=>false));
?>
	<ul>

	<li><?php echo _("GIS Maps in Sahana can be set to display a default region");?> </li>
	<li><?php echo _("In order to set the map display for a particular region, ") .
			_("you should know the Northing/X coordinate and the Easting/Y coordinate of that region");?></li>
    <li><?php echo _("If these values are known, you can set them below:");?> </li>
	</ul>
<?php
	shn_form_fclose();
	shn_form_fopen(adm_commit,null,array('req_message'=>false));
	
	shn_form_fsopen(_("Default Center Coordinates"));
	
	
	shn_form_text(_("Center Northing Value[coordinate of center point]"),"x_center");
	shn_form_text(_("Center Easting Value[coordinate of center point]"),"y_center");
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
		$q = "UPDATE config SET value  = '{$_POST['mod_gis']}' WHERE module_id = 'gis' AND confkey='dflt'";
		if(!$db->Execute($q)){
			//handle error
			//add new value into database
			$post_val = $_POST['mod_gis'];
			$qe = "INSERT INTO config VALUES('gis','dflt',$post_val)";
			$db->Execute($qe);
		}
		
	}
	echo "<strong>"._("Your Changed Were Saved")."</strong>";
	shn_gis_adm_default();	
}
/**
 * Commit default Northing/Easting values
 * @access private
 */
function shn_gis_adm_commit(){
	echo "<h3>"._("Your Changes Were Saved")."</h3>";
	global $global;
	$db = $global['db'];
	//$gm="UPDATE config SET value = '{$_POST['key']}' WHERE module_id = 'gis' AND confkey = 'google_key'";                  
	if(!null==$_POST['x_center'])
	{
		$q="UPDATE config SET value = '{$_POST['x_center']}' WHERE module_id = 'gis' AND confkey = 'center_x'";       
		$db->Execute($q);
	}
	if(!null==$_POST['y_center'])
	{
		$r="UPDATE config SET value = '{$_POST['y_center']}' WHERE module_id = 'gis' AND confkey = 'center_y'";       
		$db->Execute($r);
	}
	shn_gis_adm_default();	
}
						
?>
