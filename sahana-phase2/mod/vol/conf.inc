<?php
/**This is the config file for the VOLUNTEER module, specifies configuration
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
* @subpackage vol
*/

// provide the nice display name for the OR  module
global $conf;
$conf['mod_vol_name'] = _t("Volunteer Coordination");
$conf['mod_vol_start_loc'] = 1;
$conf['mod_vol_loc_level_start']=1;
$conf['mod_vol_loc_level_end']=4;

#$conf['mod_vol']['upload_picture']['savehandler'] = 'database';
//$conf['mod_mpr']['upload_picture']['savehandler'] = 'file';
$conf['mod_mpr_upload_picture_savehandler'] = 'file';
$conf['mod_vol_upload_pic_handler'] = 'file';
$conf['mod_vol_dependencies'] = "";

