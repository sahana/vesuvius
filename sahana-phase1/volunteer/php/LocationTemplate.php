<?php

/* GET PROFILES */
function populate_location_list () {
  if ($_COOKIE['volunteer_id']) {
    $volunteer_id = $_COOKIE['volunteer_id'];
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE GetLocationsForVolunteerId($volunteer_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      while($row = pg_fetch_row($success)) {
        $volunteer_location_name = $row[0];
	$volunteer_location_id = $row[1];

        $location_hidden_text = "<input type=\"hidden\" name=\"LocationId\" value=\"$volunteer_location_id\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"Locations\">";

        include("LocationTemplate.html");
      }
    }
    $close = pg_close($conn);
  }
}

?>