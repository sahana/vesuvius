<?
/**
 * @name         Snapshot
 * @version      1.1
 * @package      snap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


/**
 * Front controller function to handle plugin architecture
 */
function shn_admin_snap_show() {
	global $global;
	global $conf;
	include_once ($global['approot'].'/mod/snap/admin_functions.inc');
	shn_snap_admin_default();
}