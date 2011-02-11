<?php
//error_reporting(E_STRICT);
ini_set( "display_errors", "stdout");
error_reporting(E_ALL);


// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require("class.pop.php");
require("../../conf/sysconf.inc.php");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");

$body = "Here is a test message.";

echo "ok\n";

$p = new pop();
$p->sendMessage("g@miernicki.com", "g", "subject", $body, $body);
echo $p->spit();