<?php
include_once $global['approot'].'/inc/lib_form.inc';
function _shn_pref_config_form($errors=false,$updated=false)
{
    global $conf;
	global $global;
	$sql_level1 = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
	$sql_level2 = "SELECT  a.incident_id , a.name, a.parent_id FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id AND b.parent_id IS NULL";
	$sql_level3 = "SELECT a.incident_id, a.name, b.incident_id as parent_id FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id INNER JOIN incident c ON b.parent_id = c.incident_id AND c.parent_id IS NULL";
	$arr_level1 = $global['db']->GetAll($sql_level1);
	$arr_level2 = $global['db']->GetAll($sql_level2);
	$arr_level3 = $global['db']->GetAll($sql_level3);

    if($_POST['ims_level'] == 'level2' ){
        foreach($arr_level2 as $row){
            $arr[$row['incident_id']] = $row['name'];
        }
    }elseif($_POST['ims_level'] == 'level3' ){
        foreach($arr_level3 as $row){
            $arr[$row['incident_id']] = $row['name'];
        }
    }else{
        foreach($arr_level1 as $row){
            $arr[$row['incident_id']] = $row['name'];
        }
    }

    if($errors)
        display_errors();

    shn_form_fopen("ims",null);
    
    if($updated){
        shn_form_fsopen(_(""));
?><p align="center">Updated. </p>
<?php
        shn_form_fsclose();
    }
    
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_("Default Incident"));
    shn_form_select(array('level1'=>$conf['mod_admin_ims_level1'],
                            'level2'=>$conf['mod_admin_ims_level2'],
                            'level3'=>$conf['mod_admin_ims_level3']),_('Incident Type'),'ims_level','onChange="submit(this)"');
    shn_form_select($arr,_('Select Incident'),'ims_incident_id');
 
    shn_form_fsclose();
 
    shn_form_submit(_('Update'));
    shn_form_fclose(); 
}

function _shn_pref_config_validate()
{
    
    $error_flag=false;
    //clean the post
    shn_tools_clean_post(&$local_post);
    
    //anything entered?
    if(empty($local_post)){
        add_error(_("You have not completed the form"));
        return false;
    }

    if(! isset($local_post['ims_level'])){
        add_error(_("Please Select the incident type"));
        $error_flag=true;
    }

    if(! isset($local_post['ims_incident_id'])){
        add_error(_("Please an incident"));
        $error_flag=true;
    }

    if($error_flag)
        return false;
    else{
        shn_user_pref_update ('ims', 'incident_id',$local_post['ims_incident_id']);
        return true;
    }
}

?>
