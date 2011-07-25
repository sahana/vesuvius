<?php
/**
 * @name         Hospital Administration
 * @version      0.1
 * @package      ha
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


/**
 * Default Admin function
 *
 * @access public
 * @return void
 */
function shn_ha_default() {
	shn_ha_log();
}




/**
 * Show all hospital registrations.
 *
 * @access public
 * @return void
 */
function shn_ha_log() {
	global $global;
	echo "<div id=\"home\">";
	echo "
		<h2><b><i>>> "._t('HOSPITAL_VIEW|View/Edit Registered Hospitals')."</i></b></h2>
		<h2><a href=\"index.php?mod=ha&act=add\"><b>"._t('HOSPITAL_VIEW|Add an additional Hospital to the sytem')."</b></a></h2>
	";
	$query  = "
		SELECT *
		FROM hospital
		ORDER BY creation_time DESC;
	";
	$result = $global['db']->Execute($query);
	$count = 0;
	echo "<div class=\"form-container\"><form><fieldset>";
	echo "<legend>"._t('HOSPITAL_VIEW|All Hospitals')."</legend>";
	echo "<table id=\"regLog\"><tr>
		<td class=\"evener\"><b>"._t('HOSPITAL_VIEW|PL Hospital ID')."</b></td>
		<td class=\"evener\"><b>"._t('HOSPITAL_VIEW|Name')."</b></td>
		<td class=\"evener\"><b>"._t('HOSPITAL_VIEW|Shortname')."</b></td>
		<td class=\"evener\"><b>"._t('HOSPITAL_VIEW|Added')."</b></td>
		<td class=\"evener\"><b>"._t('HOSPITAL_VIEW|Edit This Hospital')."</b></td>
	</tr>";
	while($row = $result->FetchRow()) {
		if(($count%2)==0) {
			$odd = "class=\"odder\"";
		} else {
			$odd = "class=\"evener\"";
		}
		echo "  <tr>
			<td ".$odd.">".$row['hospital_uuid']."</td><td ".$odd.">".$row['name']."</td><td ".$odd.">".$row['short_name']."</td>
			<td ".$odd.">".$row['creation_time']."</td><td ".$odd."><a href=\"index.php?mod=ha&act=edit&uuid=".$row['hospital_uuid']."\">Edit</a>
			</tr>";
		$count++;
	}
	if($count==0) {
		echo "<tr><td colspan=6 class=\"odder\">No Hospitals added so far..</td></tr>";
	}
	echo "</table>";
	echo "</fieldset></form></div>";
	echo "</div>";
}



/**
 * Edit a hospital.
 *
 * @access public
 * @return void
 */
function shn_ha_edit($uu = null) {
	global $global;
	if($uu != null) {
		$uuid = $uu;
	} else {
		$uuid = $_GET['uuid'];
	}
	echo "<div id=\"home\">";
	echo "<h2>"._t('HOSPITAL_EDIT|Edit a Hospital')."</h2>";
	$query  = "SELECT * FROM hospital WHERE hospital_uuid = '".mysql_real_escape_string($uuid)."' LIMIT 1;";
	$result = $global['db']->Execute($query);
	$row = $result->FetchRow();
	echo "
		<script>
			function confirmDelete() {
				var answer = confirm('Are you sure you want to delete this hospital? This action cannot be undone.');
				if(answer) {
					window.location = 'index.php?mod=ha&act=delete&uuid=".$uuid."';
				}
			}
			function saveHospital() {
				var f = document.getElementById('editHospital');
				f.submit();
			}
		</script>
	";
	echo "<p><b>"._t('HOSPITAL_EDIT|Key:</b><b class=\"red\"> * </b> - Fields tagged with a red asterisk(<span class=\"red\"> * </span>) are mandatory and must be filled in.')."</p>";
	echo "<div class=\"form-container\"><form method=\"post\" id=\"editHospital\" name=\"editHospital\" action=\"index.php?mod=ha&act=save&uuid=".$uuid."\"><fieldset>";
	echo "<legend>"._t('HOSPITAL_EDIT|Edit')."</legend>";
	echo "<table id=\"regLog\">
		<tr><td style=\"width: 250px;\"  class=\"odder\"><b>UUID</b></td><td class=\"odder\">".$row['hospital_uuid']."</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Name')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"name\" name=\"name\" value=\"".$row['name']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Short Name')."</b></td><td class=\"odder\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"short_name\" name=\"short_name\" value=\"".$row['short_name']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Street Address 1')."</b></td><td class=\"evener\">
			<input size=30 maxlength=120 class=\"hospitalInput\" id=\"street1\" name=\"street1\" value=\"".$row['street1']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Street Address 2')."</b></td><td class=\"odder\">
			<input size=30 maxlength=120 class=\"hospitalInput\" id=\"street2\" name=\"street2\" value=\"".$row['street2']."\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|City')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"city\" name=\"city\" value=\"".$row['city']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|County')."</b></td><td class=\"odder\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"county\" name=\"county\" value=\"".$row['county']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Region (State)')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"region\" name=\"region\" value=\"".$row['region']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Postal Code')."</b></td><td class=\"odder\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"postal_code\" name=\"postal_code\" value=\"".$row['postal_code']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Country')."</b></td><td class=\"evener\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"country\" name=\"country\" value=\"".$row['country']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Latitude')."</b></td><td class=\"odder\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"latitude\" name=\"latitude\" value=\"".$row['latitude']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Longitude')."</b></td><td class=\"evener\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"longitude\" name=\"longitude\" value=\"".$row['longitude']."\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Phone')."</b></td><td class=\"odder\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"phone\" name=\"phone\" value=\"".$row['phone']."\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|Fax')."</b></td><td class=\"evener\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"fax\" name=\"fax\" value=\"".$row['fax']."\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Email')."</b></td><td class=\"odder\">
			<input size=30 maxlength=64 class=\"hospitalInput\" id=\"email\" name=\"email\" value=\"".$row['email']."\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_EDIT|NPI')."</b></td><td class=\"evener\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"npi\" name=\"npi\" value=\"".$row['npi']."\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_EDIT|Patient ID Prefix')."</b></td><td class=\"odder\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"patient_id_prefix\" name=\"patient_id_prefix\" value=\"".$row['patient_id_prefix']."\"><span class=\"req\">*</span>
		</td></tr>

		<tr>
			<td style=\"width: 250px;\" class=\"evener\">&nbsp;</td>
			<td class=\"evener\"><input class=\"styleTehButton\" id=\"saveButton\" type=\"button\" value=\"Save\" onclick=\"saveHospital();\"><br><br><br><br></td>
		</tr>

		<tr>
			<td colspan=2 class=\"odder\"><br>
				"._t('HOSPITAL_EDIT|<b>Note</b>: Deleting a Hospital is a permanent action and cannot be undone. In addition to this, deleting a Hospital will also remove the association of any persons there
				once was to this organization.<br><br>')."
				<input class=\"styleTehButton\" id=\"deleteButton\" type=\"button\" value=\"Delete\" onclick=\"confirmDelete();\"><br><br>
			</td>
		</tr>
	</table>
	</fieldset></form></div>
	</div>
	<br><br>";
}



/**
 * Deletes a Registration
 */
function shn_ha_delete() {
	global $global;
	$uuid = $_GET['uuid'];
	$q1 = "DELETE FROM hospital WHERE hospital_uuid = '".mysql_real_escape_string($uuid)."';";
	$r1 = $global['db']->Execute($q1);
	add_confirmation("Hospital deleted.");
	shn_ha_log();
}



/**
 * Save any changes to the hospital
 */
function shn_ha_save() {

	//echo "<pre>".print_r($_POST, true)."</pre>";

	$error = false;
	if(trim($_POST['name']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>name</b> may not be empty."));
	}
	if(trim($_POST['short_name']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>short name</b> may not be empty."));
	}
	if(trim($_POST['street1']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>street address 1</b> may not be empty."));
	}
	if(trim($_POST['city']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>city</b> may not be empty."));
	}
	if(trim($_POST['county']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>county</b> may not be empty."));
	}
	if(trim($_POST['region']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>region</b> may not be empty."));
	}
	if(trim($_POST['postal_code']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>postal code</b> may not be empty."));
	}
	if(trim($_POST['country']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>country</b> may not be empty."));
	}
	if(trim($_POST['latitude']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>latitude</b> may not be empty."));
	}
	if(trim($_POST['longitude']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>longitude</b> may not be empty."));
	}
	if(trim($_POST['patient_id_prefix']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>patient id prefix</b> may not be empty."));
	}

	if(!$error) {
		global $global;
		$query = "
			UPDATE hospital
			SET
				name              = '".mysql_real_escape_string($_POST['name'])."',
				short_name        = '".mysql_real_escape_string($_POST['short_name'])."',
				street1           = '".mysql_real_escape_string($_POST['street1'])."',
				street2           = '".mysql_real_escape_string($_POST['street2'])."',
				city              = '".mysql_real_escape_string($_POST['city'])."',
				county            = '".mysql_real_escape_string($_POST['county'])."',
				region            = '".mysql_real_escape_string($_POST['region'])."',
				postal_code       = '".mysql_real_escape_string($_POST['postal_code'])."',
				country           = '".mysql_real_escape_string($_POST['country'])."',
				latitude          = '".mysql_real_escape_string($_POST['latitude'])."',
				longitude         = '".mysql_real_escape_string($_POST['longitude'])."',
				phone             = '".mysql_real_escape_string($_POST['phone'])."',
				fax               = '".mysql_real_escape_string($_POST['fax'])."',
				email             = '".mysql_real_escape_string($_POST['email'])."',
				npi               = '".mysql_real_escape_string($_POST['npi'])."',
				patient_id_prefix = '".mysql_real_escape_string($_POST['patient_id_prefix'])."'

			WHERE hospital_uuid = '".$_GET['uuid']."';";

		$result = $global['db']->Execute($query);
		add_confirmation(_t("HOSPITAL_MESSAGE|Saved hospital information."));
		shn_ha_log();
	} else {
		shn_ha_edit($_POST['uuid']);
	}
}





/**
 * Add a new Hospital.
 *
 * @access public
 * @return void
 */
function shn_ha_add() {
	global $global;

	echo "<div id=\"home\">";
	echo "
		<h2><a href=\"index.php?mod=ha&act=log\"><b>"._t('HOSPITAL_VIEW|View/Edit Registered Hospitals')."</b></a></h2>
		<h2><b><i>>>"._t('HOSPITAL_VIEW|Add an additional Hospital to the sytem')."</i></b></h2>
	";
	echo "
		<script>
			function saveNewHospital() {
				var f = document.getElementById('editHospital');
				f.submit();
			}
		</script>
	";
	echo "<p><b>"._t('HOSPITAL_ADD|Key:</b><b class=\"red\"> * </b> - Fields tagged with a red asterisk(<span class=\"red\"> * </span>) are mandatory and must be filled in.')."</p>";
	echo "<div class=\"form-container\"><form method=\"post\" id=\"editHospital\" name=\"editHospital\" action=\"index.php?mod=ha&act=saveNew\"><fieldset>";
	echo "<legend>New</legend>";
	echo "<table id=\"regLog\">

		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Name')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"name\" name=\"name\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Short Name')."</b></td><td class=\"odder\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"short_name\" name=\"short_name\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Street Address 1')."</b></td><td class=\"evener\">
			<input size=30 maxlength=120 class=\"hospitalInput\" id=\"street1\" name=\"street1\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Street Address 2')."</b></td><td class=\"odder\">
			<input size=30 maxlength=120 class=\"hospitalInput\" id=\"street2\" name=\"street2\" value=\"\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|City')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"city\" name=\"city\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|County')."</b></td><td class=\"odder\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"county\" name=\"county\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Region (State)')."</b></td><td class=\"evener\">
			<input size=30 maxlength=60 class=\"hospitalInput\" id=\"region\" name=\"region\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Postal Code')."</b></td><td class=\"odder\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"postal_code\" name=\"postal_code\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Country')."</b></td><td class=\"evener\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"country\" name=\"country\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Latitude')."</b></td><td class=\"odder\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"latitude\" name=\"latitude\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Longitude')."</b></td><td class=\"evener\">
			<input size=30 maxlength=30 class=\"hospitalInput\" id=\"longitude\" name=\"longitude\" value=\"\"><span class=\"req\">*</span>
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Phone')."</b></td><td class=\"odder\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"phone\" name=\"phone\" value=\"\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|Fax')."</b></td><td class=\"evener\">
			<input size=30 maxlength=16 class=\"hospitalInput\" id=\"fax\" name=\"fax\" value=\"\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Email')."</b></td><td class=\"odder\">
			<input size=30 maxlength=64 class=\"hospitalInput\" id=\"email\" name=\"email\" value=\"\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"evener\"><b>"._t('HOSPITAL_ADD|NPI')."</b></td><td class=\"evener\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"npi\" name=\"npi\" value=\"\">
		</td></tr>


		<tr><td style=\"width: 250px;\" class=\"odder\"><b>"._t('HOSPITAL_ADD|Patient ID Prefix')."</b></td><td class=\"odder\">
			<input size=30 maxlength=32 class=\"hospitalInput\" id=\"patient_id_prefix\" name=\"patient_id_prefix\" value=\"\"><span class=\"req\">*</span>
		</td></tr>

		<tr>
			<td style=\"width: 250px;\" class=\"evener\">&nbsp;</td>
			<td class=\"evener\"><br><input class=\"styleTehButton\" id=\"saveButton\" type=\"button\" value=\"Save\" onclick=\"saveNewHospital();\"><br><br><br><br></td>
		</tr>
	</table>";
	echo "</fieldset></form></div>";
	echo "</div><br><br>";
}



/**
 * Save a new hospital
 */
function shn_ha_saveNew() {

	//echo "<pre>".print_r($_POST, true)."</pre>";

	$error = false;
	if(trim($_POST['name']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>name</b> may not be empty."));
	}
	if(trim($_POST['short_name']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>short name</b> may not be empty."));
	}
	if(trim($_POST['street1']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>street address 1</b> may not be empty."));
	}
	if(trim($_POST['city']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>city</b> may not be empty."));
	}
	if(trim($_POST['county']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>county</b> may not be empty."));
	}
	if(trim($_POST['region']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>region</b> may not be empty."));
	}
	if(trim($_POST['postal_code']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>postal code</b> may not be empty."));
	}
	if(trim($_POST['country']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>country</b> may not be empty."));
	}
	if(trim($_POST['latitude']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>latitude</b> may not be empty."));
	}
	if(trim($_POST['longitude']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>longitude</b> may not be empty."));
	}
	if(trim($_POST['patient_id_prefix']) == "") {
		$error = true;
		add_error(_t("HOSPITAL_ERROR|Hospital <b>patient id prefix</b> may not be empty."));
	}

	if(!$error) {
		global $global;
		$query = "
			INSERT INTO hospital(
				`name`,
				`short_name`,
				`street1`,
				`street2`,
				`city`,
				`county`,
				`region`,
				`postal_code`,
				`country`,
				`latitude`,
				`longitude`,
				`phone`,
				`fax`,
				`email`,
				`npi`,
				`patient_id_prefix`
			) VALUES (
				'".mysql_real_escape_string($_POST['name'])."',
				'".mysql_real_escape_string($_POST['short_name'])."',
				'".mysql_real_escape_string($_POST['street1'])."',
				'".mysql_real_escape_string($_POST['street2'])."',
				'".mysql_real_escape_string($_POST['city'])."',
				'".mysql_real_escape_string($_POST['county'])."',
				'".mysql_real_escape_string($_POST['region'])."',
				'".mysql_real_escape_string($_POST['postal_code'])."',
				'".mysql_real_escape_string($_POST['country'])."',
				'".mysql_real_escape_string($_POST['latitude'])."',
				'".mysql_real_escape_string($_POST['longitude'])."',
				'".mysql_real_escape_string($_POST['phone'])."',
				'".mysql_real_escape_string($_POST['fax'])."',
				'".mysql_real_escape_string($_POST['email'])."',
				'".mysql_real_escape_string($_POST['npi'])."',
				'".mysql_real_escape_string($_POST['patient_id_prefix'])."'
			)";
		$result = $global['db']->Execute($query);
		add_confirmation(_t("HOSPITAL_MESSAGE|Saved hospital information."));
		shn_ha_log();
	} else {
		shn_ha_add();
	}
}

