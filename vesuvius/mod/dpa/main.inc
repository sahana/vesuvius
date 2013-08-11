<?php
/**
 * @name         Dynamic Portable App Controller Functions
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0811
 */
// Module Status definitions
define('DPA_STATUS_OK', 1);
define('DPA_STATUS_FAIL', -1);
define('DPA_STATUS_DOWNLOADING', 2);
define('DPA_DEBUG', false);
define('DPA_WRAPPER_WIN', 'portable-wrapper_win.zip'); // Portable wrapper for Microsoft Windows Platform

include_once ($global['approot'] . '/mod/dpa/lib_portableapp.inc');
include_once ($global['approot'] . '/mod/dpa/lib_portablewrapper.inc');
include_once ($global['approot'] . '/mod/dpa/lib_helper.inc');

function shn_dpa_default() {
    /* DEBUG INFO */
    if (DPA_DEBUG) {
        echo 'REQUEST_URI: ' . $_SERVER['REQUEST_URI'] . PHP_EOL;
        echo 'REQUEST_URI: ' . $_SERVER['PHP_SELF'] . PHP_EOL;
    }

    // perform a pre-check to make sure everything is in place
    shn_dpa_precheck();

    // load common html stuff
    shn_dpa_load_html();

    $active_html = '<span style="background-image: url(../res/img/ok-icon.png); background-size:18px 18px; background-repeat:no-repeat; height: 20px; color: #008000; font-weight: bold; padding-left: 30px;">ACTIVE</span>';
    $failure_html = '<span style="background-image: url(../res/img/error-icon.png); background-size:20px 20px; background-repeat:no-repeat; height: 20px; color: red; font-weight: bold; padding-left: 30px;">INACTIVE</span>';

    // check module status
    $dpa_status = (shn_dpa_isActive()) ? $active_html : $failure_html;
    echo '<span style="font-size: 16px;color: #039;">Dynamic Portable App Status:&nbsp; ' . $dpa_status . '</span><span class="dpa_tooltip_icon">?</span><br/><br/>';
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
        $control = "shn_dpa_wrapper_fix_win";
    } elseif (isset($_GET['winwrapperstatus'])) {
        $control = "shn_dpa_win_wrapper_status";
    }

    if ($control == "") {
        $control = "shn_dpa_status";
    }
    call_user_func($control);
}

function shn_dpa_status() {

    $status_ok_html = "<div style=\"background-image: url(../res/img/ok-icon.png); background-size:18px 18px; background-repeat:no-repeat; height: 20px; color: #008000; font-weight: bold; padding-left: 30px;\">OK</div>";
    $status_downloading_html = "<div style=\"background-image: url(../res/img/download-icon.png); background-size:22px 22px; background-repeat:no-repeat; height: 22px; color: #FF9933; font-weight: bold; padding-left: 30px;\">DOWNLOADING</div>";
    $status_error_html = "<div style=\"background-image: url(../res/img/error-icon.png); background-size:20px 20px; background-repeat:no-repeat; height: 20px; color: red; font-weight: bold; padding-left: 30px;\">FAILED</div>";

    $dpa_status = shn_dpa_check_status();
    $bin_status_html = ($dpa_status['bin_directory'] === DPA_STATUS_OK) ? $status_ok_html : $status_error_html;
    $repo_status_html = ($dpa_status['repository'] === DPA_STATUS_OK) ? $status_ok_html : $status_error_html;
    $wrapper_status_html = ($dpa_status['win_wrapper'] === DPA_STATUS_OK) ? $status_ok_html : (($dpa_status['win_wrapper'] === DPA_STATUS_DOWNLOADING) ? $status_downloading_html : $status_error_html);
    ?>   
    <div id="result" style="padding: 10px 5px 10px 15px;">
        <table id="tbl_dpa_status" style="width: 750px;" >
            <thead>
            <td style="width: 400px;"><strong><center>Prerequisites Checklist</center></strong></td>
            <td style="width: 200px;"><strong>Status</strong></td>
            <td style="width: 150px;"><strong>Options</strong></td>
            </thead>
            <tbody>
                <tr>
                    <td><strong>bin</strong> directory is writable</td>
                    <td> <? echo $bin_status_html; ?> </td>
                    <td><center><input id="btn_status_bindir_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; <? if ($dpa_status['bin_directory'] === DPA_STATUS_OK) echo "display:none;" ?> " /></center></td>
            </tr>
            <tr>
                <td>Portable wrappers repository is active</td>
                <td> <? echo $repo_status_html; ?> </td>
                <td><center><input id="btn_status_repo_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; <? if ($dpa_status['repository'] === DPA_STATUS_OK) echo "display:none;" ?> " /></center></td>
            </tr>
            <tr>
                <td>Portable wrapper for Microsoft Windows platform is available</td>
                <td> <? echo $wrapper_status_html; ?> </td>
                <td><center>
                <? if ($dpa_status['win_wrapper'] === DPA_STATUS_FAIL) { ?>
                    <input id="btn_status_win_wrapper_fix" type="button" value="Fix" class="styleTehButton" style="padding: 3px 12px 3px 12px; " />
                <? } elseif ($dpa_status['win_wrapper'] === DPA_STATUS_DOWNLOADING) { ?>
                    <input id="btn_status_win_wrapper_progress" type="button" value="Check Progress" class="styleTehButton" style="padding: 3px 5px 3px 5px; " />
                <? } ?>
            </center></td>

            </tr>
            </tbody>
        </table>
    </div>
    <?php
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
			<h5>*Note: For a complete description of each module and its functionality please follow this <a href="http://wiki.sahanafoundation.org/doku.php/agasti:vesuvius:modules" target="_blank">link</a>.</h5>
            
            <div id="dpa_download" style="padding: 10px 5px 10px 15px;">
         ';
    shn_form_fopen2("vesuvius-portable?downloadp", null, array('req_message' => false, 'id' => 'dpa_download_form'));

    echo '
			<div id="result">
				<div style="margin: 0 0 10px 5px;">
					<a id="dpa_checkall" class="dpa_toolbar" href="#">Check All</a> 
					<a id="dpa_uncheckall" class="dpa_toolbar" href="#" style="padding-left: 10px;">Uncheck All</a>
				</div>
				<table style="width: 100%;">
				<thead>
					<td style="width: 20px; ">&nbsp;</td>
					<td style="width: 180px; ">Module Name</td>
					<td style="width: 75%; ">Module Description</td>
				</thead>
				<tbody>
		 ';

    $mods = shn_get_all_modules();

    foreach ($mods as $mod => $mod_arr) {
        $checked = "";
        if (in_array($mod_arr[0], $conf['mod_dpa_required'])) {
            $checked = 'checked = "checked" disabled="disabled"';
            $class = 'required_modules';
        } else {
            $class = 'modules';
        }
        echo '
                <tr>
                    <td style="text-align: center; padding: 5px 5px 5px 5px;">
             ';

        echo '<input type="checkbox" class="' . $class . '" name="' . $mod_arr[0] . '" align="right" ' . $checked . ' />';

        echo '
                </td>
                    <td>' . $mod_arr[1] . '</td>
					<td>' . shn_dpa_get_mod_desc($mod_arr[0]) . '</td>
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
    $portable_wrapper_file = "";
    // Get user selected platform
    $os = (isset($_GET['os'])) ? trim($_GET['os']) : "";
    if ($os === "windows") {
        $portable_wrapper_file = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN;
    }

    // unique string to identify file download session
    $nonce_str = (isset($_GET['nonce'])) ? trim($_GET['nonce']) : "";

    if (file_exists($portable_wrapper_file)) {
        $download_file = shn_dpa_create_portable_app($portable_wrapper_file);
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
        shn_dpa_add_log("Failed to create Portable App.");
        setcookie("FILE_READY", $nonce_str . ":ERROR", 0, "/");
    }
    ob_end_flush();
    exit;
}

function shn_dpa_log() {
    global $conf;
    $log_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_log_file'];
    echo '
            <div id="result" class="logArea" style="height: 400px; padding: 10px 5px 10px 15px;">
            <table style="width: 100%;">
                            <thead>
                    <td style="width: 75px;"><strong>Date</strong></td>
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