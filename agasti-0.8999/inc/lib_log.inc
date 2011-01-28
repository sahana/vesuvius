<?php
/**
 * Sahana logging and cronology library
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage logging
 * @author     Chamindra de Silva <chamindra@opensource.lk>
 * @author 		Ravith Botejue <ravithb@yahoo.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */
define ("INFO","LOG_LEVEL_INFO");
define ("DEBUG","LOG_LEVEL_DEBUG");
define ("WARNING","LOG_LEVEL_WARNING");
define ("ERROR","LOG_LEVEL_ERROR");
define ("FATAL","LOG_LEVEL_FATAL");

define ("PERSON_SENSITIVE","LOG_SENSITIVITY_PERSON_SENSITIVE");
define ("ORGANIZATION_SENSITIVE","LOG_SENSITIVITY_ORGANIZATION_SENSITIVE");
define ("LEAGALLY_SENSITIVE","LOG_SENSITIVITY_LEAGALLY_SENSITIVE");
define ("NATIONAL_SECURITY_SENSITIVE","LOG_SENSITIVITY_NATIONAL_SECURITY_SENSITIVE");
define ("SOCIALLY_SENSITIVE","LOG_SENSITIVITY_SOCIALLY_SENSITIVE");
define ("DISASTER_MITIGATION_SENSITIVE","LOG_SENSITIVITY_DISASTER_MITIGATION_SENSITIVE");
define ("SYSTEM_SENSITIVE","LOG_SENSITIVITY_SYSTEM_SENSITIVE");
define ("NOT_SENSITIVE","LOG_SENSITIVITY_NOT_SENSITIVE");
define ("UNCLASSIFIED","LOG_SENSITIVITY_UNCLASSIFIED");

include_once($global['approot'].'inc/lib_uuid.inc');
include_once($global['approot'].'inc/lib_form.inc');


function shn_log_form($UUID)
{


}

/**
 * shn_log_event
 *
 * @param string UUID
 * @param string action
 * @param string message
 * @param string details
 * @return void
 */
/**function shn_log_event($UUID,$comments,$details=null,$date=null)
 {

 global $conf, $global;

 $datetime = ($date)? $date : date("Y-m-d H:i:s");

 $sql['event_date'] = $datetime;
 $sql['user_uuid'] = $_SESSION['user_id'];
 //$userlogid=$_SESSION['userlogid'];
 $sql['module'] = $global['module'];
 $sql['log_uuid'] = shn_create_uuid('log');
 $sql['opt_cron_type'] = 'cron';
 $sql['pgoc_uuid'] = $UUID;
 $sql['comments'] = $message;
 $sql['action'] = $global['action'];
 $sql['details'] = $details;

 //var_dump($sql);
 shn_db_insert($sql,'chronology');
 }*/

function shn_log_event($data_item_UUID=null,$comments,$details=null,$log_level=INFO,$sensitivity_level=NOT_SENSITIVE,$date_time=null,$module=null,$action=null,array $extra_opts=null)
{
	global $global,$conf;
	
	$datetime = (isset($date_time))? $date_time : date("Y-m-d H:i:s");
	
	$ext_opt_str = null;
	// prepare extra opts
	if($extra_opts != null){
		foreach($extra_opts as $key => $value){
			$ext_opt_str = $ext_opt_str . "<" . $key . ">" . $value . "</" . $key .">"; 
		}
	}
	
	//$conf['default_logger']= 'FileLogger'; // test only.
	try{
		$generic_logger = new ReflectionClass("Logger");
		// reflect the class
		$class = null;
		if(isset($conf['default_logger'])){
			$class = new ReflectionClass($conf['default_logger']);
		}
		//echo "<pre>";var_dump($conf);echo "</pre>";

		// if not null and instance of generic logger.
		if($class!=null && $class->isSubclassOf($generic_logger)){
			// reflect method to be called
			$log_method = $class->getMethod('log_message');
			// prepare argument list
			$args= array($data_item_UUID,$comments,$details,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str);
			//var_dump($args);
			// invoke method on a new instance of the class.
			$logger_instance = $class->newInstance();
			
			//$logger_instance->log_message($data_item_UUID,$comments,$details,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str);
			//var_dump($logger_instance);
			$log_method->invokeArgs($logger_instance,$args);
		}else{
			// Use default if reflection fails.
			Logger::log_message($data_item_UUID,$comments,$details,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str);
		}
	} catch (Exception $ex){
		echo "Reflection Exception : <pre>".$ex->getTraceAsString()."<br/>".$ex->getMessage()."</pre>";

	}

}

function shn_log_display($UUID=null)
{
	global $global;
	global $conf;

	?>
<div id="result">
<table>
	<thead>
	<?php
	shn_form_table_row(array('Date/Time','Module:Action','By User','Comments'));
	?>
	</thead>
	<?php
	$sql="";
	if($UUID!=null){
		$sql = "SELECT event_date,action,module,user_uuid,comments,pgoc_uuid from chronology
            WHERE pgoc_uuid = '$UUID' 
            ORDER BY event_date DESC";
	}else{
		$sql = "SELECT event_date,action,module,user_uuid,comments,pgoc_uuid from chronology
            ORDER BY event_date DESC";
		add_warning(_t("UUID is NULL"));
	}
	//add_warning("UUID is $UUID");
	$rs = $global['db']->Execute($sql);
	if ($rs) {
		while ($arr = $rs->FetchRow()) {
			//$act = shn_breadcrumb_get_nicename($arr[2], $arr[1]);
			$act = $arr[1];
			$mod = $conf['mod_'.$arr[2].'_name'];

			shn_form_table_row(array($arr[0],$mod.':'.$act,$arr[3],$arr[4]));
		}
	}
	?>
</table>
</div>
	<?php
}

/**
 * Generic class that will log messages using echo.
 * Extend and override logging function to perform custom logging.
 *
 */
class Logger{
	function log_message($data_item_UUID=null,$comments,$details=null,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str){
		echo "<pre> $datetime - $log_level : $sensitivity_level $module:$action ($data_item_UUID) $comment : $detail</pre><br/>";
	}

}

class DatabaseLogger extends Logger{
	function log_message($data_item_UUID=null,$comments,$details=null,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str){
		global $conf, $global;
		// log data array.
		$log_data_arr=null;
		if($data_item_UUID!=null){
			$log_data_arr['pgoc_uuid']=$data_item_UUID; // related data item uuid.
		}

		//$userlogid=$_SESSION['userlogid'];
		//	$log_data_arr['opt_cron_type'] = 'cron';

		$log_data_arr['comments'] = $comments;
		$log_data_arr['details'] = $details;
		$log_data_arr['sensitivity_level'] = $sensitivity_level;
		$log_data_arr['log_level'] = $log_level;
		$log_data_arr['event_date'] = $datetime;
		$log_data_arr['module'] = ($module!=null)?$module:$global['module'];
		$log_data_arr['action'] = ($action!=null)?$action:$global['action'];
		$log_data_arr['log_uuid'] = shn_create_uuid('log');
		$log_data_arr['user_uuid'] = $_SESSION['user_id'];
		//var_dump($sql);
		shn_db_insert($log_data_arr,'chronology');
	}

}

class FileLogger extends Logger{
	function log_message($data_item_UUID=null,$comments,$details=null,$log_level,$sensitivity_level,$datetime,$module,$action,$ext_opt_str){
		global $conf, $global;
		// log data array.
		$log_data_arr=array();
		if($data_item_UUID!=null){
			$log_data_arr['pgoc_uuid']=$data_item_UUID; // related data item uuid.
		}

		//$userlogid=$_SESSION['userlogid'];
		//	$log_data_arr['opt_cron_type'] = 'cron';

		$log_data_arr['comments'] = $comments;
		$log_data_arr['details'] = $details;
		$log_data_arr['sensitivity_level'] = $sensitivity_level;
		$log_data_arr['log_level'] = $log_level;
		$log_data_arr['event_date'] = $datetime;
		$log_data_arr['module'] = ($module!=null)?$module:$global['module'];
		$log_data_arr['action'] = ($action!=null)?$action:$global['action'];
		$log_data_arr['log_uuid'] = shn_create_uuid('log');
		$log_data_arr['user_uuid'] = $_SESSION['user_id'];
		

		//$conf['log_file_name_prefix'] = 'log'; // test only
		//$conf['log_file_location'] = "/home/ravith/workspace/sahana-phase2/log"; // test only
		$log_str = $log_data_arr['event_date']." - ".$log_data_arr['log_level']." : ".$log_data_arr['sensitivity_level']." ".$log_data_arr['module'].":".$log_data_arr['action']." (".$log_data_arr['pgoc_uuid'].") ".$log_data_arr['comments']." : ".$log_data_arr['details']." ".(isset($ext_opt_str)?": Extra Opts : " . $ext_opt_str . "\r\n":"");
	
		$log_file_name=((isset($conf['log_file_name_prefix']))?$conf['log_file_name_prefix']:'') . date("Ymd") . '.log';
		
		$log_location = $global['approot'].$conf['log_file_location'];
		//var_dump($log_location);
		
		if(!file_exists($log_location)){
			mkdir($log_location,0777,true);
		}
		//echo "<pre>{Permissions of ".$log_location." : ".fileperms($log_location."/")."}</pre>";
		$log_file = fopen($log_location . '/' . $log_file_name,"a+");
		if($log_file){
			fputs($log_file,$log_str);
			fclose($log_file);
		}else{
			echo "ERROR WRITING LOG";
		}
	}
}
