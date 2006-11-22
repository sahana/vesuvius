<?php
/**
 * This handler will decompress the upload file
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

switch($_SESSION['fileinfo']['type']){
    case 'application/x-gzip':
        $file_open='gzopen';
        $read='gzread';
        $file_close='gzclose';
    break;
    case 'application/x-bzip':
        $file_open='bzopen';
        $read='bzread';
        $file_close='bzclose';
    break;
    case 'text/xml':
        $file_open='fopen';
        $read='fread';
        $file_close='fclose';
    break;
}

?>