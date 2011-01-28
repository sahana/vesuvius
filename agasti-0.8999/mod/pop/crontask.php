<?php
error_reporting(E_STRICT);

// cron job task for for mpres

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require_once("../lpf/lib_lpf.inc");
require_once("../../conf/sysconf.inc.php");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");

/*
$m = new pop();
$m->loopInbox();
echo $m->spit();
*/