<?php

// Configuration settings for My sit
global $sit;
// Email Settings
$sit['from_name'] = "ravindra desilva"; // from email name
$sit['from_email'] = "ravindra@opensource.lk"; // from email address
//$sit['reply_tol']('kushi223344@yahoo.com', 'sri')
// Just in case we need to relay to a different server, 
// provide an option to use external mail server.

$sit['smtp_mode'] = "enabled"; 
$sit['smtp_host'] = "smtp.opensource.lk";
$sit['smtp_port'] = 25;
$sit['smtp_username'] ="";
$sit['smtp_password'] ="";
?>
