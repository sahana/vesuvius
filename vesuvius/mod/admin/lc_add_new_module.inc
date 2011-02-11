<?php
/**
*
* Sahana Localization
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

function _shn_admin_lc_add_new_module()
{
	global $global;
	include_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	$lc_list = _shn_get_lang_list();
	shn_form_fopen("lc_add_new_module_post");
    shn_form_fsopen(_t("User Interface Language Translation"));
    $locale = $_SESSION["locale"];
    shn_form_select($lc_list,_t("Please select language: "),"locale",'DISABLED=DISABLED',array('value'=>"$locale"));
    shn_form_submit(_t("Merge"),'name="merge"');
    shn_form_fclose();

}

function _shn_admin_lc_add_new_module_update()
{
		$locale = $_SESSION["locale"];
		$return = array();
        $cmd = 'xgettext --keyword=__ --keyword=_e ' .
        '--keyword=_t  --default-domain=sahana ' .
        '--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .
        '--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_merge.po';
        system($cmd, &$return);

        $cmd = 'msgmerge --output-file=../res/locale/' . $locale . '/LC_MESSAGES/sahana.po ../res/locale/' . $locale . '/LC_MESSAGES/sahana.po ../res/locale/' . $locale . '/LC_MESSAGES/sahana_merge.po';
	    system($cmd, &$return);
	    print_r($return);
   		echo _t('New module translation merge succesfully');
   		add_confirmation(_t('New module translation merge succesfully'));
}

