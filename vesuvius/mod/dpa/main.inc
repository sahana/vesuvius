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
 * @lastModified 2013.0813
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
    shn_tabmenu_item("download", _t("DPA-Menu|Download"), 'dpa');
    shn_tabmenu_item("status", _t("DPA-Menu|Status"), 'dpa');
    shn_tabmenu_item("config", _t("DPA-Menu|Configuration"), 'dpa');
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
        $control = "shn_dpa_download";
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

    echo '<div id="dpa_download" style="padding: 10px 5px 10px 15px;">';

    shn_form_fopen2("vesuvius-portable?downloadp", null, array('req_message' => false, 'id' => 'dpa_download_form'));
    shn_form_fsopen("About Dynamic Portable App");
    echo '
            <p style="text-align:justify; color: black; font-size:13px; font-weight: bold; line-height:200%">
            Dynamic Portable App is created by copying the hosted code of a Vesuvius instance and packaging all that inside a portable wrapper archive.
            Portable App can be deployed into a portable device and launch without any configuration or installation overhead. Also it does not rely on network connectivity since Vesuvius instance is running locally.
            It can be taken into shelters in disaster zones for data collection when public communication infrastructure is impaired.
            </p>
            <p style="text-align:justify; color: black; font-size:13px; font-weight: bold; line-height:200%">
            Portable App can be customized to support only certain modules that exist in the parent Vesvuvius instance. Also it can be customized to contain only data related to a specific event. 
            </p>
        ';
    shn_form_fsclose();

    shn_form_fsopen("Select Modules");

    echo '        
            <h5>Note: Only selected modules will be available in the Portable App created.<h5>
            <h5>Note: Existing user accounts will <u>not</u> be available in the downloaded Portable App. You will be prompted to create a new admin account at the first run.</h5>
            <h5>Note: Some important modules are selected by default.</h5>
            <h5>Note: For a complete description of each module and its functionality please follow <a href="http://wiki.sahanafoundation.org/doku.php/agasti:vesuvius:modules" target="_blank">this link</a>.</h5>
         ';

    echo '
            <div id="result">
                    <div style="margin: 20px 0 10px 5px;">
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
    shn_form_fsclose();

    $disasters = shn_dpa_get_disasters();
    shn_dpa_event_js($disasters[1]);
    shn_form_fsopen("Select Filters");
    echo '<table><tr><td style="width: 20px; "><input type="checkbox" id="dpa_event_filter" name="dpa_event_filter" /></td><td>Enable filter by event</td></tr></table><br/>';
    echo '<h5>Note: Only the selected event will be available in the portable app.</h5>';
    echo '<h5>Note: Parent events will be automatically added.</h5>';

    shn_form_select($disasters[0], "Parent Disaster", 'dpa_selected_disaster', 'style="width: 200px" disabled');
    shn_form_select(array('-1' => 'N/A'), "Incident", 'dpa_selected_incident', 'style="width: 200px" disabled');
    shn_form_select(array('-1' => 'N/A'), "Event", 'dpa_selected_event', 'style="width: 200px" disabled=disabled');

    echo '<table><tr><td style="width: 20px; "><input type="checkbox" id="dpa_image_filter" name="dpa_image_filter" /></td><td>Include profile images</td></tr></table><br/>';
    echo '<h5>Note: Portable app file size will increase depending on the number of person records with images.</h5>';

    shn_form_fsclose();

    shn_form_fsopen("Select Operating System");
    $extra_opts['req'] = true;
    shn_form_select(array("windows" => 'Microsoft Windows Platform'), "Download Portable App for", 'dpa_target_os', null, $extra_opts);
    shn_form_fsclose();

    shn_form_fsopen("Publish to Site");
    echo '<table><tr><td style="width: 20px; "><input type="checkbox" id="dpa_enable_publish" name="dpa_enable_publish" /></td><td>Enable publish to site</td></tr></table><br/>';
    echo '
            <p style="text-align:justify; color: black; font-size:13px; line-height:200%">Allow registered users to download the portable app that will be created by publishing it to site. You will only get a confirmation message once
            the portable app creation process is successfully completed. Goto Manage section to manage previously published portable app instances.</p>
            <br/>
            <h5>Enter a description for this portable instance that will be displayed to other users.</h5>
         ';
    shn_form_text("Description", 'dpa_publish_desc', 'size="80" autocomplete="on" disabled=disabled');
    echo '<br/>';
    shn_form_submit("Publish only", 'class="styleTehButton" id="dpa_btn_publish" value="publish" disabled=disabled');
    shn_form_fsclose();

    shn_form_submit("Download", 'class="styleTehButton" id="dpa_btn_download" value="download" ');
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
    $os = (isset($_GET['dpa_target_os'])) ? trim($_GET['dpa_target_os']) : "";
    if ($os === "windows") {
        $portable_wrapper_file = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN;
    }

    if (file_exists($portable_wrapper_file)) {
        $download_file = shn_dpa_create_portable_app($portable_wrapper_file);
    }

    if (isset($_GET['enable_publish']) && $download_file !== false && file_exists($download_file)) {
        
    }
    if (isset($_GET['enable_download']) && $download_file !== false && file_exists($download_file)) {
        shn_dpa_add_log("Portable App successfully created.");
        // unique string to identify file download session
        $nonce_str = (isset($_GET['nonce'])) ? trim($_GET['nonce']) : "";
        setcookie("FILE_READY", $nonce_str, 0, "/");
        setcookie("FILE_CHECKSUM", hash_file('md5', $download_file), 0, "/");
        $file_url = "vesuviusportable.zip";
        session_write_close();

        if (ini_get('zlib.output_compression')) {
            ini_set('zlib.output_compression', 'Off');
        }

        if (strstr($_SERVER['HTTP_USER_AGENT'], "MSIE")) {
            header("Content-Type: application/zip");
            //header('Content-Disposition: attachment;filename="' . basename($file_url) . '"');
            header('Content-Disposition: attachment;');
            header('Expires: 0');
            header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
            header("Content-Transfer-Encoding: binary");
            header('Pragma: public');
            header("Content-Length: " . filesize($file_url));
        } else {
            header("Content-Type: application/zip");
            header('Content-Disposition: attachment;');
            //header('Content-Disposition: attachment;filename="' . basename($file_url) . '"');
            header('Content-Transfer-Encoding: binary');
            header("Expires: 0");
            header('Pragma: no-cache');
            header('Content-Length: ' . filesize($download_file));
        }
        if (readfile_chunked($download_file)) {
            shn_dpa_add_log("Portable App successfully downloaded by the user.");
        }
        unlink($download_file);
    }
    if ($download_file === false || !file_exists($download_file)) {
        shn_dpa_add_log("Failed to create Portable App.");
        setcookie("FILE_READY", $nonce_str . ":ERROR", 0, "/");
    }
    ob_end_flush();
    exit;
}

function shn_dpa_log() {
    global $conf;
    $log_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_log_file'];

    if (!file_exists($log_file)) {
        file_put_contents($log_file, "");
    }
    $file_handle = fopen($log_file, "r");
    if ($file_handle === false) {
        echo '<div id="result"><h2>Error reading log file.</h2></div>';
    } else {
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
        echo "
            </table>
            </div>
        ";
        fclose($file_handle);
    }
}