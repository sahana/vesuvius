<?php
/**
*
* Sahana Admin & ACL section
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

function _shn_admin_lc_add_new_language_form()
{
	global $global;
	include_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	shn_form_fopen("lc_add_new_language_post");
    shn_form_fsopen(_t("Add Language"));
    echo "<p>"._t("NOTE : Please make sure file and directory permissions are given to to sahana/res folder")."</p>";
    $extra_opts['req'] = true;
	shn_form_text(_t('Language Name : '),'lang_name','', $extra_opts);
	shn_form_text(_t('Language Folder Name : '),'lang_folder_name','', $extra_opts);
    shn_form_fsclose();
    shn_form_submit(_t("Add New"),'name="add"');
    shn_form_fsopen(_t("Remove Language"));
    echo "<p>"._t("NOTE : Please make sure file and directory permissions are given to to sahana/res folder")."</p>";
    $lang = _shn_get_lang_list();
    $extra_opts['req'] = false;
	shn_form_select($lang,_t("Language List : "),'lang_name_remove',"",$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_t("Remove"),'name="remove"');
    shn_form_fclose();
}

function _shn_admin_lc_add_new_language()
{
	$lang = $_POST['lang_name'];
	$lang_folder_name = $_POST['lang_folder_name'];

	$handle = fopen("../res/locale/locale", "a");

	$content = $lang_folder_name."\t".$lang."\n";
	if(fwrite($handle,$content) === FALSE) {
       add_error(_("Cannot write to file, please give file and directory permissions to sahana/res folder"));
       display_errors();
       exit;
    }else {
    	add_confirmation($lang._t(" language add successfully"));
    }

}

function _shn_admin_lc_remove_language()
{
	$handle = fopen("../res/locale/locale", "r");

	while($localeinfo = fscanf($handle,"%s\t%s\t%s\n")) {
    	list ($locale, $name,$ex_name) = $localeinfo;
    	if($ex_name!=null) {
    		$name = $name." ".$ex_name;
    	}

    	if($locale!=$_POST['lang_name_remove'])
    		$l_list[$locale] = $name;
    	else
    		$language = $name;
    	//... do something with the values
	}

	$handle = fopen("../res/locale/locale", "w");

	foreach($l_list as $key => $value) {
		$content = $key."\t".$value."\n";
		if(fwrite($handle,$content) === FALSE) {
        	add_error(_t("Cannot write to file, please give file and directory permissions to sahana/res folder"));
        	display_errors();
        	exit;
    	}
	}

	add_confirmation($language._t(" language removed successfully"));
}

