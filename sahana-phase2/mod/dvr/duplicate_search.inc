<?php
/**
 *Major functions to search for duplicate entries of a disaster victim
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_misc.inc');
include_once ($global['approot'] . '/mod/dvr/lib.inc');

	global $global;
	_shn_dvr_print_header(_t("Duplicate Search"));
	shn_form_fopen("duplicate_sch", null, false);

	

	$duplicates = array();
	$duplicates = _shn_dvr_find_duplicates();
	if($duplicates)
	{
	shn_form_fsopen(_t("Duplicates"));
		?>
		<div id ="result">
			<table>
				<thead>
					<tr>
						<td><?=_t("Entry Name")?></td>
						<td><?=_t("Mobile")?></td>
						<td><?=_t("Telephone")?></td>
						<td><?=_t("Duplicate Entry")?></td>
						<td><?=_t("Mobile (Duplicate)")?></td>
						<td><?=_t("Telephone")?></td>
						<td><?=_t("Compare")?></td>
						<td><?=_t("Delete duplicate")?></td>
					</tr>	
				</thead>
		<?foreach($duplicates as $dup){ ?>
		<tr>
			<td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?=$dup['entry']['id']?>'><b><?=$dup['entry']['name']?></b></a></td>
			<td><?=$dup['entry']['mobile']?></td>
			<td><?=$dup['entry']['telephone']?></td>
			<td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?=$dup['dup']['id']?>'><b><?=$dup['dup']['name']?></b></a></td>
			<td><?=$dup['dup']['mobile']?></td>
			<td><?=$dup['dup']['telephone']?></td>
			<td><a href='index.php?mod=dvr&act=compare_duplicates&p_uuid1=<?=$dup['entry']['id']?>&p_uuid2=<?=$dup['dup']['id']?>'>Compare</a></td>
			<td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?=$dup['dup']['id']?>' onClick="javascript: return confirmdelete('<?=$dup['dup']['id']?>')">Delete</a></td>
		</tr> 
		
		<?php
		shn_form_fsclose();
		}//print $xx.',';
	}
	else
	{
		_shn_html_print_alert(_("No duplicates found."));
	}
?></table>
</div>
<?php
	
	shn_form_fclose();
	
/////////////////////////////////////////////////////////////////////////////

/**
 * get the entries from the database
 *
 * @return unknown
 */
function _shn_dvr_get_victims()
{
	global $global;
	$sql = "SELECT p.p_uuid AS id,p.full_name AS name,c.contact_value AS mobile,t.contact_value AS tele FROM person_uuid p,contact c,contact t WHERE p.p_uuid=c.pgoc_uuid AND p.p_uuid=t.pgoc_uuid AND c.opt_contact_type='mobile' AND t.opt_contact_type='telephone'";
	//$sql1 = "SELECT contact_value AS telephone FROM contact WHERE c.opt_contact_type='telephone'";
	$res = $global['db']->GetAll($sql);
	//$res1 = $global['db']->GetAll($sql1);
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
		$result[$i]['mobile'] = $r['mobile'];
		$result[$i]['telephone'] = $r['tele'];
		$i++;
	}

	return $result;
}

function _shn_dvr_find_duplicates()
{
	$a = array();
	$a = _shn_dvr_get_victims();
	$count = count($a);
	$b = array();
	for($j=0; $j<=$count; $j++)
	{	
		for($k=$count-1; $k>=0; $k--)
		{
			if($j < $k)
			{
				if ($a[$j]['name'] == $a[$k]['name'] && $a[$j]['name'] != null)
				{	
					$c = array();
					$c['entry']= $a[$j];
					$c['dup'] = $a[$k];
					array_push($b,$c);
				}

				elseif ($a[$j]['mobile'] == $a[$k]['mobile'] && $a[$j]['mobile'] != null)
				{
					$c = array();
					$c['entry']= $a[$j];
					$c['dup'] = $a[$k];
					array_push($b,$c);
					
				}
				
				elseif($a[$j]['tele'] == $a[$k]['tele'] && $a[$j]['name'] == $a[$k]['name'] && $a[$j]['tele'] != null)
				{
					$c = array();
					$c['entry']= $a[$j];
					$c['dup'] = $a[$k];
					array_push($b,$c);
				}
				//array_push($b['dup'],$a[$k]);
			}
			
			else
			break;
		}
///**
// * 
// * for($k=0; $k<=$count; $k++)
// * {
// * 		if($j != $k)
// * 		{
// * 			if($a[$j]['name'] == $a[$k]['name'])
// * 			array_push($b,$a[$j]['name']);
// * 		}
// * }
// * 
// */

	}
	return $b;
}

?>


<script language="JavaScript">

function confirmdelete(id)
{
return confirm('This person with  id '+id+' will be permanently deleted');
}


</script>


