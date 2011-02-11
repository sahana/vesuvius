<?php
// cron job for mpres

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require("class.mpres.php");
require("class.nameParser.php");
require("class.lpfPatient.php");
require("../../conf/sysconf.inc.php");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");

$m = new mpres();
$m->loopInbox();
echo $m->spit();