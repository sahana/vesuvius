<?php
/**
 * @name         Hospital Administration
 * @version      23
 * @package      ha
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1205
 */



global $global;

// create an array as it does not exist previosuly and will make warnings
$global['xajax_functions'] = array();

// publicly register accessible xajax funtions
array_push($global['xajax_functions'],'ha_append_log');
array_push($global['xajax_functions'],'ha_prepend_log');
array_push($global['xajax_functions'],'ha_show_message');
array_push($global['xajax_functions'],'ha_show_hospitals');
array_push($global['xajax_functions'],'ha_perform_edit');
array_push($global['xajax_functions'],'ha_perform_delete');
array_push($global['xajax_functions'],'ha_perform_insert');
array_push($global['xajax_functions'],'ha_perform_save');
array_push($global['xajax_functions'],'ha_perform_help');

// adds a message to the log div @ tail
function ha_append_log($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ head
function ha_prepend_log($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addPrepend('rezLog','innerHTML',$message);
	return $global['xajax_res']->getXML();
}


// shows a status message before another ajax function is executed
function ha_show_message($message = "no message specified?") {

	global $global;
	$global['xajax_res']->addAssign('rezMain','innerHTML','<div class="loadingMessage"><center><blink>'.$message.'</blink></center></div>');
	return $global['xajax_res']->getXML();
}


// reloads the mainArea div with information of what pages we have
function ha_show_hospitals($internal = FALSE) {

	global $conf;
	global $global;
	$htmlLog = "";
	$htmlMain = "";
	$total = 0;
	$char = "<span style=\"text-shadow: 1px 1px 1px #000;\">▶</span>";

	$htmlMain .= "
		<table class=\"emTable\">
			<tr>
				<td style=\"font-size: 120%; padding-left: 8px;\" ><b>Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Edit</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>Short Name</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>UUID</b></td>
				<td style=\"font-size: 120%; padding-left: 8px;text-align: center;\" ><b>NPI</b></td>
			</tr>
	";

	// get list of hospitals
	$q = "
		SELECT *
		FROM hospital
		ORDER BY hospital_uuid ASC;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show hospitals"); }

	// find out how many hospitals we have and load them into an array
	$hospitals = array();
	$hcount = 0;
	while($row = $result->FetchRow() ){
		$hospitals[$hcount] = $row;
		$hcount++;
	}
	$total = $hcount;

	$i = 1; // we start with the 2nd row of teh table (header?) :)
	$eo = 0; // 2nd row is odd ~ of course u knew that computers start counting at 0 :P
	while($i <= $hcount) {
		$row           = $hospitals[$i-1];
		$type          = "<b><span style=\"color: blue;\">".$char."</span> &nbsp; </b>";
		$uuid          = $row['hospital_uuid'];
		$name          = "<b>".$row['name']."</b>";
		$shortname     = $row['short_name'];
		$npi           = $row['npi'];

		// find class to color the row...
		if(($eo % 2) == 0) {
			$evenOddClass = "mainRowEven";
		} else {
			$evenOddClass = "mainRowOdd";
		}

		$htmlMain .= "
			<tr>
				<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">".$type."<a href=\"#\" onclick=\"javascript: ha_append_log('Editing Hospital <b>#".$uuid." </b>...<br>'); ha_perform_edit(".$uuid.");\">".$name."<a/></td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"javascript: ha_append_log('Editing Hospital <b>#".$uuid." </b>...<br>'); ha_perform_edit(".$uuid.");\" value=\"Edit\"></td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$shortname."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$uuid."</td>
				<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$npi."</td>
			</tr>
		";

		$i++;
		$eo++;
	}
	// end hospitals
	////////////////////////////////////////////////////////////////////////////////////////////////..................................

	if ($hcount == 0) {
		$htmlMain .= "<tr><td colspan=5 class=\"mainRowEven\" style=\"text-align: center;\">No Hospitals have been created yet.</td></tr>";
	}
	$htmlMain .= "</table>";

	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: ha_perform_edit(0);" value="'._t('Hospitals-Add-Button|Add a new Hospital').'">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Help-Message|Opening Help...').'<br>\'); ha_perform_help();" value="'._t('Hospitals-Help-Button|Help').'">
	';

	//---- internally, no ajax, just pass back data
	if ( $internal ) {
		return $htmlMain;
	} else {
		$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

		$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezMain','innerHTML',$htmlMain);

		$htmlLog .= _t("Hospitals-Log-Message|Found <b>").$total._t("Hospitals-Log-Message|</b> Hospital(s).<br>");
		$global['xajax_res']->addAppend('rezLog','innerHTML',$htmlLog);
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
		return $global['xajax_res']->getXML();
	}
}



// shows help
function ha_perform_help() {

	global $global;

	// help content
	$pageMainHtml = "
		"._t('Hospitals-Help-Text|coming soon....')."
	";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Closing Help...').'<br>\'); setTimeout(\'ha_show_hospitals();\', 250);" value="'._t('Hospitals-Help-Button|Close Help').'">
	';

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', $pageMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $pageControlHtml);
	return $global['xajax_res']->getXML();
}




// saves the event attributes to the database
function ha_perform_save($hospital_uuid, $rj) {

	global $global;
	$r = json_decode($rj, true);
	$suggest = false;
	$log = "";

	// figure out if either of the legaleses have changed:
	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = ".$hospital_uuid.";
	";
	$result          = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital save 1"); }
	$row             = $result->FetchRow();
	$oldLegalese     = $row['legalese'];
	$oldLegaleseAnon = $row['legaleseAnon'];
	$updateClause    = "";

	// if they have changed, add to the update clause to give them new timestamps
	if($r['legalese'] != $oldLegalese) {
		$updateClause .= "
			legaleseTimestamp = NOW(),
		";
	}
	if($r['legaleseAnon'] != $oldLegaleseAnon) {
		$updateClause .= "
			legaleseAnonTimestamp = NOW(),
		";
	}

	$hospital_uuid                  = (int)$r['hospital_uuid'];
	$name                           = mysql_real_escape_string($r['name']);
	$short_name                     = mysql_real_escape_string($r['short_name']);
	$street1                        = mysql_real_escape_string($r['street1']);
	$street2                        = mysql_real_escape_string($r['street2']);
	$city                           = mysql_real_escape_string($r['city']);
	$county                         = mysql_real_escape_string($r['county']);
	$region                         = mysql_real_escape_string($r['region']);
	$postal_code                    = mysql_real_escape_string($r['postal_code']);
	$country                        = mysql_real_escape_string($r['country']);
	$latitude                       = (double)$r['latitude'];
	$longitude                      = (double)$r['longitude'];
	$phone                          = mysql_real_escape_string($r['phone']);
	$fax                            = mysql_real_escape_string($r['fax']);
	$email                          = mysql_real_escape_string($r['email']);
	$www                            = mysql_real_escape_string($r['www']);
	$npi                            = mysql_real_escape_string($r['npi']);
	$patient_id_prefix              = mysql_real_escape_string($r['patient_id_prefix']);
	$patient_id_suffix_variable     = (int)$r['patient_id_suffix_variable'];
	$patient_id_suffix_fixed_length = mysql_real_escape_string($r['patient_id_suffix_fixed_length']);
	$icon_url                       = mysql_real_escape_string($r['icon_url']);
	$legalese                       = mysql_real_escape_string($r['legalese']);
	$legaleseAnon                   = mysql_real_escape_string($r['legaleseAnon']);
	$photo_required                 = (int)$r['photo_required'];
	$honor_no_photo_request         = (int)$r['honor_no_photo_request'];
	$photographer_name_required     = (int)$r['photographer_name_required'];


	// save the revision
	$q = "
		UPDATE hospital
		SET
			hospital_uuid                  = '".$hospital_uuid."',
			name                           = '".$name."',
			short_name                     = '".$short_name."',
			street1                        = '".$street1."',
			street2                        = '".$street2."',
			city                           = '".$city."',
			county                         = '".$county."',
			region                         = '".$region."',
			postal_code                    = '".$postal_code."',
			country                        = '".$country."',
			latitude                       = '".$latitude."',
			longitude                      = '".$longitude."',
			phone                          = '".$phone."',
			fax                            = '".$fax."',
			email                          = '".$email."',
			www                            = '".$www."',
			npi                            = '".$npi."',
			patient_id_prefix              = '".$patient_id_prefix."',
			patient_id_suffix_variable     = '".$patient_id_suffix_variable."',
			patient_id_suffix_fixed_length = '".$patient_id_suffix_fixed_length."',
			icon_url                       = '".$icon_url."',
			legalese                       = '".$legalese."',
			legaleseAnon                   = '".$legaleseAnon."',
			".$updateClause."
			photo_required                 = '".$photo_required."',
			honor_no_photo_request         = '".$honor_no_photo_request."',
			photographer_name_required     = '".$photographer_name_required."'
		WHERE hospital_uuid       = '".$hospital_uuid."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital save 2"); }

	$log .= _t("Hospitals-Log-Message|Hospital #<b>").$hospital_uuid."</b> <span style=\"color: green;\">"._t('Hospitals-Log-Message|Saved')."</span>.<b><br>";

	// update log/ui
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Add a new Hospital...').'<br>\'); ha_perform_edit(0);" value="'._t("Hospitals-Add-Button|Add a new Hospital").'">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Opening Help...').'<br>\'); ha_perform_help();" value="'._t("Hospitals-Help-Button|Help").'">
	';
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);
	$global['xajax_res']->addAssign('rezMain', 'innerHTML', ha_show_hospitals(TRUE));
	$global['xajax_res']->addAppend('rezLog', 'innerHTML', $log);
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// delete a page
function ha_perform_delete($hospital_uuid, $confirm) {

	global $global;

	if($confirm == "true") {
		$q = "
			DELETE from hospital
			WHERE hospital_uuid = '".$hospital_uuid."';
		";

		$res = $global['db']->Execute($q);
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', _t('Hospitals-Log-Message|Hospital <b>#').$hospital_uuid.'</b> <span style="color: red;">'._t('Hospitals-Log-Message|removed').'</span>.<br>');
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital delete 1"); }
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', _t('Hospitals-Log-Message|Hospital').' <b>#'.$hospital_uuid.'</b> <span style="color: red;">'._t('Hospitals-Log-Message|removed').'</span>.<br>');
	} else {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', _t("Hospitals-Log-Message|Remove operation aborted.<br>"));
	}

	// update UI
	$pageControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Adding a new Hospital...').'<br>\'); ha_perform_edit(0);" value="'._t('Hospitals-Add-Button|Add a new Hospital').'">
		&nbsp; &nbsp; &nbsp; &nbsp;
		<input class="styleTehButton red" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Opening Help...').'<br>\'); ha_perform_help();" value="'._t('Hospitals-Help-Button|Help').'">
	';
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

	$global['xajax_res']->addAssign('rezMain', 'innerHTML', ha_show_hospitals(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// add a new hospital with default atributes and return uuid
function ha_perform_new() {

	global $global;

	$group = $_SESSION['group_id'];

	// insert a new hospital
	$q = "
		INSERT INTO hospital ()
		VALUES ();
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital new 1"); }

	// find id of newest hospital we just added
	$q = "
		SELECT *
		FROM hospital
		ORDER BY hospital_uuid DESC
		LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital new 2"); }
	$row = $result->FetchRow();
	return $row['hospital_uuid'];
}



// presents a gui to edit a hospital and its corresponding fields
function ha_perform_edit($hospital_uuid) {

	global $global;
	$new = false;

	//$global['xajax_res']->setFlag('debug', true);

	// if hospital_uuid = 0, must add a new hospital and then continue to edit it
	if($hospital_uuid == 0) {
		$hospital_uuid = ha_perform_new();
		$new = true;
	}

	// get incident info
	$q = "
		SELECT *
		FROM hospital
		WHERE hospital_uuid = ".$hospital_uuid.";
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "hospital edit 1"); }
	$row = $result->FetchRow();

	// generate checkboxes
	$check1 = $row['patient_id_suffix_variable'] == "1" ? "CHECKED" : "";
	$check2 = $row['photo_required']             == "1" ? "CHECKED" : "";
	$check3 = $row['honor_no_photo_request']     == "1" ? "CHECKED" : "";
	$check4 = $row['photographer_name_required'] == "1" ? "CHECKED" : "";
	$patient_id_suffix_variable = "<input type=\"checkbox\" id=\"patient_id_suffix_variable\" name=\"patient_id_suffix_variable\" ".$check1." value=\"default\">";
	$photo_required             = "<input type=\"checkbox\" id=\"photo_required\"             name=\"photo_required\"             ".$check2." value=\"default\">";
	$honor_no_photo_request     = "<input type=\"checkbox\" id=\"honor_no_photo_request\"     name=\"honor_no_photo_request\"     ".$check3." value=\"default\">";
	$photographer_name_required = "<input type=\"checkbox\" id=\"photographer_name_required\" name=\"photographer_name_required\" ".$check4." value=\"default\">";


	$editMainHtml = "

<table class=\"emTable\">

	<tr>
		<td class=\"mainRowEven emFirst emLast\" colspan=2 ><b>"._t('Hospitals-EditHospitalForm-Title|Hospital Information')."</b></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\">"._t('Hospitals-EditHospitalForm-TextField|Hospital UUID')."</td>
		<td class=\"mainRowOdd emFirstWhite\"><input id=\"hospital_uuid\" type=\"text\" value=\"".$row['hospital_uuid']."\" size=8 readonly /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\">"._t('Hospitals-EditHospitalForm-TextField|Name')."</td>
		<td class=\"mainRowEven emFirst emLast\"><input id=\"name\" type=\"text\" size=60 maxlength=60 value=\"".$row['name']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\">"._t('Hospitals-EditHospitalForm-TextField|Short Name')."</td>
		<td class=\"mainRowOdd emFirstWhite\"><input id=\"short_name\" type=\"text\" size=30 maxlength=30 value=\"".$row['short_name']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\">"._t('Hospitals-EditHospitalForm-TextField|Street 1')."</td>
		<td class=\"mainRowEven emFirst emLast\"><input id=\"street1\" type=\"text\" size=60 maxlength=120 value=\"".$row['street1']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\">"._t('Hospitals-EditHospitalForm-TextField|Street 2')."</td>
		<td class=\"mainRowOdd emFirstWhite\"><input id=\"street2\" type=\"text\" size=60 maxlength=120 value=\"".$row['street2']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" >"._t('Hospitals-EditHospitalForm-TextField|City')."</td>
		<td class=\"mainRowEven emFirst emLast\" ><input id=\"city\" type=\"text\" size=60 maxlength=60 value=\"".$row['city']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" >"._t('Hospitals-EditHospitalForm-TextField|County')."</td>
		<td class=\"mainRowOdd emFirstWhite\" ><input id=\"county\" type=\"text\" size=60 maxlength=60 value=\"".$row['county']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" >"._t('Hospitals-EditHospitalForm-TextField|State / Region')."</td>
		<td class=\"mainRowEven emFirst emLast\" ><input id=\"region\" type=\"text\" size=60 maxlength=60 value=\"".$row['region']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" >"._t('Hospitals-EditHospitalForm-TextField|Postal Code')."</td>
		<td class=\"mainRowOdd emFirstWhite\" ><input id=\"postal_code\" type=\"text\" size=60 maxlength=60 value=\"".$row['postal_code']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" >"._t('Hospitals-EditHospitalForm-TextField|Country')."</td>
		<td class=\"mainRowEven emFirst emLast\" ><input id=\"country\" type=\"text\" size=60 maxlength=60 value=\"".$row['country']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" >"._t('Hospitals-EditHospitalForm-TextField|Phone')."</td>
		<td class=\"mainRowOdd emFirstWhite\" ><input id=\"phone\" type=\"text\" size=16 maxlength=16 value=\"".$row['phone']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" >"._t('Hospitals-EditHospitalForm-TextField|Fax')."</td>
		<td class=\"mainRowEven emFirst emLast\" ><input id=\"fax\" type=\"text\" size=16 maxlength=16 value=\"".$row['fax']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" >"._t('Hospitals-EditHospitalForm-TextField|Email')."</td>
		<td class=\"mainRowOdd emFirstWhite\" ><input id=\"email\" type=\"text\" size=64 maxlength=64 value=\"".$row['email']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" >"._t('Hospitals-EditHospitalForm-TextField|Web Address')."</td>
		<td class=\"mainRowEven emFirst emLast\" ><input id=\"www\" type=\"text\" size=64 maxlength=256 value=\"".$row['www']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" >"._t('Hospitals-EditHospitalForm-TextField|NPI #')."</td>
		<td class=\"mainRowOdd emFirstWhite\" ><input id=\"npi\" type=\"text\" size=32 maxlength=32 value=\"".$row['npi']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven\" style=\" border-bottom: none;\" colspan=2>
			<label>"._t('Hospitals-EditHospitalForm-TextField|Enter a Street Address: ')."</label>
			<input id=\"address\" type=\"text\" /> &nbsp; -OR- &nbsp; <input type=\"button\" style=\"position: relative; top: -2px;\" class=\"styleTehButton\" onclick=\"detect_load();\" value=\""._t('Hospitals-Info-Form|Detect My Current Location')."\" />
		</td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emFirst emLast\" style=\"border-top: none; border-bottom: none;  padding: 0px;\" colspan=2>
			<div id=\"mapCanvas\" style=\"width: 100%; height: 500px;\"></div>
		</td>
	</tr>
	<tr>
		<td class=\"mainRowEven\" style=\" border-top: none;\" colspan=2>
			<label>latitude: </label>
				<input id=\"latitude\" type=\"text\"/ value=\"".$row['latitude']."\" readonly>
			<label> &nbsp; longitude: </label>
				<input id=\"longitude\" type=\"text\"/ value=\"".$row['longitude']."\" readonly>
		</td>
	</tr>
</table>
<table class=\"emTable\">
	<tr>
		<td class=\"mainRowEven emFirst emLast\" colspan=2 style=\"\"><b>"._t('Hospitals-EditHospitalForm-Text|Hospital Policies')."</b></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">"._t('Hospitals-EditHospitalForm-TextField|PatientID prefix')."</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"patient_id_prefix\" type=\"text\" size=32 maxlength=32 value=\"".$row['patient_id_prefix']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">"._t('Hospitals-EditHospitalForm-TextField|PatientID suffix length is variable')."</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$patient_id_suffix_variable."</td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">"._t('Hospitals-EditHospitalForm-TextField|PatientID suffix fixed length')."</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><input id=\"patient_id_suffix_fixed_length\" type=\"text\" size=32 maxlength=32 value=\"".$row['patient_id_suffix_fixed_length']."\" /></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">"._t('Hospitals-EditHospitalForm-Message|Photo Required')."</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$photo_required."</td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">"._t('Hospitals-EditHospitalForm-Text|Honor No Photo Request')."</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\">".$honor_no_photo_request."</td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">"._t('Hospitals-EditHospitalForm-Message|Photographer Name Required')."</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">".$photographer_name_required."</td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">"._t('Hospitals-EditHospitalForm-TextField|Legalese')."</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><textarea name=\"legalese\" id=\"legalese\" style=\"height: 100px; width: 90%;\">".$row['legalese']."</textarea></td>
	</tr>
	<tr>
		<td class=\"mainRowEven emFirst emLast\" style=\"\">"._t('Hospitals-EditHospitalForm-TextField|Anonymous Legalese')."</td>
		<td class=\"mainRowEven emFirst emLast\" style=\"\"><textarea name=\"legaleseAnon\" id=\"legaleseAnon\" style=\"height: 100px; width: 90%;\">".$row['legaleseAnon']."</textarea></td>
	</tr>
</table>
<table class=\"emTable\">
	<tr>
		<td class=\"mainRowEven emFirst emLast\" colspan=2 style=\"\"><b>"._t('Hospitals-EditHospitalForm-Text|Hospital Icon')."</b></td>
	</tr>
	<tr>
		<td class=\"mainRowOdd emLastWhite\" style=\"\">"._t("Hospitals-EditHospitalForm-TextField|Icon URL")."</td>
		<td class=\"mainRowOdd emFirstWhite\" style=\"\"><textarea name=\"icon_url\" id=\"icon_url\" style=\"height: 30px; width: 90%;\">".$row['icon_url']."</textarea></td>
	</tr>
</table>
	";

	// control HTML
	$editControlHtml = '

		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Canceling Changes...').'<br>\'); setTimeout(\'ha_show_hospitals();\', 250);" value="'._t('Hospitals-Edit-Button|Cancel Edit / Close').'">
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Saving Changes...').'<br>\'); setTimeout(\'ha_perform_save('.$hospital_uuid.', ha_get_data());\', 250);" value="'._t('Hospitals-Edit-Button|Save Changes').'">
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Saving Changes...<br>').'\'); setTimeout(\'ha_perform_save('.$hospital_uuid.', ha_get_data());\', 250);" value="'._t('Hospitals-Edit-Button|Save Changes and Close').'">
		<input class="styleTehButton" type="button" onclick="javascript: ha_append_log(\''._t('Hospitals-Log-Message|Canceling Changes...<br>').'\'); setTimeout(\'ha_show_hospitals();\', 250);" value="'._t('Hospitals-Edit-Button|Cancel Editing and Close').'">
	';

	// if Admin... show delete button
	if($_SESSION['group_id'] == "1") {
		if(isset($hasChildren) && $hasChildren == true) {
			$disabled = "DISABLED style=\"opacity: 0.2;\"";
		} else {
			$disabled = "";
		}
		$editControlHtml .= '
			&nbsp; &nbsp; &nbsp; &nbsp;
			<input class="styleTehButton red" type="button" onclick="javascript: ha_delete('.$hospital_uuid.');" value="'._t('Hospitals-Remove-Button|Remove this Hospital').'" '.$disabled.' >
		';
	}

	$global['xajax_res']->addAssign('rezMain',    'innerHTML', $editMainHtml);
	$global['xajax_res']->addAssign('rezControl', 'innerHTML', $editControlHtml);

	if($new) {
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Event <b>#'.$hospital_uuid.'</b> <span style="color: green;">Created</span>.<br>');
		$global['xajax_res']->addAppend('rezLog', 'innerHTML', 'Editing Hospital <b>#'.$hospital_uuid.' </b>...<br>');
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	}

	$global['xajax_res']->addScript("load_map(".$row['latitude'].", ".$row['longitude'].", '');");

	return $global['xajax_res']->getXML();
}





