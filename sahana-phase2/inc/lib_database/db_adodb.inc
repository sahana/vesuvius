<?
/**
* Bridge functions that bridges between db generic functions library and database abstraction layer. Inspired by Leo West's WEBO project.
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @subpackage lib_database
* @author     Janaka Wicksramasinghe <janaka@opensource.lk>
* @version    $Id: db_adodb.inc,v 1.1.1.1 2005-09-24 21:22:52 chamindra Exp $
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

//Include the ADOdb Library
require_once($global['approot'].'3rdparty/adodb/adodb.inc.php');

//Exception handling <-- Hell NO, OOP sucks
#include("inc/lib_database/db_libs/adodb/adodb-exceptions.inc.php");
/**
* Directing the session to the database
*/

if($session_writer == 'database'){
        $ADODB_SESSION_DRIVER=$conf['db_engine'];
        $ADODB_SESSION_CONNECT=$conf['db_host'];
        $ADODB_SESSION_USER =$conf['db_user'];
        $ADODB_SESSION_PWD =$conf['db_pass'];
        $ADODB_SESSION_DB =$conf['db_name'];
        $ADODB_SESSION_TBL = 'core_sessions';
        require_once('3rdparty/adodb/session/adodb-session.php');
}

$db = null;

function _shn_db_connect()
{
        global $db;
	global $conf;

        $return = true;

        $db = NewADOConnection($conf['db_engine']);

        if(! @ $db->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_port']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name'])){
                /* @todo use a generic error container */
                /* @todo I18N */
                add_error("Can not connect to the Database");
                $return = false;
        }
	if($conf['enable_monitor_sql'])
		$db->LogSQL();
        return $return;
}

function _shn_db_error() {
        global $db;
	if (! is_object($db))
	  add_error_debug(__FILE__,__LINE__, 0, "Database object does not exist");
	return $db->ErrorMsg();
}

function _shn_db_errno() {
        global $db;
	if (! is_object($db))
	  add_error_debug(__FILE__,__LINE__, 0, "Database object does not exist");
	return $db->ErrorNo();
}

function _shn_db_insert_id() {
        global $db;
	if (! is_object($db))
	  add_error_debug(__FILE__,__LINE__, 0, "Database object does not exist");
	return $db->Insert_ID();
}

function _shn_db_exec( $sql ) {
        global $db,$enable_cache,$cache_dir;

	if (! is_object($db))
	  add_error_debug(__FILE__,__LINE__, 0, "Database object does not exist");
	/* Adding the caching ability */
	if($enable_cache)
		$qid = $db->Execute( $sql );
	else
		$qid = $db->Execute( $sql );
	add_error_debug(__FILE__, __LINE__, 10, $sql);
	if ($msg = db_error())
        {
                #global $AppUI;
                add_error_debug(__FILE__, __LINE__, 0, "Error executing: <pre>$sql</pre>");
		// Useless statement, but it is being executed only on error, 
		// and it stops infinite loop.
		$db->Execute( $sql );
		if (!db_error())
			echo '<script language="JavaScript"> location.reload(); </script>';
        }
        if ( ! $qid && preg_match('/^\<select\>/i', $sql) )
	  add_error_debug(__FILE__, __LINE__, 0, $sql);
	return $qid;
}

function _shn_db_free_result($cur ) {
        // TODO
        //	mysql_free_result( $cur );
        // Maybe it's done my Adodb
	if (! is_object($cur))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_free_result");
        $cur->Close();
}

function _shn_db_num_rows( $qid ) {
	if (! is_object($qid))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_num_rows");
	return $qid->RecordCount();
        //return $db->Affected_Rows();
}

function _shn_db_fetch_row( &$qid ) {
	if (! is_object($qid))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_fetch_row");
	return $qid->FetchRow();
}

function _shn_db_fetch_assoc( &$qid ) {
	if (! is_object($qid))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_fetch_assoc");
        return $qid->FetchRow();
}

function _shn_db_fetch_array( &$qid  ) {
	if (! is_object($qid))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_fetch_array");
        $result = $qid->FetchRow();
	// Ensure there are numerics in the result.
	if ($result && ! isset($result[0])) {
	  $ak = array_keys($result);
	  foreach ($ak as $k => $v) {
	    $result[$k] = $result[$v];
	  }
	}
	return $result;
}

function _shn_db_fetch_object( $qid  ) {
	if (! is_object($qid))
	  add_error_debug(__FILE__, __LINE__, 0, "Invalid object passed to db_fetch_object");
	return $qid->FetchNextObject(false);
}

function _shn_db_escape( $str ) {
        global $db;
	return substr($db->qstr( $str ), 1, -1);
}

function _shn_db_version() {
        return "ADODB";
}

function _shn_db_unix2dateTime( $time ) {
        global $db;
        return $db->DBDate($time);
}

function _shn_db_dateTime2unix( $time ) {
        global $db;

        return $db->UnixDate($time);

        // TODO - check if it's used anywhere...
//	if ($time == '0000-00-00 00:00:00') {
//		return -1;
//	}
}
?>
