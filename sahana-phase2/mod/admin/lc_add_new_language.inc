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
    shn_form_fsopen(_("Add Language"));
	shn_form_text(_('Language Name : '),'lang_name','', $extra_opts);
	shn_form_text(_('Language Folder Name : '),'lang_folder_name','', $extra_opts);
    shn_form_fsclose();    
    shn_form_submit(_("Add New"),'name="add"');
    shn_form_fsopen(_("Remove Language"));
    $lang = _shn_get_lang_list();
	shn_form_select($lang,_("Language List : "),'lang_name_remove',"",$extra_opts);
    shn_form_fsclose();    
    shn_form_submit(_("Remove"),'name="remove"');
    shn_form_fclose();    
}

function _shn_admin_lc_add_new_language()
{
	$lang = $_POST['lang_name'];
	$lang_folder_name = $_POST['lang_folder_name'];
	 
	$handle = fopen("../res/locale/locale", "a");
	 	
	$content = $lang_folder_name."\t".$lang."\n";
	if(fwrite($handle,$content) === FALSE) {       	
       echo "Cannot write to file ($filename)";
       exit;
    }else {
    	add_confirmation($lang._(" language add successfully"));
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
        	echo "Cannot write to file ($filename)";
        	exit;
    	}
	}
	 
	add_confirmation($language._(" language removed successfully"));
}

?>