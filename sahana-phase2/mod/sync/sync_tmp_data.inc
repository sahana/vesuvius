<?php
/**
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once('lib_sync.inc');
//loop through tables
foreach($_SESSION['sync']['tables'] as $table){
//read the sync.xml file
//get the nessary function or the handeler
    shn_sync_merge($table);
//mearge data
}

//
?>