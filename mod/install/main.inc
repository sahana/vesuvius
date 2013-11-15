<?
/**
 * @name         Installer
 * @version      1
 * @package      install
 * @author       Ramindu Deshapriya <rasade88@gmail.com> <rdeshapriya@virtusa.com>
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0911
 */





function shn_install_default() {

	global $global;
	echo '<p>Installer under construction</p><br>';

    shn_write_htaccess();
}

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
     add_confirmation("Successfully wrote .htaccess file");
    }
    fclose($file);
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







