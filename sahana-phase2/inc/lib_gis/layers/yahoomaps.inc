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



	shn_form_fsopen(_t('Yahoo Maps'));
	shn_form_checkbox(_t('Enable Yahoo Maps'),'ol_yahoo_maps');
	shn_form_text(_t("Enter Yahoo Maps Key"),"ol_yahoo_map_key",'size="100"',array('value'=>$conf['gis_ol_yahoo_key']));
	shn_form_fsclose();
 
?>

