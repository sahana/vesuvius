<?php
/* $Id: lib_st_help.inc,v 1.3 2006-06-02 11:59:27 janakawicks Exp $ */

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

    if(empty($_GET['help_id'])){
        echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
        foreach($_SESSION['form_help'] as $help_id => $value){
            $clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
            echo "help_arr[".$help_id."] = \"$clean_value\";\n";
        }
    }else{
        echo $_SESSION['form_help'][$_GET['help_id']];
    }
    
}

function shn_stream_close()
{

}
?>
