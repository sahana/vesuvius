<?php

$_openoffice_path = str_replace('\\', '/', dirname(__FILE__));
$_openoffice_path = explode('/', $_openoffice_path);
array_pop($_openoffice_path);
$_openoffice_path = implode('/', $_openoffice_path);

define ('PATH_ROOT',$_openoffice_path.'/');
define ('PATH_CALC',PATH_ROOT.'');
define ('TEMPLATE_FILE_PATH_CALC',PATH_CALC.'templates/');
//define ('SAVE_FILE_PATH_CALC',PATH_CALC.'');


$_openoffice_path = explode('/', $_openoffice_path);
array_pop($_openoffice_path);
array_pop($_openoffice_path);
$_openoffice_path = implode('/', $_openoffice_path);
$_openoffice_path = $_openoffice_path."/www/tmp";

define ('SAVE_FILE_PATH_CALC',$_openoffice_path.'');

require_once ('EasyZIP.class.php');
require_once ('Fonction.class.php');
require_once ('Manifest.class.php');
require_once ('Meta.class.php');
require_once ('Settings.class.php');
require_once ('Styles.class.php');
require_once ('Content.class.php');


class OpenOfficeSpreadsheet {

	/**
	 * @access	public
	 * @var 	object $manifest 
	 */
	public $manifest;
	
	/**
	 * @access	public
	 * @var 	object			$meta		
	 */
	public $meta;
	
	/**
	 * @access	public
	 * @var 	object			$settings			
	 */
	public $settings;
	
	/**
	 * @access	public
	 * @var 	object			$styles			
	 */
	public $styles;
	
	/**
	 * @access	public
	 * @var 	object			$content			
	 */
	public $content;
	
	/**
	 * @access	protected
	 * @var 	string			$pathTemplates		
	 */
	protected $pathTemplates;
	
	/**
	 * @access	protected
	 * @var 	string			$pathSave		
	 */
	protected $pathSave;
	
	/**
	 * @access	protected
	 * @var 	string			$documentName		
	 */
	protected $documentName;
	
	/**
	 * @access	protected
	 * @var 	string			$extension			
	 */
	protected $extension;
	
	/**
	 * @access	protected
	 * @var 	string			$contentType		
	 */
	protected $contentType;
	
	/**
	 * @access	protected
	 * @var 	boolean			$keepGeneratedRep		
	 */
	protected $keepGeneratedRep;

	/**
	 * @access 	public
	 * @param 	string			$document_name			
	 * @param 	string			$path_save				
	 * @param 	string			$path_templates			
	 * @return 	object									
	 */
	public function __construct($document_name, $path_save = '', $path_templates = '') {
		$docSave                = $this->_setTempDirName();
		$path_templates         = ($path_templates == '') ? TEMPLATE_FILE_PATH_CALC : $path_templates;
		$path_save              = ($path_save == '') ? SAVE_FILE_PATH_CALC : $path_save;
		$this->extension        = 'ods';
		$this->contentType      = 'application/vnd.oasis.opendocument.spreadsheet';
		$this->keepGeneratedRep = false;
		
		$this->pathTemplates    = Fonction::removeLastSlash($path_templates);
		$this->pathSave         = Fonction::removeLastSlash($path_save).'/'.$docSave;
		$this->documentName     = Fonction::checkFileName($document_name, $this->extension);
		
		try {
			$this->manifest = new Manifest($this->pathSave.'/META-INF', $this->pathTemplates.'/META-INF', true, false);
			$this->meta     = new Meta($this->pathSave, $this->pathTemplates, true, false);
			$this->settings = new Settings($this->pathSave, $this->pathTemplates, true, false);
			$this->styles   = new Styles($this->pathSave, $this->pathTemplates, true, false);
			$this->content  = new Content($this, $this->pathSave, $this->pathTemplates, true, false);
		} catch (Exception $e) {
			echo '<br><b>Notice : </b>'.$e->getMessage().'<br>';
		}
	}

	/**
	 * @access 	public
	 * @param 	string			$sheet			
	 * @return 	object							
	 */
	public function addSheet($sheet) {
		return $this->content->addSheet($sheet);
	}
	
	/**
	 * @access 	public
	 * @param 	boolean			$in_file		
	 * @return 	object|boolean							
	 */
	public function save($in_file = true,$report_title='',$keyword='',$owner='',$report_id_in = '',$print_ok = '') 
		{
		$this->_saveFile();
		$zip = new EasyZIP();
		
		if ($handle = opendir($this->pathSave))
		{ 
			while (false !== ($filename = readdir($handle))) 
			{
				if ($filename != '.' && $filename != '..')
				{
					if (is_dir($this->pathSave.'/'.$filename))
						$zip->addDir($this->pathSave, $filename);
					else
						$zip->addFile($filename, $this->pathSave.'/');
				}
			}
			closedir($handle);
		}
		$fileName = ($in_file) ? $this->documentName : '';
		$result = $zip->zipFile($fileName,$report_title,$keyword,$owner,$report_id_in,$print_ok);

			Fonction::delDir($this->pathSave);

		return $result;
		}
	
	/**
	 * @access 	public
	 * @return 	void
	 */
	public function output() {
		header('Content-type: '.$this->contentType);
		header('Content-Disposition: attachment; filename='.$this->documentName);
		header('Cache-control: no-store, no-cache, must-revalidate');
		header('Pragma: no-cache');
		header('Last-Modified: '.gmdate('D, d M Y H:i:s').' GMT');
		header('Expires: 0');
		
		echo $this->save(false);
	}
	
	/**
	 * @access 	public
	 * @param 	string			$file		
	 * @param 	boolean			$xmp		
	 * @return 	string			
	 */
	public function saveXML($file = '', $xmp = false) {
		$xml = (!$xmp) ? '' : '<xmp>';
		switch ($file) {
			case 'manifest': $xml .= $this->manifest->saveXML(); break;
			case 'meta':     $xml .= $this->meta->saveXML();     break;
			case 'settings': $xml .= $this->settings->saveXML(); break;
			case 'styles':   $xml .= $this->styles->saveXML();   break;
			case 'content':  $xml .= $this->content->saveXML();  break;
			default:
				$xml .= $this->manifest->saveXML();	
				$xml .= $this->meta->saveXML();
				$xml .= $this->settings->saveXML();
				$xml .= $this->styles->saveXML();
				$xml .= $this->content->saveXML();
		}
		$xml .= (!$xmp) ? '' : '</xmp>';
		return $xml;
	}

	/**
	 * @access 	public
	 * @param 	boolean			$choix	
	 * @return 	void
	 */
	public function keepGeneratedDir($choix) {
		if ($choix)
			$this->keepGeneratedRep = true;
		else 
			$this->keepGeneratedRep = false;	
	}
	
	/**
	 * @access 	public
	 * @return 	string		 */
	public function getGeneratedDirName() {
		return $this->pathSave;	
	}
	
	/**
	 * @access 	public
	 * @return 	string							
	 */
	public function getTemplatesDirName() {
		return $this->pathTemplates;	
	}
	
	/**
	 * @access 	public
	 * @return 	string	*/
	public function getExtensionFile() {
		return $this->extension;	
	}
	
	/**
	 * @access 	public
	 * @return 	string	
	 */
	public function getContentTypeFile() {
		return $this->contentType;	
	}

	/**
	 * @access 	protected
	 * @return 	void
	 */
	protected function _saveFile() {
		if (!is_dir($this->pathSave))
			mkdir($this->pathSave, 0777);
		if (!is_dir($this->pathSave.'/Configurations2'))
			mkdir($this->pathSave.'/Configurations2', 0777);
		if (!is_dir($this->pathSave.'/Pictures'))
			mkdir($this->pathSave.'/Pictures', 0777);
		if (!is_dir($this->pathSave.'/Thumbnails'))
			mkdir($this->pathSave.'/Thumbnails', 0777);
		copy($this->pathTemplates.'/Thumbnails/thumbnail.png', $this->pathSave.'/Thumbnails/thumbnail.png');
		copy($this->pathTemplates.'/Configurations2/EMPTY.log', $this->pathSave.'/Configurations2/EMPTY.log');
		copy($this->pathTemplates.'/Pictures/EMPTY.log', $this->pathSave.'/Pictures/EMPTY.log');
		$this->manifest->saveFile();
		$this->meta->saveFile();
		$this->settings->saveFile();
		$this->styles->saveFile();
		$this->content->saveFile();
	}
	
	/**
	 * @access 	protected
	 * @return 	string		
	 */
	protected function _setTempDirName() {

		if (function_exists('microtime'))
			$docSave = 'temp_'.str_replace('.', '', microtime(true));
		else

			$docSave = 'temp_'.date('U');
		return $docSave;
	}
	
}

