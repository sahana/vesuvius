<?php
/**View News Functionality of the Press and Media Module
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
function _shn_pnm_list_news(){
	global $global;
	require ($global['approot'] . 'mod/pnm/lib_news.inc');
	
	
	$res = _shn_pnm_get_news();
	?>
	<div id="result">
	<table width="10">
	<tr>
		<th >Title</th>
		<th >Date/Time</th>
	</tr>
	<?php
	foreach ($res as $row){
		echo '<tr>';
		//	echo '<td>'.$row[0] .'</td>';
			echo "<td> <a href=index.php?mod=pnm&act=view_news_item&uuid=$row[0]>$row[1]</a></td>";
			//echo '<td>'.$row[2] .'</td>';
			echo '<td>'.date('Y-M-d h:m',$row[3]).'</td>';
		echo '</tr>';
	}
	?>
	</table>
	</div>
	<?php
}


function _shn_pnm_view_news_item($uuid){
	global $global;
	require ($global['approot'] . 'mod/pnm/lib_news.inc');
	
	$res = _shn_pnm_get_news_item($uuid);
	
	shn_form_fopen("view_news",null,false);
	//shn_form_fsopen(_t('View News item'),false);
	echo '<h2 align="center">' . $res->Fields(1) . '</h2>';
	echo $res->Fields(2);
	//shn_form_fsclose();
	shn_form_fclose();
}
