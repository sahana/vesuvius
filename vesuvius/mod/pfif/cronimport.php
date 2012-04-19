<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */


// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

// cron job task for for pfif import
// set approot since we don't know it yet
$global['approot'] = getcwd() . "/../../";
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("pfif.inc");
require_once("repository.inc");
require_once("croninit.inc");

/**
 *  Log harvest end
 */
function update_harvest_log($r, $req_params, $status) {
   $pfif_info = $_SESSION['pfif_info'];
   $pfif_info['end_time'] = time();
   //var_dump("ending harvest with pfif_info:", $pfif_info);
   $r->end_harvest($status, $req_params, $pfif_info);
}

/*
 -----------------------------------------------------------------------------------------------------------------------
*/

// Update persons or notes, depending on arg 1.
if ($argc < 2) {
   die("Wrong number of arguments: Expecting at least 2.");
} else if ($argv[1] != "person" && $argv[1] != "note") {
   die("Expect 'person' or 'note' as first argument.");
}
$is_person = ($argv[1] == "person") ? true : false;
$is_scheduled = ($argc > 2 && $argv[2] == "test") ? false : true;
$mode = $is_scheduled ? "scheduled" : "test";

print "\nStarting PFIF ".$argv[1]." import at ".strftime("%c")."\n";
print "Using db " . $global['db']->database . " in " . $mode . " mode\n";

// Get all PFIF repository sources.
$repositories = Pfif_Repository::find_source(($is_person)? 'person' : 'note');
if (!$repositories) {
   die("No repositories ready for harvest.\n");
}
//var_dump("Found repositories for import", $repositories);

$sched_time = time();
foreach ($repositories as $r) {
   if ($r->is_ready_for_harvest($sched_time)) {
      add_pfif_service($r); //initialize pfif_conf
   }
}
unset($r);
unset($repositories);

$import_queue = $pfif_conf['services'];
//print "Queued imports:\n".print_r($import_queue,true)."\n";

foreach ($import_queue as $service_name => $service) {
   $repos = $service['repository'];
   //var_dump("repository", $repos);

   $req_params = $repos->get_request_params();
   $pfif_uri = $service['feed_url'] .
           '?min_entry_date=' . $req_params['min_entry_date'] .
           '&max_results=' . $service['max_results'] .
           '&key=' . $service['auth_key'] .
           '&skip=' . $req_params['skip'] .
           '&version=' . $service['version'];
   $p = new Pfif();
   $p->setService($service_name, $service);
   //print_r($pfif_conf);
   try {
      $repos->start_harvest($mode, 'in');
      print "\nImport started from $pfif_uri at " . $repos->get_log()->start_time . "\n";
      if ($is_person) {
         $loaded = $p->loadPersonsFromXML($pfif_uri);
      } else {
         $loaded = $p->loadNotesFromXML($pfif_uri);
      }
      if ($loaded > 0) {
         print "Loaded $loaded XML records. ";
         if ($is_scheduled) { // Output to database for production
            if ($is_person) {
               $stored = $p->storePersonsInDatabase();
            } else {
               $stored = $p->storeNotesInDatabase();
            }
            print "Stored $stored records.\n";
         } else {
            // Output to file for test/debug. (This leverages export functionality.)
            $xml = $p->storeInXML(false); // non-embedded format
            //print $xml;
            $logfile_name = 'crontest_' . $service_name . '.xml';
            $fh = fopen($logfile_name, 'a+');
            $charstowrite = strlen($xml);
            $written = fwrite($fh, $xml, $charstowrite);
            fclose($fh);
            print "wrote $written of $charstowrite characters to $logfile_name\n";
         }
         // Note: For tests, only last_entry_date is saved. (No skip, etc.)
         update_harvest_log($repos, $req_params, 'completed');
      } else {
         if ($loaded == -1) {
            pfif_error_log("Import failed from repository $service_name at ".date("Y-m-d H:i:s")."\n");
         } else {
            print "0 records for import from repository $service_name\n";
         }
         update_harvest_log($repos, $req_params, 'error');
      }
      unset($p);
   } catch (Exception $e) {
      pfif_error_log("Error in import: " . $e->getMessage() . "\n");
   }
   unset($_SESSION['pfif_info']);
}
unset($service);
print "PFIF import completed " . strftime("%c") . "\n";
