<?php
/**
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library	    GIS
* @version		$Id: virtualearth.inc,v 1.4 2008-03-29 20:16:22 mifanc Exp $
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
		global $conf;
		shn_form_fsopen(_t('MS Virtual Earth'));
			shn_form_fsopen('MS Virtual Earth');
				shn_form_fsopen('INFO');
					echo _t("<p>Enable <a href='http://maps.live.com/'>Microsoft Virtual Earth</a> &trade; Mapping Service" .
							" by selecting the checkbox option below.</p>");
					echo _t("<p>The Virtual Earth mapping API requires Internet connectivity</p>");
					
				shn_form_fsclose();
				shn_form_fsopen('ENABLE');
					shn_form_checkbox(_t('Enable Microsoft Virtual Earth'),'ol_ms_earth');			
				shn_form_fsclose();
			shn_form_fsclose();
		shn_form_fsclose();
	}
}
 
?>

