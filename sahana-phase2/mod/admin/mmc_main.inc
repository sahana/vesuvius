<?php
function shn_admin_mmc_default()
{
    //|--mod prefix--|--Modules--|--Version--|--Author--|
?>
	<h2>Installed Modules</h2>
	<div id="result">
	<table>
	<thead>
    	<td><?php echo _t('Module Prefix');?></td>
    	<td><?php echo _t('Module Name');?></td>
    	<td><?php echo _t('Version');?></td>
    	<td><?php echo _t('Author');?></td>
	</thead>
<?php
    foreach(shn_get_module_names() as $module) {
        echo "<tr>";
        echo "<td>".$module."</td>";
        echo "<td>".shn_get_module_name($module)."</td>";
        echo "<td>".shn_db_get_config($module,'version')."</td>";
        echo "<td>".shn_db_get_config($module,'authors')."</td>";
        echo "</tr>";
    }
?>
	</table>
	</div>
<?php  
}

function shn_admin_mmc_add()
{
    switch($_REQUEST['seq']) {
        case 'upload':
            if(! _shn_admin_mmc_upload_form_validate()) {
                _shn_admin_mmc_upload_form(true);
            }
        	break;

        case 'commit':
            _shn_admin_mmc_upload_commit();
        	break;

        default :
            $_SESSION['admin']['mmc'] = null;
            if(_shn_admin_mmc_check_system())
                _shn_admin_mmc_upload_form();
            else
                display_errors();
        	break;
    }
}


function _shn_admin_mmc_check_system()
{
    global $global;
    //check www/tmp is writable or not 
    if(!is_writeable($global['approot'].'/www/tmp')) {
        add_error(_t(" www/tmp path is not writeable. Please make it writeable."));
    }

    //check mod is writable 
    if(!is_writeable($global['approot'].'/mod')) {
        add_error(_t("Modules directory is not writeable. Please make it writeable."));
    }

    //check backup location is writeable
    if(!is_writeable($global['approot'].'/backup')) {
        add_error(_t("Backup directory is not writeable. Please make it writeable."));
    }

    if(is_errors())
        return false;
    else
        return true;

}

function _shn_admin_mmc_upload_form($errors=false)
{
   if($errors)
        display_errors(); 

    shn_form_fopen("mmc_add",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_hidden(array('seq'=>'upload'));
    shn_form_fsopen(_t('Upload module Zip file'));
    shn_form_upload(_t('Zip File'),"zip_file");
    shn_form_fsclose();
    shn_form_submit(_t('Upload'));
    shn_form_fclose();
    
}

function _shn_admin_mmc_upload_form_validate()
{
    global $global;
    require_once($global['approot'].'/3rd/pclzip/pclzip.lib.php');
    
    if($_FILES['zip_file']['error']==UPLOAD_ERR_NO_FILE) {
        add_error(_t("Please upload the module file"));
        return false;
    }

    if($_FILES['zip_file']['error'] != 0) {
        add_error(_t("There was an error on uploading please try again."));
        return false;
    }

    if(! preg_match('/zip/',$_FILES['zip_file']['type'])) {
        add_error(_t("The uploaded file is not a valid zip file"));
        return false;
    }

    //unzip on tmp location
    if(! $tmp_dir = _shn_admin_mmc_create_tmp_dir()) {
        return false;
    }

    if(! move_uploaded_file($_FILES['zip_file']['tmp_name'], $tmp_dir.$_FILES['zip_file']['name'])) {
        add_error(_t("Couldn't move the uploaded file."));
        if(! shn_tools_rmdir_rf($tmp_dir))
            add_error(_t("Couldn't delete the tmp directory, it's not harmful although you may want to clean it mannually to gain more disk speace")); 
        return false;
    }

    //try unziping the files
    if(! $module_info = _shn_admin_mmc_unzip_and_check($tmp_dir, $tmp_dir.$_FILES['zip_file']['name']) ) {
        return false;     
    }

    //check depenencies
    $func = "shn_{$module_info['mod_prefix']}_depens";
    if(function_exists($func)) {
        $dependencies = $func();
        foreach($dependencies as $dep_mod) {
            if(!shn_module_exists($dep_mod)) {
                $not_found[$dep_mod] = true; //should be nice name
            }
        }
    }   
    //if not found dependencies
    if($not_found) {
        add_error(_t("You can not install/upgrade this module due to the following dependent modules are missing"));
        foreach($not_found as $not_found => $nice_name) {
            add_error($not_found);
        }
        return false;
    }

    $_SESSION['admin']['mmc']['tmp_dir'] = $tmp_dir;
    $_SESSION['admin']['mmc']['module_info'] = $module_info;

    //check module exists or not
    if(shn_module_exists($module_info['mod_prefix'])) {
        //if same version don't upgrade
        $cur_version = shn_db_get_config($module_info['mod_prefix'],'version');
        if($cur_version == $module_info['version']) {
            add_error(_t("The module you uploaded is the same version of what is already installed."));
            return false;
        }
        //ugrade
        $_SESSION['admin']['mmc']['type'] = 'upgrade';
        $func = "shn_{$module_info['mod_prefix']}_upgrade_page";
        //if the shn_<mod>_upgade_page() exists call that 
        if($module_info['setup.inc'] && function_exists($func)) {
            $func();
        }else {
            shn_form_fopen("mmc_add",null);
            shn_form_hidden(array('seq'=>'commit'));
            shn_form_fsopen(_t('Confirm'));
            echo "<p>";
            echo _t("You are going upgrade {$module_info['name']} to {$module_info['version']}<br>");
            echo _t("Data and the Original module will be backup, you can find them in the backup folder<br>");
            echo _t("Are you sure you want to continue? (I know, you have only one option, dude get use to it)");
            echo "</p>";
            shn_form_fsclose();
            shn_form_submit(_t('Yes'));
            shn_form_fclose();
            return true;
        }
    }else {
        //install
        $_SESSION['admin']['mmc']['type'] = 'install';
        $func = "shn_{$module_info['mod_prefix']}_install_page";
        //if the shn_<mod>_install_page() exists call that 
        if($module_info['setup.inc'] && function_exists($func)) {
            $func();
        }else {
            shn_form_fopen("mmc_add",null);
            shn_form_hidden(array('seq'=>'commit'));
            shn_form_fsopen(_t('Confirm'));
            echo "<p>";
            echo _t("You are going install {$module_info['name']} {$module_info['version']}<br>");
            echo _t("Are you sure you want to continue? (I know, you have only one option, dude get use to it)");
            echo "</p>";
            shn_form_fsclose();
            shn_form_submit(_t('Yes'));
            shn_form_fclose();
            return true;
        }
    }
}

function _shn_admin_mmc_create_tmp_dir()
{
    global $global;
    $tmp_dir = $global['approot'].'/www/tmp/'.'tmp_'.time().'/';
    if(! mkdir($tmp_dir)) {
        add_error(_t("Couldn't create the directory in the www/tmp. Make sure the location is writable."));
        return false;
    }else {
        return $tmp_dir;
    }
}

function _shn_admin_mmc_unzip_and_check($folder, $zipfile)
{
    global $global;
    $module_zip = new PclZip($zipfile);
    $list = $module_zip->extract(PCLZIP_OPT_PATH,$folder);
    if($list == 0) {
        add_error(_t("Unrecoverable error : '") . $module_zip->errorName(true). "'");
        if(! shn_tools_rmdir_rf($folder))
            add_error(_t("Couldn't delete the tmp directory, it's not harmful although you may want to clean it mannually to gain more disk speace")); 
        return false;
    }else {
        //check files
        //find the <directory>
        $d = dir($folder);
        while($file = $d->read()) {
            if(! ($file == '.' || $file == '..') ) { 
                if(is_dir($folder.'/'.$file)){
                    $dir_name = $file;
                }
            }
        }
        if(!$dir_name) {
            add_error(_t("No directory found in the zip file. Could be an invalid zip or files have been zipped incorrectly."));
            return false;
        }else {
            $return['mod_prefix'] = $dir_name;
            //conf.inc 
            if(!file_exists($folder.$dir_name.'/conf.inc')) {
                add_error(_t("No config file found in the zip. Please install a correct module zip file."));
                return false;
            }
            //conf.inc -- name, version
            include_once($folder.$dir_name.'/conf.inc');
            if(!$return['name']=$conf['mod_'.$dir_name.'_name']) {
                add_error(_t("Could not find the module name."));
                return false;
            }
            if(!$return['version']=$conf['mod_'.$dir_name.'_version']) {
                add_error(_t("Could not find the module version."));
                return false;
            } 
                
            //main.inc
            if(!file_exists($folder.$dir_name.'/main.inc')) {
                add_error(_t("Could not find the main.inc"));
                return false;
            }
            
            //check and give warnings
            //inc/dbcreate.sql
            //inc/dbupgrade.sql
            //ins/setup.inc 
            if(!file_exists($folder.$dir_name.'/ins/setup.inc')) {
                $return['setup.inc'] = false;
            }else {
                include_once($folder.$dir_name.'/ins/setup.inc');
                $func = 'shn_'.$dir_name.'_depends';
                if(function_exists($func)) {
                    $return['depends']=$func();
                }
            }

            if(!file_exists($folder.$dir_name.'/ins/dbcreate.sql')) {
                $return['dbcreate.sql'] = false;
            }else {
                $return['dbcreate.sql'] = $conf['db_engine'].'-dbcreate.sql';
            }

            if(!file_exists($folder.$dir_name.'/ins/dbupgrade.sql')) {
                $return['dbupgrade.sql'] = false;
            }else {
                $return['dbupgrade.sql'] = $conf['db_engine'].'-dbupgrade.sql';
            }
            
            //ins/setup.inc -- install(), uninstall(), upgrade()
            #include_once($folder.$dir_name.'/ins/setup.inc');
            #if(!function_exists('shn_'.$dir_name.'_install'){
            #    add_error(_t("Could not find the setup.inc"));
            #    return false;
            #}
        }
        return $return;
    }
}

function _shn_admin_mmc_upload_commit()
{
    global $global;
    global $conf;

    require_once($global['approot'].'/3rd/pclzip/pclzip.lib.php');

    if($_SESSION['admin']['mmc']['type'] == 'upgrade') {
        //backup the current module <mod>-<version>-<date>-<userid>.zip
        //e.g. mpr-0.2-192833032-5.zip
        $backup_file = $global['approot']."/backup/".
                $_SESSION['admin']['mmc']['module_info']['mod_prefix'].'-'.
                $_SESSION['admin']['mmc']['module_info']['version'].'-'.
                mktime().'-'.
                $_SESSION['user_id'].'.zip';
        $module_zip = new PclZip($backup_file);
        chdir($global['approot']."/mod/");
        $err = $module_zip->create($_SESSION['admin']['mmc']['module_info']['mod_prefix']);
        if($err == 0) {
            die("Error : ".$archive->errorInfo(true));
        }

        //if dbupdate.sql then backup data and schema
        //TODO:
        if($_SESSION['admin']['mmc']['module_info']['dbupgrade.sql']) {
            $sql_file = $_SESSION['admin']['mmc']['tmp_dir'].'/'.
                        $_SESSION['admin']['mmc']['module_info']['mod_prefix'].
                        '/ins/'.
                        $_SESSION['admin']['mmc']['module_info']['dbupgrade.sql'];
            $sql = implode("\n", file($sql_file) );
            $global['db']->Execute($sql);
            //TODO: Catch errors
        }

        //Remove existing directory 
        if(! shn_tools_rmdir_rf($global['approot']."/mod/".
            $_SESSION['admin']['mmc']['module_info']['mod_prefix'])) {
            die("couldn't delete the existing module directory");
        }
        
    }else {

    }
    //Move the tmp to mod folder
    if(! rename($_SESSION['admin']['mmc']['tmp_dir'].
            '/'.$_SESSION['admin']['mmc']['module_info']['mod_prefix'],
            $global['approot']."/mod/".$_SESSION['admin']['mmc']['module_info']['mod_prefix']) ) {
        die("could not move the tmp to main mod folder");

    }

    //remove the tmp folder
    if(! shn_tools_rmdir_rf($_SESSION['admin']['mmc']['tmp_dir']) ) {
        die("Could not delete the tmp folder");
    }

    //update the version 
    shn_db_config_update($_SESSION['admin']['mmc']['module_info']['mod_prefix'], 'version', $_SESSION['admin']['mmc']['module_info']['version']);

   
}


function shn_tools_rmdir_rf($path)
{
    global $rm_rf_error;
    if(file_exists($path)) {
        $d = dir($path);
        while($file = $d->read()) {
            if(! ($file == '.' || $file == '..') ) {
                if(is_dir($file)) {
                    shn_tools_rmdir_rf($path.'/'.$file);
                }else {
                    if(! unlink($path.'/'.$file)) {
                        $rm_rf_error = true;
                    }
                }
            }
        }
        if($rm_rf_error) {
            return false;
        }else {
            if(rmdir($path)) {
                return true;
            }else {
                $rm_rf_error = true;
                return false;
            }
        }
    }else {
        $rm_rf_error = true;
        return false;
    }
}

