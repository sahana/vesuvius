<?php
/**
 * This is the main file for the Sahana module. Once the module is selected in the 
 * post all actions are passed to this file for processing.
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Ishan Liyanage <ishanul@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage xst (Extensible Streaming)
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once "handler_location.inc";
include_once "handler_catalog.inc";


 function shn_text_xst_get_loc(){
     shn_location_get_loc();
 }
 function shn_text_xst_get_loc_val(){
 	_shn_get_locations();
 }
 function shn_text_xst_sub_cat(){
 	shn_text_catalog_sub_cat();
 }
 function shn_text_xst_help()
{
    if(empty($_GET['help_id'])){
        echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
        if(isset($_SESSION['form_help']))
            foreach($_SESSION['form_help'] as $help_id => $value){
                $clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
                echo "help_arr[".$help_id."] = \"$clean_value\";\n";
            }
    }else{
        echo $_SESSION['form_help'][$_GET['help_id']];
    }
}
 
 ?>