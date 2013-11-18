<?
/**
 * @name         Installer
 * @version      1
 * @package      install
 * @author       Ramindu Deshapriya <rasade88@gmail.com> <rdeshapriya@virtusa.com>
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0911
 */


/**
 * Default function for install module
 */
function shn_install_default() {

	global $global;
	echo '<p>Installer under construction</p><br>';

    shn_write_htaccess();

    shn_write_conf_init();
}

/**
 * Write .htaccess file
 */
function shn_write_htaccess() {
    global $global;
    $error = false;
    $htxml = simplexml_load_file($global['approot']."/mod/install/htaccess.xml");

    $file_contents = "AddType application/x-httpd-php .php .xml\n"
                        ."ErrorDocument 404 index.php\n"
                        ."DirectoryIndex index.php\n"
                        ."RewriteEngine On\n"
                        ."RewriteBase ".$_SERVER['REQUEST_URI']."\n"
                        ."RewriteCond %{REQUEST_FILENAME} -d [OR] RewriteCond %{REQUEST_FILENAME} -f\n"
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


    $file = fopen($global['approot']."/www/.htaccess", 'w+');
    if ( fwrite($file, $file_contents) ) {
        add_confirmation("Successfully wrote .htaccess file. Please ensure that Apache mod_rewrite is enabled.");
    }
    else {
        add_error("Failed to write .htaccess file");
    }
    fclose($file);
}

/**
 * Function to get database details for conf file
 */
function shn_write_conf_init() {
    shn_form_fopen("conf", "install", array('enctype'=>'enctype="multipart/form-data"', 'req_message' => true));
        shn_form_fsopen('Database details');
            shn_form_text('Database Host', 'db_host', null, array('value'=>'localhost', 'help' => 'Your database server\'s host.'));
            shn_form_text('Database port', 'db_port', null, array('value'=>'3306', 'help' => 'Your database server\'s port.'));
            shn_form_text('Database name', 'db_name', null, array('help' => 'The name of the database you\'ll be using for Vesuvius'));
            shn_form_text('Database username', 'db_user', null, array('help' => 'Database username'));
            shn_form_password('Database password', 'db_pass', null, array('help' => 'The password for the database user you have specified.'));
            shn_form_submit('Submit Configuration');
        shn_form_fsclose();
    shn_form_fclose();
}

/**
 * Write the configuration file
 */
function shn_install_conf() {
    global $global;
    if ( shn_install_conf_validate() ) {
        $db_params = $_SESSION['conf_fields'];
        $db_name_string = '$conf[\'db_name\']';
        $db_user_string = '$conf[\'db_user\']';
        $db_pass_string = '$conf[\'db_pass\']';
        $db_port_string = '$conf[\'db_port\']';
        $db_host_string = '$conf[\'db_host\']';
        $conf_file_contents = file_get_contents($global['approot'].'/conf/sahana.conf.example');

        $conf_file_contents .= "\n# Database Configuration\n".
            "$db_name_string = \"{$db_params['db_name']}\";\n".
            "$db_host_string = \"{$db_params['db_host']}\";\n".
            "$db_user_string = \"{$db_params['db_user']}\";\n".
            "$db_pass_string = \"{$db_params['db_pass']}\";\n".
            "$db_port_string = \"{$db_params['db_port']}\";\n";

        if ( file_put_contents($global['approot'].'/conf/sahana.conf', $conf_file_contents) ) {
            add_confirmation("Wrote sahana.conf successfully.");
        }
        //Include the ADOdb Library
        require_once($global['approot'].'3rd/adodb/adodb.inc.php');
        $db = NewADOConnection('mysql');
        if ( $db->Connect($db_params['db_host'], $db_params['db_user'], $db_params['pass'], $db_params['db_name']) ) {
            if (!$db->Execute("LOAD DATA INFILE 'vesuviusStarterDb_v092.sql'")) {
                add_error("Failed at data import.".$db->ErrorMsg());
            }
            else {
                add_confirmation("Data import completed successfully.");
            }
        }
        else {

            add_error("Data import encountered an error.");
            shn_write_conf_init();
        }
    }
    else {
        shn_write_conf_init();
    }

}

function shn_install_conf_validate() {
    $local_post = array();
    $no_errors = true;
    //clean the post -- trim them all
    foreach($_POST as $k => $v) {
        $v = trim($v);
        if($v != '') {
            $local_post[$k] = $v;
        }
    }
    $_SESSION['conf_fields'] = $local_post;
    if ( empty($local_post) ) {
        $no_errors = false;
        $error_text = "Please fill in all the fields.";
    }
    if ( empty($local_post['db_name']) ) {
        $no_errors = false;
        $error_text = "Please add a name for the Vesuvius database you created.";
    }
    if ( empty($local_post['db_user']) ) {
        $no_errors = false;
        $error_text = "Please add a username for the Vesuvius database you created.";
    }
    /*if ( empty($local_post['db_pass']) ) {
        $no_errors = false;
        $error_text = "Please add a password for the Vesuvius database you created.";
    }*/
    if ( !$no_errors ) {
        add_error($error_text);
    }
    return $no_errors;
}
function shn_install_stream_init() {

    global $global;

    echo "<body>";
    echo "<div id=\"container\">";

    include_once($global['approot'].'/www/theme/'.$global['theme'].'/header.php');

    echo "<div id=\"wrapper\" class=\"clearfix\">";
    echo "<div id=\"wrapper_menu\">";
    echo "
		<div id=\"menuwrap\">
		<ul id=\"menu\">
	";
    echo "
		</ul>
		</div> <!-- /menuwrap -->
		</div>
		<div id=\"content\">
		<div style=\"padding: 20px 0px 0px 36px; font-size: 16px;\">
	";
    ob_start();
}
function shn_install_stream_close() {
    global $global;

    // flush the output buffer
    $output = ob_get_contents();
    ob_end_clean();

    // check for exceptions
    $exception_list = $global['exception_list'];
    $result = null;
    $exception = null;
    $is_abort = false;

    if(isset($exception_list)) {
        foreach($exception_list as $ex){
            $res = $ex->getResult();
            $exception = $ex;
            $result = $res;
            if(isset($res) && $res==REPORT_AND_ABORT) {
                break;
            }
        }
        if ($result == REPORT_AND_ABORT) {
            add_error($exception->getMessage());
            $is_abort = true;
        } else if ($result == REPORT_AND_CONTINUE) {
            add_warning($exception->getMessage());
        }
    }

    // display the errors first before the rest of the module output
    display_errors();
    display_submit_message('confirmation', '&nbsp;');
    display_submit_message('warning', 'Warning');
    display_submit_message('information', 'Information');
    if ($is_abort == false) {
        echo $output;
    }

    echo "</div>";

    echo "</div>";
    echo "<!-- /content -->";

    include_once($global['approot'].'/www/theme/'.$global['theme'].'/footer.php');

    echo "</div>";
    echo "<!-- /wrapper -->";

    echo "</div>";
    echo "<!-- /container -->";

    echo "</body>";
    echo "</html>";
    ob_flush();
}

function _shn_text_display_errors() {
    global $global;
    if (count($global['submit_errors']) > 0) {
        echo "Uhoh.. There were a few errors!<br><br>";
        $i = 1;
        foreach ($global['submit_errors'] as $err) {
            echo "#".$i." ".$err."<br>";
            $i++;
        }
    }

}







