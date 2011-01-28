<?php
/**
 * @author       Greg Miernicki <g@miernicki.com>
 * @author       Quentin Zervaas <x@phpriot.com>
 * @package      googleGeocoder
 * @subpackage   mpres
 * @version      1.0
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2010.1008
 */

class googleGeocoder {
	public static $url = 'http://maps.google.com/maps/geo';

	const G_GEO_SUCCESS             = 200;
	const G_GEO_BAD_REQUEST         = 400;
	const G_GEO_SERVER_ERROR        = 500;
	const G_GEO_MISSING_QUERY       = 601;
	const G_GEO_MISSING_ADDRESS     = 601;
	const G_GEO_UNKNOWN_ADDRESS     = 602;
	const G_GEO_UNAVAILABLE_ADDRESS = 603;
	const G_GEO_UNKNOWN_DIRECTIONS  = 604;
	const G_GEO_BAD_KEY             = 610;
	const G_GEO_TOO_MANY_QUERIES    = 620;

	protected $_apiKey;
	protected $_search;

	public function __construct($search, $key = "") {
		$this->_search = $search;
		$this->_apiKey = $key;
		$this->lookup();
	}


	// http://maps.google.com/maps/geo?q=location&output=json&oe=utf8&sensor=false
	public function performRequest($search, $output = "xml") {
		$url = sprintf("%s?q=%s&output=%s&key=%s&oe=utf-8", self::$url, urlencode($search), $output, $this->_apiKey);
		$ch = curl_init($url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		$response = curl_exec($ch);
		curl_close($ch);
		return $response;
	}


	public function lookup() {
		$response = $this->performRequest($this->_search, "xml");
		$xml      = new SimpleXMLElement($response);
		$status   = (int)$xml->Response->Status->code;
		echo "<pre>".print_r($xml,true)."</pre>\n";
		switch ($status) {
			case self::G_GEO_SUCCESS:
				$placemarks = array();
				foreach ($xml->Response->Placemark as $placemark) {
					$placemarks[] = googlePlacemark::FromSimpleXml($placemark);
				}
				//$placemarks[] = "one item";
				return $placemarks;

			case self::G_GEO_UNKNOWN_ADDRESS:
			case self::G_GEO_UNAVAILABLE_ADDRESS:
				//$placemarks[] = "messed up";
				return $placemarks;

			default:
				throw new Exception(sprintf('Google Geo error %d occurred', $status));
		}
	}
}



// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //



class googlePlacemark {
	const ACCURACY_UNKNOWN      = 0;
	const ACCURACY_COUNTRY      = 1;
	const ACCURACY_REGION       = 2;
	const ACCURACY_SUBREGION    = 3;
	const ACCURACY_TOWN         = 4;
	const ACCURACY_POSTCODE     = 5;
	const ACCURACY_STREET       = 6;
	const ACCURACY_INTERSECTION = 7;
	const ACCURACY_ADDRESS      = 8;

	protected $_point;
	protected $_address;
	protected $_accuracy;



	public function setAddress($address) {
		$this->_address = (string)$address;
	}



	public function getAddress() {
		return $this->_address;
	}



	public function __toString() {
		return $this->getAddress();
	}



	public function setPoint(googlePoint $point) {
		$this->_point = $point;
	}



	public function getPoint() {
		return $this->_point;
	}



	public function setAccuracy($accuracy) {
		$this->_accuracy = (int)$accuracy;
	}



	public function getAccuracy() {
		return $this->_accuracy;
	}



	public static function FromSimpleXml($xml) {
		$point = googlePoint::create($xml->Point->coordinates);
		$placemark = new self;
		$placemark->setPoint($point);
		$placemark->setAddress($xml->address);
		$placemark->setAccuracy($xml->AddressDetails['Accuracy']);
		return $placemark;
	}
}



// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //


class googlePoint {
	protected $_lat;
	protected $_lng;

	public function __construct($latitude, $longitude) {
		$this->_lat = $latitude;
		$this->_lng = $longitude;
	}

	public function getLatitude() {
		return $this->_lat;
	}

	public function getLongitude() {
		return $this->_lng;
	}


	public static function create($str) {
		list($longitude, $latitude, $elevation) = explode(',', $str, 3);
		return new self($latitude, $longitude);
	}
}