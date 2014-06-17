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
function shn_install_default($confGenerator) {

    global $global;
    echo  _t('<p>Installer under construction. Please report any issues at ')
        . '<a href="https://github.com/ramdesh/vesuvius_installer/issues">' . _t('the Github page.</a></p><br>');
    
    $error = shn_system_error_check();
     if (!$error){
         
         include_once($global['approot'].'/mod/install/SHN_AccessGenerator.php');
         
         $accessGenerator = new SHN_AccessGenerator($global['approot']);
         $accessGenerator->writeHtaccess();
         
         $confGenerator->writeConfInit();
     }
}

/**
 * check if system is configured to continue installation
 * @todo: check for version compatibility of php, mysql, etc..
 */
function shn_system_error_check(){
    global $global;
    $error = false;
    if(!is_writable($global['approot'] . '/conf')){
        add_error("no write access to \" /conf \" directory");
        $error = true;
    } 
    if (!is_writable($global['approot'] . '/www')){
        add_error("no write access to \" /www \" directory");
        $error = true;
    } 
    if ($error){
        shn_form_fopen2("", null, false);
            shn_form_fsopen("System Configurations");
                echo _t("Please modify your system according to the errors above and click recheck to continue installation<br/><br/>");
                shn_form_submit('Recheck');
            shn_form_fsclose();
        shn_form_fclose();
    }
    return $error;
}


/**
 * Create database while the instalation process.
 *
 * @param Array $db_params Parameters array obtained from the installation form.
 * @return boolean Whether creating is success or not. 
 */
function shn_create_database($db_params) {

    // This option is needed showing errors
    define('ADODB_ERROR_HANDLER_TYPE', E_USER_WARNING);

    // Include required ADOdb classes
    require_once('../3rd/adodb/adodb-errorhandler.inc.php');
    require_once('../3rd/adodb/adodb.inc.php');

    $db_type = 'mysql';
    $db = ADONewConnection($db_type);
    $db->debug = FALSE;

    // Connect to the dbms server
    $ok = $db->Connect($db_params['db_host'], $db_params['db_user'], $db_params['db_pass']);

    // If connection is successful
    if ($ok) {

        // Get creata database query
        $dict = NewDataDictionary($db);
        $sql = $dict->CreateDatabase($db_params['db_name']);

        // Try to create the database
        if ($dict->ExecuteSQLArray($sql) == 2) {
            return true;
        } else {
            add_error(_t("Create database encountered an error: ") . $db->ErrorMsg());
        }

    } else {
        add_error(_t("Connecting to server encountered an error: ") . $db->ErrorMsg());
    }

    return false;

}



function shn_install_stream_init() {

    global $global;

    echo '<body>'
        . '<div id="container">';

    include_once($global['approot'].'/www/theme/'.$global['theme'].'/header.php');

    echo  '<div id="wrapper" class="clearfix">'
        . '<div id="wrapper_menu">'
        . '<div id="menuwrap">'
        . '<ul id="menu">'
        . '</ul>'
        . '</div>'
        . '</div>'
        . '<div id="content">'
        . '<div style="padding: 20px 0px 0px 36px; font-size: 16px;">';
    
    ob_start();
}
function shn_install_stream_close() {
    global $global;

    // flush the output buffer
    $output = ob_get_contents();
    ob_end_clean();

    // check for exceptions
    if(array_key_exists("exception_list",$global)){
		$exception_list = $global['exception_list'];
		}
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

    echo  '</div>'
        . '</div>';

    include_once($global['approot'].'/www/theme/'.$global['theme'].'/footer.php');

    echo  '</div>'
        . '</div>'
        . '</body>'
        . '</html>';
    ob_flush();
}

function _shn_text_display_errors() {
    global $global;
    if (count($global['submit_errors']) > 0) {
        echo _t("Uhoh.. There were a few errors!<br><br>");
        $i = 1;
        foreach ($global['submit_errors'] as $err) {
            echo "#".$i." ".$err."<br>";
            $i++;
        }
    }

}
