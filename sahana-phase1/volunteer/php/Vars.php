<?php

$username = $_COOKIE[username];
$password = $_COOKIE[password];

$time = time();

if ($_POST['referring_page']) {
  $referring_page = $_POST['referring_page'];
  setcookie ("referring_page", $referring_page, $time+3200);
}
else if ($_COOKIE['referring_page']) {
  $referring_page = $_COOKIE['referring_page'];
}

$conn = pg_connect("dbname=skillsregister");

/* CACHE QUERIES */
include('CachedQueries.php');

/* GET USERS DETAILS */
$success = pg_query($conn, "EXECUTE GetPersonalDetails('$username', '$password')");

if (!$success) {
  echo pg_last_error();
}

$row = pg_fetch_row($success);

$title = $row[0];
$firstname = $row[1];
$surname = $row[2];

/* GET USERS ORGANISATION */
if ($_COOKIE['person_id']) {
  $person_id = $_COOKIE['person_id'];
  $success = pg_query($conn, "EXECUTE GetOrganisationOfContact('$person_id')");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  $org_name = $row[0];
}

/* GET Full time/Part time/Casual CODES */
$success = pg_query($conn, "EXECUTE GetCodesForCodeType('FPCT')");

if (!$success) {
  echo pg_last_error();
}

$fpct_codes = "";
while ($row = pg_fetch_row($success)) {
  $value = $row[0];
  $text = $row[1];
  $fpct_codes = $fpct_codes . "<option value=\"$value\">$text</option>";
}

/* GET Permanent/Temporary CODES */
$success = pg_query($conn, "EXECUTE GetCodesForCodeType('PTFL')");

if (!$success) {
  echo pg_last_error();
}

$ptfl_codes = "";
while ($row = pg_fetch_row($success)) {
  $value = $row[0];
  $text = $row[1];
  $ptfl_codes = $ptfl_codes . "<option value=\"$value\">$text</option>";
}

/* GET Country Codes */
if ($_POST['Country']) {
  $country = $_POST['Country'];
  if (($country == "add") && (strlen($_POST['AddCountry']) > 1)) {
    $country = CountryAdd($_POST['AddCountry']);
  }
}

$success = pg_query($conn, "EXECUTE GetCodesForCodeType('CTRY')");

if (!$success) {
  echo pg_last_error();
}

$country_list = "";
while ($row = pg_fetch_row($success)) {
  $value = $row[0];
  $text = $row[1];
  $country_list = $country_list . "<option value=\"$value\">$text</option>";
}

/* GET State Codes */
if ($_POST['Country']) {
  $country_list = str_replace("<option value=\"$country\">", "<option value=\"$country\" selected>", $country_list);
  if ($_POST['State']) {
    $state = $_POST['State'];
    if (($state == "add") && (strlen($_POST['AddState']) > 1)) {
      $state = StateAdd($country, $_POST['AddState']);
    }
  }

  if ($_POST['Country'] != "add") {
    $success = pg_query($conn, "EXECUTE GetChildCodesForRelationship('CNST', $country)");
    if (!$success) {
      echo pg_last_error();
    }
  }
  if (($_POST['Country'] == "add") && (strlen($_POST['AddCountry']) < 3)) {
    $state_list = "<select name=\"State\" disabled=\"disabled\">";
  }
  else {
    $state_list = "<select name=\"State\">";
  }
  while ($row = pg_fetch_row($success)) {
    $value = $row[0];
    $text = $row[1];
    $state_list = $state_list . "<option value=\"$value\">$text</option>";
  }
}
else {
  $state_list = "<select name=\"State\" disabled=\"disabled\">";
}
$state_list = $state_list . "<option value=\"add\" selected>--- select an option ---</option>";
$state_list = $state_list . "</select>";

/* GET Region Codes */
if (($_POST['State']) && ($_POST['submit'] != "choose country")) {
  $state_list = str_replace(" selected>", ">", $state_list);
  $state_list = str_replace("<option value=\"$state\">", "<option value=\"$state\" selected>", $state_list);
  if ($_POST['Region']) {
    $region = $_POST['Region'];
    if (($region == "add") && (strlen($_POST['AddRegion']) > 1)) {
      $region = RegionAdd($state, $_POST['AddRegion']);
    }
  }
  if ($_POST['State'] != "add") {
    $success = pg_query($conn, "EXECUTE GetChildCodesForRelationship('STRG', $state)");
    if (!$success) {
      echo pg_last_error();
    }
  }

  $region_list = "<select name=\"Region\">";
  while ($row = pg_fetch_row($success)) {
    $value = $row[0];
    $text = $row[1];
    $region_list = $region_list . "<option value=\"$value\">$text</option>";
  }
}
else {
  $region_list = "<select name=\"State\" disabled=\"disabled\">";
}
$region_list = $region_list . "<option value=\"add\" selected>--- select an option ---</option>";
$region_list = $region_list . "</select>";

if ($_POST['Region']) {
  $region_list = str_replace(" selected>", ">", $region_list);
  $region_list = str_replace("<option value=\"$region\">", "<option value=\"$region\" selected>", $region_list);
}

/* GET Skills */
if ($_POST['SkillId']) {
  $skill = $_POST['SkillId'];
  if (($skill == "add") && (strlen($_POST['AddSkill']) > 2)) {
    $skill = SkillAdd($_POST['AddSkill']);
  }
}

$success = pg_query($conn, "EXECUTE GetSkills");

if (!$success) {
  echo pg_last_error();
}

$skills_list = "";
while ($row = pg_fetch_row($success)) {
  $value = $row[0];
  $text = $row[1];
  $skills_list = $skills_list . "<option value=\"$value\">$text</option>";
}

if ($_POST['SkillId']) {
  $skills_list = str_replace("<option value=\"$skill\">", "<option value=\"$skill\" selected>", $skills_list);
}

/* GET Skills not already selected by a volunteer */
if ($_COOKIE['volunteer_id']) {
  $success = pg_query($conn, "EXECUTE VolunteerGetRemainingSkills(${_COOKIE['volunteer_id']})");

  if (!$success) {
    echo pg_last_error();
  }

  $remaining_skill_list = "";
  while ($row = pg_fetch_row($success)) {
    $value = $row[0];
    $text = $row[1];
    $remaining_skill_list = $remaining_skill_list . "<option value=\"$value\">$text</option>";
  }
}

/* SET SEARCH LOCATION */
if ($_POST['LocationId']) {
  $LocationId = $_POST['LocationId'];
}
else if ($_POST['Region'] != 0) {
  $LocationId = $region;
}
else if ($_POST['State'] != 0) {
  $LocationId = $state;
}
else if ($_POST['Country'] != 0) {
  $LocationId = $country;
}
else {
  $LocationId = -1;
}

/* CHECK STATS ON SEARCH PAGE.  SET ERROR */
if (($_POST['submit'] == "search") || ($_POST['submit'] == "match") || ($_POST['submit'] == "Match All")) {
  $submit = $_POST['submit'];
  $search_error = <<<EOT
                      <table border=0 align=center>
                        <tr><td colspan=2><font color="#FF0000">
						The following fields are required in order to conduct a search:
					  </font></td></tr>
EOT;
  if ($LocationId == -1) {
    $search_error = $search_error . "<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>";
    $search_error = $search_error . "<td><font color=\"#FF0000\">Search Location</font></td></tr>";
  }
  if ((!$_POST['SkillId']) || ($_POST['SkillId'] == "add")) {
    $search_error = $search_error . "<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>";
    $search_error = $search_error . "<td><font color=\"#FF0000\">Search Skills</font></td></tr>";
  }
  $search_error = $search_error . "</table>";
  if (($_POST['OpportunityId']) ||
      (($_POST['ProfileId']) && ($_COOKIE['volunteer_id'])) ||
      (($LocationId != -1) && ($_POST['SkillId'] != "add"))
     ) {
    if (($referring_page == "PersonalPage") && ($submit == "search")){
      $match_id = VolunteerSearch($_POST['FPC'], $_POST['PermTemp'], $_POST['SkillId'], $LocationId);
      setcookie ("match_id", $match_id, $time+3200);
    }
    else if (($referring_page == "OrgPersonalPage") && ($submit == "search")) {
      $match_id = OrganisationSearch($_POST['FPC'], $_POST['PermTemp'], $_POST['SkillId'], $LocationId);
      setcookie ("match_id", $match_id, $time+3200);
    }
    else if ((($referring_page == "Matching") && ($submit == "match")) ||
             (($referring_page == "Matching") && ($submit == "Match All"))) {

      $match_id = VolunteerSearchAuto($_COOKIE['volunteer_id'],0);
      setcookie ("match_id", $match_id, $time+3200);
    }
    else if (($referring_page == "OrgMatching") && ($submit == "match")) {
      $match_id = OrganisationSearchAuto($_POST['OpportunityId']);
      setcookie ("match_id", $match_id, $time+3200);
    }
    header ("Location: $submit_page");
  }
}

/* CHECK STATS ON OPPORTUNITY PAGE.  SET ERROR */
if ($referring_page == "OrgMatching") {
  if ($_POST['submit'] == "add opportunity") {
  $add_error = <<<EOT
                        <table border=0 align=center>
                          <tr><td colspan=2><font color="#FF0000">
	  					  The following fields are required in order to add an opportunity:
		  			    </font></td></tr>
EOT;
    if ($LocationId == -1) {
      $add_error = $add_error . "<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>";
      $add_error = $add_error . "<td><font color=\"#FF0000\">Search Location</font></td></tr>";
    }
    if (!$_POST['SkillId']) {
      $add_error = $add_error . "<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>";
      $add_error = $add_error . "<td><font color=\"#FF0000\">Search Skills</font></td></tr>";
    }
    $add_error = $add_error . "</table>";
    if (($LocationId != -1) && ($_POST['SkillId'])) {
      $opportunity_id = OpportunityAdd($_POST['FPC'], $_POST['PermTemp'], $_POST['SkillId'], $LocationId, $_COOKIE['person_id']);
      header ("Location: $submit_page");
    }
  }
  else if ($_POST['submit'] == "delete") {
    $devnull = OpportunityDelete($_POST['OpportunityId']);
  }
}

/* CHECK STATS ON SKILLS PAGE */
if (($_COOKIE['volunteer_id']) &&
    ($referring_page == "Skills") &&
    ($_POST['submit'])) {
  $volunteer_id = $_COOKIE['volunteer_id'];
  $add_skill_id = $_POST['SkillId'];
  if ($_POST['submit'] == "delete") {
    $devnull = VolunteerSkillDelete($volunteer_id, $add_skill_id);
  }
  else if ($_POST['submit'] == "add skill") {
    if (($add_skill_id == 0) && (strlen($_POST['AddSkill']) > 2)) {
      $add_skill_id = SkillAdd($_POST['AddSkill']);
    }
    $added_volunteer_skill = VolunteerSkillAdd($volunteer_id, $add_skill_id);
  }
}

/* CHECK STATS ON LOCATIONS PAGE */
if (($_COOKIE['volunteer_id']) &&
    ($referring_page == "Locations") &&
    ($_POST['submit'])) {
  $volunteer_id = $_COOKIE['volunteer_id'];
  if ($_POST['submit'] == "delete") {
    $devnull = VolunteerAddressDelete($volunteer_id, $LocationId);
  }
  else if ($_POST['submit'] == "add location") {
    $added_volunteer_location = VolunteerLocationAdd($volunteer_id, $LocationId);
  }
}

/* CHECK STATS ON LOCATIONS PAGE */
if (($_COOKIE['volunteer_id']) &&
    ($referring_page == "Matching") &&
    ($_POST['submit'])) {
  $volunteer_id = $_COOKIE['volunteer_id'];
  if ($_POST['submit'] == "delete") {
    $devnull = WorkProfileDelete($_POST['ProfileId']);
  }
  else if ($_POST['submit'] == "add profile") {
    $added_profile_id = WorkProfileAdd($volunteer_id, $_POST['Basis'], $_POST['Tenure']);
  }
}

/* SET SEARCH POST DATA */
$search_post_data = <<<EOD
	<input type="hidden" name="Country" value="${_POST['Country']}">
	<input type="hidden" name="State" value="${_POST['State']}">
	<input type="hidden" name="Region" value="${_POST['Region']}">
	<input type="hidden" name="VolunteerId" value="${_POST['VolunteerId']}">
        <input type="hidden" name="WorkProfileId" value="${_POST['ProfileId']}">
	<input type="hidden" name="OpportunityId" value="${_POST['OpportunityId']}">
	<input type="hidden" name="SkillId" value="${_POST['SkillId']}">
	<input type="hidden" name="LocationId" value="$LocationId">
EOD;

function VolunteerSearch ($fpc_flag, $permtemp_flag, $skill_id, $location_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerSearch($fpc_flag, $permtemp_flag, $skill_id, $location_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function VolunteerSearchAuto ($volunteer_id, $profile_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerSearchAuto($volunteer_id, $profile_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

if ((($referring_page == "PersonalPage") && ($_POST['submit'] == "contact")) ||
    (($referring_page == "Messages") && ($_POST['submit'] == "contact"))) {
  $success = pg_query($conn, "UPDATE Match
                                 SET ContactOrganisation = true
                               WHERE MatchIdentifier = ${_POST['MatchIdentifier']}");

  if (!$success) {
    echo pg_last_error();
  }
}
else if ((($referring_page == "OrgPersonalPage") && ($_POST['submit'] == "contact")) ||
         (($referring_page == "OrgMessages") && ($_POST['submit'] == "contact"))) {
  $success = pg_query($conn, "UPDATE Match
                                 SET ContactVolunteer = true
                               WHERE MatchIdentifier = ${_POST['MatchIdentifier']}");

  if (!$success) {
    echo pg_last_error();
  }
}

if (($referring_page == "Messages") && ($_POST['submit'] == "mark as read")) {
  $success = pg_query($conn, "UPDATE Match
                                 SET VolunteerRead = true
                               WHERE MatchIdentifier = ${_POST['MatchIdentifier']}");

  if (!$success) {
    echo pg_last_error();
  }
}
else if (($referring_page == "OrgMessages") && ($_POST['submit'] == "mark as read")) {
  $success = pg_query($conn, "UPDATE Match
                                 SET OrganisationRead = true
                               WHERE MatchIdentifier = ${_POST['MatchIdentifier']}");

  if (!$success) {
    echo pg_last_error();
  }
}

function OrganisationSearch ($fpc_flag, $permtemp_flag, $skill_id, $location_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select OrganisationSearch($fpc_flag, $permtemp_flag, $skill_id, $location_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function OrganisationSearchAuto ($opportunity_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select OrganisationSearchAuto($opportunity_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function OpportunityAdd ($fpc_flag, $permtemp_flag, $skill_id, $location_id, $person_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select OpportunityAdd($fpc_flag, $permtemp_flag, $skill_id, $location_id, $person_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function OpportunityDelete ($opportunity_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select OpportunityDelete($opportunity_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function VolunteerSkillDelete ($volunteer_id, $skill_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerSkillDelete($volunteer_id, $skill_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function VolunteerAddressDelete ($volunteer_id, $location_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerAddressDelete($volunteer_id, $location_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function WorkProfileDelete ($profile_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select WorkProfileDelete($profile_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function VolunteerSkillAdd ($volunteer_id, $skill_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerSkillAdd($volunteer_id, $skill_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function VolunteerLocationAdd ($volunteer_id, $location_id) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select VolunteerAddressAdd($volunteer_id, $location_id)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function SkillAdd ($skill_name) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select SkillAdd('$skill_name')");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function CountryAdd ($country_name) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select CountryAdd('$country_name')");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function StateAdd ($country_identifier, $state_name) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select StateAdd($country_identifier, '$state_name')");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function RegionAdd ($state_identifier, $region_name) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select RegionAdd($state_identifier, '$region_name')");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function WorkProfileAdd ($volunteer_id, $basis, $tenure) {
  $temp_conn = pg_connect("dbname=skillsregister");
  $success = pg_query($temp_conn, "select WorkProfileAdd($volunteer_id, $basis, $tenure)");

  if (!$success) {
    echo pg_last_error();
  }

  $row = pg_fetch_row($success);
  return $row[0];

  $close = pg_close($temp_conn);
}

function WriteHeader() {
  if (($_COOKIE['volunteer_id']) && (!$_COOKIE['person_id'])) {
    include("VolunteerHeader.html");
  }
  else {
    include("OrganisationHeader.html");
  }
}

function clear_cookies() {
  $time = time();
  setcookie("match_id", $match_id, $time-3200);
  setcookie("person_id", $person_id, $time-3200);
  setcookie("volunteer_id", $volunteer_id, $time-3200);
  setcookie("username", $username, $time-3200);
  setcookie("password", $password, $time-3200);
  setcookie("referring_page", $referring_page, $time-3200);
}

$close = pg_close($conn);

?>
