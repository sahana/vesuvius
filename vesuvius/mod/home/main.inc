<?
/**
 * @name         Home
 * @version      1.0
 * @package      home
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0405
 */


// array of events used for generating the home page...
$events = array();


/**
 * Displays a Landing Page
 * @access public
 * @return void
 */
function shn_home_default() {
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

	// HEPL HACK!
	echo "
		<br><br><h3>For this event you can search and report new information through our first generation site :</h3>
		<span style=\"line-height: 160%; font-size: 120%;\">
		<span style=\"color: red;\"><span style=\"text-shadow: 1px 1px 1px #000;\">▶</span></span>&nbsp;
		<a href=\"http://hepl.nlm.nih.gov\">Haiti Earthquake People Locator</a></span><br>
	";

	echo "
		<script>
			document.getElementById('menu').style.visibility = 'hidden';
		</script>
		</div>
	";
}



function addChildren($id, $spacer, $closed) {
	global $events;
	global $global;
	$q = "
		SELECT *
		FROM incident
		WHERE parent_id = '".$id."'
		AND closed = '".$closed."'
		ORDER BY date DESC;
	";
	$res = $global['db']->Execute($q);

	// add child to the array and then find its children recursively
	while($row = $res->FetchRow() ){
		$row['spacer'] = $spacer;
		$events[] = $row;
		addChildren($row['incident_id'], 2, $closed);
	}
}



// get a list of events based on the closed status...
function getList($closed) {
	global $global;
	global $events;

	if(isset($_SESSION['group_id'])) {
		$groupSql = "(private_group IS NULL OR private_group = '".$_SESSION['group_id']."')";
	} else {
		$groupSql = "private_group IS NULL";
	}

	$q = "
		SELECT *
		FROM incident
		WHERE parent_id is NULL
		AND closed = '".$closed."'
		AND ".$groupSql."
		ORDER BY date DESC;
	";
	$res = $global['db']->Execute($q);

	// add disasters to the array
	while($row = $res->FetchRow() ){
		$row['spacer'] = 0;
		$events[] = $row;
		addChildren($row['incident_id'], 1, $closed);
	}
}


// show a list of events
function showList() {
	global $global;
	global $events;
	require_once ($global['approot'].'mod/lpf/lib_lpf.inc');

	foreach($events as $row) {
		if(trim($row['description']) == "") {
			$descript = "";
		} else {
			$descript = " - ".$row['description'];
		}

		echo "<span style=\"line-height: 160%; font-size: 120%;\">";

		if(isset($_GET['shortname'])) {
			$goBack = "../";
		} else {
			$goBack = "";
		}

		if($row['spacer'] == 0) {
			echo "
				<span style=\"color: red;\"><span style=\"text-shadow: 1px 1px 1px #000;\">▶</span></span>&nbsp;
				<a href=\"".makeBaseUrlMinusEventForHome()."/".$row['shortname']."/index.php?mod=inw&act=default\">".$row['name']."</a>".$descript."<br>
			";
		} else if($row['spacer'] == 1) {
			echo "
				&nbsp;&nbsp;&nbsp;&nbsp;
				<span style=\"color: orange;\"><span style=\"text-shadow: 1px 1px 1px #000;\">▶</span></span>&nbsp;
				<a href=\"".makeBaseUrlMinusEventForHome()."/".$row['shortname']."/index.php?mod=inw&act=default\">".$row['name']."</a>".$descript."<br>
			";
		} else if($row['spacer'] == 2) {
			echo "
				&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;
				<span style=\"color: yellow;\"><span style=\"text-shadow: 1px 1px 1px #000;\">▶</span></span>&nbsp;
				<a href=\"".makeBaseUrlMinusEventForHome()."/".$row['shortname']."/index.php?mod=inw&act=default\">".$row['name']."</a>".$descript."<br>
			";
		}

		echo "</span>";
	}
}




/*
function shn_home_old() {
	echo "
		This is an organized online bulletin board to aid in locating someone after a disaster.<br><br>
		Anyone may use the search feature, without logging in or registering for an account to search for people. You may also get basic information about someone missing or found, including photos, as reported by family members, friends, or participating local hospitals.<br>
		<br>
		<br>
		<span class=\"styleTehButton\" onclick=\"location.href='index.php?mod=inw&amp;act=default';\">Click Here to Begin Searching for People</span>
		<br>
		<br>
		<br><br>
		To do more with the site like reporting people, first <a href=\"index.php?act=signup\">create an account</a> and login. Then you can:<br>
		<br>
		<ul>
			<li>Report someone as missing, and include photographs of them</li>
			<li>Update that report, e.g., if the person is found or their status changes</li>
			<li>Share the ability to update a report with family members and friends</li>
			<li>Receive email notifications when the status of a person changes or more information is reported about them.
		</li></ul>
		<br>
		Participating local hospitals can report basic information about arriving disaster victims.&nbsp; (Suburban Hospital’s implementation is furthest along.)<br>
		<br>
		<br>
	";
}
*/

