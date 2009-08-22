<?php
/**Admin controller of the Web Services Module 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ws
*/

include_once($global['approot'].'/inc/lib_form.inc');


function _shn_ws_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=ws&act=adm_enable_authentication"><?php echo _t("Enable/Disable Web Service Authentication") ?></a> 

</div>

<br />
<?php

}

function shn_ws_adm_default()
{
    _shn_ws_adm_sub_menu();
?>
    <p><b> <?php echo _t("Welcome to the Web Services admin page") ?> </b></p>
    <p> <?php echo _t("Use the Above Navigation to Administer Web Services") ?></p>

    


<?php
}



function shn_ws_adm_enable_authentication()
{
    _shn_ws_adm_sub_menu();
    shn_ws_adm_enable_auth_form();
}

function shn_ws_adm_enable_authentication_cr()
{
	global $global;
	$db=$global["db"];
	
	if($_POST['action']=='enable'){
		$q="update config set value=true where module_id='ws' and confkey='authentication'";
	}else{
		$q="update config set value=false where module_id='ws' and confkey='authentication'";
	}
	$res=$db->Execute($q);
	shn_ws_adm_enable_authentication();
}

/**
 * Generates a form to enable/disable Web Service Authentication
 * @access public
 * @return void
 */

function shn_ws_adm_enable_auth_form(){

    global $global;
    $db=$global['db'];
 
 	echo "<h3>"._t("Enable/Disable Web Service Authentication")."</h3>" ;

	shn_form_fopen("adm_enable_authentication_cr","ws",array('req_message'=>false));
 	$acl=shn_acl_is_web_service_auth_enabled();
 	if($acl==true){
 		shn_form_hidden(array("action"=>'disable'));
		shn_form_submit(_t("Disable Web Service Authentication"));
 	}else{
 		shn_form_hidden(array("action"=>'enable'));
		shn_form_submit(_t("Enable Web Service Authentication"));
 	}
    shn_form_fclose();
}





