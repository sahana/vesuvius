<script language="JavaScript">

function setIncident()
{
if(document.forms[1].all_incidents.value=="")	

	document.forms[1].all_incidents.value="all";
	else
	document.forms[1].all_incidents.value="";
	
}


function confirmdelete(name)
{
return confirm(name+' will be permanently deleted');
}


</script>


<?php

/* $Id: search_individual.inc,v 1.11 2009-08-22 17:17:22 ravithb Exp $ */

/* $Id: search_individual.inc,v 1.11 2009-08-22 17:17:22 ravithb Exp $ */

/**
 * 
 * Search groups and individuals in disaster victims registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_dvr_search_default()
{
    shn_form_fopen("search_individual",null,array('req_message'=>false)); 
    shn_form_hidden(array('seq'=>'search'));
    shn_form_hidden(array('incident'=>'one'));
    shn_form_fsopen(_t('General Search'));
    shn_form_text(_t('Any Card Number'),'card','size="30"');
    shn_form_text(_t('Any Name'),'name','size="30"');
 
    shn_form_checkbox(_t('All incidents'),'all_incidents','onClick=setIncident()',null);
    shn_form_submit(_t('Next'));
    //advanced search link
    shn_form_fsclose();
    ?>
<!--    <a href="index.php?mod=dvr&act=search_individual&seq=advanced">Advanced Search</a>-->
    
    <?php
    shn_form_fclose();
}

//advanced search to be completed




function shn_dvr_individual_search_results()
{
	 ?>
	<br />
	<?php
	global $global;
	$card=$_POST['card'];
	$name=$_POST['name'];
	
	$all_incidents=$_POST['all_incidents'];
	if($all_incidents!=null)
	{
		$all_incidents="all";
	}
	else
	{
		$all_incidents=null;
	}
	
    include_once ($global['approot'] . '/mod/dvr/data_access.inc');
    include_once ($global['approot'] . '/mod/dvr/lib.inc');
    $results=_shn_dvr_get_individual_search_results($card,$name,$all_incidents);
    //print 'all incidents'.$all_incidents;
	
	?>
	
	<br />
    <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?php echo _t("Group Type")?></td>
            <td><?php echo _t("Group Head Name")?></td>
            <td><?php echo _t("Full Name")?></td>
            <td><?php echo _t("Family Name")?></td>
          	<td><?php echo _t("NIC")?></td>
            <td><?php echo _t("Address")?></td>
         	<td><?php echo _t('Edit') ?></td>
         	<td><?php echo _t('Transfer')?></td>
          	<td><?php echo _t('Delete')?></td>
          	
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        <tr>
        <td>
        </td>
        <td><?php echo _shn_dvr_getoptiondescription($results->fields['group_type'])?></td>
        <td><?php echo _shn_dvr_get_person_full_name($results->fields['head_uuid'])?>
        <td><?php echo $results->fields['full_name']?></td>
        <td><?php echo $results->fields['family_name']?></td>
        <td><?php echo $results->fields['serial']?></td>
        <td><?php echo $results->fields['address']?></td>
        <td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $results->fields['pid']?>'><?php echo _t('Edit') ?></a></td>
      	<td><a href='index.php?mod=dvr&act=transfer_indv&p_uuid=<?php echo $results->fields['pid']?>'><?php echo _t('Transfer') ?></a></td>
        <td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?php echo $results->fields['pid']?>' onClick="javascript: return confirmdelete('<?php echo $results->fields['full_name']?>')">Delete</a></td>
      
        </tr>
        <?php
        $results->MoveNext();
        }
        ?>
        </table>
        </div>
        
        <?php
	
//print 'ok'	;

	
}




function shn_dvr_search_advance()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen(_t('Advanced Search'));

    shn_form_fsopen(_t('Identity'));
    shn_form_text(_t('Identity'),'idcard','size="30"');
    shn_form_checkbox(_t('Identity Card'),'idcard_chk');
    shn_form_checkbox(_t('Passport Number'),'pass_chk');
    shn_form_checkbox(_t('Driving License'),'drv_chk');
    shn_form_fsclose();

    shn_form_fsopen(_t('Name'));
    shn_form_text(_t('Name'),'name','size="30"');
    shn_form_checkbox(_t('Full Name'),'fullname_chk');
    shn_form_checkbox(_t('Family Name'),'familyname_chk');
    shn_form_checkbox(_t('Local Name'),'localname_chk');
    shn_form_fsclose();

    shn_form_fsopen(_t('Basic Details'));
    shn_form_fsclose();

    shn_form_submit(_t('Next'));
    shn_form_fsclose();
    ?>
     <a href="index.php?mod=dvr&act=search_individual">Simple Search</a>
    <?php
    shn_form_fclose();

}

