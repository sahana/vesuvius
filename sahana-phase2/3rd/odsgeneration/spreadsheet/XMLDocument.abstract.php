<?php

require_once ('Fonction.class.php');

abstract class XMLDocument {

	/**
	 * @access	protected
	 * @var 	object			$core
	 */
	protected $core;

	/**
	 * @access	protected
	 * @var 	object			$xpath
	 */
	protected $xpath;
	
	/**
	 * @access	protected
	 * @var 	string			$pathTemplates
	 */
	protected $pathTemplates;
	
	/**
	 * @access	protected
	 * @var 	string			$pathSave
	 */
	protected $pathSave;
	
	/**
	 * @access	protected
	 * @var 	string			$fileName	
	 */
	protected $fileName;
	
	/**
	 * @access	protected
	 * @var 	array			$nameSpaces		 */
	protected $nameSpaces;
	
	/**
	 * @access	protected
	 * @var 	object			$root					
	 */
	protected $root;
	
	/**
	 * @access 	public
	 * @param 	string			$file_name			
	 * @param 	string			$path_save			
	 * @param 	string			$path_templates		
	 * @param 	boolean			$format_output		
	 * @param 	boolean			$white_space			
	 * @return 	void
	 */
	public function load($file_name, $path_save, $path_templates, $format_output, $white_space) {
		try {
			$this->fileName         = $file_name;
			$this->pathTemplates    = Fonction::removeLastSlash($path_templates);
			$this->pathSave         = Fonction::removeLastSlash($path_save);
			$this->core = new DOMDocument;
			$this->core->preserveWhiteSpace = $white_space;
			$this->core->formatOutput       = $format_output;

			if (!@$this->core->load($this->pathTemplates.'/'.$this->fileName)) {
				throw new Exception('');	
			}
			$this->xpath = new DOMXPath($this->core);
			$this->root  = $this->core->documentElement; 

			$this->nameSpaces = Fonction::getNamespace();
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	public
	 * @param 	boolean			$xmp
	 * @return 	string	
	 */
	public function saveXML($xmp = false) {
		$this->_beforeSave();
		if ($xmp) {
			$str = '<xmp>';
			$str .= $this->core->saveXML();
			$str .= '</xmp>';	
		} else {
			$str = $this->core->saveXML();
		}
		$this->_afterSave();
		return $str;
	}
	
	/**
	 * @access 	public
	 * @return 	boolean								
	 */
	public function saveFile() {
		if (!is_dir($this->pathSave))
			mkdir($this->pathSave, 0777);
		if ($this->_beforeSave()){
			$this->core->save($this->pathSave.'/'.$this->fileName);
			return $this->_afterSave();
		} else {
			return false;
		}
	}

	/**
	 * @access 	public
	 * @return 	string								
	*/
	public function getGeneratedDirName() {
		return $this->pathSave;	
	}
	
	/**
	 * @access 	public
	 * @return 	string								
	 */
	public function getTemplatesDirName() {
		return $this->pathTemplates;	
	}
	
	/**
	 * @access 	public
	 * @return 	string								
	 */
	public function getFileName() {
		return $this->fileName;	
	}

	/**
	 * @access 	protected
	 * @return 	boolean								
	 */
	protected function _beforeSave() {
		return true;
	}
	
	/**
	 * @access 	protected
	 * @return 	boolean								
	 */
	protected function _afterSave() {
		return true;
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$type					
	 * @param 	string			$element				
	 * @param 	string			$str					
	 * @param 	object			$parent					
	 * @return 	object									
	 */
	protected function _addElement($type, $element, $str = null, $parent = null) {
		try {
			if ($str)
				$new = $this->core->createElementNS($this->nameSpaces[$type], $type.':'.$element, Fonction::checkString($str));
			else 
				$new = $this->core->createElementNS($this->nameSpaces[$type], $type.':'.$element);
			if (!$parent)
				$this->root->appendChild($new);
			else 
				$parent->appendChild($new);
			return $new;
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$type					
	 * @param 	string			$element				
	 * @param 	string			$str					
	 * @param 	object			$parent					
	 * @return 	object	
	 */
	protected function _setElement($type, $element, $str = null, $parent = null) {
		try {
			$elem = $this->xpath->query('//'.$type.':'.$element);
			if ($elem->length == 0)
				return $this->_addElement($type, $element, $str, $parent);
			else {
				$pos = 0;
				$el = $elem->item($pos);
				$txt = $this->core->createTextNode($str);
				$el->replaceChild($txt, $el->firstChild);
				return $el;	
			}
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	
}


