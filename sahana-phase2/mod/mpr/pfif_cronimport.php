<?php
/**
* @package     pfif
* @version      1.1
* @author       Carl H. Cornwell <ccornwell@mail.nih.gov>
* LastModified: 2010:0308:1402
* License:      LGPL
* @link         TBD
*/
// print "Configuring error reporting  ...\n";
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");


// cron job task for for mpr_pfif import

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";
require_once("../../conf/sysconf.inc.php");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");
require_once("pfif.inc");
require_once $global['approot'] . 'mod/mpr/pfif_util.inc.php';
require_once $global['approot'] . 'mod/mpr/pfifconf.inc.php'; // TODO: Replace this with pfif_repository
require_once $global['approot'] . 'mod/mpr/pfif_repository.inc';
require_once $global['approot'] . 'mod/mpr/pfif_croninit.inc';

/**
* Switch database in order to support multiple DB instances. 
* TBD: how are disasters mapped to repositories?
*/
function shn_db_use($db_name,$db_host=null) {
global $global, $conf;

    if (empty($db_host)) $db_host = $conf['db_host'];
    $global['db']->Close();
    $global['db'] = NewADOConnection($conf['db_engine']);
    $_host_port = $db_host.(isset($conf['db_port'])?':'.$conf['db_port']:'');
    $global['db']->Connect($_host_port,$conf['db_user'],$conf['db_pass'],$db_name);
}

/**
 *  Update the harvest log for the specified repository
 */
function update_harvest_log($r, $status) {
    $pfif_info = $_SESSION['pfif_status'];
    $pfif_info['end_time'] = time();
    $r->end_import($status,$pfif_info);
}
 /*
  -----------------------------------------------------------------------------------------------------------------------
   */
print_r($_SERVER);
print "Using db ".$global['db']->database."\n";
// die("\n");

$repositories = Pfif_Repository::find_source(); // Get all sources
if (!$repositories) {
    die("EXITING TEST WITH STATUS = FAILED\n");
}

$sched_time = time();
$next = array(); // list of next scheduled times for each repository
$import_repos = array();

foreach ($repositories as $r) {
    if ($r->is_ready_for_import($sched_time)) {
        add_pfif_service($r);
        $import_repos[$r->id] = $r;
        $next[$r->id] = $r->sched_interval_minutes*60 + $sched_time;
    } else {
        $next[$r->id] = $r->sched_interval_minutes*60 + 
                        $r->harvest_log->end_time;
    }
}
unset($r);
unset($repositories);

print "Queued imports:\n".print_r($pfif_conf,true)."\nNext import:";
print_r($next);
print "\n";

// die("CONFIGURING TEST DRIVER FOR REPOSITORY IMPORT SCHEDULING\n");

$import_queue = $pfif_conf['services'];
foreach ($import_queue as $service_name => $service) {
    $repos = $import_repos[$pfif_conf['map']][$service_name];
    $incident_conf = $pfif_conf['service_to_incident'][$service_name];
    $pfif_conf['disaster_id'] = $incident_conf['disaster_id'];
    
    $service_uri = $service['feed_url'];
    $pfif_uri = $service_uri.
                    '?min_entry_date=2010-01-27T19:20:00Z'.
                    '&max_results=5'.
                    '&skip=15';
    print "IMPORT REQUEST: $pfif_uri \n";
    $p = new Pfif();
    $p->setPfifConf($pfif_conf);
    //$_SESSION['user_pref_ims_incident_id'] = $incident_conf['incident_id'];

    $repos->start_import('scheduled','in');
    try {
        $loaded = $p->loadFromXML($pfif_uri);

        if ($loaded) {
            shn_db_use($incident_conf['db_name'],$incident_conf['db_host']);
            if (false) { // Output to database for production
                $loaded = $p->storeInDatabase();
                print "Import ".($loaded ? "stored" : "store failed")."\nl";        
            } else { // Output to file for test/debug
                $xml =  $p->storeInXML(PFIF_V_1_2); // PFIF_V_1_1);
                // print $xml;
                $logfile_name = 'crontest_'.$service_name.'.xml'; 
                $fh = fopen($logfile_name,'a+');
                $charstowrite = strlen($xml);
                $written = fwrite($fh,$xml,$charstowrite);
                fclose($fh);
                print "wrote $written of $charstowrite characters to $logfile_name\n";
            }
            update_harvest_log('completed');
        } else {
           print "Import failed from repository $service_name\n";
            update_harvest_log('error');
        }
        unset ($p);
    } catch (Exception $e) {
        error_log("Error in import: ".$e->getMessage()."\n");
    }
}
unset($service);
