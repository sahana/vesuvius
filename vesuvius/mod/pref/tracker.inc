<?
/**
 * @name         User Preferences
 * @version      1.1
 * @package      pref
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */


function shn_pref_tracking() {
	global $global;

	$showAll = true;

	// persons in the current event //////////////////////////////////////////////////////////
	if($_GET['shortname'] != "") {
		$showAll = false;

		// current event reported
		$q = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
		$r  = $global['db']->Execute($q);
		$count = 0;
		while($row = $r->FetchRow()) {
			if($count == 0) {
				echo "
					<div class=\"form-container\"><form><fieldset>
					<legend>People that I'm following or Reported for the ".$row['name']."</legend>
					<table id=\"repLog\">
					<tr>
					<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
					<td class=\"noBorderLeft evener\" >Full Name</td>
					</tr>
				";

			}
			if($count%2 == 0) {
				$class = "odder";
			} else {
				$class = "evener";
			}
			echo "
				<tr>
				<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
				<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['p_uuid']."</b></a></td>
				<td class=\"noBorderLeft ".$class."\" >
				<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['full_name']."</b></a></td>
				</tr>
			";
			$count++;
		}

		if($count == 0) {
			echo "
				<div class=\"form-container\"><form><fieldset>
				<legend>People that I'm following or Reported for the current event.</legend>
				<table id=\"repLog\">
			";
		}

		// current event following
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
		$r  = $global['db']->Execute($q);
		while($row = $r->FetchRow()) {
			if($count%2 == 0) {
				$class = "odder";
			} else {
				$class = "evener";
			}
			echo "
				<tr>
				<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
				<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['p_uuid']."</b></a></td>
				<td class=\"noBorderLeft ".$class."\" >
				<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['full_name']."</b></a></td>
				</tr>
			";
			$count++;
		}

		if($count == 0) {
			echo "<tr><td class=\"noBorderLeft\" colspan=2>No persons reported.</td></tr>";
		}
		echo "</table>";
		echo "</fieldset>";
		echo "</form></div><br>";
	}



	// Personally Reported ///////////////////////////////////////////////////////////////////
	if($showAll) {
		$other = "";
	} else {
		$other = "Other ";
	}
	echo "
		<div class=\"form-container\"><form><fieldset>
		<legend>".$other."People That I Have Reported</legend>
	";

	if($showAll) {
		$q  = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id;
		";
	} else {
		$q  = "
			SELECT *
			FROM person_to_report u, person_uuid p, incident i
			WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = u.p_uuid
			AND p.incident_id = i.incident_id
			AND i.shortname <> '".mysql_real_escape_string($_GET['shortname'])."';
		";
	}
	$r  = $global['db']->Execute($q);

	$count = 0;
	while($row = $r->FetchRow()) {
		if($count == 0) {
			echo "
				<table id=\"repLog\">
				<tr>
				<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
				<td class=\"noBorderLeft evener\" >Full Name</td>
				<td class=\"noBorderLeft evener\" >Event</td>
				</tr>
			";

		}
		if($count%2 == 0) {
			$class = "odder";
		} else {
			$class = "evener";
		}
		echo "
			<tr>
			<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['p_uuid']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['full_name']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			".$row['name']."</b></td>
			</tr>
		";
		$count++;
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=3>No persons reported.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div><br>";



	// Persons Following ///////////////////////////////////////////////////////////////////////
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>".$other."People That I Am Following</legend>";

	if($showAll) {
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id = i.incident_id;
		";
	} else {
		$q  = "
			SELECT *
			FROM person_followers f, person_uuid p, incident i
			WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
			AND p.p_uuid = f.p_uuid
			AND p.incident_id <> i.incident_id
			AND i.shortname = '".mysql_real_escape_string($_GET['shortname'])."';
		";
	}
	$r  = $global['db']->Execute($q);

	$count = 0;
	echo "<table id=\"followLog\">";
	while($row = $r->FetchRow()) {
		if($count == 0) {
			echo "
				<table id=\"repLog\">
				<tr>
				<td class=\"noBorderLeft evener\" >Origin ID / Origin URL</td>
				<td class=\"noBorderLeft evener\" >Full Name</td>
				<td class=\"noBorderLeft evener\" >Event</td>
				</tr>
			";

		}
		if($count%2 == 0) {
			$class = "odder";
		} else {
			$class = "evener";
		}
		echo "
			<tr>
			<td style=\"width: 250px;\" class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['p_uuid']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\"><b>".$row['full_name']."</b></a></td>
			<td class=\"noBorderLeft ".$class."\" >
			".$row['name']."</b></td>
			</tr>
		";
		$count++;
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=3>Not following any persons.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div>";


}
