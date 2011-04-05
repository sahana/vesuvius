<?php
/**
 * @name         MPR Email Service
 * @version      1.8
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0404
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


