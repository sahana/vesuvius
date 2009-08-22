<?php
/**Admin controller of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once "admin_forms.inc";

function _shn_or_adm_sub_menu()
{
// This submenu appears in Administration > Module Configuration > Organization Registry
?>
<div id="submenu_v">
    <a href="index.php?mod=or&act=adm_or_type">
	<?php echo _t("Organization Types")?>
    </a> 
    <a href="index.php?mod=or&act=adm_sector"><?php echo _t("Organization Sectors")?></a>
<!--<a href="index.php?mod=or&act=adm_location_range">Set Location Range</a>
<a href="index.php?mod=or&act=adm_location">Set starting Location</a> -->
</div>

<br />
<?php
}
function shn_or_adm_default()
{
    _shn_or_adm_sub_menu();
?>
    <h2>
	<?php echo _t("Organisation Registry Configuration.")?>
    </h2>
    <br />
    
    <p>
	<?php echo _t("Use the following links or the above tabs to chage organization types and sectors.") ?>
    </p>

    <ul>
        <li>
	    <b>
		<a href="index.php?mod=or&act=adm_or_type">
		    <?php echo _t("Organization Types") ?>
		</a>
	    </b>
	    <br /> - <?php echo _t("Change the types of organizations, (add new, edit or delete)") ?>
	</li>
	<br />
        
	<li>
	    <b>
		<a href="index.php?mod=or&act=adm_sector">
		    <?php echo _t("Organization Sectors") ?>
		</a>
	    </b>
	    <br /> - <?php echo _t("Change the organization sectors, (add new, edit or delete)")?>
	</li>
	<br />
    </ul>

<?php
}



function shn_or_adm_or_type()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_type_form();
}

function shn_or_adm_type_cr()
{
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    	$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_org_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="DELETE FROM field_options WHERE field_name='opt_org_type' AND option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
    $msg= "Organization types were succesfully added/removed ";
    add_confirmation($msg);
    shn_or_adm_or_type();
}

function shn_or_adm_sector()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_sector_form();
}

function shn_or_adm_sector_cr()
{
	
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    	$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="INSERT INTO field_options(field_name,option_code,option_description) VALUES('opt_sector_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="DELETE FROM field_options WHERE field_name='opt_sector_type' AND option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
        	$msg= _t("Organization services were succesfully added/removed ");
     	add_confirmation($msg);
    shn_or_adm_sector();
}


