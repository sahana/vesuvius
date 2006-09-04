<?php
/* $Id: lib_stream_text.inc,v 1.1 2006-09-04 04:52:43 janakawicks Exp $ */

/**
 *
 * Streaming Help Library
 *
 * PHP version 4 and 5
 * 
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

function shn_stream_init()
{
    //for install hack
    $my_approot = realpath(dirname(__FILE__)).'/../';
    if(!file_exists($my_approot.'conf/sysconf.inc')){
        session_start();
    }
    //install hack ends
}

function shn_stream_close()
{

}
?>
