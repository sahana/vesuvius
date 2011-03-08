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
 * Admin menu items to sit outside conventional modular admin
 */
function shn_snap_admin_menu() {
 	global $global;
 	include_once $global['approot']."/mod/snap/admin_menu_actions.inc";
	shn_sub_mod_menuitem("snap_show", _t("Snapshot"), 'admin');
}