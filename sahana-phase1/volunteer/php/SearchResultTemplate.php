<?php
$submit_page = "SearchResults.php";
$match_id = $_COOKIE['match_id'];

/* GET VOLUNTEER SEARCH RESULTS */
function populate_search_results_list ($match_id) {
  if (($_COOKIE['referring_page'] == "PersonalPage") ||
      ($_COOKIE['referring_page'] == "Matching")) {
    do_for_volunteer($match_id);
  }
  else if (($_COOKIE['referring_page'] == "OrgPersonalPage") ||
           ($_COOKIE['referring_page'] == "OrgMatching")) {
    do_for_organisation($match_id);
  }
}

function do_for_volunteer($match_id) {
  if ($match_id) {
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE VolunteerGetOpportunitiesForMatchId($match_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      $result_id = 1;
      while($row = pg_fetch_row($success)) {
        $opp_id = $row[0];
        $skill_success = pg_query($conn, "EXECUTE GetSkillsForOpportunityId($opp_id)");

        if (!$skill_success) {
          echo pg_last_error();
        }

	$matched_job_skills = "";
        while($opp_row = pg_fetch_row($skill_success)) {
          $this_skill = $opp_row[0];
          $matched_job_skills = $matched_job_skills . "<li>$this_skill</li>";
        }
        $tenure_success = pg_query($conn, "EXECUTE GetTenureAndBasisForOpportunityId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $matched_job_basis = $opp_row[0];
        $matched_job_tenure = $opp_row[1];

	$contact_method_success = pg_query($conn, "EXECUTE GetContactMethodForOpportunityId($opp_id)");

	if (!$contact_method_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($contact_method_success);
	$matched_job_contact_method = $opp_row[0];
 
	$match_success = pg_query($conn, "EXECUTE VolGetMatchIdentifierForMatchId($match_id, $opp_id)");

	if (!$match_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($match_success);
	$match_identifier = $opp_row[0];

        $contact_string = "<input type=\"hidden\" name=\"MatchIdentifier\" value=\"$match_identifier\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"PersonalPage\">";

	$has_matched = pg_query($conn, "EXECUTE VolunteerCheckIfOrgContacted($match_identifier)");
        if (pg_num_rows($has_matched) > 0) {
	  $contact_string = $opportunity_contact_string . 
			    "<input type=\"submit\" name=\"submit\" value=\"contact\" disabled=\"disabled\">";
	  $contact_error = "<font color=\"#FF0000\">You have contacted this organisation about this Opportunity</font>";
	}
	else {
	  $contact_string = $contact_string . 
			    "<input type=\"submit\" name=\"submit\" value=\"contact\">";
	  $contact_error = "";
	}
        include("SearchResultTemplate.html");
	$result_id++;
      }
    }
    $close = pg_close($conn);
  }
}

function do_for_organisation($match_id) {
  if ($match_id) {
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE OrganisationGetVolunteersForMatchId($match_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      while($row = pg_fetch_row($success)) {
        $vol_id = $row[0];
        $skill_success = pg_query($conn, "EXECUTE GetSkillsForVolunteerId($vol_id)");

        if (!$skill_success) {
          echo pg_last_error();
        }

	$matched_job_skills = "";
        while($vol_row = pg_fetch_row($skill_success)) {
          $this_skill = $vol_row[0];
          $matched_job_skills = $matched_job_skills . "<li>$this_skill</li>";
        }
        $tenure_success = pg_query($conn, "EXECUTE GetTenuresForVolunteerId($vol_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	for ($i=0, $matched_job_tenure=""; $i < pg_num_rows($tenure_success); $i++) {
	  $opp_row = pg_fetch_row($tenure_success);
          $matched_job_tenure = $matched_job_tenure . $opp_row[0];
	  if ($i+2 < pg_num_rows($tenure_success)) $matched_job_tenure = $matched_job_tenure . ", ";
          else if ($i+1 < pg_num_rows($tenure_success)) $matched_job_tenure = $matched_job_tenure . " OR ";
        }

        $tenure_success = pg_query($conn, "EXECUTE GetBasisForVolunteerId($vol_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	for ($i=0, $matched_job_basis=""; $i < pg_num_rows($tenure_success); $i++) {
	  $opp_row = pg_fetch_row($tenure_success);
          $matched_job_basis = $matched_job_basis . $opp_row[0];
	  if ($i+2 < pg_num_rows($tenure_success)) $matched_job_basis = $matched_job_basis . ", ";
          else if ($i+1 < pg_num_rows($tenure_success)) $matched_job_basis = $matched_job_basis . " OR ";
        }

	$contact_method_success = pg_query($conn, "EXECUTE GetContactMethodForVolunteerId($vol_id)");

	if (!$contact_method_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($contact_method_success);
	$matched_job_contact_method = $opp_row[0];
 
	$match_success = pg_query($conn, "EXECUTE OrgGetMatchIdentifierForMatchId($match_id, $vol_id)");

	if (!$match_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($match_success);
	$match_identifier = $opp_row[0];

        $contact_string = "<input type=\"hidden\" name=\"MatchIdentifier\" value=\"$match_identifier\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"OrgPersonalPage\">";

	$has_matched = pg_query($conn, "EXECUTE OrgCheckIfVolunteerContacted($match_identifier)");
        if (pg_num_rows($has_matched) > 0) {
	  $contact_string = $contact_string . 
		 	    "<input type=\"submit\" name=\"submit\" value=\"contact\" disabled=\"disabled\">";
	  $contact_error = "<font color=\"#FF0000\">You have contacted this organisation about this Opportunity</font>";
	}
	else {
	  $contact_string = $contact_string . 
			    "<input type=\"submit\" name=\"submit\" value=\"contact\">";
	  $contact_error = "";
	}
        include("SearchResultTemplate.html");
      }
    }
    $close = pg_close($conn);
  }
}

?>