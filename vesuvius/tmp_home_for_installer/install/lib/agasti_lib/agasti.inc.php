<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
require_once (dirname(__FILE__) . '/Yaml/Yaml.php');


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
          4 => array('title' => '5. Configuration Summary', 'fun' => 'stage4'),
          5 => array('title' => '6. Installation Summary', 'fun' => 'stage5'),
    //    6 => array('title' => '7. Enter Secure Mode', 'fun' => 'stage6' ),
        );

        return $steps;
    }


    function stage0()
    {
    return '<div class=info><h2>Welcome to the Sahana Agasti 2.0 Installation Wizard</h2><br />
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
    $LICENSE_FILE=$this->INS_CONFIG['rootpath'] .'/install/LICENSE';
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
    $requirementArray[$this->INS_CONFIG['rootpath'].'/install/']='777';
    $requirementArray[$this->INS_CONFIG['rootpath'].'/install/css/']='775';
    //$requirementArray[]='';
    //$requirementArray[]='';

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
                  <label>host:</label>
                  <input type="text" name="db_host" id="db_host" class="inputGray"
                         value="' . $this->getConfig('DB_SERVER', 'localhost') . '"/>
                </li>
                <li>
                  <label>database:</label>
                  <input type="text" name="db_name" id="db_name" class="inputGray"
                         value="' . $this->getConfig('DB_DATABASE', 'agasti23') . '" />
                </li>
                <li>
                  <label>username:</label>
                  <input type="text" name="db_user" id="db_user" class="inputGray"
                         value="' . $this->getConfig('DB_USER', 'root') . '" />
                </li>
                <li>
                  <label>password:</label>
                  <input type="password" name="db_pass" id="db_pass" class="inputGray"
                         value="' . $this->getConfig('DB_PASSWORD', 'root') . '" />
                </li>
                <input id="init_schema" type="hidden" name="init_schema" checked="checked" />
                <li><span class="fail">this will drop your current database.</span></li>
              </ul>
            </fieldset>
            <fieldset>
              <legend><img src="images/config.png" alt="config gear icon" />Administrator Information:</legend>
              <ul>
                <li>
                  <label>name:</label>
                  <input type="text" name="admin_name" id="admin_name" class="inputGray"
                         value="' . $this->getConfig('ADMIN_NAME', 'administrator') . '" /><br />
                </li>
                <li>
                  <label>email:</label>
                  <input type="text" name="admin_email" id="admin_email" class="inputGray"
                         value="' . $this->getConfig('ADMIN_EMAIL', 'b@m.an') . '" /><br />
                </li>
              </ul>
            </fieldset>';
    $results = 'The database is created manually.  First, the Agasti Installer will test your
      configuration settings before continuing.  Enter your database settings and click "Test Connection". <br /><br/>'
        . $instruct . $table . $retry;

    return $results;
  }


  function stage4()
  {
    $current = $this->getCurrent();

    return 'Below is your installation configuration summary:<br /><div class="info">
        <strong>Database Host</strong>: ' . $this->getConfig('DB_SERVER') .
    '<br /><strong>Database Name</strong>: ' . $this->getConfig('DB_DATABASE') .
    '<br /><strong>Database User</strong>: ' . $this->getConfig('DB_USER') .
    '<br /><strong>Database Password</strong>: ' . preg_replace('/./', '*', $this->getConfig('DB_PASSWORD', 'unknown')) .
    '<br /><strong>Administrator</strong>: ' . $this->getConfig('ADMIN_NAME') .
    '<br /><strong>Admin E-mail</strong>: ' . $this->getConfig('ADMIN_EMAIL') .
    '</div><br /> Please verify your settings.  By clicking next you will install Sahana Agasti.';
  }


  function stage5()
  {
    if ($this->INSTALL_RESULT == 'Success!') {
      return '<span class="okay">Congratulations!  Installation was successful:</span> <br /><div class="info">
        <strong>Database Host</strong>: ' . $this->getConfig('DB_SERVER') .
      '<br /><strong>Database Name</strong>: ' . $this->getConfig('DB_DATABASE') .
      '<br /><strong>Database User</strong>: ' . $this->getConfig('DB_USER') .
      '<br /><strong>Database Password</strong>: ' . preg_replace('/./', '*', $this->getConfig('DB_PASSWORD', 'unknown')) .
      '<br /><strong>Administrator</strong>: ' . $this->getConfig('ADMIN_NAME') .
      '<br /><strong>Admin E-mail</strong>: ' . $this->getConfig('ADMIN_EMAIL') .
      '</div><br /> NOTE: to continue with Agasti setup you must first create the "Super User"
        account by editing the config file.  In .../config please edit the config.yml file with the
        Super User username and password.  After you have done so, click finish and you will be
        redirected to log in with the Super User username and password and thenthen create your
        first user.';
    } else {
      return '<span class="fail">There was an error with your installation:</span><br /><div class="info">' . $this->INSTALL_RESULT . '</div>';
    }
  }

  function stage6()
  {
    return "there is no step 6 in the installer, well, no screen for it at least: this should login the user and redirect to admin/createuser, i.e. you shouldn't even SEE this";
  }



  function getCurrent()
  {
    $filename = 'databases.yml';
    if (file_exists($filename)) {
      $dbArray = Yaml::load($filename);
    } else {
      $install_flag = false;
    }
    $filename = 'config.yml';
    if (file_exists($filename)) {
      $cfgArray = Yaml::load($filename);
    } else {
      $install_flag = true;
      $existing_auth_method = "bypass";
    }
    try {
      $db_params = parseDSN($dbArray['all']['doctrine']['param']['dsn']);
      $this->setConfig('db_config', $dbArray);
      $this->setConfig('DB_SERVER', $db_params['host']);
      $this->setConfig('DB_DATABASE', $db_params['dbname']);
      $this->setConfig('DB_USER', $dbArray['all']['doctrine']['param']['username']);
      $this->setConfig('DB_PASSWORD', $dbArray['all']['doctrine']['param']['password']);
      $this->setConfig('ADMIN_NAME', $cfgArray['admin']['admin_name']);
      $this->setConfig('ADMIN_EMAIL', $cfgArray['admin']['admin_email']);
      $this->setConfig('AUTH_METHOD', $cfgArray['admin']['auth_method']['value']);
    } catch (Exception $e) {
      return 'file was unreadable';
    }
    return array($dbArray, $cfgArray);
  }



  function dbParams($db_params)
  {
    $arguments = array(
      'task' => 'configure:database',
      //'dsn' => buildDsnString('mysql', $_POST['db_host'], $_POST['db_name'], $_POST['db_port']),
      'dsn' => $db_params['dsn'], // ilya 2010-07-21 15:16:58
      'hostname'=>$db_params['hostname'],
      'dbname'=>$db_params['dbname'],
      'username' => $db_params['username'],
      'password' => $db_params['password'],
    );
    $options = array(
      'help' => null,
      'quiet' => null,
      'trace' => null,
      'version' => null,
      'color' => null,
      'env' => 'all',
      'name' => 'doctrine',
      'class' => 'sfDoctrineDatabase',
      'app' => null
    );
    $dbConfig = new appConfigureDatabaseTask();
    $dbConfig->execute($arguments, $options);
  }



  function CheckConnection($db_config)
  {
    if ($db_config['dsn'] != '') {
      try {
        $this->dbParams($db_config);
        $serverlink=mysql_connect($db_config['hostname'], $db_config['username'], $db_config['password']);
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
    } else {
      $result = 'Database configuration is not valid: bad DSN';
    }
    return $result;
  }



  //This method only writes app.yml and config.yml files
  function appSaveSetup($config)
  {
      /** remember to set the superadmin config.yml up!!!  */
    sfClearCache('frontend', 'all');
    sfClearCache('frontend', 'dev');
    sfClearCache('frontend', 'prod');
    //require_once (dirname(__FILE__) . '/lib/Yaml/Yaml.php');
    $file = 'config.yml';
// update config.yml
    try {
      file_put_contents($file, Yaml::dump($config, 4));
    } catch (Exception $e) {
      echo "hey, something went wrong:" . $e->getMessage();
    }

    $file = 'app.yml';
    touch($file);
//if app.yml doesn't exist
    $appConfig = Yaml::load($file);
    $appConfig['all']['sf_guard_plugin'] =
        array('check_password_callable'
          => array('agSudoAuth', 'authenticate'));
    $appConfig['all']['sf_guard_plugin_signin_form'] = 'agSudoSigninForm';

    $appConfig['all']['.array']['menu_top'] =
        array(
          'homepage' => array('label' => 'Home', 'route' => '@homepage'),
          'prepare' => array('label' => 'Prepare', 'route' => '@homepage'),
          'respond' => array('label' => 'Respond', 'route' => '@homepage'),
          'recover' => array('label' => 'Recover', 'route' => '@homepage'),
          'mitigate' => array('label' => 'Mitigate', 'route' => '@homepage'),
          'foo' => array('label' => 'Foo', 'route' => '@foo'),
          'modules' => array('label' => 'Modules', 'route' => '@homepage'),
          'admin' => array('label' => 'Administration', 'route' => '@admin'),
          'help' => array('label' => 'Help', 'route' => '@about'));

    $appConfig['all']['.array']['menu_children'] =
        array(
          'facility' => array('label' => 'Facilities', 'route' => '@facility', 'parent' => 'prepare'),
          'org' => array('label' => 'Organizations', 'route' => '@org', 'parent' => 'prepare'),
          'scenario' => array('label' => 'Scenarios', 'route' => '@scenario', 'parent' => 'prepare'),
          'activate' => array('label' => 'Activate a Scenario', 'route' => '@scenario', 'parent' => 'respond'),
          'event' => array('label' => 'Manage Events', 'route' => '@homepage', 'parent' => 'respond'),
          'event_active' => array('label' => 'Manage [Active Event]', 'route' => '@homepage', 'parent' => 'respond'));

    $appConfig['all']['.array']['menu_grandchildren'] =
        array(
          'facility_new' => array('label' => 'Add New Facility', 'route' => 'facility/new', 'parent' => 'facility'),
          'facility_list' => array('label' => 'List Facilities', 'route' => 'facility/list', 'parent' => 'facility'),
          'facility_import' => array('label' => 'Import Facilities', 'route' => '@facility', 'parent' => 'facility'),
          'facility_export' => array('label' => 'Export Facilities', 'route' => '@facility', 'parent' => 'facility'),
          'facility_types' => array('label' => 'Manage Facility Types', 'route' => '@facility', 'parent' => 'facility'),
          'org_new' => array('label' => 'Add New Organization', 'route' => 'organization/new', 'parent' => 'org'),
          'org_list' => array('label' => 'List Organizations', 'route' => 'organization/list', 'parent' => 'org'),
          'scenario_create' => array('label' => 'Build New Scenario', 'route' => 'scenario/new', 'parent' => 'scenario'),
          'scenario_list' => array('label' => 'List Scenarios', 'route' => 'scenario/list', 'parent' => 'scenario'),
          'scenario_facilitygrouptypes' => array('label' => 'Edit Facility Group Types', 'route' => 'scenario/grouptype', 'parent' => 'scenario'),
          'scenario_active' => array('label' => '[Active Scenario]', 'route' => '@scenario', 'parent' => 'scenario'),
          'event_active_staff' => array('label' => 'Staff', 'route' => '@homepage', 'parent' => 'event_active'),
          'event_active_facilities' => array('label' => 'Facilities', 'route' => '@homepage', 'parent' => 'event_active'),
          'event_active_clients' => array('label' => 'Clients', 'route' => '@homepage', 'parent' => 'event_active'),
          'event_active_reporting' => array('label' => 'Reporting', 'route' => '@homepage', 'parent' => 'event_active'));

// updates config.yml
    try {
      file_put_contents($file, Yaml::dump($appConfig, 4));
    } catch (Exception $e) {
      echo 'hey, something went wrong: ', $e->getMessage();
      return false;
    }
    $file = 'databases.yml';
//the below line will fail if the permissions are not correct, should be wrapped in a try/catch
    $dbConfiguration = Yaml::load($file);
    $dbConfiguration['all']['doctrine']['param']['attributes'] = array(
      'default_table_type' => 'INNODB',
      'default_table_charset' => 'utf8',
      'default_table_collate' => 'utf8_general_ci'
    );
    try {
      file_put_contents($file, Yaml::dump($dbConfiguration, 4));
    } catch (Exception $e) {
      echo "hey, something went wrong:" . $e->getMessage();
      return false;
    }

    return true;
    //once save setup is complete, create entry in ag_host (needed for global params
  }

  function doInstall($db_params)
  {
    /*$databaseManager = new sfDatabaseManager($this->dbParams($db_params));
    $buildSql = new Doctrine_Task_GenerateSql();
    $dropDb = new Doctrine_Task_DropDb();
    $dropDb->setArguments(array('force' => true));
    $buildSql->setArguments(array(
      'models_path' => sfConfig::get('sf_lib_dir') . '/model/doctrine',
      'sql_path' => sfConfig::get('sf_data_dir') . '/sql',
    ));
    $createDb = new Doctrine_Task_CreateDb();
    try {
      if ($dropDb->validate()) {
        $dropDb->execute();
      } else {
        throw new Doctrine_Exception($dropDb->ask());
      }
    } catch (Exception $e) {
      $installed[] = 'Could not drop DB! : ' . "\n" . $e->getMessage();
    }
    try {
      if ($createDb->validate()) {
        $createDb->execute();
      } else {
        throw new Doctrine_Exception($createDb->ask());
      }
      $installed[] = 'Successfully created database';
    } catch (Exception $e) {
      $installed[] = 'Could not create DB! : ' . "\n" . $e->getMessage();
    }
    try {
      if ($buildSql->validate()) {
        $buildSql->execute();
      }
      $installed[] = 'Successfully built SQL';
    } catch (Exception $e) {
      $installed[] = 'Could not build SQL! : ' . "\n" . $e->getMessage();
    }

    try {
      $allmodels = Doctrine_Core::loadModels(
              sfConfig::get('sf_lib_dir') . '/model/doctrine',
              Doctrine_Core::MODEL_LOADING_CONSERVATIVE);
      $installed[] = 'Sucessefully loaded all data models';
    } catch (Exception $e) {
      $installed[] = 'Could not load models! : ' . "\n" . $e->getMessage();
    }
    try {
      Doctrine_Core::createTablesFromArray(Doctrine_Core::getLoadedModels());
      $installed[] = 'Successfully created database tables from models';
    } catch (Exception $e) {

      $installed[] = 'Could not create tables! : ' . "\n" . $e->getMessage();
    }

     try {
        Doctrine_Core::loadData(sfConfig::get('sf_data_dir') . '/fixtures', false);
        //$installed[] = 'Successfully loaded core data fixtures';
        $installed = 'Success!';
      } catch (Exception $e) {
        $installed[] = 'Could not insert SQL! : ' . "\n" . $e->getMessage();
      }*/
//
//    $packages = agPluginManager::getPackagesByStatus(1); //get all enabled packages
//    foreach($packages as $package)
//    {
//      try {
////        if($package == 'agStaffPackage'){
////          Doctrine_Core::loadModels(sfConfig::get('sf_lib_dir') . '/model/doctrine', Doctrine_Core::MODEL_LOADING_AGGRESSIVE);
////        }
////        else{
//          Doctrine_Core::loadModels(sfConfig::get('sf_app_dir') . '/lib/packages/' . $package . '/lib/model/doctrine', Doctrine_Core::MODEL_LOADING_AGGRESSIVE);
////        }
//        Doctrine_Core::loadData(sfConfig::get('sf_app_dir') . '/lib/packages/' . $package  . '/data/fixtures', true);
//        $installed[] = 'Successfully loaded packaged data fixtures';
//      } catch (Exception $e) {
//        $installed[] = 'Could not insert SQL! : ' . "\n" . $e->getMessage();
//      }
//    }

//    this entry is achieved by proxy of the agHost.yml fixture/example
//
//    try {
//      $ag_host = new agHost();
//      $ag_host->setHostname($this->getConfig('DB_SERVER'));
//      $ag_host->save();
//      //$installed[] = 'Successfully generated host record based on database server host';

//    } catch (Exception $e) {
//      $installed[] = 'Could not insert ag_host record ' . $e->getMessage();
//    }

    /*if(is_array($installed)){
      return implode('<br>', $installed);
    }
      else{
      return $installed;
    }*/

  }

  
}


class appConfigureDatabaseTask extends Yaml
{

  function execute($arguments = array(), $options = array())
  {
    //parent::execute($arguments, $options);
    if (null !== $options['app'])
    {
      //$file = sfConfig::get('sf_apps_dir').'/'.$options['app'].'/config/databases.yml';
        $file = 'databases.yml';
    }
    else
    {
      $file = 'databases.yml';
    }
    //echo file_exists($file);
    $config = file_exists($file) ? Yaml::load($file) : array();

    $config[$options['env']][$options['name']] = array(
      'class' => $options['class'],
      'param' => array_merge(isset($config[$options['env']][$options['name']]['param']) ? $config[$options['env']][$options['name']]['param'] : array(), array('dsn' => $arguments['dsn'], 'hostname'=>$arguments['hostname'], 'dbname'=>$arguments['dbname'], 'username' => $arguments['username'], 'password' => $arguments['password'])),
    );

    file_put_contents($file, Yaml::dump($config, 4));
  }

}

?>
