<?
/**
 * @name         PL User Services
 * @version      24
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0221
 */


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
$p->p_uuid = "pl.nlm.nih.gov/person.4001384";
$p->load();
//echo "\n\n".print_r(get_defined_vars(), true)."\n\n";
echo "\n\n".print_r(var_dump($p->edxl), true)."\n\n";

/*
//$p->theString = file_get_contents('reference_REUNITE3.xml');
//$p->xmlFormat = "REUNITE3";

$p->theString = file_get_contents('TP.xml');
//$p->theString = file_get_contents('reference_TRIAGEPIC1.xml');
$p->xmlFormat = "TRIAGEPIC1";

$p->parseXml();
$p->rep_uuid = 1;
$p->insert();

echo "\n\n".$p->p_uuid."\n\n";
*/

