<?php
include 'EpiCurl.php';
include 'EpiOAuth.php';
include 'EpiTwitter.php';
$consumer_key = 'tY5Tin1kJAU239FROhrA';
$consumer_secret = 'QNJwKOFcTNpDrqUrzAoJ0xuiVHboClavcXXoRcQ88';
$token = '449990541-BORa5ny2TeuFZ9p5XsJjxS1hKm7dGFzGcJKC0hJZ';
$secret= 'v6xh3p57A4nfSPD8TutMWdO7xYkTBl9lcIAz2tiZg';
$twitterObj = new EpiTwitter($consumer_key, $consumer_secret, $token, $secret);
$twitterObjUnAuth = new EpiTwitter($consumer_key, $consumer_secret);
?>

<h1>Single test to verify everything works ok</h1>

<h2><a href="javascript:void(0);" onclick="viewSource();">View the source of this file</a></h2>
<div id="source" style="display:none; padding:5px; border: dotted 1px #bbb; background-color:#ddd;">
<?php highlight_file(__FILE__); ?>
</div>

<hr>

<h2>Generate the authorization link</h2>
<?php echo $twitterObjUnAuth->getAuthenticateUrl(); ?>

<hr>

<h2>Verify credentials</h2>
<?php
  $creds = $twitterObj->get('/account/verify_credentials.json');
?>
<pre>
<?php print_r($creds->response); ?>
</pre>

<hr>

<h2>Post status</h2>
<?php
  $status = $twitterObj->post('/statuses/update.json', array('status' => 'This a simple test from twitter-async at ' . date('m-d-Y h:i:s')));
?>
<pre>
<?php print_r($status->response); ?>
</pre>

<script> function viewSource() { document.getElementById('source').style.display=document.getElementById('source').style.display=='block'?'none':'block'; } </script>
