<?php
/**
 * @name         MPR Email Service
 * @version      1.6
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

// cron job for mpres

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require("class.mpres.php");
require("class.nameParser.php");
require("class.lpfPatient.php");
require("../../conf/sahana.conf");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");

$m = new mpres();
$m->loopInbox();
echo $m->spit();
