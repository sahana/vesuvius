<?php

if ($_POST['username'] || $_POST['password']) {
  $username = $_POST['username'];
  $password = md5($_POST['password']);
  $time = time();
  $referring_page = $_POST['referring_page'];

  $conn = pg_connect("dbname=skillsregister");

  include("CachedQueries.php");

  $success = pg_query($conn, "EXECUTE GetPersonalDetails ('$username','$password')");
  if (!$success) {
    echo pg_last_error();
  }
  else if (pg_num_rows($success) == 0) {
    $error = "<font color=\"#FF0000\">Incorrect credentials.  Please try again.</font>";
  }
  else {
    $login_error = 0;
    setcookie ("username", $username, $time+3200);
    setcookie ("password", $password, $time+3200);

    if ($referring_page == "VolunteerLogin") {
      $success = pg_query($conn, "select GetVolunteerId('$username', '$password')");

      if (!$success) {
	echo pg_last_error();
      }
      if (pg_num_rows($success) > 0) {
        $row = pg_fetch_row($success);
        setcookie ("volunteer_id", $row[0], $time+3200);
      }
      header ("Location: PersonalPage.php");
    }
    else if ($referring_page == "OrganisationLogin") {
      $success = pg_query($conn, "select GetPersonId('$username', '$password')");

      if (!$success) {
        echo pg_last_error();
      }
      if (pg_num_rows($success) > 0) {
        $row = pg_fetch_row($success);
        setcookie ("person_id", $row[0], $time+3200);
      }
      header ("Location: OrgPersonalPage.php");
    }

  }

  $close = pg_close($conn);
}

?>
