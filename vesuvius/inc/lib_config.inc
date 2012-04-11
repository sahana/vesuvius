<?
/**
 * @name         Config Library
 * @version      1.0
 * @package      framework
 * @author       http://www.linux.lk/~chamindra
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


global $global;
$approot = $global['approot'];


// load the configuration: first, the sysconf.inc, then the modules, then from the database
function shn_config_load_in_order() {
	global $conf;
	global $global;

	shn_config_base_conf_fetch();
	shn_config_module_conf_fetch('all');
	shn_config_database_fetch($conf,'all');
}



// update the config file $config_file with the search/replace hash
// $config_file, generating an output file $output_file
function shn_config_file_update($modify, $config_file, $output_file) {
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
function shn_config_base_conf_fetch() {
	global $global;
	global $conf;

	$approot = $global['approot'];
	require($approot.'conf/sahana.conf');
}



// Load the repective module conf.inc file
function shn_config_module_conf_fetch($module = 'all') {
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
function shn_config_database_fetch($conf, $type='base') {
	global $global;

	if($type == 'all') {
		$sql = "SELECT module_id, confkey, value FROM config";
	} else {
		$sql = "SELECT module_id, confkey, value FROM config WHERE module_id = '$type'";
	}
	if($results = $global['db']->GetAll($sql)) {
		foreach($results as $result) {
			// translate the boolean strings to actual boolean values
			if ($result['value'] === 'true') $result['value'] = true;
			if ($result['value'] === 'false') $result['value'] = false;
			$conf[$result['confkey']] = $result['value'];
		}
	}
}



// update a conf key/value pair in the database
function shn_config_database_update($key, $value, $type='base') {
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


