<?php

include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
include_once 'lib_pre.inc';
include_once 'lib_pre_frm.inc';

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

function _shn_pre_gis_disaster_report($duuid){
	global $global;
	$sql1 = "SELECT map_northing, map_easting, area, a.area_uuid FROM gis_location AS g, pre_threat_area AS a WHERE a.area_uuid = g.poc_uuid AND a.area_uuid IN " .
			"(SELECT area_uuid FROM pre_threat_area_disaster WHERE disaster_uuid = '$duuid')";
	$res1 = $global['db']->Execute($sql1);
	$sql2 = "SELECT map_northing, map_easting, area, a.area_uuid FROM gis_location AS g, pre_shelter_area AS a WHERE a.area_uuid = g.poc_uuid AND a.area_uuid IN " .
			"(SELECT area_uuid FROM pre_shelter_disaster WHERE disaster_uuid = '$duuid')";
	$res2 = $global['db']->Execute($sql2);
	if($res1->RecordCount() > 0 || $res2->RecordCount() > 0){
		$map_array = array();
		for($i = 0; $i < $res1->RecordCount(); $i++){
			$area_url = 'mod=pre&act=list_threat_area&seq=list&area='.$res1->fields['area_uuid'];
			array_push($map_array, array("lat"=>$res1->fields['map_northing'], 'lon'=>$res1->fields['map_easting'],"name"=>$res1->fields['area'],"id"=>$res1->fields['area_uuid'], 'marker'=>'marker'));
			$res1->MoveNext();
		}
		for($i = 0; $i < $res2->RecordCount(); $i++){
			$area_url = 'mod=pre&act=list_shelter_area&seq=list&area='.$res2->fields['area_uuid'];
			array_push($map_array, array("lat"=>$res2->fields['map_northing'], 'lon'=>$res2->fields['map_easting'],"name"=>$res2->fields['area'],"id"=>$res2->fields['area_uuid'], 'marker'=>'marker_r3'));
			$res2->MoveNext();
		}
		//shn_gis_map_with_markers($map_array);
		shn_gis_density_map($map_array);
	}
	else{
		_shn_pre_print_alert('No record for this disaster');
	}
}



