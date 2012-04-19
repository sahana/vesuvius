<?php
require_once( $global['approot'].'/mod/lpf/googlevoice/class.googlevoice.php');
include_once( $global['approot'].'/mod/lpf/splitText.php');

function gv_send($gmail, $gmail_pwd, $msg) {
	try {
		$gv = new GoogleVoice($gmail, $gmail_pwd);
		$arr = splitText($msg, ' ', 140);
		$i=count($arr)-1;
		while ($i >= 0) {
			$gv->sms($a[1], $arr[$i]);
			$i--;
		}
		// echo sent successfully
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>New SMS message was sent to '. $a[0]. ', status: '.$gv->status);
	}
	catch (Exception $e) {
		// echo save error
		//em_save_post_error($id, $_SESSION['user'], $e->getMessage());
		// echo error
		//$global['xajax_res']->addAppend('rezLog', 'innerHTML', '<br>SMS error:'. $e->getMessage());
	}
}       
?>
