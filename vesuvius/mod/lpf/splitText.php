<?php
function splitText($s, $delimiter, $limit) {
	$p = '';
	$i = 0;
	$j = 0;
	$len = 0;
	$r = array();
	if (strlen($s)<=$limit)
		$r[0] = $s;
	else {
		$arr = explode($delimiter, $s);
		$len = 0;
		$prefix = '';
		while ($i<count($arr)) {
			$prefix = "#".($j+1).".";
			if ($p=='')
				$p = $prefix . $arr[$i];
			else
				$p .= ' ' . $arr[$i];
			$p = trim($p);
			$len = strlen($p);
			if ($len > $limit) {
				$p = substr($p, 0, $len-strlen($arr[$i])-1);
				$r[$j++] = $p;
				$p = '';
			}
			else if ($len == $limit) {
				$r[$j++] = $p;
				$p = '';
				$i++;
			}
			else {
				$i++;
			}
		}
		if (strlen($p)>0)
			$r[count($r)] = $p;
	}
	return $r;
}
?>
