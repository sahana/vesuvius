<?php
/* $Id: lib_st_help.inc,v 1.1 2006-05-04 12:29:31 janakawicks Exp $ */

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
    if(empty($_GET['help_id'])){
        echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
        foreach($_SESSION['form_help'] as $help_id => $value){
            echo "help_arr[".$help_id."] = \"$value\";\n";
        }
    }else{
        echo $_SESSION['form_help'][$_GET['help_id']];
    }
    
}

function shn_stream_close()
{

}
?>
