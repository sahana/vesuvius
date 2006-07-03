<?php
include_once $global['approot']."/mod/pref/ims_config.inc";
function shn_pref_ims_config()
{
	switch ($_POST['seq']) {
        case 'entry':
            if(_shn_pref_config_validate()){
               _shn_pref_config_form(false,true); 
            }else{
                _shn_pref_config_form(true,false);
            }
        break;

        default:
            _shn_pref_config_form();
        break;
    }
}

function shn_pref_ims_set_incident()
{
	$incident_id = addslashes(strip_tags(trim($_REQUEST['incident_id'])));	
   	shn_user_pref_update ('ims', 'incident_id',$incident_id);
}
?>
