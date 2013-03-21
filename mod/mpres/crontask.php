<?php
/**
 * @name         MPR Email Service
 * @version      21
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */

// cron job for mpres

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");
require_once("../../mod/lpf/lib_lpf.inc");
require_once("class.mpres.php");

// instantiating the instance performs full execution
$m = new mpres();
