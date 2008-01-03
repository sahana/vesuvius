<?php
/** 
* Configuration information for help items in GIS / Wikimaps
* Admins can set cutom text information for help items here
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package module
* @subpackage gis
*/


global $conf;
/**
 * Help item for Situation Name Detail Of Add Situation Form
 */
 $conf['mod_gis_situation_name_help']=_("Enter a short descriptive name to describe the situation");
 
 /**
  * Help item for Situation Detail
  */
 $conf['mod_gis_situation_type_help']=_("Select the type of the situation. This will be used in filtering.");
 
 /**
  * Help Item for situation URL
  */
  $conf['mod_gis_situation_url_help']=_("You can provide a URL of a website or a wiki site for more information");
  
  /**
  * Help Item for situation author
  */
  $conf['mod_gis_situation_author_help']=_("If a name is provided here, it will be publicly displayed with the other information. If this is left blank, it would show up as anonymous");
  
  /**
  * Help Item for situation date
  */
  $conf['mod_gis_situation_date_help']=_("Enter the date of the situation event");
?>
