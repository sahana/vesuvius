<?php
/**
 * This is the conf file for the Snapshot module.
 *
 * @package	module
 * @subpackage	snap
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

global $global;


$conf['mod_snap_name']         = "Snapshot";
$conf['mod_snap_dependencies'] = "admin(1.0)";
$conf['mod_mpr_version']       = 1.0;

// Folder location to store .sql backups (snapshots)
$conf['mod_snap_storage_location'] = $global['approot'].'backups/';