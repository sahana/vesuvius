<?php

include_once ($global['approot'] . '/inc/lib_form.inc');

global $global;
print "Transfer Individual";
$a = array();
$a = duplicate();
foreach($a as $xx)
print $xx.'_______';

function ela()
{
	global $global;
	$sql = "SELECT p.p_uuid as id,p.full_name as name,c.contact_value FROM person_uuid p,contact c WHERE p.p_uuid=c.pgoc_uuid AND c.opt_contact_type='mobile'";

	$res = $global['db']->GetAll($sql);
	$result=array();

	$i = 0;
	//while(!$res->EOF){
	//	$result[$i]['id'] = $res->fields['id'];
	//	$result[$i]['name'] = $res->fields['name'];
	//	$i++;
	//	$res->MoveNext();
	//}
	foreach($res as $r){
		$result[$i]['id'] = $r['id'];
		$result[$i]['name'] = $r['name'];
		
		$i++;
	}

	return $result;
}

function duplicate()
{
	$a = array();
	$a = ela();
	$count = count($a);
	$b = array();
	for($j=0; $j<=$count; $j++)
	{	
		for($k=0; $k<=$count; $k++)
		{
			if($j!=$k)
			{
				if($a[$j]['name'] == $a[$k]['name'])
				array_push($b,$a[$j]['name']);
			}
		}
		
	}
	return $b;
}

?>
