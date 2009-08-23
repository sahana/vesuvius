<?php

require_once ('XMLElement.abstract.php');
require_once ('Fonction.class.php');


class Picture extends XMLElement {
	

	/**
	 * @access 	protected
	 * @var 	string			$picturePath		
	 */
	protected $picturePath;
	
	/**
	 * @access 	protected
	 * @var 	TableCell		$cellAddress		
	 */
	protected $cellAddress;
	
	/**
	 * @access 	protected
	 * @var 	string			$sheetAddress		
	 */
	protected $sheetAddress;
	
	/**
	 * @access 	protected
	 * @var 	float			$xEnd				
	 */
	protected $xEnd;
	
	/**
	 * @access 	protected
	 * @var 	float			$yEnd				
	 */
	protected $yEnd;
	
	/**
	 * @access 	protected
	 * @var 	integer			$zIndex			
	 */
	protected $zIndex;
	
	/**
	 * @access 	protected
	 * @var 	string			$name			
	 */
	protected $name;
	
	/**
	 * @access 	protected
	 * @var 	string			$style			
	 */
	protected $style;
	
	/**
	 * @access 	protected
	 * @var 	string			$textStyle		
	 */
	protected $textStyle;
	
	/**
	 * @access 	protected
	 * @var 	float			$width		
	 */
	protected $width;
	
	/**
	 * @access 	protected
	 * @var 	float			$height		
	 */
	protected $height;
	
	/**
	 * @access 	protected
	 * @var 	float			$svgx			
	 */
	protected $svgx;
	
	/**
	 * @access 	protected
	 * @var 	float			$svgy			
	 */
	protected $svgy;
	
	/**
	 * @access 	protected
	 * @var 	string			$type		
	 */
	protected $type;
	
	/**
	 * @access 	protected
	 * @var 	string			$show			
	 */
	protected $show;
	
	/**
	 * @access 	protected
	 * @var 	string			$actuate			
	 */
	protected $actuate;

	/**
	 * Constructeur qui load une Picture
	 *
	 * @access 	public
	 * @param 	object			$core				
	 * @param 	object			$xpath			
	 * @param 	string			$picture_path		
	 * @param 	string			$sheet_name			
	 * @return 	object			
	 */
	public function __construct($core = '', $xpath = '', $picture_path = '', $sheet_name = '') {
		if ($core && $xpath) {
			$this->load('picture', $core, $xpath);
			$this->root = $xpath->query('//office:spreadsheet')->item(0);
			$path = explode('/', Fonction::removeLastSlash($picture_path));
			
			$name = array_pop($path);
			//$path = (count($path) == 0) ? $path = '' : implode('/', $path); //comment
			
			$this->picturePath = implode('/', $path);

			$this->name = $name;
			$this->sheetAddress = $sheet_name;
			$this->type = 'simple';
			$this->show = 'embed';
			$this->actuate = 'onLoad';
			
			$this->type = 'image/gif';
			$this->zIndex = 0;
		}
	}
		
	/**
	 * @access 	public
	 * @param 	float			$x					
	 * @param 	float			$y				
	 * @return 	void
	 */
	public function setSVG($x, $y) {
		$this->setSVGX($x);
		$this->setSVGY($y);
	}
	
	/**
	 * @access 	public
	 * @param 	float			$width			
	 * @param 	float			$heigh				
	 * @return 	void
	 */
	public function setSize($width, $height) {
		$this->setWidth($width);
		$this->setHeight($height);
	}
	
	/**
	 * @access 	public
	 * @param 	float			$x_end			
	 * @param 	float			$y_end			
	 * @param 	TableCell		$cell		
	 * @return 	void
	 */
	public function setBottomRightCorner($x_end, $y_end, $cell) {
		$this->setCellAddress($cell);
		$this->setXEnd($x_end);
		$this->setYEnd($y_end);
	}
	
	/**
	 * @access 	public
	 * @return 	string		
	 */
	public function getPathName() {
		if ($this->picturePath == '') {
			return $this->getName();	
		} else {
			return $this->getPath().'/'.$this->getName();	
		}
	}
	
	/**
	 * @access 	public
	 * @param 	string			$actuate			
	 * @return 	void
	 */
	public function setActuate($actuate) {
		$this->actuate = $actuate;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$show				
	 * @return 	void
	 */
	public function setShow($show) {
		$this->show = $show;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$type	
	 * @return 	void
	 */
	public function setType($type) {
		$this->type = $type;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$style		
	 * @return 	void
	 */
	public function setTextStyle($style) {
		$this->textStyle = $style;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$style		
	 * @return 	void
	 */
	public function setStyle($style) {
		$this->style = $style;
	}
	
	/**
	 * @access 	public
	 * @param 	string			$name			
	 * @return 	void
	 */
	public function setName($name) {
		$this->name = $name;
	}
	
	/**
	 * @access 	public
	 * @param 	integer			$index		
	 * @return 	void
	 */
	public function setZIndex($index) {
		$this->zIndex = $index;
	}
	
	/**
	 * @access 	public
	 * @return 	TableCell		$style			
	 */
	public function getCellAddress() {
		$cell = $this->cellAddress;
		$l = Fonction::getLetters(true);
		return $this->sheetAddress.'.'.$l[$cell->getX()].$cell->getY();
	}
	
	/**
	 * @access 	public
	 * @return 	string			
	 */
	public function getActuate() {
		return $this->actuate;
	}
	
	/**
	 * @access 	public
	 * @return 	string					
	 */
	public function getShow() {
		return $this->show;
	}
	
	/**
	 * @access 	public
	 * @return 	string				
	 */
	public function getType() {
		return $this->type;
	}
	
	/**
	 * @access 	public
	 * @return 	float				
	 */
	public function getSVGX() {
		return $this->svgx;
	}
	
	/**
	 * @access 	public
	 * @return 	float				
	 */
	public function getSVGY() {
		return $this->svgy;
	}
	
	/**
	 * @access 	public
	 * @return 	float					
	 */
	public function getWidth() {
		return $this->width;
	}
	
	/**
	 * @access 	public
	 * @return 	float							
	 */
	public function getHeight() {
		return $this->height;
	}
	
	/**
	 * @access 	public
	 * @return 	string				
	 */
	public function getTextStyle() {
		return $this->textStyle;
	}
	
	/**
	 * @access 	public
	 * @return 	string			
	 */
	public function getStyle() {
		return $this->style;
	}
	
	/**
	 * @access 	public
	 * @return 	string				
	 */
	public function getName() {
		return $this->name;
	}
	
	/**
	 * @access 	public
	 * @return 	integer						
	 */
	public function getZIndex() {
		return $this->zIndex;
	}
	
	/**
	 * @access 	public
	 * @return 	float			
	 */
	public function getXEnd() {
		return $this->xEnd;
	}
	
	/**
	 * @access 	public
	 * @return 	float					
	 */
	public function getYEnd() {
		return $this->yEnd;
	}
	
	/**
	 * @access 	public
	 * @return 	string			
	 */
	public function getPath() {
		return $this->picturePath;
	}
	
	
	/**
	 * @access 	protected
	 * @param 	TableCell		$cell		
	 * @return 	void
	 */
	protected function setCellAddress($cell) {
		$this->cellAddress = $cell;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$x		
	 * @return 	void
	 */
	protected function setSVGX($x) {
		$this->svgx = $x;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$y			
	 * @return 	void
	 */
	protected function setSVGY($y) {
		$this->svgy = $y;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$width			
	 * @return 	void
	 */
	protected function setWidth($width) {
		$this->width = $width;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$height			
	 * @return 	void
	 */
	protected function setHeight($height) {
		$this->height = $height;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$x				
	 * @return 	void
	 */
	protected function setXEnd($x) {
		$this->xEnd = $x;
	}
	
	/**
	 * @access 	protected
	 * @param 	float			$y		
	 * @return 	void
	 */
	protected function setYEnd($y) {
		$this->yEnd = $y;
	}
	
}


