<?php
/**
 * Sahana config library
 * Sahana - http://sahana.sourceforge.net
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage config
 * @author     http://www.linux.lk/~chamindra
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

global $global;
$approot = $global['approot'];

// define the configuration priority order
require_once ($approot.'conf/conf-order.inc.php');
include_once('lib_config_meta.inc.php');

// load all the configurations based on the database or file order
function shn_config_load_in_order() {

	global $conf;
	global $global;

	// give database the priority or the conf files
	if ('database' ==  $conf['sahana_conf_priority'] ) {
		// database overrides conf files
		shn_config_base_conf_fetch();
		shn_config_module_conf_fetch('all');
		shn_config_database_fetch($conf,'all');
	} else {
		// conf files overrides database
		shn_config_database_fetch($conf,'all');
		shn_config_base_conf_fetch();
		shn_config_module_conf_fetch('all');
	}
}

// update the config file $config_file with the search/replace hash
// $config_file, generating an output file $output_file
function shn_config_file_update($modify, $config_file, $output_file)
{
	global $global;

	$fh_c = fopen($config_file,'r');
	if (!( $fh_t = fopen($output_file,'w') ))
	return false; // if unable to open the file for write

	while (! feof ($fh_c) ) {

		$line = fgets($fh_c,1024);
		$match = false;

		// iterate through the list of possible replacements in the line
		foreach ($modify as $search => $replace ) {

			if (preg_match($search,$line)) {
				$match = true;
				fputs($fh_t,$replace."\n");
			}
		}
		if (!$match) // if no match was found output the default line
		fputs($fh_t, $line);
	}
	fclose($fh_c);
	fclose($fh_t);
	return true;
}

// Load all .inc files in the main /conf including sysconf.inc.php
function shn_config_base_conf_fetch()
{
	global $global;
	global $conf;

	$approot = $global['approot'];

    $d = dir($approot.'conf/');
    while (false !== ($f = $d->read())) {
        if ( preg_match('/\.inc\.php$/',$f) ) {

            //echo 'included '.$f;
            require_once($approot.'conf/'.$f);
        }
    }

	// require ($approot.'conf/sysconf.inc.php');
}

// Load the repective module conf.inc file
function shn_config_module_conf_fetch($module = 'all')
{
	global $global;
	global $conf;

	$approot = $global['approot'];

	if ('all' == $module) {
		// include the module configuration files
		$d = dir($approot.'mod/');
		while (false !== ($f = $d->read())) {
			if (file_exists($approot.'mod/'.$f.'/conf.inc')) {
				include_once($approot.'mod/'.$f.'/conf.inc');

				// if module enabled flag is not set add it to conf
				if (!isset($conf['mod_'.$f.'_enabled'])) {
					$conf['mod_'.$f.'_enabled'] = true;
				}
			}
		}
	} else {
		include ($approot.'mod/'.$module.'/conf.inc');
	}

}

/**
 * shn_config_fetch
 *
 *    - all  : all configuration
 *    - base : base configuration
 *    - you can specify the module name
 *
 */
function shn_config_database_fetch($conf, $type='base')
{
	global $global;
    
	if($type == 'all')
	$sql = "SELECT module_id, confkey, value FROM config";
	else
	$sql = "SELECT module_id, confkey, value FROM config WHERE module_id = '$type'";

	if($results = $global['db']->GetAll($sql)){
		foreach($results as $result) {

			// translate the boolean strings to actual boolean values
			if ($result['value'] === 'true') $result['value'] = true;
			if ($result['value'] === 'false') $result['value'] = false;
			$conf[$result['confkey']] = $result['value'];
		}
	}
}

// update a conf key/value pair in the database
function shn_config_database_update($key, $value, $type='base')
{
	global $global;

	$sql = "SELECT module_id, confkey, value FROM config
                WHERE confkey = '$key' AND module_id = '$type'";

	if($results = $global['db']->GetALL($sql)) {
		$sql = "UPDATE config SET value = '$value'
                WHERE confkey = '$key' AND module_id = '$type'";
		$global['db']->Execute($sql);

	} else {

		$sql = "INSERT INTO config VALUES (NULL,'$type', '$key', '$value')";
		$global['db']->Execute($sql);
	}
}

function shn_config_validate_value($key,$value){
	$metadata = shn_config_get_metadata($key);
	$type = $metadata['type'];
	if($type == 'boolean'){
		if(preg_match("/^true$/i",$value)){
			$value = true;
		}
		if(preg_match("/^false$/i",$value)){
			$value = false;
		}
		if(is_bool($value)==false){
			return _t(sprintf("%s is not a valid boolean value.",$value));
		}
	}else if($type == 'password'){
		$minsize = $metadata['min_size'];
		$maxsize = $metadata['max_size'];
		$allow_null = $metadata['allow_null'];
		if(isset($allow_null) && ($allow_null==false && $value===null)){
			return _t(sprintf("Null values are not allowed."));
		}
		if(isset($minsize) && strlen($value) < $minsize){
			return _t(sprintf("The minimum size is %s",$minsize));
		}
		if(isset($maxsize) && strlen($value) > $maxsize){
			return _t(sprintf("The maximum size is %s",$maxsize));
		}
	}else if($type == 'integer'){
		$minvalue = $metadata['min_value'];
		$maxvalue = $metadata['max_value'];
		$allow_null = $metadata['allow_null'];
		if(isset($allow_null) && ($allow_null==false && $value===null)){
			return _t(sprintf("Null values are not allowed."));
		}
		if(ctype_digit($value) == false){
			return _t(sprintf("%s is not a valid integer value",$value));
		}
		if(isset($minvalue) && $value < $minvalue){
			return _t(sprintf("The minimum value is %s",$minvalue));
		}
		if(isset($maxvalue) && $value > $maxvalue){
			return _t(sprintf("The maximum value is %s",$maxvalue));
		}
	}else if($type == 'double'){
		$minvalue = $metadata['min_value'];
		$maxvalue = $metadata['max_value'];
		$allow_null = $metadata['allow_null'];
		$precision = $metadata['precision'];// not implemented yet.
		if(isset($allow_null) && ($allow_null==false && $value===null)){
			return _t(sprintf("Null values are not allowed."));
		}
		if(is_numeric($value) == false){
			return _t(sprintf("%s is not a valid double value",$value));
		}
		if(isset($minvalue) && $value < $minvalue){
			return _t(sprintf("The minimum value is %s",$minvalue));
		}
		if(isset($maxvalue) && $value > $maxvalue){
			return _t(sprintf("The maximum value is %s",$maxvalue));
		}
	}else if($type == 'url'){

	}else if($type == 'email'){
        if(!shn_valid_email($value)){
        	return _t(sprintf("%s is not a valid email address",$value));
        }
	}else if($type == 'string'){
		$size = $metadata['size'];
        if(isset($size) && $size>0){
        	if(strlen($value)!=$size){
        		return _t(sprintf("The string should be exactly %s characters long.",$size));
        	}
        }
    }
	// no errors
	return false;

}

