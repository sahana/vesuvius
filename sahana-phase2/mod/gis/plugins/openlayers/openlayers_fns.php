<?php
/** 
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

function ol_basic_map()
{
 	global $conf;
?>
		var lon = <?=$conf['mod_gis_center_x']?>;
        var lat = <?=$conf['mod_gis_center_y']?>;
        var zoom = 5;
        var map, velayer, layer,marker;
        
		map = new OpenLayers.Map($('map'));
		
		OpenLayers.ProxyHost='';
			// WMS
	    var wms = new OpenLayers.Layer.WMS( "OpenLayers WMS", 
	                      "http://labs.metacarta.com/wms/vmap0", 
	                      {layers: 'basic'} );
	       
	       // MSN VirtualEearth
	    velayer = new OpenLayers.Layer.VirtualEarth( "VE",
            { minZoomLevel: 4, maxZoomLevel: 6 }); 
           
           // KaMap satellite Mapping
        var kamap = new OpenLayers.Layer.KaMap("KaMap","http://openlayers.org/world/index.php",{g:"satellite",map:"world"}); 
            
            
            // WMS Transparent Overlay
        var twms = new OpenLayers.Layer.WMS( "World Map","http://world.freemap.in/cgi-bin/mapserv?",
				{map: '/www/freemap.in/world/map/factbooktrans.map',transparent:'true', 
					layers: 'factbook', 'format':'png'} );
					
			//WFS
		var layer = new OpenLayers.Layer.WFS( "Owl Survey","http://www.bsc-eoc.org/cgi-bin/bsc_ows.asp?",
        		{typename: "OWLS", maxfeatures: 30});
        		
        	//GeoRSS Feed
        var url = "http://earthquake.usgs.gov/recenteqsww/eqs7day-M2.5.xml";
        var parts = url.split("/");

			var georss = new OpenLayers.Layer.GeoRSS(parts[parts.length-1], url );
			
            
            //map.addLayers([georss,velayer,kamap,twms,layer,wms]);
            map.addLayers([kamap,twms,layer,wms]);
            
            markers = new OpenLayers.Layer.Markers("markers");
            map.addLayer(markers);
            
            map.setCenter(new OpenLayers.LonLat(lon, lat), zoom);
            map.addControl( new OpenLayers.Control.LayerSwitcher() );
            map.addControl( new OpenLayers.Control.PanZoomBar() );
            
            map.events.register("click", map, function(e) { 
                var lonlat = map.getLonLatFromViewPortPx(e.xy);
                alert("You clicked near " + lonlat.lat + " N, " +
                                          + lonlat.lon + " E");
            });
<?php
}

function marker_map()
{
	global $conf;
?>
	//OpenLayers.ProxyHost="";
	var lon = <?=$conf['mod_gis_center_x']?>;
    var lat = <?=$conf['mod_gis_center_y']?>;
    var zoom = 5;
    var map, velayer, layer,marker;
    map = new OpenLayers.Map($('map'));
	var wms = new OpenLayers.Layer.WMS( "OpenLayers WMS", 
	                      "http://labs.metacarta.com/wms/vmap0", 
	                      {layers: 'basic'} );

	var layer = new OpenLayers.Layer.WFS( "Owl Survey",
						"http://www.bsc-eoc.org/cgi-bin/bsc_ows.asp?",
						{typename: "OWLS", maxfeatures: 30});	                      
	map.addLayers([wms,layer]);
	map.zoomToMaxExtent();
	map.setCenter(new OpenLayers.LonLat(lon, lat), zoom);
            map.addControl( new OpenLayers.Control.LayerSwitcher() );
            map.addControl( new OpenLayers.Control.PanZoomBar() );
<?php
}
?>
