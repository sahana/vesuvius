<?
/**
 * @name         Push Out Post
 * @version      1.0
 * @package      pop
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


//error_reporting(E_STRICT);
ini_set( "display_errors", "stdout");
error_reporting(E_ALL);


// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require_once("../../mod/lpf/lib_lpf.inc");
require_once("../../conf/sahana.conf");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once("../../inc/lib_uuid.inc");
require_once("../../inc/lib_image.inc");

$body = "Here is a test message.";

echo "ok\n";

$p = new pop();
$p->sendMessage("jochow@mail.nih.gov", "Disaster4@mail.nih.gov", "subject", $body, $body);
echo $p->spit();
