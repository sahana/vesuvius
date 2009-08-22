<?php
/**
 * $id$
 * Google Maps plugin for Sahana GIS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    module
* @subpackage google_maps
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Show basic map
 * called by shn_gis_map in gis api
 */
function show_map($opt=null)
{
	global $global;
	global $conf;
	$key = $conf['gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_gms()
	{
			
		//alert('map');
	
	       var map = new GMap2(document.getElementById("map"));
				 map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
				 map.addControl(new GMapTypeControl());//satellite image switch
				 
				map.setCenter(new GLatLng(<?php echo $conf['gis_center_y']!=''?$conf['gis_center_y']:8.5?>,<?php echo $conf['gis_center_x']!=''?$conf['gis_center_x']:79.5?>), <?php echo $conf['gis_zoom']?>,G_SATELLITE_MAP);
		onloadfunc();
	}		
//]]>	
</script>
	<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
<?php
}



/**
 * show map with marker addition event
 * ability to enter markers on map
 * called by shn_gis_add_marker_map_form in gis api
 * 
 * $extra_opts['marker']=>'single' will disable multiple markers on the map.
 */
function show_add_marker_map($name,$extra_opts=null)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_add_mkr_js()
	{
			var map = new GMap2(document.getElementById("map"));
			map.addControl(new GLargeMapControl());
	       //map.addControl(new GSmallMapControl());
			map.addControl(new GMapTypeControl());//satellite image switch
				 
			map.setCenter(new GLatLng(<?php echo $conf['gis_center_y']?>,<?php echo $conf['gis_center_x']?>), <?php echo $conf['gis_zoom']?>,G_SATELLITE_MAP);			
			GEvent.addListener(map, 'click', function(overlay, point) {
	  		if (overlay) {
				var html = "<?php echo $name?>";
				//overlay.openInfoWindowHtml(html);
				map.removeOverlay(overlay);
			} 
			else {
				<?php if(isset($extra_opts) && $extra_opts['marker']==='single'){ ?>
				map.clearOverlays();
				<?php } ?>
				map.addOverlay(new GMarker(point));
				// store x,y coords in hidden variables named loc_x, loc_y
				// must be set via calling page
				var x_point=document.getElementsByName("loc_x");
				var y_point=document.getElementsByName("loc_y");
				x_point[0].value=point.lng();
				y_point[0].value=point.lat();
				//alert(x_point[0].value);
			}	
		});		
		onloadfunc();	
	}		
	//]]>	
	
	</script>
	<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
	
<?php
}


/**
 * show map with markers
 * called by shn_gis_map_with_markers in gis api
 * 
 */
function show_map_with_markers($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_markers_js()
	{
			if(GBrowserIsCompatible())
			{
				function createMarker(point,html) {
        			var marker = new GMarker(point);
        			GEvent.addListener(marker, "click", function() {
          				marker.openInfoWindowHtml(html);
        			});
        		return marker;
      			}
      			
      			var map = new GMap2(document.getElementById("map"));
      			map.addControl(new GLargeMapControl());
	       		//map.addControl(new GSmallMapControl());
				map.addControl(new GMapTypeControl());//satellite image switch
				
				map.setCenter(new GLatLng(<?php echo $conf['gis_center_y']?>,<?php echo $conf['gis_center_x']?>), <?php echo $conf['gis_zoom']?>,G_SATELLITE_MAP);
<?php
				for($i=0;$i< sizeof($array);$i++){
					$lat=$array[$i]["lat"];
					$lon=$array[$i]["lon"];
					$name=$array[$i]["name"];
					$url=$array[$i]["url"];
					$pre_url="index.php?";
					$url=$pre_url.$url;
?>	
					var point = new GLatLng(<?php echo $lat?>,<?php echo $lon?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?php echo _lc($name)?></strong><br><a href="<?php echo $url?>">View</a></div>');
      				map.addOverlay(marker);
<?php
				}
?>
      		}
      		else{
      			alert("Incompatible");
      			}      			
		onloadfunc();
	}		
	//]]>	
	
	</script>
<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
<?php
}

/**
 * Show map with wiki style markers
 * called by shn_gis_map_with_wiki_markers in gis api
 */
function show_map_with_wiki_marker($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_wiki_js()
	{
			if(GBrowserIsCompatible())
			{
				function createMarker(point,html) {
        			var marker = new GMarker(point);
        			GEvent.addListener(marker, "click", function() {
          				marker.openInfoWindowHtml(html);
        			});
        		return marker;
      			}
      			
      			var map = new GMap2(document.getElementById("map"));
      			map.addControl(new GLargeMapControl());
	       		//map.addControl(new GSmallMapControl());
				map.addControl(new GMapTypeControl());//satellite image switch
				
				map.setCenter(new GLatLng(<?php echo $conf['gis_center_y']?>,<?php echo $conf['gis_center_x']?>), <?php echo $conf['gis_zoom']?>,G_SATELLITE_MAP);
<?php
				for($i=0;$i< sizeof($array);$i++){
					$lat=$array[$i]["lat"];
					$lon=$array[$i]["lon"];
					$name=$array[$i]["name"];
					$desc=$array[$i]["desc"];
					$url=$array[$i]["url"];
					if(!(($array[$i]["date"])=="0000-00-00 00:00:00")){
						$date=_t('Date: ').date('l dS \of F Y',strtotime($array[$i]["date"]));
					} else {
						$date="";
					}
					$author=($array[$i]["author"]!="")?$array[$i]["author"]:_t("anonymous");
					$edit=$array[$i]["edit"];
					if($array[$i]["image"]!=null){
						$image = $array[$i]["image"];
						//$image="{<img src='{$image}' width='100' height='100' >}";
						$image=($image?"<img src=$image width=100 height=100 ><br>":'');
						
					}
					else
						$image='';
					
					//$edit="help";
?>	
					var point = new GLatLng(<?php echo $lat?>,<?php echo $lon?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?php echo _lc($name)?></strong><br><?php echo _lc($desc)?><br><?php echo $image?><a href="<?php echo $url?>">Link</a><br><?php echo $date?><br><strong>Author:</strong><?php echo $author?><br><a href="<?php echo $edit?>"> Edit</a></div>');
      				map.addOverlay(marker);
<?php
				}
				$image=null;
?>
      		}
      		else{
      			alert("Incompatible");
      			}      			
		onloadfunc();
	}		
	//]]>	
	
	</script>
<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
<?php
}

/**
 * Map with custom markers
 * called by shn_gis_density_map in gis api
*/
function show_map_with_custom_markers($array)
{
	global $global;
	global $conf;
	$db=$global['db'];
	$key = $conf['gis_google_key'];
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_markers_js()
	{
			if(GBrowserIsCompatible())
			{
				var icon = new GIcon();
				//icon.image = <?php echo $global['approot'].$conf['gis_marker_folder']."marker_r1.png"?>;
				//icon.shadow = "http://labs.google.com/ridefinder/images/mm_20_shadow.png";
				icon.iconSize = new GSize(20, 34);
				//icon.shadowSize = new GSize(22, 20);
				icon.iconAnchor = new GPoint(5, 34);
				icon.infoWindowAnchor = new GPoint(5, 2);
				
				
				
				function createMarker(point,html,markerName) {
        			var myicon=new GIcon(icon);
        			myicon.image = "<?php echo $conf['gis_marker_folder']?>"+markerName+".png";
        			//myicon.image="http://localhost/~nazgul/sahana-main/sahana-phase2-pan/www/theme/default/img/"+markerName+".png";
        			//myicon.image="http://www.google.com/mapfiles/marker.png";
        			var marker = new GMarker(point,myicon);
        			GEvent.addListener(marker, "click", function() {$location=preg_split('/,/',$_REQUEST['longlat'],4);
          				marker.openInfoWindowHtml(html);
        			});
        		return marker;
      			}
      			
      			var map = new GMap2(document.getElementById("map"));
      			map.addControl(new GLargeMapControl());
	       		//map.addControl(new GSmallMapControl());
				map.addControl(new GMapTypeControl());//satellite image switch
				
				map.setCenter(new GLatLng(<?php echo $conf['gis_center_y']?>,<?php echo $conf['gis_center_x']?>), <?php echo $conf['gis_zoom']?>,G_SATELLITE_MAP);
<?php
				for($i=0;$i< sizeof($array);$i++){
					$lat=$array[$i]["lat"];
					$lon=$array[$i]["lon"];
					$name=$array[$i]["name"];
					$url=$array[$i]["id"];
					$pre_url="index.php?mod=cr&act=ecmp&seq=view&cmp_id=";
					$url=$pre_url.$name;
					$desc=(isset($array[$i]["desc"]))?$array[$i]["desc"]:"";
					$marker_name=(isset($array[$i]["marker"]))?$array[$i]["marker"]:"marker";
?>	
					var point = new GLatLng(<?php echo $lat?>,<?php echo $lon?>);
      				var marker = createMarker(point,'<div id="wiki_info"><strong><?php echo _lc($name)?></strong><br><?php echo $desc?><br><a href="<?php echo $url?>">View</a></div>',"<?php echo $marker_name?>");
      				map.addOverlay(marker);
<?php
				}
?>
      		}
      		else{
      			alert("Incompatible");
      			}      			
		onloadfunc();
	}		
	//]]>	
	
	</script>
	<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
<?php
}

// this funtion is to draw polyline
function show_map_polylines($cords,$title=null)
{

	global $global;
	global $conf;
	$key = $conf['gis_google_key'];
	$step=0;
	
?>
	<script src="http://maps.google.com/maps?file=api&v=2&key=<?php echo $key?>" type="text/javascript"></script>
	<script type="text/javascript">
	  
	//<![CDATA[
        var onloadfunc = window.onload;
	window.onload=function show_map_gms()
	{
		var map = new GMap2(document.getElementById("map"));
		map.addControl(new GLargeMapControl());
	       	map.addControl(new GMapTypeControl());//satellite image switch
	//<![CDATA[
		map.setCenter(new GLatLng(<?php echo $cords[0]['right'][0];?>,<?php echo $cords[0]['right'][1];?>), 4);
		// Create GPolylineOptions argument as an object literal.
		// Note that we don't use a constructor.
	  
	  
	var polyOptions = {geodesic:true};
	<?php while($cords[$step]){
	if($cords[$step]){?>
	var polyline = new GPolyline([
	new GLatLng(<?php echo $cords[$step]['right'][0];?>, <?php echo $cords[$step]['right'][1]?>),
	new GLatLng(<?php echo $cords[$step]['left'][0]?>,<?php echo $cords[$step]['left'][1]; ?>)
	], "#ff0000", 10, 1, polyOptions);
	map.addOverlay(polyline);
	var marker = new GMarker(new GLatLng(<?php echo $cords[$step]['right'][0];?>,<?php echo $cords[$step]['right'][1];?>));
	map.addOverlay(marker);
	map.addOverlay(polyline);
	GEvent.addListener(marker,"click", function() {
    var myHtml = "<?php echo substr($title[$step]['title'],0,30);?><br/>Alert arrived <?php echo $title[$step]['days'];?> day(s) <?php echo $title[$step]['hours'];?> Hours ago<br/><a href='<?php echo $title[$step]['link']?>'>Visit Website</a>";
    
    map.openInfoWindowHtml(new GLatLng(<?php echo $cords[$step]['right'][0]?>,<?php echo $cords[$step]['right'][1]?>), myHtml);
      });
	 
<?php }$step++;}?>
		onloadfunc();
	}		
//]]>	
</script>
	<div id="map" style="width: <?php echo $conf['gis_width']?>px; height: <?php echo $conf['gis_height']?>px"></div>
<?php
} 






