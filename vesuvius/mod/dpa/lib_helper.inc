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
 * @lastModified 2013.0726
 */
 
 
 
 function shn_dpa_check_status() {
    global $global, $conf;
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
        if (!mkdir($conf['mod_dpa_bin'], 0755, true)) {
            add_error("Could not create 'bin' directory. Portable App module may not function properly.");
            add_error("Please set a valid path as the 'bin' directory.");
        }
    } else {
        if (!is_writable($conf['mod_dpa_bin'])) {
            chmod($conf['mod_dpa_bin'], 0755);
        }
    }
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

function shn_dpa_get_mod_desc($mod_name){
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
	if (isset($mod_desc[(string)$mod_name])){
		return $mod_desc[(string)$mod_name];
	}else{
		return "No description available";
	}
	
}