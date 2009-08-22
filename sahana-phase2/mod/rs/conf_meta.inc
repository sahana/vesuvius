<?php
/**
 * Main Configuration Metadata of the Reporting System. 
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue <ravithb@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

$conf['mod_rs_name'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>_t("Reporting System"));
$conf['mod_rs_menuorder'] = array('type'=>'integer','allow_null'=>false,'default_value'=>19);
$conf['mod_rs_dependencies'] = "";
$conf['mod_rs_chart_update_interval'] = array('type'=>'integer','allow_null'=>false,'min_value'=>0,'default_value'=>19);
