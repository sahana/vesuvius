<?php

/**Admin Module for MapServer
*
* PHP version 5
* 
* @author       Hasitha Anjana <hasianjana@gmail.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @module      MapServer
* @version     $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

$conf['mod_ms_name'] = _("MapServer Configuration");
$conf['mod_ms_menuorder'] = 5;

/**
 * Basic configuration file for the map file generator.
 */

//  MapServer module needs configuring before it will operate
$conf['ms_configured'] = 0;

// These folders need to be writable by the webserver.
// These are relative to mod/ms/ 
$conf['ms_MAP_PATH'] = "maps/";
$conf['ms_SHAPE_PATH'] = "shapefiles/";
// This folder is from /www/ (needs to be accessible by browsers)
// Don't include a leading '/' to make the paths portable
$conf['ms_IMG_PATH'] = "res/img/maps";

// Path to MapServ CGI
$conf['ms_MAPSERV_CGI'] = "/var/www/cgi-bin/mapserv";

// Currently unused
$conf['ms_FONT_SET'] = "fontset.txt";

// Do not change this variable
$conf['ms_BASE_MAP'] = "TEMPLATE0.map";


