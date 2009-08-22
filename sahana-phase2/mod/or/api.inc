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
 * Edited by	H. Iroshan on 2009/07/01
 * 
 * if functions  returns array  types, in order to automate the
 * Aggregator Mashup portal it is important to have  common 
 * Standard to return types of web services functions. 
 *
 * If the return type of a web service function is a array this array should   
 * be in this format. 
 *
 * First element of the array should be the the field names
 ** Ex :-
 ***** $catalog_list[] = array("ct_uuid","parentid","name");
 * 
 *Return array should be return its values according to the following mechanism
 ** Ex :- 
 ***** array($res->fields["ct_uuid"], $res->fields["parentid"],$res->fields["name"]);
 *
 *Therefore I have modified these functions 
 *** shn_or_service_list,
 *** shn_or_type_list, 
 */



/**
 * This returns the list of organizations
 * @param int $limit To limit the number of organizations returned
 * @access public
 * @return array
 */
include_once "lib_or.inc";

function shn_or_organization_list($limit=null,$name_filter='',$type_filter='all',$service_filter='all',$location_filter=-1,$address_filter='')
{
	    global $global;
	   	$db=$global['db'];
		$id_list=shn_or_org_search($limit,$name_filter,$type_filter,$service_filter,$location_filter,$address_filter);
        $org_name_list=shn_or_organization_name($id_list);
        
        foreach($org_name_list as $org_id=>$org_name){
       			$org_list[] = array('name' => $org_name, 'id' =>$org_id);
        }
        
        return $org_list;
}

/**
 * This returns the list of services organizations can offer
 * @access public
 * @return array
 */

function shn_or_service_list()
{
	global $global;
	$q="SELECT * FROM field_options WHERE field_name='opt_sector_type'";
	$res = $global['db']->Execute($q);
    $service_list[] = array("option_description","option_code");
    while((!$res==NULL) && (!$res->EOF)) {
    	    $service_list[] = array($res->fields["option_description"],$res->fields["option_code"]);
    		$res->MoveNext();
    }
    return $service_list;
}

/**
 * This returns the list of organization types , by which organizations are grouped
 * @access public
 * @return array
 */
 
function shn_or_type_list($limit=null,$filter=null){
	global $global;
	$q="SELECT * FROM field_options WHERE field_name='opt_org_type'";
	$db=$global['db'];
	if($limit==null){
		 $res = $db->Execute($q);
	}else{
		$res=$db->SelectLimit($q,$limit);
	}
    $type_list[] = array("option_description","option_code");
    while((!$res==NULL) && (!$res->EOF)) {
    	    $type_list[] = array($res->fields["option_description"],$res->fields["option_code"]);
    		$res->MoveNext();
    }
    return $type_list;
}

function shn_or_organization_name($org_id_arr){
	global $global;
	$db=$global['db'];
	$org_arr=array();
	foreach ($org_id_arr as $i){
		$q="SELECT name FROM org_main WHERE o_uuid='$i'";
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
                $q="SELECT option_code FROM field_options WHERE option_description='$i'";
        		$res_sec=$db->Execute($q);
        		while(!$res_sec==NULL && !$res_sec->EOF){
     				array_push($sec_code, $res_sec->fields["option_code"]);
     				$res_sec->MoveNext();
        		 	}
        		 }
        		 
        		 $db_sectors=shn_or_create_database_IN_array($sec_code);	
        		 $sec_from="sector,";
        		 $sector_str="sector.opt_sector IN {$db_sectors} and org_main.o_uuid=sector.pgoc_uuid and";
        }
       
        
		//$q="select distinct o_uuid from sector,org_main,resource_to_incident where sector.opt_sector='{$sector}' and org_main.o_uuid=sector.pgoc_uuid and org_main.opt_org_type='{$org_type}' and resource_to_incident.incident_id in $inci and resource_to_incident.x_uuid=org_main.o_uuid";
		$q="SELECT DISTINCT o_uuid,name FROM  $sec_from org_main WHERE $sector_str privacy=false";
        
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





