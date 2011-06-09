<?
/**
 * @name         PL User Services
 * @version      1.9.2
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0606
 */


require_once("../../3rd/nusoap/lib/nusoap.php");
//$wsdl = "https://plstage.nlm.nih.gov/~miernickig/sahanaDev/www/index.php?wsdl";
$wsdl = "https://pl.nlm.nih.gov/?wsdl";
$client = new nusoap_client($wsdl);
$result = $client->call('getEventListUser', array('username'=>'testDontDelete', 'password'=>'dontDelete99'));
echo "<pre>".print_r($result, true)."</pre>";
