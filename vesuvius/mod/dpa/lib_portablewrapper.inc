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
 * @lastModified 2013.0726
 */
 


 
function shn_dpa_win_wrapper_fix() {
    global $global, $conf;
    ignore_user_abort(true); // run script in background 
    set_time_limit(0); // run script forever     
    // end any previously started output buffer handlers
    while (ob_get_level()) {
        ob_end_clean();
    }

    ob_start();
	$filename = $conf['mod_dpa_bin'] . DPA_WRAPPER_WIN;
    $filename_tmp = $filename . '.tmp';
    $filename_status = $filename . '.status';
    
    $ch_status = false;
    $repo = shn_dpa_get_repo_data();

    if (file_exists($filename_tmp)) {
        $response = "Wrapper file download has already started.";
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }

    if (file_exists($filename)) {
        $response = "Wrapper file already exists.";
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }

    if ($repo['status'] === "active") {
        $url = $repo['url'];
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_BUFFERSIZE, (1024 * 1024));

		//This is the file where we save the data received from the repository
        $fp = fopen($filename_tmp, 'w+'); 
		
		// close the session before starting the long running process
        session_write_close(); 

        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_PROGRESSFUNCTION, 'shn_dpa_win_wrapper_dlprogress');
        curl_setopt($ch, CURLOPT_FILE, $fp); // write curl response to file
        curl_setopt($ch, CURLOPT_NOPROGRESS, false); // needed to make progress function work
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_USERAGENT, $_SERVER['HTTP_USER_AGENT']);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 10);
        curl_setopt($ch, CURLOPT_FORBID_REUSE, 0);
        $ch_status = curl_exec($ch);
        curl_close($ch);
    } else {
        $response = "Portable wrappers repository did not repond. Please check repository URL";
        $data = array('response' => $response);
        echo json_encode($data);
        exit;
    }
    $file_status = false;
    if (file_exists($filename_tmp)) {
        fclose($fp);
        if (hash_file('md5', $filename_tmp) === $repo['checksum']) {
            $file_status = true;
            rename($filename_tmp, $filename);
        }else{
            unlink($filename_tmp);
        }        
    }

    if (file_exists($filename_status))
        unlink($filename_status);

    if ($file_status !== false) {
        $response = "OK! Wrapper file successfully downloaded. Page will be refreshed now.<script>setTimeout(function() { location.reload();}, 2000); </script>";
    } else {
        $response = "Error! Something went wrong. Please try again later";
    }
    $data = array('response' => $response);
    echo json_encode($data);
    exit;
}

function shn_dpa_win_wrapper_dlprogress($download_size, $downloaded, $upload_size, $uploaded) {
    global $global, $conf;
    $filename_status = $conf['mod_dpa_bin'] . '/portable-bin_win.zip.status';
    if ($download_size > 0) {
        $progress = $downloaded / $download_size * 100;
        $progress = number_format((float)$progress, 2, '.', '');
        file_put_contents($filename_status, $progress);
    }
}

function shn_dpa_win_wrapper_status() {
    global $global, $conf;
    $filename = $conf['mod_dpa_bin'] . '/portable-wrapper_win.zip';
    $filename_tmp = $filename . '.tmp';
    $filename_status = $filename . '.status';

    // end any previously started output buffer handlers
    while (ob_get_level()) {
        ob_end_clean();
    }
    ob_start();
    $res = "";
    if (file_exists($filename)) {
        $res = "Portable wrapper file download is complete! Page will be refreshed now.<script>setTimeout(function() { location.reload();}, 2000); </script>";
    } elseif (file_exists($filename_tmp) && file_exists($filename_status)) {
        $res = "Portable wrapper file is being downloaded. Download Progess: " . file_get_contents($filename_status) . " %";
    } else {
        $res = "Portable wrapper file download has failed.";
    }
    $data = array('response' => $res);
    echo json_encode($data);
    exit;
}