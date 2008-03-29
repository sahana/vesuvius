<?php
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: multimap.inc,v 1.5 2008-03-29 19:55:41 mifanc Exp $
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
			shn_form_fsopen('Multimap');
				shn_form_fsopen('INFO');
					echo _t("<p>Enable <a href='http://multimap.com/'>Multimap</a> &trade; Mapping Service" .
							" by selecting the checkbox option below.</p>");
					echo _t("<p>The Multimap mapping API requires Internet connectivity and a valid Multimap key</p>");
					
				shn_form_fsclose();
				shn_form_fsopen('ENABLE');
					shn_form_checkbox(_t('Enable Multimap'),'ol_multimap');			
				shn_form_fsclose();
			shn_form_fsclose();
			shn_form_fsopen('API Key');
				shn_form_fsopen('INFO');
					echo _t("<p>Multimap requires a  key for operation</p>");
					echo _t("<p>Register a multimap key, and enter it below</p>");
					echo _t("<p>Register your Multimap key at: </p> <a href='http://multimap.com/' target=_blank>Multimap</a>");
				shn_form_fsclose();
				shn_form_fsopen('Enter API Key');
					shn_form_text(_t("Enter Multimap Key"),"ol_multi_map_key",'size="100"',array('value'=>$conf['gis_ol_multimap_key']));
				shn_form_fsclose();
			shn_form_fsclose();
		shn_form_fsclose();
	}
}
 
?>

