<?php
/**
 * @name         Google Translate
 * @version      1.2
 * @package      rez
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.05.24
 */
global $global;
define("GOOGLE_TRANS_ATTRIB", "id=\"google_translate_element\"");
include_once ($global['approot'].'/inc/lib_errors.inc');
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
	}
	/*$contents = file_get_contents($global['approot'].'/res/locale/locale');
	$locale = substr($contents, 0, 2);*/
	else return 'en';
}
/**
 * @param $text String String to be translated
 * @desc Function to use Google Translate API to translate strings
 * @return The string translated into the relevant language
 * Google Translate API Key = AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM
 */
function shn_google_translate($text) {
	//get the language we need to translate to
	$lang = shn_getLocale();
	//if locale is same as original, return original
	if ( $lang == 'en' ) {
		return $text;
	}
	//first, we have to check whether the current locale is supported by Google Translate API
	$crl = curl_init();
	/*curl_setopt($crl , CURLOPT_URL, 'https://www.googleapis.com/language/translate/v2/languages?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM');
	$langResult = json_decode(curl_exec($crl));*/
<<<<<<< TREE



=======
>>>>>>> MERGE-SOURCE
	//Since we're sending a GET request to Google Translate REST API, we need to make some characters URI-friendly
	$text = urlencode($text);
	/*$fields = array (
				'key'	=>	'AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM',
				'q'		=>	$text,
				'source'=>	'en',
				'target'=>	$lang 
			);
	$header = array ('X-HTTP-Method-Override: GET');*/
	curl_setopt($crl , CURLOPT_URL, "https://www.googleapis.com/language/translate/v2?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM&q={$text}&source=en&target={$lang}");
	curl_setopt($crl, CURLOPT_RETURNTRANSFER, 1);
	/*post request
	 POST request needs to be sent with header change 
	curl_setopt($crl, CURLOPT_POST, 1);
	curl_setopt($crl, CURLOPT_POSTFIELDS, $fields);
	curl_setopt($crl, CURLOPT_HTTPHEADER, $header); */
	$result = curl_exec($crl);
	$result = json_decode($result, true);

	curl_close($crl);


	//check for first 'data' level of json string
	if (!is_array($result) || !array_key_exists('data', $result)) {
    	add_error('Upper Level data key not found in JSON string');
   	}

    // Check for second 'translations' level in json string
    if (!array_key_exists('translations', $result['data'])) {
     	add_error('2nd Level translations key not found in JSON string');
   	}
 	//Ensure that the result is an array
    if (!is_array($result['data']['translations'])) {
        add_error('Translations array not returned properly');
    }
<<<<<<< TREE

 	return $result['data']['translations'][0]['translatedText'];

=======
    
 	return urldecode($result['data']['translations'][0]['translatedText']);
    
>>>>>>> MERGE-SOURCE
    //Exception if final step fails
    add_error('Could not translate!');
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
	echo "<script>
function googleTranslateElementInit() {
  new google.translate.TranslateElement({
    pageLanguage: 'en',
    includedLanguages: '{$loc}',
    layout: google.translate.TranslateElement.InlineLayout.SIMPLE
  }, 'google_translate_element');
}
</script><script src=\"//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit\"></script>";
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
<<<<<<< TREE

}=======
	
}
//GET URL: "https://www.googleapis.com/language/translate/v2?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM&q={$text}&source=en&target={$lang}">>>>>>> MERGE-SOURCE
