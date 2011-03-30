<?
/**
 * @name         Login Handler
 * @version      1.0
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



global $conf;
global $global;



if ($_SESSION['logged_in'] == true ) {
	echo "
		<div id=\"loginform\">
			<a href=\"index.php?mod=pref&act=default\">My Settings</a> | <a href=\"index.php?mod=pref&act=logout\">Logout</a>
		</div>
	";
} else {
	echo "
		<div id=\"loginform\">
			<a href=\"index.php?mod=pref&act=loginForm\">Login / Register</a>
		</div>
	";
}
