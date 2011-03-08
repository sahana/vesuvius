<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Nilushan Silva
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */

// PFIF 1.1

// print "Configuring error reporting  ...\n";
error_reporting(E_ALL | E_STRICT); // E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

function get_export_params($repository_id) {
    // TODO: implement retrieval from pfif_repository table
    // for now, hard coding google or google_chile params
    $params = array(2 =>
                        array('service_name'=>'google',
                              'last_entry'=>'2010-02-01 23:44:00',
                              'max_record_count'=>'2'),
                    4 =>
                        array('service_name'=>'google_chile',
                              'last_entry'=>'2010-03-04T21:14:41Z',
                              'max_record_count'=>'2'));
    $entry = $params[$repository_id];
    return $entry;
}

// cron job task for for mpr_pfif export

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

require("../../conf/sysconf.inc.php");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");

require_once $global['approot'] . 'mod/mpr/add.inc';
require_once $global['approot'] . 'mod/mpr/pfif_util.inc.php';
require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';
require("pfif.inc");
// print "Loaded pfif.inc\n";
define('HAITI_REPOSITORY',2);
define('CHILE_REPOSITORY',4);
print "database = ".$conf['db_name']."\n";
$repository_id = $conf['db_name'] == 'sahanaCEPL' ? CHILE_REPOSITORY : HAITI_REPOSITORY;

$export_params = get_export_params($repository_id);
$service_name = $export_params['service_name'];
$start_time = $export_params['last_entry'];

print_r($pfif_conf);
print_r($export_params);

$p = new Pfif();

if (true) {
    $loaded = $p->loadFromDatabase('all',$start_time);
    print "load for post to $service_name at $start_time ".($loaded ? "suceeded with $loaded records" : "failed")."\n";
} else {
    $id = 'LPFp-46833'; // CEPL web('pl.nlm.nih.gov/person.2140';)// 'CEPL-20100301-0002-e7fcd'; // HEPL ('LPFp-46833');
    $loaded = $p->loadFromDatabase('id?'.$id);
    print "load $id".($loaded ? " suceeded with $loaded records" : " failed")."\n";
}

if ($loaded && $loaded > 0) {
   $xml =  $p->storeInXML(PFIF_V_1_2,'_test'); // PFIF_V_1_1); // TODO: need to exclude any previously uploaded records with person_status.upated = start_time.

   $fh = fopen('crontest.xml','w');
   $charstowrite = strlen($xml);
   $written = fwrite($fh,$xml,$charstowrite);
   fclose($fh);
   print "Logged $written of $charstowrite characters to crontest.xml\n";

   // $post_status = $p->postDbToService('LPFp-46833',$service_name); // TESTING
   $post_status = "TESTING: record(s) not uploaded"; // $p->postToService('xml',$xml,$service_name);
   print "Post status:\n $post_status \n";
} else {
   print "Export failed: no records to upload\n";
}
// require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';
// echo print_r($pfif_conf,true);
