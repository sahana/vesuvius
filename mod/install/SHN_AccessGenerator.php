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
 * This class is reponsible for generating .htaccess file,
 * while the installation process.
 */
class SHN_AccessGenerator
{
    
    const HTACCESS_FILE_RELATIVE_PATH = "/www/.htaccess";
    
    const RULES_CONF_FILE_RELATIVE_PATH = "/mod/install/rewriteBaseConf.xml";
    
    const HTACCESS_CONF_FILE_RELATIVE_PATH = "/mod/install/htaccess.xml";
    
    private $_appRoot = null;
    
    /**
     * The constrctor.
     * 
     * @param   String  $appRoot    The absolute path for the application root directory.
     */
    public function __construct($appRoot)
    {
        $this->_appRoot = $appRoot;
    }
    
    /**
     * Controll the process of writing the .htaccess file.
     */
    public function writeHtaccess()
    {
        
        $htxml = simplexml_load_file($this->_appRoot . self::HTACCESS_CONF_FILE_RELATIVE_PATH);
        
        $file_contents = "AddType application/x-httpd-php .php .xml\n"
                         . "DirectoryIndex index.php\n"
                         . "RewriteEngine On\n"
                         . "RewriteBase " . dirname($_SERVER['PHP_SELF']) . "\n"
                         . "RewriteCond %{REQUEST_FILENAME} -d [OR] \nRewriteCond %{REQUEST_FILENAME} -f\n"
                         . "RewriteRule .* - [S=" . $htxml->rulecount . "]\n";
        
        $file_contents .= $this->_getRewriteBaseString();
        
        $file_contents .= $this->_getModuleString($htxml);
        
        $file_contents .= "RewriteRule ^([^/][a-z0-9]+)$ $2?shortname=$1 [QSA]\n"
                            ."RewriteRule ^([^/][a-z0-9]+)/$ $2?shortname=$1 [QSA]\n"
                            ."RewriteRule ^([^/][a-z0-9]+)/(.+)$ $2?shortname=$1 [QSA]\n";
        
        $this->_writeToHtaccessFile($file_contents);
        
    }
    
    /**
     * Create the string represent modules, which should be placed in .htaccess file.
     * 
     * @param   object  $htxml  SimpleXMLElement Object representation for the module xml file.
     * 
     * @return string 
     */
    private function _getModuleString($htxml)
    {
        
        $module_string = "";
        
        foreach($htxml->modules->module as $module) {
            
            $module_string .= "RewriteRule ^(";
            
            for( $i=0;$i<count($module->alias);$i++ )
            {
                if ( $i != count($module->alias) - 1 ) {
                    $module_string .= $module->alias[$i]."|";
                }
                else {
                    $module_string .= $module->alias[$i].")";
                }
            }
            
            $module_string .= "$           $2?mod=".$module->name." [QSA]\n";
            
        }
        
        return $module_string;
        
    }
    
    /**
     * Get set of rewrite rules as string, which should be placed in .htaccess file.
     * 
     * @return string 
     */
    private function _getRewriteBaseString()
    {
        
        $rewriteBaseConfXml = simplexml_load_file($this->_appRoot . self::RULES_CONF_FILE_RELATIVE_PATH);
        
        $rewriteRulesString = "";
        
        foreach ($rewriteBaseConfXml->reWriteRule as $rule)
        {
            
            $rewriteRulesString .= "RewriteRule ^(" . $rule->name . ")$ ?";
            $isFirst = true;
            
            foreach ($rule->params->param as $param)
            {
                if ($isFirst)
                {
                    $rewriteRulesString .= $param->name . "=" . $param->value;
                    $isFirst = false;
                }
                else {
                    $rewriteRulesString .= "&" . $param->name . "=" . $param->value;
                }
            }
            
            $rewriteRulesString .= " [L]\n";
            
        }
        
        return $rewriteRulesString;
    }
    
    /**
     * Write the generated content in to the .htaccess file.
     * 
     * @param   String  $fileContent    The content for the file.
     */
    private function _writeToHtaccessFile($fileContent)
    {
        
        $htaccessFile = fopen($this->_appRoot . self::HTACCESS_FILE_RELATIVE_PATH, 'w+');
        
        if (fwrite($htaccessFile, $fileContent))
        {
            add_confirmation(_t("Successfully wrote .htaccess file. Please ensure that Apache mod_rewrite is enabled."));
        }
        else {
            add_error(_t("Failed to write .htaccess file"));
        }
        
        fclose($htaccessFile);
        
    }
    
}

?>
