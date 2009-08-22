<?php
/**
* $id$
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @package    framework 
* @subpackage rss    
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* 
* 
* 	
* Currently support in varrying degrees for GPX, KML, GML and GeoRSS
*/

    interface geoFactorysUpload
    {
        public function shn_sm_geo_get_features();
    }
    
    abstract class GeoFactoryUpload
    {
        public $dom;
        
        function __construct($filepath_ = "tmp/dom.txt")
        {
            $this->dom = new DOMDocument;
            $this->dom->load($filepath_);           
        }
    }
    
    class GPXFactoryUpload extends GeoFactoryUpload implements geoFactorysUpload
    {
        
        public function shn_sm_geo_get_features()
        {
            $features = array();
            
            $time = $this->dom->getElementsByTagName('time')->item(0)->nodeValue;
            
            $metadata = $this->dom->getElementsByTagName('metadata');
            if($metadata->length > 0){
              $metadata_author = $metadata->item(0)->getElementsByTagName('author')->item(0)->nodeValue;
            }
            $item_points = $this->dom->getElementsByTagName('wpt');
            $item_rte = $this->dom->getElementsByTagName('rte');
            $item_trk = $this->dom->getElementsByTagName('trk');
            $extensions = $this->dom->getElementsByTagName('extensions');
            
            // Parse all points
            for ($i = 0; $i < $item_points->length; $i++) {
                $point_latitude = $item_points->item($i)->getAttribute('lat');
                $point_longitude = $item_points->item($i)->getAttribute('lon');
                $point_height = $item_points->item($i)->getElementsByTagName('ele')->item(0)->nodeValue;
                $point_date =  $item_points->item($i)->getElementsByTagName('time')->item(0)->nodeValue;
                $point_name = $item_points->item($i)->getElementsByTagName('name')->item(0)->nodeValue;
                $point_description = $item_points->item($i)->getElementsByTagName('desc')->item(0)->nodeValue;
                $point_link = $item_points->item($i)->getElementsByTagName('link')->item(0)->nodeValue;
                $point_extensions = $item_points->item($i)->getElementsByTagName('extensions')->item(0)->nodeValue;
                
                // Clean ups
                if('' == trim($point_height)){
                    $point_height = '0';
                }
                if('' == trim($point_name)){
                    $point_name = "GPS Point";
                }
                if('' == trim($point_date)){
                    $point_date = date('Y-m-d H:i:s'); // 2008-07-09 21:48:16  	
                }
                if('' == trim($point_extensions)){
                    // look for sahana module type and other things
                }
                
                $point_coords = $point_latitude . ',' .  $point_longitude . ',' . $point_height . ',wkt{POINT('. $point_latitude . ' ' .  $point_longitude . ' ' . $point_height . ')}';
                
                $feature = array(
                    'f_type'          => 'point',
                    'f_coords'        => $point_coords,  
                    'f_name'          => $point_name,
                    'f_description'   => $point_description,
                    'f_author'        => $metadata_author,
                    'f_url'           => $point_link,
                    'f_event_date'    => $point_date,
                    'f_extended_data' => $point_extensions
                );
                array_push($features, $feature);
            }
            
            // Parse all routes
            for ($i = 0; $i < $item_rte->length; $i++) {

                $line_name = $item_rte->item($i)->getElementsByTagName('name')->item(0)->nodeValue;
                $line_description = $item_rte->item($i)->getElementsByTagName('desc')->item(0)->nodeValue;
                $line_link = $item_rte->item($i)->getElementsByTagName('link')->item(0)->nodeValue;
                $line_extensions = $item_rte->item($i)->getElementsByTagName('extensions')->item(0)->nodeValue;
                
                // get all points within route
                $line_points = $item_point->getElementsByTagName('rtept');
                
                if($line_points->length > 0){
                    $line_date = $item_rte->item($i)->getElementsByTagName('time')->item(0)->nodeValue;
                    // TODO  calc c.o.m of line untill built function use first point.
                    $line_coords = $item_rte->item(0)->getAttribute('lat') . ',' .  $item_rte->item(0)->getAttribute('lon') . ',0,wkt{LINE(';
                    $lonlathi = array();
                    for ($i = 0; $i < $line_points->length; $i++) {
                        
                        $line_latitude = $item_rte->item($i)->getAttribute('lat');
                        $line_longitude = $item_rte->item($i)->getAttribute('lon');
                        $line_height = $item_rte->item($i)->getElementsByTagName('ele')->item(0)->nodeValue;
                        if('' == trim($line_height)){
                            $line_height = '0';
                        }
                        $line_coord = implode(' ' , array($line_latitude, $line_longitude, $line_height));
                        array_push($lonlathi, $line_coord);
                    }
                    $line_coords = $line_coords . implode(',', $lonlathi) . ')}';
                
                    // Clean ups
                    if('' == trim($line_name)){
                        $line_name = "GPS ";
                    }
                    if('' == trim($line_extensions)){
                        // look for sahana module type and other things
                    }
                    if('' == trim($point_date)){ 
                        $line_date = date('Y-m-d H:i:s');    
                    } 
                
                    $feature = array(
                        'f_type'          => 'line',
                        'f_coords'        => $line_coords,  
                        'f_name'          => $line_name,
                        'f_description'   => $line_description,
                        'f_author'        => $metadata_author,
                        'f_url'           => $line_link,
                        'f_event_date'    => $line_date,
                        'f_extended_data' => $line_extensions
                    );
                    array_push($features, $feature);
                }
            }
            
            // Parse all tracks
            for ($i = 0; $i < $item_trk->length; $i++) {

                $line_name = $item_trk->item($i)->getElementsByTagName('name')->item(0)->nodeValue;
                $line_description = $item_trk->item($i)->getElementsByTagName('desc')->item(0)->nodeValue;
                $line_link = $item_trk->item($i)->getElementsByTagName('link')->item(0)->nodeValue;
                $line_extensions = $item_trk->item($i)->getElementsByTagName('extensions')->item(0)->nodeValue;
                
                // get all points within route
                $line_points_set = $item_point->getElementsByTagName('trkseg');
                for ($i = 0; $i < $line_points_set->length; $i++) {
                    if($line_points_set->length > 0){
                        $line_points = $item_point->getElementsByTagName('trkpt');
                        if($line_points->length > 0){
                            $line_date = $item_trk->item($i)->getElementsByTagName('time')->item(0)->nodeValue;
                            // TODO  calc c.o.m of line untill built function use first point.
                            $line_coords = $item_trk->item(0)->getAttribute('lat') . ',' .  $item_trk->item(0)->getAttribute('lon') . ',0,wkt{LINE(';
                            $lonlathi = array();
                            for ($i = 0; $i < $line_points->length; $i++) {
                        
                                $line_latitude = $item_trk->item($i)->getAttribute('lat');
                                $line_longitude = $item_trk->item($i)->getAttribute('lon');
                                $line_height = $item_trk->item($i)->getElementsByTagName('ele')->item(0)->nodeValue;
                                if('' == trim($line_height)){
                                    $line_height = '0';
                                }
                                $line_coord = implode(' ' , array($line_latitude, $line_longitude, $line_height));
                                array_push($lonlathi, $line_coord);
                            }
                            $line_coords = $line_coords . implode(',', $lonlathi) . ')}';
                
                            // Clean ups
                            if('' == trim($line_name)){
                                $line_name = "GPS ";
                            }
                            if('' == trim($line_extensions)){
                                // look for sahana module type and other things
                            }
                            if('' == trim($point_date)){ 
                                $line_date = date('Y-m-d H:i:s');    
                            } 
                
                            $feature = array(
                                'f_type'          => 'line',
                                'f_coords'        => $line_coords,  
                                'f_name'          => $line_name,
                                'f_description'   => $line_description,
                                'f_author'        => $metadata_author,
                                'f_url'           => $line_link,
                                'f_event_date'    => $line_date,
                                'f_extended_data' => $line_extensions
                            );
                            array_push($features, $feature);
                        }
                    }
                }
            }
            return $features;
        }
        
    }





    class KMLFactoryUpload extends GeoFactoryUpload implements geoFactorysUpload
    {
        
        public function shn_sm_geo_get_features()
        {
//            $items = $doc1->getElementsByTagName('Placemark');
//            $_SESSION['point']['count']=$items->length;
//                
//            for ($i = 0; $i < $items->length; $i++) {
//                $point_name = $items->item($i)->getElementsByTagName('name')->item(0)->nodeValue;
//                    
//                if(trim($point_name)=='') {
//                    $point_name = "Unknown";
//                }
//                $point_description = $items->item($i)->getElementsByTagName('description')->item(0)->nodeValue;
//                $point = $items->item($i)->getElementsByTagName('Point');
//                //add check
//                $point_longlatheight = explode(',', ($point->item(0)->getElementsByTagName('coordinates')->item(0)->nodeValue), 3);
//                $point_longitude = $point_longlatheight[0];
//                $point_latitude = $point_longlatheight[1];
//                $point_height = $point_longlatheight[2];
            }
        }
    }

    class GMLFactoryUpload extends GeoFactoryUpload implements geoFactorysUpload
    {
        
        public function shn_sm_geo_get_features()
        {
          //            $items = $doc1->getElementsByTagName('Point');
//            for ($i = 0; $i < $items->length; $i++) {
//                // Check for possible coodinate tags & parse aproprately
//                        
//                $coordinates = $items->item($i)->getElementsByTagName('coordinates');
//                // Example - <coordinates>5.0,40.0</coordinates>
//                if($coordinates->length > 0) {  
//                    $point_longlat = explode(',', ($coordinates->item(0)->nodeValue), 2);
//                    $point_longitude = $point_longlat[0];
//                    $point_latitude = $point_longlat[1]; 
//                            
//                } else {
//                    $coordinates = $items->item($i)->getElementsByTagName('pos');
//                    // Example - <gml:pos>49.40 -123.26</gml:pos>                            
//                    if($coordinates->length > 0) {
//                        $point_longlat = explode(" ", ($coordinates->item(0)->nodeValue), 2);
//                        $point_longitude = $point_longlat[0];
//                        $point_latitude = $point_longlat[1];
//                                
//                    } else {
//                        $coordinates = $items->item($i)->getElementsByTagName('coord');
//                        // Example - <gml:coord><gml:X>20.0</gml:X><gml:Y>5.0</gml:Y></gml:coord>
//                        if($coordinates->length > 0){
//                            $point_longitude = $coordinates->item(0)->getElementsByTagName('X')->item(0)->nodeValue;
//                            $point_latitude  = $coordinates->item(0)->getElementsByTagName('Y')->item(0)->nodeValue;
//                                
//                        }
//                    }
//                }
//            /* Fix later
//            $points_holder = $item[$i].parent_node();
//            $point_name = $points_holder->getElementsByTagName('name')->item(0)->nodeValue;
//            $point_description = $points_holder->getElementsByTagName('description')->item(0)->nodeValue;
//            if(trim($point_name)=='') {
//                $point_name = "Unknown";
//            }
//             */
//            }  
        }
    
    }
    
    class GeoRSSFactoryUpload extends GeoFactoryUpload implements geoFactorysUpload
    {
        public function shn_sm_geo_get_features()
        {
            
        }
    }









