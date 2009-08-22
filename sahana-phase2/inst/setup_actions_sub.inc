<?php
/**Action implementations of the Sahana Advanced Web Setup
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue. <ravithb@yahoo.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage setup
 */

/**
 * Implementation of the call back to write all the configuration to persistant form.
 *
 * @todo To undo any changes to the database table config.
 * @param Array $config_key_vals The configuration key value paris.
 * @param boolean $undo The flag to indicate rollback. If true the appropriate functions will
 * be called to undo any changes made to the database table config and the file system.
 * @return boolean Whether the operation succeeded
 */
function _shn_setup_write_config($config_key_vals,$undo=false){
	global $global,$conf;
	$conf_file = $global['approot']."conf/sysconf.inc.php";
	if($undo==false){

		// replace the config values in the modify code array.
		$modify = array();
		foreach($config_key_vals as $key=>$value){
			$modify["/\'$key\'/"] = '$conf[\''.$key.'\'] = \''.$value.'\';';
		}

		if ( @shn_config_file_update( $modify, $global['approot'].'conf/sysconf.inc.tpl.php',
		$conf_file) ) {
			return true;
		} else {
			add_error(_t('Could not write to file ').$conf_file._t(' file. You may not have write permissions to the parent directory.'));
			return false;
		}
	}else{
		// undo changes

		if(file_exists($conf_file)){
			$res = unlink($conf_file);
			if(!$res){
				add_error(_t("Unable to undo the changes made. Please delete the ").$conf_file._t(" file manually"));
			}
		}
	}
}

/**
 * General Call back implementation to setup the database tables and users.
 *
 * @param Array $conf_key_vals The configuration key value pairs.
 * @param Array $db_action The names of the actions which are used to construct the delegate method call.
 *                          Executed in the order specified.
 * @return boolean Whether the operation succeeded or not.
 */
function _shn_setup_setupdb($conf_key_vals,$db_action_arr)
{
	global $global;
	global $conf;
	if($conf_key_vals['db_type']=='mysql'){
		$res = true;
		foreach($db_action_arr as $db_action){
			// mysql specific setup
			// the database specific function should handle any transactions.
			$function_name = '_shn_setup_db_'.$db_action.'_mysql';
			if(function_exists($function_name)){
				$res &= $function_name($conf_key_vals);
			}else{
				echo sprintf(_t("Function %s is not found"),$function_name)."<br/>";
			}
		}
		return $res;
	}
}

function _shn_setup_db_create_user_mysql($conf_key_vals){
	global $global;

	$_tdb1 =  &NewADOConnection('mysql');
	$_host_port = $conf_key_vals['db_host'].":".(isset($conf_key_vals['db_port'])?$conf_key_vals['db_port']:"3306");
	if(_shn_setup_is_keep_user()==false){
		// start a new connection
		$_tdb1->Connect($_host_port,$conf_key_vals['root_db_user'],$conf_key_vals['root_db_pass']);
		/*$res=$_tdb1->Execute("SELECT * FROM `user` WHERE `User`='".$conf_key_vals['db_user']."'");
		 if(!($res->EOF)){
		 add_error(_t("System database username already exists. Use a different system database username."));
		 $_tdb1->Close();
		 return false;
		 }*/

		// create system user and privileges
		$_tdb1->Execute("CREATE USER '".$conf_key_vals['db_user']."'@'".$conf_key_vals['db_host']."' IDENTIFIED BY '".$conf_key_vals['db_pass']."'");
		$_tdb1->Close();
	}

}

function _shn_setup_db_create_db_mysql($conf_key_vals){
	global $global;

	// another separate connection to create users and databases.
	$_tdb2 = &NewADOConnection('mysql');
	$_tdb2->Connect($_host_port,$conf_key_vals['root_db_user'],$conf_key_vals['root_db_pass'],'mysql');
	if($_tdb2->IsConnected()==false){
		add_error(_t("Incorrect database username or password."));
		$_tdb2->Close();
		return false;
	}

	if (_shn_setup_is_drop_db()){
		$_tdb2->Execute("DROP DATABASE ".$conf_key_vals['db_name']);
	}

	// create the main database
	$_tdb2->Execute("CREATE DATABASE IF NOT EXISTS ".$conf_key_vals['db_name']);

	$_tdb2->Execute("GRANT ALL PRIVILEGES ON ".$conf_key_vals['db_name'].".* TO '".$conf_key_vals['db_user']."'@'".$conf_key_vals['db_host']."'");
	$_tdb2->Close();
}

/**
 * Setup the mysql database.
 *
 * @param Array $conf_key_vals The configuration key value pairs.
 * @return boolean Whether the operation succeeded or not.
 */
function _shn_setup_db_setup_db_mysql($conf_key_vals){
	global $global;
    if(file_exists($global['approot']."about.inc")){
        include_once $global['approot']."about.inc";
        global $about;
    }
	// another connection with transactions to create thetables and data.
	$_tdb3 = &NewADOConnection('mysql');
	$_tdb3->Connect($_host_port,$conf_key_vals['db_user'],$conf_key_vals['db_pass'],$conf_key_vals['db_name']);
	//$_tdb3->debug=true;
	//$_tdb3->StartTrans();
	$global['db'] = $_tdb3;
	$conf['db_engine']=$conf_key_vals['db_type'];
	$conf['mysql_engine']="myisam";

	if($conf['db_engine'] == 'mysql')
	{
		$_tdb3->Execute("set storage_engine ='".$conf['mysql_engine']."'");
	}
	// setup the base.
	_shn_setup_run_sqlscript($_tdb3,'inst/mysql-dbcreate.sql');
	_shn_setup_run_sqlscript($_tdb3,'inst/mysql-config.sql');
	_shn_setup_run_sqlscript($_tdb3,'inst/sample-data.sql');

	$selected_mods = array();

	if(_shn_setup_get_setup_type()==SIMPLE_SETUP){
		// simple setup.
		$all_mods = shn_get_all_modules();
		if($all_mods!=null){
			foreach($all_mods as $mod){
				array_push($selected_mods,$mod[0]);
			}
		}
	}else{
		// advanced setup.
		// setup the selected modules.
		$selected_mods = _shn_setup_get_selected_modules();
	}
	
	if($selected_mods!=null){
		foreach($selected_mods as $mod){
			_shn_setup_run_sqlscript($_tdb3,'mod/'.$mod.'/inst/dbcreate.sql');
			_shn_setup_run_sqlscript($_tdb3,'mod/'.$mod.'/inst/mysql-config.sql');
			if(file_exists($global['approot'].'/mod/'.$mod.'/inst/setup.inc')){
				include_once($global['approot'].'/mod/'.$mod.'/inst/setup.inc');
				$datacreate_funct = 'shn_'.$mod.'_datacreate';
				if(function_exists($datacreate_funct)){
					global $global;
					$global['db'] = $_tdb3;
					$datacreate_funct();
				}				
			}
			$_tdb3->Execute("INSERT INTO modules(module,status) VALUES(?,?)",array($mod,'installed'));
		}
	}
	// insert the sample data separately if it should be..
	if(_shn_setup_is_setup_sample_data()){
		if($selected_mods!=null){
			foreach($selected_mods as $mod){
				_shn_setup_run_sqlscript($_tdb3,'mod/'.$mod.'/inst/sample-data.sql');
			}
		}
	}

	shn_acl_install($conf_key_vals['admin_name'],$conf_key_vals['root_pwd'],$conf_key_vals['user_name'],$conf_key_vals['user_pwd']);

	//$res = $_tdb3->CompleteTrans();
	//$_tdb3->Close();
	//return $res;

	// add the version information to the database.
	include_once $global['approot']. 'inc/lib_security/lib_acl.inc';
	$_tdb3->Execute("INSERT INTO sahana_version(sahana_version,sahana_release,release_date,release_info) VALUES ('".$about['version']."','".$about['release']."','".$about['release_date']."','".$about['release_info']."')");
	return true;
}

/**
 * Undo any changes made to the database management system by the sahana setup. Used to roll back when the setup fails, to avoid
 * partial installations.
 *
 * @param Array $conf_key_vals The configuration key value paris.
 */
function _shn_setup_db_undo_mysql($conf_key_vals){
	$db = &NewADOConnection('mysql');
	$_host_port = $conf_key_vals['db_host'].":".(isset($conf_key_vals['db_port'])?$conf_key_vals['db_port']:"3306");
	$db->Connect($_host_port,$conf_key_vals['root_db_user'],$conf_key_vals['root_db_pass'],'mysql');
	// only drop if the user was created by the setup
	if(_shn_setup_is_keep_user()==false){
		$res=$db->Execute("SELECT * FROM `user` WHERE `User`='".$conf_key_vals['db_user']."'");
		if(!($res->EOF)){
			// drop the created user.
			$db->Execute("DROP USER ".$conf_key_vals['db_user']."'@'%'");
		}
	}
	// only drop if it was created by setup.
	if(_shn_setup_is_drop_db()==false){
		$res = $db->Execute("SELECT * from `db` WHERE `Db`='".$conf_key_vals['db_name']."'");
		// check whether the user has overridden operation to drop database.
		if($db->IsConnected() && (!$res->EOF)){
			$db->Execute("DROP DATABASE ".$conf_key_vals['db_name']);
		}
	}
	$db->Close();
}

/**
 * Run a SQL Script on the selected database connection
 *
 * @param ADOConnection $db The database connection.
 * @param String $script_path The path of the script.
 */
function _shn_setup_run_sqlscript($db, $script_path)
{
	global $global;

	$script = $global['approot'].$script_path;

	if(file_exists($script)){
		if ($fh = fopen($script,'r')) {
			$sql=''; // clear the bucket

			while (! feof($fh) ) { // a fix as Execute gets confused over carriage returns
				$buffer = fgets($fh,1024); // read the script and fill the buffer
				$sql=$sql.$buffer; // fill the buffer until ';' appear
				if(preg_match('/;/',$buffer)) { // look after ';'
					$db->Execute($sql);
					$sql=''; // clear the bucket again
				}
			}
			//$sql = fread($fh,filesize($script));
			fclose($fh);
		}
	}
	// @todo error handler if file does not exist
}

/**
 * Persist any configuratio in the advanced configuration page.
 *
 * @param Array $config_key_vals The configuration key value pairs.
 */
function _shn_setup_adv_write_advanced_config($config_key_vals){

	global $global;

	include_once($global['approot']."inc/lib_config.inc");
	shn_config_database_update('acl_enabled','enable'==$config_key_vals['acl'],'admin');
	shn_config_database_update('theme',$config_key_vals['theme']);

	// module specific configuration goes here.
	$selected_modules = _shn_setup_get_selected_modules();
	if(isset($selected_modules)){
		// load configuration
		shn_config_module_conf_fetch('all');

		foreach($selected_modules as $sel_mod){
			// include the module specific setup.inc
			$mod_setup_file = $global['approot']."mod/".$sel_mod."/ins/setup.inc";
			if(file_exists($mod_setup_file)){
				include_once($mod_setup_file);
				// the module specific configuration save callback function.
				$mod_conf_save_func = "_shn_".$sel_mod."_setup_config_save";
				if(function_exists($mod_conf_save_func)){
					$mod_conf_page_func($config_key_vals);
				}
			}
		}
	}
	return true;
}

/**
 * Persist the password policy configured by the user.
 *
 * @param Array $config_key_vals The configuration key value pairs.
 */
function _shn_setup_adv_write_pwd_policy($config_key_vals){
	global $global;
	include_once($global['approot']."inc/lib_config.inc");

	shn_config_database_update('pwd_min_chars',$config_key_vals['pwd_min_chars'],'admin');
	if(isset($config_key_vals['pwd_max_chars'])){
		shn_config_database_update('pwd_max_chars',true,'admin');
	}
	if(isset($config_key_vals['pwd_has_uppercase'])){
		shn_config_database_update('pwd_has_uppercase',true,'admin');
	}
	if(isset($config_key_vals['pwd_has_numbers'])){
		shn_config_database_update('pwd_has_numbers',true,'admin');
	}
	if(isset($config_key_vals['pwd_has_spchars'])){
		shn_config_database_update('pwd_has_spchars',true,'admin');
	}
	if(isset($config_key_vals['pwd_has_username'])){
		shn_config_database_update('pwd_has_username',true,'admin');
	}
	if(isset($config_key_vals['pwd_has_reppatterns'])){
		shn_config_database_update('pwd_has_reppatterns',true,'admin');
	}
	return true;
}

/**
 * Persist the module selection.
 *
 */
function _shn_setup_adv_write_selected_modules(){
	global $global;
	include_once($global['approot']."inc/lib_config.inc");
	$selected_mods = _shn_setup_get_selected_modules();
	$all_modules = shn_get_all_modules();

	$non_installed_mods = array();
	foreach ($all_modules as $mod){
		if(in_array($mod,$selected_mods)==false){
			array_push($non_installed_mods,$mod);
		}
	}

	foreach ($selected_mods as $mod){
		shn_config_database_update('installed',true,$mod);
	}

	foreach ($non_installed_mods as $mod){
		shn_config_database_update('installed',false,$mod);
	}

	return true;
}

