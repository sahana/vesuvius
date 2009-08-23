<?php

require_once ('XMLElement.abstract.php');
require_once ('Fonction.class.php');
require_once ('TableCell.class.php');
require_once ('Picture.class.php');

class Table extends XMLElement {

	/**
	 * @access 	protected
	 * @var 	string			$sheetName	
	 */
	protected $sheetName;
	
	/**
	 * @access 	protected
	 * @var 	object			$obj	
	 */
	protected $obj;
	
	/**
	 * @access 	protected
	 * @var 	array			$cells
	 */
	protected $cells;
	
	/**
	 * @access 	protected
	 * @var 	array			$pictures	
	 */
	protected $pictures;

	/**
	 * @access 	public
	 * @param 	string			$sheet			
	 * @param 	object			$core			
	 * @param 	object			$xpath				
	 * @return 	object					
	 */
	public function __construct($sheet = '', $core = '', $xpath = '') {
		if ($sheet && $core && $xpath) {
			$this->load('calc-table', $core, $xpath);
			$this->cells = array();
			$this->pictures = array();
			$this->sheetName = $sheet;
			$this->root = $xpath->query('//office:spreadsheet')->item(0);
			$this->obj = $this->_addElement('table', 'table');
			$this->obj->setAttribute('table:name', Fonction::checkAttribute($this->sheetName));
		}
	}

	/**
	 * @access 	public
	 * @param 	string			$img			
	 * @return 	Picture				
	 */
	public function addPicture($img) {
		//echo "in the add picture function";
		$_sd_path = str_replace('\\', '/', dirname(__FILE__));
		
		$_sd_path = explode('/', dirname(__FILE__));
		array_pop($_sd_path);

		array_pop($_sd_path);
		array_pop($_sd_path);
		$_sd_path = implode('/', $_sd_path);
		$_sd_path = $_sd_path."/www/tmp/Pictures/";
	
		$pict = new Picture($this->core, $this->xpath, $_sd_path.$img, $this->sheetName);
		$this->pictures[] = $pict;
		return $pict;
	}
	
	/**
	 * @access 	public
	 * @param 	integer			$x					
	 * @param 	integer			$y				
	 * @return 	object			
	 */
	public function getCell($x, $y) {
		if (is_object($x) || is_object($y)) {
			return false;	
		}
		if (isset($this->cells[$y])){
			if (isset($this->cells[$y][$x]))
				return $this->cells[$y][$x];
		}

		$cell = new TableCell($this, $this->core, $this->xpath);
		$cell->setPos($x, $y);
		$this->cells[$y][$x] = $cell;		
		return $cell;
	}
	
	/**
	 * @access 	public
	 * @param 	integer|object	$x				
	 * @param 	integer|object	$y			
	 * @param 	string			$func		
	 * @param 	string|array	$data			
	 * @param 	string|array	$dataRef			
	 * @return 	array						
	 */
	public function getRangeCells($x, $y, $func = '', $data = '', &$dataRef = '') {
		$cells = array();
		if (is_object($x) && is_object($y)) {
			$xdep = $x->getX(); $xfin = $y->getX();
			$ydep = $x->getY(); $yfin = $y->getY();
			for ($yc = $ydep; $yc <= $yfin; $yc++) {
				for ($xc = $xdep; $xc <= $xfin; $xc++) {
					$cell = $this->getCell($xc, $yc);
					$cells[] = $cell;
					if ($func)
						$this->$func($cell, $xc, $yc, $xdep, $ydep, $xfin, $yfin, $data, $dataRef);
				}
			}
		} else {
			$cell = $this->getCell($x, $y);
			$cells[] = $cell;
			if ($func)
				$this->$func($cell, $x, $y, $x, $y, $x, $y, $data, $dataRef);
		}
		return $cells;
	}
	
	/**
	 * @access 	public
	 * @return 	integer				
	 */
	public function getNbRowsMax() {
		$maximum = 0;
		foreach ($this->cells as $row => $obj) {
			foreach ($obj as $col => $cell) {
				$spanned = $cell->getSpannedRows();
				if ($maximum < $row + $spanned)
					$maximum = $row + $spanned;
			}	
		}
		return $maximum;
	}
	
	/**

	 * @access 	public
	 * @return 	integer					
	 */
	public function getNbColsMax() {
		$maximum = 0;
		foreach ($this->cells as $row => $obj) {
			foreach ($obj as $col => $cell) {
				$spanned = $cell->getSpannedCols();
				if ($maximum < $col + $spanned)
					$maximum = $col + $spanned;
			}	
		}
		return $maximum;
	}
	
	/**
	 * @access 	public
	 * @param 	integer			$col				
	 * @return 	string					
	 */
	public function getColumnName($col) {
		$lettres = Fonction::getLetters(true);
		if (isset($lettres[$col]))
			return $lettres[$col];
		else 
			return 0;	
	}
	
	/**
	 * @access 	public
	 * @param 	string			$contenu			
	 * @param 	integer			$x				
	 * @param 	integer			$y					
	 * @return 	void
	 */
	public function setFormulaSUM($contenu, $x, $y) {
		$cell = $this->getCell($x, $y);
		$this->cells[$y][$x]->setFormulaSUM($contenu);
	}
	
	/**
	 * @access 	public
	 * @param 	string			$contenu			
	 * @param 	integer|object	$x				
	 * @param 	integer|object	$y				
	 * @return 	void
	 */
	public function setCellContent($contenu, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setContent($contenu);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$couleur			
	 * @param 	integer|object	$x			
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellBackgroundColor($couleur, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setBackgroundColor($couleur);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data	
	 * @param 	integer|object	$x		
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellColor($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setColor($data);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data	
	 * @param 	integer|object	$x		
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellFontWeight($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setFontWeight($data);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data	
	 * @param 	integer|object	$x		
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellWidth($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setWidth($data);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data	
	 * @param 	integer|object	$x		
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellHeight($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setHeight($data);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data		
	 * @param 	integer|object	$x			
	 * @param 	integer|object	$y		
	 * @return 	void
	 */
	public function setCellBorder($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y);
		foreach ($cells as $cell) {
			$cell->setBorder($data);
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$data			
	 * @param 	integer|object	$x				
	 * @param 	integer|object	$y				
	 * @return 	void
	 */
	public function setCellBorderAround($data, $x, $y) {
		$cells = $this->getRangeCells($x, $y, '_setCellBorderAround', $data);
	}

	
	/**
	 * @access 	public
	 * @return 	string				
	 */
	public function getName() {
		return $this->sheetName;	
	}
	
	/**
	 * @access 	public
	 * @return 	array					
	 */
	public function getCells() {
		return $this->cells;	
	}
	
	/**
	 * @access 	public
	 * @return 	array						
	 */
	public function getXML() {
		return $this->obj;	
	}
	
	/**
	 * @access 	public
	 * @return 	array			
	 */
	public function getPictures() {
		return $this->pictures;	
	}
		
	/**
	 * @access 	protected
	 * @param 	object			$cell					
	 * @param 	integer			$x						
	 * @param 	integer			$y						
	 * @param 	integer			$xdep					
	 * @param 	integer			$ydep					
	 * @param 	integer			$xfin					
	 * @param 	integer			$yfin					
	 * @param 	string|array	$data					
	 * @param 	string|array	$dataRef		
	 * @return 	void
	 */
	protected function _setCellBorderAround($cell, $x, $y, $xdep, $ydep, $xfin, $yfin, $data, &$dataRef) {
		if ($y == $ydep)
			$cell->setBorderTop($data);
		if ($x == $xdep)
			$cell->setBorderLeft($data);
		if ($y == $yfin)
			$cell->setBorderBottom($data);
		if ($x == $xfin)
			$cell->setBorderRight($data);
	}
	
	/**
	 * @access 	protected
	 * @param 	object			$cell				
	 * @param 	integer			$x					
	 * @param 	integer			$y					
	 * @param 	integer			$xdep				
	 * @param 	integer			$ydep				
	 * @param 	integer			$xfin				
	 * @param 	integer			$yfin				
	 * @param 	string|array	$data					
	 * @param 	string|array	$dataRef				
	 * @return 	void
	 */
	protected function _setSum($cell, $x, $y, $xdep, $ydep, $xfin, $yfin, $data, &$dataRef) {
		$dataRef += $cell->getContent() * 1;
	}
	
}


