<?php
/**Internal Library of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/


function shn_or_service_list(){
	global $global;
	$q="select * from field_options where field_name='opt_sector_type'";
	$res = $global['db']->Execute($q);
    $service_arr=array();
    while((!$res==NULL) && (!$res->EOF)) {
    		array_push(
    			 $service_arr,
    			 $res->fields["option_description"]
    		);	
    		$res->MoveNext();
    }
    return $service_arr;
}


function shn_or_type_list(){
	global $global;
	$q="select * from field_options where field_name='opt_org_type'";
	$res = $global['db']->Execute($q);
    $type_arr=array();
    while((!$res==NULL) && (!$res->EOF)) {
    		array_push(
    			 $type_arr,
    			 $res->fields["option_description"]
    		);	
    		$res->MoveNext();
    }
    return $type_arr;
}
?>