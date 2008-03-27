<?php
/**
* Sahana Messaging Module
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library		GIS
* @version		$id$
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Layer Catalog management main
 * Tabbed functionality for seperate layers
 */
function shn_gis_layer_main()
{
	_shn_gis_layer_main_form();
}

function _shn_gis_layer_main_form()
{
	shn_form_fopen('gis',null,array('tab'=>'float'));
	_shn_gis_layer_load_admin_forms();
	shn_form_drawtab();
	shn_form_submit(_t('Save Settings'));
	shn_form_fclose();
}

/**
 * Load layer classes admin sections as tabs 
 */
function _shn_gis_layer_load_admin_forms()
{
	global $global;
	global $conf;
	$gis_layer_dir=$global['approot'].'/inc/lib_gis/layers/';
	$dir = opendir($gis_layer_dir);
	
	
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include_once ($global['approot'].'/inc/lib_gis/layers/'.$file);
			$class = spliti('\.',$file);
			
			$classname = $class[0];
			$layer_obj = new $classname();
			$layer_obj->print_form();
			
						
		}
	}
	
}

?>
