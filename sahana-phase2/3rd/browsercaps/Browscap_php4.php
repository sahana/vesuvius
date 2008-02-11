<?php
/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */


/**
 * Options for regex patterns.
 *
 * REGEX_DELIMITER:  Delimiter of all the regex patterns in the whole class.
 * REGEX_MODIFIERS:  Regex modifiers.
 */
define('REGEX_DELIMITER', 	'@');
define('REGEX_MODIFIERS', 	'i');

/**
 * The values to quote in the ini file
 */
define('VALUES_TO_QUOTE', 	'Browser|Parent');

/**
 * Definitions of the function used by the uasort() function to order the
 * userAgents array.
 *
 * ORDER_FUNC_ARGS:  Arguments that the function will take.
 * ORDER_FUNC_LOGIC: Internal logic of the function.
 */
define('ORDER_FUNC_ARGS', 	'$a, $b');
define('ORDER_FUNC_LOGIC', 	'$a=strlen($a);$b=strlen($b);return$a==$b?0:($a<$b?1:-1);');

/**
 * Maximum deep to cycle trough the browsers to find a parent for the
 * current one.
 */
define('MAX_DEEP', 			8);

/**
 * The headers to be sent for checking the version and requesting the file.
 */
define('REQUEST_HEADERS', 	"GET %s HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n");


/**
 * Browscap.ini parsing class with caching and update capabilities
 *
 * PHP version 4
 *
 * LICENSE: This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @package    Browscap
 * @author     Jonathan Stoppani <st.jonathan@gmail.com>
 * @copyright  Copyright (c) 2006 Jonathan Stoppani
 * @version    0.6
 * @license    http://www.gnu.org/licenses/lgpl.html GNU Lesser General Public License
 * @link       http://garetjax.info/projects/browscap/
 */
class Browscap
{	
	/**
	 * Options for auto update capabilities
	 * 
	 * $_remoteVerUrl:  The location to use to check out if a new version of the
	 *                  browscap.ini file is available.
	 * $_remoteIniUrl:  The location from which download the ini file.
	 *                  The placeholder for the file should be represented by a %s.
	 * $_iniVersion:    The version of the ini file to download, will be inserted
	 *                  into the REMOTE_INI_URL value.
	 * $_timeout:		The timeout for the requests.
	 */
	var $remoteIniUrl  	= 'http://browsers.garykeith.com/stream.asp?PHP_BrowsCapINI';
	var $remoteVerUrl  	= 'http://browsers.garykeith.com/version-date.asp';
	var $iniVersion		= 'BrowsCapINI';
	var $timeout		= 2;
	
	/**
	 * Where to store the cached php arrays.
	 *
	 * @var string
	 */
	var $cacheFilename 	= 'cache.php';
	
	/**
	 * Where to store the downloaded ini file.
	 *
	 * @var string
	 */
	var $iniFilename 	= 'browscap.ini';
	
	/**
     * Path to the cache directory
     *
     * @var string	
     */
	var $cacheDir 		= null;
	
	/**
	 * Flag to be set to true after loading the cache
	 *
	 * @var bool
	 */
	var $_cacheLoaded	= false;
	
	/**
     * Where to store the value of the included php cache file
     *
     * @var array
     */
	var $_userAgents	= array();
	var $_browsers		= array();
	var $_patterns		= array();
	var $_common		= array();

	/**
	 * Constructor class, checks for the existence of (and loads) the cache and
	 * if needed updated the definitions
	 *
	 * @param string $cache_dir
	 */
	function Browscap($cache_dir)
	{	
		if (!isset($cache_dir)) {
			$this->_error('You have to provide a path to read/store the browscap cache file');
		}
		
		$cache_dir = realpath($cache_dir);
		
		if (substr($cache_dir, -4) === '.php') {
			$this->cacheFilename = basename($cache_dir);
			$this->cacheDir = dirname($cache_dir);
		} else {
			$this->cacheDir = $cache_dir;
		}
		
		$this->cacheDir .= DIRECTORY_SEPARATOR;
	}

	/**
	 * Gets the information about the browser by User Agent
	 *
	 * @param string $user_agent   the user agent string
	 * @param bool   $return_array whether return an array or an object 
	 * @return stdObject the object containing the browsers details. Array if 
	 *                   $return_array is set to true.
	 */
	function getBrowser($user_agent = null, $return_array = false)
	{	
		if (!$this->_cacheLoaded) {
			$cache_file = $this->cacheDir . $this->cacheFilename;
						
			if (!file_exists($cache_file)) {
				$this->updateCache();
			}
			
			$this->_loadCache($cache_file);
		}
		
		if (!isset($user_agent) && isset($_SERVER['HTTP_USER_AGENT'])) {
			$user_agent = $_SERVER['HTTP_USER_AGENT'];
		}
		
		$browser = $this->_common;
	
		foreach ($this->_patterns as $key => $pattern) {
			if (preg_match($pattern . 'i', $user_agent)) {
				$browser = array(
					'browser_name_regex'    => trim(strtolower($pattern), REGEX_DELIMITER),
					'browser_name_pattern'  => $this->_userAgents[$key]
				);
				
				$browser = $value = $browser + $this->_browsers[$key];
				
				$maxdeep = MAX_DEEP;
				while (array_key_exists('Parent', $value) && (--$maxdeep > 0)) {
					$value      =   $this->_browsers[$value['Parent']];
					$browser    +=  $value;
				}
				
				if (!empty($browser['Parent'])) {
					$browser['Parent'] = $this->_userAgents[$browser['Parent']];
				}
	
				break;
			}
		}
		
		return $return_array ? $browser : (object) $browser;
	}
	
	/**
	 * Parses the ini file and updates the cache
	 *
	 * @return bool whether the file was correctly written to the disk
	 */
	function updateCache()
	{	
		$ini_path 	= $this->cacheDir . $this->iniFilename;
		$cache_path	= $this->cacheDir . $this->cacheFilename;
	
		$remote_ini_url = sprintf($this->remoteIniUrl, $this->iniVersion);
		$this->_getRemoteIniFile($remote_ini_url, $ini_path);
	
		$browsers 								= parse_ini_file($ini_path, true);
		$this->_common['browser_name_regex'] 	= REGEX_DELIMITER
		                                        . '^.*$'
		                                        . REGEX_DELIMITER;
		$this->_common['browser_name_pattern'] 	= '*';
		$this->_common							+= array_pop($browsers);
		$this->_userAgents 						= array_keys($browsers);
		usort(
			$this->_userAgents,
			create_function(ORDER_FUNC_ARGS, ORDER_FUNC_LOGIC)
		);
		
		$user_agents_keys = array_flip($this->_userAgents);
		
		$search		= array('\*', '\?');
    	$replace	= array('.*', '.');

		foreach ($this->_userAgents as $user_agent) {
			$pattern = preg_quote($user_agent, REGEX_DELIMITER);
			$this->_patterns[] 	= REGEX_DELIMITER
							    . '^'
						  		. str_replace($search, $replace, $pattern)
						 	 	. '$'
						  		. REGEX_DELIMITER;
			
			if (!empty($browsers[$user_agent]['Parent'])) {
				$parent = $browsers[$user_agent]['Parent'];
				$browsers[$user_agent]['Parent'] = $user_agents_keys[$parent];
			}
			
			$this->_browsers[] = $browsers[$user_agent];
        }

		$cache = $this->_buildCache();
		
		return (bool) file_put_contents($cache_path, $cache, LOCK_EX);
	}
	
	/**
	 * Loads the cache into odject's properties
	 *
	 * @return void
	 */
	function _loadCache($cache_file)
	{
		require $cache_file;
		
		$this->_browsers 	= $browsers;
		$this->_userAgents	= $userAgents;
		$this->_common		= $common;
		$this->_patterns	= $patterns;
		
		$this->_cacheLoaded = true;
	}
	
	/**
	 * Parses the array to cache and creates the php string to write to disk
	 *
	 * @return string the php string to save into the cache file
	 */
	function _buildCache()
	{
		$cacheTpl = "<?php\n\$browsers=%s;\n\$common=%s;\n\$userAgents=%s;\n\$patterns=%s;\n";
	
		$patternsArray 		= $this->_array2string($this->_patterns);
		$commonArray		= $this->_array2string($this->_common);
		$userAgentsArray	= $this->_array2string($this->_userAgents);
		$browsersArray		= $this->_array2string($this->_browsers);
		
		return sprintf(
			$cacheTpl,
			$browsersArray,
			$commonArray,
			$userAgentsArray,
			$patternsArray
		);
	}
	
	/**
	 * Updates the local copy of the ini file (by version checking) and adapts
	 * his syntax to php
	 *
	 * @param string $url  the url of the remote server
	 * @param string $path the path of the ini file to update
	 * @throws Browscap_Exception
	 * @return bool if the ini file was updated
	 */
	function _getRemoteIniFile($url, $path)
	{
		// Check version
		if (file_exists($path)) {
			$local_tmstp 	= filemtime($path);
			$remote_tmstp	= $this->_getRemoteMTime();
			
			if ($remote_tmstp < $local_tmstp) {
				// No update needed, return
				return false;
			}
		}

		// Get updated .ini file
		$remote_url		= parse_url($url);
		$remote_handler = fsockopen($remote_url['host'], 80, $c, $e, $this->timeout);
		
		if (!$remote_handler) {
			$this->_error("Could not connect to {$remote_url['host']}");
		}
		
		if (isset($remote_url['query'])) {
			$remote_url['path'] .= '?' . $remote_url['query'];
		}

		stream_set_timeout($remote_handler, $this->timeout);
		
		$out = sprintf(REQUEST_HEADERS, $remote_url['path'], $remote_url['host']);
		fwrite($remote_handler, $out);
		
		$response = fgets($remote_handler);
		if (strpos($response, '200 OK') === false) {
			$this->_error("Bad response from {$remote_url['host']} (1)");
		}
		
		$end = false;
		do {
			if (fgets($remote_handler) == "\r\n") {
				$end = true;
			}
		} while (!$end);
		
		// Ok, lets read the file
		$content = '';
		while (!feof($remote_handler)) {
			$pattern = REGEX_DELIMITER
					 . '('
					 . VALUES_TO_QUOTE
					 . ')="?([^"]*)"?$'
					 . REGEX_DELIMITER;
			$subject = trim(fgets($remote_handler, 4096));
		
			$content .= preg_replace($pattern, '$1="$2"', $subject) . "\n";
		}
		
		fclose($remote_handler);
		
		if (!file_put_contents($path, $content)) {
			$this->_error("Could not write .ini content to $path");
		}
		
		return true;
	}
	
	/**
	 * Gets the remote ini file update timestamp
	 *
	 * @throws Browscap_Exception
	 * @return int the remote modification timestamp
	 */
	function _getRemoteMTime()
	{
		$remote_url		= parse_url($this->remoteVerUrl);
		$remote_handler = fsockopen($remote_url['host'], 80, $c, $e, $this->timeout);

		if (!$remote_handler) {
			$this->_error("Could not connect to {$remote_url['host']}");
		}
		
		stream_set_timeout($remote_handler, $this->timeout);
		
		$out = sprintf(REQUEST_HEADERS, $remote_url['path'], $remote_url['host']);
		fwrite($remote_handler, $out);
		
		$response = fgets($remote_handler);
		if (strpos($response, '200 OK') === false) {
			$this->_error("Bad response from {$remote_url['host']}");
		}
		
		do {
			$remote_tmstp = strtotime(trim(fgets($remote_handler)));
		} while (!$remote_tmstp);
		
		if (!$remote_tmstp) {
			$this->_error("Bad datetime format from {$remote_url['host']}");
		}

		fclose($remote_handler);
		return $remote_tmstp;
	}
	
	function _error($message)
	{
		trigger_error($message, E_USER_WARNING);
	}
	
	/**
	 * Converts the given array to the php string which represent it
	 *
	 * @param array $array the array to parse and convert
	 * @return string the array parsed into a php string
	 */
	function _array2string($array)
	{
		foreach ($array as $key => $value) {
			if (is_int($key)) {
				$key	= '';
			} elseif (ctype_digit((string) $key)) {
				$key 	= intval($key) . '=>' ;
			} else {
				$key 	= "'" . str_replace("'", "\'", $key) . "'=>" ;
			}
			
			if (is_array($value)) {
				$value	= $this->_array2string($value);
			} elseif (ctype_digit((string) $value)) {
				$value 	= intval($value);
			} else {
				$value 	= "'" . str_replace("'", "\'", $value) . "'";
			}
			
			$strings[]	= $key . $value;
		}
		
		return 'array(' . implode(',', $strings) . ')';
	}
}

define('FILE_APPEND', 1);
function file_put_contents($n, $d, $flag = false)
{
	$mode 	= ($flag == FILE_APPEND || strtoupper($flag) == 'FILE_APPEND') ? 'a' : 'w';
	$f 		= @fopen($n, $mode);
	
	if ($f === false) {
		return 0;
	} else {
		if (is_array($d)) {
			$d = implode($d);
		}
		$bytes_written = fwrite($f, $d);
	
		fclose($f);
		
		return $bytes_written;
	}
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * c-hanging-comment-ender-p: nil
 * End:
 */
 
