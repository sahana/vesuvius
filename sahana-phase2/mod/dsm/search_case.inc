<?php
global $global;
include $global['approot'] . "/inc/lib_paging.inc";

function _shn_search_case_default()
{
	shn_form_fopen("search_case",null,array('req_message'=>false)); 
    shn_form_hidden(array('seq'=>'search'));
    //shn_form_hidden(array('incident'=>'one'));
    shn_form_fsopen(_t('General Search'));
    
    shn_form_text(_t('Any Name'),'name','size="30"');
    shn_form_text(_t('Disease'),'disease','size="30"');
    
    //shn_form_checkbox(_t('All incidents'),'all_incidents','onClick=setIncident()',null);
    shn_form_submit(_t('Next'));
    //advanced search link
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_dsm_searching($name, $disease)
{
//    if($name){
//	    //split name
//	    $names = preg_split("/\s+/",$_POST['name']);
//	    foreach($names as $name){
//	        $encode1 .= " encode1 LIKE '".soundex($name)."' OR ";
//	        $encode2 .= " encode2 LIKE '".metaphone($name)."%' OR ";
//	    }
//	    $encode1 = substr($encode1,0,strlen($encode1) - 3);
//	    $encode2 = substr($encode2,0,strlen($encode2) - 3);
//        $sql = "SELECT pgl_uuid as p_uuid FROM phonetic_word, person_status WHERE pgl_uuid=p_uuid AND (($encode1) OR ($encode2)) $type GROUP BY 1";
//    }
    if ($name != null && $disease != null)
    {
	    $sql = "SELECT * FROM diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND d. AND p.full_name LIKE '%{$name}%' AND d.disease = '{$disease}'";
    } else if($name != null && $disease == null) {
    	$sql = "SELECT * FROM diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND p.full_name LIKE '%{$name}%'";
    }else if($name == null && $disease != null) {
    	$sql = "SELECT * FROM diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid AND d.disease = '{$disease}'";
    }else if($name == null && $disease == null) {
    	$sql = "SELECT * FROM diagnosis as d,person_uuid as p WHERE d.pat_id=p.p_uuid";
    }
    
	$results=shn_paging_get_report($sql,10,$headers,array('post'=>true,'return'=>true));
	_shn_dsm_search_results($results);
}

function _shn_dsm_search_results($results)
{
	shn_form_fopen("search_case",null,array('req_message'=>false));
	?>
	
	<br />
    <div id ="result">
	<table>
        <thead>

            <td><?php echo _t("Patient Name")?></td>
            <td><?php echo _t("Doctor Name")?></td>
          	<td><?php echo _t("Date")?></td>
            <td><?php echo _t("Address")?></td>
         	<td><?php echo _t('Edit') ?></td>
         	<td><?php echo _t('View')?></td>
          	<td><?php echo _t('Delete')?></td>
          	
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        <tr>
        
        <td><?php echo _shn_dsm_get_person_full_name($results->fields['pat_id'])?></td>
        <td><?php echo _shn_dsm_get_person_full_name($results->fields['doc_id'])?></td>
        <td><?php echo $results->fields['dia_date']?></td>
        <td><?php echo $results->fields['address']?></td>
        <td><a href='index.php?mod=dsm&act=edit_case&p_uuid=<?php echo $results->fields['pat_id']?>'><?php echo _t('Edit') ?></a></td>
      	<td><a href='index.php?mod=dsm&act=view_case&p_uuid=<?php echo $results->fields['pat_id']?>'><?php echo _t('View') ?></a></td>
        <td><a href='index.php?mod=dsm&act=delete_individual&p_uuid=<?php echo $results->fields['pid']?>' onClick="javascript: return confirmdelete('<?php echo $results->fields['full_name']?>')">Delete</a></td>
      
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
 