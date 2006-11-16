<?php
/* $Id: [sahana_home]/mod/vm/proj_locate.inc,v 1.0 2006/06/19  */
/**
 *
 * Volunteer Management Module -- utility functions.
 *
 * <p>This file is part of the Volunteer Management module. It includes functions that are used
 * for google maps mapping for specific projects or all projects.  Include when v-m related maps
 * are required.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Jonathan Raye <jr978@bard.edu>
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu>
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 */

/**
 *  Retrieves the project_id from _Post data, queries 
 *  the corresponding GPS coordinates, and maps the project
 *  to the google maps api frame.
 * 
 *  Performs a DB query of the <b>vm_projects</b> and <b>location</b> 
 *  tables given the project's id.
 *
 *  @param string $no  Null, or no matter.
 *  @access public
 *  @return void
 */
function _shn_vm_proj_locate($no=NULL)
{
    global $global;
    $db=$global['db'];
 
    $q = "select value from config where confkey = 'google_key'";
    $result=$db->Execute($q);
    $gmap_key=$result->fields[0];

    $project_id = $_GET['project'];
    
    ?>
	<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $gmap_key?>" type="text/javascript"></script>


	<div id="map" style="width: 600px; height: 600px"></div>
	  <script type="text/javascript">
       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch

	<?php	//query the database for information on the partiular project
		$q = "select location_id, name, start_date, end_date from vm_projects where proj_id = '${project_id}'";
    		$result=$db->Execute($q);
		$location_id =  $result->fields[0];
		//concat message for the popup window
    		$message = $result->fields[1] . "<br>Start Date: " . $result->fields[2] . "<br>End Date: " . $result->fields[3];

		//use the location_id to get gps coordinates for mapping
		$q = "select map_northing, map_easting from gis_location where location_id = '${location_id}'";
    		$result=$db->Execute($q);
    		$longitude=$result->fields[0];
    		$latitude=$result->fields[1];
    			
	?>	
		//zoom map to area around project, with zoom level 5
		map.centerAndZoom(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>), 5);
		
		//make a new marker with the concatonated message in the popup window
		var marker = new GMarker(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>));
		GEvent.addListener(marker, 'click', function() {
			marker.openInfoWindowHtml("<?php echo $message?>");
			});
		map.addOverlay(marker);
			
	   </script>	


    <?php
}  // end _shn_vm_proj_locate()

/**
 * Retrieves the GPS coordinates and other relevant data for every project, and maps the projects
 * to the google maps api frame.
 * 
 * Performs a DB query of the <b>vm_projects</b> and <b>location</b> tables.
 *
 * @param string $no  NULL or no matter.
 * @access public
 * @return void
 */
function _shn_vm_proj_locate_all($no=NULL)
{
//error_reporting(E_ALL);

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
		
		//query all projects
		$q = "select location_id, name, start_date, end_date, proj_id from vm_projects order by proj_id asc";
		$res_proj=$db->Execute($q);
		while(!$res_proj->EOF){
        		$location_id=$res_proj->fields[0]; 
			
			$pos = strpos($res_proj->fields[1],'\'');
			$proj_name = "";
			if(NULL == $pos){
			$proj_name = $res_proj->fields[1];
			}else{
			$proj_name = substr($res_proj->fields[1],0,$pos) . "\'" . substr($res_proj->fields[1],$pos+1);
			}
			
			//make a link with project_id in the url, to go to the project details page
			$message = "<a href=\"index.php?mod=vm&act=proj_detail&project=" . $res_proj->fields[4] . "\">" . $proj_name . "</a><br>Start Date: " . $res_proj->fields[2] . "<br>End Date: " . $res_proj->fields[3];
			//query gps data for the location
			$q = "select map_northing, map_easting from gis_location where location_id = '${location_id}'";
    			$result=$db->Execute($q);
    			$longitude=$result->fields[0];
    			$latitude=$result->fields[1];

			?>
			map.addOverlay(createMarker(new GPoint(<?php echo $latitude?>, <?php echo $longitude?>), '<?php echo $message?>'));
			<?php
					
        		$res_proj->MoveNext();
		}

	    			
	?>
	
				
	   </script>	
	

    <?php
}

?>

