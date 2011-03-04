<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @author       Prabath Kumarasinghe<prabath321@gmail.com>
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */



function _shn_admin_lc_translate_update() {
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



function _shn_admin_lc_translate_compile() {
	$return = array();
	$locale = $_SESSION["locale"];
	$cmd = 'msgfmt ../res/locale/' . $locale . '/LC_MESSAGES/sahana.po --output-file=../res/locale/' . $locale . '/LC_MESSAGES/sahana.mo';
	system($cmd, &$return);
	if($return == 1) {
		add_error('Translation not updated, please give directory and file permission to sahana/res folder.');
		display_errors();
		exit;
	} else {
		add_confirmation(_t('Translation updated succesfully.'));
	}
}

