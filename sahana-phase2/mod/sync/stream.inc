<?php
/**
 * 
 * Functions used by the Stream controler 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Priyanga Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/* {{{ Search Form */
/**
 * Table Data download function
 * 
 * @access public
 * @return void
 */
function shn_sync_download(){
    switch ($_GET['stream_type']){
        case 'soap' :
            return '';
        break;

        case 'xml' :
            global $global;
            require($global['approot'].'mod/sync/down.inc');
            foreach($_POST as $mod){
                $sync_down = 'shn_sync_dump_'.$mod;
                if (function_exists($sync_down))
                {
                    $sync_down();
                }
            }
	break;
        default:
            return '';
        break;
    }
}
?>
