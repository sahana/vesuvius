<?php

require_once ('XMLDocument.abstract.php');
require_once ('Fonction.class.php');
require_once ('Table.class.php');

class Content extends XMLDocument {

	/**
	 * @access 	protected
	 * @var 	array			$sheets	
	 */
	protected $sheets;
	
	/**
	 * @access 	protected
	 * @var		object			$parent	
	 */
	protected $parent;
	/**
	 * @access 	public
	 * @param 	object			$parent				
	 * @param 	string			$path_save			
	 * @param 	string			$path_templates		
	 * @param 	boolean			$format_output		
	 * @param 	boolean			$white_space			
	 * @return 	object									
	 */
	public function __construct($parent, $path_save, $path_templates, $format_output, $white_space) {
		try {
			$fileName = 'content.xml';
			$this->load($fileName, $path_save, $path_templates, $format_output, $white_space);
			$this->root = $this->core->documentElement;
			$this->parent = $parent;
			$this->sheets = array();
		} catch (Exception $e) {
			throw $e;	
		}
	}	
	
	/**
	 * @access 	public
	 * @param 	string			$sheet				
	 * @return 	object								
	 */
	public function addSheet($sheet) {
		try {
			$obj = new Table($sheet, $this->core, $this->xpath);
			$this->sheets[] = $obj;
			return $obj;
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$sheet					
	 * @param 	boolean			$solo_no_array		
	 * @return 	array								
	 */
	public function getSheetsByName($name, $solo_no_array = false) {
		$tab = array();
		foreach ($this->sheets as $sheet) {
			if ($sheet->getName() == $name)
				$tab[] = $sheet;
		}
		if ($solo_no_array) {
			if (count($tab) == 1)
				return $tab[0];
		}
		return $tab;
	}
	
	/**
	 * @access 	public
	 * @param 	integer			$index				
	 * @return 	object								
	 */
	public function getSheetByIndex($index) {
		return (isset($this->sheet[$index])) ? $this->sheet[$index] : false;
	}
	
	/**
	 * @access 	protected
	 * @return 	boolean							
	 */
	protected function _beforeSave() {
		$styles = array(
			'col' => array(), 'colused' => array(),
			'row' => array(), 'rowused' => array(),
			'cel' => array(), 'celused' => array(),
			'gra' => array(), 'graused' => array(),
			'leg' => array(), 'legused' => array(),
			'tab' => array(), 'tabused' => array(),
			'num' => array(), 'numused' => array()
		);
		$sheetsCols = array();
		$fonts = array();
		$maxCol = 0;
		$colDef = 'co1';
		foreach ($this->sheets as $key => $sheet){
			$cells = $sheet->getCells();
			$cols = array();

			foreach ($cells as $row => $obj) {
				foreach ($obj as $col => $cell) {
					$used = $this->_getUsedCellStyles($cell, $styles);
					$cell->setStyleName($used);
					$fonts[] = $cell->getFontFamily();
					if (!isset($cols[$col]) || $cols[$col] == '' || ($used['col'] != $colDef))
						$cols[$col] = $used['col'];
				}
			}
			if ($maxCol < $sheet->getNbColsMax()) {
				$maxCol = $sheet->getNbColsMax();
			}
			$sheetsCols[$key] = Fonction::array_count_followed_values($cols, $colDef, $maxCol);

			foreach ($sheet->getPictures() as $pict) {
				$used = $this->_getUsedGraphStyles($pict, $styles);
				$pict->setStyle = $used['gra'];
				$pict->setTextStyle = $used['text'];
			}
		}
		$this->_insertFontFamilies($fonts);
		$this->_insertStyles($styles);

		foreach ($this->sheets as $key => $sheet){
			$cells = $sheet->getCells();
			foreach ($sheetsCols[$key] as $col) {
				$tbCol = $this->_addTableElement('table-column', null, $sheet->getXML());
				$tbCol->setAttribute('table:style-name', $col['value']);
				if ($col['nb'] > 1)
					$tbCol->setAttribute('table:number-columns-repeated', $col['nb']);
			}
			$rowCourant = 0;
			ksort($cells);

			foreach ($cells as $row => $obj) {
				ksort($obj);
				$cell = current($obj);
				$st = $cell->getStyleName();
				if ($rowCourant < $row - 1) {
					$tbRow = $this->_addTableElement('table-row', null, $sheet->getXML());
					$tbRow->setAttribute('table:number-rows-repeated', ($row - $rowCourant - 1));
					$tbCell = $this->_addTableElement('table-cell', null, $tbRow);
					$tbCell->setAttribute('table:style-name', 'ce1');
				}
				$tbRow = $this->_addTableElement('table-row', null, $sheet->getXML());
				$tbRow->setAttribute('table:style-name', $st['row']);
				$colCourant = 0;
				foreach ($obj as $col => $cell) {
					$st = $cell->getStyleName();

					if ($colCourant < $col - 1) {
						$tbCell = $this->_addTableElement('table-cell', null, $tbRow);
						$tbCell->setAttribute('table:number-columns-repeated', ($col - $colCourant - 1));
					}
					
					$tbCell = $this->_addTableElement('table-cell', null, $tbRow);
					$tbCell->setAttribute('table:style-name', $st['cel']);
					if ($cell->getFormula() != '') {
						$tbCell->setAttribute('table:formula', 'oooc:'.$cell->getFormula());
					}
					if ($cell->getSpannedRows() > 1) {
						$tbCell->setAttribute('table:number-rows-spanned', $cell->getSpannedRows());
					}
					if ($cell->getSpannedCols() > 1) {
						$tbCell->setAttribute('table:number-columns-spanned', $cell->getSpannedCols());
					}
					if ($cell->getType() == 'float') {
						$tbCell->setAttribute('office:value-type', $cell->getType());
						$tbCell->setAttribute('office:value', $cell->getContent());
					}
					if ($cell->getContent() != '') {
						$content = $this->_addTextElement('p', $cell->getContent(), $tbCell);
					}
					$colCourant = $col;
				}
				$rowCourant = $row;
			}

			foreach ($sheet->getPictures() as $pict) {
				//copy($pict->getPathName(), $this->pathSave.'/Pictures/'.$pict->getName());
				
				copy($pict->getPathName(), $this->pathSave.'/Pictures/'.$pict->getName());
				
		
				//copy('/home/sanjeewa/public_html/sahana-phase2/mod/rs/S4010230.JPG', $this->pathSave.'/Pictures/'.$pict->getName());

				$this->parent->manifest->addFileEntry($pict->getType(), 'Pictures/'.$pict->getName());

				$tbFrame = $this->_addDrawElement('frame', null, $tbCell);
				$tbFrame->setAttribute('table:end-cell-address', Fonction::checkAttribute($pict->getCellAddress()));
				$tbFrame->setAttribute('table:end-x', $pict->getXEnd());
				$tbFrame->setAttribute('table:end-y', $pict->getYEnd());
				$tbFrame->setAttribute('draw:z-index', $pict->getZIndex());
				$tbFrame->setAttribute('draw:name', Fonction::checkAttribute($pict->getName()));
				$tbFrame->setAttribute('draw:style-name', $pict->getStyle());
				$tbFrame->setAttribute('draw:text-style-name', $pict->getTextStyle());
				$tbFrame->setAttribute('svg:width', $pict->getWidth());
				$tbFrame->setAttribute('svg:height', $pict->getHeight());
				$tbFrame->setAttribute('svg:x', $pict->getSVGX());
				$tbFrame->setAttribute('svg:y', $pict->getSVGY());

				$tbImage = $this->_addDrawElement('image', null, $tbFrame);
				$tbImage->setAttribute('xlink:href', $pict->getPath().'/'.$pict->getName()); //Fonction::checkAttribute($pict->getPath())
				$tbImage->setAttribute('xlink:type', $pict->getType());
				$tbImage->setAttribute('xlink:show', $pict->getShow());
				$tbImage->setAttribute('xlink:actuate', $pict->getActuate());
			}	
		}
		return true;		
	}

	
	/**
	 * @access 	protected
	 * @param 	array			$fonts	
	 * @return 	void
	 */
	protected function _insertFontFamilies($fonts) {
		$fontFace = $this->xpath->query('//office:font-face-decls')->item(0);
		$fonts = array_unique($fonts);
		foreach ($fonts as $font) {
			$style = $this->_addStyleElement('font-face', '', $fontFace);
			$style->setAttribute('style:name', $font);
			$style->setAttribute('svg:font-family', $font);
		}
	}
	
	/**
	 * @access 	protected
	 * @param 	array			$styles	
	 * @return	void
	 */
	protected function _insertStyles($styles) {
		$automaticStyles = $this->xpath->query('//office:automatic-styles')->item(0);
		foreach ($styles['cel'] as $elem) {
			$t = null; $s = null; $p = null; $n = null; $ns = null;
			$style = $this->_addStyleElement('style', null, $automaticStyles);
			$style->setAttribute('style:name', $elem['name']);
			$style->setAttribute('style:family', 'table-cell');
			$style->setAttribute('style:parent-style-name', 'Defaut');
			if ($elem['backgroundColor'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('fo:background-color', $elem['backgroundColor']);
			}
			if ($elem['borderTop'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('fo:border-top', $elem['borderTop']);
			}
			if ($elem['borderLeft'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('fo:border-left', $elem['borderLeft']);
			}
			if ($elem['borderBottom'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('fo:border-bottom', $elem['borderBottom']);
			}
			if ($elem['borderRight'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('fo:border-right', $elem['borderRight']);
			}
			if ($elem['fontStyle'] != '') {
				$t = (!$t) ? $this->_addStyleElement('text-properties', null, $style) : $t;
				$t->setAttribute('fo:font-style', $elem['fontStyle']);
			}
			if ($elem['fontSize'] != '') {
				$t = (!$t) ? $this->_addStyleElement('text-properties', null, $style) : $t;
				$t->setAttribute('fo:font-size', $elem['fontSize']);
			}
			if ($elem['fontFamily'] != '') {
				$t = (!$t) ? $this->_addStyleElement('text-properties', null, $style) : $t;
				$t->setAttribute('style:font-name', $elem['fontFamily']);
			}
			if ($elem['fontWeight'] != '') {
				$t = (!$t) ? $this->_addStyleElement('text-properties', null, $style) : $t;
				$t->setAttribute('fo:font-weight', $elem['fontWeight']);
			}
			if ($elem['color'] != '') {
				$t = (!$t) ? $this->_addStyleElement('text-properties', null, $style) : $t;
				$t->setAttribute('fo:color', $elem['color']);
			}
			if ($elem['textAlign'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('style:text-align-source', 'fix');
				$s->setAttribute('style:repeat-content', 'false');
				$p = (!$p) ? $this->_addStyleElement('paragraph-properties', null, $style) : $p;
				$p->setAttribute('fo:text-align', $elem['textAlign']);
			}
			if ($elem['verticalAlign'] != '') {
				$s = (!$s) ? $this->_addStyleElement('table-cell-properties', null, $style) : $s;
				$s->setAttribute('style:vertical-align', $elem['verticalAlign']);
			}
			if ($elem['decimal'] != '') {
				$ns = (!$ns) ? $this->_addNumberElement('number-style', null, $automaticStyles) : $ns;
				$n = (!$n) ? $this->_addNumberElement('number', null, $ns) : $n;
				$ns->setAttribute('style:name', $elem['decimal']['pos']);
				$n->setAttribute('number:decimal-places', $elem['decimal']['val']);
				$n->setAttribute('number:min-integer-digits', 1);
				$style->setAttribute('style:data-style-name', $elem['decimal']['pos']);
			}
		}
		foreach ($styles['col'] as $elem) {
			$style = $this->_addStyleElement('style', null, $automaticStyles);
			$style->setAttribute('style:name', $elem['name']);
			$style->setAttribute('style:family', 'table-column');
			$tbCol = $this->_addStyleElement('table-column-properties', null, $style);
			if ($elem['width']) {
				$tbCol->setAttribute('fo:break-before', 'auto');
				$tbCol->setAttribute('style:column-width', $elem['width']);
			}
		}
		foreach ($styles['row'] as $elem) {
			$style = $this->_addStyleElement('style', null, $automaticStyles);
			$style->setAttribute('style:name', $elem['name']);
			$style->setAttribute('style:family', 'table-row');
			$tbRow = $this->_addStyleElement('table-row-properties', null, $style);
			if ($elem['height']) {
				$tbRow->setAttribute('style:row-height', $elem['height']);
				$tbRow->setAttribute('fo:break-before', 'auto');
				$tbRow->setAttribute('style:use-optimal-row-height', 'false');
			}
		}
		foreach ($styles['gra'] as $elem) {
			$style = $this->_addStyleElement('style', null, $automaticStyles);
			$style->setAttribute('style:name', $elem['name']);
			$style->setAttribute('style:family', 'graphic');
			$tbGra = $this->_addStyleElement('graphic-properties', null, $style);
		
			$tbGra->setAttribute('draw:stroke', 'none');
			$tbGra->setAttribute('draw:fill', 'none');
			$tbGra->setAttribute('draw:textarea-horizontal-align', 'center');
			$tbGra->setAttribute('draw:textarea-vertical-align', 'middle');
			$tbGra->setAttribute('draw:color-mode', 'standard');
			$tbGra->setAttribute('draw:luminance', '0%');
			$tbGra->setAttribute('draw:contrast', '0%');
			$tbGra->setAttribute('draw:gamma', '100%');
			$tbGra->setAttribute('draw:red', '0%');
			$tbGra->setAttribute('draw:green', '0%');
			$tbGra->setAttribute('draw:blue', '0%');
			$tbGra->setAttribute('fo:clip', 'rect(0cm 0cm 0cm 0cm)');
			$tbGra->setAttribute('draw:image-opacity', '100%');
			$tbGra->setAttribute('style:mirror', 'none');
			
			$style = $this->_addStyleElement('style', null, $automaticStyles);
			$style->setAttribute('style:name', 'P1');
			$style->setAttribute('style:family', 'paragraph');
			$tbP = $this->_addStyleElement('paragraph-properties', null, $style);
			$tbGra->setAttribute('fo:text-align', 'center');
		}
	}
	
	/**

	 * @access 	protected
	 * @param 	Picture			$cell				
	 * @param 	array			$styles					
	 * @return	array									
	 */
	protected function _getUsedGraphStyles(Picture $pict, &$styles) {
		// Styles relatifs aux cellules (+2 parce qu'on commence au style ce2)
		$str = '';
		$used['gra'] = 'gr1';
		$used['text'] = 'P1';
		return $used;
	}
	
	/**

	 * @access 	protected
	 * @param 	TableCell		$cell					
	 * @param 	array			$styles					
	 * @return	array									
	 */
	protected function _getUsedCellStyles($cell, &$styles) {
		// Styles relatifs aux cellules (+2 parce qu'on commence au style ce2)
		$strdecimal = '';
		$str = '';
		$str .= ($cell->getBackgroundColor()) ? $cell->getBackgroundColor() : '';
		$str .= ($cell->getBorderBottom()) ? $cell->getBorderBottom() : '';
		$str .= ($cell->getBorderLeft()) ? $cell->getBorderLeft() : '';
		$str .= ($cell->getBorderRight()) ? $cell->getBorderRight() : '';
		$str .= ($cell->getBorderTop()) ? $cell->getBorderTop() : '';
		$str .= ($cell->getFontStyle()) ? $cell->getFontStyle() : '';
		$str .= ($cell->getFontSize()) ? $cell->getFontSize() : '';
		$str .= ($cell->getFontFamily()) ? $cell->getFontFamily() : '';
		$str .= ($cell->getFontWeight()) ? $cell->getFontWeight() : '';
		$str .= ($cell->getTextAlign()) ? $cell->getTextAlign() : '';
		$str .= ($cell->getVerticalAlign()) ? $cell->getVerticalAlign() : '';
		$str .= ($cell->getColor()) ? $cell->getColor() : '';
		$str .= ($cell->getDecimal()) ? $cell->getDecimal() : '';
		if ($cell->getDecimal() && !in_array($cell->getDecimal(), $styles['numused'])) {
			$styles['numused'][] = $cell->getDecimal();
			$strdecimal = array('val' => $cell->getDecimal(), 'pos' => 'N'.count($styles['numused']));
		}
		if (!in_array($str, $styles['celused']) && $str != '') {
			$used['cel'] = 'ce'.(count($styles['cel']) + 2);
			$styles['celused'][] = $str;
			$styles['cel'][] = array(
				'name' => $used['cel'],
				'backgroundColor' => $cell->getBackgroundColor(),
				'borderBottom' => $cell->getBorderBottom(),
				'borderLeft' => $cell->getBorderLeft(),
				'borderRight' => $cell->getBorderRight(),
				'borderTop' => $cell->getBorderTop(),
				'color' => $cell->getColor(),
				'fontStyle' => $cell->getFontStyle(),
				'fontSize' => $cell->getFontSize(),
				'fontFamily' => $cell->getFontFamily(),
				'fontWeight' => $cell->getFontWeight(),
				'textAlign' => $cell->getTextAlign(),
				'verticalAlign' => $cell->getVerticalAlign(),
				'decimal' => $strdecimal
			);
		} else {
			$used['cel'] = ($str != '') ? 'ce'.(array_search($str, $styles['celused']) + 2) : 'ce1';
		}
		// Styles relatifs aux lignes (+2 parce qu'on commence au style ro2)
		$str = '';
		$str .= ($cell->getHeight()) ? $cell->getHeight() :	'';
		if (!in_array($str, $styles['rowused']) && $str != '') {
			$used['row'] = 'ro'.(count($styles['row']) + 2);
			$styles['rowused'][] = $str;
			$styles['row'][] = array(
				'name' => $used['row'],
				'height' => $cell->getHeight()
			);
		} else {
			$used['row'] = ($str != '') ? 'ro'.(array_search($str, $styles['rowused']) + 2) : 'ro1';
		}
		// Styles relatifs aux colonnes (+2 parce qu'on commence au style co2)
		$str = '';
		$str .= ($cell->getWidth()) ? $cell->getWidth() : '';
		if (!in_array($str, $styles['colused']) && $str != '') {
			$used['col'] = 'co'.(count($styles['col']) + 2);
			$styles['colused'][] = $str;
			$styles['col'][] = array(
				'name' => $used['col'],
				'width' => $cell->getWidth()
			);
		} else {
			$used['col'] = ($str != '') ? 'co'.(array_search($str, $styles['colused']) + 2) : 'co1';
		}
		return $used;
	}
	
	/**

	 * @access 	protected
	 * @param 	string			$element				
	 * @param 	string			$str					
	 * @param 	object			$parent				
	 * @return 	object									
	 */
	protected function _addTableElement($element, $str = null, $parent = null) {
		try {
			return $this->_addElement('table', $element, $str, $parent);
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**

	 * @access 	protected
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent				
	 * @return 	object								
	 */
	protected function _addStyleElement($element, $str = null, $parent = null) {
		try {
			return $this->_addElement('style', $element, $str, $parent);
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent			
	 * @return 	object								
	 */
	protected function _addTextElement($element, $str = null, $parent = null) {
		try {
			return $this->_addElement('text', $element, $str, $parent);
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$element			
	 * @param 	string			$str				
	 * @param 	object			$parent					
	 * @return 	object									
	 */
	protected function _addNumberElement($element, $str = null, $parent = null) {
		try {
			return $this->_addElement('number', $element, $str, $parent);
		} catch (Exception $e) {
			throw $e;	
		}
	}
	
	/**
	 * @access 	protected
	 * @param 	string			$element				
	 * @param 	string			$str					
	 * @param 	object			$parent				
	 * @return 	object									
	 */
	protected function _addDrawElement($element, $str = null, $parent = null) {
		try {
			return $this->_addElement('draw', $element, $str, $parent);
		} catch (Exception $e) {
			throw $e;	
		}
	}

}


