<?php

/**
 * DSM search_dis.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
include_once($global['approot'] . "/inc/lib_paging.inc");

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
	    $sql = "SELECT * FROM dsm_diseases";
	} else if ($gname != null && $mname != null) {
	    $sql = "SELECT * FROM dsm_diseases as d WHERE d.dis_name LIKE '%{$gname}%' AND d.med_name LIKE '%{$mname}%'";
	} else if ($gname == null && $mname != null){
	    $sql = "SELECT * FROM dsm_diseases as d WHERE d.med_name LIKE '%{$mname}%'";
	} else if ($gname != null && $mname == null) {
		$sql = "SELECT * FROM dsm_diseases as d WHERE d.dis_name LIKE '%{$gname}%'";
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

            <td><?=_t("Disease Name")?></td>
            <td><?=_t("Medical Name")?></td>
          	<!--<td><?=_t("Date")?></td>-->
            <!--<td><?=_t("Address")?></td>-->
         	<td><?=_t('Edit') ?></td>
         	<td><?=_t('View')?></td>
          	<!--<td><?=_t('Delete')?></td>-->
          	
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        <tr>
        
        <td><?=$results->fields['dis_name']?></td>
        <td><?=$results->fields['med_name']?></td>
        <!-- <td><?=$results->fields['dia_date']?></td>-->
        <!-- <td><?=$results->fields['address']?></td>-->
        
        <td><?php shn_acl_secure_hyperlink('dsm','edit_case','Edit',$stream=null,$params=array('dis_uuid'=>$results->fields['dis_id']),$text_opts='');?></td>
      	<td><?php shn_acl_secure_hyperlink('dsm','sur_rep','View',$stream=null,$params=array('dis_uuid'=>$results->fields['dis_id']),$text_opts='');?></td>
        <!-- <td><a href='index.php?mod=dsm&act=delete_individual&p_uuid=<?=$results->fields['pid']?>' onClick="javascript: return confirmdelete('<?=$results->fields['full_name']?>')">Delete</a></td>-->
      
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