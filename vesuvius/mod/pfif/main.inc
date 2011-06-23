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


global $global;
global $conf;
require_once($global['approot'].'/mod/pfif/lib_pfif.inc');


function shn_pfif_menu() {
	echo "
		<ul>
			<li><a href=\"index.php?mod=pfif\">World</a></li>
			<li><a href=\"index.php?mod=pfif&act=galaxy\">Galaxy</a></li>
			<li><a href=\"index.php?mod=pfif&act=universe\">Universe</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
	";
}


/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_pfif_default() {
	global $global;
	shn_pfif_menu();
	echo "hello world!";
}


/**
 * the galaxy action!
 * @access public
 * @return void
 */
function shn_pfif_galaxy() {
	global $global;
	shn_pfif_menu();
	echo "hello galaxy!";
}



/**
 * the universe action!
 * @access public
 * @return void
 */
function shn_pfif_universe() {
	global $global;
	shn_pfif_menu();
	echo "hello universe!";
}