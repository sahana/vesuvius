<?php
/**
 * @name         MPR Email Service
 * @version      1.7
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0324
 */


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
