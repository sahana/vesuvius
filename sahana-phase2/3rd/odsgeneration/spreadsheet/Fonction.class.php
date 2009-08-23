<?php

class Fonction {	
		
	/**
	 * @access 	public
	 * @return 	object				
	 */
	public function __construct() {
	}	
		
	/**
	 * @access 	static
	 * @return 	array									
	 */
	static function getNamespace() {
		$nameSpaces = array(
			'manifest'	=> 'urn:oasis:names:tc:opendocument:xmlns:manifest:1.0',
			'office' 	=> 'urn:oasis:names:tc:opendocument:xmlns:office:1.0',
			'style'  	=> 'urn:oasis:names:tc:opendocument:xmlns:style:1.0',
			'text'  	=> 'urn:oasis:names:tc:opendocument:xmlns:text:1.0',
			'table' 	=> 'urn:oasis:names:tc:opendocument:xmlns:table:1.0',
			'draw'  	=> 'urn:oasis:names:tc:opendocument:xmlns:drawing:1.0',
			'fo'    	=> 'urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0',
			'meta'   	=> 'urn:oasis:names:tc:opendocument:xmlns:meta:1.0',
			'number'	=> 'urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0',
			'svg'    	=> 'urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0',
			'chart'  	=> 'urn:oasis:names:tc:opendocument:xmlns:chart:1.0',
			'dr3d'  	=> 'urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0',
			'form'  	=> 'urn:oasis:names:tc:opendocument:xmlns:form:1.0',
			'script'	=> 'urn:oasis:names:tc:opendocument:xmlns:script:1.0',
			'dc'     	=> 'http://purl.org/dc/elements/1.1/',
			'ooo'    	=> 'http://openoffice.org/2004/office',
			'ooow'   	=> 'http://openoffice.org/2004/writer',
			'oooc'  	=> 'http://openoffice.org/2004/calc',
			'math'  	=> 'http://www.w3.org/1998/Math/MathML',
			'xlink' 	=> 'http://www.w3.org/1999/xlink',
			'dom'   	=> 'http://www.w3.org/2001/xml-events',
			'xsd'   	=> 'http://www.w3.org/2001/XMLSchema',
			'xsi'   	=> 'http://www.w3.org/2001/XMLSchema-instance',
			'xforms' 	=> 'http://www.w3.org/2002/xforms'
		);
		return $nameSpaces;
	}
	
	/**
	 * @access 	static
	 * @param 	boolean			$vide				
	 * @return 	array								
	 */
	static function getLetters($vide = true) {
		$lettres = array(
			 'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',  'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',
			'aa', 'ab', 'ac', 'ad', 'ae', 'af', 'ag', 'ah', 'ai', 'aj', 'ak', 'al', 'am', 'an', 'ao', 'ap', 'aq', 'ar', 'as', 'at', 'au', 'av', 'aw', 'ax', 'ay', 'az',
			'ba', 'bb', 'bc', 'bd', 'be', 'bf', 'bg', 'bh', 'bi', 'bj', 'bk', 'bl', 'bm', 'bn', 'bo', 'bp', 'bq', 'br', 'bs', 'bt', 'bu', 'bv', 'bw', 'bx', 'by', 'bz',
			'ca', 'cb', 'cc', 'cd', 'ce', 'cf', 'cg', 'ch', 'ci', 'cj', 'ck', 'cl', 'cm', 'cn', 'co', 'cp', 'cq', 'cr', 'cs', 'ct', 'cu', 'cv', 'cw', 'cx', 'cy', 'cz',
			'da', 'db', 'dc', 'dd', 'de', 'df', 'dg', 'dh', 'di', 'dj', 'dk', 'dl', 'dm', 'dn', 'do', 'dp', 'dq', 'dr', 'ds', 'dt', 'du', 'dv', 'dw', 'dx', 'dy', 'dz',
			'ea', 'eb', 'ec', 'ed', 'ee', 'ef', 'eg', 'eh', 'ei', 'ej', 'ek', 'el', 'em', 'en', 'eo', 'ep', 'eq', 'er', 'es', 'et', 'eu', 'ev', 'ew', 'ex', 'ey', 'ez',
			'fa', 'fb', 'fc', 'fd', 'fe', 'ff', 'fg', 'fh', 'fi', 'fj', 'fk', 'fl', 'fm', 'fn', 'fo', 'fp', 'fq', 'fr', 'fs', 'ft', 'fu', 'fv', 'fw', 'fx', 'fy', 'fz',
			'ga', 'gb', 'gc', 'gd', 'ge', 'gf', 'gg', 'gh', 'gi', 'gj', 'gk', 'gl', 'gm', 'gn', 'go', 'gp', 'gq', 'gr', 'gs', 'gt', 'gu', 'gv', 'gw', 'gx', 'gy', 'gz',
			'ha', 'hb', 'hc', 'hd', 'he', 'hf', 'hg', 'hh', 'hi', 'hj', 'hk', 'hl', 'hm', 'hn', 'ho', 'hp', 'hq', 'hr', 'hs', 'ht', 'hu', 'hv', 'hw', 'hx', 'hy', 'hz',
			'ia', 'ib', 'ic', 'id', 'ie', 'if', 'ig', 'ih', 'ii', 'ij', 'ik', 'il', 'im', 'in', 'io', 'ip', 'iq', 'ir', 'is', 'it', 'iu', 'iv'
		);
		if ($vide)
			array_unshift($lettres, '');
		return $lettres;
	}
		
	/**
	 * @access 	static
	 * @param 	string			$str				
	 * @return 	string							
	 */
	static function removeLastSlash($str) {
		$str = str_replace('\\', '/', $str);
		$str = rtrim($str, '/');
		return $str;
	}
	
	/**
	 * @access 	static
	 * @param 	string			$file_name			
	 * @param 	string			$extension			
	 * @return 	string								
	 */
	static function checkFileName($file_name, $extension) {
		$nom = explode('.', $file_name);
		switch ($nom[count($nom) - 1]){
			case 'zip':
			case 'jar':
			case $extension:
				$ok = true;
				break;
			default:
				$ok = false;	
		}

		if (!$ok){
			$file_name = implode('.', $nom).'.'.$extension;
		}
		return $file_name;
	}
	
	/**
	 * @access 	static
	 * @param 	string			$str					
	 * @param 	boolean			$add_slashes			
	 * @param 	boolean			$is_attribute			
	 * @return 	string								
	 */
	static function checkString($str, $add_slashes = false, $is_attribute = false) {
		$bad = array(
			array( 'char' => '&', 'repl' => 'et' ),
			array( 'char' => '+', 'repl' => '+' ),
			array( 'char' => '#', 'repl' => '#' ),
			array( 'char' => '<', 'repl' => '<' ),
			array( 'char' => '>', 'repl' => '>' )
		);
		if ($is_attribute)
			array_push($bad, array('char' => '"', 'repl' => "'"));
		foreach ($bad as $c)
			$str = str_replace($c['char'], $c['repl'], $str);
		$str = stripslashes($str);
		if ($add_slashes){
			$str = addslashes($str);
		}
		$str = utf8_encode($str);
		return $str;	
	}
	
	/**
	 * @access 	static
	 * @param 	string			$str				
	 * @param 	boolean			$add_slashes		
	 * @return 	string								
	 */
	static function checkAttribute($str, $add_slashes = false) {
		return self::checkString($str, $add_slashes, true);	
	}
	
	/**
    	 *
	 * @access	public
	 * @param 	string			$dir_name			
	 * @return	boolean								
     */
	static function delDir($dir_name) {
		self::removeLastSlash($dir_name);
		if(empty($dir_name))
			return false;
		if(file_exists($dir_name)) {
			$dir = dir($dir_name);
			while($file = $dir->read()) {
				if($file != '.' && $file != '..') {
					if(is_dir($dir_name.'/'.$file))
						self::delDir($dir_name.'/'.$file);
					else
						unlink($dir_name.'/'.$file);
				}
			}
			$dir->close();
			rmdir($dir_name.'/'.$file);
			return true;
		}
		return false;
	}

	/**
	 * @access 	static
	 * @param 	array			$arr			
	 * @param 	string			$default			
	 * @param 	integer			$max_col			
	 * @return 	array					
	 */
	function array_count_followed_values($arr, $default = '', $max_col = 0) {
		$tmp = array();
		$insert = true;
		$cpt = 0;
		$courant = null;
		foreach ($arr as $key => $val) {
			// Si on a une valeur par d�aut, on la g�e
			if ($default && $cpt < $key - 1 && $key - $cpt - 1 > 0) {
				if ($courant !== $default) {
					$tmp[] = array(
						'value' => $default,
						'nb' => $key - $cpt - 1
					);
					$insert = ($default !== $val) ? true : false;
				} else {
					$pos = count($tmp) - 1;
					if (isset($tmp[$pos]['nb'])) {
						$tmp[$pos]['nb']++;
					}
					$insert = false;
				}
			} else {
				$insert = ($courant !== $val) ? true : false;
			}

			if ($insert) {
				$tmp[] = array(
					'value' => $val,
					'nb' => 1
				);
			} else {
				$pos = count($tmp) - 1;
				if (isset($tmp[$pos]['nb'])) {
					$tmp[$pos]['nb']++;
				}
			}
			$cpt = $key;
			$courant = $val;
		}
		
		if ($max_col > count($arr)) {
			end($arr);
			if ($max_col - key($arr) > 0) {
				$tmp[] = array(
					'value' => $default,
					'nb' => $max_col - key($arr)
				);
			}
		}
		return $tmp;
	}

	/**
	 * @access 	static
	 * @param 	object			$list				
	 * @param 	string			$infos			
	 * @return 	void
	 */
	static function debug_node_list ($list, $infos = '') {
		echo "<br>This list has " . $list->length . " elements\n";
		if (count($list) == 0)
			echo "<br>This list seems to be empty\n";
		else {
			echo "<ol>\n";
			foreach ($list as $el) {
				echo "<li>\n"; self::debug_element_rec ($el, ''); echo "</li>\n";
			}
			echo "</ol>\n"; 
		}
	}

	/**
	 * @access 	static
	 * @param 	object			$el					
	 * @param 	string			$info				
	 * @return 	void
	 */
	static function debug_element_rec ($el, $info = '') {
		$nodeType = $el->nodeType;
		echo "<br> Node Type = " . $nodeType . "\n";

		switch ($nodeType) {
			case XML_TEXT_NODE: 
				echo "<br>Node Value =" . $el->nodeValue;
				break;
			case XML_ELEMENT_NODE: 
				echo "<br>Element Name =" . $el->nodeName;
				break;
			case XML_ATTRIBUTE_NODE:
				echo "<br>Attribute Name =" . $el->nodeName;
				break;
			default:
				echo "<br>Strange Node !!! TYPE of element = " . gettype($el) . "\n";
		}
		if ($el->hasAttributes()) {
			echo "<br>Attributes: ";
			foreach ($el->attributes as $attr) {
				echo "[ " . $attr->name . " = " . $attr->value . " ]\n";
			}
		}
		if ($el->hasChildNodes()) {
			self::debug_node_list ($el->childNodes, "Children of " . $el->nodeName);
		} 
	}
	
	/**
	 * @access 	static
	 * @param 	
	 * @return
	 */
	static function debugCells($cells, $directPrint = false) {
		$tab = array();
		foreach ($cells as $col => $obj) {
			foreach ($obj as $row => $cell) {
				$tab[$col][$row] = $cell->getName();
			}	
		}	
		if ($directPrint) {
			echo '<pre>';
			print_r($tab);
			echo '</pre>';
		} else {
			return $tab;
		}		
	}

}


