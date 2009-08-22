<?php
/**News Library of the Press and Media Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
* @copyright Respective Authors
* @package    sahana
* @subpackage pnm
* 
* Developed during Sahana 2009 as a tribute.
*/
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
