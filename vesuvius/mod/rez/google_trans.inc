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
include_once ($global['approot'].'/inc/lib_errors.inc');
/**
 * 
 * @desc Function to get the current locale from the locale file
 * @return The current locale
 */
function shn_getLocale() {
	global $global; 
	$contents = file_get_contents($global['approot'].'/res/locale/locale');
	$locale = substr($contents, 0, 2);
	return $locale;
}
/**
 * @param $text String String to be translated
 * @desc Function to use Google Translate API to translate strings
 * @return The string translated into the relevant language
 * Google Translate API Key = AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM
 */
function shn_google_translate($text) {
	//first, we have to check whether the current locale is supported by Google Translate API
	$crl = curl_init();
	/*curl_setopt($crl , CURLOPT_URL, 'https://www.googleapis.com/language/translate/v2/languages?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM');
	$langResult = json_decode(curl_exec($crl));*/
	
	//get the language we need to translate to
	$lang = shn_getLocale();
	
	
	
	//Since we're sending a GET request to Google Translate REST API, we need to make some characters URI-friendly
	$text = urlencode($text);
	curl_setopt($crl , CURLOPT_URL, "https://www.googleapis.com/language/translate/v2?key=AIzaSyBeTv-NoFYl3LdDUZh1Ysd0H_fpZn2SrYM&q={$text}&source=en&target={$lang}");
	curl_setopt($crl, CURLOPT_RETURNTRANSFER, 1);
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
    
 	return $result['data']['translations'][0]['translatedText'];
    
    //Exception if final step fails
    add_error('Could not translate!');
}