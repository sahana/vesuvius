<?php
/**
 * @name         browscap
 * @version      0.9
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0111
 */

global $global;
global $conf;

include_once $global['approot']."3rd/browsercaps/browscap.php";

// This stores the browser caps object in the $global variable under the key 'bcaps'
$bcaps = new Browscap($global['approot']."www/tmp/bcaps_cache");

// always update :)
$bcaps->doAutoUpdate = true;

$global['bcaps'] = $bcaps;

