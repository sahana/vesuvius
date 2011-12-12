<?php
// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

// Delete all records for an incident. Requires an incident id.
// Optional: Supply a p_uuid to delete through this record only.
//
// set approot since we don't know it yet
$global['approot'] = getcwd() . "/../";
require_once("../conf/sahana.conf");
require_once("../3rd/adodb/adodb.inc.php");
require_once("../inc/handler_db.inc");
require_once("../inc/lib_uuid.inc");
require_once("../inc/lib_image.inc");
require_once("../inc/lib_locale/gettext.inc");

/*
 -----------------------------------------------------------------------------------------------------------------------
*/

if ($argc < 2 || $argc > 3) {
   die("Wrong number of arguments: Expecting an incident ID and optional max p_uuid.\n");
}
$incident_id = $argv[1];
$max_p_uuid = $argv[2];

print "Beginning cleanup at " . strftime("%c") . "\n";
print "Using db " . $global['db']->database . "\n";
$webroot = $global['approot'] . "www/";

$limit_prune = (empty($max_p_uuid))? '':"up through record $max_p_uuid ";
print "Prune of $incident_id ".$limit_prune."has begun.\n";

// If we are removing all records, reset last_count for last export log  record. (Otherwise,
// the first 'last_count' new records won't get exported.)
If (!$limit_prune) {
   $sql = "UPDATE pfif_export_log pe, pfif_repository pr SET pe.last_count=0 WHERE " .
       "pr.incident_id=$incident_id " .
       "AND pe.repository_id = pr.id " .
       "AND pe.status = 'paused'";
   $st = $global['db']->Execute($sql);
   if($st === false) {
      $errchk = $global['db']->ErrorMsg();
      die("Error updating last_count for export log for this incident: ".$errchk);
   }
}

// Person_status table provides strict chronological ordering. Fetch person_status.status_id for this p_uuid.
if (!empty($max_p_uuid)) {
   $sql = "SELECT status_id FROM person_status WHERE p_uuid = '".$max_p_uuid."'";
   $result = $global['db']->GetRow($sql);
   if ($result === false) {
      $errchk = $global['db']->ErrorMsg();
      die("Database error: ".$errchk."\n");
   } else if (count($result) == 0) {
      die("Incorrect person ID: '$max_p_uuid'!\n");
   }
}
$status_id = $result['status_id'];

// Do deletions.

// Get all missing persons for this incident (but not their reporters).
$status_check = empty($max_p_uuid)? '':"AND ps.status_id <= $status_id";
$sql = "SELECT pu.p_uuid FROM person_uuid pu, person_status ps WHERE " .
       "pu.incident_id=$incident_id " .
       "AND ps.p_uuid = pu.p_uuid " .
       $status_check;
$p_uuids = $global['db']->GetCol($sql);
if($p_uuids === false) {
   $errchk = $global['db']->ErrorMsg();
   die("Error getting records for this incident: ".$errchk);
}

foreach ($p_uuids as $p_uuid) {
   // Delete any associated images.
   $sql = "SELECT url, url_thumb FROM image WHERE p_uuid = '$p_uuid'";
   $image_result = $global['db']->GetRow($sql);
   if($image_result === false) {
      $errchk = $global['db']->ErrorMsg();
      //die("Error getting images for this incident: ".$errchk);
      error_log("Error getting images for this incident: ".$errchk);
   } else if (count($image_result) > 0) {
      // There is an image so delete it and its thumbnail.
      $file = $webroot . $image_result['url'];
      //print "Deleting '" . $file . "'\n";
      if (!unlink($file)) {
         error_log("Unable to delete $file.");
      }
      $thumb = $webroot . $image_result['url_thumb'];
      if ($thumb != $file) {
         //print "Deleting '" . $thumb . "'\n";
         if (!unlink($thumb)) {
            error_log("Unable to delete $thumb.");
         }
      }
   }
   // Delete the person in question and all dependent data (such as reporter) .
   $sql = "CALL delete_reported_person('$p_uuid', 1)";  // delete Notes
   $st = $global['db']->Execute($sql);
   if($st === false) {
      $errchk = $global['db']->ErrorMsg();
      //die("Error calling delete_pfif_person for this incident: ".$errchk);
      error_log("Error calling delete_person for this incident: ".$errchk);
   }
   print "Deleted '$p_uuid'\n";
}
print count($p_uuids)." persons deleted from incident $incident_id.\n";

print "SOLR will do a full reload of indexes.\n";
fopen("http://pl.nlm.nih.gov:8983/solr/dataimport?command=full-import", "r");

print "Cleanup completed at ".strftime("%c")."\n";
