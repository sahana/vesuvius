<?php

function _shn_ims_assign_form($errors=false,$type=false)
{
    global $conf;
	global $global;

    //Display Current
    if($errors)
        display_errors(); 

    $sql = "SELECT b.name, b.incident_id FROM resource_to_incident a INNER JOIN incident b USING (incident_id) WHERE a.x_uuid = '{$_REQUEST['id']}'";
    $arr = $global['db']->GetAll($sql);
    if(! empty($arr)) {
        shn_form_fopen("ims_assign",null);
        
        shn_form_hidden(array('seq'=>'delete'));
        shn_form_hidden(array('id'=>$_REQUEST['id']));
        shn_form_fsopen(_t('Currently Assign Incidents'));
?>
		<table>
		<thead>
    	<td width="100%"><strong><?php echo _t('Incident Name');?></strong></td>
    	<td width="100%"><strong><?php echo _t('Delete');?></strong></td>
		</thead>
<?php
		foreach($arr as $row) {
?>
			<tr>
    		<td><?php echo $row['name'];?>
    		</td>
    		<td><input type="checkbox" name="ims_delete[<?php echo $row['incident_id'];?>]" value="<?php echo $row['incident_id'];?>" />
    		</td>
			</tr>
<?php
		}
?>
		</table>
<?php
        shn_form_fsclose();
        shn_form_submit(_t('Delete'));
        shn_form_fclose();
    }


	$sql_level1 = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
	$sql_level2 = "SELECT  a.incident_id , a.name, a.parent_id, b.name as parent_name FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id AND b.parent_id IS NULL";
	$sql_level3 = "SELECT a.incident_id, a.name, b.incident_id as parent_id, b.name as parent_name,c.name as grand_parent_name FROM incident a INNER JOIN incident b  ON a.parent_id = b.incident_id INNER JOIN incident c ON b.parent_id = c.incident_id AND c.parent_id IS NULL";
	$arr_level1 = $global['db']->GetAll($sql_level1);
	$arr_level2 = $global['db']->GetAll($sql_level2);
	$arr_level3 = $global['db']->GetAll($sql_level3);

    $arr = null;
    if($_POST['ims_level'] == 'level2') {
        foreach($arr_level2 as $row) {
            $arr[$row['incident_id']] = $row['parent_name'].' --> '.$row['name'];
        }
    }elseif($_POST['ims_level'] == 'level3') {
        foreach($arr_level3 as $row) {
            $arr[$row['incident_id']] = $row['grand_parent_name'].' --> '.$row['parent_name'].' --> '.$row['name'];
        }
    }else{
        foreach($arr_level1 as $row) {
            $arr[$row['incident_id']] = $row['name'];
        }
    }

    if($errors)
        display_errors();

    shn_form_fopen("ims_assign",null);
    
    if($updated) {
        shn_form_fsopen(_t(""));
?>		<p align="center"><?php echo _t('Added.');?></p>
<?php
        shn_form_fsclose();
    }
    
    shn_form_hidden(array('id'=>$_REQUEST['id']));
    shn_form_fsopen(_t("Incident Type"));
    shn_form_hidden(array('seq'=>'change_type'));
    shn_form_select(array('level1'=>$conf['mod_admin_ims_level1'],
                            'level2'=>$conf['mod_admin_ims_level2'],
                            'level3'=>$conf['mod_admin_ims_level3']),_t('Incident Type'),'ims_level','onChange="submit(this)"');
    shn_form_fsclose();
    shn_form_fclose(); 

    shn_form_fopen("ims_assign",null);
    shn_form_fsopen(_t("New Incident"));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_hidden(array('id'=>$_REQUEST['id']));
    shn_form_select($arr,_t('Select Incident'),'ims_incident_id');
    shn_form_fsclose();
 
    shn_form_submit(_t('Add'));
    shn_form_fclose(); 
}


function _shn_ims_assign_validate()
{
    global $global;
    $error_flag=false;
    //clean the post
    shn_tools_clean_post(&$local_post);
    
    //anything entered?
    if(empty($local_post)) {
        add_error(_t("You have not completed the form"));
        return false;
    }

    if(! isset($local_post['id'])) {
        add_error(_t("Please specify the id"));
        $error_flag=true;
    }

    if(! isset($local_post['ims_incident_id'])) {
        add_error(_t("Please specify an incident"));
        $error_flag=true;
    }

    if($error_flag)
        return false;
    else{
        #shn_user_pref_update ('ims', 'incident_id',$local_post['ims_incident_id']);
        $sql = "INSERT INTO resource_to_incident (incident_id, x_uuid) VALUES ('{$local_post['ims_incident_id']}', '{$local_post['id']}')";
        $global['db']->Execute($sql);
        return true;
    }
}


