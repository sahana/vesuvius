<?php
/**
 * @name         Google Translate
 * @version      1.2
 * @package      res
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.06.01
 */


global $global;
define('GOOGLE_TRANS_ATTRIB', 'id="google_translate_element"');
//Defining approot for when google_trans will be called by google_po_builder
$global['approot']  = realpath(dirname(__FILE__)).'/../';
include_once ($global['approot'].'/inc/lib_errors.inc');
include_once ($global['approot'].'/res/po_parser.inc');
include_once ('translation_log.inc');

class GTranslator {
	private $_parser;
	private $_po_rewrite_locales = array();
	public function GTranslator() {
		$this->_parser = new POParser();
	}
	/**
	 * This function utilises the PO Parser to build a Google Translated PO file
	 * @param unknown_type $locale
	 */
	function buildGooglePO($locale) {
		global $global; 
		$total_chars = 0;
		$translated_chars = 0;
		$untranslated_chars = 0;
		if ( !isset($global['translation_log']) ) {
			if ( is_writable('translation_log.txt') ) {
				$global['translation_log'] = new TranslationLog();
			}
		
		}
		$this->_parser->parse($locale);
		$entries = $this->_parser->getEntries();
		foreach ( $entries as &$entry ) { 
			$total_chars += strlen($entry['msgid']);
			if ( $entry['msgstr'] == '' ) {
				$entry['msgstr'] = $this->shn_google_translate($entry['msgid'], $locale);
				if ( $entry['msgstr'] == '' ) {
					$untranslated_chars += strlen($entry['msgid']);
				}
				else {
					$translated_chars += strlen($entry['msgid']);
				}
				$global['translation_log']->writeLog('Google translation for string "'.$entry['msgid'].'" for locale '.$locale.': "'.$entry['msgstr'].'"');
			}
		}
		$global['translation_log']->writeLog('Google PO rebuild for locale '.$locale.' done.');
		$global['translation_log']->writeLog('Total characters in PO: '.$total_chars);
		$global['translation_log']->writeLog('Total translated characters: '.$translated_chars);
		$global['translation_log']->writeLog('Total untranslated characters: '.$untranslated_chars);
		$this->_parser->setEntries($entries);
		$this->_parser->writeToFile();
	}
	/**
	 * Add a locale for PO rewrite in the near future
	 * @param string $locale
	 */
	function rewrite_po($locale) {
		global $global;
		$localelist = file_get_contents($global['approot'].'/res/rewrite_pos_list.txt');
		$localelist = explode(',', $localelist, -1);
		if ( array_search($locale, $localelist) === false ) {
			$po_list = fopen($global['approot'].'/res/rewrite_pos_list.txt', 'a');
			fwrite($po_list, $locale.',');
			fclose($po_list);
		}
	}
	function get_po_rewrite_locales() {
		return $this->_po_rewrite_locales;
	}
	/**
	 *
	 * @desc Function to get the current locale from the locale file
	 * @return The current locale
	 */
	function shn_getLocale() {
		global $global;
		if ( isset($_SESSION['locale']) ) {
			$locale = substr($_SESSION['locale'], 0, 2);
			return $locale;
		} else {
			return 'en';
		}
	}


	/**
	 * Dummy function
	 */
	function shn_google_translate_dummy($text) {
		//echo $text.' was passed to GTranslate function\n';
		$translations = array ('Add a new Hospital' => 'Ajouter un nouvel hôpital',
								'Hospital Information'	=> 'Information Hospitalier',
								'Name' => 'Nom',
								'Hospital Administration' => 'Hôpital d\'administration');
		
		if ( array_key_exists($text, $translations) ) {
			return $translations[$text];
		}
		else return $text;
		
		
	}
	/**
	 * @param $text String String to be translated
	 * @desc Function to use Google Translate API to translate strings
	 * @return The string translated into the relevant language
	 */
	function shn_google_translate($text, $locale) {

		// removing context filter, contexts are filtered out before they come here
		/*if ( strpos($text, "|") != false ) {
		list($context,$msgid) = explode("|", $text);
		$text = $msgid;
		}*/
		$lang = $locale;
		// if locale is same as original, return original
		if( $lang == 'en' )  {
			return $text;
		}
		if ( $locale == 'test' ) {
			//Test condition, we are setting the language to Welsh
			$lang = 'cy';
		}
		$key = 'AIzaSyBC0pNz4quKZdoqv9s2ughgMAgQiFzz_p4';
		

		//first, we have to check whether the current locale is supported by Google Translate API
		$crl = curl_init();

		/*curl_setopt($crl , CURLOPT_URL, 'https://www.googleapis.com/language/translate/v2/languages?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM');
		 $langResult = json_decode(curl_exec($crl));*/

		//Since we're sending a GET request to Google Translate REST API, we need to make some characters URI-friendly
		$text = urlencode($text);

		/*$fields = array (
		 'key'	=>	'AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM',
				'q'		=>	$text,
				'source'=>	'en',
				'target'=>	$lang
		);
		$header = array ('X-HTTP-Method-Override: GET');*/

		curl_setopt($crl, CURLOPT_URL, "https://www.googleapis.com/language/translate/v2?key={$key}&q={$text}&source=en&target={$lang}");
		curl_setopt($crl, CURLOPT_RETURNTRANSFER, 1);

		/*post request
		 POST request needs to be sent with header change
		curl_setopt($crl, CURLOPT_POST, 1);
		curl_setopt($crl, CURLOPT_POSTFIELDS, $fields);
		curl_setopt($crl, CURLOPT_HTTPHEADER, $header);
		*/

		$result = curl_exec($crl);
		$result = json_decode($result, true);
		curl_close($crl);


		//check for first 'data' level of json string
		if (!is_array($result) || !array_key_exists('data', $result)) {
			print('Upper Level data key not found in JSON string');
			return '';
		}

		// Check for second 'translations' level in json string
		if (!array_key_exists('translations', $result['data'])) {
			print('2nd Level translations key not found in JSON string');
			return '';
		}

		//Ensure that the result is an array
		if (!is_array($result['data']['translations'])) {
			print('Translations array not returned properly');
			return '';
		}

		return urldecode($result['data']['translations'][0]['translatedText']);

	}



	/**
	 *
	 * @desc Initialize Google Translate element for a page
	 */
	function shn_google_translate_element_init() {
		if ( isset($_SESSION["locale"]) ) {
			$loc = $_SESSION["locale"];
		}
		else $loc = shn_getLocale();
		$loc = 'de';
		echo "
		<script>
		function googleTranslateElementInit() {
		new google.translate.TranslateElement( {
		pageLanguage: 'en',
		includedLanguages: '{$loc}',
		layout: google.translate.TranslateElement.InlineLayout.SIMPLE
	}, 'google_translate_element');
	}
	</script>
	<script src=\"//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit\"></script>";
	}



	/**
	 *
	 * @desc Function to add Google Translate attribute to HTML elements
	 */
	function shn_add_gtrans_attrib() {
		return "id=\"google_translate_element\"";
	}



	/**
	 * @param String $text Text to add the translate element to
	 * @desc Function to add Google Translate element to the page
	 */
	function shn_google_translate_element($text) {
		echo "<div id=\"google_translate_element\">".$text."</div>";

	}

}