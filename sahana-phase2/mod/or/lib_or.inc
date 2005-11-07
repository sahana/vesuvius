<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/




function shn_or_district_villages($bsd_district){
global $global;
$db=$global["db"];

	$q="select location_id,name from location where parent_id={$bsd_district}";
        $res_tmp=$db->Execute($q);
        $k=0;
    
        while ((!$res_tmp==NULL)&&(!$res_tmp->EOF)){
	        $loc=$loc."{$res_tmp->fields[0]}";
            $res_tmp->MoveNext();
            if(!$res_tmp->EOF)
                $loc=$loc.",";
	}

return $loc;

}


function shn_or_province_villages($bsd_province){
global $global;
$db=$global["db"];

	$q="select location_id,name from location where parent_id={$bsd_province}";
        $res_tmp=$db->Execute($q);
        $k=0;
       
        while ((!$res_tmp==NULL)&&(!$res_tmp->EOF)){
	        $loc=$loc.shn_or_district_villages($res_tmp->fields[0]);
            $res_tmp->MoveNext();

	}

return $loc;

}
