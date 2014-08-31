<?php

/**
 * @name         Installer
 * @version      1
 * @package      install
 * @author       Chanaka Dharmarathna <pe.chanaka.ck@gmail.com>
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2014.05.26
 */

/**
 * This class is reponsible for generating sahana.conf file,
 * while the installation process.
 */
class SHN_ConfigurationGenerator
{
    
    const LICENSE_AGREEMENT_FILE_RELATIVE_PATH = '/mod/install/licenseAgreement.txt';
    
    private $_appRoot = null;
    
    /**
     * The constructor.
     * 
     * @param   String  $appRoot    The root directory of the application.
     */
    public function __construct($appRoot)
    {
        $this->_appRoot = $appRoot;
    }
    
    /**
     * Function to get database details for conf file
     */
    public function writeConfInit()
    {
        
        echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"res/installer.css\" />";
        echo "<script type=\"text/javascript\" src=\"res/js/jquery.min.js\"></script>";
        echo "<script type=\"text/javascript\" src=\"res/js/installerValidateHelper.js\"></script>";
        echo "<script type=\"text/javascript\" src=\"res/js/jquery.form-validator.min.js\"></script>";
        
        shn_form_fopen("conf", "install", array('enctype'=>'enctype="multipart/form-data"', 'req_message' => true));
        shn_form_fsopen(_t('Database details'));
        shn_form_text(_t('Database host'), 'db_host', " data-validation=\"required\" data-validation-error-msg=\"" . _t("Please enter the Database host") . "\" ", array('value'=>'localhost', 'help' => _t("Your database server's host."), 'req' => true));
        shn_form_text(_t('Database port'), 'db_port', " data-validation=\"required\" data-validation-error-msg=\"" . _t("Please enter the Database port") . "\" ", array('value'=>'3306', 'help' => _t("Your database server's port."), 'req' => true));
        shn_form_radio(array(_t('Create New'), _t('Use Existing')), '', 'db_preference', null, null);
        shn_form_text(_t('Database name'), 'db_name', " data-validation=\"required\" data-validation-error-msg=\"" . _t("Please enter the Database name") . "\" ", array('help' => _t("The name of the database you'll be using for Vesuvius"), 'req' => true));
        shn_form_text(_t('Database username'), 'db_user', " data-validation=\"required\" data-validation-error-msg=\"" . _t("Please enter Database username") . "\" ", array('help' => _t('Database username'), 'req' => true));
        shn_form_password(_t('Database password'), 'db_pass', null, array('help' => _t('The password for the database user you have specified.')));
        shn_form_textarea('', 'license', ' readonly style="font-size:11px;"', array('value' => $this->_getLicenseAgreementText(), 'cols' => '45', 'rows' => '8'));
        shn_form_checkbox(_t('I agree with the terms of the License Agreement'), 'license_agreement', " data-validation=\"required\" data-validation-error-msg=\"" . _t("You should agree to the terms") . "\" ", array('req' => true, 'value' => 1, 'disabled' => false));
        shn_form_submit(_t('Submit Configuration'));
        shn_form_fsclose();
        shn_form_fclose();
        
        echo "<script> $.validate(); </script>";
        
    }
    
    
    /**
     * Write the configuration file
     */
    public function installConf()
    {
        
        if ($this->_installConfValidate() )
        {
            $db_params = $_SESSION['conf_fields'];
            $db_name_string = '$conf[\'db_name\']';
            $db_user_string = '$conf[\'db_user\']';
            $db_pass_string = '$conf[\'db_pass\']';
            $db_port_string = '$conf[\'db_port\']';
            $db_host_string = '$conf[\'db_host\']';
            $conf_file_contents = file_get_contents($this->_appRoot . '/conf/sahana.conf.example');

            $conf_file_contents .= "\n# Database Configuration\n".
                "$db_name_string = \"{$db_params['db_name']}\";\n".
                "$db_host_string = \"{$db_params['db_host']}\";\n".
                "$db_user_string = \"{$db_params['db_user']}\";\n".
                "$db_pass_string = \"{$db_params['db_pass']}\";\n".
                "$db_port_string = \"{$db_params['db_port']}\";\n";

            $isImportSuccess = false;
            
            if ($db_params['db_preference'] == 0)
            {
                if (shn_create_database($db_params))
                {
                    $isImportSuccess = $this->_importData($db_params);
                }
            } else {
                $isImportSuccess = $this->_importData($db_params);
            }
            
            if ($isImportSuccess)
            {
                
                add_confirmation(_t("Data import completed successfully."));
                
                if ( file_put_contents($this->_appRoot . '/conf/sahana.conf', $conf_file_contents) )
                {
                    add_confirmation(_t("Wrote sahana.conf successfully."));
                    echo _t('<p>Installation Complete. Now you can ') . '<a href="index.php">' . _t('go to the Vesuvius main page.') . '</a>';
                }
                
            } else {
                
                add_error(_t("Data import encountered an error: ") . $mysql_import_command);
                $this->writeConfInit();
                
            }
            
        }
        else {
            $this->writeConfInit();
        }

    }
    
    /**
     * Validate configurations.
     * 
     * @return boolean 
     */
    private function _installConfValidate()
    {
        $local_post = array();
        $no_errors = true;
        
        //clean the post -- trim them all
        foreach($_POST as $k => $v)
        {
            $v = trim($v);
            if($v != '') {
                $local_post[$k] = $v;
            }
        }
        
        $_SESSION['conf_fields'] = $local_post;
        
        if ( empty($local_post) )
        {
            $no_errors = false;
            $error_text = _t("Please fill in all the fields.");
        }
        
        if ( empty($local_post['db_name']) )
        {
            $no_errors = false;
            $error_text = _t("Please add a name for the Vesuvius database you created.");
        }
        
        if ( empty($local_post['db_user']) )
        {
            $no_errors = false;
            $error_text = _t("Please add a username for the Vesuvius database you created.");
        }
        
        if (empty($local_post['license_agreement']))
        {
            $no_errors = false;
            $error_text = _t("If you do not agree to the terms of this license agreement, please do not install the software.");
        }
        
        /*if ( empty($local_post['db_pass']) ) {
            $no_errors = false;
            $error_text = "Please add a password for the Vesuvius database you created.";
        }*/
        
        if ( !$no_errors )
        {
            add_error($error_text);
        }
        
        return $no_errors;
    }
    
    /**
     * Import sample data to the database.
     *
     * @global Array $global Global variable containing meta data.
     * @param Array $db_params Array $db_params Parameters array obtained from the installation form.
     */
    private function _importData($db_params) {

        global $global;

        if ( $db_params['db_pass'] == "" )
        {
            $mysql_import_command = "mysql -h {$db_params['db_host']} -u {$db_params['db_user']} {$db_params['db_name']} < {$global['approot']}backups/vesuviusStarterDb_v092.sql";
        }
        else {
            $mysql_import_command = "mysql -h {$db_params['db_host']} -u {$db_params['db_user']} -p{$db_params['db_pass']} {$db_params['db_name']} < {$global['approot']}backups/vesuviusStarterDb_v092.sql";
        }

        exec($mysql_import_command, $output = array(), $exit_value);
        
        return ($exit_value == 0);

    }
    
    /**
     * Get the GNU LGPL V3 agreement text.
     * 
     * @return type 
     */
    private function _getLicenseAgreementText()
    {
        
        $licenseText =  file_get_contents($this->_appRoot . self::LICENSE_AGREEMENT_FILE_RELATIVE_PATH);
        return ($licenseText === false) ? $this->_getLicenseAgreementTextOnError() : $licenseText;
        
    }
    
    /**
     * Additional license agreement text in case, read licenseAgreement.txt file fais.
     * 
     * @return type 
     */
    private function _getLicenseAgreementTextOnError()
    {
        
        return "This software follows GNU Lesser General Public License (LGPL) at http://www.gnu.org/licenses/lgpl.html. Please go through the all terms and conditions.";
        
    }

}

?>