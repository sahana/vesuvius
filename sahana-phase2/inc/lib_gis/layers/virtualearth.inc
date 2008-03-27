<?php
/**
* Sahana Messaging Module
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @module	    GIS
* @version		
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class virtualearth implements layer{
	
	function virtualearth()
	{
		
	}
	function print_form()
	{
		shn_form_fsopen(_t('MS Virtual Earth'));
		shn_form_checkbox(_t('Enable Microsoft Virtual Earth'),'ol_ms_earth');
		shn_form_fsclose();
	}
}
 
?>

