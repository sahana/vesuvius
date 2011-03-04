<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Prabath Kumarasinghe<prabath321@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */



function _shn_admin_lc_upload_files() {
	global $global;
	include_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	$lc_list = _shn_get_lang_list();
	shn_form_fopen('lc_file_browser',null,array('enctype'=>'enctype="multipart/form-data"'));
	shn_form_fsopen(_t("File Selection"));
	$locale = $_SESSION["locale"];
	shn_form_select($lc_list,_t("Please select language: "),"locale",'',array('value'=>"$locale"));
	shn_form_upload(_t("Upload Spread Sheet : "),'userfile', array('req'=>true));
	shn_form_fsclose();
	shn_form_submit(_t("Import"));
	shn_form_fclose();
}

