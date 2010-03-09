<?php

/**Page generation functions of the Sahana Advanced Web Setup
 *
 * PHP version 5
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
 * Setup general dependencies such as GD and Gettext.
 *
 */
function shn_setup_general_dependencies()
{
	global $global, $writableDirectories;
	$isOK = true;
	$tick_img = '<img align="top" src="theme/default/img/tic.png" alt="tick"/>';
	$cross_img = '<img align="top" src="theme/default/img/cross.png" alt="cross"/>';
	$oops_img = '<img align="bottom" src="theme/default/img/oops.png" alt="oops"/>';
	// this is the first step in all setups.
	$step_no = 1;
	$_SESSION['setup_step_no'] = 1;

	?>
<h1><?php echo _t('Sahana Web Setup - Step ').$step_no?></h1>

<p><?php echo _t('Welcome to Sahana. Please follow the following steps to setup the Sahana system')?></p>

<p><?php echo _t('First we need to check if all the relevant dependencies for the Sahana system to be install are available on your system')?></p>
	<?php
	shn_form_fopen('general_dependencies_submit',null,array('req_message'=>false));
	shn_form_fsopen(_t('PHP libraries'));
	?>
<p><?php echo _t('The following checks if all the relevant Sahana libraries are installed')?></p>
	<?php

	$value = (version_compare(phpversion(), '5', '>'));
	$isOK &= $value;

	//if ($isOK) echo "is OK";
	if ($value) {
		shn_form_label(_t('PHP Version'), $tick_img.phpversion()." is installed");
	} else {
		shn_form_label(_t('PHP Version'), $cross_img.phpversion()." is installed");
		echo "<p><br/>$oops_img Sahana needs PHP version 5.0 or higher. Please upgrade your version of PHP</p>";
	}

	// Check if php-gd is loaded
	$value = (extension_loaded('gd'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_t('PHP-GD Library'), $tick_img."installed");
	} else {
		shn_form_label(_t('PHP-GD Library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-GD for image manipulations. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	// Check if php-gettext is loaded
	$value = (extension_loaded('gettext'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_t('PHP-gettext Library'), $tick_img."installed");
	} else {
		shn_form_label(_t('PHP-gettext Library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-gettext for to support local languages. Please install PHP-gettext and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	$value = (extension_loaded('mysql'));
	$isOK &= $value;

	if ($value) {
		shn_form_label(_t('MySQL library'), $tick_img."installed");
	} else {
		shn_form_label(_t('MySQL library'), $cross_img."is not installed");
		echo "<p><br/>$oops_img Sahana needs PHP-MySQL library and MySQL for database operation. Please install PHP-MySQL library and MySQL and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
	}

	shn_form_fsclose();
	shn_form_fsopen(_t('File and Directory Permissions'));
	?>
<p><?php echo _t('The following checks if certain files and sub-directories have write permissions for Sahana to function,')?></p>
	<?php

	$notWritable = array();
	foreach ($writableDirectories as $dir) {
		$dirWritable = is_writable($global['approot'].$dir);
		$isOK &= $dirWritable;
		
		if ($dirWritable) {
			shn_form_label(_t("<i>sahana/$dir/</i>"),"is <strong><font color=green>writable</font></strong>!<br>");
		} else {
			shn_form_label(_t("<i>sahana/$dir/</i>"),"is <strong><font color=red>not writable</font></strong>!<br>");
			$notWritable[] = $dir;
		}
	}
	if (!empty($notWritable)) {
		$missingDirectories = implode('</strong>, <strong>', $notWritable);
		echo "<p>Note: <font color=gray>";
		if (count($notWritable) > 1) {
			echo "A few directories (<strong>$missingDirectories</strong>) need to be writable by the web server at least. Please change the permissions of these directories and try again.";
		}
		else {
			echo "The <strong>$missingDirectories</strong> directory needs to be writable by the web server at least. Please change the permissions of this directory and try again.";
		}
		echo '</font></p>';
	}
	shn_form_fsclose();

	if ($isOK) {
		echo _t('<p>All the dependencies are OK and you may move to
                the next step</p>')."\n";
		shn_form_submit(_t('Next >>'));
	} else {
		echo _t('<p>Please correct the required dependencies above and</p>')."\n";
		shn_form_submit(_t('Try Again'));
	}
	shn_form_fclose();
}

/**
 * Generate the license page.
 *
 * @param unknown_type $step_no
 */
function shn_setup_license($step_no=null)
{
	global $global;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php echo _t('Sahana Web Setup - Step ').$step_no?></h2>
	<?php

	$license = file_get_contents($global['approot']."lgpl-2.1.txt");
	$license = htmlentities($license,ENT_QUOTES,'utf-8',false);
	shn_form_fopen('license_submit',null,array('req_message'=>false));
	shn_form_fsopen(_t('License Agreement'));
	echo _t("You will need to adhere to the following license to proceed with the setup.");
	echo "<br/>";
	shn_form_textarea(null,'license',null,array('value'=>$license,'rows'=>15,'cols'=>70,'no_label'=>true));
	shn_form_fsclose();
	shn_form_label("Do you accept the above license agreement?",null);
	echo "<br/>";

	shn_form_submit(_t('<< No, Go Back'),'name="back_button"');
	shn_form_submit(_t('Yes, Continue >>'));
	shn_form_fclose();
}

/**
 * Generate the select setup page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_select_setup($step_no=null)
{
	global $global;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php echo _t('Sahana Database Setup - Step ').$step_no?></h2>
	<?php
	shn_form_fopen('select_setup_submit',null,array('req_message'=>false));
	shn_form_fsopen(_t('Select a setup type to continue.'));
	shn_form_fsopen(_t("Simple Setup"));
	echo _t("To setup the most common modules and configuration.");
	echo "<br/>";
	shn_form_submit(_t("Simple"),'name="setup_type_simple"');
	shn_form_fsclose();
	shn_form_fsopen(_t("Advanced Setup"));
	echo _t("To customize modules and configuration.");
	echo "<br/>";
	shn_form_submit(_t("Advanced"),'name="setup_type_adv"');
	shn_form_fsclose();
	/*shn_form_fsopen(_t("Scenario Based Setup"));
	 echo _t("To customize modules and configuration for a specific scenario.");
	 echo "<br/>";
	 shn_form_submit(_t("Scenario Based"),'name="setup_type_scen"');
	 shn_form_fsclose();*/
	shn_form_fsclose();
	shn_form_submit(_t('<< Back'),'name="back_button"');
	shn_form_fclose();
}

function shn_setup_select_dbsetup($step_no=null){
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
<h2><?php
echo _t('Sahana Web Setup - Step ').$step_no;
?></h2>
<?php
display_errors();
shn_form_fopen('select_dbsetup_submit',null,array('req_message'=>false));
shn_form_fsopen(_t('Select a database setup method'));
shn_form_radio(array("use_new_db"=>_t("New Database")),null,'dbsetup_method',null,array('no_label'=>true,'value'=>($_SESSION[SETUP_DATA_PREFIX."dbsetup_method"])));
shn_form_radio(array("use_empty_db"=>_t("Use Empty Database")),null,'dbsetup_method',null,array('no_label'=>true,'value'=>($_SESSION[SETUP_DATA_PREFIX."dbsetup_method"])));
shn_form_radio(array("use_existing_db"=>_t("Use Existing Database")),null,'dbsetup_method',null,array('no_label'=>true,'value'=>($_SESSION[SETUP_DATA_PREFIX."dbsetup_method"])));
shn_form_fsclose();
shn_form_submit(_t('<< Back'),'name="back_button"');
shn_form_submit(_t("Next >>"));
shn_form_fclose();
}

/**
 * Generate the database setup page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_simple_dbsetup($step_no=null)
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h2><?php
    echo _t('Sahana Web Setup - Step ').$step_no;
    ?></h2>
    <?php
    display_errors();
    shn_form_fopen('simple_dbsetup_submit',null);
    if(isset($_SESSION['setup_system_db_user_exists'])){
    	/*
    	 * 	Duplicate system database username. Confirm to keep or give a different name.
    	 */

    	shn_form_fsopen('User Exists.');
    	echo "<div class='warning message'>";
    	echo _t("Database user name ".$_SESSION[SETUP_DATA_PREFIX."db_user"]." already exists.
    To continue, select a different user name. If you want to keep the existing user click on 'Keep User'. ");
    	echo "</div>";
    	//add_warning('test');
    	shn_form_submit(_t('Keep User'),'name="keep_ex_user"');
    	shn_form_fsclose();
    }

    if(isset($_SESSION['setup_system_db_exists'])){
    	/*
    	 * 	Duplicate system database. Confirm to keep or give a different name.
    	 */
    	shn_form_fsopen('Database Exists.');
    	echo "<div class='warning message'>";
    	echo _t("Database ".$_SESSION[SETUP_DATA_PREFIX."db_name"]." already exists.
        Enter a different database name to continue. Press 'Drop Database' to delete the database and to continue installation.");
    	echo "</div>";
    	shn_form_submit(_t('Drop Database'),'name="drop_ex_db"');
    	shn_form_fsclose();
    }
    shn_form_fsopen(_t('Database'));
    shn_form_select(
    array( 'mysql' => 'MySQL 4.1 or above','pgsql"disabled="disabled' => 'PostgreSQL'),
                    'Database Types', 'db_type',(isset($_SESSION[SETUP_DATA_PREFIX."db_type"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_type"]):array());
    shn_form_text(_t('Database Host:Port'),'db_host','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_host"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_host"].((isset($_SESSION[SETUP_DATA_PREFIX."db_port"]))?':'.$_SESSION[SETUP_DATA_PREFIX."db_port"]:''),'req'=>true):array('value'=>'localhost:3306','req'=>true)
    );
    shn_form_text(_t('Database Name'),'db_name','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_name"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_name"],'req'=>true):array('value'=>'sahana','req'=>true)
    );
    $db_user_help = _t('This is the root/super user name who has access rights to create new databases and users on your database server.');
    shn_form_text(_t('Database User'),'root_db_user','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."root_db_user"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."root_db_user"],'req'=>true,'help'=>$db_user_help):array('value'=>'','req'=>true,'help'=>$db_user_help)
    );
    $db_pass_help = _t('This is the password for the root/super user. Note: this password will only be used to create a database and a new user having access rights to the same.');
    shn_form_password(_t('Database Password'),'root_db_pass','size="30"', (isset($_SESSION[SETUP_DATA_PREFIX."root_db_pass"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."root_db_pass"],'req'=>true,'help'=>$db_pass_help):array('value'=>'','req'=>true,'help'=>$db_pass_help));
    $sys_user_help = _t('This is the username of the user which will be created for this sahana instance on your database server. All system database access will happen through this user\'s credentials');
    shn_form_text(_t('System Database User'),'db_user','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_user"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_user"],'req'=>true,'help'=>$sys_user_help):array('value'=>'sahana_sys','req'=>true,'help'=>$sys_user_help));
    $sys_pass_help = _t('This is the password for the above system database user. You do not need to remember this password as it will be used only by the system to access the database. The default value of this field is "password"');
    shn_form_password(_t('System Database Password'),'db_pass','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_pass"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_pass"],'req'=>true,'help'=>$sys_pass_help):array('value'=>'password','req'=>true,'help'=>$sys_pass_help));

    //show only in simple setup
    if(_shn_setup_get_setup_type() == SIMPLE_SETUP){
    	// add sample data check box.
    	// check for a mandatory field to see if this is the first time request
    	shn_form_checkbox(_t('Create Sample Data.'),'dbsample',(isset($_SESSION[SETUP_DATA_PREFIX."dbsample"])?'checked':(isset($_SESSION[SETUP_DATA_PREFIX.'db_type'])?'':'checked')),
    	array('value'=>'y'));
    }
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t('Setup Database >>'));
    shn_form_fclose();
}

function shn_setup_empty_dbsetup()
{
	global $global;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	add_warning(_t("Any existing tables in the selected database will be destroyed."));
	?>
    <h2><?php
    echo _t('Sahana Web Setup - Step ').$step_no;
    ?></h2>
    <?php
    display_errors();
    display_submit_message();

    shn_form_fopen('empty_dbsetup_submit',null);
    shn_form_fsopen(_t('Select an empty database'));
    shn_form_fsopen(_t('Database'));
    shn_form_select(
    array( 'mysql' => 'MySQL 4.1 or above','pgsql"disabled="disabled' => 'PostgreSQL'),
                    'Database Types', 'db_type',(isset($_SESSION[SETUP_DATA_PREFIX."db_type"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_type"]):array());
    shn_form_text(_t('Database Host:Port'),'db_host','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_host"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_host"].((isset($_SESSION[SETUP_DATA_PREFIX."db_port"]))?':'.$_SESSION[SETUP_DATA_PREFIX."db_port"]:''),'req'=>true):array('value'=>'localhost:3306','req'=>true)
    );
    shn_form_text(_t('Database Name'),'db_name','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_name"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_name"],'req'=>true):array('value'=>'sahana','req'=>true)
    );
    shn_form_text(_t('System Database User'),'db_user','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_user"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_user"],'req'=>true):array('value'=>'sahana_sys','req'=>true));
    shn_form_password(_t('System Database Password'),'db_pass','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_pass"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_pass"],'req'=>true):array('value'=>'password','req'=>true));
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t('Setup Database >>'));
    shn_form_fclose();
}


function shn_setup_existing_dbsetup()
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h2><?php
    echo _t('Sahana Web Setup - Step ').$step_no;
    ?></h2>
    <?php
    display_errors();
    shn_form_fopen('existing_dbsetup_submit',null);
    shn_form_fsopen(_t('Select an existing database'));
    shn_form_fsopen(_t('Database'));
    shn_form_select(
    array( 'mysql' => 'MySQL 4.1 or above','pgsql"disabled="disabled' => 'PostgreSQL'),
                    'Database Types', 'db_type',(isset($_SESSION[SETUP_DATA_PREFIX."db_type"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_type"]):array());
    shn_form_text(_t('Database Host:Port'),'db_host','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_host"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_host"].((isset($_SESSION[SETUP_DATA_PREFIX."db_port"]))?':'.$_SESSION[SETUP_DATA_PREFIX."db_port"]:''),'req'=>true):array('value'=>'localhost:3306','req'=>true)
    );
    shn_form_text(_t('Database Name'),'db_name','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_name"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_name"],'req'=>true):array('value'=>'sahana','req'=>true)
    );
    shn_form_text(_t('System Database User'),'db_user','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_user"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_user"],'req'=>true):array('value'=>'sahana_sys','req'=>true));
    shn_form_password(_t('System Database Password'),'db_pass','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."db_pass"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."db_pass"],'req'=>true):array('value'=>'password','req'=>true));
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t('Setup Database >>'));
    shn_form_fclose();
}

/**
 * Generate the simple configuration page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_simple_config($step_no=null)
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h2><?php
    echo _t("Sahaha Web Setup - Step ").$step_no;
    ?></h2>
    <p><?php echo _t("Please follow the following steps to setup the Sahana configuration.") ?></p>

    <?php
    display_errors();
    global $global ,  $conf;
    ?>
    <script
    	type="text/javascript" src="res/js/styleswitcher.js"></script>
    <noscript>Style change preview is not available, without javascript
    support.</noscript>

    <?php
    shn_form_fopen('simple_config_submit',null);

    // pass the previous post varibles into hidden for the configuration file

    shn_form_fsopen(_t('Installation Details'));

    echo '<p>The following details are needed to uniquely identify your Sahana installation</p>'; // some spellings corrected by chamath 2007-03-15 09:50

    $help_txt = "The following field is randomly generated to help uniquely identify \
                     this Sahana installation. Please use this unless you have a \
                     convention defined";
    shn_form_text(_t('Unique Installation ID'),'base_uuid','size="4" maxlength="4"',
    (isset($_SESSION[SETUP_DATA_PREFIX."base_uuid"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."base_uuid"],'req'=>true , 'help' => $help_txt):array('value'=> shn_generate_uuid(4),'req'=>true , 'help' => $help_txt));
    shn_form_text(_t('Administrator Name'),'root_name','size="40"',(isset($_SESSION[SETUP_DATA_PREFIX."root_name"]))?array('value'=>$_SESSION[SETUP_DATA_PREFIX."root_name"],'req'=>true):array('req'=>true ));
    shn_form_text(_t('Administrator Email'),'root_email','size="40"',(isset($_SESSION[SETUP_DATA_PREFIX."root_email"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."root_email"]):array()));
    shn_form_text(_t('Administrator Telephone'),'root_tel','size="30"',(isset($_SESSION[SETUP_DATA_PREFIX."root_tel"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."root_tel"]):array()) );

    shn_form_fsclose();

    shn_form_fsopen(_t('Administrator Account'));
    shn_form_text(_t('Admin User Name'),'admin_name','size="40"', (isset($_SESSION[SETUP_DATA_PREFIX."admin_name"])?array('req'=>true, 'value'=>$_SESSION[SETUP_DATA_PREFIX."admin_name"],'help'=>'The root user is the administrator
                    of the system and has the greatest privilages'):array('req'=>true, 'value'=>'admin','help'=>'The root user is the administrator
                    of the system and has the greatest privilages') ));
    $_POST['root_pwd']='';
    $_POST['root_pwd_confirm']='';
    shn_form_password(_t('Password'),'root_pwd','size="30"',array('req'=>true)
    );
    shn_form_password(_t('Confirm Password'),'root_pwd_confirm','size="30"',array('req'=>true));
    shn_form_fsclose();

    shn_form_fsopen(_t('Create Normal User Account'));
    shn_form_text(_t('Normal User Name'),'user_name','size="40"', (isset($_SESSION[SETUP_DATA_PREFIX."user_name"])?array('req'=>true,'value'=>$_SESSION[SETUP_DATA_PREFIX."user_name"], 'help'=>'Please login as this user for non-admin work'):array('req'=>true,'value'=>'sahana', 'help'=>'Please login as this user for non-admin work')) );
    $_POST['user_pwd']='';
    $_POST['user_pwd_confirm']='';
    shn_form_password(_t('Password'),'user_pwd','size="30"',array('req'=>true));
    shn_form_password(_t('Confirm Password'),'user_pwd_confirm','size="30"',array('req'=>true));
    shn_form_fsclose();

    shn_form_fsopen(_t('Configuration File'));
    if (is_writeable($global['approot'].'conf')) {

    	echo '<p>The next step is to write the configuration file sysconf.inc in the Sahana /conf directory.</p>';

    } else {
    	echo '<p>The PHP/Web Server should normally not have access to write
        or modify the configuration file located in Sahana application <b>/conf</b> 
        directory, as this is a security risk. Please specify where to write the temporary file (e.g. /tmp). Subsequently you need to move this file to 
        the Sahana <b>/conf</b> directory.</p>';

    	$tmp_filename = tempnam('/tmp','sysconf.inc.php');
    	// Need the temporary directory rather than the filename
    	$tmp_filename = preg_replace('/sysconf.inc.php.*$/','sysconf.inc.php',
    	$tmp_filename);

    	shn_form_text(_t('Location To Write Config File (sysconf.inc.php)'),
                    'conffile','size="50"', (isset($_SESSION[SETUP_DATA_PREFIX."conffile"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."conffile"],
                    'req'=>true ):array('value'=>"$tmp_filename",
                    'req'=>true )));

    }
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t('Write Configuration File >>'));
    shn_form_fclose();
}

/**
 * Generate the module selection page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_select_modules($step_no=null)
{
	global $global, $conf;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h2><?php 
    echo _t("Sahaha Web Setup - Step ").$step_no;
    ?></h2>
    <p><?php echo _t("Please follow the following steps to setup the Sahana configuration.") ?></p>
    <?php
    display_errors();

    // load configuration
    shn_config_module_conf_fetch('all');

    $all_modules = shn_get_all_modules();
    asort($all_modules);

    $_essencial_modules = _shn_setup_get_essencial_modules();

    shn_form_fopen('adv_select_modules_submit',null,array('req_message'=>false));
    shn_form_fsopen(_t("Sahana Core"));
    echo _t("The following core modules will be installed by default.");
    echo "<hr/><ul>";
    foreach($_essencial_modules as $esmod){
    	echo "<li>".shn_get_module_name($esmod)."</li>";
    }
    echo "</ul>";
    shn_form_fsclose();

    shn_form_fsopen(_t('Please select the required modules'));
    foreach($all_modules as $key=>$value){
    	if(in_array($value[0],$_essencial_modules)){
    		// put the value in session directly.
    		_shn_setup_put_value_in_session('module_'.$value[0],true);
    	}else{
    		$checked = "";
    		if(_shn_setup_are_modules_selected()){
    			if(in_array($value[0],_shn_setup_get_selected_modules())){
    				$checked = "CHECKED";
    			}
    		}
    		shn_form_checkbox($value[1],'module_'.$value[0],'onchange="selectDepModsInUI(this)" '.$checked,array('value'=>$value[0]));
    	}
    }

    //include_once($global['approot']."/tools/jdebug.php");
    ?>
    <script type="text/javascript">

    var allDeps = new Array();
    // number of hits per module
    var arrHits = new Array();
    <?php
	// remove essencial modules
	// so that no javascript is generated for them
	$new_arr = array();
	foreach($all_modules as $key=>$value){
		if(in_array($value[0],$_essencial_modules)==false){
			$new_arr[$key]=$value;
		}
	}
	$all_modules = $new_arr;

	foreach($all_modules as $key=>$value){
		if(isset($conf['mod_'.$value[0].'_dependencies'])){
			echo "allDeps['".$value[0]."'] = new Array(";
			// get the dependant modules by splitting the dependencies string.
			$dep_mods = explode(",",'"'.$conf['mod_'.$value[0].'_dependencies'].'"');
			// generate a string of all dependant modules separated by commas.
			$mods_str = "";
			$_j = 0;
			foreach($dep_mods as $mod_code){
				if($_j>0){
					$mods_str .= "\",\"".$mod_code;
				}else{
					// first time no preceding comma.
					$mods_str = $mod_code;
				}
				$_j++;
			}
			echo $mods_str.");\n";
		}
		echo "arrHits['".$value[0]."'] = 0;\n";
	}
		?>
	function selectDepModsInUI(src){
		var checkBoxes = document.getElementsByTagName('input');
		var mod_deps = allDeps[src.value];
		if(mod_deps != null){
			// for each module in the module dependency list
			for(j=0;j<mod_deps.length;j++){
				if(src.checked==true){
					// increment hits
					arrHits[mod_deps[j]]++;
				}else{
					// 	decrement hits
					arrHits[mod_deps[j]]--;
				}
				// check the dependent check boxes algorithm
				for(k=0;k<checkBoxes.length;k++){
					// get only the check boxes.
					if(checkBoxes[k].getAttribute("type")=="checkbox" && (checkBoxes[k].id.indexOf("module_")>-1)){
						if(checkBoxes[k].value == mod_deps[j]){
							if(arrHits[checkBoxes[k].value]!=null && arrHits[checkBoxes[k].value]>0){
								// there are other modules that depend which are selected
								// keep selected and disabled.
								checkBoxes[k].checked = true;
								checkBoxes[k].disabled = true;
							}else{
								// no modules dependant are selected.
								checkBoxes[k].checked = src.checked;
								checkBoxes[k].disabled = src.checked;
							}					
						}
					}
				}										
			}
			
			
		} 
	}
//-->
</script>
    <?php
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t('Next >>'));
    shn_form_fclose();
}

/**
 * Generate the advanced configuration page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_advanced_config($step_no=null)
{
	global $global, $conf;
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h2><?php 
    echo _t("Sahaha Web Setup - Step ").$step_no;
    ?></h2>

    <?php
    display_errors();
    shn_form_fopen('adv_advanced_config_submit');
    shn_form_fsopen(_t('System Settings'));

    shn_form_select(
    array( 'disable' => _t('Disable'),'enable' =>_t('Enable')),
    _t('Access Control'),'acl',isset($_SESSION[SETUP_DATA_PREFIX."acl"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."acl"]):array());

    // create the associative array of themes.
    $available_themes = _shn_setup_get_available_themes();
    $themelist = array();
    foreach($available_themes as $tname){
    	if($tname!=$conf['theme']){
    		?>
    <link rel="stylesheet"
    	media="screen, projection" type="text/css"
    	href="theme/<?php echo $tname?>/sahana.css" />
    <link
    	rel="stylesheet" media="print" type="text/css"
    	href="theme/<?php echo $tname?>/print.css" />
    <link
    	rel="stylesheet" media="handheld" type="text/css"
    	href="theme/<?php echo $tname?>/mobile.css" />
    		<?php
    	}
    	$themelist[$tname] = ucwords($tname)._t(' Theme');
    }
    shn_form_select($themelist,_t('Theme'),'theme','onchange=setActiveStyleSheet(this.options[this.selectedIndex].value)',isset($_SESSION[SETUP_DATA_PREFIX."theme"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."theme"]):array('value'=>'default'));
    shn_form_fsclose();
    
    shn_form_submit(_t("<<Next "));
    shn_form_submit(_t('Back>>'),'name="back_button"');

    $selected_modules = _shn_setup_get_selected_modules();
    if(isset($selected_modules)){
    	// load configuration
    	shn_config_module_conf_fetch('all');

    	foreach($selected_modules as $sel_mod){
    		// include the module specific setup.inc
    		$mod_setup_file = $global['approot']."mod/".$sel_mod."/ins/setup.inc";
    		if(file_exists($mod_setup_file)){
    			include_once($mod_setup_file);
    			// the module specific configuration page generator callback function.
    			$mod_conf_page_func = "_shn_".$sel_mod."_setup_config_page";
    			if(function_exists($mod_conf_page_func)){
    				shn_form_fsopen(shn_get_module_name($sel_mod)._t(" Configuration"));
    				$mod_conf_page_func();
    				shn_form_fsclose();
    				shn_form_submit(_t('<< Back'),'name="back_button"');
    				shn_form_submit(_t("Next >>"));
    			}
    		}
    	}
    }

    shn_form_fclose();
}

/**
 * Generate the password policy configuration page.
 *
 * @param Integer $step_no The step number. Optional, if not provided will be taken from the session as $_SESSION['setup_step_no']
 */
function shn_setup_adv_pwd_policy($step_no=null)
{
	$step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];
	?>
    <h1><?php 
    echo _t("Sahaha Web Setup - Step ").$step_no;
    ?></h1>
    <?php
    display_errors();
    shn_form_fopen('adv_pwd_policy_submit');
    shn_form_fsopen(_t('Define a system wide password policy'));
    shn_form_text(_t('Minimum No of characters'),'pwd_min_chars','maxlength="2" size="2"',isset($_SESSION[SETUP_DATA_PREFIX."pwd_min_chars"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."pwd_min_chars"]):array('value'=>8));
    shn_form_text(_t('Maximum No of characters'),'pwd_max_chars','maxlength="2" size="2"',isset($_SESSION[SETUP_DATA_PREFIX."pwd_max_chars"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."pwd_max_chars"],'maxlength'=>2,'size'=>2):array('value'=>16,'maxlength'=>2,'size'=>2));
    shn_form_checkbox(_t('should contain uppercase characters'),'pwd_has_uppercase',isset($_SESSION[SETUP_DATA_PREFIX."pwd_has_uppercase"])?'checked="checked"':'');
    echo "<br/>";
    shn_form_checkbox(_t('should contain numbers'),'pwd_has_numbers',isset($_SESSION[SETUP_DATA_PREFIX."pwd_has_numbers"])?'checked="checked"':'');
    echo "<br/>";
    shn_form_checkbox(_t('should contain special characters'),'pwd_has_spchars',isset($_SESSION[SETUP_DATA_PREFIX."pwd_has_spchars"])?'checked="checked"':'');
    echo "<br/>";
    shn_form_checkbox(_t('should not contain the username'),'pwd_has_username',isset($_SESSION[SETUP_DATA_PREFIX."pwd_has_username"])?'checked="checked"':'');
    echo "<br/>";
    shn_form_checkbox(_t('should not contain repeating patterns'),'pwd_has_reppatterns',isset($_SESSION[SETUP_DATA_PREFIX."pwd_has_reppatterns"])?'checked="checked"':'');
    shn_form_fsclose();
    shn_form_submit(_t('<< Back'),'name="back_button"');
    shn_form_submit(_t("Next >>"));
    shn_form_fclose();
}

/**
 * Generate the select scenario page.
 *
 * @param Integer $step_no The step number.
 */
/*
 function shn_setup_scen_select_scenario($step_no=null)
 {
 $step_no = isset($step_no)?$step_no:$_SESSION['setup_step_no'];

 $tick_img = 'theme/default/img/tic.png';
 $cross_img = 'theme/default/img/cross.png';

 $scenario_module_map = array(
 _t("Default")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Tsunami Wave/Surge")=>"admin,cms,cs,dvr,gis,home,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Forest  Fire")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,or,pref,rms,rs,sync,vm,vol",
 _t("Flood")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,or,pref,rms,rs,sync,vm,vol",
 _t("Hurricane")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,or,pref,rms,rs,sync,vm,vol",
 _t("Drought")=>"admin,cms,cs,gis,home,ims,mpr,or,pref,rms,rs,sync,vm,vol",
 _t("Conflicts")=>"admin,cms,cr,cs,dvr,gis,home,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Epidemic")=>"admin,cms,cr,cs,dvr,gis,home,ims,pref,rms,rs,sync,vm,vol",
 _t("Earthquake")=>"admin,cms,cr,cs,dvr,gis,home,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Insect Infestation")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Nuclear/Chemical Hazard")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Famine")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Land Slide")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 _t("Volcano")=>"admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,or,pref,rms,rs,sync,vm,vol",
 );

 //ksort(&$scenario_module_map);
 ?>
 <h1><?php
 echo _t("Sahaha Web Setup - Step ").$step_no;
 ?></h1>
 <?php
 display_errors();
 shn_form_fopen('SCEN_SELECT_SCEN');
 shn_form_fsopen(_t('Select a scenario.'));

 shn_form_select(array_flip($scenario_module_map),_t("Scenario"),'selected_scenario','onchange="tickModules(this)"',isset($_SESSION[SETUP_DATA_PREFIX."selected_scenario"])?array('value'=>$_SESSION[SETUP_DATA_PREFIX."selected_scenario"]):array('value'=>'admin,cms,cr,cs,dvr,gis,home,hr,ims,mpr,msg,pref,rms,rs,skel,sync,vm,vol,ws'));
 shn_form_fsclose();
 shn_form_submit(_t('<< Back'),'name="back_button"');
 shn_form_submit(_t("Next >>"));
 shn_form_submit(_t('Customize'),'name="scenario_customize"');
 ?>
 <br />
 <br />
 <?php
 shn_form_fsopen("Selected Modules");

 // load configuration
 shn_config_module_conf_fetch('all');

 $all_modules = shn_get_all_modules();
 asort($all_modules);

 $_essencial_modules = _shn_setup_get_essencial_modules();
 $_essencial_mod_str = implode(",",$_essencial_modules);

 ?>
 <div id="modulePreview"><script type="text/javascript"
 language="javascript">
 <!--
 var tickImg = "<?php echo $tick_img; ?>";
 var crossImg = "<?php echo $cross_img; ?>";
 var essentialModules = "<?php echo $_essencial_mod_str; ?>";

 function tickModules(selectBox){
 var mods = selectBox.options[selectBox.selectedIndex].value;

 mods += (","+essentialModules);
 mods = mods.split(",");

 var allImgTags = document.getElementsByTagName("img");
 for(i=0;i<allImgTags.length;i++){
 var tagId = allImgTags[i].id;
 var tag = allImgTags[i];
 if(tagId && tagId.indexOf("img_")==0){
 tag.src = crossImg;
 }
 }
 for(i=0;i<mods.length;i++){
 var imgElem = document.getElementById("img_"+mods[i]);
 if(imgElem){
 imgElem.src = tickImg;
 }
 }
 }

 var modTable = '<?php
 echo "<table class=\"layout\">";
 foreach($all_modules as $key=>$value){
 echo "<tr><td>";
 echo $value[1];
 echo "</td><td>";
 echo '<img id="img_'.$value[0].'" align="top" src="'.$tick_img.'" alt="tick"/>';
 echo "</td><tr>";

 }
 echo "</table>"; ?>';
 // append if javascript is enabled.
 document.getElementById("modulePreview").innerHTML = modTable;
 -->
 </script>
 <noscript>
 <p><?php echo _t("Module preview is not available without javascript."); ?></p>
 </noscript>
 </div>
 <?php
 shn_form_fsclose();
 shn_form_fclose();
 }
 */
/**
 * Generate the complete setup page.
 *
 */
function shn_setup_complete()
{
	global $global;
	$oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';
	?>
    <h1><?php 
    echo _t("Sahaha Web Setup - Step ").$step_no;
    ?></h1>
    <?php
    display_errors();
    shn_form_fopen('default','admin',array('req_message' => false));
    shn_form_fsopen(_t('Starting Sahana'));

    $sahana_url = 'http://'.$_SERVER['HTTP_HOST'].preg_replace('/index.php\?.*$/','',$_SERVER['REQUEST_URI']);
    shn_form_hidden(array('shn_url'=>$sahana_url));

    if (is_writeable($global['approot'].'conf')) {
    	?>
    <p><b><u><?php echo $oops_img._t('WARNING: Security')?></u></b></p>
    <p><?php echo _t('To secure the configuration you have to remove write 
                 permissions from the configuration file sysconf.inc.php located in 
                 the Sahana directory conf/');?></p>

    <p><?php echo _t('Click the button below to start Sahana');?> <?php
    }
    shn_form_fsclose();
    shn_form_submit(_t('Start Sahana'));
    session_destroy();
    shn_form_fclose();
}

/**
 * Show any errors occurred during setup and an option to restart the setup.
 *
 */
function shn_setup_error()
{
	global $global;
	?>
    <h1><?php
    echo _t("Setup Error");
    ?></h1>
    <?php
    display_errors();
    shn_form_fopen('default','admin',array('req_message' => false));
    shn_form_fsopen(_t('Restart Setup'));
    ?>
    <p><?php echo _t('Click the button below to restart the setup.');?></p>
    <?php
    shn_form_fsclose();
    shn_form_submit(_t('Restart Setup'));
    session_destroy();
    shn_form_fclose();
}

/**
 * Generate the Sahana Header
 *
 */
function shn_setup_header()
{
	?>
<body>
<div id="container"><?php 
shn_include_page_section('header',$module);
?>
<div id="wrapper" class="clearfix">
<div id="content" class="clearfix"><?php
}

/**
 * Generate the Sahana Footer
 *
 */
function shn_setup_footer()
{
	?></div>
<!-- /content --> <?php
shn_include_page_section('footer',$module);
?></div>
<!-- /wrapper --></div>
<!-- /container -->
</body>
</html>
<?php
}

/**
 * Generate an error message page.
 *
 */
