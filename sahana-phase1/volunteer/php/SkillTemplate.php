<?php

/* GET PROFILES */
function populate_skill_list () {
  if ($_COOKIE['volunteer_id']) {
    $volunteer_id = $_COOKIE['volunteer_id'];
    $conn = pg_connect("dbname=skillsregister");
    include("CachedQueries.php");
    $success = pg_query($conn, "EXECUTE GetSkillsForVolunteerId($volunteer_id)");

    if (!$success) {
      echo pg_last_error();
    }
    if (pg_num_rows($success) == 0) {
      include("Match_Error.html");
    }
    else {
      while($row = pg_fetch_row($success)) {
        $volunteer_skill_name = $row[0];
	$volunteer_skill_id = $row[1];

        $skill_hidden_text = "<input type=\"hidden\" name=\"SkillId\" value=\"$volunteer_skill_id\">
		           <input type=\"hidden\" name=\"referring_page\" value=\"Skills\">";

        include("SkillTemplate.html");
      }
    }
    $close = pg_close($conn);
  }
}

?>