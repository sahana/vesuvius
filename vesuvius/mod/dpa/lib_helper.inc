<?php

/**
 * @name         Dynamic Portable App Helper Functions
 * @version      0.1
 * @package      dpa
 * @author       Akila Ravihansa Perera <ravihansa3000@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0813
 */
function shn_dpa_check_status() {
    global $conf;
    $bin_dir_status = (file_exists($conf['mod_dpa_bin']) && is_writable($conf['mod_dpa_bin'])) ? DPA_STATUS_OK : DPA_STATUS_FAIL;
    $repository_status = (shn_dpa_get_repo_status()) ? DPA_STATUS_OK : DPA_STATUS_FAIL;
    $win_wrapper_status = (file_exists($conf['mod_dpa_bin'] . "portable-wrapper_win.zip")) ? DPA_STATUS_OK : DPA_STATUS_FAIL;
    if ($win_wrapper_status === DPA_STATUS_FAIL) {
        $win_wrapper_status = (file_exists($conf['mod_dpa_bin'] . "portable-wrapper_win.zip.tmp")) ? DPA_STATUS_DOWNLOADING : DPA_STATUS_FAIL;
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
    if ($status['bin_directory'] === DPA_STATUS_OK && $status['win_wrapper'] === DPA_STATUS_OK)
        return true;
    else
        return false;
}

function shn_dpa_load_html() {
    global $global;
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
                    height:110px;
                    padding:10px;
                    background-color:#E5EAEF;
                    border: 2px solid rgba(52, 104, 154, 0.15);
                    text-align: center;
                }
                
                #dpa_wizard_box {
                    width:750px; 
                    height:600px;
                    padding:10px;
                    background-color:#E5EAEF;
                    border: 2px solid rgba(52, 104, 154, 0.15);
                    
                }
                
                .dpa_toolbar{
                        font-weight: bold;
                        font-size: 105%;
                }
                
                .dpa_tooltip_icon{
                        cursor: pointer;
                        display: inline-block;
                        font-size: 13px;
                        width: 20px;
                        height: 20px;
                        background-color: #89A4CC;
                        line-height: 20px;
                        color: white;
                        font-weight: bold;
                        border-radius: 10px;
                        text-align: center;
                        position: relative;
                        margin: 0 0 0 20px;
                }
                
                .dpa_tooltip_icon:hover { background-color: #3D6199; }

                .dpa_tooltip {
                        background-color: #E5EAEF;
                        color: White;
                        position: absolute;
                        left: 25px;
                        top: -25px;
                        z-index: 1000000;
                        width: 500px;
                        height: 80px;
                        border-radius: 5px;
                }
                
                .dpa_tooltip:before {
                        border-color: transparent #3D6199 transparent transparent;
                        border-right: 6px solid #3D6199;
                        border-style: solid;
                        border-width: 6px 6px 6px 0px;
                        content: "";
                        display: block;
                        height: 0;
                        width: 0;
                        line-height: 0;
                        position: absolute;
                        top: 40%;
                        left: -6px;
                }
                
                .dpa_tooltip p {
                        margin: 10px;
                        color: #34689A;
                        text-align: left;
                        font-size: 90%;
                }
                .message_container { 
                    margin:0 0 20px 0; 
                    padding: 5px; 
                    border: #E5EAEF 1px solid; 
                    background-color: #fcfcfc; 
                    -moz-border-radius: 5px; border-radius: 5px; 
                    -webkit-border-radius: 5px; box-shadow: 0px 0px 5px rgba(191,191,191,0.4);
                }
            </style>
         ';

    echo '<div id="dpa_dialog" class="window"></div>';

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
        if (!mkdir($conf['mod_dpa_bin'], 0755, true)) {
            add_error("Could not create 'bin' directory. Portable App module may not function properly.");
            add_error("Please set a valid path for the 'bin' directory.");
        }
    } else {
        if (!is_writable($conf['mod_dpa_bin'])) {
            chmod($conf['mod_dpa_bin'], 0755);
        }
    }

    // check publish directory exists, try to create if not
    if (!file_exists($conf['mod_dpa_publish'])) {
        if (!mkdir($conf['mod_dpa_publish'], 0755, true)) {
            add_error("Could not create 'publish' directory. Portable App module may not function properly.");
            add_error("Please set a valid path for the 'publish' directory.");
        }
    } else {
        if (!is_writable($conf['mod_dpa_publish'])) {
            chmod($conf['mod_dpa_publish'], 0755);
        }
    }
}

function shn_dpa_get_repo_data() {
    $dpa_config = shn_dpa_read_config();
    $service_url = (isset($dpa_config['end_point'])) ? $dpa_config['end_point'] : false;
    if ($service_url === false) {
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

function shn_dpa_read_config() {
    global $conf;
    $config_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_config_file'];
    if (!file_exists($config_file)) {
        $config_arr = array(
            'end_point' => 'http://ravihansa3000.com/vesuvius-repo/index.php'
        );
        shn_dpa_save_config($config_arr);
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

    return $doc->save($config_file);
}

function shn_dpa_save_publish($publish_filename) {
    global $conf;
    $publish_list_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_publish_list_file'];
    date_default_timezone_set('UTC');
    $desc = (isset($_GET['dpa_publish_desc']) ? $_GET['dpa_publish_desc'] : '');
    $publish_arr = array(
        'description' => $desc,
        'md5' => md5($publish_filename),
        'created_by' => $_SESSION['user'],
        'date' => date("Y-m-d"),
        'time' => date("H:i:s")
    );

    if (!file_exists($publish_list_file)) {
        $doc = new DOMDocument();
        $doc->formatOutput = true;

        $r = $doc->createElement("dynamic-portable-app");
        $doc->appendChild($r);
        if (!$doc->save($publish_list_file)) {
            return false;
        }
    }

    $doc = new DOMDocument();
    $doc->formatOutput = true;
    $doc->load($publish_list_file);
    $root_node = $doc->getElementsByTagName("dynamic-portable-app")->item(0);
    $file_node = $doc->createElement("file");
    $nameAttribute = $doc->createAttribute('name');
    $nameAttribute->value = $publish_filename;
    $file_node->setAttribute('name', $publish_filename);
    foreach ($publish_arr as $key => $value) {
        $node = $doc->createElement($key);
        $node->appendChild($doc->createTextNode($value));
        $file_node->appendChild($node);
    }
    $root_node->appendChild($file_node);
    return $doc->save($publish_list_file);
}

function shn_dpa_get_published() {
    global $conf;
    $publish_list_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_publish_list_file'];
    if (!file_exists($publish_list_file)) {
        return false;
    }

    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;
    $doc->load(realpath($publish_list_file));
    $nodes = $doc->getElementsByTagName("file");
    $published_list = array();
    foreach ($nodes as $node) {
        if ($node->nodeType === 1) {
            $file_item = array();
            $file_item['filename'] = (string) $node->getAttribute('name');
            $file_item['description'] = (string) $node->getElementsByTagName("description")->item(0)->nodeValue;
            $file_item['md5'] = (string) $node->getElementsByTagName("md5")->item(0)->nodeValue;
            $file_item['created_by'] = (string) $node->getElementsByTagName("created_by")->item(0)->nodeValue;
            $file_item['date'] = (string) $node->getElementsByTagName("date")->item(0)->nodeValue;
            $file_item['time'] = (string) $node->getElementsByTagName("time")->item(0)->nodeValue;
            $published_list[] = $file_item;
        }
    }
    return $published_list;
}

function shn_dpa_get_features() {
    global $conf;
    $feature_list_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_feature_list_file'];
    if (!file_exists($feature_list_file)) {
        return false;
    }

    $doc = new DOMDocument();
    $doc->preserveWhiteSpace = false;
    $doc->load(realpath($feature_list_file));
    $nodes = $doc->getElementsByTagName("feature");
    $feature_list = array();
    foreach ($nodes as $node) {
        if ($node->nodeType === 1) {
            $feature_item = array();
            $feature_item['modules'] = (string) $node->getAttribute('modules');
            $feature_item['description'] = (string) $node->getAttribute('description');
            $feature_list[] = $feature_item;
        }
    }
    return $feature_list;
}

function shn_dpa_delete_published($filename) {
    global $conf;
    $publish_list_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_publish_list_file'];
    if (!file_exists($publish_list_file)) {
        return false;
    }
    $doc = new DOMDocument();
    $doc->load(realpath($publish_list_file));
    $doc_el = $doc->documentElement;
    $file_nodes = $doc_el->getElementsByTagName('file');
    foreach ($file_nodes as $node) {
        if (((string) $node->getAttribute('name')) === $filename) {
            $doc_el->removeChild($node);
        }
    }
    $doc->save($publish_list_file);
}

function _is_curl_installed() {
    if (in_array('curl', get_loaded_extensions())) {
        return true;
    } else {
        return false;
    }
}

function readfile_chunked($filename) {
    $chunksize = 1 * (1024 * 1024); // 1MB per chunk
    $buffer = "";
    $handle = fopen($filename, 'rb');
    if ($handle === false) {
        return false;
    }

    $abort_download = false;
    while (!feof($handle) && !$abort_download) {
        $buffer = fread($handle, $chunksize);
        if ($buffer === false) {
            $abort_download = true;
            shn_dpa_add_log("Portable App download failed...file read error.");
        } else {
            echo $buffer;
        }
        if (connection_status() != CONNECTION_NORMAL) {
            $abort_download = true;
            shn_dpa_add_log("Portable App download failed...connection was closed.");
        }
        ob_flush();
        flush();
    }
    fclose($handle);
    return !$abort_download;
}

function shn_dpa_get_mod_desc($mod_name) {
    $mod_desc = array(
        "admin" => "Allows initial and on-going system configuration and control.",
        "pref" => "Permits user-specific settings.",
        "xst" => "Allows streaming of XML content.",
        "arrive" => "AJAX modue to watch the realtime influx of persons.",
        "ha" => "Allows hospital administrators/emergency managers to enter & edit organizational & event data.",
        "inw" => "Offers search and display capabilities for missing and found persons reported from multiple sources",
        "mpres" => "The Missing Person Registery Email Service parses incoming information about missing & found people",
        "plus" => "Provides SOAP Document Literal web services",
        "em" => "Allows a hospital admin or Sahana admin to define and geolocate disasters/incidents/events.",
        "rez" => "Defines the content of the home and other web pages.",
        "snap" => "Allows backup and restore of database instances, provided they are under 200MB.",
        "pop" => "Handles outbound email.",
        "eap" => "For a previously-reported person, whose record is retrieved, this allows revision or expansion.",
        "edit" => "Edit a Person module with a myriad of new features",
        "cam" => "Allows controlled capture of a photo from a webcam.",
        "eq" => "Allows the management of record expiration requests made by users without sufficient privileges to manually expire records.",
        "aq" => "Allows the management of reported abuse cases.",
        "stat" => "For a particular event, this will provide all-person data in tabular and graphical form, categorized by time, status, and other features.",
        "tp" => "This exposes a face for the download of the TriagePic application for hospital personnel.",
        "pfif" => "This supports supervision of data import/export in PFIF 1.2, 1.3 formats with accompanying photos.",
        "dpa" => "This will create a Portable App by dynamically cloning hosted code and data. Portable App can be downloaded as a zip archive."
    );
    if (isset($mod_desc[(string) $mod_name])) {
        return $mod_desc[(string) $mod_name];
    } else {
        return "No description available";
    }
}

function shn_dpa_add_log($msg) {
    global $conf;
    $log_file = $conf['mod_dpa_bin'] . $conf['mod_dpa_log_file'];
    date_default_timezone_set('UTC');
    $data = date("Y-m-d") . "|";
    $data = $data . date("H:i:s") . "|";
    $data = $data . $_SERVER['REMOTE_ADDR'] . "|" . $_SESSION['user'] . "|" . $msg . PHP_EOL;

    $fp = fopen($log_file, "a+");
    if ($fp && flock($fp, LOCK_EX)) { // lock the log file
        fwrite($fp, $data);
        flock($fp, LOCK_UN); // release the lock
        fclose($fp);
    }
}

function shn_dpa_get_disasters() {
    global $global;
    $q = "
		SELECT *
		FROM incident i
		LEFT JOIN sys_user_groups g
		ON i.private_group = g.group_id		
		ORDER BY date desc;
	";
    $result = $global['db']->Execute($q);
    if ($result === false) {
        daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "show events 1");
    }

    $root_parents = array();
    $disasters = array();
    $dcount = 0;
    while ($row = $result->FetchRow()) {
        if (is_null($row['parent_id']))
            $root_parents[$row['incident_id']] = $row['name'];
        else
            $disasters[$row['incident_id']] = array($row['name'], $row['parent_id']);

        $dcount++;
    }
    $event_arr[] = $root_parents;
    $event_arr[] = $disasters;
    return $event_arr;
}

function shn_dpa_event_js($child_events) {
    ?>
    <script type="text/javascript">
        var event_list = <? echo json_encode($child_events); ?>;
    </script>
    <?
}

function shn_dpa_send_file_data($download_file) {

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
}

function shn_dpa_load_wizard() {
    echo '
            <div id="dpa_wizard_box" class="window">
                <div style="text-align: right; font-weight: bold;">
                    <a id="dpa_hide_wizard" href="javascript:void(0);" onclick="$(wizard_id).hide();">[close]</a>            
                </div>               
         ';
    echo '
                <div style="margin: 10px 0;" class="message_container">
                    <p style="text-align:justify; color: black; font-size:13px; font-weight: bold; line-height:200%">
                        The wizard will help you with selecting required modules to support the features you need. You may find a list of
                        features that are available in this Vesuvius instance. Select the ones you need to integrate with the portable app and click OK.
                        It will then select the required modules that should be cloned to support those features.
                    </p>
                </div>
         ';
    echo '      
                <table style="width: 97%; margin: 20px 0;">
                    <thead>
                        <td style="width: 15px;"><strong></strong></td>
                        <td style="width: 500px;"><strong>Feature description</strong></td>                   
                    </thead>
	';
    $feature_list = shn_dpa_get_features();
    if ($feature_list) {
        foreach ($feature_list as $feature) {
            echo '<tr>';
            echo '<td><input class="dpa_wizard_feature" type="checkbox" value="' . $feature['modules'] . '" /></td>';
            echo '<td>' . $feature['description'] . '</td>';
            echo '</tr>';
        }
    }

    echo '
                </table>
                <div style="text-align: center;">
                    <input id="dpa_wizard_ok" type="button" class="styleTehButton" value="OK" />
                    <input id="dpa_wizard_cancel" type="button" class="styleTehButton" value="Cancel" style="margin-left: 15px;" />
                </div>
            </div>            
       ';
}