<?php

require_once ('Fonction.class.php');

abstract class XMLElement {

	
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
	 * @var 	string			$element		
	 */
	protected $element;
	
	/**
	 * @access	protected
	 * @var 	object			$root		
	 */
	protected $root;
	
	/**
	 * @access	protected
	 * @var 	array			$nameSpaces				 */
	protected $nameSpaces;

	
	/**
	 * @access 	public
	 * @param 	string			$element				
	 * @param 	object			$core					
	 * @param 	object			$xpath					
	 * @return 	void
	 */
	public function load($element, $core, $xpath) {
		$this->element = $element;
		$this->core    = $core;
		$this->xpath   = $xpath;
		$this->root    = $this->core->documentElement;
		$this->nameSpaces = Fonction::getNamespace();
	}
	
	/**
	 * @access 	public
	 * @param 	boolean			$xmp		
	 * @return 	string							
	 */
	public function saveXML($xmp = false) {
		if ($xmp) {
			$str = '<xmp>';
			$str .= $this->core->saveXML();
			$str .= '</xmp>';	
		} else {
			$str = $this->core->saveXML();
		}
		return $str;
	}

	
	/**
	 * @access 	public
	 * @return 	string								
	 */
	public function getElementType() {
		return $this->element;	
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$type				
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent				
	 * @return 	object								s
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


