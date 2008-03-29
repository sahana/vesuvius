<?php
/* $id$ */
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @module	    GIS
* @version		$id$
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


global $global;
include_once $global['approot'].'inc/lib_gis/layer_class.inc';

class googlemaps implements layer{
	
	function googlemaps()
	{
		
	}
	function print_form()
	{
		shn_form_fsopen(_t('Google Maps'));
			shn_form_fsopen('Google Maps');
				shn_form_fsopen('INFO');
					echo _t("<p>Enable <a href='http://maps.google.com/'>GoogleMaps</a> &trade; Mapping Service" .
							" by selecting the checkbox option below.</p>");
					echo _t("<p>The GoogleMaps mapping API requires Internet connectivity and a valid Google Maps key</p>");
					
				shn_form_fsclose();
				shn_form_fsopen('ENABLE');
					shn_form_checkbox(_t('Enable Google Maps'),'ol_google_maps');	
				shn_form_fsclose();
			shn_form_fsclose();
			shn_form_fsopen('Viewport Settings');
				shn_form_checkbox(_t('Google Map View'),'ol_google_map_view');
				shn_form_checkbox(_t('Google Satellite View'),'ol_google_map_sat');
				shn_form_checkbox(_t('Google Hybrid View'),'ol_google_map_hyb');
			shn_form_fsclose();
			shn_form_fsopen(_t('API Key'));
				shn_form_fsopen(_t('INFO'));
					echo _t("<p>Google Maps requires a unique key pointing to where Sahana is hosted</p>");
					echo _t("<p>Register a google maps key for the url you host sahana in, and enter it below</p>");
					echo _t("<p>Register your Google Maps key at: </p> <a href='http://www.google.com/apis/maps/' target=_blank>Google Maps</a>");
				shn_form_fsclose();
				shn_form_fsopen(_t('Enter API Key'));
					shn_form_text(_t("Enter Google Maps Key"),"ol_google_map_key",'size="100"',array('value'=>$conf['gis_google_key']));
				shn_form_fsclose();
			shn_form_fsclose();
		shn_form_fsclose();
	}
}
?>

