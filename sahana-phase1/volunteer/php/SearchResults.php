<?php
$referring_page = $_POST['referring_page'];
$submit_page = 'SearchResults.php';
include("Vars.php");
if (substr($referring_page, 0, 3) == 'Org') {
  $login_page = 'OrganisationLogin.php';
  include("OrganisationSecurity.php");
}
else {
  $login_page = 'VolunteerLogin.php';
  include("VolunteerSecurity.php");
}
include("SearchResultTemplate.php");
include("SearchResults.html");
?>