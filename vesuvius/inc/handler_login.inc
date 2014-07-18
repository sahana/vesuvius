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
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



global $conf;
global $global;



if ($_SESSION['logged_in'] == true ) {
	echo "
		<div id=\"loginform\">
			<a href=\"settings\">My Settings</a> <span style=\"color: #e5eaef;\">&nbsp;|&nbsp;</span> <a href=\"logout\">Logout</a>
		</div>
	";
} else {
	echo "
		<div id=\"loginform\">
			<a href=\"login\">Login or Register</a>
		</div>
	";
}
