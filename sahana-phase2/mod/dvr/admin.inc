<?php

/**
 * DVR Administrative Section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dvr
 * @subpackage  dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * dvr 
 * 
 * @access public
 * @return void
 */
function shn_dvr_adm_default() {
?>
<p><b>
<?php echo _t("Welcome to the Disaster Victim Registry admin page");?> </b></p>
    <p>
    <?php
   shn_dvr_adminmenu();
   ?>
   <br/>
     <p><b> <?php echo _t("Welcome to the DVR administration  page")?> </b></p>
     
    <p> <?php echo _t("Follow above links to administer the disaster victim registry")?></p>
<?php
}


function shn_dvr_adminmenu() {
	global $global;
	$module = $global['module'];
	// Create the module menuj
	shn_adm_menuopen(_t("Disaster Victim Registry"));
 	shn_adm_menuitem("adm_checklist", _t("Manage Checklist"));

	//shn_adm_menuitem("adm_opt_age_group", _t("Manage Groups"));
	shn_adm_menuclose();

}


function shn_dvr_adm_checklist()
{
    global $global;
    shn_dvr_adminmenu();
    shn_form_fopen("adm_checklist",null,array("req"=>false));
    shn_form_fsopen(_t("Currently Available Services/Facilities"));
    ?>	   <table> 
	    <thead>
    <td><strong><?php echo _t('Code');?></strong></td>
    <td width="100%"><strong><?php echo _t('Description');?></strong></td>
    <td width="100%"><strong><?php echo _t('Delete');?></strong></td>
    </thead>
    <?php
 $button = $_POST['selection'];
    if ($button == 'Update') {
		$count=0;
		while ($_POST[$_SESSION['option_code'.$count]] != null) {
    		$code = $_POST[$_SESSION['option_code'.$count]];
    	    $desc = $_POST[$_SESSION['option_description'.$count]];
    		$todelete = $_POST[$count];
    		
            if($todelete=='on') { 
    	        _shn_dvr_delete_option($code);
            } elseif ($_POST[$_SESSION['option_description'.$count]] == null) {
                add_error(_t("Description should not be empty."));
            } elseif ($_POST[$_SESSION['option_description'.$count]] != $_SESSION['option_description'.$count]) {
                _shn_dvr_update_option($code,$desc);
                add_confirmation(_t($_SESSION['option_description'.$count].' changed to '.$_POST[$_SESSION['option_description'.$count]].'.'));
    	    }
		$count++;	
		}
    }	    
	elseif ($button == 'Add Item') {
	    _shn_dvr_adm_form_commit();
	}  

    $sql = "SELECT field_name, option_code, option_description FROM field_options WHERE field_name = 'opt_dvr_service'";
	$sel = $global['db']->GetAll($sql);
    $result = array();
    $count=0;
    foreach ($sel as $row) {
        $_SESSION['option_code'.$count] = $row['option_code'];
        //$_SESSION[$count]['field_name'] = $row['field_name'];
        $_SESSION['option_description'.$count] = $row['option_description'];
        ?>
<tr>
    <td><input type="text" READONLY name="<?php echo $_SESSION['option_code'.$count];?>" 
            value="<?php echo $_SESSION['option_code'.$count];?>"  />
    </td>
    <td><input type="text" name="<?php echo $_SESSION['option_description'.$count];?>" 
            value="<?php echo $_SESSION['option_description'.$count];?>" />
    </td>
    <td><input type="checkbox" name="<?php echo $count;?>" />
    </td>
    <?php 
    $count++;
    } ?>
</tr>
</table>
<br></br>
<?php
    shn_form_submit(_t("Update"), "name = 'selection'");
    shn_form_fsclose();
    shn_form_fsopen(_t("Add Service / Facility"));
        
?>
<table>
	<tr>
	<td>
	<?php
	$extra_opts['req'] = true;	
	shn_form_text(_t("Item Name"),"service_name",'size="30"',$extra_opts);
	?>
	</td></tr>
	<tr><td>
	<?php
	
		
	shn_form_text(_t("Item Abbrevation [3 letter unique abbr. to store in the database]"),"service_abbr",'size="3" maxlength="3"',$extra_opts);
	?>
	</td></tr>
	</table>
	<?php
	
	shn_form_fsclose();
	shn_form_submit(_t("Add Item"), "name ='selection'");
	shn_form_fclose();
} 



function _shn_dvr_adm_form_commit()
{
	
    global $global;
	$db = $global['db'];
	
	if(!empty($_POST['service_name']))
	{
		if(!empty($_POST['service_abbr']))
		{
			$q1 = "SELECT * FROM field_options WHERE option_description='{$_POST['service_name']}'";
				$res1 = $db->Execute($q1);
				
				$q2 = "SELECT * FROM field_options WHERE option_code='{$_POST['service_abbr']}'";
				$res2 = $db->Execute($q2);
				if (1 <= $res1->RecordCount()) {
				    add_error(_t("Item already exists"));
				} elseif (1 <= $res2->RecordCount()) {
				    add_error(_t("Use different abbrevation."));
				} else {
				    $q = "INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_dvr_service','{$_POST['service_abbr']}','{$_POST['service_name']}')";
				    $res = $db->Execute($q);
				    $_POST['service_abbr']=null;
				    $_POST['service_name']=null;
			    }
				
		    } else {
		        add_error(_t("Please fill the abbrevation."));
		    }
	
	} else {
	add_error(_t("Please fill the service."));
	}
}

function _shn_dvr_delete_option($code)
{
    global $global;
	$sql= "DELETE FROM field_options WHERE option_code='$code'";
    $global['db']->Execute($sql);
    add_confirmation(_t('Service / Facility was removed successfully.'));
}

function _shn_dvr_update_option($optioncode, $optiondescription)
{
    global $global;	
    $sql="UPDATE field_options SET option_description='{$optiondescription}' WHERE option_code='{$optioncode}'";
    $global['db']->Execute($sql);
}
?>



