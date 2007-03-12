<?php
/* $Id: edit_bed.inc,v 1.3 2007-03-12 18:29:18 mifanc Exp $ */

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

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

global $editid;
function _shn_cr_cedt_start($errors=false){
	if($errors)
		display_errors();
	global $global;
	$db = $global['db'];
?>
<h2><?php echo _("Update Existing Hospital Beds")?></h2>
<?php
	$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields['c_uuid'];
	$_SESSION['editid']=$editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(ebed);
	shn_form_fsopen(_("Hospital Details"));
	shn_form_hidden(array('seq'=>'chk'));
?>
<table>
<tr>
<td>
<?php	
shn_form_text(_("ICU Beds Used"),"icu_used",'size="5"',array('value'=>$_SESSION['camp_icu_used']));
?>
</td><td>

<?php
shn_form_text(_("ICU Beds Available"),"icu_available",'size="5"',array('value'=>$_SESSION['camp_icu_available']));
?>
</td>
</tr>

<tr>
<td>
<?php
shn_form_text(_("Medicine Beds Used"),"med_used",'size="5"',array('value'=>$_SESSION['camp_med_used']));
?>
</td><td>

<?php
shn_form_text(_("Medicine Beds Available"),"med_available",'size="5"',array('value'=>$_SESSION['camp_med_available']));
?>
</td>
</tr>


<tr>
<td>
<?php
shn_form_text(_("Surgery Beds Used"),"surg_used",'size="5"',array('value'=>$_SESSION['camp_surg_used']));
?>
</td><td>

<?php
shn_form_text(_("Surgery Beds Available"),"surg_available",'size="5"',array('value'=>$_SESSION['camp_surg_available']));
?>
</td>
</tr>

<tr>
<td>
<?php
shn_form_text(_("Paediatrics Beds Used"),"ped_used",'size="5"',array('value'=>$_SESSION['camp_ped_used']));
?>
</td><td>

<?php
shn_form_text(_("Paeddiatrics Beds Available"),"ped_available",'size="5"',array('value'=>$_SESSION['camp_ped_available']));
?>
</td>
</tr>
<tr>
<td>
<?php
shn_form_text(_("Obsterics Beds Used"),"obs_used",'size="5"',array('value'=>$_SESSION['camp_obs_used']));
?>
</td><td>

<?php
shn_form_text(_("Obsterics Beds Available"),"obs_available",'size="5"',array('value'=>$_SESSION['camp_obs_available']));
?>
</td>
</tr>






</table>
<?php
//shn_form_text(_("Total Infected"),"infected_count",'size="5"',array('value'=>$_SESSION['camp_infected']));




shn_form_submit("Update");
	shn_form_fsclose();
shn_form_fclose();
}





function _shn_cr_cedt_chk($errors=false){
if($errors)
	display_errors;
	
	global $global;

$_SESSION['camp_icu_used']=$_POST['icu_used'];

 $_SESSION['camp_icu_available']=$_POST['icu_available'];

	$_SESSION['camp_med_used']=$_POST['med_used'];
	$_SESSION['camp_med_available']=$_POST['med_available'];
	$_SESSION['camp_surg_used']=$_POST['surg_used'];
	$_SESSION['camp_surg_available']=$_POST['surg_available'];


  $_SESSION['camp_ped_used']=$_POST['ped_used'];
        $_SESSION['camp_ped_available']=$_POST['ped_available'];

  $_SESSION['camp_obs_used']=$_POST['obs_used'];
        $_SESSION['camp_obs_available']=$_POST['obs_available'];




}

function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


if(!(null == ($_POST['icu_used']))){
		if(!is_numeric(trim($_POST['icu_used']))){
			add_error(_("The ICU Used Count is not a valid number"));
			$error_flag=true;
		}
	}
if(!(null == ($_POST['icu_available']))){
                if(!is_numeric(trim($_POST['icu_available']))){
                        add_error(_("The ICU available is not a valid number"));
                        $error_flag=true;
                }
        }

	if(!(null == ($_POST['med_used']))){
		if(!is_numeric(trim($_POST['med_used']))){
			add_error(_("The Medical Beds Used Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['med_availble']))){
		if(!is_numeric(trim($_POST['women']))){
			add_error(_("The Medical Beds Availble Count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['surg_used']))){
		if(!is_numeric(trim($_POST['surg_used']))){
			add_error(_("The Surgery Beds Used Count is not a valid number"));
			$error_flag=true;
		}
	}
	
    if(!(null == ($_POST['surg_availble']))){
                if(!is_numeric(trim($_POST['surg_available']))){
                        add_error(_("The Surgery Beds Available Count is not a valid number"));
                        $error_flag=true;
                }
        }
        if(!(null == ($_POST['ped_used']))){
                if(!is_numeric(trim($_POST['ped_used']))){
                        add_error(_("The Piadertics Used Bed Count is not a valid number"));
                        $error_flag=true;
                }
        }


 if(!(null == ($_POST['ped_available']))){
                if(!is_numeric(trim($_POST['ped_available']))){
                        add_error(_("The Piadertics Available Bed Count is not a valid number"));
                        $error_flag=true;
                }
        }


if(!(null == ($_POST['obs_used']))){
                if(!is_numeric(trim($_POST['obs_used']))){
                        add_error(_("The Obsterics Used Bed Count is not a valid number"));
                        $error_flag=true;
                }
        }


 if(!(null == ($_POST['obs_available']))){
                if(!is_numeric(trim($_POST['obs_available']))){
                        add_error(_("The Obsterics Available Bed Count is not a valid number"));
                        $error_flag=true;
                }
        }






	
	return $error_flag;
}


/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
*/

function _shn_cr_get_session($camp_id){
	global $global;
	$db = $global['db'];
	
$query="select * from hospital_beds  where c_uuid='{$camp_id}'";
	
	$res = $db->Execute($query);








$_SESSION['camp_icu_used']=$res->fields['icu_used'];
	$_SESSION['camp_icu_available']=$res->fields['icu'];
	$_SESSION['camp_med_used']=$res->fields['med_used'];
	$_SESSION['camp_med_available']=$res->fields['med'];
	$_SESSION['camp_surg_used']=$res->fields['surg_used'];
        $_SESSION['camp_surg_available']=$res->fields['surg'];
 $_SESSION['camp_ped_used']=$res->fields['paed_used'];
        $_SESSION['camp_ped_available']=$res->fields['paed'];

 $_SESSION['camp_obs_used']=$res->fields['obs_used'];
        $_SESSION['camp_obs_available']=$res->fields['obs'];




											
}


function _shn_cr_cedt_commit(){
//insert to database;
global $global;
global $editid;
$db = $global['db'];




$q="update hospital_beds set icu='{$_SESSION['camp_icu_available']}',med='{$_SESSION['camp_med_available']}',surg
='{$_SESSION['camp_surg_available']}',paed='{$_SESSION['camp_ped_available']}',obs='{$_SESSION['camp_obs_available']}',icu_used='{$_SESSION['camp_icu_used']}',med_used='{$_SESSION['camp_med_used']}',surg_used='{$_SESSION['camp_surg_used']}',paed_used='{$_SESSION['camp_ped_used']}',obs_used='{$_SESSION['camp_obs_used']}'  where c_uuid='{$_SESSION['editid']}'";


//print $_SESSION['camp_icu_available'];

//$q="update hospital_beds set icu='{$_SESSION['camp_icu_available']}'   where c_uuid='{$_SESSION['editid']}'";




$res = $db->Execute($q);





//$q="update camp_reg set men='{$_SESSION['camp_men']}'  where c_uuid='{$_SESSION['editid']}'";


//$res = $db->Execute($q);
?>

<?  add_confirmation(_("You Have Succesfully Edited the Bed Count {$_SESSION[camp_name]}")); ?></h2>


</tbody>
</table>
</div>

</ul>
<br><br>
<p><?php echo _("Use the Navigation Menu to Continue")?></p>
<?php	
}

?>

