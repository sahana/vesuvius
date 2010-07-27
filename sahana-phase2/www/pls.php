<?
/** 
 * This script handles rerouting all requests from something like:
 *
 * http://server/pls.php
 * to
 * http://server/index.php?stream=soap&mod=ws&act=regdl&wbsmod=pls
 *
 * allowing other to access the services with a much shorter url. 
 */



/**
 * Make the base url of the links we use
 */
function makeBaseUrl() {
	if(isset($_SERVER['HTTPS'])) {
		$protocol = "https://";
	} else {
		$protocol = "http://";
	}
	$link = $protocol.$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$link = str_replace("pls.php", "", $link);
	return $link;
}



/** Redirect the web services to the longer URL */
header("Location: ".makeBaseUrl()."index.php?stream=soap&mod=ws&act=regdl&wbsmod=pls&".$_SERVER['QUERY_STRING']);
