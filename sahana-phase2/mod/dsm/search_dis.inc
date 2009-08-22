<?php
global $global;
include $global['approot'] . "/inc/lib_paging.inc";

function _shn_search_dis_default()
{
	shn_form_fopen("search_dis",null,array('req_message'=>false)); 
    shn_form_hidden(array('seq'=>'search'));
    //shn_form_hidden(array('incident'=>'one'));
    shn_form_fsopen(_t('General Search'));
    
    shn_form_text(_t('Disease Name'),'gname','size="30"');
    shn_form_text(_t('Medical Name'),'mname','size="30"');
    
    //shn_form_checkbox(_t('All incidents'),'all_incidents','onClick=setIncident()',null);
    shn_form_submit(_t('Next'));
    //advanced search link
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_dsm_searching($gname, $mname)
{
	if($gname == null && $mname == null) {
	    $sql = "SELECT * FROM diseases";
	} else if ($gname != null && $mname != null) {
	    $sql = "SELECT * FROM diseases as d WHERE d.dis_name LIKE '%{$gname}%' AND d.med_name LIKE '%{$mname}%'";
	} else if ($gname == null && $mname != null){
	    $sql = "SELECT * FROM diseases as d WHERE d.med_name LIKE '%{$mname}%'";
	} else if ($gname != null && $mname == null) {
		$sql = "SELECT * FROM diseases as d WHERE d.dis_name LIKE '%{$gname}%'";
	}
	$results=shn_paging_get_report($sql,10,$headers,array('post'=>true,'return'=>true));
	_shn_dsm_search_results($results);
}

function _shn_dsm_search_results($results)
{
	shn_form_fopen("search_dis",null,array('req_message'=>false));
	?>
	
	<br />
    <div id ="result">
	<table>
        <thead>

            <td><?php echo _t("Disease Name")?></td>
            <td><?php echo _t("Medical Name")?></td>
          	<!--<td><?php echo _t("Date")?></td>-->
            <!--<td><?php echo _t("Address")?></td>-->
         	<td><?php echo _t('Edit') ?></td>
         	<td><?php echo _t('View')?></td>
          	<!--<td><?php echo _t('Delete')?></td>-->
          	
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        <tr>
        
        <td><?php echo $results->fields['dis_name']?></td>
        <td><?php echo $results->fields['med_name']?></td>
        <!-- <td><?php echo $results->fields['dia_date']?></td>-->
        <!-- <td><?php echo $results->fields['address']?></td>-->
        <td><a href='index.php?mod=dsm&act=edit_case&dis_uuid=<?php echo $results->fields['dis_id']?>'><?php echo _t('Edit') ?></a></td>
      	<td><a href='index.php?mod=dsm&act=sur_rep&dis_uuid=<?php echo $results->fields['dis_id']?>'><?php echo _t('View') ?></a></td>
        <!-- <td><a href='index.php?mod=dsm&act=delete_individual&p_uuid=<?php echo $results->fields['pid']?>' onClick="javascript: return confirmdelete('<?php echo $results->fields['full_name']?>')">Delete</a></td>-->
      
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
