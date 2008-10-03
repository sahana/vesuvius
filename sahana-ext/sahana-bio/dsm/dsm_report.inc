<?php 
/**Reports of the Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Hayesha Somarathne <hayeshais@gmail.com>
             
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage dsm
*/

global $global;
include_once $global['approot'] . "/inc/lib_location.inc";





//SELECT COUNT(*) AS rows FORM rtbs_h544 WHERE DATE_SUB(CURDATE(),INTERVAL DAYOFWEEK(CURDATE()) DAY) <= date " 


function _shn_dsm_get_date() {
    	global $global;
    	$db = $global["db"];
	$date = null;
		
	$sql= "SELECT date FROM rtbs_h544";
	$sql_date = $db->Execute($sql);
		
	while(!$sql_date == NULL && !$sql_date->EOF) {
		$date = $sql_date->fields['date'];
		$sql_date->MoveNext();
       	}

 return $date;
}

/*
function _shn_dsm_get_disease($disease) {
    	global $global;
    	$db = $global["db"];
		$disease_id = 0;
		
		$sql = "SELECT * FROM rtbs_disease WHERE disease_name={$disease}";
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF){
			$disease_id = $res->fields['disease_id'];
			$res->MoveNext();
		}
 return $disease_id;
}*/


function _shn_dsm_weekly_disease_count($disease) {
    	global $global;
    	$db = $global["db"];
		
		$date = _shn_dsm_get_date();
		
			$sql_disease_count = "SELECT COUNT(*) AS count FROM rtbs_h544 WHERE WEEKOFYEAR('{$date}') = WEEKOFYEAR(CURDATE()) AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name='{$disease}')"; 
			$res = $db->Execute($sql);
			
			$count = null;
			while(!$res == NULL && !$res->EOF){
				$count = $res->fields['count'];
				$res->MoveNext();
			}
			
 return $count;
}


function _shn_dsm_get_province() {
    	global $global;
    	$db = $global["db"];
		$province = array();
		
		$sql_province = "SELECT state FROM rtbs_location";
		$res_province = $db->Execute($sql_province);
		while(!$res_province == NULL && !$res_province->EOF){
			$province[$depth] = $res_province->fields['province'];
			$depth++;
			$res_province->MoveNext();
		}
 return $province;
}


function _shn_dsm_get_district() {
    	global $global;
    	$db = $global["db"];
		$depth = 0;
		$district = array();
		
		$sql_district = "SELECT city FROM rtbs_location";
		$res = $db->Execute($sql_district);
		while(!$res == NULL && !$res->EOF){
			$district[$depth] = $res->fields['district'];
			$depth++;
			$res->MoveNext();
		}
 return $district;
}

function _shn_dsm_get_moh_area() {
    	global $global;
    	$db = $global["db"];
		$moh_area = array();
		
		$sql_moh_area = "SELECT moh_area FROM rtbs_location";
		$res = $db->Execute($sql_moh_area);
		while(!$res == NULL && !$res->EOF){
			$moh_area[$depth] = $res->fields['moh_area'];
			$depth++;
			$res->MoveNext();
		}
 return $moh_area;
}


function _shn_dsm_get_rdhs_div() {
    	global $global;
    	$db = $global["db"];
		$rdhs_div = array();
		
		$sql_rdhs_div = "SELECT rdhs_div FROM rtbs_location";
		$res = $db->Execute($sql_rdhs_div);
		while(!$res == NULL && !$res->EOF){
			$rdhs_div[$depth] = $res->fields['rdhs_div'];
			$depth++;
			$res->MoveNext();
		}
 return $rdhs_div;
}




function _shn_dsm_header_validate()
{
    if($_POST['province']=='' ){
        add_error('Select the Province is required');
        return false;
    }
	if ($_POST['district']==''){
        add_error('Select the District is required');
        return false;
	}
    if($_POST['moh_area']=='' ){
        add_error('Select the M.O.H. Area');
        return false;
    }
	if ($_POST['rdhs_div']==''){
        add_error('Select R.D.H.S. Div');
        return false;
	}	

    return true;
}
?>