<script language="JavaScript">

function setIncident()
{
if(document.forms[1].all_incidents.value=="")	

	document.forms[1].all_incidents.value="all";
	else
	document.forms[1].all_incidents.value="";
	
}


function confirmdelete(id)
{
return confirm('This person with  id '+id+' will be permanently deleted');
}


</script>


<?php
/* $Id: search_individual.inc,v 1.4 2008-01-03 04:41:36 isurunishan Exp $ */
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
    shn_form_fsopen(_('General Search'));
    shn_form_text(_('Any Card Number'),'card','size="30"');
    shn_form_text(_('Any Name'),'name','size="30"');
 
    shn_form_checkbox(_('All incidents'),'all_incidents','onClick=setIncident()',null);
    shn_form_submit(_('Next'));
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
            <td><?=_("Group Type")?></td>
            <td><?=_("Group Head Name")?></td>
            <td><?=_("Full Name")?></td>
            <td><?=_("Family Name")?></td>
          	<td><?=_("NIC")?></td>
            <td><?=_("Address")?></td>
         <td>Edit</td>
          <td>Delete</td>
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        <tr>
        <td>
        </td>
        <td><?=_shn_dvr_getoptiondescription($results->fields['group_type'])?></td>
        <td><?=_shn_dvr_get_person_full_name($results->fields['head_uuid'])?>
        <td><?=$results->fields['full_name']?></td>
        <td><?=$results->fields['family_name']?></td>
        <td><?=$results->fields['serial']?></td>
        <td><?=$results->fields['address']?></td>
        <td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?=$results->fields['pid']?>'>Edit</a></td>
      
        <td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?=$results->fields['pid']?>' onClick="javascript: return confirmdelete('<?=$results->fields['pid']?>')">Delete</a></td>
      
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
    shn_form_fsopen(_('Advanced Search'));

    shn_form_fsopen(_('Identity'));
    shn_form_text(_('Identity'),'idcard','size="30"');
    shn_form_checkbox(_('Identity Card'),'idcard_chk');
    shn_form_checkbox(_('Passport Number'),'pass_chk');
    shn_form_checkbox(_('Driving License'),'drv_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Name'));
    shn_form_text(_('Name'),'name','size="30"');
    shn_form_checkbox(_('Full Name'),'fullname_chk');
    shn_form_checkbox(_('Family Name'),'familyname_chk');
    shn_form_checkbox(_('Local Name'),'localname_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Basic Details'));
    shn_form_fsclose();

    shn_form_submit(_('Next'));
    shn_form_fsclose();
    ?>
     <a href="index.php?mod=dvr&act=search_individual">Simple Search</a>
    <?php
    shn_form_fclose();

}

?>