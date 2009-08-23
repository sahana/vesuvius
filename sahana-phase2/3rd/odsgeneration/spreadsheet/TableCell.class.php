<?php

require_once ('XMLElement.abstract.php');
require_once ('Fonction.class.php');


class TableCell extends XMLElement {

	
	/**
	 * @access 	protected
	 * @var 	object			$parent					
	 */
	protected $parent;
	
	/**
	 * @access 	protected
	 * @var 	string			$type					
	 */
	protected $type;
	
	/**
	 * @access 	protected
	 * @var 	string			$styleName				
	 */
	protected $styleName;
	
	/**
	 * @access 	protected
	 * @var 	string			$formula				
	 */
	protected $formula;
	
	/**
	 * @access 	protected
	 * @var 	integer			$posx					
	 */
	protected $posx;
	
	/**
	 * @access 	protected
	 * @var 	integer			$posy					
	 */
	protected $posy;
	
	/**
	 * @access 	protected
	 * @var 	integer			$width					
	 */
	protected $width;
	
	/**
	 * @access 	protected
	 * @var 	integer			$height					
	 */
	protected $height;
	
	/**
	 * @access 	protected
	 * @var 	string			$contenu				
	 */
	protected $contenu;
	
	/**
	 * @access 	protected
	 * @var 	string			$backgroundColor		
	 */
	protected $backgroundColor;
	
	/**
	 * @access 	protected
	 * @var 	string			$borderTop				
	 */
	protected $borderTop;
	
	/**
	 * @access 	protected
	 * @var 	string			$borderLeft				
	 */
	protected $borderLeft;
	
	/**
	 * @access 	protected
	 * @var 	string			$borderBottom			
	 */
	protected $borderBottom;
	
	/**
	 * @access 	protected
	 * @var 	string			$borderRight			
	 */
	protected $borderRight;
	
	/**
	 * @access 	protected
	 * @var 	string			$fontWeight				
	 */
	protected $fontWeight;
	
	/**
	 * @access 	protected
	 * @var 	string			$fontStyle				
	 */
	protected $fontStyle;
	
	/**
	 * @access 	protected
	 * @var 	string			$fontSize				
	 */
	protected $fontSize;
	
	/**
	 * @access 	protected
	 * @var 	string			$fontFamily				
	 */
	protected $fontFamily;
	
	/**
	 * @access 	protected
	 * @var 	string			$textAlign				
	 */
	protected $textAlign;
	
	/**
	 * @access 	protected
	 * @var 	string			$verticalAlign			L'alignement vertical du texte
	 */
	protected $verticalAlign;
	
	/**
	 * @access 	protected
	 * @var 	string			$color					La couleur du texte
	 */
	protected $color;
	
	/**
	 * @access 	protected
	 * @var 	integer			$spannedRows			Le nombre de lignes fusionn�s depuis la cellule
	 */
	protected $spannedRows;
	
	/**
	 * @access 	protected
	 * @var 	integer			$spannedCols			Le nombre de colonnes fusionn�s depuis la cellule
	 */
	protected $spannedCols;
	
	/**
	 * @access 	protected
	 * @var 	integer			$decimal			
	 */
	protected $decimal;
	
	/**
	 * @access 	public
	 * @param 	object			$parent			
	 * @param 	object			$core				
	 * @param 	object			$xpath				
	 * @return 	object								
	 */
	public function __construct($parent = '', $core = '', $xpath = '') {
		if ($parent && $core && $xpath) {
			$this->load('table-cell', $core, $xpath);
			$this->root = $core;
			$this->parent = $parent;
		}
	}

	/**
	 * @access 	static
	 * @param 	object			$cell1			
	 * @param 	object			$cell2					
	 * @return 	integer									
	 */
	static function getNbRows($cell1, $cell2) {
		$nbRows = $cell1->getY() - $cell2->getY();
		if ($nbRows < 0)
			$nbRows *= -1;
		return $nbRows;
	}
	
	/**
	 * @access 	static
	 * @param 	object			$cell1					Une cellule TableCell
	 * @param 	object			$cell2					Une cellule TableCell
	 * @return 	integer									Le nombre de colonnes entre les 2 cellules
	 */
	static function getNbCols($cell1, $cell2) {
		$nbCols = $cell1->getX() - $cell2->getX();
		if ($nbCols < 0)
			$nbCols *= -1;
		return $nbCols;
	}

	/**
	 * @access 	public
	 * @return 	void
	 */
	public function setType() {
		$contenu = $this->contenu;
		$type = 'string';
		if (is_float($contenu) || is_numeric($contenu) || is_int($contenu))
			$type = 'float';
		// Check s'il s'agit d'une formule
		if (strpos($contenu, '=SUM') !== false) {
			$type = $this->formulaSUM($contenu);
		}
		$this->type = $type;
		return $type;
	}
	
	/**
	 * Fonction qui set comme contenu de cellule une somme (par exemple A1:B6;C10)
	 *
	 * @access 	public
	 * @param 	string			$formula				La formule (par exemple 'A1:B6;C10')
	 * @return 	void
	 */
	public function setFormulaSUM($formula) {
		$f = (strpos($formula, '=SUM(') === false) ? '=SUM('.$formula.')' : $formula;
		// On sauve la formule
		$f = str_replace('(', '([.', $f); $f = str_replace(')', '])', $f);
		$f = str_replace(';', '];[.', $f); $f = str_replace(':', ':.', $f);
		// On en extrait les donn�s
		$formula = ltrim($formula, '=SUM(');
		$formula = rtrim($formula, ')');
		$l = Fonction::getLetters(true);
		
		$somme = 0;
		$blocs = explode(';', $formula);
		$cellules = $this->parent->getCells();
		foreach ($blocs as $bloc) {
			$cells = explode(':', $bloc);
			$tab = array();
			foreach ($cells as $cell) {
				$cols = ''; $row = '';
				for ($i = 0; $i < strlen($cell); $i++) {
					if (is_int($cell[$i]) || is_float($cell[$i]) || is_numeric($cell[$i])) $row .= $cell[$i];
					else $cols .= $cell[$i];
				}
				
				$col = array_search(strtolower($cols), $l);
				$tab[] = $cellules[$row][$col];
			}
			
			if (count($tab) == 1) 
				$somme += $tab[0]->getContent() * 1;	
			else 
				$cells = $this->parent->getRangeCells($tab[0], $tab[1], '_setSum', '', $somme);	
		}
		
		$this->formula = $f;
		$this->contenu = $somme;
		$this->type = 'float';
		return $this->type;
	}

	/**
	 * @access 	public
	 * @param 	integer			$x						La position de la cellule en X (colonne)
	 * @param 	integer			$y						La position de la cellule en Y (ligne)
	 * @return 	void
	 */
	public function setPos($x, $y) {
		$this->setPosX($x);	
		$this->setPosY($y);
	}
	
	/**
	 * @access 	public
	 * @param 	integer			$width					
	 * @param 	integer			$height					
	 * @return 	void
	 */
	public function setDimensions($width, $height) {
		$this->setwidth($x);	
		$this->setheight($y);
	}
	
	/**
	 * Fonction qui set les bordures de la cellule (0.002cm solid #000000)
	 *
	 * @access 	public
	 * @param 	string			$data					
	 * @param 	string			$dataLR					
	 * @return 	void
	 */
	public function setBorder($data, $dataLR = '') {
		$this->setBorderTop($data);	
		$this->setBorderBottom($data);
		$borderLR = ($dataLR != '') ? $dataLR : $data;
		$this->setBorderLeft($borderLR);	
		$this->setBorderRight($borderLR);	
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function setFontBold() {
		$this->setFontWeight('bold');
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function setFontItalic() {
		$this->setFontStyle('italic');
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function setTextCenter() {
		$this->setTextAlign('center');
	}
	
	/**
	 * @access 	public
	 * @return 	string									Le nom de la cellule
	 */
	public function getName() {
		return 'ce'.$this->getX().$this->getY();
	}
	
	/**
	 * @access 	public
	 * @param 	string			$type					'col' ou 'row'
	 * @return 	string									Le nom de la cellule
	 */
	public function getFreeName($type) {
		switch ($type) {
			case 'col':
				$retour = 'ce'.($this->getX() - 1).$this->getY();
				break;
			case 'row':
				$retour = 'ce'.$this->getX().($this->getY() - 1);
				break;
			default:
				$retour = 'ce'.$this->getX().$this->getY();
		}
		return $retour;
	}
		
	/**
	 * @access 	public
	 * @param 	string			$contenu				
	 * @param 	boolean			$set_type				
	 * @return 	void
	 */
	public function setContent($contenu, $set_type = true) {
		$this->contenu = $contenu;
		if ($set_type)
			$this->type = $this->setType();
	}
	
	/**
	 * @access 	public
	 * @param 	array			$style					
	 * @return 	void
	 */
	public function setStyleName($style) {
		$this->styleName = $style;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$couleur		
	 * @return 	void
	 */
	public function setBackgroundColor($couleur) {
		$this->backgroundColor = $couleur;
	}
	
	/**
	 * Fonction qui set la bordure du haut de la cellule (1px solid #000000)
	 *
	 * @access 	public
	 * @param 	string			$data				
	 * @return 	void
	 */
	public function setBorderTop($data) {
		$this->borderTop = $data;	
	}
	
	/**
	 * Fonction qui set la bordure de gauche de la cellule (1px solid #000000)
	 *
	 * @access 	public
	 * @param 	string			$data					
	 * @return 	void
	 */
	public function setBorderLeft($data) {
		$this->borderLeft = $data;	
	}
	
	/**
	 * Fonction qui set la bordure du bas de la cellule (1px solid #000000)
	 *
	 * @access 	public
	 * @param 	string			$data				
	 * @return 	void
	 */
	public function setBorderBottom($data) {
		$this->borderBottom = $data;	
	}
	
	/**
	 * Fonction qui set la bordure de droite de la cellule (1px solid #000000)
	 *
	 * @access 	public
	 * @param 	string			$data					La d�inition de la bordure de droite
	 * @return 	void
	 */
	public function setBorderRight($data) {
		$this->borderRight = $data;	
	}
	
	/**
	 * Fonction qui set la position de la cellule en X (colonne)
	 *
	 * @access 	public
	 * @param 	integer			$x						La position de la cellule en X (colonne)
	 * @return 	void
	 */
	public function setPosX($x) {
		$this->posx = $x;
	}
	
	/**
	 * Fonction qui set la position de la cellule en Y (ligne)
	 *
	 * @access 	public
	 * @param 	integer			$y						La position de la cellule en Y (ligne)
	 * @return 	void
	 */
	public function setPosY($y) {
		$this->posy = $y;	
	}
	
	/**
	 * Fonction qui set la hauteur de la cellule
	 *
	 * @access 	public
	 * @param 	integer			$height					La hauteur de la cellule
	 * @return 	void
	 */
	public function setHeight($height) {
		$this->height = $height;
	}
	
	/**
	 * Fonction qui set la largeur de la cellule
	 *
	 * @access 	public
	 * @param 	integer			$width					La largeur de la cellule
	 * @return 	void
	 */
	public function setWidth($width) {
		$this->width = $width;
	}
	
	/**
	 * Fonction qui set le gras de la police
	 *
	 * @access 	public
	 * @param 	string			$weight					Le gras de la police
	 * @return 	void
	 */
	public function setFontWeight($weight) {
		$this->fontWeight = $weight;
	}
	
	/**
	 * Fonction qui set le style de la police
	 *
	 * @access 	public
	 * @param 	string			$style					Le style de la police
	 * @return 	void
	 */
	public function setFontStyle($style) {
		$this->fontStyle = $style;
	}
	
	/**
	 * Fonction qui set la taille de la police
	 *
	 * @access 	public
	 * @param 	string			$size					La taille de la police
	 * @return 	void
	 */
	public function setFontSize($size) {
		$this->fontSize = $size;
	}
	
	/**
	 * Fonction qui set la famille de la police
	 *
	 * @access 	public
	 * @param 	string			$family					La famille de la police
	 * @return 	void
	 */
	public function setFontFamily($family) {
		$this->fontFamily = $family;
	}
	
	/**
	 * Fonction qui set l'alignement du texte
	 *
	 * @access 	public
	 * @param 	string			$align					L'alignement du texte
	 * @param 	boolean			$left_right				True pour dire que le texte se lit de gauche �droite
	 * @return 	void
	 */
	public function setTextAlign($align, $left_right = true) {
		if ($left_right) {
			if ($align == 'left') $align = 'start';
			if ($align == 'right') $align = 'end';
		} else {
			if ($align == 'right') $align = 'start';
			if ($align == 'left') $align = 'end';
		}
		$this->textAlign = $align;
	}
	
	/**
	 * Fonction qui set l'alignement vertical du texte
	 *
	 * @access 	public
	 * @param 	string			$align					L'alignement vertical du texte
	 * @return 	void
	 */
	public function setVerticalAlign($align) {
		if ($align == 'center') $align = 'middle';
		$this->verticalAlign = $align;
	}
	
	/**
	 * Fonction qui set la couleur du texte
	 *
	 * @access 	public
	 * @param 	string			$coul					La couleur du texte
	 * @return 	void
	 */
	public function setColor($coul) {
		$this->color = $coul;
	}
	
	/**
	 * Fonction qui set le nombre de lignes �fusionner depuis la cellule (cellule courante comprise)
	 *
	 * @access 	public
	 * @param 	integer			$spannedRows			Le nombre de lignes �fusionner depuis la cellule
	 * @return 	void
	 */
	public function setSpannedRows($spannedRows) {
		$this->spannedRows = $spannedRows;
	}
	
	/**
	 * Fonction qui set le nombre de lignes �fusionner depuis la cellule (cellule courante comprise)
	 *
	 * @access 	public
	 * @param 	integer			$spannedCols			Le nombre de colonnes �fusionner depuis la cellule
	 * @return 	void
	 */
	public function setSpannedCols($spannedCols) {
		$this->spannedCols = $spannedCols;
	}
	
	/**
	 * Fonction qui set le nombre de d�imales
	 *
	 * @access 	public
	 * @param 	integer			$decimal				Le nombre de d�imales
	 * @return 	void
	 */
	public function setDecimal($decimal) {
		$this->contenu = number_format($this->contenu, $decimal);
		$this->decimal = $decimal;
	}
	
	/**
	 * Fonction qui retourne le type de contenu de la cellule
	 *
	 * @access 	public
	 * @return 	string									Le type de contenu de la cellule
	 */
	public function getType() {
		return $this->type;	
	}
	
	/**
	 * Fonction qui retourne le nom du style utilis�et de la colonne et ligne associ�
	 *
	 * @access 	public
	 * @return 	string									Le nom du style de la cellule et de la colonne et ligne associ�
	 */
	public function getStyleName() {
		return $this->styleName;	
	}
	
	/**
	 * Fonction qui retourne le contenu de la cellule
	 *
	 * @access 	public
	 * @return 	string									Le contenu de la cellule
	 */
	public function getContent() {
		return $this->contenu;	
	}
	
	/**
	 * Fonction qui set la couleur de fond de la cellule
	 *
	 * @access 	public
	 * @return 	string									La couleur de fond
	 */
	public function getBackgroundColor() {
		return $this->backgroundColor;
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function getBorderTop() {
		return $this->borderTop;
	}
	
	/**
	 * Fonction qui r�up�e la bordure de gauche de la cellule
	 *
	 * @access 	public
	 * @return 	void
	 */
	public function getBorderLeft() {
		return $this->borderLeft;
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function getBorderBottom() {
		return $this->borderBottom;
	}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function getBorderRight() {
		return $this->borderRight;
	}
	
	/**
	 * Fonction qui retourne la position de la cellule en X (colonne)
	 *
	 * @access 	public
	 * @return 	integer									La position de la cellule en X (colonne)
	 */
	public function getX() {
		return $this->posx;	
	}
	
	/**
	 * Fonction qui retourne la position de la cellule en Y (ligne)
	 *
	 * @access 	public
	 * @return 	integer									La position de la cellule en Y (ligne)
	 */
	public function getY() {
		return $this->posy;	
	}
	
	/**
	 * Fonction qui retourne la largeur de la cellule
	 *
	 * @access 	public
	 * @return 	integer									La largeur de la cellule
	 */
	public function getWidth() {
		return $this->width;	
	}
	
	/**
	 * Fonction qui retourne la hauteur de la cellule
	 *
	 * @access 	public
	 * @return 	integer									La hauteur de la cellule
	 */
	public function getHeight() {
		return $this->height;	
	}
	
	/**
	 * Fonction qui retourne le gras de la police
	 *
	 * @access 	public
	 * @return 	string									Le gras de la police
	 */
	public function getFontWeight() {
		return $this->fontWeight;
	}
	
	/**
	 * Fonction qui retourne le style de la police
	 *
	 * @access 	public
	 * @return 	string									Le style de la police
	 */
	public function getFontStyle() {
		return $this->fontStyle;
	}
	
	/**
	 * Fonction qui retourne la taille de la police
	 *
	 * @access 	public
	 * @return 	string									La taille de la police
	 */
	public function getFontSize() {
		return $this->fontSize;
	}
	
	/**
	 * Fonction qui retourne la famille de la police
	 *
	 * @access 	public
	 * @return 	string									La famille de la police
	 */
	public function getFontFamily() {
		return $this->fontFamily;
	}
	
	/**
	 * Fonction qui retourne l'alignement du texte
	 *
	 * @access 	public
	 * @return 	string									L'alignement du texte
	 */
	public function getTextAlign() {
		return $this->textAlign;
	}
	
	/**
	 * Fonction qui retourne l'alignement vertical du texte
	 *
	 * @access 	public
	 * @return 	string									L'alignement vertical du texte
	 */
	public function getVerticalAlign() {
		return $this->verticalAlign;
	}
	
	/**
	 * Fonction qui retourne la couleur du texte
	 *
	 * @access 	public
	 * @return 	string									La couleur du texte
	 */
	public function getColor() {
		return $this->color;
	}
	
	/**
	 * Fonction qui retourne le nombre de lignes �fusionner depuis la cellule (cellule courante comprise)
	 *
	 * @access 	public
	 * @return 	integer									Le nombre de lignes �fusionner depuis la cellule
	 */
	public function getSpannedRows() {
		return $this->spannedRows;
	}
	
	/**
	 * Fonction qui retourne le nombre de lignes �fusionner depuis la cellule (cellule courante comprise)
	 *
	 * @access 	public
	 * @return 	integer									Le nombre de colonnes �fusionner depuis la cellule
	 */
	public function getSpannedCols() {
		return $this->spannedCols;
	}
	
	/**
	 * @access 	public
	 * @return 	integer									
	 */
	public function getDecimal() {
		return $this->decimal;
	}
	
	/**
	 * @access 	public
	 * @return 	string						
	 */
	public function getFormula() {
		return $this->formula;
	}
	
}


