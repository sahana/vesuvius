<?
/**
 * @name         Gettext Handler
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
 * Dummy function to emulate the gettext() function when gettext is not installed
 * This will be replaced by a pure PHP gettext library
 *
 * @param string $string
 * @access public
 * @return string
 */
function gettext($string) {
	return $string;
}



/**
 * Dummy function to emulate the _t() function when gettext is not installed
 * This will be replaced by a pure PHP gettext library
 *
 * @param mixed $string
 * @access protected
 * @return void
 */
function _t($string) {
	return $string;
}



