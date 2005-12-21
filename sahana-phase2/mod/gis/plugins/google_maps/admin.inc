<?php
/* $id$ */
/**Admin Module for Google Maps
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   	Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');

function shn__default(){
?>
<h2><?php echo _("Google Maps Admin Page")?></h2>	
<?php
	_shn_gis_gm_form();
}

function _shn_gis_gm_form(){
	//shn_form_fopen(abc);
	// @todo: using small hack at the moment to bypass front controller. correct later
?>
	<div id="formcontainer">
	<form method="POST" action="index.php?mod=gis/plugins/google_maps&act=adm_com" id="formset">
<?php
	shn_form_fsopen("Configure Google Maps");
	shn_form_text("Enter Google Maps Key","gmap_key",'size="110"');
	shn_form_fsclose();
	shn_form_submit("Done");
	shn_form_fclose();
}
?>
