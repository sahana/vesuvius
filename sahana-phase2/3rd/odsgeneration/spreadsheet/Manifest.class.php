<?php

require_once ('XMLDocument.abstract.php');
require_once ('Fonction.class.php');

class Manifest extends XMLDocument {
	/**
	 * @access 	public
	 * @param 	string			$path_save			
	 * @param 	string			$path_templates		
	 * @param 	boolean			$format_output		
	 * @param 	boolean			$white_space		
	 * @return 	object			
	 */
	public function __construct($path_save, $path_templates, $format_output, $white_space) {
		$fileName = 'manifest.xml';
		$this->load($fileName, $path_save, $path_templates, $format_output, $white_space);
		$this->root = $this->core->documentElement;
	}	
		
	/**
	 * @access 	public
	 * @param 	string			$media_type	
	 * @param 	string			$full_path			
	 * @return 	void
	 */
	public function addFileEntry($media_type, $full_path) {
		$new = $this->_addManifestElement('file-entry');
		$new->setAttribute('manifest:media-type', Fonction::checkAttribute($media_type));
		$new->setAttribute('manifest:full-path', Fonction::checkAttribute($full_path));
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent				
	 * @return 	object		
	 */
	protected function _addManifestElement($element, $str = '', $parent = null) {
		return $this->_addElement('manifest', $element, $str, $parent);
	}
	
}


