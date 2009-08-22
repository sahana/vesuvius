<?php
/**
* Whiz - a tiny caching template engine
* requires that its $cache_dir is writable
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

class Whiz {
	protected $vars;
	protected $cache_dir;
	protected $template_dir;

	function Whiz($cache_dir, $template_dir) {
		$this->cache_dir = $cache_dir;
		$this->template_dir = $template_dir;
		$this->vars = array();

		// check if we have a cache directory
		if(!file_exists($cache_dir))
			if(!mkdir($cache_dir)) {
				add_error(_("Template error: could not create template cache directory."));
				return false;
			}
	}

	function assign($key, $value) {
		$this->vars[$key] = $value;
	}

	function display($template) {
		$template_path = $this->template_dir.$template;
		if(!file_exists($template_path)) {
			add_error(_("Template error: No such template file:") . $template_path);
			return false;
		}
		$cache_id = md5(realpath($template_path));
		$cache_path = $this->cache_dir.basename($template).'.'.$cache_id.'.inc';
		if(!file_exists($cache_path) || filemtime($cache_path) <= filemtime($template_path)) {
			require('tags.inc');
			$compiled = preg_replace($find, $replace, file_get_contents($template_path));
			$compiled = preg_replace($empty_blocks, "\n", $compiled);
			if(empty($compiled)||!$compiled) {
				add_error(_("Template error: Error caching template file:") . $template);
				return false;
			}
			else {
				if(!($h = @fopen($cache_path, 'w'))) {
					add_error(_("Template error: could not write to template cache directory."));
					return false;
				}
				fwrite($h, $compiled);
				fclose($h);
			}
		}
		extract($this->vars);
		include($cache_path);
		return true;
	}

	function clear_cache() {
		if (is_dir($this->cache_dir))
    		if ($dh = opendir($this->cache_dir)) {
        		while (($file = readdir($dh)) !== false)
        			if(!is_dir($file))
            			unlink($this->cache_dir.$file);
				closedir($dh);
    		}
	}
}

