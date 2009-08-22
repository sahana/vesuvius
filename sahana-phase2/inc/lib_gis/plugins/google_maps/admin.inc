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
* @author     Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* 
*/

include_once($global['approot'].'/inc/lib_form.inc');


function shn_plugin_default(){
?>
<h2><?php echo _t("Google Maps Admin Page")?></h2>	
<?php
	_shn_gis_gm_form();
}

function _shn_gis_gm_form(){
	global $global;
	$db = $global['db'];
	
	global $conf;
	$value = $conf['gis_google_key'];
	
	shn_form_fopen("gis_plugin_default&plugin=google_maps&seq=commit",null,array('req'=>false));
	shn_form_fsopen(_t("INFO"));
	echo _t("<p>Google Maps requires a unique key pointing to where Sahana is hosted</p>");
	echo _t("<p>Register a google maps key for the url you host sahana in, and enter it below</p>");
	echo _t("<p>Get your key from:</p> <a href='http://www.google.com/apis/maps/' target=_blank>Google Maps</a>");
	shn_form_fsclose();
	shn_form_fsopen(_t("Configure Google Maps"));
	shn_form_text(_t("Enter Google Maps Key"),"gmap_key",'size="100"',array('value'=>$value));
	shn_form_fsclose();
	shn_form_submit(_t("Save"));
	shn_form_fclose();
	
}

function shn_plugin_commit()
{
	global $global;
	$db = $global['db'];
		
	if(!null==($_POST['gmap_key'])){
		$query = "select * from config where confkey='gis_google_key' and module_id='admin'";
		$res = $db->Execute($query);
		if(!$res->EOF)
		{
			$gm="UPDATE config SET value = '{$_POST['gmap_key']}' WHERE module_id = 'admin' AND confkey = 'gis_google_key'";
			$db->Execute($gm);
		}
		else
		{
			$insert = "insert into config (module_id,confkey,value) values ('admin','gis_google_key','{$_POST['gmap_key']}')";
			$db->Execute($insert);
		}
		
	}
}


