<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */

global $global;

function __select_locale() {
	$lc_list = _shn_get_lang_list();
	$locale = $_SESSION["locale"];
	print "<h5>" . _t("Current language : ") . _lc($locale) . "</h5>";
	shn_form_fopen("lc_set",null,array('req_message'=>false));
	shn_form_hidden(array('seq'=>'set_locale'));
	shn_form_fsopen(_t("Select Locale"));
	shn_form_select($lc_list,"","locale",'onChange=submit(this);',array('value'=>"$locale"));
	shn_form_fsclose();
	shn_form_submit(_t("Set Locale"));
	shn_form_fclose();
}



switch($_REQUEST['seq']) {
	case ''	:
		if(_shn_lc_issetdblc()) {
			$locale = _shn_lc_getdblc();

			print "<h5>" .
			_t("Current locale setting in the Database : ") .
			_lc($locale) .
			" </h5>";

			__select_locale();
		}else {
			print "<h5>" .
					_t("The locale setting is not set in the Database") .
					"</h5><br /><h5>" .
					_t("Please select a valid locale from the list") .
				"</h5>";
			__select_locale();
		}
				break;

	case 'set_locale':
				$locale = $_POST['locale'];
				_shn_lc_setdblc($locale);
				_shn_lc_setcookielc($locale);
				_shn_lc_setsessionlc($locale);
				__select_locale();
				break;
}

