<?php

$conn = pg_connect("dbname=skillsregister");

$success = pg_query($conn, "SELECT c.CodeDescription,
                                   p.FirstName,
                                   p.Surname
                              FROM Person p
                             INNER JOIN Code c
                                ON p.Title = c.CodeId");
if (!$success) {
  echo pg_last_error();
}
else if pg_num_rows($success) == 0 {
  $error = "Incorrect credentials.  Please try again."
}

$row = pg_fetch_row($VolMatch);

$title = $row[0];
$firstname = $row[1];
$surname = $row[2];

$close = pg_close($conn);  
?>
