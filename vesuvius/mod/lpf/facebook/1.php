<?php
// this url will redirect to 2.php where we will save the permanent session key
$url = http://www.facebook.com/login.php?api_key=&connect_display=popup&v=1.0&next=2.php&cancel_url=http://www.facebook.com/connect/login_failure.html&fbconnect=true&return_session=true&session_key_only=true&req_perms=read_stream,publish_stream,offline_access;
header(location: $url);
?>
