<?php
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: yahoomaps.inc,v 1.5 2008-03-29 20:07:41 mifanc Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;

include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class yahoomaps implements layer{
	
	function print_form()
	{
		global $conf;
		shn_form_fsopen(_t('Yahoo Maps'));
			shn_form_fsopen('Yahoo Maps');
				shn_form_fsopen('INFO');
					echo _t("<p>Enable <a href='http://maps.yahoo.com/'>Yahoo Maps</a> &trade; Mapping Service" .
							" by selecting the checkbox option below.</p>");
					echo _t("<p>The Yahoo Maps mapping API requires Internet connectivity and a valid Yahoo Map key</p>");
					
				shn_form_fsclose();
				shn_form_fsopen('ENABLE');
					shn_form_checkbox(_t('Enable Yahoo Maps'),'ol_yahoo_maps');		
				shn_form_fsclose();
			shn_form_fsclose();
			shn_form_fsopen('Viewport Settings');
				shn_form_checkbox(_t('Yahoo Map View'),'ol_yahoo_map_view');
				shn_form_checkbox(_t('Yahoo Satellite View'),'ol_yahoo_map_sat');
				shn_form_checkbox(_t('Yahoo Hybrid View'),'ol_yahoo_map_hyb');
			shn_form_fsclose();
			shn_form_fsopen('API Key');
				shn_form_fsopen('INFO');
					echo _t("<p>Yahoo Maps requires a  key for operation</p>");
					echo _t("<p>Register a Yahoo Map key, and enter it below</p>");
					echo _t("<p>Register your Yahoo Map key at: </p> <a href='http://maps.yahoo.com/' target=_blank>Yahoo Maps</a>");
				shn_form_fsclose();
				shn_form_fsopen('Enter API Key');
					shn_form_text(_t("Enter Yahoo Maps Key"),"ol_yahoo_map_key",'size="100"',array('value'=>$conf['gis_ol_yahoo_key']));
				shn_form_fsclose();
			shn_form_fsclose();
		shn_form_fsclose();
	}
}
 
?>

