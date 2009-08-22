<?php

global $global;
include_once $global['approot']."/inc/lib_uuid.inc";


function shn_amp_get_mods(){

global $global;
    global $conf;
    $module_list = array();

    $approot = $global['approot'];
    //echo "$approot<br/>";
    $d = dir($approot."/mod");
    while (false !== ($f = $d->read())) {
        if (file_exists($approot."mod/".$f."/ws.xml")) {
          $nice_name=$conf['mod_'.$f.'_name'];
          array_push($module_list, array($f,$nice_name));
        }
    }
	
    return $module_list; 
}

