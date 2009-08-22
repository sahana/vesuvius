<?php

/**
 * Lib for managing formats
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <hevayo@gmail.com>
 * @package    module
 * @subpackage die
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


function _shn_die_fetch_formats(){
    global $global;
    global $dieconf;

    $approot = $global['approot'];

    $d = dir($approot.'mod/rs/formats/');
    while (false !== ($f = $d->read())) {
        if (file_exists($approot.'mod/rs/formats/'.$f.'/conf.inc')) {
            include_once($approot.'mod/rs/formats/'.$f.'/conf.inc');
        }
    }
}


function _shn_die_get_applicable_formats($extention){
    global $dieconf;
    //select formats by extention
    foreach($dieconf['extentions'] as $format=>$exts)
        foreach($exts as $ext)
            if($extention==$ext)
                $applicable[]=$format;

    if(count($applicable)== 0)
        return false;
    else if(count($applicable)>1){
        //if there are more than one format apply confirm functions
        return $applicable;
    }
    else
        return $applicable[0];
    //retuen format list
}

