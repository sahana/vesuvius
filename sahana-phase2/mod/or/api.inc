<?php
/** API of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

/**
 * This returns the list of organizations
 * @param int $limit To limit the number of organizations returned
 * @access public
 * @return array
 */

function shn_or_organization_list($limit){
		
	    global $global;
	   	$db=$global['db'];
        
      	$q="select distinct o_uuid,name from  org_main where privacy=false";
        $res_org=$db->Execute($q);
        $org_list=array();
        
        while(!$res_org==NULL && !$res_org->EOF){
       		
        		$org_list[] = array('name' => $res_org->fields["name"], 'id' => $res_org->fields["o_uuid"]);
        		$res_org->MoveNext();
        }
       return $org_list;
}

/**
 * This returns the list of services organizations can offer
 * @access public
 * @return array
 */

function shn_or_service_list(){
	global $global;
	$q="select * from field_options where field_name='opt_sector_type'";
	$res = $global['db']->Execute($q);
    $service_list=array();
    while((!$res==NULL) && (!$res->EOF)) {
    	    $service_list[] = array('name' => $res->fields["option_description"], 'id' => $res->fields["option_code"]);
    		$res->MoveNext();
    }
    return $service_list;
}

/**
 * This returns the list of organization types , by which organizations are grouped
 * @access public
 * @return array
 */
 
function shn_or_type_list(){
	global $global;
	$q="select * from field_options where field_name='opt_org_type'";
	$res = $global['db']->Execute($q);
    $type_list=array();
    while((!$res==NULL) && (!$res->EOF)) {
    	    $type_list[] = array('name' => $res->fields["option_description"], 'id' => $res->fields["option_code"]);
    		$res->MoveNext();
    }
    return $type_list;
}

function shn_or_organization_name($org_id_arr){
	global $global;
	$db=$global['db'];
	$org_arr=array();
	foreach ($org_id_arr as $i){
		$q="select name from org_main where o_uuid='$i'";
		$res=$db->Execute($q);
		$org_arr[$i]=$res->fields["name"];
	}
	return $org_arr;
}



function shn_or_organization_search($incidents=null,$sectors=null,$types=null,$extra_opts=null){
	    global $global;
	   	include_once "lib_or.inc";
        $db=$global['db'];
        if($rootsonly==true){
        		$root=" and parent_id is NULL ";
        }else{
        		$root="";
        }
        if($sectors==null){
        		$sec_from="";
        		$sector_str="";
        }else{
        		 $sec_code=array();
        		 foreach ($sectors as $i){
        		 	$q="select option_code from field_options where option_description='$i'";
        		 	$res_sec=$db->Execute($q);
        		 	while(!$res_sec==NULL && !$res_sec->EOF){
     				array_push(
     						$sec_code,
     						$res_sec->fields["option_code"]
     						);
     				$res_sec->MoveNext();
        		 	}
        		 }
        		 
        		 $db_sectors=shn_or_create_database_IN_array($sec_code);	
        		 $sec_from="sector,";
        		 $sector_str="sector.opt_sector IN {$db_sectors} and  org_main.o_uuid=sector.pgoc_uuid and";
        }
       
        
		//$q="select distinct o_uuid from sector,org_main,resource_to_incident where sector.opt_sector='{$sector}' and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type='{$org_type}' and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
		$q="select distinct o_uuid,name from  $sec_from org_main where $sector_str privacy=false";
        
        //      if($incidents==null)
	//		$q = "select o_uuid,name from org_main where privacy=false".$root." order by o_uuid";
		//else
	
        $res_org=$db->Execute($q);
        $org_list=array();
        while(!$res_org==NULL && !$res_org->EOF){
        		$org_list[$res_org->fields["o_uuid"]]=$res_org->fields["name"];
        		$res_org->MoveNext();
        }

        return $org_list;
}





?>