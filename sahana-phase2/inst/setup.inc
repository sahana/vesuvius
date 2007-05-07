<?php
/**
* Sahana web setup. Initially launched to setup the database and sahana configuration 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @author     Pradeeper http://www.linux.lk/~pradeeper
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

session_start();

if (!function_exists("gettext"))
{
    global $global;
    include_once ($global['approot'].'inc/lib_locale/lib_gettext.inc');
}

require_once ($global['approot'].'inc/handler_html_head.inc');
require_once ($global['approot'].'inc/lib_modules.inc'); 
require_once ($global['approot'].'inc/lib_form.inc'); 
require_once ($global['approot'].'inc/lib_errors.inc'); 
require_once ($global['approot'].'3rd/adodb/adodb.inc.php');
require_once ($global['approot'].'inc/lib_uuid.inc');
require_once ($global['approot'].'inc/lib_config.inc');
//require_once ($global['approot'].'inc/lib_locale/handler_locale.inc');

shn_setup_main();

// main setup switchboard 
function shn_setup_main()
{
    $action = $_GET['act'];
    $modify = array();

    // display nice header
    shn_setup_header();
    switch ($action) {

    case 'dependancy': // first setup form
        if (shn_setup_check_dependancy()) { // check if all the dependencies are fullfill
            shn_setup_form1();
        } else {
            display_errors();
            shn_setup_form_dependancy(); 
        }
      
        break;

    case 'dbsetup': // second setup form
        if (shn_setup_database()) { // check if database writing is a success
            shn_setup_form2();
            
        } else {
            display_errors();
            shn_setup_form1();
        }
        break;
        
    case 'cfgsetup': // third setup form

		shn_email_validate();// try to catch the invalid emailaddresses of "second settup form"
		
		if(!shn_setup_acl()){
			display_errors();
            shn_setup_form2();
            break;
		}
		
		if (shn_setup_config_update($_POST['conffile'])) { 
            // check if writing the file was a success
            shn_setup_form_conffile();
        } else {
            display_errors();
            shn_setup_form2();
        }
        break;

    default: 
        // first database setup form
        shn_setup_form_dependancy();

    }
    shn_setup_footer();
}

function shn_email_validate()
{
	$email = $_POST['root_email'];
	if((eregi("^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$", $email))||($email=="")) {
	// if email is a valid one then do nothing ;-)
	}
	else {
		echo "<b><font color=red>$email</font> is an Invalid email address!</b>";// this is till we come up some nice screen
		shn_setup_form2();
		break;
	}
}// end of shn_email_validate

function shn_setup_check_dependancy()
{
    global $global;

    $continue = true;

    if (!version_compare(phpversion(), '4.1', '>')) $continue = false;
    if (!extension_loaded('gd')) $continue = false;
    if (!extension_loaded('mysql')) $continue = false;
    if (!extension_loaded('gettext')) $continue = false;
    if (!is_writable($global['approot'].'www/tmp')) $continue = false;

    return $continue;
}

function shn_setup_form_dependancy()
{
    global $global;
    $isOK = true;
    $tick_img = '<img align="top" src="theme/default/img/tic.png"/>';
    $cross_img = '<img align="top" src="theme/default/img/cross.png"/>';
    $oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';
?>
    <h1><?=_('Sahana Web Setup - Step 1')?></h1>

    <p><?=_('Welcome to Sahana. Please follow the following steps to setup the Sahana system')?></p>

    <p><?=_('First we need to check if all the relevant dependencies for the Sahana system to be install are available on your system')?></p>
<?php

    shn_form_fopen(_('dependancy'));

    shn_form_fsopen(_('PHP libraries'));
?>
    <p><?=_('The following checks if all the relevant Sahana libraries are installed')?></p>
<?php
    
    $value = (version_compare(phpversion(), '4.1', '>'));
    $isOK &= $value;

    //if ($isOK) echo "is OK"; 
    if ($value) {
        shn_form_label(_('PHP Version'), $tick_img.phpversion()." is installed");
    } else {
        shn_form_label(_('PHP Version'), $cross_img.phpversion()." is installed");
        echo "<p><br/>$oops_img Sahana needs PHP version 4.1 or higher. Please upgrate your version of PHP</p>";
    }
   
    // Check if php-gd is loaded  
    $value = (extension_loaded('gd'));
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('PHP-GD Library'), $tick_img."installed");
    } else {
        shn_form_label(_('PHP-GD Library'), $cross_img."is not installed");
        echo "<p><br/>$oops_img Sahana needs PHP-GD for image manipulations. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
    }

    // Check if php-gettext is loaded
    $value = (extension_loaded('gettext'));
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('PHP-gettext Library'), $tick_img."installed");
    } else {
        shn_form_label(_('PHP-gettext Library'), $cross_img."is not installed");
        echo "<p><br/>$oops_img Sahana needs PHP-gettext for to support local languages. Please install PHP-GD and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
    }

    $value = (extension_loaded('mysql'));
    $isOK &= $value;

    if ($value) {
        shn_form_label(_('MySQL library'), $tick_img."installed");
    } else {
        shn_form_label(_('MySQL library'), $cross_img."is not installed");
        echo "<p><br/>$oops_img Sahana needs PHP-MySQL library and MySQL for database operation. Please install PHP-MySQL library and MySQL and restart the webserver. To find out how to do this for your operating system see <a href=\"http://www.sahana.lk/wiki/doku.php?id=manual:install\">Sahana WIKI</a></p>";
    }

    shn_form_fsclose();
    shn_form_fsopen(_('File and Directory Permissions'));
?>
    <p><?=_('The following checks if certain files and sub-directories have write permissions for Sahana to function,')?></p>
<?php
    $tmpWritable = is_writable($global['approot'].'www/tmp');
    $isOK &= $tmpWritable;


    if ($tmpWritable) {
        //shn_form_label(_('Sahana www/tmp/ is writable?'),"The Sahana sub-directory writable");
        shn_form_label(_('<i>sahana/www/tmp/</i>'),"is <strong><font color=green>writable</font></strong>!<br>");
    } else {
        //shn_form_label(_('Sahana www/tmp/ is writable?'),"The Sahana sub-directory not writable");
        shn_form_label(_('<i>sahana/www/tmp/</i>'),"is <strong><font color=red>not writable</font></strong>!<br>");
        //echo "<p><br/>$oops_img The directory ".$global['approot']."www/tmp needs to be writable by the web server at least. Please change the permissions of this directory and try again.</p>";
    }

/* if ($value) {
        shn_form_label(_('Sahana www/tmp/ is writable?'), $tick_img."The Sahana sub-directory writable");
    } else {
        shn_form_label(_('Sahana www/tmp/ is writable?'), $cross_img."The Sahana sub-directory not writable");
        echo "<p><br/>$oops_img The directory ".$global['approot']."www/tmp needs to be writable by the web server at least. Please change the permissions of this directory and try again.</p>";
    }

/*   $value = (is_writable($global['approot'].'res/locale'))? 'checked':'';

    shn_form_checkbox('Sahana res/locale is writable?','write_locale',$value.' 
                        disabled="true"',array('value'=>'y','help'=>'hello')); 
*/
    $confWritable = is_writable($global['approot'].'conf');

    if ($confWritable) {
        //shn_form_label(_('Sahana www/conf/ is writable?'), $tick_img."The Sahana sub-directory writable");
        shn_form_label(_('<i>sahana/conf/</i>'),"is <strong><font color=green>writable</font></strong>!<br>");
    } else {
        //shn_form_label(_('Sahana www/conf/ is writable?'), "The Sahana sub-directory not writable");
        shn_form_label(_('<i>sahana/conf/</i>'),"is <strong><font color=red>not writable</font></strong>!<br>");
    }

    if (!$tmpWritable || !$confWritable) {
        $both = (!$tmpWritable && !$confWritable);

        echo "<p>Note: <font color=gray>" . (($both ? "both " : "")) . ((!$confWritable) ? "<strong>sahana/conf/</strong>" : "") . (($both) ? " and " : " ") . ((!$tmpWritable) ? "<strong>sahana/www/tmp/</strong>" : "") . " need" . ((!$both) ? "s" : "") . " to be writable by the web server at least. Please change the permissions of " . ((!$both) ? "this directory" : "these directories") . " and try again.</font></p>";
    }
    
    shn_form_fsclose();

    if ($isOK) {
        echo _('<p>All the dependencies are OK and you may move to
                the next step</p>')."\n";
        shn_form_submit(_('Next >>'));
    } else {
        echo _('<p>Please correct the required dependencies above and</p>')."\n";
        shn_form_submit(_('Try Again'));
    }
    shn_form_fclose();
}

// the database setup form
function shn_setup_form1()
{
 ?>
    <h2><?=_('Sahana Database Setup - Step 2')?></h2>
<?php

    shn_form_fopen('dbsetup');

    shn_form_fsopen(_('Database'));
    shn_form_select(
        array( 'mysql' => 'MySQL 4.1 or above','pgsql"disabled="disabled' => 'PostgreSQL'), 
                'Database Types', 'dbtype');
    shn_form_text(_('Database Host:Port'),'dbhost','size="30"',
                array('value'=>'localhost','req'=>true ));
    shn_form_text(_('Database Name'),'dbname','size="30"',
                array('value'=>'sahana', 'req'=>true));
    shn_form_text(_('Database User'),'dbuser','size="30"',
                array('value'=>'root', 'req'=>true));
    shn_form_password(_('Database Password'),'dbpass','size="30"', array('req'=>true));
    shn_form_fsclose();

    shn_form_fsopen(_('Schema\'s to Install'));
    // please add somedescription,
/*
    ?> <p><?=_('Check this to create the default categories for aid goods,units.')?></p> <?
*/
    shn_form_checkbox(_('Default Item Categories'),'dbsample','checked',
                        array('value'=>'y'));
                        // this 'help' is to be removed :
                        //, 'help'=>'Check this to 
                        //create the default categories for aid goods, units')); 
    shn_form_fsclose();
    shn_form_submit(_('Setup Database >>'));
 
    shn_form_fclose();
}


// the config file setup form
// the config file setup form
function shn_setup_form2()
{
 ?>
    <h1>Sahaha Web Setup - Step 3</h1>
    <p> Please follow the following steps to setup the Sahana configuration </p>
<?php
    global $global;

    shn_form_fopen('cfgsetup');
    
    // pass the previous post varibles into hidden for the configuration file
    shn_form_hidden( array(
        'dbhost' => $_POST['dbhost'] ,
        'dbname' => $_POST['dbname'] ,
        'dbuser' => $_POST['dbuser'] ,
        'dbpass' => $_POST['dbpass'] ));           

    shn_form_fsopen(_('Installation Details'));

    echo '<p>The following details are needed to uniquely identify your Sahana installation</p>'; // some spellings corrected by chamath 2007-03-15 09:50

    $help_txt = "The following field is randomly generated to help uniquely identify \
                 this Sahana installation. Please use this unless you have a \
                 convention defined";
    shn_form_text(_('Unique Installation ID'),'base_uuid','size="4" maxlength="4"',
                array('value'=> shn_generate_uuid(4),'req'=>true , 'help' => $help_txt));
    shn_form_text(_('Administrator Name'),'root_name','size="40"' );
    shn_form_text(_('Administrator Email'),'root_email','size="40"' );
    shn_form_text(_('Administrator Telephone'),'root_tel','size="30"' );

    shn_form_fsclose();

    shn_form_fsopen(_('Settings'));

    shn_form_select(
        array( 'disable' => _('Disable'),'enable' =>_('Enable')), 
                _('Access Control'),'acl');
    shn_form_select(
        array( 'default' => _('Default Theme'),
               'classic' => _('Classic Theme'),
               'green'   => _('Green Theme') 
             ), ('Theme'), 'theme');
    shn_form_fsclose();
    
    shn_form_fsopen(_('Administrator Account'));
    	shn_form_text(_('Admin User Name'),'admin_name','size="40"', array('req'=>true, 'value'=>'admin','help'=>'The root user is the administrator
                of the system and has the greatest privilages') );
	 	shn_form_password(_('Password'),'root_pwd','size="30"', 
        array('req'=>true));
        shn_form_password(_('Confirm Password'),'root_pwd_confirm','size="30"',array('req'=>true));
  	shn_form_fsclose();
	
	shn_form_fsopen(_('Create Normal User Account'));
        shn_form_text(_('Normal User Name'),'user_name','size="40"', array('req'=>true,'value'=>'sahana', 'help'=>'Please login as this user for non-admin work') );
		shn_form_password(_('Password'),'user_pwd','size="30"',array('req'=>true));
		shn_form_password(_('Confirm Password'),'user_pwd_confirm','size="30"',array('req'=>true));
	shn_form_fsclose();

    shn_form_fsopen(_('Configuration File'));

    if (is_writeable($global['approot'].'conf')) {
    
        echo '<p>The next step is to write the configuration file sysconf.inc in the Sahana /conf directory.</p>';

        shn_form_hidden(array('conffile' => 
            $global['approot'].'conf/sysconf.inc'));

    } else {

        echo '<p>The PHP/Web Server should normally not have access to write 
    or modify the configuration file located in Sahana application <b>/conf</b> 
    directory, as this is a security risk. Please specify where to write the temporary file (e.g. /tmp). Subsequently you need to move this file to 
    the Sahana <b>/conf</b> directory.</p>';

        $tmp_filename = tempnam('/tmp','sysconf.inc');
        // Need the temporary directory rather than the filename
        $tmp_filename = preg_replace('/sysconf.inc.*$/','sysconf.inc',
                        $tmp_filename); 

        shn_form_text(_('Location To Write Config File (sysconf.inc)'),
                'conffile','size="50"', array('value'=>"$tmp_filename",
                'req'=>true ));

    }
    shn_form_fsclose();

    shn_form_submit(_('Write Configuration File >>'));
 
    shn_form_fclose();
}


function shn_setup_form_conffile()
{
?>
    <h1><?=_('Sahaha Web Setup - Step 3')?></h1>
    <p><?=_('Configuration file ')?><?=$_POST['conffile']?> <?=_(' has been successfully written.')?></p>

<?php
    global $global;
    $oops_img = '<img align="bottom" src="theme/default/img/oops.png"/>';

    shn_form_fopen('default','admin',array('req_message' => false));
    shn_form_fsopen(_('Starting Sahana'));
    
    shn_form_hidden( array(
        'conffile' => $_POST['conffile'] )); 
    $sahana_url = 'http://'.$_SERVER['HTTP_HOST'].preg_replace('/index.php\?.*$/','',$_SERVER['REQUEST_URI']);

    if (is_writeable($global['approot'].'conf')) {
?>
    <p><b><u><?php echo $oops_img._('WARNING: Security')?></u></b></p>
    <p><?php echo _('To secure the configuration you have to remove write 
             permissions from the configuration file sysconf.inc located in 
             the Sahana directory conf/')?></p>

    <p><?=_('Click the button below to start Sahana')?>

<?php
    } else {
?>

    <p><?=_('To finish the configuration follow the steps below')?></p>
    <p> <b>1.</b><?=_(' Copy the temporary config file created from: ')?><br/>
        <u><?=$_POST['conffile']?></u> to: <br/>
     <u><?=$global['approot']."conf/sysconf.inc"?></u></p>
    <p> <b>2.</b><?=_(' For security reasons delete the temporary configuration file at ')?><u><?=$_POST['conffile']?></u></p>
    <p> <b>3.</b><?=_(' Once done click the button below to start Sahana or access it anytime using the url: ')?><a href="<?=$sahana_url?>"><?=$sahana_url?></a></p>

<?php        
    }
    shn_form_fsclose();
    shn_form_submit(_('Start Sahana'));    
    shn_form_fclose();
}

// connect to the database and run the scripts specified by the user
function shn_setup_database()
{
    global $global;

    $db = &NewADOConnection('mysql');
    if (! $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass']) ) {
        add_error(_('Could not connect to the database. Please check the setting and try again'));
        return false;
    }

    // create the main database
    $db->Execute("CREATE DATABASE IF NOT EXISTS ".$_POST['dbname']);
    $db->Connect($_POST['dbhost'],$_POST['dbuser'],$_POST['dbpass'],$_POST['dbname']);
    $global['db'] = $db;

    // setup the choosen sql scripts
    shn_setup_run_sqlscript($db,'inst/mysql-dbcreate.sql');
    shn_setup_run_sqlscript($db,'inst/mysql-acl.sql');
    shn_setup_run_sqlscript($db,'mod/rms/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/gis/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/cs/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/ims/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'mod/msg/ins/dbcreate.sql'); // patched by SriGaneshan 2007-03-11 23:42
    shn_setup_run_sqlscript($db,'mod/rs/ins/dbcreate.sql');
    shn_setup_run_sqlscript($db,'inst/mysql-config.sql');
    

    if ($_POST['dbsample']=='y') {
        include_once($global['approot'].'inc/lib_uuid.inc');
        shn_setup_run_sqlscript($db,'inst/mysql-sampledata.sql');
        include($global['approot'].'mod/cs/ins/setup.inc');
        shn_cs_datacreate();
    }

    return true;
}

// runs the script file relative to the approot
function shn_setup_run_sqlscript($db, $relative_script_path)
{
    global $global;

    $script = $global['approot'].$relative_script_path;

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
    // @todo error handler if file does not exist
}


function shn_setup_config_update($tmp_configfile)
{
    global $global;

    $modify = array( 
        '/\'theme\'/' => '$conf[\'theme\'] = \''.$_POST['theme'].'\';' ,
        '/\'db_host\'/' => '$conf[\'db_host\'] = \''.$_POST['dbhost'].'\';' ,
        '/\'db_name\'/' => '$conf[\'db_name\'] = \''.$_POST['dbname'].'\';' ,
        '/\'base_uuid\'/' => '$conf[\'base_uuid\'] = \''.$_POST['base_uuid'].'\';' ,
        '/\'root_name\'/' => '$conf[\'root_name\'] = \''.$_POST['root_name'].'\';' ,
        '/\'root_tel\'/' => '$conf[\'root_tel\'] = \''.$_POST['root_tel'].'\';' ,
        '/\'root_email\'/' => '$conf[\'root_email\'] = \''.$_POST['root_email'].'\';' ,
        '/\'db_user\'/' => '$conf[\'db_user\'] = \''.$_POST['dbuser'].'\';' ,
        '/\'db_pass\'/' => '$conf[\'db_pass\'] = \''.$_POST['dbpass'].'\';' );           

    if ( @shn_config_file_update( $modify, $global['approot'].'conf/sysconf.inc.tpl',
                            $tmp_configfile) ) {
        return true;
    } else {
        add_error(_('Could not write to file $tmp_configfile. Try another location'));
        return false;
    }
}

// install the ACL base
function shn_setup_acl(){
	$error=false;
	if ((null==$_POST["admin_name"])or(is_null($_POST["admin_name"]))){
        $error=true;
        add_error(_("Admin user name cannot be empty"));
	}
	if ((null==$_POST["root_pwd"])or(is_null($_POST["root_pwd"]))){
        $error=true;
        add_error(_("Root password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"root_pwd_confirm"});
    }
	if ((null==$_POST["root_pwd_confirm"])or(is_null($_POST["root_pwd_confirm"]))){
        $error=true;
        add_error(_("Root Confirm password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"root_pwd_confirm"});
    }
    if (!($_POST{"root_pwd"}==$re_password)){
        $error=true;
        add_error("Root password and confirm password should match");
    }
    if ((null==$_POST["user_name"])or(is_null($_POST["user_name"]))){
        $error=true;
        add_error(_("Normal user name cannot be empty"));
	}
    if ((null==$_POST["user_pwd"])or(is_null($_POST["user_pwd"]))){
        $error=true;
        add_error(_("User password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"user_pwd_confirm"});
    }
	if ((null==$_POST["user_pwd_confirm"])or(is_null($_POST["user_pwd_confirm"]))){
        $error=true;
        add_error(_("User Confirm password cannot be empty"));
    }else {    
        $re_password=trim($_POST{"user_pwd_confirm"});
    }
    if (!($_POST{"user_pwd"}==$re_password)){
        $error=true;
        add_error("User password and confirm password should match");
    }

    if($error){
		return false;
    }
    $_SESSION['dbhost']=null;
    $_SESSION['dbname']=null;
    $_SESSION['dbuser']=null;
    $_SESSION['dbpass']=null;
	$_SESSION['dbhost']=$_POST['dbhost'];
	$_SESSION['dbname']=$_POST['dbname'];
	$_SESSION['dbuser']=$_POST['dbuser'];
	$_SESSION['dbpass']=$_POST['dbpass'];
   	global $global;
    include_once $global['approot']. 'inc/lib_security/acl_api.inc';
	return (shn_acl_install(NULL));
	
}

function shn_setup_header() 
{
?>
    <body>
    <div id="container">
<?php 
    shn_include_page_section('header',$module);
?>
    <div id="wrapper" class="clearfix">
    <div id="content" class="clearfix">      
<?php
}

function shn_setup_footer()
{
?>
    </div> <!-- /content -->
<?php
    shn_include_page_section('footer',$module);
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php
}
