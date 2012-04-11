<?
/**
 * @name         Snapshot
 * @version      12
 * @package      snap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */


global $global;

$conf['mod_snap_name']             = "Snapshot";
$conf['mod_mpr_version']           = "12";

// Folder location to store .sql backups (snapshots)
$conf['mod_snap_storage_location'] = $global['approot'].'backups/';
