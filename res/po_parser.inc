<?php
/**
 * Copyright (C) 2008, Iulian Ilea (http://iulian.net), all rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @name         PO Parser for Google Translation implementation
 * @version      1.2
 * @package      res
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.06.01
 */
global $global;
include_once ($global['approot'].'/inc/lib_errors.inc');
class POParser
{
    private $_filename = '';
    private $_pogfile = '';
    private $_parsedData = array();

    /**
     * Format of a msgid entry:
     * array(
     *      'references'   => array(),		// each file on a new line
     *      'translator-comments'   => '',
     *      'extracted-comments'    => '',
     *      'flags'        => array(
     *          'fuzzy'
     *          ...
     *      ),
     *      'previous-msgctxt'  => '',
     *      'previous-msgid'    => '',
     *      'msgctxt'       => '',
     *      'msgid'         => '',
     *
     *      // when no plural forms
     *      'msgstr'        => '',
     *
     *      // when plural forms
     *      'msgid_pural'   => '',
     *      'msgstr'        => array(
     *          0   => '',                  // singular
     *          1   => '',                  // 1st plural form
     *          2   => '',                  // 2nd plural form
     *          ...
     *          n   => ''                   // nth plural form
     *      )
     * )
     *
     * @see http://www.gnu.org/software/gettext/manual/gettext.html#PO-Files
     */
    // Getter and Setter functions for headers and entries in parsed data
	public function setHeaders($headers) {
		$this->_parsedData['headers'] = $headers; 
	}
	public function getHeaders() {
		return $this->_parsedData['headers'];
	}
	public function setEntries($entries) {
		$this->_parsedData['entries'] = $entries;
	}
	public function getEntries() {
		return $this->_parsedData['entries'];
	}
    protected function _dequote($str)
    {
        return substr($str, 1, -1);
    }

    public function parse($locale)
    {
    	$this->_filename = $filename = 'locale/'.$locale.'.po';
    	$this->_pogfile = 'locale/'.$locale.'_g.pog';
        // basic file verification
        if (!is_file($filename)) {
            add_error('POParser says: The specified PO file does not exist.');
            return null;
        }
        if (substr($filename, strrpos($filename, '.')) !== '.po') {
            add_error('POParser says: The specified file is not a PO file.');
            return null;
        }
        $lines = file($filename, FILE_IGNORE_NEW_LINES);

        // on the first two lines I'm expecting msgid respectively msgstr,
        // both containing empty strings
        $entries = array(
//            array(
//                'msgid'     => '',
//                'msgstr'    => array('')
//            )
        );

        // parsing headers; stop at the first empty line
        $headers = array(
            'Project-Id-Version'            => '',
            'Report-Msgid-Bugs-To'          => '',
            'POT-Creation-Date'             => '',
            'PO-Revision-Date'              => '',
            'Last-Translator'               => '',
            'Language-Team'                 => '',
            'Content-Type'                  => '',
            'Content-Transfer-Encoding'     => '',
            'Plural-Forms'                  => '',
        );
        $i = 2;
        while ($line = $lines[$i++]) {
            $line = $this->_dequote($line);
            $colonIndex = strpos($line, ':');
            if ($colonIndex === false) {
                continue;
            }
            $headerName = substr($line, 0, $colonIndex);
            if (!isset($headers[$headerName])) {
                continue;
            }
            // skip the white space after the colon and remove the \n at the end
            $headers[$headerName] = substr($line, $colonIndex + 1, -2);
        }

        $entry = array();
        for ($n = count($lines); $i < $n; $i++) {
            $line = $lines[$i];
            if ($line === '') {
                $entries[] = $entry;
                $entry = array();
                continue;
            }
            if ($line[0] == '#') {
                $comment = substr($line, 3);
                switch ($line[1]) {
                    // translator comments
                    case ' ': {
                        if (!isset($entry['translator-comments'])) {
                            $entry['translator-comments'] = $comment;
                        }
                        else {
                            $entry['translator-comments'] .= "\n" . $comment;
                        }
                        break;
                    }
                    // extracted comments
                    case '.': {
                        if (!isset($entry['extracted-comments'])) {
                            $entry['extracted-comments'] = $comment;
                        }
                        else {
                            $entry['extracted-comments'] .= "\n" . $comment;
                        }
                        break;
                    }
                    // reference
                    case ':': {
                        if (!isset($entry['references'])) {
                            $entry['references'] = array();
                        }
                        $entry['references'][] = $comment;
                        break;
                    }
                    // flag
                    case ',': {
                        if (!isset($entry['flags'])) {
                            $entry['flags'] = array();
                        }
                        $entry['flags'][] = $comment;
                        break;
                    }
                    // previous msgid, msgctxt
                    case '|': {
                        // msgi[d]
                        if ($comment[4] == 'd') {
                            $entry['previous-msgid'] = $this->_dequote(substr($comment, 6));
                        }
                        // msgc[t]xt
                        else {
                            $entry['previous-msgctxt'] = $this->_dequote(substr($comment, 8));
                        }
                        break;
                    }
                }
            }
            else if (strpos($line, 'msgid') === 0) {
                if ($line[5] === ' ') {
                    $entry['msgid'] = $this->_dequote(substr($line, 6));
                }
                // msgid[_]plural
                else {
                    $entry['msgid_plural'] = $this->_dequote(substr($line, 13));
                }
            }
            else if (strpos($line, 'msgstr') === 0) {
                // no plural forms
                if ($line[6] === ' ') {
                    $entry['msgstr'] = $this->_dequote(substr($line, 7));
                }
                // plural forms
                else {
                    if (!isset($entry['msgstr'])) {
                        $entry['msgstr'] = array();
                    }
                    $entry['msgstr'][] = $this->_dequote(substr($line, strpos($line, ' ') + 1));
                }
            }
            /**
             * Added support for msgctxt - RD
             */
            else if (strpos($line, 'msgctxt') === 0) {
            	if ($line[7] === ' ') {
            		$entry['msgctxt'] = $this->_dequote(substr($line, 8));
            	}
            }
            else if ($line[0] === '"' && isset($entry['msgstr'])) {
                $line = "\n" . preg_replace('/([^\\\\])\\\\n$/', "\$1\n", $this->_dequote($line));
                if (!is_array($entry['msgstr'])) {
                    $entry['msgstr'] .= $line;
                }
                else {
                    $entry['msgstr'][count($entry['msgstr']) - 1] .= $line;
                }
            }
        }
        $this->_parsedData = array('headers' => $headers, 'entries' => $entries);
    }
    /**
     * Function to write parsed (and translated) PO data back to file
     */
    function writeToFile() {
    	$fileoutput =  "# Google translation for vesuvius\n".
					   "# This file is distributed under the same license as the vesuvius package.\n";
    	$fileoutput .= "msgid \"\"\nmsgstr \"\"\n";
    	foreach ( $this->_parsedData['headers'] as $id=>$header ) {
    		$fileoutput .= "\"".$id.':'.$header."\\n\"\n";
    	}
    	foreach ( $this->_parsedData['entries'] as $entry ) {
    		$fileoutput .= "\n";
    		if ( array_key_exists('references', $entry) ) {
    			foreach ( $entry['references'] as $reference ) {
    				$fileoutput .= "#: ".$reference."\n";
    			}
    			if ( array_key_exists('msgctxt', $entry) ) {
    				$fileoutput .= "msgctxt \"".$entry['msgctxt']."\"\n";
    			}
    			$fileoutput .= "msgid \"".$entry['msgid']."\"\n";
    			$fileoutput .= "msgstr \"".$entry['msgstr']."\"\n";
    		}
    		
    	}
    	$file = fopen($this->_pogfile, 'w');
    	if ( $file != false ) {
    		fwrite($file, $fileoutput);
    		fclose($file);
    	}
    	else {
    		print("Google PO file write failed");
    	}
    	
    }
}