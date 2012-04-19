<?
/**
 * @name         Push Out Post
 * @version      13
 * @package      pop
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0222
 */


ini_set( "display_errors", "stdout");
error_reporting(E_ALL);


// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";

// include required libraries
require("../../mod/lpf/lib_lpf.inc");
require("../../conf/sahana.conf");
require("../../3rd/adodb/adodb.inc.php");
require("../../inc/handler_db.inc");
require("../../inc/lib_uuid.inc");
require("../../inc/lib_image.inc");

$body = "Here is a test message.";

echo "ok\n";

$p = new pop();
$p->sendMessage("g@miernicki.com", "g", "subject", $body, $body);
echo $p->spit();
