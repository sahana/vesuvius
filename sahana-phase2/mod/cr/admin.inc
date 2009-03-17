<?php
/* $Id: admin.inc,v 1.19 2009-03-17 06:08:24 ravithb Exp $ */

/**Admin Module for CR
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author   Chathra Hendehewa <chathra@opensource.lk>
 * @author   Mifan Careem <mifan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

include_once($global['approot'] . '/inc/lib_form.inc');

function _shn_cr_adm_sub_menu()
{
    ?>
<div id="submenu_v"><a href="index.php?mod=cr&act=adm_forms"><?php echo _t("Configure Form Display") ?></a>
</div>
<br>
    <?php
}

function shn_cr_adm_default()
{
    // _shn_cr_adm_sub_menu();
    global $conf;
    ?>
<h2><?php echo  $conf['mod_cr_name'] . _t(" Administration")?></h2>
    <?php
    shn_cr_adm_forms();
     
}
function shn_cr_adm_forms()
{
    _shn_cr_adm_sub_menu();
    _shn_cr_adm_form_change();
}

function _shn_cr_adm_form_change()
{
    global $global;
    /*
    shn_form_fopen(adm_form_setdivision);
    shn_form_fsopen("Select Division");
    shn_form_hidden(array('seq'=>'commit'));
    shn_form_opt_select("opt_location_type","Select Type to be displayed as Division for camps");
    shn_form_fsclose();
    shn_form_submit("Set Division");
    shn_form_fclose();
    */
    shn_form_fopen(adm_form_commit,null,array("req"=>false));
    shn_form_fsopen(_t("Add Service / Facility"));
    shn_form_opt_select("opt_camp_service",_t("Currently Available Services/Facilities"));
    echo "<br/>";
    shn_form_text(_t("Service Name"),"service_name",'size="30"');
    shn_form_text(_t("Service Abbrevation [3 letter unique abbr. to store in the database]"),"service_abbr",'size="3"');
    shn_form_fsclose();
    shn_form_submit(_t("Add Service"));
    shn_form_submit(_t('Delete Services'), 'name=delete');
    shn_form_fclose();
}

function shn_cr_adm_form_commit()
{

    global $global;
    $db = $global['db'];
    $db_flag = true;
    if(isset($_POST['delete'])){
		$sql = "DELETE FROM field_options WHERE field_name = 'opt_camp_service' AND option_code = '".$_POST['opt_camp_service']."'";
    	$res = $global['db']->Execute($sql);
    	if($res === false){
    		add_error(_t('Unable to delete the service'));
    	}
    	else{
    		add_confirmation(_t('Service deleted successfuly'));
    		$sql1 = "DELETE FROM camp_services WHERE opt_camp_service = '".$_POST['opt_camps_service']."'";
    		$res1 = $global['db']->Execute($sql1);
    		if($res1 === false){
    			add_error(_t('Unable to delete for assigned camp services'));
    		}    		
    		add_confirmation(_t('Service assigned in camps deleted successfuly'));
    	}
	}
	elseif(!empty($_POST['service_name'])){
		if(!empty($_POST['service_abbr'])){
			if(strlen($_POST['service_abbr'])==3){
				$q = "SELECT option_code FROM field_options";
				$res = $db->Execute($q);

				while(!$res->EOF){
    				$value = $res->fields["option_code"];
    				if($value==$_POST['service_abbr']){
    					add_error(_t("Abbrevation exist, please insert unique abbrevation"));
    					$db_flag = false;
    					break;
    				}
    				$res->MoveNext();
   	 			}
				if($db_flag){
					$q = "insert into field_options(field_name,option_code,option_description) values('opt_camp_service','{$_POST['service_abbr']}','{$_POST['service_name']}')";
					$res = $db->Execute($q);
					add_confirmation(_t("Added values"));
				}

			}
			else
			add_error(_t("Abbrevation should in 3 characters"));
		}
		else{
			//error: enter code
			add_error(_t("Please fill in empty values"));
		}
	}
	else{
		// do not store new services
		add_warning(_("Nothing to add"));
	}
    shn_cr_adm_default();
}

function shn_cr_adm_form_setdivision()
{
    global $global;
    $db = $global['db'];

    $q = "SELECT * FROM config WHERE confkey='division_type' AND module_id='cr'";
    $res=$db->Execute($q);

    if ($res->EOF) {
        //insert first time
        //echo "first time";
        $q = "INSERT INTO config(module_id,confkey,value) VALUES ('cr', 'division_type','{$_POST['opt_location_type']}')";

        $res = $db->Execute($q);
    } else {
        //do update
        $q = "UPDATE config SET value='{$_POST['opt_location_type']}' WHERE confkey='division_type' && module_id='cr'";
        $ref = $db->Execute($q);
    }
    shn_cr_adm_default();
}
?>

