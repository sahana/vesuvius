<?php

/** 
* Configuration information for help items in GPS / Markers
* Admins can set cutom text information for help items here
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Sriganeshan <sri@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package module
* @subpackage gis
*/


global $conf;
/**
 * Help item for Marker Name Detail Of Add Marker Form
 */
 $conf['mod_gps_marker_name_help']="Enter a short descriptive name to describe the marker";
 
 /**
  * Help item for Marker Detail
  */
 $conf['mod_gps_marker_type_help']="Select the type of the marker. This will be used " .
 		"in filtering";
  
  /**
  * Help Item for Marker author
  */
  $conf['mod_gps_marker_author_help']="Enter a name to be added as creator of this file ";
  /**
  * Help Item for File author
  */
$conf['mod_gps_file_author_help']="Enter the author of the above file or a corresponding individual's/team's name";
 /**
  * Help Item for Author name
  */
$conf['mod_gps_author_name_help']= "Enter the creator of the marker";
 /**
  * Help Item for Marker date
  */

$conf['mod_gps_marker_date_help']="Enter the date the marker was created";

