<?
/**
 * @name         User Preferences
 * @version      1.0
 * @package      pref
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


function shn_pref_personal() {

echo "<i>Coming Soon: The ability modify personal details within your user profile.</i>";

}





function shn_pref_tracking() {
	global $global;

	echo "<h2>People I'm Tracking</h2>";

	// Personally Reported ///////////////////////////////////////////////////////////////////

	echo "
		<br>
		<div class=\"form-container\"><form><fieldset>
		<legend>People That I Have Reported</legend>
	";

	$q  = "
		SELECT *
		FROM person_to_report u, person_uuid p
		WHERE rep_uuid = '".$_SESSION['user_p_uuid']."'
		AND p.p_uuid = u.p_uuid;
	";
	$r  = $global['db']->Execute($q);

	$count = 0;
	echo "<table id=\"repLog\">";
	while($row = $r->FetchRow()) {
		$count++;
		if($count%2 == 0) {
			$class = "evener";
		} else {
			$class = "odder";
		}
		echo "
			<tr><td class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\">ID: <b>".$row['p_uuid']."</b>&nbsp&nbsp;&nbsp;&nbsp;&nbsp; Name: <b>".$row['full_name']."</b></a>
			</td></tr>";
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=2>No persons reported.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div>";




	// Persons Following ///////////////////////////////////////////////////////////////////////

	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>People That I Am Following</legend>";

	$q  = "
		SELECT *
		FROM person_followers f, person_uuid p
		WHERE follower_p_uuid = '".$_SESSION['user_p_uuid']."'
		AND p.p_uuid = f.p_uuid;
	";
	$r  = $global['db']->Execute($q);

	$count = 0;
	echo "<table id=\"followLog\">";
	while($row = $r->FetchRow()) {
		$count++;
		if($count%2 == 0) {
			$class = "evener";
		} else {
			$class = "odder";
		}
		echo "
			<tr><td class=\"noBorderLeft ".$class."\" >
			<a href=\"index.php?mod=eap&act=edit&uuid=".base64_encode($row['p_uuid'])."\">ID: <b>".$row['p_uuid']."</b>&nbsp&nbsp;&nbsp;&nbsp;&nbsp; Name: <b>".$row['full_name']."</b></a>
			</td></tr>";
	}
	if($count == 0) {
		echo "<tr><td class=\"noBorderLeft\" colspan=2>Not following any persons.</td></tr>";
	}
	echo "</table>";
	echo "</fieldset>";
	echo "</form></div>";


}
