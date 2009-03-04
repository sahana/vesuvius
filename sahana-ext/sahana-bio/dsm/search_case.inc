<?php

/**
 * DSM search_case.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @author     Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
include_once $global['approot'] . "/inc/lib_paging.inc";

function _shn_search_case_default()
{
	global $global;
	$db = $global['db'];
	shn_form_fopen("search_case",null,array('req_message'=>false));
	shn_form_hidden(array('seq'=>'search'));
	//shn_form_hidden(array('incident'=>'one'));
	shn_form_fsopen(_t('General Search'));

	$res = $db->Execute("SELECT dis_id,dis_name FROM dsm_diseases");
	$opts = $res->GetAssoc();

	//shn_form_text(_t('Any Name'),'name','size="30"');
	//shn_form_text(_t('Disease'),'disease','size="30"');
	shn_form_select($opts,_t("Disease"),'disease','multiple="multiple" size="5"');

	$res = $db->Execute("SELECT option_code,option_description FROM field_options WHERE field_name='dsm_field_data_type'");
	while($res && $row=$res->FetchRow()){
		shn_form_text($row['option_description'],'~dsm~field~data~type@'.$row['option_code']);
	}

	//shn_form_checkbox(_t('All incidents'),'all_incidents','onClick=setIncident()',null);
	shn_form_submit(_t('Next'));
	//advanced search link
	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_dsm_search_case(){
	global $global;
	$db = $global['db'];
	$page = 1;
	if(isset($_REQUEST['page_no'])){
		$page = $_REQUEST['page_no'];
	}

	$disease = $_POST['disease'];

	$query = "SELECT cd.case_id,cd.submission_id,cd.patient_identifier,d.dis_name,o.option_description,f.text,cd.value FROM dsm_case_data cd JOIN dsm_diseases d ON d.dis_id = cd.dis_id JOIN dsm_fields f ON f.field_id = cd.field_id JOIN field_options o ON f.data_type = o.option_code AND o.field_name='dsm_field_data_type' WHERE ";

	$conditions = '';
	if(isset($disease) && strlen(trim($disease))>0){
		$conditions .= (" d.dis_id = '".$disease."' AND ");
	}

	foreach($_POST as $k=>$v){
		//echo $k."->".$_POST[$k]."<br/>";
		if(preg_match('/\~dsm\~field\~data\~type@.+/',$k)>0){
			$data_type = explode('~dsm~field~data~type@',$k);
			$data_type = $data_type[1];

			if(isset($data_type) && strlen(trim($data_type))>0){
				if(is_array($v)==false){
					if(strlen(trim($v))>0){
						$conditions .= ("( f.data_type = '".$data_type."' AND cd.value LIKE '%".$v."%') AND ");
					}
				}else{
					$conditions .= ("( d.data_type = '".$data_type."'");
					foreach($v as $_k=>$_v){
						if(strlen(trim($_v))>0){
							$conditions .= (" AND (( cd.value LIKE '%".$_v."%') OR ");
						}
					}
					$conditions .= ") ) AND ";
				}
			}
		}
	}
	
	$conditions .= "1=1";
	$query = $query.$conditions;
	$query .= " ORDER BY cd.case_id,cd.dis_id";
	//$db->debug = true;
	
	/*$res = $db->Execute($query);
	$count = $res->RecordCount();
	$rpp = 20;
	$res = $db->SelectLimit($query,$rpp);*/
	
	shn_paging_get_report($query,20,array(_t('Case ID'),_t('Submition ID'),_t('Patient Identification Code'),_t('Disease Name'),_t('Data Type'),_t('Field Name'),_t('Value')),array('paging_url'=>'index.php?mod=dsm&act=search_case&seq=search'));
}
//function _shn_dsm_searching($name, $disease)
//{
////    if($name){
////	    //split name
////	    $names = preg_split("/\s+/",$_POST['name']);
////	    foreach($names as $name){
////	        $encode1 .= " encode1 LIKE '".soundex($name)."' OR ";
////	        $encode2 .= " encode2 LIKE '".metaphone($name)."%' OR ";
////	    }
////	    $encode1 = substr($encode1,0,strlen($encode1) - 3);
////	    $encode2 = substr($encode2,0,strlen($encode2) - 3);
////        $sql = "SELECT pgl_uuid as p_uuid FROM phonetic_word, person_status WHERE pgl_uuid=p_uuid AND (($encode1) OR ($encode2)) $type GROUP BY 1";
////    }
//    if ($name != null && $disease != null)
//    {
//	    $sql = "SELECT * FROM dsm_diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND d. AND p.full_name LIKE '%{$name}%' AND d.disease = '{$disease}'";
//    } else if($name != null && $disease == null) {
//    	$sql = "SELECT * FROM dsm_diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND p.full_name LIKE '%{$name}%'";
//    }else if($name == null && $disease != null) {
//    	$sql = "SELECT * FROM dsm_diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND d.disease = '{$disease}'";
//    }else if($name == null && $disease == null) {
//    	$sql = "SELECT * FROM dsm_diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid";
//    }
//
//	$results=shn_paging_get_report($sql,10,$headers,array('post'=>true,'return'=>true));
//	_shn_dsm_search_results($results);
//}

function _shn_dsm_search_results($results)
{
	shn_form_fopen("search_case",null,array('req_message'=>false));
	?>

<br />
<div id="result">
<table>
	<thead>

		<td><?=_t("Patient Name")?></td>
		<td><?=_t("Doctor Name")?></td>
		<td><?=_t("Date")?></td>
		<td><?=_t("Address")?></td>
		<td><?=_t('Edit') ?></td>
		<td><?=_t('View')?></td>
		<td><?=_t('Delete')?></td>

	</thead>
	<?php
	while(!$results->EOF)
	{
		?>
	<tr>

		<td><?=_shn_dsm_get_person_full_name($results->fields['pat_id'])?></td>
		<td><?=_shn_dsm_get_person_full_name($results->fields['doc_id'])?></td>
		<td><?=$results->fields['dia_date']?></td>
		<td><?=$results->fields['address']?></td>
		<td><a
			href='index.php?mod=dsm&act=edit_case&p_uuid=<?=$results->fields['pat_id']?>'><?=_t('Edit') ?></a></td>
		<td><a
			href='index.php?mod=dsm&act=view_case&p_uuid=<?=$results->fields['pat_id']?>'><?=_t('View') ?></a></td>
		<td><a
			href='index.php?mod=dsm&act=delete_individual&p_uuid=<?=$results->fields['pid']?>'
			onClick="javascript: return confirmdelete('<?=$results->fields['full_name']?>')">Delete</a></td>

	</tr>
	<?php
	$results->MoveNext();
	}
	?>
</table>
</div>

	<?php
	shn_form_fclose();
}
?>