<?php

require_once ('XMLDocument.abstract.php');
require_once ('Fonction.class.php');

class Settings extends XMLDocument {
		
	/**
	 * Constructeur de classe
	 *
	 * @access 	public
	 * @param 	string			$path_save				
	 * @param 	string			$path_templates			
	 * @param 	boolean			$format_output		
	 * @param 	boolean			$white_space			
	 * @return 	object								
	 */
	public function __construct($path_save, $path_templates, $format_output, $white_space) {
		$fileName = 'settings.xml';
		$this->load($fileName, $path_save, $path_templates, $format_output, $white_space);
	}	

	/**
	 * @access 	public
	 * @return 	void
	 */
	public function blu() {
		
	}
	
}


