<?php 
require_once 'src/facebook.php';
$appid = '272810739444941';
 
// Create FB Object Instance 
$facebook = new Facebook(array( 
    'appId'  => $appid, 
    'secret' => 'f589181f7e8f51c5492f6c07f59873f8', 
    'cookie' => false, 
    )); 
 
//print_r($facebook);

$access_token = $facebook->getAccessToken();
print_r($access_token);
return;
try { 
$attachment = array('message' => 'my first post', 
            'access_token' => $access_token, 
                    'name' => 'Attachment Name', 
                    'caption' => 'Attachment Caption', 
                    'link' => 'http://apps.facebook.com/myjc11/', 
                    'description' => 'Description .....', 
                    'picture' => 'http://www.google.com/logo.jpg', 
                    'actions' => array(array('name' => 'Action Text',  
                                      'link' => 'http://apps.facebook.com/myjc11/')) 
                    ); 
 
$result = $facebook->api('/'.$appid.'/feed/', 'post', $attachment); 
} 
 
//If the post is not published, print error details 
catch (FacebookApiException $e) { 
echo '<pre>'; 
print_r($e); 
echo '</pre>'; 
} 

 
?>
