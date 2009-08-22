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

/*
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
        default:
            add_error(_t("Extention is not a valied Sahana dump file extention."));
            add_error($error);
            throw new Exception($error);
    }
*/
    $ext=end(explode('.',$_SESSION['fileinfo']['name']));
    switch($ext){
        case 'gz':
            if(!function_exists('gzopen')){
                add_error(_t("Missing Zlib extension on the server : Unable to process file."));
                throw new Exception($error);
            }
            $file_open='gzopen';
            $read='gzread';
            $file_close='gzclose';
        break;
        case 'bz2':
            if(!function_exists('bzopen')){
                add_error(_t("Missing Bzip2 extension on the server : Unable to process file."));
                throw new Exception($error);
            }
            $file_open='bzopen';
            $read='bzread';
            $file_close='bzclose';
        break;
        case 'xml':
            $file_open='fopen';
            $read='fread';
            $file_close='fclose';
        break;
        default:
            add_error(_t("Extention is not a valied Sahana dump file extention."));
            throw new Exception($error);
    }
