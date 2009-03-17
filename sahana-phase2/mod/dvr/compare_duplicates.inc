<?php
/**
 *Major functions to compare details of duplicate entries of disaster victims
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
include_once ($global['approot'] . '/mod/dvr/lib.inc');
include_once ($global['approot'] . '/mod/dvr/data_access.inc');
include_once ($global['approot'] . '/mod/or/lib_or.inc');

/**
 * //////////////////////////////////////////////////////////////////////////
 */	
	switch($_REQUEST['seq'])
	{	
		case 'delete' :
		{
			$_POST['p_uuid']= $_SESSION['dvr']['person2']['id'];
			//shn_dvr_delete_individual();
			_shn_dvr_delete_person($_SESSION['dvr']['person2']['id']);
			$msg = $_SESSION['dvr']['person2']['p_full_name'] . " person was succesfully deleted ";
			add_confirmation($msg);
			unset($_SESSION['dvr']['person1']);
			unset($_SESSION['dvr']['person2']);
			shn_dvr_duplicate_search();
			
			break;
		}
		default :
		{
			$p_uuid1 = $_GET['p_uuid1'];
			$p_uuid2 = $_GET['p_uuid2'];
			if($p_uuid2)
			_shn_dvr_comparison_page($p_uuid1,$p_uuid2);
			
			else
			_shn_dvr_comparison_pageall($p_uuid1);
		}
		
		
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * get all the details of the victim from database and return those
 *
 * @param unknown_type $p_uuid
 * @param unknown_type $person
 * @return $_SESSION['dvr'][$person][......]
 */
function _shn_dvr_get_compare_details($p_uuid,$person)
{
	$_SESSION['dvr'][$person]['id'] = $p_uuid;
	$results = get_person_major_details($p_uuid);
	$_SESSION['dvr'][$person]['group_type'] = _shn_dvr_getoptiondescription($results->fields['group_type']);
	$_SESSION['dvr'][$person]['head_id'] = $results->fields['head_id'];
	$_SESSION['dvr'][$person]['group_id'] = $results->fields['groupid'];
	
	$personal = get_person_full_name($p_uuid);

	$_SESSION['dvr'][$person]['p_full_name'] = $personal->fields['full_name'];
	$_SESSION['dvr'][$person]['p_family_name'] = $personal->fields['family_name'];
	$_SESSION['dvr'][$person]['p_local_name'] = $personal->fields['l10n_name'];
	
	$personal_results = get_personal_details($p_uuid);
	
	$_SESSION['dvr'][$person]['dob'] = $personal_results->fields['birth_date'];
	$_SESSION['dvr'][$person]['age_group'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_age_group']);
	$_SESSION['dvr'][$person]['gender'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_gender']);
	$_SESSION['dvr'][$person]['marital'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_marital_status']);
	$_SESSION['dvr'][$person]['religion'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_religion']);
	$_SESSION['dvr'][$person]['race'] = _shn_dvr_getoptiondescription($personal_results->fields['opt_race']);
	
	$_SESSION['dvr'][$person]['curr_loc'] = _shn_dvr_get_current_location($p_uuid);
	$_SESSION['dvr'][$person]['dis_loc'] = _shn_dvr_get_displaced_location($p_uuid);
	
	$id_results = get_identity_to_person($p_uuid);

	while (!$id_results->EOF) {
		$id = $id_results->fields['serial'];
		$val = $id_results->fields['opt_id_type'];
		if ($val == 'idcard') {
			$_SESSION['dvr'][$person]['idcard'] = $id;
		} else
			if ($val == 'pas') {
				$_SESSION['dvr'][$person]['passport'] = $id;
			} else
				if ($val == 'dln') {
					$_SESSION['dvr'][$person]['drv_licence'] = $id;
				}
		$id_results->MoveNext();
	}
	
	$contact_results = get_contacts($p_uuid);
	
	while (!$contact_results->EOF) {
		$ctct_type = $contact_results->fields['opt_contact_type'];
		$ctct_value = $contact_results->fields['contact_value'];

		if ($ctct_type == "mobile") {
			$_SESSION['dvr'][$person]['mobile'] = $ctct_value;
		} else
			if ($ctct_type == "telephone") {
				$_SESSION['dvr'][$person]['telephone'] = $ctct_value;
			} else
				if ($ctct_type == "address") {
					$_SESSION['dvr'][$person]['address'] = $ctct_value;
				}
		$contact_results->MoveNext();

	}
	
	$physical_result = get_person_physical_details($p_uuid);
	
	$_SESSION['dvr'][$person]['opt_eye_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_eye_color']);
	$_SESSION['dvr'][$person]['opt_skin_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_skin_color']);
	$_SESSION['dvr'][$person]['opt_hair_color'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_hair_color']);
	$_SESSION['dvr'][$person]['height'] = $physical_result->fields['height'];
	$_SESSION['dvr'][$person]['weight'] = $physical_result->fields['weight'];
	$_SESSION['dvr'][$person]['opt_blood_type'] = _shn_dvr_getoptiondescription($physical_result->fields['opt_blood_type']);
	$_SESSION['dvr'][$person]['comments'] = $physical_result->fields['comments'];
	$chars = preg_split('/,/', $comments);
	$_SESSION['dvr'][$person]['last_clothing'] = $chars[0];
	
	return $_SESSION['dvr'][$person];
}


function _shn_dvr_comparison_pageall($p_uuid)
{
	_shn_dvr_print_header(_t("Compare Duplicates"));
	shn_form_fopen("compare_duplicates", null, false);
	shn_form_hidden(array('seq'=>'delete'));//echo "<pre>";var_dump($_SESSION['entries']);echo "</pre>";
	_shn_dvr_get_compare_details($p_uuid, "entry");
	
	$pop = $_SESSION['entries']; //echo "<pre>";var_dump($pop[$p_uuid]);echo "</pre>";
	$dup_count = count($pop[$p_uuid]); 
	?>
	<div>
	<table width="100%">
				<thead>
					<tr>
						<td><?php echo _t("Entry Name")?></td>
						<td><?php echo _t("Mobile")?></td>
						<td><?php echo _t("Telephone")?></td>
						<td><?php echo _t("NIC")?></td>
						<td><?php echo _t("Passport")?></td>
						<td><?php echo _t("Licence")?></td>
					</tr>
				</thead>
				<tr>
					<td><b><?php echo $_SESSION['dvr']['entry']['p_full_name']?></b></td>
					<!-- <td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $_SESSION['dvr']['entry']['id']?>'><b><?php echo $_SESSION['dvr']['entry']['p_full_name']?></b></a></td> -->
					<td><?php echo $_SESSION['dvr']['entry']['mobile']?></td>
					<td><?php echo $_SESSION['dvr']['entry']['telephone']?></td>
					<td><?php echo $_SESSION['dvr']['entry']['idcard']?></td>
					<td><?php echo $_SESSION['dvr']['entry']['passport']?></td>
					<td><?php echo $_SESSION['dvr']['entry']['drv_licence']?></td>
					<!-- <td></td> -->
					<!-- <td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?php echo $_SESSION['dvr']['entry']['id']?>' onClick="javascript: return confirmdelete('<?php echo $_SESSION['dvr']['entry']['p_full_name']?>')">Delete</a></td> -->
                </tr>
             </table>
	</div>
	<br>
	<p><b><?php echo  $dup_count." duplicates found." ?></b></p>
	<div id ="result">
			<table width="100%">
				<thead>
					<tr>
						<td><?php echo _t("Duplicates")?></td>
						<td><?php echo _t("Mobile")?></td>
						<td><?php echo _t("Telephone")?></td>
						<td><?php echo _t("NIC")?></td>
						<td><?php echo _t("Passport")?></td>
						<td><?php echo _t("Licence")?></td>
						<td><?php echo _t("Compare")?></td>
						<td><?php echo _t("Delete duplicate")?></td>
					</tr>	
				</thead>
           
	<?php
	
	foreach($pop[$p_uuid] as $p){
	    _shn_dvr_get_compare_details($p, "person");
	?>
	<tr>
			<!-- <td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $_SESSION['dvr']['person']['id']?>'><b><?php echo $_SESSION['dvr']['person']['p_full_name']?></b></a></td> -->
			<td><b><?php echo $_SESSION['dvr']['person']['p_full_name']?></b></td>
			<td><?php echo $_SESSION['dvr']['person']['mobile']?></td>
			<td><?php echo $_SESSION['dvr']['person']['telephone']?></td>
			<td><?php echo $_SESSION['dvr']['person']['idcard']?></td>
			<td><?php echo $_SESSION['dvr']['person']['passport']?></td>
			<td><?php echo $_SESSION['dvr']['person']['drv_licence']?></td>
			<td><a href='index.php?mod=dvr&act=compare_duplicates&p_uuid1=<?php echo $_SESSION['dvr']['entry']['id']?>&p_uuid2=<?php echo $_SESSION['dvr']['person']['id']?>'>Compare</a></td>
			<td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?php echo $_SESSION['dvr']['person']['id']?>' onClick="javascript: return confirmdelete('<?php echo $_SESSION['dvr']['person']['p_full_name']?>')">Delete</a></td>
		</tr>
		<?php
		shn_form_fsclose();
		}
?></table>
</div>
<?php
    shn_form_fclose();
	shn_form_fopen("duplicate_search",null,false);
	shn_form_hidden(array('seq'=>'back'));
	shn_form_submit("Back");
	shn_form_fclose();
	
}


/**
 *comparison page
 */
function _shn_dvr_comparison_page($p_uuid1,$p_uuid2)
{
	_shn_dvr_print_header(_t("Compare Duplicates"));
	shn_form_fopen("compare_duplicates", null, false);
	shn_form_hidden(array('seq'=>'delete'));
    shn_form_fsopen(_t('Details'));
	

	_shn_dvr_get_compare_details($p_uuid1, "person1");
	_shn_dvr_get_compare_details($p_uuid2, "person2");
	
	?>
<DIV id ="result">	
<table width="100%">
  <thead>
  	<tr>
  	   	<td><?php echo _t('Description') ?></td>
    	<td><?php echo _t('Detail of the Entry') ?></td>
    	<td><?php echo _t('Detail of the Duplicate') ?></td>
    </tr>
  </thead>
  <tr>
  	   	<td></td>
    	<td style="text-align: center;"><?shn_show_thumb_url($p_uuid1, 'database', 'dvr', 'addvictim_img', false);?></td>
    	<td style="text-align: center;"><?shn_show_thumb_url($p_uuid2, 'database', 'dvr', 'addvictim_img', false);?></td>
    </tr>
  <tr>
  <td><b><?php echo _t('Personel details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  
  <tr>
  	<td><?php echo _t('Full Name') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['p_full_name'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['p_full_name']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Family Name') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['p_family_name']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['p_family_name'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Local Name') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['p_local_name'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['p_local_name'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Group Type') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['group_type'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['group_type']  ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Date of Birth') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['dob'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['dob'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Age Group') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['age_group'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['age_group'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Gender') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['gender'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['gender'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Marital Status') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['marital'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['marital'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Religion') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['religion'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['religion'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Race') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['race'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['race'] ?></td>
  </tr>
  <tr>
  <td><b><?php echo _t('Contact Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?php echo _t('Mobile Number') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['mobile']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['mobile']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Telephone Number') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['telephone']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['telephone']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Address') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['address']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['address']?></td>
  </tr>
  <tr>
  <td><b><?php echo _t('Location Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?php echo _t('Current Location') ?></td>
    <td><?php echo shn_location_string($_SESSION['dvr']['person1']['curr_loc']) ?></td>
    <td><?php echo shn_location_string($_SESSION['dvr']['person2']['curr_loc'])?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Displaced Location') ?></td>
    <td><?php echo shn_location_string($_SESSION['dvr']['person1']['dis_loc']) ?></td>
    <td><?php echo shn_location_string($_SESSION['dvr']['person2']['dis_loc']) ?></td>
  </tr>
   <tr>
  <td><b><?php echo _t('Identity') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  <tr>
  	<td><?php echo _t('NIC') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['idcard']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['idcard'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Passport') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['passport']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['passport'] ?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Driving Licence') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['drv_licence'] ?></td>
    <td><?php echo $_SESSION['dvr']['person2']['drv_licence'] ?></td>
  </tr>
  <tr>
  <td><b><?php echo _t('Physical Details') ?></b></td>
  <td></td>
  <td></td>
  </tr>
  
  <tr>
  	   	<td><?php echo _t('Finger Photograph') ?></td>
    	<td><?shn_show_thumb_url($p_uuid1, 'database', 'dvr', 'addfingerprint_img', false, "finger");?></td>
    	<td><?shn_show_thumb_url($p_uuid2, 'database', 'dvr', 'addfingerprint_img', false, "finger");?></td>
    </tr>
  <tr>
  	<td><?php echo _t('Eye Colour') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['opt_eye_color']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['opt_eye_color']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Skin Colour') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['opt_skin_color']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['opt_skin_color']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Hair Colour') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['opt_hair_color']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['opt_hair_color']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Height') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['height']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['height']?></td>
  </tr>
  <tr>
  	<td><?php echo _t('Weight') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['weight']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['weight']?></td>
  </tr>
   <tr>
  	<td><?php echo _t('Blood Type') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['opt_blood_type']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['opt_blood_type']?></td>
  </tr>
  <tr>
  <td><b><?php echo _t('Other') ?></b></td>
  <td></td>
  <td></td>
  </tr>
   <tr>
  	<td><?php echo _t('Last Clothing') ?></td>
    <td><?php echo $_SESSION['dvr']['person1']['last_clothing']?></td>
    <td><?php echo $_SESSION['dvr']['person2']['last_clothing']?></td>
  </tr>
  
</table>
</DIV>
	
<?php
	shn_form_submit(_t("Delete Duplicate"));
	echo '<input type="button" value="Back" onClick="history.back()"/>';
	shn_form_fsclose();
	shn_form_fclose();
}
	

?>
<script language="JavaScript">

function confirmdelete(name)
{
return confirm('This person '+name+' will be permanently deleted');
}


</script>
