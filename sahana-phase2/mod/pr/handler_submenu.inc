<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */	
	
	function shn_pr_submenu()
	{
		global $global,$conf;
		shn_mod_menuopen(_t($conf['mod_pr_name']));
		shn_mod_menuitem('default',_t('Person Registry'),'pr');
		
		shn_sub_mod_menuopen(_t('Person Information'));
		shn_sub_mod_menuitem('add_person', _t('Add Person'));		
		shn_sub_mod_menuitem('list_person', _t('List Person(s)'));		
		shn_sub_mod_menuclose();
		
		shn_sub_mod_menuopen(_t('Group Information'));
		shn_sub_mod_menuitem('add_group', _t('Add Group'));		
		shn_sub_mod_menuitem('list_group', _t('List Group'));		
		shn_sub_mod_menuclose();
		
		shn_sub_mod_menuopen(_t('Report(s)'));		
		shn_sub_mod_menuitem('person_rpt', _t('Person(s)'));
		shn_sub_mod_menuitem('group_rpt', _t('Group(s)'));				
		shn_sub_mod_menuclose();
		
		shn_mod_menuitem('person_api',_t('Person API Samples'),'pr');
		
		shn_mod_menuclose();
		
		include $global['approot']."/inc/handler_mainmenu.inc";
	}

