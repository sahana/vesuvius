<?
  // Remember to copy files from the SDK's src/ directory to a
  // directory in your application on the server, such as php-sdk/
  require_once('src/facebook.php');

  $config = array(
    'appId' => '272810739444941',
    'secret' => 'f589181f7e8f51c5492f6c07f59873f8',
    'cookie' => true
  );

  $facebook = new Facebook($config);
print_r($_REQUEST);
return;
$signed_request = $_REQUEST["signed_request"];
list($encoded_sig, $payload) = explode('.', $signed_request, 2);
$data = json_decode(base64_decode(strtr($payload, '-_', '+/')), true);
print_r($data);
return;

  $access_token = $facebook->getAccessToken();
  print_r($access_token);
  print("\r\n");
  $uid = 'myjc11';

try { 
    $signed_request = $facebook->getSignedRequest(); 
    if ($signed_request)
       print_r($signed_request);
    else
       echo 'empty signed request';

    $page_id = $signed_request['profile_id']; 
    print_r($page_id);
} catch (FacebookApiException $e) { 
    error_log($e); 
} 
return;
  if($access_token) {
$pages = $facebook->api(array( 
'method' => 'fql.query', 
'query' => 'SELECT page_id FROM page_admin' 
)); 
}

// 'query' => 'SELECT page_id FROM page_admin WHERE uid = '.$uid.'' 
  if ($facebook) {
    $user_id = $facebook->getUser();
    print_r($user_id);
  }
?>
<html>
  <head></head>
  <body>

  <?
    if($user_id) {

      // We have a user ID, so probably a logged in user.
      // If not, we'll get an exception, which we handle below.
      try {
        $ret_obj = $facebook->api('/me/feed', 'POST',
                                    array(
                                      'link' => 'www.example.com',
                                      'message' => 'Posting with the PHP SDK!'
                                 ));
        echo '<pre>Post ID: ' . $ret_obj['id'] . '</pre>';

      } catch(FacebookApiException $e) {
        // If the user is logged out, you can have a 
        // user ID even though the access token is invalid.
        // In this case, we'll get an exception, so we'll
        // just ask the user to login again here.
        $login_url = $facebook->getLoginUrl( array(
                       'scope' => 'publish_stream'
                       )); 
        echo 'Please <a href="' . $login_url . '">login.</a>';
        error_log($e->getType());
        error_log($e->getMessage());
      }   
      // Give the user a logout link 
      echo '<br /><a href="' . $facebook->getLogoutUrl() . '">logout</a>';
    } else {

      // No user, so print a link for the user to login
      // To post to a user's wall, we need publish_stream permission
      // We'll use the current URL as the redirect_uri, so we don't
      // need to specify it here.
      $login_url = $facebook->getLoginUrl( array( 'scope' => 'publish_stream' ) );
      echo 'Please <a href="' . $login_url . '">login.</a>';

    } 

  ?>      

  </body> 
</html> 
