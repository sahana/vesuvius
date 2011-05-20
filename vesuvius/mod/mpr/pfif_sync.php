<?php
/**
 * @package      pfif
 * @version      1.0
 * @author       Leif  <lneve@mail.nih.gov>
 * LastModified: 2011:0411:1502
 * License:      LGPL
 * @link         TBD
 */
// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");

// This program syncs up certain Sahana DB fields (e.g. last_seen, last_updated and
// opt_status) with the associated fields from PFIF Notes. It achieves this by retrieving 
// all notes that are more recent than information in Sahana and applying them in
// chronological order to the Sahana. This way newer values supersede older values.

// set approot since we don't know it yet
$global['approot'] = getcwd() . "/../../";
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");
require_once("../../inc/lib_locale/gettext.inc");
require_once("pfif.inc");
require_once $global['approot'] . 'mod/mpr/pfif_util.inc.php';
require_once $global['approot'] . 'mod/mpr/conf.inc';

/*
 -----------------------------------------------------------------------------------------------------------------------
*/

print "Starting Sahana-PFIF sync at " . strftime("%c") . "\n";
print "Using db " . $global['db']->database . "\n";
// Store Japanese correctly.
$global['db']->Execute("SET NAMES 'utf8'");

// Get all persons with their last update time and information which needs to be checked for updating.
$sql = "SELECT ps.p_uuid,ps.last_updated,ps.opt_status FROM person_status ps";
$result = $global['db']->Execute($sql);
if($result === false) {
   $errchk = $global['db']->ErrorMsg();
   die("Error getting records needing update: ".$errchk);
}

// Loop through persons to update each one with any new notes.
$count_updated = 0;
while ($row = $result->FetchRow()) {
   $p_uuid = $row['p_uuid'];
   $last_updated = $row['last_updated'];
   $old_status = $row['opt_status'];
   // Get all notes for this person with a later source date in source date order.
   // FIXME: Notes with equal time that came in before Person are a problem.
   $sql = "SELECT pn.source_date,pn.status,pn.found,pn.last_known_location". 
        " FROM pfif_note pn WHERE pn.p_uuid = '".$p_uuid."'".
        " AND pn.source_date > '".$last_updated."' ORDER BY pn.source_date";
   $note_result = $global['db']->Execute($sql);
   if ($note_result === false) {
      $errchk = $global['db']->ErrorMsg();
      die("Error getting later notes: ".$errchk);
   }
   $source_date = $last_updated;
   while ($note_row = $note_result->FetchRow()) {
      // Update last_seen if present.
      if (!empty($note_row['last_known_location'])) {
         $last_known_location = mysql_real_escape_string($note_row['last_known_location']);
      } else {
         $last_known_location = '';
      }
      // Determine PFIF mapping.
      $status = $note_row['status'];
      $found = $note_row['found'];
      $mapped_status = shn_map_status_from_pfif($status, $found, $old_status);
      $old_status = $mapped_status;
      // Update last_updated.
      $source_date = $note_row['source_date'];
      // Only update last known location if not empty.
      if (!empty($last_known_location)) {
         $sql = "UPDATE person_status ps,person_details pd SET".
             " ps.last_updated='".$source_date."',ps.opt_status='".$mapped_status."',pd.last_seen='".$last_known_location."'".
             " WHERE ps.p_uuid='".$p_uuid."' AND ps.p_uuid = pd.p_uuid";
      } else {
         $sql = "UPDATE person_status ps,person_details pd SET".
             " ps.last_updated='".$source_date."',ps.opt_status='".$mapped_status."'".
             " WHERE ps.p_uuid='".$p_uuid."' AND ps.p_uuid = pd.p_uuid";
      }
      //print $sql."\n";
      $ret = $global['db']->Execute($sql);
      if($ret === false) {
         $errchk = $global['db']->ErrorMsg();
         die("Error performing update: ".$errchk);
      }
   }
   if ($source_date != $last_updated) $count_updated++;
}
print "Sahana-PFIF sync completed at " . strftime("%c") . " $count_updated persons updated.\n";
