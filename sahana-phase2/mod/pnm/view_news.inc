<?php
function _shn_pnm_list_news(){
	global $global;
	require ($global['approot'] . 'mod/pnm/lib_news.inc');
	
	
	$res = _shn_pnm_get_news();
	?>
	<div id="result">
	<table>
	<tr>
		<th>Title</th>
		<th>Date/Time</th>
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


function _shn_pnm_view_news_item(){
	global $global;
	require ($global['approot'] . 'mod/pnm/lib_news.inc');
}
?>