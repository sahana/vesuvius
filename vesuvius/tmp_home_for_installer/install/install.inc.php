<?php

/**
 * Agasti 2.0 Installer
 *
 * PHP Version 5
 *
 * LICENSE: This source file is subject to LGPLv3.0 license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author Charles Wisniewski, CUNY SPS
 *
 * Copyright of the Sahana Software Foundation, sahanafoundation.org
 */
/**
 * Sahana Agasti 2.0 install.inc.php
 * this file houses installation specific functions, primarily called from install.php
 */
require_once (dirname(__FILE__) . '/lib/agasti_lib/agasti2.inc.php');
require_once(dirname(__FILE__) . '/lib/requirements.inc.php');
require_once (dirname(__FILE__) . '/lib/func.inc.php');


class appInstall extends Agasti
{
  /* protected *//*
    var $INS_CONFIG;
    var $DISABLE_NEXT;
    var $steps = array();
   */

  /* public */

  function __construct(&$INS_CONFIG)
  {
    $this->DISABLE_NEXT = FALSE;
    $this->RETRY_SUCCESS = FALSE;
    $this->SAVE_SUCCESS=FALSE;
    $this->ERROR_MESSAGE = '';
    $this->INSTALL_RESULT = '';

    $this->INS_CONFIG = &$INS_CONFIG;
    $Agasti=new Agasti($INS_CONFIG);

    $this->steps = $Agasti->getStepsArray();
    //echo count($this->steps);

    if(count($this->steps)==6){
        $this->MayonEventHandler();
    }

    if(count($this->steps)==7){
        $this->VesuviusEventHandler();
    }

    
    GLOBAL $trans;
    $trans = array(
//     requirements.inc.php
      'S_PHP_VERSION' => 'PHP version',
      'S_MINIMAL_VERSION_OF_PHP_IS' => 'Minimal version of PHP is',
      'S_PHP_MEMORY_LIMIT' => 'PHP memory limit',
      'S_IS_A_MINIMAL_PHP_MEMORY_LIMITATION_SMALL' => 'is a minimal PHP memory limitation',
      'S_PHP_POST_MAX_SIZE' => 'PHP post max size',
      'S_IS_A_MINIMUM_SIZE_OF_PHP_POST_SMALL' => 'is minimum size of PHP post',
      'S_PHP_MAX_EXECUTION_TIME' => 'PHP max execution time',
      'S_PHP_MAX_INPUT_TIME' => 'PHP max input time',
      'S_IS_A_MINIMAL_LIMITATION_EXECTUTION_TIME_SMALL' => 'is a minimal limitation on execution time of PHP scripts',
      'S_IS_A_MINIMAL_LIMITATION_INPUT_PARSE_TIME_SMALL' => 'is a minimal limitation on input parse time for PHP scripts',
      'S_PHP_TIMEZONE' => 'PHP timezone',
      'S_NO_SMALL' => 'no',
      'S_YES_SMALL' => 'yes',
      'S_TIMEZONE_FOR_PHP_IS_NOT_SET' => 'Timezone for PHP is not set',
      'S_PLEASE_SET' => 'Please set',
      'S_OPTION_IN_SMALL' => 'option in',
      'S_PHP_DATABASES_SUPPORT' => 'PHP databases support',
      'S_REQUIRES_ANY_DATABASE_SUPPORT' => 'Requires any database support [MySQL or PostgreSQL or Oracle or SQLite3]',
      'S_REQUIRES_BCMATH_MODULE' => 'Requires bcmath module',
      'S_CONFIGURE_PHP_WITH_SMALL' => 'configure PHP with',
      'S_REQUIRES_MB_STRING_MODULE' => 'Requires mb string module',
      'S_PHP_SOCKETS' => 'PHP Sockets',
      'S_REQUIRED_SOCKETS_MODULE' => 'Required Sockets module',
      'S_THE_GD_EXTENSION_IS_NOT_LOADED' => 'The GD extension is not loaded.',
      'S_GD_PNG_SUPPORT' => 'GD PNG Support',
      'S_REQUIRES_IMAGES_GENERATION_SUPPORT' => 'Requires images generation support',
      'S_LIBXML_MODULE' => 'libxml module',
      'S_PHPXML_MODULE_IS_NOT_INSTALLED' => 'php-xml module is not installed',
      'S_CTYPE_MODULE' => 'ctype module',
      'S_REQUIRES_CTYPE_MODULE' => 'Requires ctype module',
      'S_PHP_UPLOAD_MAX_FILESIZE' => 'PHP upload max filesize',
      'S_IS_MINIMAL_FOR_PHP_ULOAD_FILESIZE_SMALL' => 'is minimum for PHP upload filesize',
      'S_SESSION_MODULE' => 'PHP Session',
      'S_REQUIRED_SESSION_MODULE' => 'Required Session module',
    );
    foreach ($trans as $const => $label) {
      if (!defined($const))
        define($const, $label);
    }
    unset($GLOBALS['trans']);
  }

  function getConfig($name, $default = null)
  {
//if entry method to this function is admin/config instead of install, set the global
      if(isset($this->INS_CONFIG[$name])){
          $default=$this->INS_CONFIG[$name];
          return $default;
      }
      else
          return $default;
    //return isset($this->INS_CONFIG[$name]) ? $this->INS_CONFIG[$name] : $default;
  }

  function getSelected($arrayIndex,$default,$expected){

      if(is_int($default)){
        if($expected==$default){
          $value="selected=".$default;
          return $value;
        }
        else{
          return null;
        }
      }
      else{
        if($this->getConfig($arrayIndex,$default)==$expected){
          $value="selected=".$expected;
          return $value;
        }
        else{
          return null;
        }
      }
  }

  function setConfig($name, $value)
  {
    return ($this->INS_CONFIG[$name] = $value);
  }

  function getStep()
  {
    return $this->getConfig('step', 0);
  }

  function DoNext()
  {
    if (isset($this->steps[$this->getStep() + 1])) {
      $this->INS_CONFIG['step']++;
      return true;
    }
    return false;
  }

  function DoBack()
  {
    if (isset($this->steps[$this->getStep() - 1])) {
      $this->INS_CONFIG['step']--;
      return true;
    }
    return false;
  }

  function getList()
  {
    /**
     * this is a simple html constructor, takes our array and
     * generates a series of list items
     */
    $list = "<ul>";
    foreach ($this->steps as $id => $data) {
      if ($id < $this->getStep())
        $style = 'completed';
      else if ($id == $this->getStep())
        $style = 'current';
      else
        $style = null;

      $list = $list . '<li class="' . $style . '">' . $data['title'] . '</li>';
    }
    $list = $list . "</ul>";
    return $list;
  }

  function getState()
  {
    $fun = $this->steps[$this->getStep()]['fun'];
    return $this->$fun();
  }


  

  function MayonEventHandler()
  {
      //echo "this is event handler";
    if (isset($_REQUEST['back'][$this->getStep()])){
      $this->DoBack();
      //echo "Doing the back step";
      }

    if ($this->getStep() == 1) {
      if (!isset($_REQUEST['next'][0]) && !isset($_REQUEST['back'][2])) {
        $this->setConfig('agree', isset($_REQUEST['agree']));
        //$this->doNext();
      }

      if (isset($_REQUEST['next'][$this->getStep()]) && $this->getConfig('agree', false)) {
        $this->DoNext();
      }
    }

    $foo = $this->getStep();
    $zoo = $_REQUEST['next'][$this->getStep()];
    $poo = $_REQUEST['problem'];

    if ($this->getStep() == 2 && isset($_REQUEST['next'][$this->getStep()]) && !isset($_REQUEST['problem'])) {
      $this->dbParams($db_params);
      $this->DoNext();
    }
    if ($this->getStep() == 3) {
//on our first pass, these values won't exist (or if someone has returned with no POST
      $current = $this->getCurrent();
      $db_params = array(
        'dsn' => buildDsnString('mysql', $_POST['db_host'], $_POST['db_name']), // ilya 2010-07-21 15:16:58
//'dsn' => buildDsnString($_POST['db_type'], $_POST['db_host'], $_POST['db_name'], $_POST['db_port']),
        'hostname'=>$_POST['db_host'],
        'dbname'=>$_POST['db_name'],
        'username' => $_POST['db_user'],
        'password' => $_POST['db_pass']);
      $this->setConfig('DB_SERVER', $_POST['db_host']);
      $this->setConfig('DB_DATABASE', $_POST['db_name']);
      $this->setConfig('DB_USER', $_POST['db_user']);
      $this->setConfig('DB_PASSWORD', $_POST['db_pass']);
      $this->setConfig('ADMIN_NAME', $_POST['admin_name']);
      $this->setConfig('ADMIN_EMAIL', $_POST['admin_email']);
      $config_array = array(
        'is_installed' => array('value' => 'true'),
        'sudo' => array(
          'super_user' => $current[1]['sudo']['super_user'],
          'super_pass' => $current[1]['sudo']['super_pass']),
        'admin' => array(
          'admin_name' => $this->getConfig('ADMIN_NAME'),
          'admin_email' => $this->getConfig('ADMIN_EMAIL'),
          'auth_method' => array('value' => 'bypass'),
          'log_level' => array('value' => 'default'),
        //'db_type' => $_POST['db_type'],
//'db_host' => $_POST['db_host'],
//'db_name' => $_POST['db_port'], //ilya 2010-07-21 15:17:13
          ));
//we've set our config to post values, now let's try to save
//appSaveSetup only saves config.yml and app.yml, databases.yml is not touched
//to save our databases.yml,
//$this->dbParams($db_params);
//database parameters are good here.
      if (!($this->appSaveSetup($config_array))) {
        $this->DISABLE_NEXT = true;
        unset($_REQUEST['next']);
//if we cannot save our configuration
      } else {
        $dbcheck = $this->CheckConnection($db_params);
        if ($dbcheck == 'good') {
          $this->RETRY_SUCCESS = true;
        } else {
//if we cannot establish a db connection
          $this->RETRY_SUCCESS = false;
          $this->DISABLE_NEXT = true;
          $this->ERROR_MESSAGE = $dbcheck;
//set the installer's global error message to the return of our connection attempt
          unset($_REQUEST['next']);
        }
      }
      if (isset($_REQUEST['next'][$this->getStep()])) {
//the validation comment below can be handled by:
//$this->getCurrent();
        $this->setConfig('db_config', $db_params);
        $this->setConfig('DB_SERVER', $_POST['db_host']);
        $this->setConfig('DB_DATABASE', $_POST['db_name']);
        $this->setConfig('DB_USER', $_POST['db_user']);
        $this->setConfig('DB_PASSWORD', $_POST['db_pass']);
        $this->setConfig('ADMIN_NAME', $_POST['admin_name']);
        $this->setConfig('ADMIN_EMAIL', $_POST['admin_email']);
        $this->DoNext();
//we should validate here in case someone changes correct information
      }
    }

    if ($this->getStep() == 4) {
//present user with configuration settings, show 'install button'
      if (isset($_REQUEST['next'][$this->getStep()])) {
        //$this->INSTALL_RESULT = $this->doInstall($this->getConfig('db_config'));
        $this->INSTALL_RESULT ='Success!';
        $this->DoNext();
      }
    }
    if (isset($_REQUEST['finish'])) {       //isset($_REQUEST['next'][$this->getStep()]
//$this->doNext();
      $sudo = $this->getCurrent();
      $sudoer = $sudo[1]['sudo']['super_user']; //get username and password from config.yml, should be cleaner.
      $supw = $sudo[1]['sudo']['super_pass'];
//authenticate with this
      try {
        $configuration = ProjectConfiguration::getApplicationConfiguration('frontend', 'all', false);
        $databaseManager = new DatabaseManager($configuration);
//        $connection = Doctrine_Manager::connection()->connect();
        sfContext::createInstance($configuration)->dispatch();
        agSudoAuth::authenticate($sudoer, $supw);
        redirect('admin/new');
      } catch (Exception $e) {
        $this->ERROR_MESSAGE = $e->getMessage();
      }
      return;
    }

    if (isset($_REQUEST['next'][$this->getStep()])) {
      $this->DoNext();
    }
  }

  function VesuviusEventHandler(){
	$db_params = array(
        'dbengine'=>"",
        'storageengine'=>"",
        'hostname'=>"",
        'dbport'=>"",
        'dbname'=>"",
        'username' => "",
        'password' => "");
      $system_params=array(
            'base_uuid'=>"",
            'theme'=>"",
            'enable_locale'=>"",
            'locale'=>"",
            'enable_plus_web_services'=>"",
            'pwd_min_chars'=>"",
            'pwd_max_chars'=>"",
            'pwd_has_uppercase'=>"",
            'pwd_has_lowercase'=>"",
            'pwd_has_numbers'=>"",
            'pwd_has_spchars'=>"",
            'pwd_has_username'=>"",
            'pwd_no_change_limit'=>""
        );
      $db_engine="";
      $storage_engine="";
      $db_host="";
      $db_port="";
      $db_name="";
      $db_user="";
      $db_pass="";
      $base_uuid="";
      $theme="";
      $enable_locale="";
      $locale="";
      $enable_plus_web_services="";
      $pwd_min_chars="";
      $pwd_max_chars="";
      $pwd_has_uppercase="";
      $pwd_has_lowercase="";
      $pwd_has_numbers="";
      $pwd_has_spchars="";
      $pwd_has_username="";
      $pwd_no_change_limit="";

      if (isset($_REQUEST['back'][$this->getStep()])){
        $this->DoBack();
      //echo "Doing the back step";
      }

      if ($this->getStep() == 1) {
      if (!isset($_REQUEST['next'][0]) && !isset($_REQUEST['back'][2])) {
        $this->setConfig('agree', isset($_REQUEST['agree']));
        //$this->doNext();
      }

      if (isset($_REQUEST['next'][$this->getStep()]) && $this->getConfig('agree', false)) {
        $this->DoNext();
      }
    }

    //$foo = $this->getStep();
    //$zoo = $_REQUEST['next'][$this->getStep()];
    //$poo = $_REQUEST['problem'];

    if ($this->getStep() == 2 && isset($_REQUEST['next'][$this->getStep()]) && !isset($_REQUEST['problem'])) {
      $this->dbParams($db_params);
      $this->DoNext();
    }

    if ($this->getStep() == 3) {
//on our first pass, these values won't exist (or if someone has returned with no POST
      $current = $this->getCurrent();
      if(isset ($_POST['db_engine'])){
          $db_engine=$_POST['db_engine'];
      }
      if(isset ($_POST['storage_engine'])){
          $storage_engine=$_POST['storage_engine'];
      }
      if(isset ($_POST['db_host'])){
          $db_host=$_POST['db_host'];
      }
      if(isset ($_POST['db_port'])){
          $db_port=$_POST['db_port'];
      }
      if(isset ($_POST['db_name'])){
          $db_name=$_POST['db_name'];
      }
      if(isset ($_POST['db_user'])){
          $db_user=$_POST['db_user'];
      }
      if(isset ($_POST['db_pass'])){
          $db_pass=$_POST['db_pass'];
      }
      $db_params['dbengine']=$db_engine;
      $db_params['storageengine']=$storage_engine;
      $db_params['hostname']=$db_host;
      $db_params['dbport']=$db_port;
      $db_params['dbname']=$db_name;
      $db_params['username'] = $db_user;
      $db_params['password'] = $db_pass;

      $this->setConfig('DB_ENGINE',$db_engine);
      $this->setConfig('DB_STORAGE_ENGINE',$storage_engine);
      $this->setConfig('DB_SERVER', $db_host);//
      $this->setConfig('DB_PORT',$db_port );//
      $this->setConfig('DB_DATABASE', $db_name);//
      $this->setConfig('DB_USER', $db_user);//
      $this->setConfig('DB_PASSWORD', $db_pass);//
      //$this->setConfig('ADMIN_NAME', $_POST['admin_name']);
      //$this->setConfig('ADMIN_EMAIL', $_POST['admin_email']);
      $htaccess = $this->getHtAccessArray();
//we've set our config to post values, now let's try to save
//appSaveSetup only saves config.yml and app.yml, databases.yml is not touched
//to save our databases.yml,
//$this->dbParams($db_params);
//database parameters are good here.
      if (!($this->appSaveSetup($htaccess))) {
        $this->DISABLE_NEXT = true;
        unset($_REQUEST['next']);
//if we cannot save our configuration
      } else {
        $dbcheck = $this->CheckConnection($db_params);
        if ($dbcheck == 'good') {
          $this->RETRY_SUCCESS = true;
        } else {
//if we cannot establish a db connection
          $this->RETRY_SUCCESS = false;
          $this->DISABLE_NEXT = true;
          $this->ERROR_MESSAGE = $dbcheck;
//set the installer's global error message to the return of our connection attempt
          unset($_REQUEST['next']);
        }
      }
      if (isset($_REQUEST['next'][$this->getStep()])) {
//the validation comment below can be handled by:
//$this->getCurrent();
        $this->setConfig('config', $current[0]);
        $this->setConfig('DB_ENGINE',$_POST['db_engine']);
        $this->setConfig('DB_STORAGE_ENGINE',$_POST['storage_engine']);
        $this->setConfig('DB_SERVER', $_POST['db_host']);
        $this->setConfig('DB_PORT', $_POST['db_port']);
        $this->setConfig('DB_DATABASE', $_POST['db_name']);
        $this->setConfig('DB_USER', $_POST['db_user']);
        $this->setConfig('DB_PASSWORD', $_POST['db_pass']);
        //$this->setConfig('ADMIN_NAME', $_POST['admin_name']);
        //$this->setConfig('ADMIN_EMAIL', $_POST['admin_email']);
        //$this->DoNext();
//we should validate here in case someone changes correct information
      }
    }

    if(($this->getStep() == 3) && (isset($_REQUEST['next'][$this->getStep()]))){
        $this->systemParams($system_params);
        $this->DoNext();
    }

    if ($this->getStep() == 4){
        $current = $this->getCurrent();
	if(isset ($_POST['base_uuid'])){
            $base_uuid=$_POST['base_uuid'];
        }
        if(isset ($_POST['theme'])){
            $theme=$_POST['theme'];
        }
        if(isset ($_POST['enable_locale'])){
            $enable_locale=$_POST['enable_locale'];
        }
        if(isset ($_POST['locale'])){
            $locale=$_POST['locale'];
        }
        if(isset ($_POST['enable_plus_web_services'])){
            $enable_plus_web_services=$_POST['enable_plus_web_services'];
        }
        if(isset ($_POST['pwd_min_chars'])){
            $pwd_min_chars=$_POST['pwd_min_chars'];
        }
        if(isset ($_POST['pwd_max_chars'])){
            $pwd_max_chars=$_POST['pwd_max_chars'];
        }
        if(isset ($_POST['pwd_has_uppercase'])){
            $pwd_has_uppercase=$_POST['pwd_has_uppercase'];
        }
        if(isset ($_POST['pwd_has_lowercase'])){
            $pwd_has_lowercase=$_POST['pwd_has_lowercase'];
        }
        if(isset ($_POST['pwd_has_numbers'])){
            $pwd_has_numbers=$_POST['pwd_has_numbers'];
        }
        if(isset ($_POST['pwd_has_spchars'])){
            $pwd_has_spchars=$_POST['pwd_has_spchars'];
        }
        if(isset ($_POST['pwd_has_username'])){
            $pwd_has_username=$_POST['pwd_has_username'];
        }
        if(isset ($_POST['pwd_no_change_limit'])){
            $pwd_no_change_limit=$_POST['pwd_no_change_limit'];
        }
        
	$system_params['base_uuid']=$base_uuid;
        $system_params['theme']=$theme;
        $system_params['enable_locale']=$enable_locale;
        $system_params['locale']=$locale;
        $system_params['enable_plus_web_services']=$enable_plus_web_services;
        $system_params['pwd_min_chars']=$pwd_min_chars;
        $system_params['pwd_max_chars']=$pwd_max_chars;
        $system_params['pwd_has_uppercase']=$pwd_has_uppercase;
        $system_params['pwd_has_lowercase']=$pwd_has_lowercase;
        $system_params['pwd_has_numbers']=$pwd_has_numbers;
        $system_params['pwd_has_spchars']=$pwd_has_spchars;
        $system_params['pwd_has_username']=$pwd_has_username;
        $system_params['pwd_no_change_limit']=$pwd_no_change_limit;

        $this->setConfig('BASE_UUID', $base_uuid);
        $this->setConfig('THEME', $theme);
        $this->setConfig('ENABLE_LOCALE', $enable_locale);
        $this->setConfig('LOCALE', $locale);
        $this->setConfig('ENABLE_PLUS_WEB_SERVICES', $enable_plus_web_services);
        $this->setConfig('PASSWORD_MIN_CHARS', $pwd_min_chars);
        $this->setConfig('PASSWORD_MAX_CHARS', $pwd_max_chars);
        $this->setConfig('PWD_HAS_UPPERCASE', $pwd_has_uppercase);
        $this->setConfig('PWD_HAS_LOWERCASE', $pwd_has_lowercase);
        $this->setConfig('PWD_HAS_NUMBERS', $pwd_has_numbers);
        $this->setConfig('PWD_HAS_SPCHARS', $pwd_has_spchars);
        $this->setConfig('PWD_HAS_USERNAME', $pwd_has_username);
        $this->setConfig('PWD_NO_CHANGE_LIMIT', $pwd_no_change_limit);

        $htaccess = $this->getHtAccessArray();

        if (!($this->appSaveSetup($htaccess))) {
        $this->DISABLE_NEXT = true;
        unset($_REQUEST['next']);

      } else {
        $paramcheck = $this->checkSystemParameters($system_params);
        if ($paramcheck == 'good') {
          $this->SAVE_SUCCESS = true;
        } else {

          $this->SAVE_SUCCESS = false;
          $this->DISABLE_NEXT = true;
          $this->ERROR_MESSAGE = $paramcheck;

          unset($_REQUEST['next']);
        }
      }

      if (isset($_REQUEST['next'][$this->getStep()])){
        $this->setConfig('config', $current[0]);
        $this->setConfig('BASE_UUID', $_POST['base_uuid']);
        $this->setConfig('THEME', $_POST['theme']);
        $this->setConfig('ENABLE_LOCALE', $_POST['enable_locale']);
        $this->setConfig('LOCALE', $_POST['locale']);
        $this->setConfig('ENABLE_PLUS_WEB_SERVICES', $_POST['enable_plus_web_services']);
        $this->setConfig('PASSWORD_MIN_CHARS', $_POST['pwd_min_chars']);
        $this->setConfig('PASSWORD_MAX_CHARS', $_POST['pwd_max_chars']);
        $this->setConfig('PWD_HAS_UPPERCASE', $_POST['pwd_has_uppercase']);
        $this->setConfig('PWD_HAS_LOWERCASE', $_POST['pwd_has_lowercase']);
        $this->setConfig('PWD_HAS_NUMBERS', $_POST['pwd_has_numbers']);
        $this->setConfig('PWD_HAS_SPCHARS', $_POST['pwd_has_spchars']);
        $this->setConfig('PWD_HAS_USERNAME', $_POST['pwd_has_username']);
        $this->setConfig('PWD_NO_CHANGE_LIMIT', $_POST['pwd_no_change_limit']);
        $this->DoNext();
      }
    }

    if ($this->getStep() == 5){
        if (isset($_REQUEST['next'][$this->getStep()])){
            $this->INSTALL_RESULT = $this->doInstall($this->getConfig('config'));
        }
        
    }


    if (isset($_REQUEST['next'][$this->getStep()])) {
      $this->DoNext();
    }


  }
  
}
