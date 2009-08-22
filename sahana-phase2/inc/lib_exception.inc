<?php
/**
 *
 * This is a generic exception handler library, you can add new exception classes when required
 * your own custom exceptions
 * This library give ability to report and display exceptions.
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage exception
 * @author     Ravith Botejue. <ravithb@yahoo.com>
 * @author     Prabath Kumarasinghe <prabath@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**Documentation - http://www.sahana.lk/wiki/doku.php?id=dev:exeptions */

if(file_exists($global['approot'].'conf/sysconf.inc.php'))
	include_once($global['approot'].'conf/sysconf.inc.php');
require_once($global['approot'].'inc/lib_locale/gettext.inc');
include_once($global['approot'].'inc/lib_errors.inc');


/**
 * The generic exception class where exception is unknown.
 * @param $msg			the user friendly message about the exception
 * @param $mod			the module name
 * @param $act			the module action name
 * @param $errno		the error number of the exception
*/

class SahanaException extends Exception {

function __construct($msg,$mod = null,$act = null,$errno=0){
		global $global;
		$mod = ($mod!=null)?$mod:$global['module'];
		$act = ($act!=null)?$act:$global['action'];
		//$this->result = ($result!=null)?$result:REPORT_AND_ABORT;
		$msg = "SahanaUncaughtException : <b>$msg</b>, module : <b>$mod</b>, action : <b>$act</b>";
		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($msg,$errno);
	}
}


/**
* Sahana Sql Exception Class. This will be called with the following params
*
* @param $dbms		the RDBMS you are connecting to
* @param $fn		the name of the calling function (in uppercase) default is EXECUTE
* @param $errno		the native error number from the database
* @param $errmsg	the native error msg from the database
* @param $p1		$fn specific parameter - see below
* @param $P2		$fn specific parameter - see below
*/

class SahanaSQLException extends Exception{

	var $dbms;
	var $fn;
	var $sql = '';
	var $params = '';
	var $host = '';
	var $database = '';


	function __construct($dbms=null, $fn=null, $errno=null, $errmsg=null, $p1=null, $p2=null, $thisConnection=null)
	{
		global $global;
		global $conf;
		//var_dump($global['db']);
		if (file_exists($global['approot'].'conf/sysconf.inc.php')){
			if(!isset($dbms))
				$dbms = $conf['db_engine'];
			if(!isset($thisConnection))
				$thisConnection = $global['db'];
			if(!isset($errmsg))
				$errmsg = $thisConnection->_errorMsg;
			if(!isset($fn))
				$fn = 'EXECUTE';
		}


		switch($fn) {
		case 'EXECUTE':
			$this->sql = $p1;
			$this->params = $p2;
			$s = "SahanaSQLException : $dbms database [$errno: $errmsg] in $fn(\"$p1\")\n on line ".$this->getLine()." in ".$this->getFile();
			break;

		case 'PCONNECT':
		case 'CONNECT':
			$user = $thisConnection->user;
			//echo "USER = ".$user;
			$s = "SahanaSQLException : $dbms database [$errno: $errmsg] in $fn($p1, '$user', '****', $p2)\n on line ".$this->getLine()." in ".$this->getFile();
			break;
		default:
			$s = " SahanaSQLException : $dbms database 	[$errno: $errmsg] in $fn($p1, $p2)\n on line ".$this->getLine()." in ".$this->getFile();
			break;
		}

		$this->dbms = $dbms;
		$this->host = $thisConnection->host;
		$this->database = $thisConnection->database;
		$this->fn = $fn;
		$this->msg = $errmsg;

		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($s,$errno);
	}

}

/**Start IO Exception classes*/

/** SahanaIOException is the general class of exceptions produced by failed or interrupted I/O operations
* @param $msg			the message about the exception
* @param $mod			the module name
* @param $act			the module action name
* @param $errno			the error number of the exception
*/

class SahanaIOException extends Exception{

	function __construct($msg,$mod = null,$act = null, $errno=0){
		global $global;
		$mod = ($mod!=null)?$mod:$global['module'];
		$act = ($act!=null)?$act:$global['action'];
		//$this->result = ($result!=null)?$result:REPORT_AND_ABORT;
		$msg = __CLASS__.": <b>$msg</b>, module : <b>$mod</b>, action : <b>$act</b>";
		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($msg,$errno);
	}
}

/** SahanaFileNotFoundException Signals that an attempt to open the file denoted by a specified pathname has failed.
* @param $msg			the message about the exception
* @param $file_path		the path of the file or file name
* @param $errno			the error number of the exception
*/


class SahanaFileNotFoundException extends Exception{

	function __construct($msg,$file_path=null,$errno=0){
		$msg = __CLASS__ . ": Could not find file ['$file_path'] : Exception thrown from {$this->file} on line {$this->line} : <b> $msg </b> \n";
		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($msg,$errno);
	}
}

/** SahanaFilePermissionDeniedException Signals that an attempt to open the file denoted by a specified pathname has failed due to permission.
* @param $msg			the message about the exception
* @param $file_path		the path of the file or file name
* @param $errno			the error number of the exception
*/

class SahanaFilePermissionDeniedException extends Exception{

	function __construct($msg,$file_path=null,$errno=0){
		$msg = __CLASS__ . ": Permission denied for ['$file_path'] : Exception thrown from {$this->file} on line {$this->line} : <b> $msg </b> \n";
		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($msg,$errno);
	}

}

/**
*NOTE : IOException class which you are looking for is not written in the above code then please write your own IOException class
*within above code snippet. When you are writing your own class please extends Exception class otherwise your are not able
*to throw an exception without a class object.
*/

/**End of IO Exception classes*/


/** SahanaAclNotFoundException Signals that an attempt to handle ACL and when it's failed.
* @param $msg			the message about the exception
* @param $mod			the module name
* @param $act			the module action name
* @param $errno			the error number of the exception
*/

class SahanaAclNotFoundException extends Exception{
	function __construct($msg,$mod=null,$act=null,$errno=0){
		global $global;
		$mod = ($mod!=null)?$mod:$global['module'];
		$act = ($act!=null)?$act:$global['action'];
		$msg = __CLASS__.": <b>$msg</b>, module : <b>$mod</b>, action : <b>$act</b>";
		if (!is_numeric($errno)) $errno = -1;
		parent::__construct($msg,$errno);
	}

}


/**Sahana Default Exception Handler
*Sets the default exception handler if an exception is not caught within a try/catch block.
*Execution will stop after the exception_handler is called.
* @param $exception_msg		the message about the exception.
* @param $display_error		call the diplay_errors function or not.
*/

function shn_sahana_exception_handler($exception_msg,$display_error=false){
	add_error("Uncaught Exception: ".$exception_msg->getMessage());
	if($display_error)
		display_errors("Oops. There is an exception ");
}



/**End of Exception library*/


/**TODO :
  * Database transactions rollback code will be commented due to unavalability of transaction suppport in
  * in php-mysql drivers.  When it supports please uncomment the code.
* */


/**
 * =======================================================================================
 * Previous exception handling code commented below due to unavalability of transaction suppport in php-mysql drivers
 * =======================================================================================
 */

//define("REPORT_AND_CONTINUE","RAC");
//define("REPORT_AND_ABORT","RAA");

//include_once($global['approot'].'inc/lib_log.inc');

//$global['submit_exceptions'] = array();

/**
 * Report an exception to the framework.
 *
 * @param SahanaException $exception The target exception.
 * @param array $extra_opts Any extra options.
 */
/*function report_exception($exception,array $extra_opts=null){
	var_dump($exception->getResult()==REPORT_AND_ABORT);
	global $global;
	if(isset($exception) && $exception->getResult()==REPORT_AND_ABORT){
		// roll back transactions
		$transCnt = $global['db']->transCnt;
		if($transCnt>0){
			$global['db']->RollbackTrans();
		}
	}
	echo "Pusing Exception"; echo "<pre>";var_dump($exception);echo "</pre>";
	$exception_list = &$global['exception_list'];
	array_push($exception_list,$exception);
	shn_log_event(null,_t("Exception occured."),$exception->getMessage(),ERROR,UNCLASSIFIED,null,$exception->getModule(),$exception->getAction(),null);
	var_dump($exception_list);
}*/

/*function report_exception_and_continue($exception,array $extra_opts){

}

function report_exception_and_abort($exception,array $extra_opts){

}*/


/**
 * The generic exception class where other custom exceptions can inherit from.
 *
 */

//class SahanaException{

	/**
	 * The user friendly message for this exception.
	 *
	 * @var String The user friendly message.
	 */
	//private $message;
	/**
	 * The module short code of the module which generated this exception.
	 *
	 * @var String The module short code of the module which the exception occured.
	 */
	//private $module;
	/**
	 * The action which generated this exception.
	 *
	 * @var String The action
	 */
	//private $action;
	/**
	 * The result of this exception, either of REPORT_AND_ABORT or REPORT_AND_CONTINUE.
	 *
	 * @var String The result
	 */
	//private $result;

	/**
	 * Return the user friendly message, for this exception. All messages should be localized.
	 *
	 * @return String Localized user friendly message.
	 */
	/*function getMessage(){
		return $this->message;
	}*/

	/**
	 * Return the module short code of the module which generated this exception.
	 *
	 * @return String The module short code of the module which generated this exception.
	 */
	/*function getModule(){
		return $this->module;
	}*/

	/**
	 * Return the action which generated this exception.
	 *
	 * @return String The action.
	 */
	/*function getAction(){
		return $this->action;
	}*/

	/**
	 * Return the result of this exception. There can be only two results.
	 * REPORT_AND_ABORT which will not display any page content but just an error message to the user.
	 * REPORT_AND_CONTINUE which will display a warning and the page content.
	 *
	 * @return String The result.
	 */
	/*function getResult(){
		return $this->result;
	}*/

	/**
	 * The constructor for SahanaException.
	 *
	 * @param String $msg The localized user friendly message for this exception.
	 * @param String $mod The module which generated the exception. Value is obtained from $global['module'] if not provided.
	 * @param String $act The action which generated the exception. Value is obtained form $global['action'] if not provided.
	 * @param String $result The result of the exception, should be one of REPORT_AND_CONTINUE or REPORT_AND_ABORT.
	 * @param array $extra_opts Any extra options for future customizations.
	 * @return SahanaException
	 */
	/*function SahanaException($msg,$mod = null,$act = null,$result = null,array $extra_opts = null){
		global $global;
		$this->message = $msg;
		$this->module = ($mod!=null)?$mod:$global['module'];
		$this->action = ($act!=null)?$act:$global['action'];
		$this->result = ($result!=null)?$result:REPORT_AND_ABORT;
	}
}*/


