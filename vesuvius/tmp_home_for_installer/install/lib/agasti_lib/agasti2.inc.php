<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

require_once (dirname(__FILE__) . '/Config/Config.php');
require_once (dirname(__FILE__) . '/Config/Htaccess.php');


class Agasti{
    function __construct(&$INS_CONFIG){
        $this->INS_CONFIG=&$INS_CONFIG;
    }

    function getStepsArray(){
        $steps=array(
          0 => array('title' => '1. Introduction', 'fun' => 'stage0'),
          1 => array('title' => '2. License Agreement', 'fun' => 'stage1'),
          2 => array('title' => '3. Prerequisite Check', 'fun' => 'stage2'),
          3 => array('title' => '4. Configure Database', 'fun' => 'stage3'),
          4 => array('title' => '5. Configure System', 'fun' => 'stage4'),
          5 => array('title' => '6. Configuration Summary', 'fun' => 'stage5'),
          6 => array('title' => '7. Installation Summary', 'fun' => 'stage6'),
    //    7 => array('title' => '7. Enter Secure Mode', 'fun' => 'stage6' ),
        );

        return $steps;
    }

    function stage0()
    {
        return '<div class=info><h2>Welcome to the Sahana Agasti-Vesuvius Installation Wizard</h2><br />
          <p>Agasti is an emergency management application with tools to manage staff, resources,
          client information and facilities through an easy to use web interface. The Installation
          Wizard will guide you through the installation of Agasti 2.0.</p> <br />
          Click the "Next" button to proceed to the next screen. If you want to change something at
          a previous step, click the "Previous" button.  You may cancel installation at any time by
          clicking the "Cancel" button.</p>
          <p><b> Click the "Next" button to continue.</p></b></div>';
    }

    function stage1()
    {
        $LICENSE_FILE=$this->INS_CONFIG['rootpath'] .'/www/install/LICENSE';
        $this->DISABLE_NEXT = !$this->getConfig('agree', false);

        $license = 'Missing licence file. See GPL licence.';
        if (file_exists($LICENSE_FILE))
          $license = file_get_contents($LICENSE_FILE);


        $agree = '<input class="checkbox" type="checkbox" value="yes" name="agree" id="agree" onclick="submit();"';
        $this->getConfig('agree', false) == 'yes' ? $agree .= ' checked=checked>' : $agree .= '>';


        return '<div class=info>' . nl2br($license) . "</div><br />" . $agree . '<label for="agree">I agree</label>';
    }

    function stage2()
    {
        $table = '<table class="requirements" style="align:center; width:100%;">
                    <th><tr style="font-weight:bold;">
                      <td>Option</td><td>Current Value</td><td>Required</td><td>Recommended</td><td>&nbsp;</td></tr></th>';


        /**
         * @todo clean up the following code
         */
        $final_result = true;
        $requirementArray=array();
		$requirementArray[$this->INS_CONFIG['rootpath'].'/www/']='0777';
		$requirementArray[$this->INS_CONFIG['rootpath'].'/conf/']='0777';
        $requirementArray[$this->INS_CONFIG['rootpath'].'/www/install/']='0777';
        $requirementArray[$this->INS_CONFIG['rootpath'].'/backups/']='0775';
		$requirementArray[$this->INS_CONFIG['rootpath'].'/3rd/']='0777';

        $reqs = check_php_requirements($requirementArray);
        foreach ($reqs as $req) {

          $result = null;
          if (!is_null($req['recommended']) && ($req['result'] == 1)) {
            $result = '<span class="orange">Ok</span>';
          } else if ((!is_null($req['recommended']) && ($req['result'] == 2))
              || (is_null($req['recommended']) && ($req['result'] == 1))) {
            $result = '<span class="green">Ok</span>';
          } else if ($req['result'] == 0) {
            $result = '<span class="fail">Fail</span>';
        // this will be useful$result->setHint($req['error']);
          }

          $current = '<tr><td><strong>' . $req['name'] . '</strong></td>' . '<td>' . $req['current'] . '</td>';
          $required = $req['required'] ? $req['required'] : '&nbsp;';
          $recommend = $req['recommended'] ? $req['recommended'] : '&nbsp;';
          $res = $req['result'] ? '&nbsp;' : 'fail';
          $row = '<td>' . $current . '</td><td>' . $required . '</td><td>' . $recommend . '</td><td>' . $result . '</td>';

          $table = $table . $row . '</tr>';

          $final_result &= (bool) $req['result'];
        }

        if (!$final_result) {
          $this->DISABLE_NEXT = true;

          $retry = '<input type="submit" class="inputGray" id="retry" name="retry" value="retry" />';
          $final_result = '<span class="fail">There are errors in your configuration.
            Please correct all issues and press the "retry" button.  For additional assistance
            reference the README file.</span><br /><br />' . $retry;
        } else {
          $this->DISABLE_NEXT = false;
          $final_result = '<span class="green">Your system is properly configured.  Please continue.</span>';
        }

        return $table . '</table><br />' . $final_result;
    }


    function stage3()
  {
    global $INS_CONFIG;
    $this->getCurrent();

    if (isset($_REQUEST['retry']) && $this->RETRY_SUCCESS == false) {
      $retry_label = 'retry';
      $instruct = '<span class="fail">Error</span><br />
      <br />Error Message:' . $this->ERROR_MESSAGE . '<br /><span class="fail">Please correct the
        error and press retry.</span>';
    } else if ($this->RETRY_SUCCESS == false) {
      $retry_label = 'test connection';
      $instruct = 'Press "Test connection" button when done.';
    } else {
      $instruct = 'Database Settings are <span class="green">Ok</span> please click next';
    }
    $retry = '';
    if ($this->RETRY_SUCCESS == false) {
      $retry = '<input type="submit" class="linkButton" id="retry" name="retry" value="' . $retry_label . '" />';
    }
    $table = '<fieldset>
              <legend><img src="images/database.png" alt="database icon" />Database Configuration:</legend>

              <ul>
                <li>
                  <label>Database Engine:</label>
                  <select name="db_engine" class="inputGray">
                  <option value="mysql">MySQL</option>
                  </select>
                </li>
                <li>
                  <label>Storage Engine:</label>
                  <select name="storage_engine" class="inputGray" size="1">
                  <option value="innodb" '.$this->getSelected('DB_STORAGE_ENGINE','innodb','innodb').'>InnoDB</option>
                  <option value="myisam" '.$this->getSelected('DB_STORAGE_ENGINE','innodb','myisam').'>MyIsam</option>
                  </select>
                </li>
                <li>
                  <label>Host:</label>
                  <input type="text" name="db_host" id="db_host" class="inputGray"
                         value="' . $this->getConfig('DB_SERVER', 'localhost') . '"/>
                </li>
                <li>
                  <label>Port:</label>
                  <input type="text" name="db_port" id="db_port" class="inputGray"
                         value="' . $this->getConfig('DB_PORT', '3306') . '" />
                </li>
                <li>
                  <label>Database:</label>
                  <input type="text" name="db_name" id="db_name" class="inputGray"
                         value="' . $this->getConfig('DB_DATABASE', 'agasti23') . '" />
                </li>
                <li>
                  <label>Username:</label>
                  <input type="text" name="db_user" id="db_user" class="inputGray"
                         value="' . $this->getConfig('DB_USER', 'root') . '" />
                </li>
                <li>
                  <label>Password:</label>
                  <input type="password" name="db_pass" id="db_pass" class="inputGray"
                         value="' . $this->getConfig('DB_PASSWORD', 'root') . '" />
                </li>
                <input id="init_schema" type="hidden" name="init_schema" checked="checked" />
                </ul>
            </fieldset>';
    $results = 'The database is created manually.  First, the Vesuvius Installer will test your
      configuration settings before continuing.  Enter your database settings and click "Test Connection". <br /><br/>'
        . $instruct . $table . $retry;

    return $results;
  }

  function stage4(){
      global $INS_CONFIG;
      $this->getCurrent();
      $password_length=array();
      for($i=8;$i<17;$i++){
          $password_length[$i-8]=$i;
      }
      $password_min_length=intval($this->getConfig('PASSWORD_MIN_CHARS',8));
      $password_max_length=intval($this->getConfig('PASSWORD_MAX_CHARS',8));

    if (isset($_REQUEST['retry_saving']) && $this->SAVE_SUCCESS == false) {
      $retry_label = 'retry saving';
      $instruct = '<span class="fail">Error in saving System Configuration</span><br />
      <br />Error Message:' . $this->ERROR_MESSAGE . '<br /><span class="fail">Please correct the
        error and press retry.</span>';
    } else if ($this->SAVE_SUCCESS == false) {
      $retry_label = 'Save System configuration';
      $instruct = 'Press "Save System configuration" button when done.';
    } else {
      $instruct = 'System configuration saved <span class="green">successfully</span> please click next';
    }
    $retry = '';
    if ($this->SAVE_SUCCESS == false) {
      $retry = '<input type="submit" class="linkButton" id="retry_saving" name="retry_saving" value="' . $retry_label . '" />';
    }
    $table = '<fieldset>
              <legend>System Configuration:</legend>

              <ul>
                <li>
                  <label>Base Identifier:</label>
                  <input type="text" name="base_uuid" id="base_uuid" class="inputGray"
                         value="' . $this->getConfig('BASE_UUID', 'localhost') . '"/>
                </li>
                <li>
                  <label>Theme:</label>
                  <select name="theme" class="inputGray" size="1">
                  <option value="vesuvius" '.$this->getSelected('THEME','vesuvius','vesuvius').'>Vesuvius</option>
                  <option value="lpf3" '.$this->getSelected('THEME','vesuvius','lpf3').'>Lpf3</option>
                  </select>
                </li>
                <li>
                  <label>Enable Locale:</label>
                  <select name="enable_locale" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('ENABLE_LOCALE','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('ENABLE_LOCALE','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Locale:</label>
                  <select name="locale" class="inputGray" size="1">
                  <option value="en_US" '.$this->getSelected('LOCALE','en_US','en_US').'>English</option>
                  </select>
                </li>
                <li>
                  <label>Web Services via PLUS Module:</label>
                  <select name="enable_plus_web_services" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('ENABLE_PLUS_WEB_SERVICES','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('ENABLE_PLUS_WEB_SERVICES','true','false').'>False</option>
                  </select>
                </li>
                <input id="init_schema" type="hidden" name="init_schema" checked="checked" />
                </ul>
            </fieldset>
            <fieldset>
              <legend>Password Policy:</legend>
              <ul>
                <li>
                  <label>Password Min Length:</label>
                  <select name="pwd_min_chars" class="inputGray" size="1">
                  '.self::generateValues('PASSWORD_MIN_CHARS',$password_length,$password_min_length).'
                  </select>
                </li>
                <li>
                  <label>Password Max Length:</label>
                  <select name="pwd_max_chars" class="inputGray" size="1">
                  '.self::generateValues('PASSWORD_MAX_CHARS',$password_length,$password_max_length).'
                  </select>
                </li>
                <li>
                  <label>Password has Uppercase Letters:</label>
                  <select name="pwd_has_uppercase" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_HAS_UPPERCASE','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_HAS_UPPERCASE','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Password has Lowercase Letters:</label>
                  <select name="pwd_has_lowercase" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_HAS_LOWERCASE','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_HAS_LOWERCASE','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Password has Numbers:</label>
                  <select name="pwd_has_numbers" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_HAS_NUMBERS','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_HAS_NUMBERS','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Password has Special Characters:</label>
                  <select name="pwd_has_spchars" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_HAS_SPCHARS','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_HAS_SPCHARS','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Password has Username:</label>
                  <select name="pwd_has_username" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_HAS_USERNAME','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_HAS_USERNAME','true','false').'>False</option>
                  </select>
                </li>
                <li>
                  <label>Password has no Change Limit:</label>
                  <select name="pwd_no_change_limit" class="inputGray" size="1">
                  <option value="true" '.$this->getSelected('PWD_NO_CHANGE_LIMIT','true','true').'>True</option>
                  <option value="false" '.$this->getSelected('PWD_NO_CHANGE_LIMIT','true','false').'>False</option>
                  </select>
                </li>
              </ul>
            </fieldset>';
    $results = 'Enter your system configuration settings and click "Save System configuration". <br /><br/>'
        . $instruct . $table . $retry;

    return $results;
  }

  function stage5(){
      $current = $this->getCurrent();

      return 'Below is your installation configuration summary:<br />
          <strong>Database Configuration Summary:</strong>
        <div class="info">
        <strong>Database Engine</strong>:'.$this->getConfig('DB_ENGINE').
    '<br/><strong>Database Storage Engine</strong>:'.$this->getConfig('DB_STORAGE_ENGINE').
    '<br /><strong>Database Host</strong>: ' . $this->getConfig('DB_SERVER') .
    '<br /><strong>Database Port</strong>:'.$this->getConfig('DB_PORT').
    '<br /><strong>Database Name</strong>: ' . $this->getConfig('DB_DATABASE') .
    '<br /><strong>Database User</strong>: ' . $this->getConfig('DB_USER') .
    '<br /><strong>Database Password</strong>: ' . preg_replace('/./', '*', $this->getConfig('DB_PASSWORD', 'unknown')) .
    '</div><br/>
        <strong>System Configuration Summary:</strong>
        <div class="info">
        <strong>Base Identifier</strong>:'.$this->getConfig('BASE_UUID').
    '<br /><strong>Theme</strong>:'.$this->getConfig('THEME').
    '<br /><strong>Enable Locale</strong>:'.$this->getConfig('ENABLE_LOCALE').
    '<br /><strong>Locale</strong>:'.$this->getConfig('LOCALE').
    '<br /><strong>Web Services via PLUS Module</strong>:'.$this->getConfig('ENABLE_PLUS_WEB_SERVICES').
    '<br /><strong>Password Minimum Length</strong>:'.$this->getConfig('PASSWORD_MIN_CHARS').
    '<br /><strong>Password Maximum Length</strong>:'.$this->getConfig('PASSWORD_MAX_CHARS').
    '<br /><strong>Password has Uppercase Letters</strong>:'.$this->getConfig('PWD_HAS_UPPERCASE').
    '<br /><strong>Password has Lowercase Letters</strong>:'.$this->getConfig('PWD_HAS_LOWERCASE').
    '<br /><strong>Password has Numbers</strong>:'.$this->getConfig('PWD_HAS_NUMBERS').
    '<br /><strong>Password has Special Characters</strong>:'.$this->getConfig('PWD_HAS_SPCHARS').
    '<br /><strong>Password has Username</strong>:'.$this->getConfig('PWD_HAS_USERNAME').
    '<br /><strong>Password has no Change Limit</strong>:'.$this->getConfig('PWD_NO_CHANGE_LIMIT').
    '</div><br /> Please verify your settings.  By clicking next you will install Sahana Vesuvius.';
  }

  function stage6(){
      return '<span class="okay">Installation Results</span><br/><div class="info">' . $this->INSTALL_RESULT . '</div>';
  }

  function generateValues($array_index,$password_length_array,$expected_value){
      $generatedVal='';
      foreach($password_length_array as $key=>$value){
          $generatedVal.='<option value='.$value.' '.$this->getSelected($array_index,$value,$expected_value).'>'.$value.'</option>';
      }
      return $generatedVal;
  }
  


    function dbParams($db_params)
    {
	global $INS_CONFIG;
       $filePath=$INS_CONFIG['rootpath'].'/conf/sahana.conf';
       //if($db_params['hostname']!=''){
            $arguments = $this->getConfigArray();
            $arguments['db_name']=$db_params['dbname'];
            $arguments['db_host']=$db_params['hostname'];
            $arguments['db_port']=$db_params['dbport'];
            $arguments['db_user']=$db_params['username'];
            $arguments['db_pass']=$db_params['password'];
            $arguments['db_engine']=$db_params['dbengine'];
            $arguments['storage_engine']=$db_params['storageengine'];


            $configFile=new ConfigurationFileTask();
            $configFile->execute($arguments,$filePath);
       //}
        

    }

    function systemParams($system_params){
        global $INS_CONFIG;
	$filePath=$INS_CONFIG['rootpath'].'/conf/sahana.conf';
        if($system_params['base_uuid']!=''){
            $arguments = $this->getConfigArray();
            $arguments['db_name']=$this->getConfig('DB_DATABASE','agasti23');
            $arguments['db_host']=$this->getConfig('DB_SERVER','localhost');
            $arguments['db_port']=$this->getConfig('DB_PORT','3306');
            $arguments['db_user']=$this->getConfig('DB_USER','root');
            $arguments['db_pass']=$this->getConfig('DB_PASSWORD','root');
            $arguments['db_engine']=$this->getConfig('DB_ENGINE','mysql');
            $arguments['storage_engine']=$this->getConfig('DB_STORAGE_ENGINE','innodb');
            $arguments['base_uuid']=$system_params['base_uuid'];
            $arguments['theme']=$system_params['theme'];
            $arguments['enable_locale']=$system_params['enable_locale'];
            $arguments['locale']=$system_params['locale'];
            $arguments['pwd_min_chars']=intval($system_params['pwd_min_chars']);
            $arguments['pwd_max_chars']=intval($system_params['pwd_max_chars']);
            $arguments['pwd_has_uppercase']=$system_params['pwd_has_uppercase'];
            $arguments['pwd_has_lowercase']=$system_params['pwd_has_lowercase'];
            $arguments['pwd_has_numbers']=$system_params['pwd_has_numbers'];
            $arguments['pwd_has_spchars']=$system_params['pwd_has_spchars'];
            $arguments['pwd_has_username']=$system_params['pwd_has_username'];
            $arguments['pwd_no_change_limit']=$system_params['pwd_no_change_limit'];
            $arguments['enable_plus_web_services']=$system_params['enable_plus_web_services'];

            $configFile=new ConfigurationFileTask();
            $configFile->execute($arguments,$filePath);
        }
        

    }

    function getConfigArray(){
        $config=array(
            'base_uuid'=>"pl.nlm.nih.gov/",
            'theme'=>"vesuvius",
            'db_name'=>"",
            'db_host'=>"",
            'db_port'=>"",
            'db_user'=>"",
            'db_pass'=>"",
            'db_engine'=>"",
            'storage_engine'=>"",
            'dbal_lib_name'=>"adodb",
            'enable_monitor_sql'=>'false',
            'locale'=>"en_US",
            'default_module'=>'rez',
            'default_action'=>'landing',
            'pwd_min_chars'=>8,
            'pwd_max_chars'=>16,
            'pwd_has_uppercase'=>'true',
            'pwd_has_lowercase'=>'true',
            'pwd_has_numbers'=>'true',
            'pwd_has_spchars'=>'false',
            'pwd_has_username'=>'true',
            'pwd_no_change_limit'=>'true',
            'enable_locale'=>'false',
            'enable_plus_web_services'=>'true',
            'enable_solr_for_search'=>'false'
        );
      
        return $config;
    }

    function getHtAccessArray(){
        $htaccess=array();
        $htaccess['AddType']="application/x-httpd-php .php .xml";
        $htaccess['ErrorDocument 404']="/index.php";
        $htaccess['DirectoryIndex']="/index.php";
        $htaccess['RewriteEngine']="On";
        $htaccess['RewriteBase']="/".self::generateRewriteBase();
        $htaccess['RewriteCond']=array();
        $htaccess['RewriteCond'][0]="%{REQUEST_FILENAME} -d [OR]";
        $htaccess['RewriteCond'][1]="%{REQUEST_FILENAME} -f";
        $htaccess['RewriteRule']=array();
        $htaccess['RewriteRule'][0]=".* - [S=7]";
        $htaccess['RewriteRule'][1]="^(person.[0-9]+)$ index.php?mod=eap&act=modrewrite&val=$1";
        $htaccess['RewriteRule'][2]="^(about|ABOUT)$ index.php?mod=rez&act=default&page_id=-30 [L]";
        $htaccess['RewriteRule'][3]="^(plus|PLUS)$ index.php?mod=rez&act=default&page_id=-45 [L]";
        $htaccess['RewriteRule'][4]="^(login|LOGIN)$ index.php?mod=pref&act=loginForm [L]";
        $htaccess['RewriteRule'][5]="^([^/][a-z0-9]+)$ index.php?shortname=$1";
        $htaccess['RewriteRule'][6]="^([^/][a-z0-9]+)/$ index.php?shortname=$1";
        $htaccess['RewriteRule'][7]="^([^/][a-z0-9]+)/(.+)$ $2?shortname=$1 [QSA]";

        return $htaccess;
    }

    function generateRewriteBase(){
        $filePathFromServer=$_SERVER['SCRIPT_NAME'];
        $pathVariables=explode("/", $filePathFromServer);
        $rewriteBase="";
        foreach($pathVariables as $key=>$value){
            if($value!=null || $value!=''|| $value!=""){
                if($value=='www' || $value=="www"){
                    $rewriteBase.=$value."/";
                    return $rewriteBase;
                }
                else{
                    $rewriteBase.=$value."/";
                }
            }
        }
    }

    function CheckConnection($db_config)
  {
	if($db_config['hostname']!=''){
      try {
        $this->dbParams($db_config);
        $serverlink=mysql_connect($db_config['hostname'].":".$db_config['dbport'], $db_config['username'], $db_config['password']);
        if(!$serverlink)
            $result='Error in connecting to Server'.mysql_error();
        else{
            $dbcheck=mysql_select_db($db_config['dbname']);
            if(!$dbcheck){
                $result='Error in connecting to database'.mysql_error();
            }
            else
                $result = 'good';
        }

      } catch (Exception $e) {
        $result = $e->getMessage();
      }
	}
	else{
		$result="Invalid database configurations.";
	}

    return $result;
  }

  function checkSystemParameters($sysparams){
      $this->systemParams($sysparams);
      $result='';
      if(strlen($sysparams['base_uuid'])<4){
          $result.="Base_uuid should at least have 4 characters"."<BR>";
      }
      if($sysparams['pwd_max_chars']<$sysparams['pwd_min_chars']){
          $result.="Maximum password length should greater than minimum password length. <BR>";
      }
      if((strlen($sysparams['base_uuid'])>=4) && ($sysparams['pwd_max_chars']>=$sysparams['pwd_min_chars'])){
          $result='good';
      }

      return $result;

  }


    function getCurrent()
  {
    global $INS_CONFIG;
    $filename = $INS_CONFIG['rootpath'].'/conf/sahana.conf';

    if (file_exists($filename)) {
      //$config = Config::loadFile($filename);
	$configins=new Config();
	$config=$configins->loadFile($filename);
    } else {
      $install_flag = false;
    }
    $filename = $INS_CONFIG['rootpath'].'/www/.htaccess';
    if (file_exists($filename)) {
      //$htaccess = Htaccess::loadFile($filename);
	$htaccessins=new Htaccess();
	$htaccess =$htaccessins->loadFile($filename);
    } else {
      $install_flag = true;
      $existing_auth_method = "bypass";
	$htaccess=array();
    }



    try {
      $this->setConfig('config', $config);
      $this->setConfig('DB_ENGINE',  self::obtainParameter($config,'db_engine'));
      $this->setConfig('DB_STORAGE_ENGINE',self::obtainParameter($config,'storage_engine'));
      $this->setConfig('DB_SERVER', self::obtainParameter($config,'db_host'));
      $this->setConfig('DB_DATABASE', self::obtainParameter($config,'db_name'));
      $this->setConfig('DB_PORT',self::obtainParameter($config,'db_port'));
      $this->setConfig('DB_USER', self::obtainParameter($config,'db_user'));
      $this->setConfig('DB_PASSWORD', self::obtainParameter($config,'db_pass'));
      $this->setConfig('BASE_UUID',self::obtainParameter($config,'base_uuid'));
      $this->setConfig('THEME',self::obtainParameter($config,'theme'));
      $this->setConfig('ENABLE_LOCALE',self::obtainParameter($config,'enable_locale'));
      $this->setConfig('LOCALE',self::obtainParameter($config,'locale'));
      $this->setConfig('ENABLE_PLUS_WEB_SERVICES',self::obtainParameter($config,'enable_plus_web_services'));
      $this->setConfig('PASSWORD_MIN_CHARS',intval($config['pwd_min_chars']));
      $this->setConfig('PASSWORD_MAX_CHARS',intval($config['pwd_max_chars']));
      $this->setConfig('PWD_HAS_UPPERCASE',self::obtainParameter($config,'pwd_has_uppercase'));
      $this->setConfig('PWD_HAS_LOWERCASE',self::obtainParameter($config,'pwd_has_lowercase'));
      $this->setConfig('PWD_HAS_NUMBERS',self::obtainParameter($config,'pwd_has_numbers'));
      $this->setConfig('PWD_HAS_SPCHARS',self::obtainParameter($config,'pwd_has_spchars'));
      $this->setConfig('PWD_HAS_USERNAME',self::obtainParameter($config,'pwd_has_username'));
      $this->setConfig('PWD_NO_CHANGE_LIMIT',self::obtainParameter($config,'pwd_no_change_limit'));
      $this->setConfig('htaccess', $htaccess);
      
    } catch (Exception $e) {
      return 'file was unreadable';
    }
    return array($config, $htaccess);
  }


  function obtainParameter($config,$arrayIndex){
      $arrayValue='';
      if($config[$arrayIndex]==null || $config[$arrayIndex]=='' || $config[$arrayIndex]==""){
          $arrayValue=null;
      }
      else if($config[$arrayIndex]=='false' ||$config[$arrayIndex]=="false"){
            $arrayValue='false';
      }
      else if($config[$arrayIndex]=='true' ||$config[$arrayIndex]=="true"){
            $arrayValue='true';
      }
      else{
          $arrayValue=substr($config[$arrayIndex], 1, -1);
      }
      return $arrayValue;
  }


  function appSaveSetup($htaccess)
  {
    global $INS_CONFIG;
    $file = $INS_CONFIG['rootpath'].'/www/.htaccess';

    try {
	$htaccessins=new Htaccess();
      file_put_contents($file, $htaccessins->dump($htaccess));
    } catch (Exception $e) {
      echo "hey, something went wrong:" . $e->getMessage();
      return false;
    }


    return true;
    //once save setup is complete, create entry in ag_host (needed for global params
  }
  
  function doInstall($sys_params){
      global $INS_CONFIG;
      $direcotrypath=$INS_CONFIG['rootpath'].'/backups/';
      $wwwdirectory=$INS_CONFIG['rootpath'].'/www/';
      $confdirectory=$INS_CONFIG['rootpath'].'/conf/';
      if(file_exists($direcotrypath)){
          $sqlFile=$INS_CONFIG['rootpath'].'/backups/'.self::getLatestSQLFile($direcotrypath);
      }
      $result=self::createDirectories();
      foreach ($result as $value) {
          $installed[]=$value;
      }
      if(file_exists($sqlFile)){
          $sqlResult=self::executeSQLFile($sqlFile);
      }else{
          $sqlResult="MySQL file couldn't be found";
      }
      if(file_exists($wwwdirectory)){
          if(substr(sprintf('%o', fileperms($wwwdirectory)), -4)=="0777"){
              if(!chmod($wwwdirectory,0755)){
                  $installed[]="Error in changing permissions of the ".$wwwdirectory.". You have to manually change the permissions to 0755";
              }
          }
      }
      else{
          $installed[]=$wwwdirectory." doesn't exists to change permissions.";
      }

      if(file_exists($confdirectory)){
          if(substr(sprintf('%o', fileperms($confdirectory)), -4)=="0777"){
              if(!chmod($confdirectory,0755)){
                  $installed[]="Error in changing permissions of the ".$confdirectory.". You have to manually change the permissions to 0755";
              }
          }
      }
      else{
          $installed[]=$confdirectory." doesn't exists to change permissions.";
      }
      
      
//      if($sqlResult=="successfully"){
//          $installed[]="Successfully executed sql file";
//      }
//      else{
          $installed[]=$sqlResult;
//      }

      return implode('<br>', $installed);
      
  }

  function getLatestSQLFile($directorypath){
    global $INS_CONFIG;
	$pattern='/^.*\.(sql)$/i';
    $files="";
    $fileCount=0;
    $sqlFiles="";
    $fileversion="";
    $filePath=$directorypath;
    $dir = opendir($filePath);
    while ($file = readdir($dir)) {
      if (preg_match($pattern,$file)) {
        $files[] = $file;
        $fileCount++;
      }
    }
    if ($fileCount > 0) {
        foreach ($files as $value) {
              $position=strpos($value, "_");
              if(!($position==false)){
                  $sqlFiles[]=$value;
              }

          }

          if(count($sqlFiles)==0){
          return "SQL file couldn't be found";
          }
          elseif(count($sqlFiles)==1){
              return "vesuviusStarterDb_v".$sqlFiles[0].".sql";
          }
          else{
              $maximumVal="";
              foreach($sqlFiles as $value){
                  $filenameParts=explode("_", $value);
                  $versionPart=explode(".",$filenameParts[1]);
                  $fileversion[]=substr(trim($versionPart[0]),1);
              }
              $maximumVal=$fileversion[0];
              foreach ($fileversion as $value) {
                        if($value>$maximumVal)
                            $maximumVal=$value;
              }
              return "vesuviusStarterDb_v".$maximumVal.".sql";

          }
    }
    else{
        return "There are no .sql files in the given directory.";
    }
  }

  function createDirectories(){
      global $INS_CONFIG;
      $tmpdir=$INS_CONFIG['rootpath'].'/www/tmp';
      $tmpdirresult=mkdir($tmpdir, 0777,true);
      $bcapscachedir=$INS_CONFIG['rootpath'].'/www/tmp/bcaps_cache';
      $int_cachedir=$INS_CONFIG['rootpath'].'/www/tmp/int_cache';
      $mpres_cachedir=$INS_CONFIG['rootpath'].'/www/tmp/pfif_cache';
      $plus_cachedir=$INS_CONFIG['rootpath'].'/www/tmp/plus_cache';
      $rap_cachedir=$INS_CONFIG['rootpath'].'/www/tmp/rap_cache';
      $URIdir=$INS_CONFIG['rootpath'].'/3rd/htmlpurifier/library/HTMLPurifier/DefinitionCache/Serializer/URI';
      if(file_exists($tmpdir) && substr(sprintf('%o', fileperms($tmpdir)), -4)=="0777"){
          $installed[]="The tmp directory is already created and have set the file permissions accordingly.";
          $installed[]=self::createSubdirectories($bcapscachedir);
          $installed[]=self::createSubdirectories($int_cachedir);
          $installed[]=self::createSubdirectories($mpres_cachedir);
          $installed[]=self::createSubdirectories($plus_cachedir);
          $installed[]=self::createSubdirectories($rap_cachedir);
      }
      else if(file_exists($tmpdir) && substr(sprintf('%o', fileperms($tmpdir)), -4)!="0777"){
          if(!chmod($tmpdir,0777)){
              $installed[]="The tmp directory has already been created and error in setting the file permissions. You have to set it manually.";
          }
          else{
              $installed[]="The tmp directory has already been created and successfully set the file permissions.";
              $installed[]=self::createSubdirectories($bcapscachedir);
              $installed[]=self::createSubdirectories($int_cachedir);
              $installed[]=self::createSubdirectories($mpres_cachedir);
              $installed[]=self::createSubdirectories($plus_cachedir);
              $installed[]=self::createSubdirectories($rap_cachedir);
          }
      }
      else{
          $tmpdirresult=mkdir($tmpdir, 0777,true);
          if(!$tmpdirresult){
              $installed[]="Error in creating the tmp directory. You have to create the directories and sub directories manually.";
          }
          else{
              $installed[]="Successfully created the tmp directory";
              if(!chmod($tmpdir,0777)){
                  $installed[]="Error in setting the permissions. You have to manually set the permissions and create the subdirectories";
              }
              else{
                  $installed[]="successfully set the permissions to tmp directory";
                  $installed[]=self::createSubdirectories($bcapscachedir);
                  $installed[]=self::createSubdirectories($int_cachedir);
                  $installed[]=self::createSubdirectories($mpres_cachedir);
                  $installed[]=self::createSubdirectories($plus_cachedir);
                  $installed[]=self::createSubdirectories($rap_cachedir);
              }
          }
      }

      $installed[]=self::createSubdirectories($URIdir);



      return $installed;
  }

  function createSubdirectories($dir){
      if(file_exists($dir) && substr(sprintf('%o', fileperms($dir)), -4)=="0777"){
          return $dir." directory has already been created and set the permissions.";
      }
      else if(file_exists($dir) && substr(sprintf('%o', fileperms($dir)), -4)!="0777"){
          if(!chmod($dir,0777)){
              return $dir." directory has already been created and error in setting the permissions. You have to manually set it.";
          }
          else{
              return $dir." directory has already been created and successfully set the permissions.";
          }
      }
      else{
          if(!mkdir($dir, 0777,true)){
              return "Error in creating the ".$dir.". You have to manually create it and set permissions.";
          }
          else{
              if(!chmod($dir,0777)){
                  return "Successfully created the ".$dir.". But error in setting permissions. You have to manually set permissions";
              }
              else{
                  return "Successfully created and set the permissions to the ".$dir;
              }
          }
      }
  }

  function executeSQLFile($fileName){
      global $INS_CONFIG;
      $mysqli = new mysqli($INS_CONFIG['DB_SERVER'], $INS_CONFIG['DB_USER'], $INS_CONFIG['DB_PASSWORD'], $INS_CONFIG['DB_DATABASE']);
      if (mysqli_connect_errno()){
        return "Connect failed: %s\n".mysqli_connect_error();
      }
      else{
            $file_content = file($fileName);
            $sqlLine='';
            foreach($file_content as $sql_line){
                $sqlLine.=$sql_line;
            }
            $queryresult=mysqli_multi_query($mysqli, $sqlLine);
            if(!$queryresult){
                return "Error in executing the MySQL file.";
            }
            else{
                mysqli_close($mysqli);
                return "Successfully executed the MySQL file.";
            }
        }
  }

}

class ConfigurationFileTask extends Config{
    function execute($arguments = array(),$filename)
    {
        
          $file = $filename;
        
        $config = file_exists($file) ? Config::loadFile($file) : array();

        $config=$arguments;

        file_put_contents($file, Config::dump($config));
    }
}
?>
