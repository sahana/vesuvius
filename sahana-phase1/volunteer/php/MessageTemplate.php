<?php
$submit_page = "Messages.php";

/* GET VOLUNTEER SEARCH RESULTS */
function populate_messages_list () {
  if ($_COOKIE['volunteer_id']) {
    $volunteer_id = $_COOKIE['volunteer_id'];
    do_for_volunteer($volunteer_id);
  }
  else if ($_COOKIE['person_id']) {
    $person_id = $_COOKIE['person_id'];
    do_for_organisation($person_id);
  }
}

function do_for_volunteer($volunteer_id) {
  if ($volunteer_id) {
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE VolunteerGetMessages($volunteer_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      $result_id = 1;
      $message_body = <<<EOM
Our organisation conducted a search based on the following criteria, 
and received your details as a possible match.  Please contact us so 
that we may discuss the possibility of you volunteering with our 
organisation.
EOM;
      while($row = pg_fetch_row($success)) {
        $opp_id = $row[0];
	$match_identifier = $row[1];
        $skill_success = pg_query($conn, "EXECUTE GetSkillsForOpportunityId($opp_id)");

        if (!$skill_success) {
          echo pg_last_error();
        }

        $job_skills = "";
	while($opp_row = pg_fetch_row($skill_success)) {
	  $this_skill = $opp_row[0];
	  $job_skills = $job_skills . "<li>$this_skill</li>";
	}
        $tenure_success = pg_query($conn, "EXECUTE GetTenureAndBasisForOpportunityId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $job_basis = $opp_row[0];
        $job_tenure = $opp_row[1];

	$contact_method_success = pg_query($conn, "EXECUTE GetContactMethodForOpportunityId($opp_id)");

	if (!$contact_method_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($contact_method_success);
	$job_contact_method = $opp_row[0];
 
        $tenure_success = pg_query($conn, "EXECUTE GetPersonalDetailsForOpportunityId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $contact_title = $opp_row[0];
	$contact_surname = $opp_row[2];

        $tenure_success = pg_query($conn, "EXECUTE GetPersonalDetailsForVolunteerId($volunteer_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $title = $opp_row[0];
	$surname = $opp_row[2];

	$contact_string = "<input type=\"hidden\" name=\"MatchIdentifier\" value=\"$match_identifier\">
	    	               <input type=\"hidden\" name=\"referring_page\" value=\"Messages\">";
	$contact_error = "";
        include("MessageTemplate.html");
	$result_id++;
      }
    }
    $close = pg_close($conn);
  }
}

function do_for_organisation($person_id) {
  if ($person_id) {
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE OpportunityGetMessages($person_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      $result_id = 1;
      $message_body = <<<EOM
I conducted a search based on the following criteria, and received your 
organisation's details as a possible match.  Please contact me so 
that I might discuss with you the possibility of volunteering with your 
organisation.
EOM;
      while($row = pg_fetch_row($success)) {
        $opp_id = $row[0];
	$match_identifier = $row[1];
        $skill_success = pg_query($conn, "EXECUTE GetSkillsForVolunteerId($opp_id)");

        if (!$skill_success) {
          echo pg_last_error();
        }

        $job_skills = "";
	while($opp_row = pg_fetch_row($skill_success)) {
	  $this_skill = $opp_row[0];
	  $job_skills = $job_skills . "<li>$this_skill</li>";
	}
        $tenure_success = pg_query($conn, "EXECUTE GetTenuresForVolunteerId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	for ($i=0, $job_tenure=""; $i < pg_num_rows($tenure_success); $i++) {
	  $opp_row = pg_fetch_row($tenure_success);
          $job_tenure = $job_tenure . $opp_row[0];
	  if ($i+2 < pg_num_rows($tenure_success)) $job_tenure = $job_tenure . ", ";
          else if ($i+1 < pg_num_rows($tenure_success)) $job_tenure = $job_tenure . " OR ";
        }

        $tenure_success = pg_query($conn, "EXECUTE GetBasisForVolunteerId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	for ($i=0, $job_basis=""; $i < pg_num_rows($tenure_success); $i++) {
	  $opp_row = pg_fetch_row($tenure_success);
          $job_basis = $job_basis . $opp_row[0];
	  if ($i+2 < pg_num_rows($tenure_success)) $job_basis = $job_basis . ", ";
          else if ($i+1 < pg_num_rows($tenure_success)) $job_basis = $job_basis . " OR ";
        }

	$contact_method_success = pg_query($conn, "EXECUTE GetContactMethodForVolunteerId($opp_id)");

	if (!$contact_method_success) {
	  echo pg_last_error();
	}

	$opp_row = pg_fetch_row($contact_method_success);
	$job_contact_method = $opp_row[0];
 
        $tenure_success = pg_query($conn, "EXECUTE GetPersonalDetailsForVolunteerId($opp_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $contact_title = $opp_row[0];
	$contact_surname = $opp_row[2];

        $tenure_success = pg_query($conn, "EXECUTE GetPersonalDetailsForPersonId($person_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $title = $opp_row[0];
	$surname = $opp_row[2];

	$contact_string = "<input type=\"hidden\" name=\"MatchIdentifier\" value=\"$match_identifier\">
	    	               <input type=\"hidden\" name=\"referring_page\" value=\"OrgMessages\">";
	$contact_error = "";
        include("MessageTemplate.html");
	$result_id++;
      }
    }
    $close = pg_close($conn);
  }
}

?>