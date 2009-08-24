<?php
/**This is the config file for the IMS module, specifies configuration
*  settings
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

// provide the nice display name for the OR  module
global $conf;
$conf['mod_ims_name'] = _t("Inventory Management");
$conf['mod_ims_menuorder'] = 16;
//set start_loc to -1 if you want all the locations
//$conf['mod_or_ims_start_loc'] = 1;
//$conf['mod_or_ims_loc_level_start']=1;
//$conf['mod_or_ims_loc_level_end']=3;

$conf['mod_ims_dependencies'] = "";


?>