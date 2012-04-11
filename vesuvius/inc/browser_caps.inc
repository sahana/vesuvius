<?
/**
 * @name         Browser CAPS Handler
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
global $conf;

include_once $global['approot']."3rd/browsercaps/browscap.php";

// This stores the browser caps object in the $global variable under the key 'bcaps'
$bcaps = new Browscap($global['approot']."www/tmp/bcaps_cache");

// always update :)
$bcaps->doAutoUpdate = true;

$global['bcaps'] = $bcaps;

