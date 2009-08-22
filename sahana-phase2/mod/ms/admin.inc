<?php

/**Admin Module for MapServer
*
* PHP version 5
* 
* @author       Hasitha Anjana <hasianjana@gmail.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @module      MapServer
* @version     $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";
// Default config values
include_once $global['approot']."/mod/ms/conf.inc";

function shn_ms_adm_default()
{
	print '<h2>'._t("MapServer module configuration").'</h2>';
    shn_ms_adm_configform();
}

// Form for inputting
function shn_ms_adm_configform()
{
    global $conf;
    if ($_POST['stat'] != 1) {
        shn_form_fopen("adm_configform",null,array("req"=>false));
        shn_form_fsopen(_t("Options"));
        $mapserv_help=_t("Full filesystem path to the MapServer CGI");
        shn_form_text(_t("MapServer CGI location"),"msp",'size="25"',array('value'=>$conf['ms_MAPSERV_CGI'],"help"=>$mapserv_help));
        $maps_help=_t("Folder (relative to mod/ms) in which to store created map files. This folder needs to be writable by the webserver.");
        shn_form_text(_t("Maps Folder"),"maps",'size="25"',array('req'=>true,'value'=>$conf['ms_MAP_PATH'],"help"=>$maps_help));
        $shapes_help=_t("Folder (relative to mod/ms) in which to store uploaded shape files. This folder needs to be writable by the webserver.");
        shn_form_text(_t("Shapefiles Folder"),"shapefiles",'size="25"',array('req'=>true,'value'=>$conf['ms_SHAPE_PATH'],"help"=>$shapes_help));
        $images_help=_t("Folder (relative to www) in which to store created image files. This folder needs to be writable by the webserver.");
        shn_form_text(_t("Images Folder"),"img",'size="25"',array('req'=>true,'value'=>$conf['ms_IMG_PATH'],"help"=>$images_help));
        shn_form_hidden(array('stat'=>1));
        shn_form_submit(_t("Check"));
        shn_form_fsclose();
        shn_form_fclose();
    } else {
        // Do sanity check when submitted 
        _shn_ms_adm_chkconfig();
    }
}

// Do sanity check when submitted 
function _shn_ms_adm_chkconfig()
{
    global $conf;
    global $global;
    $db = $global['db'];                  
    // Check for PHP MapScript being loaded
    $pcheck = _shn_ms_adm_check_phpms();
	// Check for PHP Zip support
    $zcheck = _shn_ms_adm_check_phpzip();
	// Check directories
    $dcheck = _shn_ms_adm_checkdirs();
	// Check MapServ CGI
    // (currently unused & hence optional)
    if ($_POST['msp'] != NULL) {
        $mcheck = _shn_ms_check_mapserv();
        if ($mcheck) {
            $item = $_POST['msp'];
            $query = "SELECT * FROM config WHERE confkey='ms_MAPSERV_CGI' AND module_id='mapserver'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$item' WHERE module_id = 'mapserver' AND confkey = 'ms_MAPSERV_CGI'";       
                $db->Execute($q);
            } else {
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('mapserver','ms_MAPSERV_CGI','$item')";
                $db->Execute($insert);
            }
        }
    }
    $res = $pcheck & $zcheck & $dcheck;
    if ($res == FALSE) {
	    add_warning ('<b>'._t("Please correct above problems and try again, otherwise the MapServer module won't work").'</b>');
    } else {
        _shn_ms_adm_saveconfig();
    }
}

// @ToDo Replace with a function which checks that the MapServ CGI works (relative URL, not file path )
// i.e. returns this value: No query information to decode. QUERY_STRING is set, but empty.
function _shn_ms_check_mapserv()
{
    $ms_path = $_POST['msp'];
    $ret = TRUE;
    if (file_exists($ms_path) == TRUE) {
	    add_confirmation (_t("MapServer CGI found").": $ms_path");
        _shn_ms_check_mapserv_depend($ms_path);
    } else {
	    add_error ("<b>"._t("MapServer CGI not found").": $ms_path</b>");
        $ret = FALSE;
    }
    return $ret;
}

// Check that MapServer dependencies are in-place
// I don't think this is our job?
function _shn_ms_check_mapserv_depend($ms_path)
{
    // Searching for libraries required by MapServ
    $misses = _shn_ms_check_libdeps($ms_path."/mapserv");
    $flag = 0;
    foreach ($misses as &$val) {
        if ($flag == 0) {
	        add_error("<b>"._t("Following Mapserver dependencies are not found")."</b>");
	        $ret = FALSE;
	    }
        add_error('<i>'._t("$val").'</i>');
        $flag = 1;
	}
    if ($flag == 0) {
        add_confirmation (_t("All MapServer dependencies are installed"));
	}
}

// 'ldd' isn't portable to Win32, but I don't think this task is required.
function _shn_ms_check_libdeps($ms_path)
{
    $cmd = "ldd ".$ms_path;
    exec($cmd, $output, $return);
    $oparr = array();
    $i = 0;
    foreach ($output as &$val) {
        $tok = strtok($val, "=>");
        while ($tok !== false) {
	        $miss_lib = $tok;
	        $tok = strtok("=>");
	        if (!strcmp("not found", trim($tok))) {
                if (_shn_ms_is_unique($oparr, $miss_lib) == true) {
	                $oparr[$i] = $miss_lib;
	                $i++;
                }
	        }
	    }
    }
    array_unique($oparr);
    return $oparr;
}

function _shn_ms_adm_checkdirs()
{
    global $conf;
    global $global;
    $db = $global['db'];
    $mapsvr_root = $global['approot']."/mod/ms";
    $ret = TRUE;
    $save = FALSE;
    if ($_POST['img'] != NULL) {
        $path = $global['approot']."/www/".$_POST['img'];
        if (_shn_ms_isdir_exist($path) == false) {
            if (mkdir($path, 0777)) {
                add_confirmation (_t("Directory created").": $path");
                $save = TRUE;
	        } else {
                add_error ("<b>"._t("No permissions to create").": $path</b>");
	            $ret = FALSE;
	        }
        } else {
	        if ((is_writable($path) && is_readable($path)) == TRUE ) {
	            add_confirmation (_t("Directory exists").": $path");
                $save = TRUE;
	        } else {
	            add_error ("<b>"._t("Webserver does not have Write permissions to directory").": $path</b>");
	            $ret = FALSE;
	        }
        }
        // Update ms_IMG_PATH
        if ($save) {
            // Strip leading /, if present. (to make portable for /sahana style installs)
            $item = ltrim($_POST['img'],"/");
            $query = "SELECT * FROM config WHERE confkey='ms_IMG_PATH' AND module_id='mapserver'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$item' WHERE module_id = 'mapserver' AND confkey = 'ms_IMG_PATH'";       
                $db->Execute($q);
            } else {
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('mapserver','ms_IMG_PATH','$item')";
                $db->Execute($insert);
            }
        }
    } else {
	    add_error("<b>"._t("Images folder cannot be blank")."</b>");
        $ret = FALSE;
    }
    $save = FALSE;
    if ($_POST['maps'] != NULL) {
        $path = $mapsvr_root."/".$_POST['maps'];
        if (_shn_ms_isdir_exist($path) == false) {
            if (mkdir($path, 0777)) {
                add_confirmation (_t("Directory created").": $path");
                $save = TRUE;
	        } else {
                add_error ("<b>"._t("No permissions to create").": $path</b>");
	            $ret = FALSE;
	        }
        } else {
	        if ((is_writable($path) && is_readable($path)) == TRUE ) {
	            add_confirmation (_t("Directory exists").": $path");
                $save = TRUE;
	        } else {
	            add_error ("<b>"._t("Webserver does not have Write permissions to directory").": $path</b>");
	            $ret = FALSE;
	        }
        }
        // Update ms_MAP_PATH
        if ($save) {
            $item = $_POST['maps'];
            $query = "SELECT * FROM config WHERE confkey='ms_MAP_PATH' AND module_id='mapserver'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$item' WHERE module_id = 'mapserver' AND confkey = 'ms_MAP_PATH'";       
                $db->Execute($q);
            } else {
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('mapserver','ms_MAP_PATH','$item')";
                $db->Execute($insert);
            }
        }
    } else {
	    add_error("<b>"._t("Maps folder cannot be blank")."</b>");
        $ret = FALSE;
    }
    $save = FALSE;
    if ($_POST['shapefiles'] != NULL) {
        $path = $mapsvr_root."/".$_POST['shapefiles'];
        if (_shn_ms_isdir_exist($path) == false) {
            if (mkdir($path, 0777)) {
                add_confirmation (_t("Directory created").": $path");
                $save = TRUE;
	        } else {
                add_error ("<b>"._t("No permissions to create").": $path</b>");
	            $ret = FALSE;
	        }
        } else {
	        if ((is_writable($path) && is_readable($path)) == TRUE ) {
	            add_confirmation (_t("Directory exists").": $path");
                $save = TRUE;
	        } else {
	            add_error ("<b>"._t("Webserver does not have Write permissions to directory").": $path</b>");
	            $ret = FALSE;
	        }
        }
        // Update ms_SHAPE_PATH
        if ($save) {
            $item = $_POST['shapefiles'];
            $query = "SELECT * FROM config WHERE confkey='ms_SHAPE_PATH' AND module_id='mapserver'";
            $res = $db->Execute($query);
            if(!$res->EOF){
                $q = "UPDATE config SET value = '$item' WHERE module_id = 'mapserver' AND confkey = 'ms_SHAPE_PATH'";       
                $db->Execute($q);
            } else {
                $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('mapserver','ms_SHAPE_PATH','$item')";
                $db->Execute($insert);
            }
        }
    } else {
	    add_error("<b>"._t("Shapefiles folder cannot be blank")."</b>");
        $ret = FALSE;
    }
    // Check for system data
    $templ_map = $mapsvr_root.'/'.$conf['ms_BASE_MAP'];
    if (file_exists($templ_map) == TRUE) {
	    add_confirmation (_t("Template map file exists").": $templ_map");
    } else {
	    add_error ("<b>"._t("Template map file does not exist").": $templ_map</b>");
        $ret = FALSE;
    }
    return $ret;
}

function _shn_ms_isdir_exist($path)
{
    $stats = is_dir($path);
    return $stats;
}

// Check for PHP MapScript being active
function _shn_ms_adm_check_phpms()
{
    /**
            * dl() is deprecated  in PHP6. Need to load in php.ini instead!
            *
            * if (PHP_OS == "WINNT" || PHP_OS == "WIN32")
            * {
            *     dl("php3_mapscript.dll");
            * } else {
            *     dl("php_mapscript.so");
            * }
            **/

    $mods = get_loaded_extensions();
    for($i=0; $i<sizeof($mods); $i++) {
        if ($mods[$i] == 'MapScript') {
	        add_confirmation(_t("PHP MapScript module active"));
            return TRUE;
        }
    }
    add_error("<b>"._t("PHP MapScript module not active")."</b>");
    return FALSE;
}

// Check for PHP Zip support
function _shn_ms_adm_check_phpzip()
{
    if(function_exists("zip_open")) {
        add_confirmation(_t("PHP Zip support available"));
        return TRUE;
    }
    add_error('<b>'._t("PHP Zip support not available. Either upgrade to v5.2.0+ or install via PECL").'.</b>');
    return FALSE;
}

// Used only by the deprecated _shn_ms_check_libdeps()
function _shn_ms_is_unique(array $arr, $str)
{
    foreach($arr as &$val) {
        if (!strcmp($str, $val)) {
	        return false;
        }
    }
    return true;
}

// Config ok, so mark module as configured
function _shn_ms_adm_saveconfig()
{
    global $global;
    $db = $global['db'];
    // Mark module as configured
    $query = "SELECT * FROM config WHERE confkey='ms_configured' AND module_id='mapserver'";
    $res = $db->Execute($query);
    if(!$res->EOF){
        $q = "UPDATE config SET value = '1' WHERE module_id = 'mapserver' AND confkey = 'ms_configured'";       
        $db->Execute($q);
    } else {
        $insert = "INSERT INTO config(module_id,confkey,value) VALUES ('mapserver','ms_configured','1')";
        $db->Execute($insert);
    }
    add_confirmation('<b>'._t("MapServer module now configured").'</b>');
}


