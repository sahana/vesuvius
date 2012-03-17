<?php

// known deficiency in using this script...
// there has to be an image_id = 1 in the image table
// if not, the lowest empty block will be skipped

error_reporting(E_ALL ^ E_NOTICE);
ini_set("display_errors", "stdout");

$global['approot'] = getcwd() . "/../";
require_once("../conf/sahana.conf");
require_once("../3rd/adodb/adodb.inc.php");
require_once("../inc/handler_db.inc");

echo "Beginning compression at " . strftime("%c") . "\n";
echo "Using db ". $global['db']->database."\n";

$start = 0;
$stop = false;

while(!$stop) {
	$q = "
		select image_id
		from image
		where image_id >= ".$start."
		limit 2;
	";
	$result = $global['db']->Execute($q);

	if($result === false) {
		die("Q1 ErrorMsg: ".$global['db']->ErrorMsg());
	}

	if($result == null || $result->EOF) {
		$stop = true;
	}

	$a = $result->fields['image_id'];

	$result->MoveNext();

	if($result == null || $result->EOF) {
		$stop = true;
	}

	$b = $result->fields['image_id'];

	if(!$stop && ((int)$b != (int)($a + 1))) {
		$q = "
			UPDATE  image
			SET image_id = '".(int)($a+1)."'
			WHERE image_id = '".$b."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			die("Q2 ErrorMsg: ".$global['db']->ErrorMsg());
		}
		echo "moved $b to ".($a+1)."\n";
	}

	$start++;
}

echo "Next image_id value: ".$start."\n";

$q = "
	UPDATE  image_seq
	SET `id` = '".(int)$start."';
";
$result = $global['db']->Execute($q);
if($result === false) {
	die("Q3 ErrorMsg: ".$global['db']->ErrorMsg());
}


$q = "
	ALTER TABLE image_seq AUTO_INCREMENT = ".$start.";
";
$result = $global['db']->Execute($q);
if($result === false) {
	die("Q4 ErrorMsg: ".$global['db']->ErrorMsg());
}



