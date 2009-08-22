<?php
	global $global;	
	include_once ($global['approot'].'/inc/lib_security/lib_acl.inc');    
    $currentrole = _shn_acl_get_roles(shn_current_user());	
	
	foreach ($currentrole as $key => $val) {
		 $user = $val;
	}
	
	
if ($_SESSION['logged_in'] == true ){
		shn_mod_menuitem("ch_passwd",_t("Change Password"));
		if($user=='SRS User'){
			shn_mod_menuitem("srs_my_profile",_t("Edit SRS My Profile"));
			shn_mod_menuitem("city_lms",_t("Learning Management System"));	
		}
	
}
shn_mod_menuitem("ims_config",_t("Default Incident"));

