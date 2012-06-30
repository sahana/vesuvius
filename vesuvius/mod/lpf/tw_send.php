<?php
include_once( $global['approot'].'/mod/lpf/twitter/EpiCurl.php');
include_once( $global['approot'].'/mod/lpf/twitter/EpiOAuth.php');
include_once( $global['approot'].'/mod/lpf/twitter/EpiTwitter.php');
include_once( $global['approot'].'/mod/lpf/splitText.php');

function tw_send($consumer_key, $consumer_secret, $token, $secret, $msg) {
	try {
		$twitterObj = new EpiTwitter($consumer_key, $consumer_secret, $token, $secret); //$a[0], $a[1], $a[2], $a[3]);
		$arr = splitText($msg, ' ', 140);
		$i=count($arr)-1;
		while ($i >= 0) {
			$status = $twitterObj->post('/statuses/update.json', array('status' => $arr[$i]));
			$i--;
		}
		// echo post sent successfully
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New post was sent to Twitter');
	}
	catch (Exception $e) {
		// save error
		//em_save_post_error($id, $_SESSION['user'], $e->getMessage());
		// echo error
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>Twitter error:'.$e->getMessage());
	}
}
?>
