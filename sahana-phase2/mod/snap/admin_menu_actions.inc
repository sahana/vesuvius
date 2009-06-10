<?php
/**
 * Snapshot Module ~ Admin Menu Actions
 *
 * @package	module
 * @subpackage	snap
 * @version	1.0
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
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