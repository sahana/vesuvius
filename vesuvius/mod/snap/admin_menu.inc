<?php
/**
 * Snapshot Module ~ Admin Menu
 *
 * @package	module
 * @subpackage	snap
 * @version	1.0
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**
 * Admin menu items to sit outside conventional modular admin
 */
function shn_snap_admin_menu() {
 	global $global;
 	include_once $global['approot']."/mod/snap/admin_menu_actions.inc";
	shn_sub_mod_menuitem("snap_show", _t("Snapshot"), 'admin');
}