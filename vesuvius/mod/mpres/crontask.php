<?php
/**
 * @name         MPR Email Service
 * @version      1.9
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0728
 */

// cron job for mpres

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require_once("class.mpres.php");
require_once("class.lpfPatient.php");
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");
require_once("../../mod/lpf/lib_lpf.inc");

$m = new mpres();
$m->loopInbox();
echo $m->spit();
