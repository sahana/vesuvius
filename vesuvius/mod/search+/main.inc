<?
/**
 * @name         Search+
 * @version      0.1
 * @package      search+
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1005
 */


// array of events used for generating the home page...
$events = array();


/**
 * Displays a Landing Page
 * @access public
 * @return void
 */
function shn_search+_default() {
	global $global;
	global $events;

	echo "
		<div style=\"padding: 20px 0px 0px 36px;\">
		<h3>To Locate Someone After a Disaster...</h3>
		begin by choosing an event from the list below :<br>
	";

	getList(0);
	if(sizeof($events) > 0 ){
		echo "<br><br><h3>For these events you can search and report new information directly to this registry :</h3>";
		showList();
	}


	$events = array(); // reset
	getList(2);
	if(sizeof($events) > 0 ){
		echo "<br><br><h3>For these events you can search locally and report new information through Google :</h3>";
		showList();
	}


	$events = array(); // reset
	getList(1);
	if(sizeof($events) > 0 ){
		echo "<br><br><h3>For these events you can search only :</h3>";
		showList();
	}

	echo "
		<script>
			document.getElementById('menu').style.visibility = 'hidden';
		</script>
		</div>
	";
}



