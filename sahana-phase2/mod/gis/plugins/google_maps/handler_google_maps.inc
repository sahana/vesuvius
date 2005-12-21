<?php

function init_map($gmap_key){
?>
		<script src="http://maps.google.com/maps?file=api&v=1&key=<?php echo $gmap_key?>" type="text/javascript"></script>

<?php
}
function init_gmap(){
?>
		<script src="http://maps.google.com/maps?file=api&v=1&key=ABQIAAAAb-bE-ljr4-6Hsb4x92lWhRT2yXp_ZAY8_ufC3CFXhHIE1NvwkxQTjccCsxIjr0poUEEARUZJgolNfw" type="text/javascript"></script>

<?php
}

function load_map(){
?>
	<div id="map" style="width: 500px; height: 400px"></div>
	  <script type="text/javascript">
		   //<![CDATA[
       var map = new GMap(document.getElementById("map"));
			 map.addControl(new GLargeMapControl());
       //map.addControl(new GSmallMapControl());
			 map.addControl(new GMapTypeControl());//satellite image switch
       map.centerAndZoom(new GPoint(-122.1419, 37.4419), 4);
       //map.centerAndZoom(new GPoint(79.8000, 7.4419),8);

			 //add marker test
			 //var point1 = new GPoint(-122.1419, 37.4419);
			 //var marker1 = new GMarker(point1);
			 //map.addOverlay(marker1);
       //]]>
    </script>
	
<?php
}

/*
 * add existing markers from db
*/
function add_marker_db($array)
{
?>
  <script type="text/javascript">
		var point1 = new GPoint(-122.1419, 37.4419);
		var marker1 = new GMarker(point1);
		map.addOverlay(marker1);            
	</script>
<?php
}

/*
 * click and add markers
*/
function add_marker($name)
{
?>
	<script type="text/javascript">
		GEvent.addListener(map, 'click', function(overlay, point) {
	  	if (overlay) {
			var html = "<?php echo $name?>";
				overlay.openInfoWindowHtml(html);
				//map.removeOverlay(overlay);
			} 
			else if (point) {
				map.addOverlay(new GMarker(point));
				<?php //store coordinates in session variable; ?>
			}
		});
	</script>
<?php
}

/**
 * info on existing markers
*/
function info_event($query_results){
?>
 <script type="text/javascript">
 	GEvent.addListener(map, 'click', function(overlay, point) {
  	if (overlay) { 
			//display information on marker
			var html = "test";
			overlay.openInfoWindowHtml(html);
		}
		else{
			//dont handle point
		}
	});
 </script>			 
<?php
}
?>
