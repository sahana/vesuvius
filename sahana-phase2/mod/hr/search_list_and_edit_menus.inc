<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_hr_search_list_and_edit_menu1()
{
	_shn_hr_print_header(_t("Search Homeless Famil(ies)"));
	shn_hr_search_hf();
	print '<br />';
	shn_hr_list_menu1_and_menu2(false,false,true);
}

function shn_hr_search_list_and_edit_menu2()
{
	_shn_hr_print_header(_t("Search Damaged House(s)"));
	shn_hr_search_damaged_house();
	print '<br />';
	shn_hr_list_menu1_and_menu2(false,true,true);
}

function shn_hr_search_list_and_edit_menu3()
{
	_shn_hr_print_header(_t("Search Contractor(s)"));
	shn_hr_search_contractor();
	print '<br />';
	shn_hr_list_menu3(false,true);
}

function shn_hr_search_list_and_edit_menu4()
{
	_shn_hr_print_header(_t("Search Site(s)"));
	shn_hr_search_site();
	print '<br />';
	shn_hr_list_menu4(false,true);
}

?>
