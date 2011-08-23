<?
/**
 * @name         PL User Services
 * @version      1.9.4
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0705
 */

//error_reporting(E_STRICT);
ini_set( "display_errors", "stdout");
error_reporting(E_STRICT);

global $global;

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require_once("../../mod/lpf/lib_lpf.inc");
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");

$p = new person();
$p->init();

$p->theString = file_get_contents('referenceXML_RU.xml');
//$p->theString = file_get_contents('RU.xml');
$p->xmlFormat = "REUNITE3";

//$p->theString = file_get_contents('referenceXML_TP.xml');
//$p->xmlFormat = "TRIAGEPIC1";

$p->parseXml();
$p->insert();

echo "\n\n".$p->p_uuid."\n\n";





