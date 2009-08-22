<?php
/**
 * debug 
 * 
 * @param mixed $message 
 * @access public
 * @return void
 */
function debug($message){
		global $conf;
		$logdate= date("jS F Y");
		$logtime= date("G:i:s");
		$message_text="DEBUG: ".$logdate.",".$logtime.": ".$message."\n";
		if($conf['debug_output']=='file'){
			shn_file_insert_log($logdate,$logtime,$message_text);
		}
		else if($conf['debug_output']=='screen'){
			echo $message_text;
		}
		
}

/**
 * shn_file_insert_log 
 * 
 * @param mixed $date 
 * @param mixed $time 
 * @param mixed $message 
 * @access public
 * @return void
 */
function shn_file_insert_log($date,$time,$message){
		global $conf;
	  $filename=$conf['debug_file_path'];
	  $fp=fopen($filename,"a");
		flock($fp,2); //write lock
		fwrite($fp,$message);
		flock($fp,3); //release lock
		fclose($fp);					
}

