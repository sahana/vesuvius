<?php
/* $Id: admin.inc,v 1.2 2005-12-21 04:10:41 mifanc Exp $ */

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
	shn_gis_adm_find_mods();
}

function shn_gis_adm_find_mods()
{
?>
	<br/><h3>GIS Plugins Detected</h3>
<?php
	global $global;
	include_once($global['approot'].'/inc/lib_modules.inc');
	$count=1;
	$gis_plugins_dir=$global['approot'].'/mod/gis/plugins/';
	$dir = opendir($gis_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			echo "$count.	<a href='index.php?mod=gis/plugins/google_maps&act=adm'>$file</a><br>";
			$count++;
		}
	}
}

function shn_gis_adm_showform(){
	shn_form_fopen("");
	shn_form_fsopen("General Configuration");
	//shn_form_select();
	shn_form_text("Center Northing Value[coordinates of center point]","");
	shn_form_text("Center Easting Value[coordinates of center point]","");
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();
}
						
?>
