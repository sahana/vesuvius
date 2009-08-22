<?php
/* $Id: conf.inc,v 1.5 2009-08-22 17:17:23 ravithb Exp $ */

/**
 * Main Configuration of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Gives the nice name of the module
 * @global string $conf['mod_sync_name']
 */
$conf['mod_sync_name'] = _t("Synchronization");
$conf['mod_sync_menuorder'] = 19; 

$conf['mod_sync_dependencies'] = "";

