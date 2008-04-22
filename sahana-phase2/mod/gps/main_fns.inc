<?php

/**
* Functions page of the GPS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package module
* @subpackage gps
* @author     sri <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_gps_default()
{
    global $conf;
?>
<div id="home">
<h2><?=$conf['mod_gps_name']?></h2>
<ul>
	<li><?=_("The {$conf['mod_gps_name']} module provides functions to upload and download GPS data, such as waypoints and routes.");?></li>
	<li><?php echo _('The data is imported/exported via GPX files which can be transferred to/from a GPS device using, e.g. <a href="http://www.gpsbabel.org/">GPSBabel</a>.');?></li>
</div>
<?php
}

?>
