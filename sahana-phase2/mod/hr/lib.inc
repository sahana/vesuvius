<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_hr_print_header($string=null)
{
        print '<h2>' . $string . '</h2>';
}


function shn_hr_get_loc_range()
{
    global $global;
    global $conf;
    $db=$global['db'];

    include_once $global['approot'].'/inc/lib_location.inc';
    
    $loc=array();
    $q="select value from config where module_id='or' and confkey='loc_range_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["start"]=$conf['mod_or_loc_level_start'];
    }else {
    	$loc["start"]=$res->fields[0];
    }
    $q="select value from config where module_id='or' and confkey='loc_range_end'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["end"]=$conf['mod_or_loc_level_end'];
    }else {
    	$loc["end"]=$res->fields[0];
    }
    return $loc;
}

function _shn_hr_get_start_loc()
{
    global $global;
    global $conf;
    $db=$global['db'];
    
    include_once $global['approot'].'/inc/lib_location.inc';
    
    $q="select value from config where module_id='or' and confkey='loc_start'";
    $res=$db->Execute($q);
    	if($res==NULL){
    		return NULL;
    }else{
    		return $res->fields["value"];
    }
}

function _shn_hr_location_string($loc)
{
	global $global;
	$db=$global["db"];
	
	include_once $global['approot'].'/inc/lib_location.inc';
	
	$loc_arr=array();
   	shn_get_parents($loc,&$loc_arr);
   	if($loc_arr[0]=='unknown'){
   		shn_form_label(_t("Organization Location"),"Unknown");
   	}else{
   		
   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="select name from location where loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location." -->".$res->Fields("name");
    			}
    			
   		}
   	}
   	return $location;
}


