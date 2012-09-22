<?php
/**
 * @name         Translation Activity Logger
 * @version      1.2
 * @package      res
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.09.18
 */
class TranslationLog {
	function writeLog($message) {
		global $global;
		$datetime = date('Y-m-d H:i:s');
		$file = fopen($global['approot'].'res/translation_log.txt', 'a');
		fwrite($file, $datetime." ".$message."\n");
		fclose($file);
	}
	
}