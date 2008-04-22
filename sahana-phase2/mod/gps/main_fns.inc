<?php
/**
* Functions page of the GIS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package module
* @subpackage gps
* @author   sri <sri@opensource.lk>
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
	<li><?=_("The  {$conf['mod_gps_name']} module provides GPS and Spatial functionalities to indirectly interact with GPS devices.");?></li>
	<li><?php echo _('It also allows users to upload and download GPS data; such as waypoints and routes');?></li>
	<li><?php echo _('This module allows users to dynamically create and download markers using maps and also acts as a library providing GPS and spatial functionalities to other sahana modules');?></li>
</div>
<?php
}

?>
