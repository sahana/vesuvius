<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */

error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");


// cron job task for for mpr_pfif import

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";
require_once("../../conf/sysconf.inc.php");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once "pfif_harvest_log.inc";

function assert_failure() {
global $global;
    print $_SESSION['test']." assertion failed\n";
    print $global['db']->ErrorMsg()."\n";
}

assert_options(ASSERT_ACTIVE,   true);
assert_options(ASSERT_BAIL,     true);
assert_options(ASSERT_WARNING,  false);
assert_options(ASSERT_CALLBACK, 'assert_failure');

$log = new Pfif_Harvest_Log();
$test_start = time(); // subsequent time tags referenced to test start time
$test_interval = 5;

$repos_id = 1;
$mode = 'scheduled';
$dir = 'in';

$_SESSION['test'] = "start";
$start_status = $log->start($repos_id,$test_start,$mode,$dir);
//print_r($log);
assert($start_status);
print $_SESSION['test'].": passed ...\n";

$log_info = array('first_entry'=>'2010-04-01T01:01:00Z',
                  'last_entry'=>'2010-04-01T01:02:00Z',
                  'last_entry_count' => 1,
                  'pfif_person_count'=>10,
                  'pfif_note_count'=>0,
                  'images_in'=>10,
                  'images_retried'=>0,
                  'images_failed'=>0);
sleep($test_interval);
$_SESSION['test'] = "pause.1";
$pause_status = $log->pause($test_start+120,$log_info);
//print_r($log);
assert($pause_status);
print $_SESSION['test'].": passed ...\n";

$log_info['first_entry'] = '2010-04-01T01:02:00Z';
$log_info['last_entry'] = '2010-04-01T01:03:00Z';
$log_info['images_in'] = 8;
$log_info['images_retried'] = 1;
$log_info['images_failed'] = 2;

sleep($test_interval);
$_SESSION['test'] = "pause.2";
$restart_status = $log->start($repos_id,$test_start+239,$mode,$dir);
$pause_status = $log->pause($test_start+240,$log_info);
//print_r($log);
assert($pause_status);
print $_SESSION['test'].": passed ...\n";

$log_info['first_entry'] = '2010-04-01T01:03:00Z';
$log_info['last_entry'] = '2010-04-01T01:04:00Z';
$log_info['images_in'] = 10;
$log_info['images_retried'] = 0;
$log_info['images_failed'] = 0;

sleep($test_interval);
$_SESSION['test'] = "stop";
$restart_status = $log->start($repos_id,$test_start+359,$mode,$dir);
$stop_status = $log->stop($test_start+360,$log_info);
//print_r($log);
assert($stop_status);
print $_SESSION['test'].": passed ...\n";

$log_info['first_entry'] = '2010-04-01T01:04:00Z';
$log_info['last_entry'] = '2010-04-01T01:05:00Z';
$log_info['images_in'] = 5;
$log_info['images_retried'] = 0;
$log_info['images_failed'] = 0;

// Test start, pause and stop and pause after stop

$_SESSION['test'] = "re-pause";
try {
    $stop_status = $log->pause($test_start+480,$log_info);
    assert(false);
} catch (RuntimeException $rte) {
//    print_r($log);
    assert(true);
    print $_SESSION['test'].": passed ...\n";
} catch (Exception $e) {
//    print_r($log);
    assert(false);
}

$_SESSION['test'] = "re-stop";
try {
    $stop_status = $log->stop($test_start+480,$log_info);
    assert(false);
} catch (RuntimeException $rte) {
//    print_r($log);
    assert(true);
    print $_SESSION['test'].": passed ...\n";
} catch (Exception $e) {
//    print_r($log);
    assert(false);
}

sleep($test_interval);
$_SESSION['test'] = "start new record";
try {
    $start_status = $log->start($repos_id,$test_start+480,$mode,$dir);
//    print_r($log);
    assert($start_status);
    print $_SESSION['test'].": passed ...\n";
} catch (Exception $e) {
//    print_r($log);
    assert(false);
}

sleep($test_interval);
$_SESSION['test'] = "stop second record";
$stop_status = $log->stop($test_start+600,$log_info);
//print_r($log);
assert($stop_status);
print $_SESSION['test'].": passed!\n";

?>