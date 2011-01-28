<?php
/**
 * MM main.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Shreekanth Bohra
 * @author     kusum
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage MM
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . '/inc/lib_menu.inc';
include_once 'conf_inc.inc';

function shn_mm_mainmenu()
{
    global $global;
    $module = $global['module'];
    shn_mod_menuopen(_t('Module Manager'));
    
    shn_mod_menuitem('default',_t('Home'));
   
    shn_sub_mod_menuopen(_t('Available features'));
    shn_mod_menuitem('module_mgr',_t('Install/Uninstall'));
    shn_mod_menuitem('update',_t('Enable/Disable a module')); // update the status of the module
	shn_mod_menuitem('upgrade',_t('Upgrade')); // Upgrade the version of the module
    shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_t('App Store '));
    shn_mod_menuitem('app_store',_t('App store Home'));
	shn_mod_menuitem('search_box',_t('App store Search'));
	shn_mod_menuitem('app_settings',_t('App store Settings'));
        shn_mod_menuitem('view_cache',_t('View Modules(caches)'));
        shn_mod_menuitem('app_store_modules',_t('View App store Modules'));
	shn_sub_mod_menuclose();
	
    shn_mod_menuclose();
    //include the main menu so that the user can navigate outside the module
    include_once($global['approot'] . '/inc/handler_mainmenu.inc');
}
 

function shn_mm_default()
{
 global $global;
    include_once $global['approot'] . '/mod/mm/home.inc';

}

function shn_mm_change_conf($module)
{

global  $global;
global $conf;
	$db = $global['db'];
	
$status=null;
	
if($module!="")
{
	$file = '../mod/'.$module.'/conf.inc';
	$data = file($file) or die('Could not read file!');
	$dt ="";

	foreach ($data as $line)
	{
		echo "<br>";
		if(preg_match("/_enabled/",$line))
		{
			if(preg_match('/True/',$line))
			{
			
			$mod_query = "delete from sys_group_to_module where module = '$module' ";
			$res = $db->Execute($mod_query);
			$mod_query1 = "UPDATE  `modules` SET `status` =  'disabled' WHERE `module` = '$module' "; // delete from modules where module=$module
			$res1 = $db->Execute($mod_query1);
			$line=str_replace('True','False',$line);
			$status=true;
			}else
			{
			$mod_query = "UPDATE  `modules` SET `status` =  'installed' WHERE `module` = '$module' ";
			$res = $db->Execute($mod_query);
			$line=str_replace('False','True',$line);
			$status=false;
			}
		}
		else
		{
			//something to write
		}

	$dt.=$line;

		
	}
	$f =fopen($file,w);
	fwrite($f,$dt);
	fclose($f);
	if($status)
	{
	add_confirmation("Successfully Disabled the module :  ".$conf['mod_'.$module.'_name']);
	}
	else
	{
	add_confirmation("Successfully Enabled the module :  ".$conf['mod_'.$module.'_name']);
	}
}
else
{
add_error(_t("Module".$conf['mod_'.$module.'_name']." may not have been installed properly or doesn't exist"));
}
}

