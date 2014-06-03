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
class SHN_AccessGenerator {
    
    private $_appRoot = null;
    
    public function __construct($appRoot)
    {
        
        $this->_appRoot = $appRoot;
        
    }
    
    /**
     * Write .htaccess file
     */
    public function writeHtaccess()
    {
        
        global $global;
        $error = false;
        $htxml = simplexml_load_file($global['approot']."/mod/install/htaccess.xml");

        $file_contents = "AddType application/x-httpd-php .php .xml\n"
                            ."DirectoryIndex index.php\n"
                            ."RewriteEngine On\n"
                            ."RewriteBase ".dirname($_SERVER['PHP_SELF'])."\n"
                            ."RewriteCond %{REQUEST_FILENAME} -d [OR] \nRewriteCond %{REQUEST_FILENAME} -f\n"
                            ."RewriteRule .* - [S=".$htxml->rulecount."]\n"
                            ."RewriteRule ^(person.[0-9]+)$ ?mod=eap&val=$1 [L]\n"
                            ."RewriteRule ^(about)$   ?mod=rez&page=-30 [L]\n"
                            ."RewriteRule ^(privacy)$ ?mod=rez&page=44  [L]\n"
                            ."RewriteRule ^(login)$              ?mod=pref&act=loginForm [L]\n"
                            ."RewriteRule ^(auth)$               ?doLogin=1 [L]\n"
                            ."RewriteRule ^(password)$           ?mod=pref&act=ch_passwd [L]\n"
                            ."RewriteRule ^(logout)$             ?act=logout [L]\n"
                            ."RewriteRule ^(register)$           ?mod=pref&act=signup [L]\n"
                            ."RewriteRule ^(register2)$          ?mod=pref&act=signup2 [L]\n"
                            ."RewriteRule ^(forgot)$             ?mod=pref&act=forgotPassword [L]\n"
                            ."RewriteRule ^(tracking)$           ?mod=pref&act=tracking [L]\n"
                            ."RewriteRule ^(reza|resourceadmin)$ ?mod=rez&act=adm_default [L]\n";
        $module_string = "";
        foreach($htxml->modules->module as $module) {
            $module_string .= "RewriteRule ^(";
            for( $i=0;$i<count($module->alias);$i++ ) {
                if ( $i != count($module->alias) - 1 ) {
                    $module_string .= $module->alias[$i]."|";
                }
                else {
                    $module_string .= $module->alias[$i].")";
                }
            }
            $module_string .= "$           $2?mod=".$module->name." [QSA]\n";
        }
        $file_contents .= $module_string;
        $file_contents .= "RewriteRule ^([^/][a-z0-9]+)$ $2?shortname=$1 [QSA]\n"
                            ."RewriteRule ^([^/][a-z0-9]+)/$ $2?shortname=$1 [QSA]\n"
                            ."RewriteRule ^([^/][a-z0-9]+)/(.+)$ $2?shortname=$1 [QSA]\n";


        $file = fopen($this->_appRoot."/www/.htaccess", 'w+');
        if ( fwrite($file, $file_contents) ) {
            add_confirmation("Successfully wrote .htaccess file. Please ensure that Apache mod_rewrite is enabled.");
        }
        else {
            add_error("Failed to write .htaccess file");
        }
        fclose($file);
    }
    
}

?>
