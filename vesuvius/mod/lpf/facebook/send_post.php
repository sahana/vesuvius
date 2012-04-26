<?php
//add php-sdk
require 'src/facebook.php';

// 139763866122513
// dce36010dc024564367b9f2e526ccd89
// NLM.LPF

//Create facebook instance.
/*
$facebook = new Facebook(array(
  'appId'  => '272810739444941',
  'secret' => 'f589181f7e8f51c5492f6c07f59873f8',
  'cookie' => true,
));
*/
$facebook = new Facebook(array(
  'appId'  => '139763866122513',
  'secret' => 'dce36010dc024564367b9f2e526ccd89',
  'cookie' => true,
));

//$user = $facebook->getUser();

$token = $facebook->getAccessToken();

$post =  array(
    'access_token' => $token,
    'message' => 'This message is posted with access token - ' . date('Y-m-d H:i:s')
);

//and make the request
// save $res = $facebook->api('/myjc11/feed', 'POST', $post);
$res = $facebook->api('/NLM.LPF/feed', 'POST', $post);
// NLM.LPF
print_r($res);
//For example this can also be used to gain user data
//and this time only token is needed
//$token =  array(
//    'access_token' => $token 
//);
//$userdata = $facebook->api('/me', 'GET', $token);
//print_r($userdata);
?>


