<?php

// Configuration meta data.
global $conf_meta;
$conf_meta = array();
include_once($global['approot'].'conf/sysconf_meta.inc.php');
$approot = $global['approot'];
// include the module configuration meta files
$d = dir($approot.'mod/');
while (false !== ($f = $d->read())) {
	if (file_exists($approot.'mod/'.$f.'/conf_meta.inc.php')) {
		include_once($approot.'mod/'.$f.'/conf_meta.inc.php');
	}
}

function shn_config_get_metadata($key){
	global $global,$conf,$conf_meta;
	if(isset($conf_meta[$key])){
		return $conf_meta[$key];
	}else{
		return array('type'=>'unknown');
	}
}
