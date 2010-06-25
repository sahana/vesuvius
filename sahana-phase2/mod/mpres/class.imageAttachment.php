<?php
/**
* @package      imageAttachment
* @version      1.1
* @author       Greg Miernicki <g@miernicki.com> <miernickig@mail.nih.gov>
* LastModified: 2010:0510
* License:      LGPL
* @link         http://www.nlm.nih.gov/
*/

class imageAttachment {

	/**
	* todo descriptions
	* @var	string
	* var boolean,array
	*/

	public $filename;
	public $fileContent;
	public $height;
	public $width;
	public $type;
	public $url; 
	public $url_thumb;
	public $original_filename;

	/**
	* Constructor:
	*/
	public function __construct($filename, $fileContent, $height, $width, $type, $url, $url_thumb, $original_filename) {
		$this->filename          = $filename;
		$this->fileContent       = $fileContent;
		$this->height            = $height;
		$this->width             = $width;
		$this->type              = $type;
		$this->url               = $url;
		$this->url_thumb         = $url_thumb;
		$this->original_filename = $original_filename;
	}


	/**
	* Destructor
	*/
	public function __destruct() {
		$this->filename          = NULL;
		$this->fileContent       = NULL;
		$this->height            = NULL;
		$this->width             = NULL;
		$this->type              = NULL;
		$this->url               = NULL;
		$this->url_thumb         = NULL;
		$this->original_filename = NULL;
	}


	/**
	* Debug
	*/
	public function debug() {
		echo "\nfilename>>".$this->filename."<<";
		echo "\nheight>>".$this->height."<<";
		echo "\nwidth>>".$this->width."<<";
		echo "\ntype>>".$this->type."<<";
		echo "\nurl>>".$this->url."<<";
		echo "\nurl_thumb>>".$this->url_thumb."<<";
		echo "\noriginal_filename>>".$this->original_filename."<<\n";
	}
}


