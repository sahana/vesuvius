<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Isuru Samaraweera <isuru@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


?><div id="home_recent"><h1><?php echo  _t('Found People'); ?></h1><?php

global $global;
global $conf;
require ($global['approot'] . 'mod/mpr/mpr_lib.inc');

$limit = $conf['mod_mpr_pictures_per_page'];
$type = "found";

$offset = 0;
$found = shn_mpr_home_show_mpr($type, $limit, $offset);
_shn_mpr_listing($found);
print '<BR/><BR/>';

?><input type="button"  value="Print Current Page" onClick="self.print()" class="hideprint"/></div><?php