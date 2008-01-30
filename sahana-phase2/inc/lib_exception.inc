<?php
define("REPORT_AND_CONTINUE","RAC");
define("REPORT_AND_ABORT","RAA");

include_once($global['approot'].'inc/lib_log.inc');

$global['submit_exceptions'] = array();

/**
 * Report an exception to the framework.
 *
 * @param SahanaException $exception The target exception.
 * @param array $extra_opts Any extra options.
 */
function report_exception($exception,array $extra_opts=null){
	//var_dump($exception->getResult()==REPORT_AND_ABORT);
	global $global;
	if(isset($exception) && $exception->getResult()==REPORT_AND_ABORT){
		// roll back transactions
		$transCnt = $global['db']->transCnt;
		if($transCnt>0){
			$global['db']->RollbackTrans();
		}
	}
	//echo "Pusing Exception"; echo "<pre>";var_dump($exception);echo "</pre>";
	$exception_list = &$global['exception_list'];
	array_push($exception_list,$exception);
	shn_log_event(null,_t("Exception occured."),$exception->getMessage(),ERROR,UNCLASSIFIED,null,$exception->getModule(),$exception->getAction(),null);
	//var_dump($exception_list);
}

/*function report_exception_and_continue($exception,array $extra_opts){

}

function report_exception_and_abort($exception,array $extra_opts){

}*/


/**
 * The generic exception class where other custom exceptions can inherit from.
 *
 */
class SahanaException{

	/**
	 * The user friendly message for this exception.
	 *
	 * @var String The user friendly message.
	 */
	private $message;
	/**
	 * The module short code of the module which generated this exception.
	 *
	 * @var String The module short code of the module which the exception occured.
	 */
	private $module;
	/**
	 * The action which generated this exception.
	 *
	 * @var String The action
	 */
	private $action;
	/**
	 * The result of this exception, either of REPORT_AND_ABORT or REPORT_AND_CONTINUE.
	 *
	 * @var String The result
	 */
	private $result;

	/**
	 * Return the user friendly message, for this exception. All messages should be localized.
	 *
	 * @return String Localized user friendly message.
	 */
	function getMessage(){
		return $this->message;
	}

	/**
	 * Return the module short code of the module which generated this exception.
	 *
	 * @return String The module short code of the module which generated this exception.
	 */
	function getModule(){
		return $this->module;
	}

	/**
	 * Return the action which generated this exception.
	 *
	 * @return String The action.
	 */
	function getAction(){
		return $this->action;
	}

	/**
	 * Return the result of this exception. There can be only two results.
	 * REPORT_AND_ABORT which will not display any page content but just an error message to the user.
	 * REPORT_AND_CONTINUE which will display a warning and the page content.
	 *
	 * @return String The result.
	 */
	function getResult(){
		return $this->result;
	}

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
	function SahanaException($msg,$mod = null,$act = null,$result = null,array $extra_opts = null){
		global $global;
		$this->message = $msg;
		$this->module = ($mod!=null)?$mod:$global['module'];
		$this->action = ($act!=null)?$act:$global['action'];
		$this->result = ($result!=null)?$result:REPORT_AND_ABORT;
	}
}
?>
