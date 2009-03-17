<?php

/* $Id: edit_bed.inc,v 1.9 2009-03-17 06:08:24 ravithb Exp $ */
/* $Id: edit_bed.inc,v 1.9 2009-03-17 06:08:24 ravithb Exp $ */

/**Update functions for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera <isuru@opensource.lk>
*
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'] . '/inc/lib_form.inc');
include_once($global['approot'] . '/inc/lib_validate.inc');
include_once($global['approot'] . '/inc/lib_errors.inc');

global $editid;
function _shn_cr_cedt_start($errors = false) 
{
	if ($errors) {
		display_errors();
	}
	global $global;
	$db = $global['db'];
?>
<h2><?php echo _t("Update Existing Hospital Beds")?></h2>
<?php
	$query = "SELECT c_uuid FROM camp_general WHERE name='{$_REQUEST['cmp_id']}'";
	$res = $db->Execute($query);
	$editid = $res->fields['c_uuid'];
	$_SESSION['editid'] = $editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(ebed);
	shn_form_fsopen(_t("Hospital Details"));
	shn_form_hidden(array('seq'=>'chk'));
?>
<table>
<tr>
<td>
<?php	
    shn_form_text(_t("ICU Beds Used"),"icu_used",'size="5"',array('value'=>$_SESSION['camp_icu_used']));
?>
</td><td>

<?php
    shn_form_text(_t("ICU Beds Available"),"icu_available",'size="5"',array('value'=>$_SESSION['camp_icu_available']));
?>
</td>
</tr>

<tr>
<td>
<?php
    shn_form_text(_t("Medicine Beds Used"),"med_used",'size="5"',array('value'=>$_SESSION['camp_med_used']));
?>
</td><td>

<?php
    shn_form_text(_t("Medicine Beds Available"),"med_available",'size="5"',array('value'=>$_SESSION['camp_med_available']));
?>
</td>
</tr>


<tr>
<td>
<?php
    shn_form_text(_t("Surgery Beds Used"),"surg_used",'size="5"',array('value'=>$_SESSION['camp_surg_used']));
?>
</td><td>

<?php
    shn_form_text(_t("Surgery Beds Available"),"surg_available",'size="5"',array('value'=>$_SESSION['camp_surg_available']));
?>
</td>
</tr>

<tr>
<td>
<?php
    shn_form_text(_t("Paediatrics Beds Used"),"ped_used",'size="5"',array('value'=>$_SESSION['camp_ped_used']));
?>
</td><td>

<?php
    shn_form_text(_t("Paeddiatrics Beds Available"),"ped_available",'size="5"',array('value'=>$_SESSION['camp_ped_available']));
?>
</td>
</tr>
<tr>
<td>
<?php
    shn_form_text(_t("Obsterics Beds Used"),"obs_used",'size="5"',array('value'=>$_SESSION['camp_obs_used']));
?>
</td><td>

<?php
    shn_form_text(_t("Obsterics Beds Available"),"obs_available",'size="5"',array('value'=>$_SESSION['camp_obs_available']));
?>
</td>
</tr>






</table>
<?php
//shn_form_text(_t("Total Infected"),"infected_count",'size="5"',array('value'=>$_SESSION['camp_infected']));




    shn_form_submit("Update");
	shn_form_fsclose();
    shn_form_fclose();
}





function _shn_cr_cedt_chk($errors=false) 
{
    if ($errors) {
	    display_errors;
    }
	
	global $global;

    $_SESSION['camp_icu_used'] = $_POST['icu_used'];

    $_SESSION['camp_icu_available'] = $_POST['icu_available'];

	$_SESSION['camp_med_used'] = $_POST['med_used'];
	$_SESSION['camp_med_available'] = $_POST['med_available'];
	$_SESSION['camp_surg_used'] = $_POST['surg_used'];
	$_SESSION['camp_surg_available'] = $_POST['surg_available'];


    $_SESSION['camp_ped_used'] = $_POST['ped_used'];
    $_SESSION['camp_ped_available'] = $_POST['ped_available'];

    $_SESSION['camp_obs_used'] = $_POST['obs_used'];
    $_SESSION['camp_obs_available'] = $_POST['obs_available'];




}

function _shn_cr_validate_error()
{
	clean_errors();
	$error_flag = false;


if (!(null == ($_POST['icu_used']))) {
		if (!is_numeric(trim($_POST['icu_used']))) {
			add_error(_t("The ICU used count is not a valid number"));
			$error_flag = true;
		}
	}
if (!(null == ($_POST['icu_available']))) {
                if (!is_numeric(trim($_POST['icu_available']))) {
                        add_error(_t("The ICU available is not a valid number"));
                        $error_flag = true;
                }
        }

	if (!(null == ($_POST['med_used']))) {
		if (!is_numeric(trim($_POST['med_used']))) {
			add_error(_t("The medical beds used count is not a valid number"));
			$error_flag = true;
		}
	}
	if (!(null == ($_POST['med_availble']))) {
		if (!is_numeric(trim($_POST['women']))) {
			add_error(_t("The medical beds availble count is not a valid number"));
			$error_flag = true;
		}
	}
	if (!(null == ($_POST['surg_used']))) {
		if (!is_numeric(trim($_POST['surg_used']))) {
			add_error(_t("The surgery beds used count is not a valid number"));
			$error_flag = true;
		}
	}
	
    if (!(null == ($_POST['surg_availble']))) {
                if (!is_numeric(trim($_POST['surg_available']))) {
                        add_error(_t("The surgery beds available count is not a valid number"));
                        $error_flag = true;
                }
        }
        if (!(null == ($_POST['ped_used']))) {
                if (!is_numeric(trim($_POST['ped_used']))) {
                        add_error(_t("The piadertics used bed count is not a valid number"));
                        $error_flag = true;
                }
        }


 if (!(null == ($_POST['ped_available']))) {
                if (!is_numeric(trim($_POST['ped_available']))) {
                        add_error(_t("The piadertics available bed count is not a valid number"));
                        $error_flag = true;
                }
        }


if (!(null == ($_POST['obs_used']))) {
                if (!is_numeric(trim($_POST['obs_used']))) {
                        add_error(_t("The obsterics used bed count is not a valid number"));
                        $error_flag = true;
                }
        }


 if (!(null == ($_POST['obs_available']))) {
                if (!is_numeric(trim($_POST['obs_available']))) {
                        add_error(_t("The obsterics available bed count is not a valid number"));
                        $error_flag = true;
                }
        }






	
	return $error_flag;
}


/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
*/

function _shn_cr_get_session($camp_id)
{
	global $global;
	$db = $global['db'];
	
    $query="SELECT * FROM hospital_beds WHERE c_uuid='{$camp_id}'";
	
	$res = $db->Execute($query);








    $_SESSION['camp_icu_used'] = $res->fields['icu_used'];
	$_SESSION['camp_icu_available'] = $res->fields['icu'];
	$_SESSION['camp_med_used'] = $res->fields['med_used'];
	$_SESSION['camp_med_available'] = $res->fields['med'];
	$_SESSION['camp_surg_used'] = $res->fields['surg_used'];
    $_SESSION['camp_surg_available'] = $res->fields['surg'];
    $_SESSION['camp_ped_used'] = $res->fields['paed_used'];
    $_SESSION['camp_ped_available'] = $res->fields['paed'];

    $_SESSION['camp_obs_used'] = $res->fields['obs_used'];
    $_SESSION['camp_obs_available'] = $res->fields['obs'];




											
}


function _shn_cr_cedt_commit()
{
    //insert to database;
    global $global;
	global $editid;
	$db = $global['db'];




	$q="UPDATE hospital_beds SET icu='{$_SESSION['camp_icu_available']}',med='{$_SESSION['camp_med_available']}',surg
	='{$_SESSION['camp_surg_available']}',paed='{$_SESSION['camp_ped_available']}',obs='{$_SESSION['camp_obs_available']}',icu_used='{$_SESSION['camp_icu_used']}',med_used='{$_SESSION['camp_med_used']}',surg_used='{$_SESSION['camp_surg_used']}',paed_used='{$_SESSION['camp_ped_used']}',obs_used='{$_SESSION['camp_obs_used']}'  where c_uuid='{$_SESSION['editid']}'";


	//print $_SESSION['camp_icu_available'];

	//$q="update hospital_beds set icu='{$_SESSION['camp_icu_available']}'   where c_uuid='{$_SESSION['editid']}'";

	$res = $db->Execute($q);

//$q="update camp_reg set men='{$_SESSION['camp_men']}'  where c_uuid='{$_SESSION['editid']}'";


//$res = $db->Execute($q);
?>

<h2><?php  add_confirmation(_t("You have succesfully edited the bed count ").$_SESSION['camp_name']); ?></h2>


</tbody>
</table>
</div>

</ul>
<br><br>
<p><?php echo _t("Use the navigation menu to continue")?></p>
<?php	
}

?>

