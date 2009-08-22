<?php
/* $Id */

/**
 * Main Controller of the User Preferences
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage pref
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";


function shn_pref_signup(){
	global $global;
	include_once $global['approot']."inc/lib_security/auth_form.inc";
	shn_auth_form_signup();
}

function shn_pref_signup_cr(){
	if(shn_auth_self_signup_cr()==true){
		shn_pref_signup();		
		if($_SESSION['security_captcha_key'] !=md5($_POST["captcha"])){
			add_error(_t("Please provide the text in the image correctly to prove you are not a bot"));

			return;
		}
		shn_pref_signup();
	}else{
	   if($_SESSION['security_captcha_key'] !=md5($_POST["captcha"])){
			add_error(_t("Please provide the text in the image correctly to prove you are not a bot"));
			shn_pref_signup();
			return;
		}
		$ret = shn_auth_add_user($_POST['account_name'],$_POST['user_name'],$_POST['password'],$role=REGISTERED,null);
		if($ret){
			$msg=$_POST{"account_name"}._(" was successfully registered as a User ");
			add_confirmation($msg);
		}else {
			shn_pref_signup();
		}		
	}
}

function shn_image_pref_captcha(){
	shn_auth_gen_captcha();
}

/*
 * include all xxx_main.inc
 */
$d = dir($global['approot'].'mod/pref/');
while (false !== ($f = $d->read())) {
	if (preg_match('/.*_main.inc$/',$f)){
		if (file_exists($global['approot'].'mod/pref/'.$f)){
			include ($global['approot'].'mod/pref/'.$f);
		}
	}
}

/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_pref_mainmenu()
{
	global $global;
	$module = $global['module'];

	// Create the module menu
	shn_mod_menuopen(_t("User Preferences"));

	shn_mod_menuitem("default",_t("Home"));

	/* get the sub menus */
	$d = dir($global['approot'].'mod/pref/');
	while (false !== ($f = $d->read())) {
		if (preg_match('/.*_menu.inc$/',$f)){
			if (file_exists($global['approot'].'mod/pref/'.$f)){
				include ($global['approot'].'mod/pref/'.$f);
			}
		}
	}

	shn_mod_menuitem("enable_ocr_xform",_t("OCR XForm"),"pref");
	shn_mod_menuclose();
	 
	// include the main menu
	include $global['approot']."/inc/handler_mainmenu.inc";
}

/**
 *
 * This function displays the home page of the User Preferences
 *
 * @access public
 * @return void
 */
function shn_pref_default()
{
	?>
<div id="home">
<h2><?php echo _t("Welcome to User Preferences");?></h2>
<p><?php echo ("User Preferences Module will allow you to set any preferred configuration.")."<br />".
_t("Which will help you to customize Sahana to your preference.")."<br />"._t("Following Preferences can be set")."</p><ul>"; 

	echo "<li><b>"._t("Multiple Incident Management")."</b></li>"."</ul>";

?>
</div>
<?php
}



/**
 * Generates a form to enable/disable XForm
 * @access public
 * @return void
 */

function shn_pref_enable_ocr_xform() {
include_once('xform_config.inc');
	echo "<h2>"._t("Enable/Disable OCR XForm")."</h2>";
	shn_form_fopen("enable_xform","pref",array("req"=>false));
	shn_form_fsopen(_t("Enable or disable the OCR friendly form generation."));
	$_value = _shn_xform_conf_value();
	$val_xform = ($_value==true?'enabled':'disabled');
	shn_form_radio(array("enabled"=>_t("Enabled"),"disabled"=>_t("Disabled")),_t("OCR friendly XForm : "),"ocr_xform_status","",array('value'=>$val_xform));
	shn_form_fsclose();
	shn_form_submit(_("Cancel"),"name='disable'");
	shn_form_submit(_("Save"));
	shn_form_fclose();
}


function shn_pref_enable_xform(){
include('xform_config.inc');
	if(!$_POST['disable']){
		$val_xform = $_POST['ocr_xform_status'];
		if($val_xform =='enabled'){
			$ret_xform = _shn_xform_set_config_value('false');
			if($ret_xform == true){
				add_confirmation(_t("Your preference was successfully saved."));
			}
			else{
				add_error(_t("An error occured while saving your preference."));
			}
		}
		else{
			$ret_xform = _shn_xform_set_config_value('true');
			if($ret_xform == false){
				add_confirmation(_t("Your preference was successfully saved."));
			}
			else{
				add_error(_t("An error occured while saving your preference."));
			}
		}
		shn_pref_enable_ocr_xform();
	}
	else {
		shn_pref_enable_ocr_xform();
	}
}




/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post)
{
	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}
}


