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

$user = "testDontDelete";
$pass = "dontDelete99";

require_once("../../3rd/nusoap/lib/nusoap.php");
$wsdl = "https://plstage.nlm.nih.gov/~miernickig/vesuvius/vesuvius/www/index.php?wsdl&api=1.9.5";
$client = new nusoap_client($wsdl);
$result = $client->call('getSessionCookie', array('username'=>$user, 'password'=>$pass));

echo "<pre>".print_r($result, true)."</pre>";


