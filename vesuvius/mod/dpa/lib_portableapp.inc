<?php

/**
 * @name         Dynamic Portable App Core Functions
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0808
 */
define('DPA_BASE_DIR', "PortableApps/SahanaFoundation.org/www/vesuvius");
define('DPA_DBDUMP_DIR', "PortableApps/SahanaFoundation.org/www/local/db_dump");

function shn_dpa_get_db_schema() {
    $dbschema = array(
        'person_uuid' => 'p_uuid',
        'person_status' => 'p_uuid',
        'user_preference' => 'p_uuid',
        'voice_note' => 'p_uuid',
        'sys_user_to_group' => 'p_uuid',
        'arrival_rate' => 'person_uuid',
        'users' => 'p_uuid',
        'person_to_report' => 'p_uuid',
        'person_deceased' => 'p_uuid',
        'contact' => 'p_uuid',
        'person_details' => 'p_uuid',
        'person_updates' => 'p_uuid',
        'edxl_co_photos' => 'p_uuid',
        'edxl_co_lpf' => 'p_uuid',
        'person_notes' => 'note_about_p_uuid',
        'edxl_co_header' => 'p_uuid',
        'rap_log' => 'p_uuid',
        'edxl_co_lpf' => 'p_uuid',
        'image' => 'p_uuid',
        'mpres_log' => 'p_uuid',
        'person_physical' => 'p_uuid'
    );
    return $dbschema;
}

function shn_dpa_create_portable_app($portable_bin) {
    global $global, $conf;
    $selected_mods = array();
    $selected_mods = array_merge($selected_mods, $conf['mod_dpa_required']);

    $mods = shn_get_all_modules();
    foreach ($mods as $mod => $mod_arr) {
        if (isset($_GET[(string) $mod_arr[0]])) {
            $selected_mods [] = $mod_arr[0];
        }
    }
    $selected_mods = array_unique($selected_mods);
    $tmpfname = uniqid("dpa_");
    $tmp_zip = $conf['mod_dpa_bin'] . $tmpfname . '.zip';
    if (!copy($portable_bin, $tmp_zip)) {
        return false;
    }

    $dpa_zip = new ZipArchive();
    if (!$dpa_zip->open($tmp_zip)) {
        unlink($tmp_zip);
        return false;
    }
    $dpa_zip->deleteName(DPA_BASE_DIR); // Remove BASE_DIR if it already exists from the archive
    $dpa_zip->close();

    $dpa_zip->open($tmp_zip);
    if (!$dpa_zip->addEmptyDir(DPA_BASE_DIR)) {
        $dpa_zip->close();
        unlink($tmp_zip);
        return false;
    }

    // Add subdirectories under approot to zip archive
    shn_dpa_add_dir($global['approot'], $dpa_zip, $selected_mods);
    $dpa_zip->close();

    // Remove sensitive information in sahana.conf
    if (!shn_dpa_clean_archive($tmp_zip)) {
        unlink($tmp_zip);
        return false;
    }

    // Add database dump
    if (!shn_dpa_add_dbdump($tmp_zip)) {
        unlink($tmp_zip);
        return false;
    }

    return $tmp_zip;
}

function shn_dpa_add_dbdump($tmp_zip) {
    global $conf;

    $dpa_zip = new ZipArchive();
    $dpa_zip->open($tmp_zip);
    // short variables - database login 
    $dbhost = $conf['db_host'];
    $dbname = $conf['db_name'];
    $dbuser = $conf['db_user'];
    $dbpass = $conf['db_pass'];
    $dbport = $conf['db_port'];

    // Get database dump only with entire structure
    $db_dump_file = $conf['mod_dpa_bin'] . uniqid("dpa_dbdump_");
    $cmd = 'mysqldump --user=' . $dbuser . ' --password=' . $dbpass . ' --host=' . $dbhost . ' --port=' . $dbport . ' --compact --skip-comments --routines --triggers --events --single-transaction --no-data ' . $dbname . ' > ' . $db_dump_file;
    exec($cmd, $output, $return_val);
    if ($return_val !== 0) {
        shn_dpa_add_log("Database dump process failed...(structure only) mysqldump returned " . $return_val);
        unlink($db_dump_file);
        return false;
    }

    if (isset($_GET['dpa_event_filter']) && isset($_GET['disaster']) && isset($_GET['incident']) && isset($_GET['event'])) {
        $selected_events_arr = array();
        if ($_GET['disaster'] !== "-1") {
            $selected_events_arr[] = $_GET['disaster'];
        }
        if ($_GET['incident'] !== "-1") {
            $selected_events_arr[] = $_GET['incident'];
        }
        if ($_GET['event'] !== "-1") {
            $selected_events_arr[] = $_GET['event'];
        }
        $events_comma_separated = implode(",", $selected_events_arr);

        // Dump incident table with selected event and parent events
        $cmd = 'mysqldump --user=' . $dbuser . ' --password=' . $dbpass . ' --host=' . $dbhost . ' --port=' . $dbport . ' --quick --skip-comments --single-transaction  --no-create-info ' . $dbname . ' incident --where="incident_id in (' . $events_comma_separated . ')" >> ' . $db_dump_file;
        exec($cmd, $output, $return_val);
        if ($return_val !== 0) {
            shn_dpa_add_log("Database dump process failed...(selected event and parent events) mysqldump returned " . $return_val);
            unlink($db_dump_file);
            return false;
        }
        // selected event is the last child in the event heirarchy
        $selected_event_id = $selected_events_arr[sizeof($selected_events_arr) - 1];

        // get db schema
        $dbschema = shn_dpa_get_db_schema();

        // dump each table by filtering out everything other than selected event related person recods
        foreach ($dbschema as $table_name => $key_field) {
            $cmd = 'mysqldump --user=' . $dbuser . ' --password=' . $dbpass . ' --host=' . $dbhost . ' --port=' . $dbport . ' --quick --skip-comments --single-transaction  --no-create-info ' . $dbname . ' ' . $table_name . ' --where="' . $key_field . ' in (SELECT p_uuid FROM person_uuid WHERE incident_id=' . $selected_event_id . ')" >> ' . $db_dump_file;
            exec($cmd, $output, $return_val);
            if ($return_val !== 0) {
                shn_dpa_add_log("Database dump process failed...(table records with related p_uuid) mysqldump returned " . $return_val);
                unlink($db_dump_file);
                return false;
            }
        }

        // dump everything else without filters
        $ignore_option_str = " ";
        $ignore_option_str = $ignore_option_str . "--ignore-table=" . $dbname . ".incident ";
        $ignore_option_str = $ignore_option_str . "--ignore-table=" . $dbname . ".plus_report_log ";
        $ignore_option_str = $ignore_option_str . "--ignore-table=" . $dbname . ".password_event_log ";
        $ignore_option_str = $ignore_option_str . "--ignore-table=" . $dbname . ".person_followers ";
        foreach ($dbschema as $table_name => $key_field) {
            $ignore_option_str = $ignore_option_str . "--ignore-table=" . $dbname . "." . $table_name . " ";
        }

        $cmd = 'mysqldump --user=' . $dbuser . ' --password=' . $dbpass . ' --host=' . $dbhost . ' --port=' . $dbport . ' --quick --skip-comments --single-transaction  --no-create-info ' . $dbname . ' ' . $ignore_option_str . ' >> ' . $db_dump_file;;
        exec($cmd, $output, $return_val);
        
        if ($return_val !== 0) {
            shn_dpa_add_log("Database dump process failed...(all records from unrelated tables) mysqldump returned " . $return_val);
            unlink($db_dump_file);
            return false;
        }
    } else {
        // Append data to the db dump file except for the 'users' table
        $cmd = 'mysqldump --user=' . $dbuser . ' --password=' . $dbpass . ' --host=' . $dbhost . ' --port=' . $dbport . ' --quick --skip-comments --single-transaction --no-create-info --ignore-table=' . $dbname . '.users ' . $dbname . ' >> ' . $db_dump_file;
        exec($cmd, $output, $return_val);

        // check whether command executed without errors
        if ($return_val !== 0) {
            shn_dpa_add_log("Database dump process failed...(full db clone) mysqldump returned " . $return_val);
            unlink($db_dump_file);
            return false;
        }
    }
    if (!($dpa_zip->addFile($db_dump_file, DPA_DBDUMP_DIR . '/vesuvius-portable-db-dump.sql'))) {
        unlink($db_dump_file);
        return false;
    }
    $dpa_zip->close();
    unlink($db_dump_file);
    return true;
}

function shn_dpa_clean_archive($tmp_zip) {
    global $global, $conf;
    $dpa_zip = new ZipArchive();
    $dpa_zip->open($tmp_zip);
    $dpa_zip->deleteName(DPA_BASE_DIR . "/conf/sahana.conf");
    $dpa_zip->close();
    $dpa_zip->open($tmp_zip);

    $tmpfname = uniqid("dpa_htaccess");
    $tmp_conf = $conf['mod_dpa_bin'] . $tmpfname;
    $new_conf = $conf['mod_dpa_bin'] . $tmpfname . ".new";
    $vesuvius_conf = $global['approot'] . "/conf/sahana.conf";
    copy($vesuvius_conf, $tmp_conf);

    $pear_path = realpath(dirname(__FILE__)) . '/PEAR/';
    set_include_path($pear_path);

    require_once ('Beautifier.php');
    require_once ('Beautifier/Batch.php');

    if (!beautify_phpfile($tmp_conf)) {
        return false;
    }

    copy($tmp_conf, $new_conf);

    $sh = fopen($tmp_conf, 'r');
    $th = fopen($new_conf, 'w');
    if (!($sh && $th)) {
        return false;
    }

    while (($buffer = fgets($sh)) !== false) {
        $buffer = trim($buffer);
        if (substr($buffer, 0, 1) !== '#' && substr($buffer, 0, 1) !== '/' && strpos($buffer, "'db_name'") !== false) {
            $buffer = '$conf[\'db_name\'] = "";' . PHP_EOL;
        }
        if (substr($buffer, 0, 1) !== '#' && substr($buffer, 0, 1) !== '/' && strpos($buffer, "'db_host'") !== false) {
            $buffer = '$conf[\'db_host\'] = "";' . PHP_EOL;
        }
        if (substr($buffer, 0, 1) !== '#' && substr($buffer, 0, 1) !== '/' && strpos($buffer, "'db_port'") !== false) {
            $buffer = '$conf[\'db_port\'] = "";' . PHP_EOL;
        }
        if (substr($buffer, 0, 1) !== '#' && substr($buffer, 0, 1) !== '/' && strpos($buffer, "'db_user'") !== false) {
            $buffer = '$conf[\'db_user\'] = "";' . PHP_EOL;
        }
        if (substr($buffer, 0, 1) !== '#' && substr($buffer, 0, 1) !== '/' && strpos($buffer, "'db_pass'") !== false) {
            $buffer = '$conf[\'db_pass\'] = "";' . PHP_EOL;
        }
        fwrite($th, $buffer . PHP_EOL);
    }
    fclose($sh);
    fclose($th);

    if (!$dpa_zip->addFile($new_conf, DPA_BASE_DIR . "/conf/sahana.conf")) {
        unlink($tmp_conf);
        unlink($new_conf);
        return false;
    }
    $dpa_zip->close();

    unlink($tmp_conf);
    unlink($new_conf);
    return true;
}

function shn_dpa_add_dir($dir, $dpa_zip, $selected_mods) {
    global $global, $conf;
    if (!is_dir($dir)) {
        return;
    }
    $dh = opendir($dir);
    if (!$dh) {
        return;
    }
    $app_base = realpath($global['approot']);
    $dir = realpath($dir);
    // Loop through all the files
    while (($file = readdir($dh)) !== false) {
        $item = realpath($dir . '/' . $file);
        //If it's a folder, run the function again
        if (!is_file($item)) {
            // Skip parent and root directories
            if (($file !== '.') && ($file !== '..')) {
                if (($dir === realpath($app_base . "/mod")) && !in_array($file, $selected_mods)) {
                    // Skip unselected modules
                } else if (isset($_GET['dpa_image_filter']) && $dir === realpath($app_base . "/www/tmp/plus_cache")) {
                    // Skip profile images container directory
                } else if ($item === realpath($conf['mod_dpa_bin'])) {
                    
                } else {
                    shn_dpa_add_dir($item, $dpa_zip, $selected_mods);
                }
            }
        } else {
            // Add file to zip archive		
            $filepathname = str_replace('\\', '/', DPA_BASE_DIR . str_replace($app_base, '', $item));
            $dpa_zip->addFile($item, $filepathname);
        }
    }
}

/* Format php script for processing */

function beautify_phpfile($file) {
    try {
        // Create the instance
        $oBeautifier = new PHP_Beautifier();
        // Add a filter, without any parameter
        $oBeautifier->addFilter('ArrayNested');
        $oBeautifier->addFilter('IndentStyles');

        // Set the indent char, number of chars to indent and newline char
        $oBeautifier->setIndentChar(' ');
        $oBeautifier->setIndentNumber(4);
        $oBeautifier->setNewLine(PHP_EOL);
        // Define the input file
        $oBeautifier->setInputFile($file);
        // Define an output file.
        $oBeautifier->setOutputFile($file . '.out');
        // Process the file. DON'T FORGET TO USE IT
        if (!$oBeautifier->process()) {
            return false;
        }
        // Save the file
        $oBeautifier->save();
    } catch (Exception $oExp) {
        return false;
    }
    unlink($file);
    rename($file . '.out', $file);
    return true;
}