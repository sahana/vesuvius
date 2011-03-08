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


global $global;


$conf['mod_snap_name']         = "Snapshot";
$conf['mod_snap_dependencies'] = "admin(1.0)";
$conf['mod_mpr_version']       = "1.1";

// Folder location to store .sql backups (snapshots)
$conf['mod_snap_storage_location'] = $global['approot'].'backups/';