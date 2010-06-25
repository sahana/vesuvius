<?php
	$address = "301 Bayside Road, St. Leonard, MD";

	require_once('class.googleGeocoder.php');
	$geocoder = new googleGeocoder();
	try {
		$placemarks = $geocoder->lookup($address);
	} catch(Exception $ex) {
		echo $ex->getMessage();
		exit;
	}
	if (count($placemarks) > 0) {
		foreach ($placemarks as $placemark) {
			echo htmlSpecialChars($placemark)."(".$placemark->getPoint()->getLatitude().",".$placemark->getPoint()->getLongitude().")\n";
		}
	} else {
	         echo "no matches";
	}
