<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage localization
* @tutorial	  localization.pkg
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
require_once $global['approot']."/inc/lib_locale/lib_locale.inc";


function __select_locale()
{
	shn_form_fopen("lc_set",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'set_locale'));

    shn_form_fsopen(_("Select Locale"));

    shn_form_select(array('en_US'=>'en_US [English US]'),_("Locale"),"locale",null);

    shn_form_fsclose();
    shn_form_submit(_("Set Locale"));
    shn_form_fclose();
}

switch ($_REQUEST['seq'])
{
	case ''	:
            if(_shn_lc_issetdblc())
            {
            	$locale = _shn_lc_getdblc();
            	print "<h3>" . _("Current locale setting ") .
            			"in the Database : $locale </h3>";
            	__select_locale();
            }
            else
            {
            	print "<h3>" .
            		  _("The locale setting is not set in the Database") .
            		  "</h3><br /><h4>" .
            		  _("Please select a valid locale from the list") .
					  "</h4>";
            	__select_locale();
            }
            break;

    case 'set_locale':
			$locale = $_POST['locale'];
			_shn_lc_setdblc($locale);
			break;
}
?>
