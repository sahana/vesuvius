<?
/**
 * @name         Resources - Locale handler
 * @version      16
 * @package      rez
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0729
 */

function shn_rez_getlocale() {
	global $global;
	if ( isset($_SESSION['locale']) ) {
		$locale = $_SESSION['locale'];
		return $locale;
	} else {
		return 'en_US';
	}
}