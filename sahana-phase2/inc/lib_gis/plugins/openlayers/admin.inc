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


function shn_plugin_default(){
?>
<h2><?php echo _t("Openlayers Admin Page")?></h2>	
<?php
	_shn_gis_gm_form();
}

function _shn_gis_gm_form(){
	//shn_form_fopen(abc);
	// @todo: using small hack at the moment to bypass front controller. correct later
?>
<!-- 	<div id="formcontainer"> -->
	<!--<form method="POST" action="index.php?mod=gis&act=adm_default&submod=google_maps&seq=commit" id="formset">-->
<?php
    shn_form_fopen("adm_default&submod=open_layers&seq=commit",null,array('req'=>false));
	shn_form_fsopen("Information");
	echo _t("<p>See 'GIS Layer Management' in left-hand menu</p>");
	shn_form_fsclose();
	shn_form_fclose();
	
}

function shn_plugin_commit()
{
	global $global;
	$db = $global['db'];
		
	if(!null==($_POST['gmap_key'])){
		echo _t("Changes were saved");
		$query = "select * from config where confkey='google_key' and module_id='gis'";
		$res = $db->Execute($query);
		if(!$res->EOF)
		{
			$gm="UPDATE config SET value = '{$_POST['gmap_key']}' WHERE module_id = 'gis' AND confkey = 'google_key'";
			$db->Execute($gm);
		}
		else
		{
			$insert = "insert into config values ('gis','google_key','{$_POST['gmap_key']})";
			$db->Execute($insert);
		}
		
	}
}
?>
