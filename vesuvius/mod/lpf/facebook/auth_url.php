
<?php
//add php-sdk
require 'src/facebook.php';

//Create facebook instance.
$facebook = new Facebook(array(
  'appId'  => '272810739444941',
  'secret' => 'f589181f7e8f51c5492f6c07f59873f8',
  'cookie' => true,
));

$loginUrl = $facebook->getLoginUrl(array(
    'canvas' => 1,
    'fbconnect' => 0,
    'scope' => 'offline_access,publish_stream'
));
if ($loginUrl)
print_r($loginUrl);
?>


