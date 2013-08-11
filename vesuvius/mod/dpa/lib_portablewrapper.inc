<?php

/**
 * @name         Dynamic Portable App Portable Wrapper Download Functions
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0811
 */
function shn_dpa_wrapper_fix_win() {
    global $conf;
    $wrapper_file = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN;
    shn_dpa_wrapper_fix($wrapper_file, 'shn_dpa_win_wrapper_dlprogress', "Windows");
}

function shn_dpa_wrapper_fix($wrapper_file, $wrapper_dlprogress, $platform) {
    ignore_user_abort(true); // run script in background 
    set_time_limit(0); // run script forever     
    // end any previously started output buffer handlers
    while (ob_get_level()) {
        ob_end_clean();
    }
    ob_start();

    $wrapper_file_tmp = $wrapper_file . '.tmp';
    $wrapper_file_status = $wrapper_file . '.status';
    $ch_status = false;
    $repo = shn_dpa_get_repo_data();

    if (file_exists($wrapper_file_tmp)) {
        $response = "Wrapper file download has already started.";
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }

    if (file_exists($wrapper_file)) {
        $response = "Wrapper file already exists." . $wrapper_file;
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }

    if ($repo['status'] === "active") {
        //This is the file where we save the data received from the repository
        $fp = fopen($wrapper_file_tmp, 'w+');
        // close the session before starting the long running process
        session_write_close();
        $url = $repo['url'];
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_BUFFERSIZE, 1024);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_PROGRESSFUNCTION, $wrapper_dlprogress);
        curl_setopt($ch, CURLOPT_FILE, $fp); // write curl response to file
        curl_setopt($ch, CURLOPT_NOPROGRESS, false); // needed to make progress function work
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 10);
        curl_setopt($ch, CURLOPT_FORBID_REUSE, 0);
        shn_dpa_add_log("Starting portable wrapper file download for " . $platform);
        $ch_status = curl_exec($ch);
        curl_close($ch);
    } else {
        $response = "Portable wrappers repository did not repond. Please check repository URL";
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }
    $file_status = false;
    if (file_exists($wrapper_file_tmp)) {
        fclose($fp);
        if (hash_file('md5', $wrapper_file_tmp) === $repo['checksum']) {
            $file_status = true;
            rename($wrapper_file_tmp, $wrapper_file);
            shn_dpa_add_log("Portable wrapper file successfully downloaded for " . $platform);
        } else {
            unlink($wrapper_file_tmp);
            shn_dpa_add_log("Portable wrapper file download failed for " . $platform . ". File integrity check failed.");
        }
    } else {
        shn_dpa_add_log("Portable wrapper file download failed for " . $platform . ". Connection error.");
    }

    if (file_exists($wrapper_file_status))
        unlink($wrapper_file_status);

    if ($file_status !== false) {
        $response = "OK! Wrapper file successfully downloaded. Page will be refreshed now.<script>setTimeout(function() { location.reload();}, 2000); </script>";
    } else {
        $response = "Error! Something went wrong. Goto View Log section for more details. Please try again later";
    }
    $data = array('response' => $response);
    echo json_encode($data);
    exit;
}

function shn_dpa_win_wrapper_dlprogress($download_size, $downloaded, $upload_size, $uploaded) {
    global $conf;
    $filename_status = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN . ".status";
    if ($download_size > 0) {
        $progress = $downloaded / $download_size * 100;
        $progress = number_format((float) $progress, 2, '.', '');
        file_put_contents($filename_status, $progress);
    }
}

function shn_dpa_win_wrapper_status() {
    global $conf;
    $wrapper_file = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN;
    $wrapper_file_tmp = $wrapper_file . '.tmp';
    $wrapper_file_status = $wrapper_file . '.status';

    // end any previously started output buffer handlers
    while (ob_get_level()) {
        ob_end_clean();
    }
    ob_start();
    $res = "";
    if (file_exists($wrapper_file)) {
        $res = "Portable wrapper file download is complete! Page will be refreshed now.<script>setTimeout(function() { location.reload();}, 2000); </script>";
    } elseif (file_exists($wrapper_file_tmp) && file_exists($wrapper_file_status)) {
        $res = "Portable wrapper file is being downloaded. Download Progess: " . file_get_contents($wrapper_file_status) . " %";
    } else {
        $res = "Portable wrapper file download has failed.";
    }
    $data = array('response' => $res);
    echo json_encode($data);
    exit;
}