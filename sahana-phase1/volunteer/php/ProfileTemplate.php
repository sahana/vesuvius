<?php

/* GET PROFILES */
function populate_profile_list () {
  if ($_COOKIE['volunteer_id']) {
    $volunteer_id = $_COOKIE['volunteer_id'];
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE GetProfilesForVolunteerId($volunteer_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      while($row = pg_fetch_row($success)) {
        $prof_id = $row[0];

        $tenure_success = pg_query($conn, "EXECUTE GetTenureAndBasisForProfileId($prof_id)");

        if (!$tenure_success) {
	  echo pg_last_error();
        }
 
	$opp_row = pg_fetch_row($tenure_success);

        $profile_basis = $opp_row[0];
        $profile_tenure = $opp_row[1];

        $profile_hidden_text = "<input type=\"hidden\" name=\"ProfileId\" value=\"$prof_id\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"Matching\">";

        include("ProfileTemplate.html");
      }
    }
    $close = pg_close($conn);
  }
}

?>