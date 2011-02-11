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

function _shn_admin_lc_upload_files()
{
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
	//shn_form_button(_t("Browse"),"onClick='LimitAttach(form,file)'",$extra_opts);
	shn_form_fclose();	
}

