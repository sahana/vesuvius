<?
/**
 * @name         Exception Library
 * @version      1.0
 * @package      framework
 * @author       Ravith Botejue. <ravithb@yahoo.com>
 * @author       Prabath Kumarasinghe <prabath@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */



if(file_exists($global['approot'].'conf/sahana.conf')) {
	require_once($global['approot'].'conf/sahana.conf');
}
require_once($global['approot'].'inc/lib_locale/gettext.inc');
require_once($global['approot'].'inc/lib_errors.inc');


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


define("REPORT_AND_CONTINUE","RAC");
define("REPORT_AND_ABORT","RAA");


