<?php

/**
 * DSM Administrative Section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dsm
 * @subpackage  dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * dsm 
 * 
 * @access public
 * @return void
 */
function shn_dsm_adm_default() {
?>
<p><b>
<?php echo _t("Welcome to the Disease Surviellance System admin page");?> </b></p>
    <p>
    <?php
   shn_dsm_adminmenu();
   ?>
   <br/>
     <p><b> <?php echo _t("Welcome to the DSM administration  page")?> </b></p>
     
    <p> <?php echo _t("Follow above links to administer the Disease Surviellance System")?></p>
<?php
}


function shn_dsm_adminmenu() {
	global $global;
	$module = $global['module'];
	// Create the module menuj
	shn_adm_menuopen(_t("Disease Surveillance System"));
 	shn_adm_menuitem("adm_dri_water", _t("Drinking Water Supply"));
 	shn_adm_menuitem("adm_age_groups", _t("Age Groups"));
 	shn_adm_menuitem("adm_nutrition_level", _t("Nutrition Level"));
 	shn_adm_menuitem("adm_sanitary", _t("Sanitary"));
 	shn_adm_menuitem("adm_seasons", _t("Seasons"));
 	//shn_adm_menuitem("adm_", _t(""));
 	//shn_adm_menuitem("adm_age_groups", _t("Age Groups"));

	//shn_adm_menuitem("adm_opt_age_group", _t("Manage Groups"));
	shn_adm_menuclose();

}


function shn_dsm_adm_dri_water()
{
    global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Drinking Water"); ?></h2>
<?php

	_shn_dsm_adm_field_options_controller('dri_water');
}

function shn_dsm_adm_age_groups()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Age Groups"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('age_groups');
}

function shn_dsm_adm_nutrition_level()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Nutrition Levels"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('nutrition_level');
}

function shn_dsm_adm_sanitary()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Sanitary"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('sanitary');
}

function shn_dsm_adm_seasons()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Seasons"); ?></h2>
<?php

	_shn_dsm_adm_field_options_controller('seasons');
}

function _shn_dsm_adm_field_options_controller($type)
{
	global $global;
    shn_form_fopen('adm_' . $type,null,array("req"=>false));
    shn_form_fsopen(_t("Update"));
    ?>	   <table> 
	    <thead>
    <td><strong><?=_t('Code');?></strong></td>
    <td width="100%"><strong><?=_t('Description');?></strong></td>
    <td width="100%"><strong><?=_t('Delete');?></strong></td>
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
    	        _shn_dsm_delete_option($code);
            } elseif ($_POST[$_SESSION['option_description'.$count]] == null) {
                add_error(_t("Description should not be empty."));
            } elseif ($_POST[$_SESSION['option_description'.$count]] != $_SESSION['option_description'.$count]) {
                _shn_dsm_update_option($code,$desc);
                add_confirmation(_t($_SESSION['option_description'.$count].' changed to '.$_POST[$_SESSION['option_description'.$count]].'.'));
    	    }
		$count++;	
		}
    }	    
	elseif ($button == 'Add Item') {
	    _shn_dsm_adm_form_commit($type);
	}  

    $sql = "SELECT field_name, option_code, option_description FROM field_options WHERE field_name = '{$type}'";
	$sel = $global['db']->GetAll($sql);
    $result = array();
    $count=0;
    foreach ($sel as $row) {
        $_SESSION['option_code'.$count] = $row['option_code'];
        //$_SESSION[$count]['field_name'] = $row['field_name'];
        $_SESSION['option_description'.$count] = $row['option_description'];
        ?>
<tr>
    <td><input type="text" READONLY name="<?=$_SESSION['option_code'.$count];?>" 
            value="<?=$_SESSION['option_code'.$count];?>"  />
    </td>
    <td><input type="text" name="<?=$_SESSION['option_description'.$count];?>" 
            value="<?=$_SESSION['option_description'.$count];?>" />
    </td>
    <td><input type="checkbox" name="<?=$count;?>" />
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
    shn_form_fsopen(_t("Add New"));   
?>
<table>
	<tr>
	<td>
	<?php
	$extra_opts['req'] = true;	
	shn_form_text(_t("Description"),"service_name",'size="30"',$extra_opts);
	?>
	</td></tr>
	<tr><td>
	<?php
	
		
	shn_form_text(_t("Abbrevation [3 letter unique abbr. to store in the database]"),"service_abbr",'size="3" maxlength="3"',$extra_opts);
	?>
	</td></tr>
	</table>
	<?php
	
	shn_form_fsclose();
	shn_form_submit(_t("Add Item"), "name ='selection'");
	shn_form_fclose();
} 



function _shn_dsm_adm_form_commit($type)
{
	
    global $global;
	$db = $global['db'];
	
	if(!empty($_POST['service_name']))
	{
		if(!empty($_POST['service_abbr']))
		{
			$q1 = "SELECT * FROM field_options WHERE option_description='{$_POST['service_name']}' AND field_name='{$_type}'";
				$res1 = $db->Execute($q1);
				
				$q2 = "SELECT * FROM field_options WHERE option_code='{$_POST['service_abbr']}'";
				$res2 = $db->Execute($q2);
				if (1 <= $res1->RecordCount()) {
				    add_error(_t("Item already exists"));
				} elseif (1 <= $res2->RecordCount()) {
				    add_error(_t("Use different abbrevation."));
				} else {
				    $q = "INSERT INTO field_options(field_name,option_code,option_description) VALUES('{$type}','{$_POST['service_abbr']}','{$_POST['service_name']}')";
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

function _shn_dsm_delete_option($code)
{
    global $global;
	$sql= "DELETE FROM field_options WHERE option_code='$code'";
    $global['db']->Execute($sql);
    add_confirmation(_t('Service / Facility was removed successfully.'));
}

function _shn_dsm_update_option($optioncode, $optiondescription)
{
    global $global;	
    $sql="UPDATE field_options SET option_description='{$optiondescription}' WHERE option_code='{$optioncode}'";
    $global['db']->Execute($sql);
}
?>



