<?php
/* $Id: conf.inc,v 1.6 2006-01-26 06:59:04 janakawicks Exp $ */

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
 * @global string $conf['mod_mpr_name']
 */
$conf['mod_mpr_name'] = _("Missing Person Registry");

/**
 * Sets the number of results shown in search query
 * @global string $conf['mod_mpr']['search']['limit']
 */
$conf['mod_mpr']['search']['limit'] = 5;

/**
 * Sets the upper limit of the location handler
 * @global string $conf['mod_mpr']['location']['upper_limit']
 */
$conf['mod_mpr']['location']['upper_limit'] = 1;

/**
 * Sets the lower limit of the location handler
 * @global string $conf['mod_mpr']['location']['lower_limit']
 */
$conf['mod_mpr']['location']['lower_limit'] = 4;

// $action_sequence => caption
$conf['mod_mpr']['edit']['tabs'] = array(_('Edit Details'), _('Add Tracker'), 
_('Upload Picture'), _('Confirm'));
?>
