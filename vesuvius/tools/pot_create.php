<?php
/**
 * Deprecated PHP translatable string dump script
 */
global $global;
$global['approot'] = '..';
$stringFiles = array ('[[person]]' => 'person.php', '[[message]]' => 'message.php');
$typeFile = array();
$origfile = fopen($global['approot'].'/mod/rap/main.inc', 'r');
$translatable = '#\_t#';
$brackets = "#\[\[*\]\]#";
$typeFile = array();
while ( !feof($origfile) ) {
	$line = fgets($origfile);
	$translatableMatches = array();
	preg_match($translatable, $line, $translatableMatches);
	print_r($translatableMatches);
	foreach( $translatableMatches as $match ) {
		$bracketMatches = array();
		preg_match($brackets,$match,$bracketMatches);
		if ( isset($bracketMatches[0]) ) {
			$type = $bracketMatches[0];
			if ( is_null($typeFile[$type]) ) {
				$typeFile[$type] = fopen($global['approot'].'/tools/'.$stringFiles[$type], 'w');
			}
			fwrite($typeFile[$type], str_replace($type, '', $match).'\n');
		}
	}
}
fclose($origfile);
foreach( $typeFile as $type ) {
	fclose($type);
}