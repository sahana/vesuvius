<?php
function _shn_ims_config_form($errors=false,$updated=false)
{
    global $conf;
    if($errors)
        display_errors();   
    shn_form_fopen("ims_config",null);
    if($updated) {
        shn_form_fsopen(_t(""));
?>		<p align="center">Updated. <a href="<?php echo  $_SERVER['PHPSELF'];?>">Click to see the menu change</a></p>
<?php
        shn_form_fsclose();
    }
    
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_t("Activate/Deactivate"));
    if($conf['mod_admin_ims_active'] == true)
        $extra_opt['value']= true;
        $extra_opt['help'] = _t('This will activate / deactivate incident management and the incident hierarchy.');
    shn_form_checkbox(_t("Activate"), 'frm_active',null,$extra_opt);
    shn_form_fsclose();

    echo "<br /><br /><br />";
    shn_form_fsopen(_t("Grouping"));
    shn_form_text(_t("Level1"), "mod_admin_ims_level1", 'class="smoothinput"', array('value'=>$conf['mod_admin_ims_level1'],'req'=>true));
    shn_form_text(_t("Level2"), "mod_admin_ims_level2", 'class="smoothinput"', array('value'=>$conf['mod_admin_ims_level2'],'req'=>true));
    shn_form_text(_t("Level3"), "mod_admin_ims_level3", 'class="smoothinput"', array('value'=>$conf['mod_admin_ims_level3'],'req'=>true));
    shn_form_fsclose();
 
    shn_form_submit(_t('Update'));
    shn_form_fclose(); 
}

function _shn_ims_config_validate()
{
    $error_flag=false;
    //clean the post
    shn_tools_clean_post(&$local_post);
    
    //anything entered?
    if(empty($local_post)) {
        add_error(_t("You have not completed the form"));
        return false;
    }

    if(! isset($local_post['mod_admin_ims_level1'])) {
        add_error(_t("Please enter the name for Level1"));
        $error_flag=true;
    }

    if(! isset($local_post['mod_admin_ims_level2'])) {
        add_error(_t("Please enter the name for Level2"));
        $error_flag=true;
    }

    if(! isset($local_post['mod_admin_ims_level3'])) {
        add_error(_t("Please enter the name for Level3"));
        $error_flag=true;
    }

    if($error_flag)
        return false;
    else {
        shn_db_config_update('admin','ims_level1',$local_post['mod_admin_ims_level1']);
        shn_db_config_update('admin','ims_level2',$local_post['mod_admin_ims_level2']);
        shn_db_config_update('admin','ims_level3',$local_post['mod_admin_ims_level3']);
        return true;
    }
}

