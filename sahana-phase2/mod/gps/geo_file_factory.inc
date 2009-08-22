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
* Factorys for creating main xml based geo data
* Currently support in varrying degrees for GPX, KML, GML and GeoRSS
* 
*/

    interface geoFactorysDownload
    {
        public function shn_sm_Geo_Add_Point($id_, $name_, $author_, $link_, $description_, $timestamp_, $icon_, $extendedData_, $coordinates_);
        public function shn_sm_Geo_Add_Path($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_);
        public function shn_sm_Geo_Add_Polygon($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_);

    }
    
    
    abstract class GeoFactoryDownload
    {
        // Creates Document.
        public $dom;
        
        function __construct()
        {
            $this->dom = new DOMDocument('1.0', 'UTF-8');
        }
        
        public function shn_sm_geo_print()
        {
            return $this->dom->saveXML();
        }
        
        public function shn_sm_geo_publish($name, $overwrite = true)
        {
            global $global;
            $relative_path = 'export/' . $this->_shn_sm_geo_get_class_name() . '/' . $name . '.xml';
            $feed_path = $global['approot'] . '/www/'. $relative_path;
            if(file_exists($feed_path)){
                if($overwrite){
                    unlink($feed_path);
                } else {
                    return null;
                }
            }
            if($this->dom->save($feed_path) === FALSE){
                return FALSE;
            }
            return $relative_path;
        }
        
        private function _shn_sm_geo_get_class_name(){
            
            $class = get_class($this);
            switch ($class) {
                case 'GPXFactory':
                return 'gpx';
                break;
                case 'GeoRSSFactory':
                return 'georss';
                break;
                case 'KMLFactory':
                return 'kml';
                break;
                case 'GMLFactory':
                return 'gml';
                break;
                default: 
                return 'other';
                break;
            }
        }
    }










    
    
    /**
     * GPX PARSER
     *
     *
     *
     */
    class GPXFactory extends GeoFactoryDownload implements geoFactorysDownload
    {
        
        private $mmetadata_Name = 'Sahana feed';
        private $mmetadata_Description = 'gpx files';
        private $mmetadata_AuthorName = 'peter';
        private $mmetadata_Copyright = 'no-one';
        private $mmetadata_Link = 'www.sahana.lk';
        private $mmetadata_Time = '2008-05-25T18:30:02Z';
        private $mmetadata_Keywords = 'sahana keywords';
        
        function __construct()
        {
            $this->dom = new DOMDocument('1.0', 'UTF-8');

            // Creates the root GPX element and appends it to the root document.
            $gpxNode = $this->dom->createElementNS('http://www.topografix.com/GPX/1/1', 'gpx');
            $gpxNode->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance' );
            $gpxNode->setAttribute('xsi:schemaLocation', 'http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd' );
            $gpxNode->setAttribute('creator', $this->mmetadata_AuthorName);

            // Creates the metadata elements and append them to the Document element.
            $metadataNode = $this->dom->createElement('metadata');
            
            $metadataNameNode = $this->dom->createElement('name', $this->mmetadata_Name);
            $metadataDescritptionNode = $this->dom->createElement('desc', $this->mmetadata_Description);
            $metadataAuthorNode = $this->dom->createElement('author', $this->mmetadata_AuthorName);
            $metadataCopyrightNode = $this->dom->createElement('copyright', $this->mmetadata_Copyright);
            $metadataLinkNode = $this->dom->createElement('link', $this->mmetadata_Link);
            $metadataTimeNode = $this->dom->createElement('time', $this->mmetadata_Time);
            $metadataKeywordsNode = $this->dom->createElement('keywords', $this->mmetadata_Keywords);          

            // Appends
            $metadataNode->appendChild($metadataNameNode);
            $metadataNode->appendChild($metadataDescritptionNode);
            $metadataNode->appendChild($metadataAuthorNode);
            $metadataNode->appendChild($metadataCopyrightNode);
            $metadataNode->appendChild($metadataLinkNode);
            $metadataNode->appendChild($metadataTimeNode);
            $metadataNode->appendChild($metadataKeywordsNode);
            $gpxNode->appendChild($metadataNode);
            $this->dom->appendChild($gpxNode);
        }
        
        public function shn_sm_Geo_Add_Point($id_, $name_, $author_, $link_, $description_, $timestamp_, $icon_, $extendedData_, $coordinates_)
        {
            /*
            lat="latitudeType [1]
            lon="longitudeType [1]
            <ele> xsd:decimal </ele> [0..1]
            <time> xsd:dateTime </time> [0..1]
            <magvar> degreesType </magvar> [0..1]
            <geoidheight> xsd:decimal </geoidheight> [0..1]
            <name> xsd:string </name> [0..1]
            <cmt> xsd:string </cmt> [0..1]
            <desc> xsd:string </desc> [0..1]
            <src> xsd:string </src> [0..1]
            <link> linkType </link> [0..*]
            <sym> xsd:string </sym> [0..1]
            <type> xsd:string </type> [0..1]
            <fix> fixType </fix> [0..1]
            <sat> xsd:nonNegativeInteger </sat> [0..1]
            <hdop> xsd:decimal </hdop> [0..1]
            <vdop> xsd:decimal </vdop> [0..1]
            <pdop> xsd:decimal </pdop> [0..1]
            <ageofdgpsdata> xsd:decimal </ageofdgpsdata> [0..1]
            <dgpsid> dgpsStationType </dgpsid> [0..1]
            <extensions> extensionsType </extensions> [0..1]
             */
            
            $new_wptNode = $this->dom->createElement('wpt');
            $new_wptNode->setAttribute('lat', $coordinates_[0][0]);
            $new_wptNode->setAttribute('lon', $coordinates_[0][0]);
            
            if('' != $height_){
                $new_wptUpdatedNode = $this->dom->createElement('eve', $height_);
                $new_wptNode->appendChild($new_wptUpdatedNode);
            }
            
            if('' != $timestamp_){
                $new_wptUpdatedNode = $this->dom->createElement('time', $timestamp_);
                $new_wptNode->appendChild($new_wptUpdatedNode);
            }
            
            if('' != $name_){
                $new_wptTitleNode = $this->dom->createElement('title', $name_);
                $new_wptNode->appendChild($new_wptTitleNode);
            }
            
            if('' != $id_){
                $new_wptIDNode = $this->dom->createElement('cmt', $id_);
                $new_wptNode->appendChild($new_wptIDNode);
            }
            
            if('' != $description_){
                $new_wptSummaryNode = $this->dom->createElement('summary', $description_);
                $new_wptNode->appendChild($new_wptSummaryNode);
            }
            
            if('' != $link_){
                $new_wptLinkNode = $this->dom->createElement('link');
                $new_wptLinkNode->setAttribute('href', $link_);
                $new_wptNode->appendChild($new_wptLinkNode);
            }
            
            // Append wpt before first rte, trk, extensions nodes           
            if($this->dom->getElementsByTagName('rte')->length > 0){
                $this->dom->insertBefore($new_wptNode, $this->dom->getElementsByTagName('rte')->item(0));
            } elseif($this->dom->getElementsByTagName('trk')->length > 0){
                $this->dom->insertBefore($new_wptNode, $this->dom->getElementsByTagName('trk')->item(0));
            } elseif($this->dom->getElementsByTagName('extensions')->length > 0){
                $this->dom->insertBefore($new_wptNode, $this->dom->getElementsByTagName('extensions')->item(0));
            } else {
                $this->dom->getElementsByTagName('gpx')->item(0)->appendChild($new_wptNode);
            }
        }
        
        public function shn_sm_Geo_Add_Path($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            /*
            <name> xsd:string </name> [0..1]
            <cmt> xsd:string </cmt> [0..1]
            <desc> xsd:string </desc> [0..1]
            <src> xsd:string </src> [0..1]
            <link> linkType </link> [0..*]
            <number> xsd:nonNegativeInteger </number> [0..1]
            <type> xsd:string </type> [0..1]
            <extensions> extensionsType </extensions> [0..1]
            <rtept> wptType </rtept> [0..*]
             */
            
            
            $new_rteNode = $this->dom->createElement('rte');
            $new_rteCmtNode = $this->dom->createElement('cmt');
            $new_rteDescriptionNode = $this->dom->createElement('src');
            $new_rteSrcNode = $this->dom->createElement('link');
            $new_rteLinkNode = $this->dom->createElement('number');
            $new_rteNumberNode = $this->dom->createElement('type');
            $new_rteTypeNode = $this->dom->createElement('extensions');
            $new_rteExtensionsNode = $this->dom->createElement('rtept');
            
            $new_rteptNode = $this->dom->createElement('');
        }
        
        public function shn_sm_Geo_Add_Polygon($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            
        }
        
        
        private function shn_sm_Geo_Create_wptType(){
            
        }
        
        
        
    }
  
  
    
    
    
    
    
    
 

         
    /**
     * GeoRSS PARSER
     *
     *
     *
     */
    class GeoRSSFactory extends GeoFactoryDownload implements geoFactorysDownload
    {
        
        private $mDefault_Title = 'Sahana feed';
        private $mDefault_Subtitle = 'SF';
        private $mDefault_Link = 'www.sahana.lk';
        private $mDefault_Updated = '2008-05-25T18:30:02Z';
        private $mDefault_AuthorName = 'peter';
        private $mDefault_AuthorEmail = 'piper';
        private $mDefault_ID = '123';
        
        
        function __construct()
        {
            $this->dom = new DOMDocument('1.0', 'UTF-8');

            // Creates the root GeoRSS element and appends it to the root document.
            $feedNode = $this->dom->createElementNS('http://www.w3.org/2005/Atom', 'feed');
            $feedNode->setAttribute('xmlns:georss', 'http://www.georss.org/georss');
            
            // Creates the default elements and append them to the Document element.
            $defaultTitleNode = $this->dom->createElement('title', $this->mDefault_Title);
            $defaultSubtitleNode = $this->dom->createElement('subtitle', $this->mDefault_Subtitle);
            $defaultLinkNode = $this->dom->createElement('link');
            $defaultLinkNode->setAttribute('href', $this->mDefault_Link);
            $defaultUpdatedNode = $this->dom->createElement('updated', $this->mDefault_Updated);
            $defaultAuthorNode = $this->dom->createElement('author');
            $defaultAuthorNameNode = $this->dom->createElement('name', $this->mDefault_AuthorName);
            $defaultAuthorEmailNode = $this->dom->createElement('email', $this->mDefault_AuthorEmail);
            $defaultAuthorNode->appendChild($defaultAuthorNameNode);
            $defaultAuthorNode->appendChild($defaultAuthorEmailNode);
            $defaultIDNode = $this->dom->createElement('id', $this->mDefault_ID);
            
            // Appends
            $feedNode->appendChild($defaultTitleNode);
            $feedNode->appendChild($defaultSubtitleNode);
            $feedNode->appendChild($defaultLinkNode);
            $feedNode->appendChild($defaultUpdatedNode);
            $feedNode->appendChild($defaultAuthorNode);
            $feedNode->appendChild($defaultIDNode); 
            $this->dom->appendChild($feedNode);
        }
        
        
        public function shn_sm_Geo_Add_Point($id_, $name_, $author_, $link_, $description_, $timestamp_, $icon_, $extendedData_, $coordinates_)
        {
            $new_entryNode = $this->dom->createElement('entry');
            
            if('' != $name_){
                $new_entryTitleNode = $this->dom->createElement('title', $name_);
                $new_entryNode->appendChild($new_entryTitleNode);
            }
            if('' != $link_){
                $new_entryLinkNode = $this->dom->createElement('link');
                $new_entryLinkNode->setAttribute('href', $link_);
                $new_entryNode->appendChild($new_entryLinkNode);
            }
            if('' != $id_){
                $new_entryIDNode = $this->dom->createElement('id', $id_);
                $new_entryNode->appendChild($new_entryIDNode);
            }
            if('' != $timestamp_){
                $new_entryUpdatedNode = $this->dom->createElement('updated', $timestamp_);
                $new_entryNode->appendChild($new_entryUpdatedNode);
            }
            if('' != $description_){
                $new_entrySummaryNode = $this->dom->createElement('summary', $description_);
                $new_entryNode->appendChild($new_entrySummaryNode);
            }
            
            $new_entryGeoRSSNode = $this->dom->createElement('georss:point', $coordinates_[0][0] . ' ' . $coordinates_[0][1]);
            
            // Appends
            $new_entryNode->appendChild($new_entryGeoRSSNode); 
            $this->dom->getElementsByTagName('feed')->item(0)->appendChild($new_entryNode);
        }
        
        public function shn_sm_Geo_Add_Path($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            
        }
        
        public function shn_sm_Geo_Add_Polygon($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            
        }
        
        /**
         * Publish a feed to '/www/rss/$name_Georss.xml'
         * will over
         * 
         * @param <type> $name
         * @param <type> $overwrite
         * @return <type>
         */
        public function shn_sm_GeoRSS_Publish($name, $overwrite)
        {
            $feed = $global['approot'] . '/www/export/georss/'. $name . '_Georss.xml';
            if(file_exists($feed)){
                if($overwrite){
                    unlink($feed); 
                } else {
                    return null;   
                }
            }
            $feed_in = fopen($feed,"w+");
            fwrite($feed_in, $this->dom->saveXML());
            fclose($feed_in);
        }
        
        /**
         * Takes a current Sahana GeoRSS feed and updates it with new info
         * 
         * @param <type> $Current_Feed
         */
        public function shn_sm_GeoRSS_Update($feed)
        {
            //$doc->load($feed);
        }
        
        private function _shn_sm_GeoRSS_Add_Entry()
        {
            
        }
        
    }
    




    
    
    



    /**
     * KML PARSER
     *
     *
     *
     */
    class KMLFactory extends GeoFactoryDownload implements geoFactorysDownload
    {
        //TODO
        /*
         * may need to package up icons with save and url to them
         * 
         * change private meths to _shn
         * 
         * validate
         */

        // STYLES
        private $mStyle_Default_Icon_Color = 'a1ff00ff';
        private $mStyle_Default_Icon_scale = '1.4';
        private $mStyle_Default_Icon_href  = 'http://www.google.com';

        private $mStyle_Default_Label_Color = 'a1ff00ff';
        private $mStyle_Default_Label_Scale = '1.4';

        private $mStyle_Default_Line_Color = 'a1ff00ff';
        private $mStyle_Default_Line_Scale = '1.4';

        private $mStyle_Default_Poly_Color = 'a1ff00ff';
        private $mStyle_Default_Poly_ColorMode = 'random';

        // DATA
        private $mData_Folder_ID = 'Sahana';
        private $mData_Folder_Name = 'Sahana';
        private $mData_Folder_Author = 'Dave'; 
        private $mData_Folder_Description = 'Sahana geodata';
        private $mData_Folder_ExtendedData = '';

        /**
         * Creates a base KML shell useing class fields
         * 
         * KML can be previewed by creating a KMLFactory and 
         * calling shn_sm_Geo_Print()
         * 
         */
        function __construct()
        {
            $this->dom = new DOMDocument('1.0', 'UTF-8');

            // Creates the root KML element and appends it to the root document.
            $kmlNode = $this->dom->createElementNS('http://earth.google.com/kml/2.2', 'kml');
            $kmlNode->setAttribute('xmlns:atom', 'http://www.w3.org/2005/Atom');
            
            // Creates a KML Document element and appends it to the KML element.
            $docNode = $this->dom->createElement('Document');        

            // STYLES
            // Creates the default Style elements and (eventualy) append them to the Document element.
            $defaultStyleNode = $this->dom->createElement('Style');
            $defaultStyleNode->setAttribute('id', 'default');

            // Creates the default Icon Style element and appends it to the Style element.
            $defaultIconStyleNode = $this->dom->createElement('IconStyle');
            $defaultIconColorNode = $this->dom->createElement('color', $this->mStyle_Default_Icon_Color);
            $defaultIconScaleNode = $this->dom->createElement('scale', $this->mStyle_Default_Icon_scale);
            $defaultIconNode = $this->dom->createElement('Icon');
            $defaultIconHrefNode = $this->dom->createElement('href', $this->mStyle_Default_Icon_href);
            $defaultIconNode->appendChild($defaultIconHrefNode);
            $defaultIconStyleNode->appendChild($defaultIconColorNode);
            $defaultIconStyleNode->appendChild($defaultIconScaleNode);
            $defaultIconStyleNode->appendChild($defaultIconNode);

            // Creates the default Label Style element and appends it to the Style element.
            $defaultLabelStyleNode = $this->dom->createElement('LabelStyle');
            $defaultLabelColorNode = $this->dom->createElement('color', $this->mStyle_Default_Label_Color);
            $defaultLabelScaleNode = $this->dom->createElement('scale', $this->mStyle_Default_Label_Scale);
            $defaultLabelStyleNode->appendChild($defaultLabelColorNode);
            $defaultLabelStyleNode->appendChild($defaultLabelScaleNode);

            // Creates the default Line Style element and appends it to the Style element.
            $defaultLineStyleNode = $this->dom->createElement('LineStyle');
            $defaultLineColorNode = $this->dom->createElement('color', $this->mStyle_Default_Line_Color);
            $defaultLineWidthNode = $this->dom->createElement('width', $this->mStyle_Default_Line_Scale);
            $defaultLineStyleNode->appendChild($defaultLineColorNode);
            $defaultLineStyleNode->appendChild($defaultLineWidthNode);

            // Creates the default Ploygon Style element and appends it to the Style element.
            $defaultPolyStyleNode = $this->dom->createElement('PolyStyle');
            $defaultPolyColorNode = $this->dom->createElement('color', $this->mStyle_Default_Poly_Color);
            $defaultPolyWidthNode = $this->dom->createElement('colorMode', $this->mStyle_Default_Poly_ColorMode);
            $defaultPolyStyleNode->appendChild($defaultPolyColorNode);
            $defaultPolyStyleNode->appendChild($defaultPolyWidthNode);

            // Appends
            $defaultStyleNode->appendChild($defaultIconStyleNode);
            $defaultStyleNode->appendChild($defaultLabelStyleNode);
            $defaultStyleNode->appendChild($defaultLineStyleNode);
            $defaultStyleNode->appendChild($defaultPolyStyleNode);
            $docNode->appendChild($defaultStyleNode);

            // DATA
            // Creates the main Folder element and infomation and (eventualy) append them to the Document element.
            $mainFolderNode = $this->dom->createElement('Folder');
            $mainFolderNode->setAttribute('id', $this->mData_Folder_ID);
            $mainFolderNameNode = $this->dom->createElement('name', $this->mData_Folder_Name);
            
            $mainFolderAtomNode = $this->dom->createElement('atom:author');
            $mainFolderAtomAuthorNode = $this->dom->createElement('atom:name', $this->mData_Folder_Author);
            $mainFolderAtomNode->appendChild($mainFolderAtomAuthorNode);
            $mainFolderDescriptionNode = $this->dom->createElement('description');
            $mainFolderDescriptionNode->appendChild($this->dom->createCDATASection($this->mData_Folder_Description));
            $mainFolderStyleNode = $this->dom->createElement('styleUrl', '#default');
            $mainFolderExtendendDataNode = $this->dom->createElement('ExtendedData', $this->mData_Folder_ExtendedData);

            // Appends
            $mainFolderNode->appendChild($mainFolderNameNode);
            $mainFolderNode->appendChild($mainFolderAtomNode);
            $mainFolderNode->appendChild($mainFolderDescriptionNode);
            $mainFolderNode->appendChild($mainFolderStyleNode);
            $mainFolderNode->appendChild($mainFolderExtendendDataNode);
            $docNode->appendChild($mainFolderNode);
            $kmlNode->appendChild($docNode);
            $this->dom->appendChild($kmlNode);
        }

        /**
         * 
         * Creates a new Placemarker node containting Point infomation and
         * adds it to the DOM
         * NULL should be entered to any unused fields
         * 
         * @param <type> $id_
         * @param <type> $name_
         * @param <type> $description_
         * @param <type> $icon_
         * @param <type> $extendedData_
         * @param <type> $longitude_
         * @param <type> $latitude_
         * @param <type> $height_
         */
        public function shn_sm_Geo_Add_Point($id_, $name_, $author_, $link_, $description_, $timestamp_, $icon_, $extendedData_, $coordinates_)
        {            
            /*
            <Point id="ID">
            <!-- specific to Point -->
            <extrude>0</extrude>                        <!-- boolean -->
            <altitudeMode>clampToGround</altitudeMode>  <!-- kml:altitudeModeEnum: clampToGround, relativeToGround, or absolute -->
            <coordinates>...</coordinates>              <!-- lon,lat[,alt] -->
            </Point>
             */
            
            $newPlacemarkPointNode = $this->dom->createElement('Point');
            $newPlacemarkCoordinateNode = $this->dom->createElement('coordinates', ($coordinates_[0][0] . ',' . $coordinates_[0][1] . ',' . $coordinates_[0][2]));
            $newPlacemarkPointNode->appendChild($newPlacemarkCoordinateNode);

            // Creates new Placemark element and appends data elements to them.
            $newPlacemarkNode = $this->_shn_sm_Geo_Create_Placemark(
                $id_, $name_, NULL, NULL, $author_, $link_, NULL, NULL, 
                NULL, NULL, $description_, NULL, $timestamp_, $icon_, 
                NULL, $extendedData_, $newPlacemarkPointNode);
        
            // May wish to change in future if use more than 1 Folder !!!
            $this->dom->getElementsByTagName('Folder')->item(0)->appendChild($newPlacemarkNode);
        }
        
        
        
        
        /**
         * 
         * @param <type> $id_
         * @param <type> $name_
         * @param <type> $link_
         * @param <type> $description_
         * @param <type> $timestamp_
         * @param <type> $extendedData_
         * @param <type> $longitude_
         * @param <type> $coordinates_
         */
        public function shn_sm_Geo_Add_Path($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            /*
            <LineString id="ID">
            <!-- specific to LineString -->
            <extrude>0</extrude>                   <!-- boolean -->
            <tessellate>0</tessellate>             <!-- boolean -->
            <altitudeMode>clampToGround</altitudeMode> 
            <!-- kml:altitudeModeEnum: clampToGround, relativeToGround, or absolute -->
            <coordinates>...</coordinates>         <!-- lon,lat[,alt] -->
            </LineString>
             */
            
            $newPlacemarkPathNode = $this->dom->createElement('LineString');
            
            $coords = '';
            foreach ($coordinates_ as $xyz){
                $longitude = $xyz[0];
                $latitude = $xyz[1];
                $height = $xyz[2];
                $coords += ' ' . $longitude . ',' . $latitude . ',' . $height;
            }
            $newPlacemarkCoordinateNode = $this->dom->createElement('coordinates', $coords);
            $newPlacemarkPathNode->appendChild($newPlacemarkCoordinateNode);
                        
            // Creates new Placemark element and appends data elements to them.
            $newPlacemarkNode = $this->_shn_sm_Geo_Create_Placemark(
                $id_, $name_, NULL, NULL, $author_, $link_, NULL, NULL, 
                NULL, NULL, $description_, NULL, $timestamp_, NULL, 
                NULL, $extendedData_, $newPlacemarkPathNode);
        
            // May wish to change in future if use more than 1 Folder !!!
            $this->dom->getElementsByTagName('Folder')->item(0)->appendChild($newPlacemarkNode);
        }
        
        
        /**
         * 
         * @param <type> $id_
         * @param <type> $name_
         * @param <type> $link_
         * @param <type> $description_
         * @param <type> $timestamp_
         * @param <type> $extendedData_
         * @param <type> $longitude_
         * @param <type> $coordinates_
         */
        public function shn_sm_Geo_Add_Polygon($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            /*
            <Polygon id="ID">
            <!-- specific to Polygon -->
            <extrude>0</extrude>                       <!-- boolean -->
            <tessellate>0</tessellate>                 <!-- boolean -->
            <altitudeMode>clampToGround</altitudeMode> 
            <!-- kml:altitudeModeEnum: clampToGround, relativeToGround, or absolute -->
            <outerBoundaryIs>
            <LinearRing>
            <coordinates>...</coordinates>         <!-- lon,lat[,alt] -->
            </LinearRing>
            </outerBoundaryIs>
            <innerBoundaryIs>
            <LinearRing>
            <coordinates>...</coordinates>         <!-- lon,lat[,alt] -->
            </LinearRing>
            </innerBoundaryIs>
            </Polygon>
             */
            
            $newPlacemarkPolygonNode = $this->dom->createElement('Polygon');
            $newPlacemarkOuterBoundaryIsNode = $this->dom->createElement('outerBoundaryIs');
            $newPlacemarkLinearRingNode = $this->dom->createElement('LinearRing');
            $coords = '';
            foreach ($coordinates_ as $xyz){
                $longitude = $xyz[0];
                $latitude = $xyz[1];
                $height = $xyz[2];
                $coords += ' ' . $longitude . ',' . $latitude . ',' . $height;
            }
            $newPlacemarkCoordinateNode = $this->dom->createElement('coordinates', $coords); 
            $newPlacemarkLinearRingNode->appendChild($newPlacemarkCoordinateNode);
            $newPlacemarkOuterBoundaryIsNode->appendChild($newPlacemarkLinearRingNode);
            $newPlacemarkPolygonNode->appendChild($newPlacemarkOuterBoundaryIsNode);
            
            // Creates new Placemark element and appends data elements to them.
            $newPlacemarkNode = $this->_shn_sm_Geo_Create_Placemark(
                $id_, $name_, NULL, NULL, $author_, $link_, NULL, NULL, 
                NULL, NULL, $description_, NULL, $timestamp_, NULL, 
                NULL, $extendedData_, $newPlacemarkPolygonNode);
        
            // May wish to change in future if use more than 1 Folder !!!
            $this->dom->getElementsByTagName('Folder')->item(0)->appendChild($newPlacemarkNode);
        }
        
        /**
         * Checks to see if dom contains style related to icon.
         * 
         * returns TRUE if style for icon allready exists FALSE if not.
         * 
         * @param <type> $icon_
         * @return <type>
         */
        private function _shn_sm_KML_style_check($icon_)
        {
            $styles = $this->dom->getElementsByTagName('Style');
            for($i = 0; $i < $styles->length; $i++) {
                $icon_check = $styles->item($i)->getAttribute('id');
                if($icon_check == $icon_){
                    return TRUE;
                }
            }
            return FALSE;
        }
        
        
        /**
         * Creates and appends new Style element containing a icon refrance
         * link useing $icon_ to the DOM. 
         * Styles id = $icon_
         * 
         * @param <type> $icon_
         * @return <type>
         */
        private function _shn_sm_KML_Add_Style($icon_)
        {
            $newStyleNode = $this->dom->createElement('Style');
            $newStyleNode->setAttribute('id', $icon_);

            // Creates the new Icon Style element and appends it to the Style element.
            $newIconStyleNode = $this->dom->createElement('IconStyle');
            $newIconColorNode = $this->dom->createElement('color', $mStyle_default_Icon_Color);
            $newIconScaleNode = $this->dom->createElement('scale', $mStyle_default_Icon_Scale);
            $newIconNode = $this->dom->createElement('Icon');
            $newIconHrefNode = $this->dom->createElement('href', $icon_);
            $newIconNode->appendChild($newIconHrefNode);
            $newIconStyleNode->appendChild($newIconColorNode);
            $newIconStyleNode->appendChild($newIconScaleNode);
            $newIconStyleNode->appendChild($newIconNode);
            $newStyleNode->appendChild($newIconStyleNode);
            
            // Appends to DOM beneath last Style element
            $docNodes = $this->dom->getElementsByTagName('Document');
            if($docNodes->length > 0){
                $mainFolderNode = $this->dom->getElementsByTagName('Folder');
                if($mainFolderNode->length > 0){
                    $this->dom->getElementsByTagName('Document')->item(0)->insertBefore($newStyleNode, $mainFolderNode->item(0));
                    return TRUE; 
                }  
            }
            return FALSE;
        }
        
        
        private function _shn_sm_Geo_Create_Placemark(
            $id_, $name_, $visibility_, $open_, $author_, $link_, $address_, $AddressDetails_, 
            $phoneNumber_, $snippet_, $description_, $abstractView_, $timestamp_, $styleUrl_, 
            $region_, $extendedData_, $geometry_)
        {
            
            /*
             <Placemark id="ID">
              <!-- inherited from Feature element -->
              <name>...</name>                      <!-- string -->
              <visibility>1</visibility>            <!-- boolean -->
              <open>0</open>                        <!-- boolean -->
              <atom:author>...<atom:author>         <!-- xmlns:atom -->
              <atom:link>...</atom:link>            <!-- xmlns:atom -->
              <address>...</address>                <!-- string -->
              <xal:AddressDetails>...</xal:AddressDetails>  <!-- xmlns:xal -->
              <phoneNumber>...</phoneNumber>        <!-- string -->
              <Snippet maxLines="2">...</Snippet>   <!-- string -->
              <description>...</description>        <!-- string -->
              <AbstractView>...</AbstractView>      <!-- Camera or LookAt -->
              <TimePrimitive>...</TimePrimitive>
              <styleUrl>...</styleUrl>              <!-- anyURI -->
              <StyleSelector>...</StyleSelector>
              <Region>...</Region>
              <Metadata>...</Metadata>              <!-- deprecated in KML 2.2 -->
              <ExtendedData>...</ExtendedData>      <!-- new in KML 2.2 -->

              <!-- specific to Placemark element -->
              <Geometry>...</Geometry>
            </Placemark> 
             */
            
            
            // Creates new Placemark element and appends data elements to them.
            $newPlacemarkNode = $this->dom->createElement('Placemark');
            $newPlacemarkNode->setAttribute('id', $id_);

            if('' != $name_){
                $newPlacemarkNameNode = $this->dom->createElement('name', $name_);
                $newPlacemarkNode->appendChild($newPlacemarkNameNode);
            }
            
            if('' != $visibility_){
                $newPlacemarkVisibilityNode = $this->dom->createElement('visibility', $visibility_);
                $newPlacemarkNode->appendChild($newPlacemarkVisibilityNode);
            }
            
            if('' != $open_){
                $newPlacemarkOpenNode = $this->dom->createElement('open', $open_);
                $newPlacemarkNode->appendChild($newPlacemarkOpenNode);
            }
            
            if('' != $author_){
                $newPlacemarkAtomAuthorNode = $this->dom->createElement('atom:author');
                $newPlacemarkAtomAuthorNameNode = $this->dom->createElement('atom:name', $author_);
                $newPlacemarkAtomAuthorNode->appendChild($newPlacemarkAtomAuthorNameNode);
                $newPlacemarkNode->appendChild($newPlacemarkAtomAuthorNode);
            }
            
            if('' != $link_){
                $newPlacemarkAtomLinkNode = $this->dom->createElement('atom:link');
                $newPlacemarkAtomLinkNode->setAttribute('href', $link_);
                $newPlacemarkNode->appendChild($newPlacemarkAtomLinkNode);
            }
            
            if('' != $address_){
                $newPlacemarkAddressNode = $this->dom->createElement('address', $address_);
                $newPlacemarkNode->appendChild($newPlacemarkAddressNode);
            }
            
            if('' != $AddressDetails_){
                // Implement
            }
            
            if('' != $phoneNumber_){
                $newPlacemarkPhoneNumberNode = $this->dom->createElement('phoneNumber', $phoneNumber_);
                $newPlacemarkNode->appendChild($newPlacemarkPhoneNumberNode);
            }
            
            if('' != $snippet_){
                $newPlacemarkSnippetNode = $this->dom->createElement('Snippet', $snippet_);
                $newPlacemarkSnippetNode->setAttribute('maxLines=', '2');
                $newPlacemarkNode->appendChild($newPlacemarkSnippetNode);
            }

            if('' != $description_){
                $newPlacemarkDescriptionNode = $this->dom->createElement('description');
                $newPlacemarkDescriptionNode->appendChild($this->dom->createCDATASection($description_)); 
                $newPlacemarkNode->appendChild($newPlacemarkDescriptionNode);
            }
            
            if('' != $timestamp_){
                $newPlacemarkTimestampNode = $this->dom->createElement('TimeStamp');
                $newPlacemarkTimestampWhenNode = $this->dom->createElement('when', $timestamp_);
                $newPlacemarkTimestampNode->appendChild($newPlacemarkTimestampWhenNode); 
                $newPlacemarkNode->appendChild($newPlacemarkTimestampNode);
            } 

            // check for $icon_. If it does not exist use default.
            if('' != $styleUrl_){
                //check to see if style allready exists. If not make new style.
                if(!$this->_shn_sm_KML_style_check($styleUrl_)){
                    $this->_shn_sm_KML_Add_Style($styleUrl_);
                }
                $newPlacemarkIconNode = $this->dom->createElement('styleUrl', ('#' . $styleUrl_));
            } else {
                $newPlacemarkIconNode = $this->dom->createElement('styleUrl', '#default');
            }
            $newPlacemarkNode->appendChild($newPlacemarkIconNode);

            
            if('' != $region_){
                $newPlacemarkNode->appendChild($region_);
            }
            
            if('' != $extendedData_){
                $newPlacemarkExtendedDataNode = $this->dom->createElement('ExtendedData', $extendedData_);
                $newPlacemarkNode->appendChild($newPlacemarkExtendedDataNode);
            }
            
            $newPlacemarkNode->appendChild($geometry_);
            
            return $newPlacemarkNode;

        }
    }

    
    
    
    
    
    
      









    
    /**
     * GML PARSER
     *
     *
     *
     */
    class GMLFactory extends GeoFactoryDownload implements geoFactorysDownload
    {
        
        
        private $mmetadata_Description = 'gml files';
        private $mmetadata_AuthorName = 'peter';
        private $mmetadata_Copyright = 'no-one';
        private $mmetadata_Link = 'www.sahana.lk';
        private $mmetadata_Time = '2008-05-25T18:30:02Z';
        private $mmetadata_Keywords = 'sahana keywords';
        
        
        private $mMetadata_Disaster_Name = 'Disaster';
        private $mMetadata_Description = 'gml files';
        private $mMetadata_Name = 'Sahana feed';
        
        function __construct()
        {
            $this->dom = new DOMDocument('1.0', 'UTF-8');
            
                        /*
            <gml:description>
                Educational institutions with student populations exceeding 500.
            </gml:description>
            <gml:name>School districts in the North Region.</gml:name>
            <gml:boundedBy>
                <gml:Box srsName="http://www.opengis.net/gml/srs/epsg.xml#4326">
                    <gml:coord>
                        <gml:X>0</gml:X>
                        <gml:Y>0</gml:Y>
                    </gml:coord>
                    <gml:coord>
                        <gml:X>50</gml:X>
                        <gml:Y>50</gml:Y>
                    </gml:coord>
                </gml:Box>
            </gml:boundedBy>
             */
            
            // Creates the root GML element and appends it to the root document.
            $gmlNode = $this->dom->createElement('gml:' . $mMetaData_Disaster_Name);
            $gmlNode->setAttribute('xmlns:gml', 'http://www.opengis.net/gml' );
            $gmlNode->setAttribute('xmlns:xlink', 'http://www.w3.org/1999/xlink' );
            $gmlNode->setAttribute('xmlns:xsi', 'http://www.w3.org/2000/10/XMLSchema-instance');
         
            $metadataNode = $this->dom->createElement('gml:metadata', $this->mMetadata_Name);
            
            // Creates the metadata elements and append them to the Document element.
            $metadataNameNode =         $this->dom->createElement('name', $this->mMetadata_Name);
            $metadataDescritptionNode = $this->dom->createElement('desc', $this->mMetadata_Description);
            $metadataDescritptionNode = $this->dom->createElement('desc', $this->mmetadata_Description);
            $metadataAuthorNode =       $this->dom->createElement('author', $this->mmetadata_AuthorName);
            $metadataCopyrightNode =    $this->dom->createElement('copyright', $this->mmetadata_Copyright);
            $metadataLinkNode =         $this->dom->createElement('link', $this->mmetadata_Link);
            $metadataTimeNode =         $this->dom->createElement('time', $this->mmetadata_Time);
            $metadataKeywordsNode =     $this->dom->createElement('keywords', $this->mmetadata_Keywords);          
            $defaultIconStyleNode =     $this->dom->createElement('IconStyle');
            
            // Appends
            $metadataNode->appendChild($metadataNameNode);
            $metadataNode->appendChild($metadataDescritptionNode);
            $metadataNode->appendChild($metadataAuthorNode);
            $metadataNode->appendChild($metadataCopyrightNode);
            $metadataNode->appendChild($metadataLinkNode);
            $metadataNode->appendChild($metadataTimeNode);
            $metadataNode->appendChild($metadataKeywordsNode);
            $gpxNode->appendChild($metadataNode);
            
            
            $this->dom->appendChild($gmlNode);
            
        }
        
        public function shn_sm_Geo_Add_Point($id_, $name_, $author_, $link_, $description_, $timestamp_, $icon_, $extendedData_,  $coordinates_)
        {
            $new_PointNode = $this->dom->createElement('gml:Point');
                
            
            $new_PointCoordinatesNode = $this->dom->createElement('gml:coordinates',  $coordinates_[0][0] . ', ' .  $coordinates_[0][1] . ', ' . $coordinates_[0][2]);
            $new_PointNode->appendChild($new_wptUpdatedNode);
            
            if('' != $name_){
                
            }    

        }
        
        public function shn_sm_Geo_Add_Path($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            
        }
        
        public function shn_sm_Geo_Add_Polygon($id_, $name_, $author_, $link_, $description_, $timestamp_, $extendedData_, $coordinates_)
        {
            
        }
        
    }
    
    

