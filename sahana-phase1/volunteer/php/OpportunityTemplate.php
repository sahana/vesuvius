<?php

/* GET OPPORTUNITIES */
function populate_opportunity_list () {
  if ($_COOKIE['person_id']) {
    $person_id = $_COOKIE['person_id'];
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE GetOpportunitiesForPersonId($person_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      while($row = pg_fetch_row($success)) {
        $opp_id = $row[0];
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
 
        $opportunity_hidden_text = "<input type=\"hidden\" name=\"OpportunityId\" value=\"$opp_id\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"OrgMatching\">";

        include("OpportunityTemplate.html");
      }
    }
    $close = pg_close($conn);
  }
}

?>