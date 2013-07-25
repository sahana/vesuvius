<?php
/**
 * @name         Dynamic Portable App
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0723
 */
include_once ($global['approot'] . '/mod/dpa/PortableAppFactory.inc');
include_once ($global['approot'] . '/mod/dpa/file_download.inc');

define('STATUS_OK', 1);
define('STATUS_FAIL', -1);
define('STATUS_DOWNLOADING', 2);

function shn_dpa_check_status() {
    global $global, $conf;
    $bin_dir_status = (file_exists($conf['mod_dpa_bin']) && is_writable($conf['mod_dpa_bin'])) ? STATUS_OK : STATUS_FAIL;
    $repository_status = (shn_dpa_get_repo_status()) ? STATUS_OK : STATUS_FAIL;
    $win_wrapper_status = (file_exists($conf['mod_dpa_bin'] . "portable-bin_win.zip")) ? STATUS_OK : STATUS_FAIL;
    if ($win_wrapper_status === STATUS_FAIL) {
        $win_wrapper_status = (file_exists($conf['mod_dpa_bin'] . "portable-bin_win.zip.tmp")) ? STATUS_DOWNLOADING : STATUS_FAIL;
    }

    $status_arr = array(
        'bin_directory' => $bin_dir_status,
        'repository' => $repository_status,
        'win_wrapper' => $win_wrapper_status
    );
    return $status_arr;
}

function shn_dpa_isActive() {
    $status = shn_dpa_check_status();
    if ($status['bin_directory'] === STATUS_OK && $status['win_wrapper'] === STATUS_OK)
        return true;
    else
        return false;
}

function shn_dpa_load_html() {
    global $global, $conf;
    echo '
            <style type="text/css">
                .window {
                    position:fixed;
                    left:0;
                    top:0;                    
                    display:none;
                    z-index:9999;
                    padding:20px;
                }
                
                #dpa_dialog {
                    width:700px; 
                    height:100px;
                    padding:10px;
                    background-color:#E5EAEF;
                    border: 2px solid rgba(52, 104, 154, 0.15);
                    text-align: center;
                }
            </style>
         ';

    echo '<div id="dpa_dialog" class="window" title="Dynamic Portable App"></div>';

    echo '
            <script type="text/javascript" src="res/js/jquery-1.6.4.min.js" ></script>
            <script type="text/javascript" src="res/js/jquery-ui-effectscore.min.js" ></script>
            <script type="text/javascript">' . file_get_contents($global['approot'] . "/mod/dpa/dpa.js") . '</script>
         ';
}

function shn_dpa_precheck() {
    global $global, $conf;
    // check if the person is not logged in or is anonymous (must be logged in and not anonymous)
    if (!isset($_SESSION['logged_in']) || $_SESSION['logged_in'] != 1 || !isset($_SESSION['group_id']) || $_SESSION['group_id'] == 3) {
        echo '
			<div class="message information"><br/>' . _t('DPA-Message|You must log in before you can download a copy of Dynamic Portable App.') . '
			<br><br></div>
			<br>
		';
        require_once($global['approot'] . 'mod/pref/main.inc');
        shn_pref_loginForm();
        return;
    }

    // check if curl extension is loaded, if not disable module functionality
    if (!(_is_curl_installed())) {
        add_error("PHP extension 'curl' is not loaded. The module is disabled.");
        add_error("Please install PHP 'curl' extension and try again.");
        return;
    }

    // check if zip extension if loaded, if not disable module functionality
    if (!extension_loaded('zip')) {
        add_error("PHP extension 'zip' is not loaded. The module is disabled.");
        add_error("Please install PHP 'zip' extension and try again.");
        return;
    }

    // check bin directory exists, try to create if not
    if (!file_exists($conf['mod_dpa_bin'])) {
        if (!mkdir($conf['mod_dpa_bin'], 0777, true)) {
            add_error("Could not create 'bin' directory. Portable App module may not function properly.");
            add_error("Please set a valid path as the 'bin' directory.");
        }
    } else {
        if (!is_writable($conf['mod_dpa_bin'])) {
            chmod($conf['mod_dpa_bin'], 0755);
        }
    }
}

function shn_dpa_default() {
    // perform a pre-check to make sure everything is in place
    shn_dpa_precheck();

    // load common html stuff
    shn_dpa_load_html();

    $active_html = '<span style="background-image: url(../res/img/ok-icon.png); background-size:18px 18px; background-repeat:no-repeat; height: 20px; color: #008000; font-weight: bold; padding-left: 30px;">ACTIVE</span>';
    $failure_html = '<span style="background-image: url(../res/img/error-icon.png); background-size:20px 20px; background-repeat:no-repeat; height: 20px; color: red; font-weight: bold; padding-left: 30px;">INACTIVE</span>';

    // check module status
    $dpa_status = (shn_dpa_isActive()) ? $active_html : $failure_html;
    echo "<h3>Dynamic Portable App Status: " . $dpa_status . "</h3><br/>";
    $control = "";
    shn_tabmenu_open();
    shn_tabmenu_item("status", _t("DPA-Menu|Status"), 'dpa');
    shn_tabmenu_item("config", _t("DPA-Menu|Configuration"), 'dpa');
    shn_tabmenu_item("download", _t("DPA-Menu|Download"), 'dpa');
    shn_tabmenu_item("log", _t("DPA-Menu|View Log"), 'dpa');
    shn_tabmenu_close();

    if (isset($_GET['status'])) {
        $control = "shn_dpa_status";
    } elseif (isset($_GET['config'])) {
        $control = "shn_dpa_config";
    } elseif (isset($_GET['download'])) {
        $control = "shn_dpa_download";
    } elseif (isset($_GET['log'])) {
        $control = "shn_dpa_log";
    } elseif (isset($_GET['configp'])) {
        $control = "shn_dpa_config_p";
    } elseif (isset($_GET['downloadp'])) {
        $control = "shn_dpa_download_p";
    } elseif (isset($_GET['winwrapperfix'])) {
        $control = "shn_dpa_win_wrapper_fix";
    } elseif (isset($_GET['winwrapperstatus'])) {
        $control = "shn_dpa_win_wrapper_status";
    }

    if ($control == "") {
        $control = "shn_dpa_status";
    }
    $control();
}

function shn_dpa_get_repo_data() {
    $dpa_config = shn_dpa_read_config();
    $service_url = (isset($dpa_config['end_point'])) ? $dpa_config['end_point'] : "";
    if ($service_url === "") {
        return false;
    }
    $curl = curl_init($service_url);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 2);
    $curl_response = curl_exec($curl);
    curl_close($curl);

    if ($curl_response !== false) {
        return json_decode($curl_response, true);
    }
    return false;
}

function shn_dpa_get_repo_status() {
    $repo_response = shn_dpa_get_repo_data();
    if ($repo_response !== false) {
        if ($repo_response['status'] === "active")
            return true;
    }
    return false;
}

function shn_dpa_status() {

    $status_ok_html = "<div style=\"background-image: url(../res/img/ok-icon.png); background-size:18px 18px; background-repeat:no-repeat; height: 20px; color: #008000; font-weight: bold; padding-left: 30px;\">OK</div>";
    $status_downloading_html = "<div style=\"background-image: url(../res/img/download-icon.png); background-size:22px 22px; background-repeat:no-repeat; height: 22px; color: #FF9933; font-weight: bold; padding-left: 30px;\">DOWNLOADING</div>";
    $status_error_html = "<div style=\"background-image: url(../res/img/error-icon.png); background-size:20px 20px; background-repeat:no-repeat; height: 20px; color: red; font-weight: bold; padding-left: 30px;\">FAILED</div>";

    $dpa_status = shn_dpa_check_status();
    $bin_status_html = ($dpa_status['bin_directory'] === STATUS_OK) ? $status_ok_html : $status_error_html;
    $repo_status_html = ($dpa_status['repository'] === STATUS_OK) ? $status_ok_html : $status_error_html;
    $wrapper_status_html = ($dpa_status['win_wrapper'] === STATUS_OK) ? $status_ok_html : (($dpa_status['win_wrapper'] === STATUS_DOWNLOADING) ? $status_downloading_html : $status_error_html);
    ?>   
    <div id="result" style="padding: 10px 5px 10px 15px;">
        <table id="tbl_dpa_status" style="width: 750px;" >
            <thead>
            <td style="width: 400px;"><strong><center>Requirements check</center></strong></td>
            <td style="width: 200px;"><strong>Status</strong></td>
            <td style="width: 150px;"><strong>Options</strong></td>
            </thead>
            <tbody>
                <tr>
                    <td><strong>bin</strong> directory is writable</td>
                    <td> <? echo $bin_status_html; ?> </td>
                    <td><center><input id="btn_status_bindir_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; <? if ($dpa_status['bin_directory'] === STATUS_OK) echo "display:none;" ?> " /></center></td>
            </tr>
            <tr>
                <td>Portable wrappers repository is active</td>
                <td> <? echo $repo_status_html; ?> </td>
                <td><center><input id="btn_status_repo_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; <? if ($dpa_status['repository'] === STATUS_OK) echo "display:none;" ?> " /></center></td>
            </tr>
            <tr>
                <td>Portable wrapper for Microsoft Windows platform is available</td>
                <td> <? echo $wrapper_status_html; ?> </td>
                <td><center>
                <? if ($dpa_status['win_wrapper'] === STATUS_FAIL) { ?>
                    <input id="btn_status_win_wrapper_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; " />
                <? } elseif ($dpa_status['win_wrapper'] === STATUS_DOWNLOADING) { ?>
                    <input id="btn_status_win_wrapper_progress" type="button" value="Check Progress" class="styleTehButton" style="padding: 3px 5px 3px 5px; " />
                <? } ?>
            </center></td>

            </tr>
            </tbody>
        </table>
    </div>
    <?php
}

function shn_dpa_read_config() {
    global $conf;
    $config_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_config_file'];
    if (!file_exists($config_file)) {
        add_error("Error reading Portable App module configuration. File could not be found.");
        return false;
    }
    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;
    $doc->load($config_file);
    $nodes = $doc->getElementsByTagName("dynamic-portable-app")->item(0)->childNodes;
    $portable_conf_data = array();
    foreach ($nodes as $node) {
        if ($node->nodeType === 1) {
            $portable_conf_data[(string) $node->nodeName] = (string) $node->nodeValue;
        }
    }
    return $portable_conf_data;
}

function shn_dpa_save_config($config_arr) {
    global $conf;
    $config_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_config_file'];

    if (file_exists($config_file)) {
        $doc = new DOMDocument();
        $doc->load($config_file);
        $nodes = $doc->getElementsByTagName("dynamic-portable-app")->item(0)->childNodes;
        foreach ($nodes as $node) {

            if ($node->nodeType === 1) {
                if (!array_key_exists($node->nodeName, $config_arr)) {
                    $config_arr[(string) $node->nodeName] = (string) $node->nodeValue;
                }
            }
        }
    }

    $doc = new DOMDocument();
    $doc->formatOutput = true;

    $r = $doc->createElement("dynamic-portable-app");
    $doc->appendChild($r);
    foreach ($config_arr as $key => $value) {
        $node = $doc->createElement($key);
        $node->appendChild($doc->createTextNode($value));
        $r->appendChild($node);
    }

    $res = $doc->save($config_file);
    if ($res === false) {
        return false;
    } else {
        return true;
    }
}

function shn_dpa_config_p() {

    $end_point_txt = (isset($_POST['end_point'])) ? trim($_POST['end_point']) : "";

    if ($end_point_txt === "" || !filter_var($end_point_txt, FILTER_VALIDATE_URL)) {
        add_error("Enter a valid repository end point URL.");
        add_error("Please complete and submit again.");
    } else {
        $config_arr = array(
            'end_point' => $end_point_txt
        );

        if (shn_dpa_save_config($config_arr)) {
            shn_dpa_add_log("Repository URL updated to " . $end_point_txt);
            add_confirmation("Portable App repository was successfully updated.");
        } else {
            add_error("Could not create portable configuration.");
        }
    }

    shn_dpa_config();
}

function shn_dpa_config() {

    $portable_conf_data = shn_dpa_read_config();
    if ($portable_conf_data !== false) {
        $extra_opts['value'] = $portable_conf_data['end_point'];
    }
    $extra_opts['req'] = true;

    echo '
            <div id="dpa_config" style="padding: 10px 5px 10px 15px;">
         ';

    shn_form_fopen2("dpa?configp&tabid=1");
    shn_form_fsopen("Repository Details");

    shn_form_text("End-point URL", 'end_point', 'size="80" autocomplete="off"', $extra_opts);
    shn_form_fsclose();
    shn_form_fsclose();
    echo "</br>";
    shn_form_submit("Submit", "class=\"styleTehButton\"");
    echo "</br>";
    shn_form_fclose();
    echo "</div>";
}

function shn_dpa_download() {

    global $conf, $global;
    if (!shn_dpa_isActive()) {
        add_error("Dynamic Portable App module is inactive.");
        add_error("Please goto status section for more details.");
        return;
    }

    echo '
            <b>Select/Unselect Modules</b> ~ Only selected modules will be available in the Portable App created.<br/><br/>
            <h5>*Note: Existing user accounts will <u>not</u> be available in the downloaded Portable App. You will be prompted to create a new admin account at the first run.</h5>
            <h5>*Note: Some important modules are selected by default.</h5>
            
            <div id="dpa_download" style="padding: 10px 5px 10px 15px;">
         ';
    shn_form_fopen2("vesuvius-portable?downloadp", null, array('req_message' => false, 'id' => 'dpa_download_form'));

    echo '
		<div id="result">
			<table style="width: 400px;">
			<thead>
			<td style="width: 30px; ">&nbsp;</td>
                        <td>Module Name</td>
                        </thead>
                        <tbody>
	';

    $mods = shn_get_all_modules();

    foreach ($mods as $mod => $mod_arr) {
        $checked = "";
        if (in_array($mod_arr[0], $conf['mod_dpa_required'])) {
            $checked = 'checked = "checked" disabled="disabled"';
        }
        echo '
                <tr>
                    <td style="text-align: center; padding: 5px 5px 5px 5px;">
             ';

        echo '<input type="checkbox" class="modules" name="' . $mod_arr[0] . '" align="right" ' . $checked . ' />';

        echo '
                </td>
                    <td>' . $mod_arr[1] . '</td>
                </tr>
        ';
    }
    echo '
		</tbody>
		</table>
		</div>
	';

    shn_form_fsopen("Select Operating System");
    $extra_opts['req'] = true;
    shn_form_select(array("windows" => 'Microsoft Windows Platform'), "Download Portable App for ", 'os', null, $extra_opts);
    shn_form_fsclose();

    shn_form_submit("Download", 'class="styleTehButton" id="#btn_download" ');
    shn_form_fclose();

    echo "</div>";
}

function shn_dpa_download_p() {

    global $conf;

    ignore_user_abort(true); // run script in background 
    set_time_limit(0); // run script forever     
    // end any previously started output buffer handlers
    while (ob_get_level()) {
        ob_end_clean();
    }

    ob_start();

    $download_file = false;
    $platform = "";
    // Get user selected platform
    $os = (isset($_GET['os'])) ? trim($_GET['os']) : "";
    if ($os === "windows") {
        $platform = "win";
    }

    $nonce_str = (isset($_GET['nonce'])) ? trim($_GET['nonce']) : "";
    $portable_bin = $conf['mod_dpa_bin'] . 'portable-bin_' . $platform . '.zip';

    if (file_exists($portable_bin)) {
        $download_file = shn_dpa_create_portable_app($portable_bin);
    }

    if ($download_file !== false && file_exists($download_file)) {
        shn_dpa_add_log("Portable App successfully created.");
        setcookie("FILE_READY", $nonce_str, 0, "/");
        setcookie("FILE_CHECKSUM", hash_file('md5', $download_file), 0, "/");
        session_write_close();

        header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
        header("Expires: Sat, 26 Jul 1997 05:00:00 GMT"); // Date in the past
        header('Content-Type: application/zip');
        header('Content-Transfer-Encoding: binary');
        header('Content-Disposition: attachment; ');
        header("Content-Description: File Transfer");
        header('Content-Length: ' . filesize($download_file));

        if (readfile_chunked($download_file)) {
            shn_dpa_add_log("Portable App download failed...connection was closed.");
        } else {
            shn_dpa_add_log("Portable App successfully downloaded by the user.");
        }

        unlink($download_file);
    } else {
        setcookie("FILE_READY", $nonce_str . ":ERROR", 0, "/");
    }
    ob_end_flush();
    exit;
}

function readfile_chunked($filename) {
    $chunksize = 1 * (1024 * 1024); // 1MB per chunk
    $buffer = "";
    $handle = fopen($filename, 'rb');
    if ($handle === false) {
        return false;
    }

    $conn_aborted = false;
    while (!feof($handle) && !$conn_aborted) {
        $buffer = fread($handle, $chunksize);
        echo $buffer;
        if (connection_status() != CONNECTION_NORMAL) {
            $conn_aborted = true;
        }
        ob_flush();
        flush();
    }
    fclose($handle);
    return $conn_aborted;
}

function shn_dpa_log() {
    global $conf;
    $log_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_log_file'];
    echo '
            <div id="result" class="logArea" style="height: 400px; padding: 10px 5px 10px 15px;">
            <table style="width: 100%;">
                            <thead>
                    <td style="width: 50px;"><strong>Date</strong></td>
                    <td style="width: 50px;"><strong>Time</strong></td>
                    <td style="width: 25px;"><strong>User IP</strong></td>
                    <td style="width: 30px;"><strong>Username</strong></td>
                    <td style="width: 400px;"><strong>User Activity</strong></td>
                    
                </thead>
	';
    if (!file_exists($log_file)) {
        file_put_contents($log_file, "", LOCK_EX);
    }
    $file_handle = fopen($log_file, "r");
    while (!feof($file_handle)) {

        $line = trim(fgets($file_handle));
        if ($line !== "") {
            $arr = explode("|", $line, 5);
            echo "<tr>";
            echo "<td>" . $arr[0] . "</td>";
            echo "<td>" . $arr[1] . "</td>";
            echo "<td>" . $arr[2] . "</td>";
            echo "<td>" . $arr[3] . "</td>";
            echo "<td>" . $arr[4] . "</td>";

            echo "</tr>";
        }
    }
    fclose($file_handle);

    echo "
            </table>
            </div>
        ";
}

function shn_dpa_add_log($msg) {
    global $conf;
    $log_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_log_file'];

    $date = getdate();

    $data = $date['year'] . " " . $date['month'] . " " . $date['mday'] . "|";
    $data = $data . $date['hours'] . ":" . $date['minutes'] . ":" . $date['seconds'] . "|";
    $data = $data . $_SERVER['REMOTE_ADDR'] . "|" . $_SESSION['user'] . "|" . $msg . PHP_EOL;

    if (!file_exists($log_file)) {
        file_put_contents($log_file, "", LOCK_EX);
    }

    $fp = fopen($log_file, "a+");
    if ($fp && flock($fp, LOCK_EX)) { // lock the log file
        fwrite($fp, $data);
        flock($fp, LOCK_UN); // release the lock
        fclose($fp);
    }
}

function _is_curl_installed() {
    if (in_array('curl', get_loaded_extensions())) {
        return true;
    } else {
        return false;
    }
}