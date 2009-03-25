<?php
function _shn_pnm_get_news(){

	global $global;
	$db=$global['db'];
	$sql = "SELECT *
FROM `pnm_news`
ORDER BY `pnm_news`.`time` DESC";
	$res = $db->GetAll($sql);
	return $res;
}

function _shn_pnm_get_news_item($uuid){
	global $global;
	$db=$global['db'];
	
	$sql= "SELECT * FROM `pnm_news` WHERE uuid='$uuid'";
	$res= $db->Execute($sql);
	return $res;
}
?>