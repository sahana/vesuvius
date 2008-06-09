<?php

include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
include_once 'lib_pre.inc';

function _shn_pre_show_area($area_uuid){
	_shn_pre_print_header("Map view");
	global $global;
	$sql = "SELECT map_northing, map_easting, area FROM gis_location AS g, pre_threat_area AS a WHERE a.area_uuid = g.poc_uuid AND a.area_uuid = '$area_uuid' ";
	$res = $global['db']->Execute($sql);	
	if($res->RecordCount() > 0){
		$map_array = array();
		$area_url='mod=pre&act=list_threat_area&seq=list&area='.$area_uuid;
        array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['area'],
					"id"=>$area_uuid,"url"=>$area_url));
	}
	shn_gis_map_with_markers($map_array);
}

function _shn_pre_show__shelter_area($area_uuid){
	_shn_pre_print_header("Map view");
	global $global;
	$sql = "SELECT map_northing, map_easting, area FROM gis_location AS g, pre_shelter_area AS a WHERE a.area_uuid = g.poc_uuid AND a.area_uuid = '$area_uuid' ";
	$res = $global['db']->Execute($sql);	
	if($res->RecordCount() > 0){
		$map_array = array();
		$area_url='mod=pre&act=list_shelter_area&seq=list&area='.$area_uuid;
        array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['area'],
					"id"=>$area_uuid,"url"=>$area_url));
	}
	shn_gis_map_with_markers($map_array);
}

?>