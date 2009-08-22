<?php
/**Admin controller of the Volunteer coordination System 
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

function _shn_vol_adm_sub_menu(){
?>
<div id="submenu_v">
<a href="index.php?mod=vol&act=adm_skills">Add Skills</a> 
<!--<a href="index.php?mod=or&act=adm_sector">Organization Sectors</a>
<a href="index.php?mod=or&act=adm_location_range">Set Location Range</a>
<a href="index.php?mod=or&act=adm_location">Set starting Location</a> -->
</div>

<br>
<?php
}
function shn_vol_adm_default()
{
    _shn_vol_adm_sub_menu();
?>
    <p><b> Welcome to the Volunteer Coordination admin page </b></p>
    <p> Use the Above Navigation to Administer</p>

    


<?php
}



function shn_vol_adm_skills()
{
    _shn_vol_adm_sub_menu();
    shn_vol_adm_skill_form();
}

function shn_vol_adm_skill_cr()
{
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    		$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="insert into field_options(field_name,option_code,option_description) values('opt_skill_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="delete from field_options where field_name='opt_skill_type' and option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
    	    $msg= "Skills were succesfully added ";
    add_confirmation($msg);
    shn_vol_adm_skills();
}

function shn_or_adm_sector()
{
    _shn_or_adm_sub_menu();
    shn_or_adm_or_sector_form();
}

function shn_or_adm_sector_cr(){
	
    global $global;
    include_once $global['approot'].'inc/lib_misc.inc';
    $db=$global['db'];
    $add = explode(",", $_POST{"added"});
    $remove = explode(",", $_POST{"removed"});
    for($i=1;$i<count($add)-1;$i++){
    		$key=shn_create_unique_database_field_value($add[$i],2,"field_options","option_code");
        $q="insert into field_options(field_name,option_code,option_description) values('opt_sector_type','$key','$add[$i]')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $q="delete from field_options where field_name='opt_sector_type' and option_code='".$remove[$i]."'";
        $res=$db->Execute($q);
    }
        	$msg= "Organization services were succesfully added/removed ";
     	add_confirmation($msg);
    shn_or_adm_sector();
}


