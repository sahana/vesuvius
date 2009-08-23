<?php

require_once ('XMLDocument.abstract.php');
require_once ('Fonction.class.php');

class Meta extends XMLDocument {
	
	
	/**
	 * @access 	public
	 * @param 	string			$path_save				
	 * @param 	string			$path_templates		
	 * @param 	boolean			$format_output		
	 * @param 	boolean			$white_space		
	 * @return 	object								
	 */
	public function __construct($path_save, $path_templates, $format_output, $white_space) {
		$fileName = 'meta.xml';
		$this->load($fileName, $path_save, $path_templates, $format_output, $white_space);
		$this->root = $this->xpath->query('//office:meta')->item(0);
		$this->setGenerator('PHP-OpenOffice 2 open source script');
	}	

	/**
	 * @access 	public
	 * @param 	string|array	$keyword		
	 * @return 	void
	 */
	public function addKeyWord($keyword) {
		if (is_array($keyword))
			$keywords = implode(' ', $keyword);
		else 
			$keywords = $keyword;
	
		$this->_addMetaElement('keyword', $keywords);
	}
	
	/**
	 * Ajoute un meta utilisateur particulier
	 *
	 * @access 	public
	 * @param 	string			$attr					L'attribut du meta
	 * @param 	string			$str					Le contenu du meta
	 * @return 	void
	 */
	public function addUserDefined($attr, $str) {
		$new = $this->_addMetaElement('user-defined', $str);
		$new->setAttribute('meta:name', Fonction::checkAttribute($attr));
	}
	
	/**
	 * @access 	public
	 * @param 	string			$generator		
	 * @return 	void
	 */
	public function setGenerator($generator) {
		$this->_setMetaElement('generator', $generator);
	}
	
	/**
	 * @access 	public
	 * @param 	string			$creator				Le nom de la personne qui a cr� le fichier
	 * @return 	void
	 */
	public function setInitialCreator($creator) {
		$this->_setMetaElement('initial-creator', $creator);
	}
	
	/**
	 * @access 	public
	 * @param 	string			$dt						La date de cr�tion du fichier
	 * @return 	void
	 */
	public function setInitialCreationDate($dt) {
		$this->_setMetaElement('creation-date', $dt);
	}
	
	/**
	 * Ajoute le nombre de fois que le document a ���it�	 *
	 * @access 	public
	 * @param 	integer			$cycle					Le nombre de fois que le document a ���it�	 * @return 	void
	 */
	public function setEditingCycles($cycle) {
		$this->_setMetaElement('editing-cycles', $cycle);
	}
	
	/**
	 * Ajoute le temps pass���iter le fichier, tous cycles confondus (P{d}T09{H}54{M}26,50{S})
	 *
	 * @access 	public
	 * @param 	string			$duration				Le temps d'�ition d'un fichier
	 * @return 	void
	 */
	public function setEditingDuration($duration) {
		$this->_setMetaElement('editing-duration', $duration);
	}
		
	/**
	 * Ajoute le titre. Appara� en haut dans la barre de titre
	 *
	 * @access 	public
	 * @param 	string			$title					Le titre du fichier
	 * @return 	void
	 */
	public function setTitle($title) {
		$this->_setDublinElement('title', $title);
	}
		
	/**
	 * Ajoute des mots-cl�ou phrases-cl�d�rivant le contenu du document
	 *
	 * @access 	public
	 * @param 	string			$subject				Le ou les mots-cl��ajouter
	 * @return 	void
	 */
	public function setSubject($subject) {
		$this->_setDublinElement('subject', $subject);
	}
		
	/**
	 * Ajoute une description
	 *
	 * @access 	public
	 * @param 	string			$description			La description
	 * @return 	void
	 */
	public function setDescription($description) {
		$this->_setDublinElement('description', $description);
	}
		
	/**
	 * Ajoute un cr�teur. Repr�ente la derni�e personne �avoir modifi�le fichier (oui oui)
	 *
	 * @access 	public
	 * @param 	string			$creator				Le nom du cr�teur
	 * @return 	void
	 */
	public function setCreator($creator) {
		$this->_setDublinElement('creator', $creator);
	}
		
	/**
	 * Ajoute la date de modification (oui oui) en lien avec le cr�teur (2003-08-29T09:54:26,50)
	 *
	 * @access 	public
	 * @param 	string			$dt						La date de modification
	 * @return 	void
	 */
	public function setCreationDate($dt) {
		$this->_setDublinElement('date', $dt);
	}
		
	/**
	 * Ajoute la langue du document
	 *
	 * @access 	public
	 * @param 	string			$language				La langue du document
	 * @return 	void
	 */
	public function setLanguage($language) {
		$this->_setDublinElement('language', $language);
	}
	
	/**
	 * Fonction qui ajoute ou modifie un ��ent sign�comme �ant "Dublin Core"
	 *
	 * @access 	protected
	 * @param 	string			$element				L'��ent Dublin Core Element
	 * @param 	string			$str					La valeur de l'��ent
	 * @param 	object			$parent					Le DOMElement parent de celui qu'on cr�
	 * @return 	object									Le DOMElement cr� ou modifi�	 */
	protected function _setDublinElement($element, $str = null, $parent = null) {
		return $this->_setElement('dc', $element, $str, $parent);
	}
	
	/**
	 * Fonction qui ajoute ou remplace un ��ent sign�comme �ant un ��ent meta
	 *
	 * @access 	protected
	 * @param 	string			$element				Le nom de l'��ent
	 * @param 	string			$str					La valeur de l'��ent
	 * @param 	object			$parent					Le DOMElement parent de celui qu'on cr�
	 * @return 	object									Le DOMElement cr� ou modifi�	 */
	protected function _setMetaElement($element, $str = null, $parent = null) {
		return $this->_setElement('meta', $element, $str, $parent);
	}
	
	/**
	 * Fonction qui ajoute un ��ent sign�comme �ant un ��ent meta
	 *
	 * @access 	protected
	 * @param 	string			$element				
	 * @param 	string			$str					
	 * @param 	object			$parent					
	 * @return 	object								
	 */
	protected function _addMetaElement($element, $str = null, $parent = null) {
		return $this->_addElement('meta', $element, $str, $parent);
	}
	
}


