<?php
	//Read configuration file and retrieve logging level
	//If not set, default to 0
	function get_level(){
	$log_level=0;
	$filename="/home/pradeeper/sahana/conf/config.inc";
	$file=fopen($filename,"r");
	while(!feof($file)){
		$value=fgets($file,100);
		if(eregi("^loglevel",$value)){
			ereg("[0-9]",$value,$array);
		  $log_level=$array[0];
			}
	}
	//echo $log_level;
	fclose($file);
	return $log_level;
	}
	//echo get_level();
?>
