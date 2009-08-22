<?php
function shn_admin_ims_config()
{
    global $global;
    
    require($global['approot'].'mod/admin/ims_config.inc');
    
    print ("<h1><center>Disaster / Event / Incident Configuration</center></h1>");

	switch ($_POST['seq']) {
        case 'entry':
            if(_shn_ims_config_validate()) {
               _shn_ims_config_form(false,true); 
            }else {
                _shn_ims_config_form(true,false);
            }
        break;

        default:
            _shn_ims_config_form();
        break;
    }
}

function shn_admin_ims_level1()
{
    global $global;
    
    require($global['approot'].'mod/admin/ims_level.inc');
    
    print ("<h1><center>Manage Disaster</center></h1>");

	switch ($_POST['seq']) {
        case 'addnew':
        case 'update':
            if(_shn_ims_level1_validate()) {
               _shn_ims_level1_form(false,$type); 
            }else {
                _shn_ims_level1_form(true,$type);
            }
        break;

        default:
            _shn_ims_level1_form();
        break;
    }
}

function shn_admin_ims_level2()
{
    global $global;
    
    require($global['approot'].'mod/admin/ims_level.inc');

    print ("<h1><center>Manage Events</center></h1>");
    
	switch ($_POST['seq']) {
        case 'addnew':
        case 'update':
            if(_shn_ims_level2_validate()) {
               _shn_ims_level2_form(false,$type); 
            }else {
                _shn_ims_level2_form(true,$type);
            }
        break;

        default:
            _shn_ims_level2_form();
        break;
    }
}

function shn_admin_ims_level3()
{
    global $global;
    
    require($global['approot'].'mod/admin/ims_level.inc');

    print ("<h1><center>Manage Incidents</center></h1>");
    
	switch ($_POST['seq']) {
        case 'addnew':
        case 'update':
            if(_shn_ims_level3_validate()) {
               _shn_ims_level3_form(false,$type); 
            }else {
                _shn_ims_level3_form(true,$type);
            }
        break;

        default:
            _shn_ims_level3_form();
        break;
    }
}

function shn_admin_ims_assign()
{
    global $global;
    
    require($global['approot'].'mod/admin/ims_assign.inc');

	switch ($_POST['seq']) {
        case 'entry':
            if(_shn_ims_assign_validate()) {
               _shn_ims_assign_form(false,true); 
            }else {
                _shn_ims_assign_form(true,false);
            }
        break;
        
        case 'delete' :
            if(isset($_POST['ims_delete'])) {
                foreach($_POST['ims_delete'] as $k => $v) {
                    $v = trim($v);
                    $k = trim($k);
                    if($v != '')
                       $global['db']->Execute("DELETE FROM resource_to_incident WHERE x_uuid = '{$_REQUEST['id']}' AND incident_id = '$k' "); 
                }
            }
            _shn_ims_assign_form(true,false);
        break;

        default:
            _shn_ims_assign_form();
        break;
    } 
}

/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post 
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post)
{
    //trim them all
    foreach($_POST as $k => $v) {
        $v = trim($v);
        if($v != '')
            $local_post[$k] = $v;
    }
}
