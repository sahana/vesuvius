<?php
/**
 * @name         Person Finder Interchange Format
 * @version      0.1
 * @package      pfif
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0622
 */


/**
 * stream some text...
 * @access public
 * @return string
 */
function shn_text_pfif_default() {
	echo "text";
}


/**
 * stream some text...
 * @access public
 * @return string
 */
function shn_xml_pfif_default() {
	echo '<description>test</description>';
}
