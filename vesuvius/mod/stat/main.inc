<?php
/**
 * @name         Statistics
 * @version      0.1
 * @package      stat
 * @author       Lan Ngoc Le <lale@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0711
 */


global $global;
global $conf;
require_once($global['approot'].'/mod/stat/lib_stat.inc');


function shn_stat_menu() {
	global $global;
	echo "
		<script>".file_get_contents($global['approot']."/mod/stat/stat.js")."</script>
		<ul>
			<li><a href=\"index.php?mod=stat\">World</a></li>
			<li><a href=\"index.php?mod=stat&act=galaxy\">Galaxy</a></li>
			<li><a href=\"index.php?mod=stat&act=universe\">Universe</a></li>
		</ul>
		<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">
	";
}


/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_stat_default() {
	global $global;
	shn_stat_menu();
	echo "hello world!";
}


/**
 * the galaxy action!
 * @access public
 * @return void
 */
function shn_stat_galaxy() {
	global $global;
	shn_stat_menu();
	echo "hello galaxy!";
	echo "<script>call_hello();</script>";
}



/**
 * the universe action!
 * @access public
 * @return void
 */
function shn_stat_universe() {
	global $global;
	shn_stat_menu();
	echo "hello universe!";
}





