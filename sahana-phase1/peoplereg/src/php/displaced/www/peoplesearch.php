<?php

/** ensure this file is being included by a parent file */
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

// I have copied this file and removed some search related
// Functions from Kamal's original search.  This is (I am saying
// this for the Nth time) dirty - I know, but, oh well...

// load the html drawing class
//require_once( $mainframe->getPath( 'front_html' ) );
//require_once( $mainframe->getPath( 'class' ) );

define("FULLTEXT", 0);
define("PLAINTEXT", 1);
define("SOUNDEX", 2);
define("METAPHONE", 3);

define("DEFAULT_SEARCH_ALGORITHM", METAPHONE);

function getDefaultHash($str) {
	switch (DEFAULT_SEARCH_ALGORITHM) {
		case PLAINTEXT:
			return $str;
			break;
		case METAPHONE:
			return metaphone($str);
			break;
		case SOUNDEX:
			return soundex($str);
			break;
		default:
			return $str;
			break;
	}
}

// todo: Go for an incremental indexing than this
function indexAll() {
	global $mainframe, $database;

	// todo: Hard coded component name chanage it to the commented one later on
	//$database->setQuery("select entity, attribute_id, value_string from #__report_attribute_values where value_string not null and value_string != ''");
	$database->setQuery("select entity, attribute_id, value_string from sahana_attribute_values where value_string is not null and value_string != ''");
	$records = $database->loadRowList();

	// for all records in the attribute value table
	foreach($records as $record) {
		// Get the string
		$whole_str = $record['value_string'];

		// later: Insert the full string to the lexicon table?

	    // Get the words
		$words = explode(" ", $whole_str);
		
		// For all words
		foreach($words as $word) {
			/*
				ALGORITHM IDs
					PLAIN TEXT 	: 1
					SOUNDEX		: 2
					METAPHONE	: 3
			*/

			// Insert the plain text word
			_insertLexicon($word, 1, $record['entity'], $record['attribute_id']); // test: erase this
			// Insert the soundex
			_insertLexicon(soundex($word), 2, $record['entity'], $record['attribute_id']); // test: erase this
			// Insert the metaphone
			_insertLexicon(metaphone($word), 3, $record['entity'], $record['attribute_id']); // test: erase this
		}
	}

    $mainframe->SetPageTitle("Indexing Data");
	HTML_peoplesearch::showIndexingCompleteMsg();
}

function incIndexAll() {
	global $mainframe, $database, $option, $Itemid;

	// Get the maximum entity id
	// later: change the table name to mambo convention
	$database->setQuery("select max(id) from sahana_entities");
	$maxEntityId = $database->loadResult();
	
	$start = mosGetParam($_REQUEST, 'entitystartid', 0);
	$start = (int) $start;
	
	// if start > max entity id, terminate
	if ($start > $maxEntityId) {
		// We are done
	} else {
		// else
		// index from start to start + interval 
		$interval = 50;
		$end = $start + $interval;
		incIndex($start, $end);
		// redirect again with a new start 
		$url = "index.php?option=".$option."&task=incindexall&Itemid=".$Itemid."&entitystartid=".$end;
		$percentComplete = (int) (($end * 100)/$maxEntityId);
		$msg = $percentComplete."% completed";
		mosRedirect($url, $msg);
	}

    $mainframe->SetPageTitle("Incremental Indexing of Data");
	HTML_peoplesearch::showIndexingCompleteMsg();
}

function incIndex($entityStart, $entityEnd) {
	global $database;

	// todo: Hard coded component name chanage it to the commented one later on
	//$database->setQuery("select entity, attribute_id, value_string from #__report_attribute_values where value_string not null and value_string != ''");
	$database->setQuery("select entity, attribute_id, value_string from sahana_attribute_values where value_string is not null and value_string != '' and entity between $entityStart and $entityEnd");
	$records = $database->loadRowList();

	// for all records in the attribute value table
	foreach($records as $record) {
		// Get the string
		_indexAttribute($record['value_string'], $record['entity'], $record['attribute_id']);
	}
}

function _indexAttribute($string, $entity_id, $attribute_id) {
	// later: Insert the full string to the lexicon table?

    // Get the words
	$words = explode(" ", $string);
		
		// For all words
	foreach($words as $word) {
		// Insert the plain text word
		_insertLexicon($word, PLAINTEXT, $entity_id, $attribute_id); // test: erase this
		// Insert the soundex
		_insertLexicon(soundex($word), SOUNDEX, $entity_id, $attribute_id); // test: erase this
		// Insert the metaphone
		_insertLexicon(metaphone($word), METAPHONE, $entity_id, $attribute_id); // test: erase this
	}
}

function _insertLexicon($hash, $algorithm_id, $entity_id, $attribute_id) {
	global $database;
	// todo: is this required?
	$hash = addslashes($hash);

    // Check whether it is already inserted into the lexicon table
	$database->setQuery("select id from sahana_lexicon where hash='$hash' and algorithm_id = $algorithm_id");
	// if yes get the lexicon id
	$lexicon_id = $database->loadResult();
	echo $database->getErrorMsg();

	// if not, insert and get the lexicon id
	if($lexicon_id == null) {
		$database->setQuery("insert into sahana_lexicon (hash, algorithm_id) values ('$hash', $algorithm_id)");

	    if ($database ->query()) {
			$database->setQuery("select id from sahana_lexicon where hash='$hash' and algorithm_id = '$algorithm_id'");
			$lexicon_id = $database->loadResult();
			echo $database->getErrorMsg();
		} else {
			echo $database->stderr();
		}
	}

	// Insert into the lexicon_entities table
	if($lexicon_id != null) {
		// Check whether available
		$database->setQuery("select lexicon_id from sahana_lexicon_entities where lexicon_id = $lexicon_id and entity_id = $entity_id and attribute_id = $attribute_id");
		if($database->loadResult() == null) {	
		    $database->setQuery("insert into sahana_lexicon_entities (lexicon_id, entity_id, attribute_id) values ($lexicon_id, $entity_id, $attribute_id)");
		    if(!$database->query()) {
			    echo $database->stderr();
		    }	
		}
	}
}

?>
