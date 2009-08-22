<?php
function _shn_itag_get_all_maps(){
	global $global;
    $db=$global["db"];
    $sql="select * from maps,media where maps.map_uuid=media.x_uuid and media.category='jpeg_maps'";
    $res=$db->Execute($sql);
    $maps=array();
    while((!$res==NULL) && (!$res->EOF)) {
    	    $maps[$res->fields["map_uuid"]] = array('name' => $res->fields["name"], 'desc' => $res->fields["description"],'media_id' => $res->fields["media_id"]);
    		$res->MoveNext();
    }
    return $maps;
}

function _shn_itag_get_map_details($id){
	global $global;
    $db=$global["db"];
    $sql="select * from maps,media where maps.map_uuid=media.x_uuid and media.category='jpeg_maps' and map_uuid='{$id}'";
  
    $res=$db->Execute($sql);
   
    if((!$res==NULL) && (!$res->EOF)) {
    	    return array('name' => $res->fields["name"], 'desc' => $res->fields["description"],'media_id' => $res->fields["media_id"],'width' => $res->fields["width"],'height' => $res->fields["height"]);
    		//$res->MoveNext();
    }
    
}

function _shn_itag_get_map_points($id){
	global $global;
    $db=$global["db"];
    $sql="select * from map_points where map_uuid='{$id}'";
    $res=$db->Execute($sql);
    $points=array();
    while((!$res==NULL) && (!$res->EOF)) {
    	    $points[$res->fields["point_uuid"]] = array('name' => $res->fields["name"], 'desc' => $res->fields["description"],'lat' => $res->fields["latitude"],'long' => $res->fields["longitude"]);
    		$res->MoveNext();
    }
    return $points;
    
}

function _shn_itag_display_marked_map($map_id){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	$details=_shn_itag_get_map_details($map_id);
	$points=_shn_itag_get_map_points($map_id);
	$url=shn_media_get_url($details["media_id"]);
	$info = getimagesize($url);
    //check the image type 
    if(! $info){
      //  add_error(_("Invalid Image Type Please try again"));
        return false;    
    }else{
    	 $width_orig = $info[0];
   		$height_orig = $info[1];
   		list($ignore,$mime) = split("\/",$info['mime']);
    	 //$mime = $_FILES[$media]["name"]['image_type'];
    }

    switch($mime=="png"){
    	case "png":
    		    
    			$image = imagecreatefrompng($url);
    			$red = imagecolorallocate ($image, 255,0,0);
				$scale_x = imagesx($image);
				$scale_y = imagesy($image);
				$box_width=(1*$scale_x) /310;
				$box_height=(1*$scale_y) /155;
				
				foreach($points as $point_id=>$point_details)
					{
					
						
					// $pt = getlocationcoords($co[0], $co[1], $scale_x, $scale_y);
					   $pt["x"]=$point_details["long"];
					 //file_put_contents("/tmp/a.txt",$pt["x"]);
					   $pt["y"]=$point_details["lat"];
					  $pt["x"]=$pt["y"]=20;
					   imagefilledrectangle($image,$pt["x"]-$box_width,
					                         $pt["y"]-$box_height,$pt["x"]+$box_width,$pt["y"]+$box_height,$red);
					}
					imagepng($image);
				break;
		default:
				$image = imagecreatefromjpeg($url);
    			$red = imagecolorallocate ($image, 255,0,0);
				$scale_x = imagesx($image);
				$scale_y = imagesy($image);
				$box_width=(1*$scale_x) /310;
				$box_height=(1*$scale_y) /155;
				foreach($points as $point_id=>$point_details)
					{
					
						
					// $pt = getlocationcoords($co[0], $co[1], $scale_x, $scale_y);
					   $pt["x"]=$point_details["long"];
					
					   $pt["y"]=$point_details["lat"];
					  //$pt["x"]=$pt["y"]=20;
					    imagefilledrectangle($image,$pt["x"]-$box_width,
					                         $pt["y"]-$box_height,$pt["x"]+$box_width,$pt["y"]+$box_height,$red);
					}
					imagejpeg($image);
				break;
    }
}
