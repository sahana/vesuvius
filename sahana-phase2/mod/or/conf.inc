<?php
/**This is the config file for the OR module, specifies configuration
*  settings
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

// provide the nice display name for the OR  module
$conf['mod_or_name'] = _t("Organization Registry");
$conf['mod_or_menuorder'] = 4; 
//set start_loc to -1 if you want all the locations
$conf['mod_or_start_loc'] = 1;
$conf['mod_or_loc_level_start']=1;
$conf['mod_or_loc_level_end']=3;

$conf['mod_or_dependencies'] = "";



