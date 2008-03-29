<?php
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: ol_wms.inc,v 1.3 2008-03-29 19:56:27 mifanc Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class ol_wms implements layer{
	
	function ol_wms()
	{
		
	}
	function print_form()
	{
		shn_form_fsopen(_t('OL WMS'));
		shn_form_checkbox(_t('Enable Open Layers Web Mapping Service'),'ol_wms');
		shn_form_fsclose();
	}
}
 
?>

