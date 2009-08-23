<?php

require_once ('XMLDocument.abstract.php');
require_once ('Fonction.class.php');

class Styles extends XMLDocument {
	

	/**
	 * @access 	public
	 * @param 	string			$path_save			
	 * @param 	string			$path_templates			
	 * @param 	boolean			$format_output			
	 * @param 	boolean			$white_space		
	 * @return 	object				
	 */
	public function __construct($path_save, $path_templates, $format_output, $white_space) {
		$fileName = 'styles.xml';
		$this->load($fileName, $path_save, $path_templates, $format_output, $white_space);
	}	
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function blu() {
		
	}

	/**
	 * @access 	protected
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent				
	 * @return 	object			
	 */
	protected function _addStyleElement($element, $str = '', $parent = null) {
		return $this->_addElement('style', $element, $str, $parent);
	}
	
}


