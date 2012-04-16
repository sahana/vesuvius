<?php
/**
 * @name         LPF Library Helper Functions
 * @version      12
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */



// update the arrival rate table...
function updateArrivalRate($person_uuid, $incident_id, $triagepic, $reunite, $website, $pfif, $vanilla_email) {

	global $global;
	$db = $global['db'];

	// lock tables to hold values for this session
	$q = "LOCK TABLE arrival_rate WRITE ;";
	$result = $db->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $db->ErrorMsg(), "updateArrivalRate 1 ((".$q."))"); }

	$q = "
		SELECT *
		FROM arrival_rate
		WHERE incident_id = ".$incident_id."
		ORDER BY arrival_time DESC
		LIMIT 1;
	";
	$result = $db->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $db->ErrorMsg(), "updateArrivalRate 2 ((".$q."))"); }

	if($result != NULL && !$result->EOF) {
		$source_all           = (int)$result->fields['source_all'];
		$source_triagepic     = (int)$result->fields['source_triagepic'];
		$source_reunite       = (int)$result->fields['source_reunite'];
		$source_website       = (int)$result->fields['source_website'];
		$source_pfif          = (int)$result->fields['source_pfif'];
		$source_vanilla_email = (int)$result->fields['source_vanilla_email'];
	} else {
		$source_all           = 0;
		$source_triagepic     = 0;
		$source_reunite       = 0;
		$source_website       = 0;
		$source_pfif          = 0;
		$source_vanilla_email = 0;
	}

	if($triagepic) {
		$source_triagepic++;
	}
	if($reunite) {
		$source_reunite++;
	}
	if($website) {
		$source_website++;
	}
	if($pfif) {
		$source_pfif++;
	}
	if($vanilla_email) {
		$source_vanilla_email++;
	}

	$source_all++;

	$q = "
		INSERT INTO arrival_rate (
			person_uuid,
			incident_id,
			arrival_time,
			source_all,
			source_triagepic,
			source_reunite,
			source_website,
			source_pfif,
			source_vanilla_email )
		VALUES (
			'".mysql_real_escape_string($person_uuid)."',
			'".mysql_real_escape_string((int)$incident_id)."',
			'".date('Y-m-d H:i:s')."',
			'".mysql_real_escape_string((int)$source_all)."',
			'".mysql_real_escape_string((int)$source_triagepic)."',
			'".mysql_real_escape_string((int)$source_reunite)."',
			'".mysql_real_escape_string((int)$source_website)."',
			'".mysql_real_escape_string((int)$source_pfif)."',
			'".mysql_real_escape_string((int)$source_vanilla_email)."' );
	";
	$result = $db->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $db->ErrorMsg(), "updateArrivalRate 3 ((".$q."))"); }

	// unlock table
	$q = "UNLOCK TABLES ;";
	$result = $db->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $db->ErrorMsg(), "updateArrivalRate 4 ((".$q."))"); }
}


// logs all DAO errors to database...
function daoErrorLog($file, $line, $method, $class, $function, $errorMessage, $other) {

	global $global;
	$db = $global['db'];
	$q = "
		INSERT INTO dao_error_log (
			file,
			line,
			method,
			class,
			function,
			error_message,
			other )
		VALUES (
			'".mysql_real_escape_string((string)$file)."',
			'".mysql_real_escape_string((string)$line)."',
			'".mysql_real_escape_string((string)$method)."',
			'".mysql_real_escape_string((string)$class)."',
			'".mysql_real_escape_string((string)$function)."',
			'".mysql_real_escape_string((string)$errorMessage)."',
			'".mysql_real_escape_string((string)$other)."' );
	";
	$result = $db->Execute($q);
}



//  validates a datetime string
function checkValidDateTime($dateTime) {

	if(preg_match("/^(\d{4})-(\d{2})-(\d{2}) ([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$/", $dateTime, $matches)) {
		if (checkdate($matches[2], $matches[3], $matches[1])) {
			return true;
		}
	}
	return false;
}



/**
 * Validate an email address.
 * Provide email address (raw input)
 * Returns true if the email address has the email
 * address format and the domain exists.
 * borrowed from: http://goo.gl/ufhg
 */
function isEmailValid($email) {
	$isValid = true;
	$atIndex = strrpos($email, "@");
	if(is_bool($atIndex) && !$atIndex) {
		$isValid = false;
	} else {
		$domain    = substr($email, $atIndex+1);
		$local     = substr($email, 0, $atIndex);
		$localLen  = strlen($local);
		$domainLen = strlen($domain);
		if($localLen < 1 || $localLen > 64) {
			// local part length exceeded
			$isValid = false;
		} else if($domainLen < 1 || $domainLen > 255) {
			// domain part length exceeded
			$isValid = false;
		} else if($local[0] == '.' || $local[$localLen-1] == '.') {
			// local part starts or ends with '.'
			$isValid = false;
		} else if(preg_match('/\\.\\./', $local)) {
			// local part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain)) {
			// character not valid in domain part
			$isValid = false;
		} else if(preg_match('/\\.\\./', $domain)) {
			// domain part has two consecutive dots
			$isValid = false;
		} else if(!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local))) {
			// character not valid in local part unless
			// local part is quoted
			if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local))) {
				$isValid = false;
			}
		}
		if($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
			// domain not found in DNS
			$isValid = false;
		}
	}
	return $isValid;
}



/**
* Function converts an XML string into an array
* Original Author: lz_speedy@web.de
* Original Source: http://goo.gl/7WRp
*/
function xml2array($xml, $get_attributes = 1, $priority = 'tag') {
	$contents = "";
	if (!function_exists('xml_parser_create')) {
		return array ();
	}
	$parser = xml_parser_create('');
	$contents = $xml;

	xml_parser_set_option($parser, XML_OPTION_TARGET_ENCODING, "UTF-8");
	xml_parser_set_option($parser, XML_OPTION_CASE_FOLDING, 0);
	xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);
	xml_parse_into_struct($parser, trim($contents), $xml_values);
	xml_parser_free($parser);
	if (!$xml_values) {
		return; //Hmm...
	}
	$xml_array = array ();
	$parents = array ();
	$opened_tags = array ();
	$arr = array ();
	$current = & $xml_array;
	$repeated_tag_index = array ();
	foreach ($xml_values as $data) {
		unset ($attributes, $value);
		extract($data);
		$result = array ();
		$attributes_data = array ();
		if (isset ($value)) {
			if ($priority == 'tag') {
				$result = $value;
			} else {
				$result['value'] = $value;
			}
		}
		if (isset($attributes) and $get_attributes) {
			foreach ($attributes as $attr => $val) {
				if ($priority == 'tag') {
					$attributes_data[$attr] = $val;
				} else {
					$result['attr'][$attr] = $val; //Set all the attributes in a array called 'attr'
				}
			}
		}
		if ($type == "open") {
			$parent[$level -1] = & $current;
			if (!is_array($current) or (!in_array($tag, array_keys($current)))) {
				$current[$tag] = $result;
				if ($attributes_data) {
					$current[$tag . '_attr'] = $attributes_data;
				}
				$repeated_tag_index[$tag . '_' . $level] = 1;
				$current = & $current[$tag];
			} else {
				if (isset ($current[$tag][0])) {
					$current[$tag][$repeated_tag_index[$tag . '_' . $level]] = $result;
					$repeated_tag_index[$tag . '_' . $level]++;
				} else {
					$current[$tag] = array (
						$current[$tag],
						$result
					);
					$repeated_tag_index[$tag . '_' . $level] = 2;
					if (isset ($current[$tag . '_attr'])) {
						$current[$tag]['0_attr'] = $current[$tag . '_attr'];
						unset ($current[$tag . '_attr']);
					}
				}
				$last_item_index = $repeated_tag_index[$tag . '_' . $level] - 1;
				$current = & $current[$tag][$last_item_index];
			}
		} elseif ($type == "complete") {
			if (!isset ($current[$tag])) {
				$current[$tag] = $result;
				$repeated_tag_index[$tag . '_' . $level] = 1;
				if ($priority == 'tag' and $attributes_data) {
					$current[$tag . '_attr'] = $attributes_data;
				}
			} else {
				if (isset ($current[$tag][0]) and is_array($current[$tag])) {
					$current[$tag][$repeated_tag_index[$tag . '_' . $level]] = $result;
					if ($priority == 'tag' and $get_attributes and $attributes_data) {
						$current[$tag][$repeated_tag_index[$tag . '_' . $level] . '_attr'] = $attributes_data;
					}
					$repeated_tag_index[$tag . '_' . $level]++;
				} else {
					$current[$tag] = array (
						$current[$tag],
						$result
					);
					$repeated_tag_index[$tag . '_' . $level] = 1;
					if ($priority == 'tag' and $get_attributes) {
						if (isset ($current[$tag . '_attr'])) {
							$current[$tag]['0_attr'] = $current[$tag . '_attr'];
							unset ($current[$tag . '_attr']);
						}
						if ($attributes_data) {
							$current[$tag][$repeated_tag_index[$tag . '_' . $level] . '_attr'] = $attributes_data;
						}
					}
					$repeated_tag_index[$tag . '_' . $level]++; //0 and 1 index is already taken
				}
			}
		} elseif ($type == 'close') {
			$current = & $parent[$level -1];
		}
	}
	return ($xml_array);
}


function makePersonUrl($uuid) {

	global $conf;

	// if the person is not reported locally, use an external url
	if(strpos($uuid, $conf['base_uuid']) === false) {
		return $conf['https'].$conf['base_uuid']."edit?puuid=".urlencode($uuid);

	// else use an internal url
	} else {
		return $conf['https'].$uuid;
	}
}



function makePageUrl() {

	global $conf;
	$link = $conf['https'].$conf['base_uuid'].$_SERVER['REQUEST_URI'];
	return $link;
}



function makeBaseUrl() {

	global $conf;
	$shorty = isset($_GET['shortname']) ? $_GET['shortname'] : "";
	$link = $conf['https'].$conf['base_uuid'].$shorty;
	return $link;
}



function makeBaseUrlMinusEvent() {

	global $conf;
	$link = $conf['https'].$conf['base_uuid'];
	return $link;
}



function makeBaseUrlMinusEventForHome() {

	global $conf;
	$link = $conf['https'].$conf['base_uuid'];
	return $link;
}



function getMicrotimeComponent() {
	$z = microtime();
	$z = explode(" ", $z);
	$z = explode(".", $z[0]);
	return $z[1];
}



