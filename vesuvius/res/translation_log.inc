<?php
/**
 * @name         Translation Activity Logger
 * @version      1.2
 * @package      res
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0224
 */
class TranslationLog {
	var $_enabled = false;
	
	/**
	 * Set whether the Log should be enabled (disabled in case of lack of write permissions to log file)
	 * @param Boolean $enabled
	 */
	function setEnabled($enabled) {
		$this->_enabled = $enabled;
	}
	/**
	 * Write $message to the log file
	 * @param String $message The message to be written
	 */
	function writeLog($message) {
		if ( $this->_enabled ) {
			global $global;
			$datetime = date('Y-m-d H:i:s');
			$file = fopen($global['approot'].'res/translation_log.txt', 'a');
			fwrite($file, $datetime." ".$message."\n");
			fclose($file);
		}
	}
	
}