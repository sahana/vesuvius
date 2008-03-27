<?php
/**
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

class multimap implements layer{
	
	function multimap()
	{
		
	}
	function print_form()
	{
		shn_form_fsopen(_t('Multimap'));
		shn_form_checkbox(_t('Enable Multimap'),'ol_multimap');
		shn_form_text(_t("Enter Multimap Key"),"ol_multi_map_key",'size="100"',array('value'=>$conf['gis_ol_multimap_key']));
		shn_form_fsclose();
	}
}
 
?>

