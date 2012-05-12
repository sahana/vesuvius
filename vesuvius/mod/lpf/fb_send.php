<?php
require_once($global['approot']. '/mod/lpf/facebook/src/facebook.php' );

function fb_send($appid, $appsecret, $userid, $msg) {

	try {
		$facebook = new Facebook(array(
			'appId'  => $appid,
			'secret' => $appsecret,
			'cookie' => true,
		));
		$token = $facebook->getAccessToken();
		$post =  array(
			'access_token' => $token,
			'message' => $msg
		);
		$res = $facebook->api('/'.$userid.'/feed', 'POST', $post);
		// echo post was sent successfully
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New post was sent to Facebook');
	}
	catch (Exception $e) {
		// save error
		//em_save_post_error($id, $_SESSION['user'], $e->getMessage());
		// echo the error message
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Facebook error:'.$e->getMessage());
	}
}
?>
