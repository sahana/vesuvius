<?php

/**
 * @package     pfif
 * @version      1.1
 * @author       Carl H. Cornwell <ccornwell@mail.nih.gov>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * LastModified: 2011:0719
 * License:      LGPL
 * @link         TBD
 */
// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE); // E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

// cron job task for for pfif export
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

print "database = " . $conf['db_name'];

// Get all PFIF repository sources.
$repositories = Pfif_Repository::find_sink();
if (!$repositories) {
   die("No repositories ready for harvest.\n");
}
//var_dump("Found repositories for export", $repositories);

$sched_time = time();
$export_repos = array();
foreach ($repositories as $r) {
   if ($r->is_ready_for_harvest($sched_time)) {
      add_pfif_service($r);             // initializes pfif_conf
      //var_dump("exporting to repository",$r);
   }
}
unset($r);
unset($repositories);
$export_queue = $pfif_conf['services'];
//print "Queued exports:\n".print_r($export_queue,true)."\n";

foreach ($export_queue as $service_name => $service) {
   $repos = $service['repository'];
   $req_params = $repos->get_request_params();
   $min_entry_date = $req_params['min_entry_date'];
   $skip = $req_params['skip'];
   $subdomain = empty($service['subdomain'])? '' : '?subdomain='.$service['subdomain'];
   $auth_key = empty($service['auth_key'])? '' : '?key='.$service['auth_key'];
   $pfif_uri = $service['post_url'].$auth_key;
   $at_subdomain = " at subdomain $subdomain ";
   $p = new Pfif();
   $p->setService($service_name,$service);

   $repos->start_harvest('scheduled', 'out');
   print "\n\nExport started to ".$service['post_url']." at ".$repos->get_log()->start_time . "\n";
   $local_date = local_date($min_entry_date);
   $loaded = $p->loadFromDatabase($local_date, null, 0, $skip);
   print "load for post to $service_name for records after $local_date " . 
         (($loaded != -1) ? "suceeded with $loaded records" : "failed") . "\n";

   if ($loaded > 0) {
      // Export only original records after min_entry_date
      $xml = $p->storeInXML(false, true);
      if ($xml != null) {
         $fh = fopen('cronpfif.xml', 'w');
         $charstowrite = strlen($xml);
         $written = fwrite($fh, $xml, $charstowrite);
         fclose($fh);
         //print "Logged $written of $charstowrite characters to cronpfif.xml\n";
   
         $post_status = $p->postToService('xml', $xml, $service_name);
         // person and note counts are in $_SESSION['pfif_info'].
         // TODO: Adjust person and note counts depending on post_status.
         update_harvest_log($repos, $req_params, 'completed');
         print "Post status:\n $post_status \n";
      } else {
         update_harvest_log($repos, $req_params, 'completed');
         print "Export complete: no records to upload\n";
      }
   } else {
      if ($loaded == -1) {
         update_harvest_log($repos, $req_params, 'error');
         print "Export failed: no records to upload\n";
      } else {
         update_harvest_log($repos, $req_params, 'completed');
         print "Export completed: no records to upload\n";
      }
   }
   unset($_SESSION['pfif_info']);
}
