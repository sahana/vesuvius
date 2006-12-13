<?php
/* $Id: [sahana_home]/mod/vm/vol_locate.inc,v 1.0 2006/06/19  */
/**
 *
 * Volunteer Management Module -- volunteer mapping functions.
 *
 * <p>This file is part of the Volunteer Management module. It includes functions that are used
 * for google maps mapping for specific volunteers or all volunteers.  Include when VM related maps
 * are required.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 *
 */

/** Contains utility functions for use with VM and VR modules */
include_once $global['approot']."/mod/vm/utility_functions.inc";

/**
 * Retrieves the GPS coordinates for all volunteers, and maps them to the google maps api frame.
 * 
 * Performs a DB query of the <b>person_uuid</b>, <b>location</b>, and <b>location_details</b> tables given the project's id.
 *
 * @param string  $no Null, or no matter
 * @access public
 * @return void
 */
function _shn_vm_vol_locate_all($no=NULL)
{
    global $global;
    $db=$global['db'];
 
    $q = "select value from config where confkey = 'google_key'";
    $result=$db->Execute($q);
    $gmap_key=$result->fields[0];
       
    ?>
	<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $gmap_key?>" type="text/javascript"></script>


	<div id="map" style="width: 600px; height: 600px"></div>
	  <script type="text/javascript">
       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch

		//hard coded default frame to map all projects
		map.centerAndZoom(new GPoint(-94.00, 39.00), 13);

		//made a marker making function for use below
		function createMarker(point, message) {
  			var marker = new GMarker(point);
			GEvent.addListener(marker, 'click', function() {
				marker.openInfoWindowHtml(message);
			});
			return marker;
		}
		
	<?php

	//query all volunteers
		$q = "select p_uuid, poc_uuid, location_id, full_name, address from person_uuid, location_details where p_uuid = poc_uuid";
		$res_vol=$db->Execute($q);
		while(!$res_vol->EOF){
			$person=$res_vol->fields[0];
        		$location_id=$res_vol->fields[2]; 
        		$fullname=$res_vol->fields[3]; 
        		$address=$res_vol->fields[4]; 
			
			//make a link with project_id in the url, to go to the project details page
			//$message = "<a href=\"index.php?mod=vm&act=proj_detail&project=" . $res_proj->fields[4] . "\">" . $res_proj->fields[1] . "</a><br>Start Date: " . $res_proj->fields[2] . "<br>End Date: " . $res_proj->fields[3];

			$message = "<div>" . $fullname . "<br>" . $address . "<br>" . get_personal_location_string($person) . "</div>";
			
			//query gps data for the location
			$q = "select map_northing, map_easting from gis_location where location_id = '${location_id}'";
    			$result=$db->Execute($q);
    			$longitude=$result->fields[0];
    			$latitude=$result->fields[1];

			?>
			<!--make the marker w/ message-->
			map.addOverlay(createMarker(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>), '<?php echo $message?>'));
			<?php
					
        		$res_vol->MoveNext();
		}
    			
	?>

	   </script>	
    <?php
}

/**
 * Retrieves the volunteer_id from _Post data, queries the corresponding GPS coordinates, and maps the volunteer
 * to the google maps api frame.
 * 
 * Performs a DB query of the <b>person_uuid</b>, <b>location</b>, and <b>location_details</b> tables given the project's id.
 *
 * @param string  $no Null, or no matter
 * @access public
 * @return void
 */
function _shn_vm_vol_locate($no=NULL)
{
    global $global;
    $db=$global['db'];
 
    $volunteer_id = $_GET['volunteer'];
 
    $q = "select value from config where confkey = 'google_key'";
    $result=$db->Execute($q);
    $gmap_key=$result->fields[0];
       
    ?>
	<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $gmap_key?>" type="text/javascript"></script>


	<div id="map" style="width: 600px; height: 600px"></div>
	  <script type="text/javascript">
       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch

		//hard coded default frame to map all projects
		map.centerAndZoom(new GPoint(-76.00, 40.00), 12);

		//made a marker making function for use below
		function createMarker(point, message) {
  			var marker = new GMarker(point);
			GEvent.addListener(marker, 'click', function() {
				marker.openInfoWindowHtml(message);
			});
			return marker;
		}
		
	<?php

	//query the volunteers
		$q = "select p_uuid, poc_uuid, location_id, full_name, address from person_uuid, location_details where p_uuid = poc_uuid and p_uuid = '${volunteer_id}'";
		$result=$db->Execute($q);
		$location_id=$result->fields[2]; 
        	$fullname=$result->fields[3]; 
        	$address=$result->fields[4]; 
			
		$message = "<div>" . $fullname . "<br>" . $address . "<br>" . get_personal_location_string($volunteer_id) . "</div>";
			
			//query gps data for the location
			$q = "select map_northing, map_easting from gis_location where location_id = '${location_id}'";
    			$result=$db->Execute($q);
    			$longitude=$result->fields[0];
    			$latitude=$result->fields[1];

			?>
			//make the marker w/ message
		map.centerAndZoom(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>), 5);

			map.addOverlay(createMarker(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>), '<?php echo $message?>'));
			<?php
					
        			
    			
	?>

	   </script>	
    <?php
}


?>

