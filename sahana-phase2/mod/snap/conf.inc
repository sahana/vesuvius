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

// Gives the nice name of the module
$conf['mod_snap_name'] = "Snapshot";

// Gives the priority order in the main menu when listed
$conf['mod_snap_dependencies'] = "admin";

// Folder location to store .sql backups (snapshots)
$conf['mod_snap_storage_location'] = $global['approot'].'backups/';