<?php
/**
 * This handler will compress the ump file
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

$tmp_file = tempnam("/tmp", "shn");
$tmp_file=$tmp_file.$_POST['compression'];
switch($_POST['compression']){
    case 'none':
        $file_open='fopen';
        $write='fwrite';
        $file_close='fclose';
        $com="";
    break;
    case 'gz':
        $file_open='gzopen';
        $write='gzwrite';
        $file_close='gzclose';
        $com=".gz";
    break;
    case 'bz2':
        $file_open='bzopen';
        $write='bzwrite';
        $file_close='bzclose';
        $com=".bz2";
    break;
    case 'zip':

    break;
}

shn_sync_dump_xml($tables,$tmp_file,$file_open,$file_close,$write)
