<?php
/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage localization
* @package    Sahana - http://sahana.sourceforge.net
* @author     Prabath Kumarasinghe<prabath321@gmail.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

function _shn_admin_lc_translate_update(){
	global $global;
	include_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	$lc_list = _shn_get_lang_list();
	shn_form_fopen("lc_ui_trns_update&update=Update",null,array('req_message'=>false));
	shn_form_fsopen(_t("User Interface Language Translation"));
    $locale = $_SESSION["locale"];
    shn_form_select($lc_list,_t("Please select language: "),"locale",'DISABLED=DISABLED',array('value'=>"$locale"));
    shn_form_submit(_t("Update"),'name="update"');
    shn_form_fclose();

}

function _shn_admin_lc_translate_compile(){
	$return = array();
	$locale = $_SESSION["locale"];
	$cmd = 'msgfmt ../res/locale/' . $locale . '/LC_MESSAGES/sahana.po --output-file=../res/locale/' . $locale . '/LC_MESSAGES/sahana.mo';
    system($cmd, &$return);
    //print_r($return);
    if($return == 1){
    	add_error('Translation not updated, please give directory and file permission to sahana/res folder.');
    	display_errors();
    	exit;
    } else {
   		add_confirmation(_t('Translation updated succesfully.'));
}

