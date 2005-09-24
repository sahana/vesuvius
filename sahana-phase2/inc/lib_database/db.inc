<?php 
/* $Id: db.inc,v 1.1.1.1 2005-09-24 21:22:55 chamindra Exp $ */

/**
* Database Generic Function Library. Inspired by dotProject includes/db_connect.php
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @subpackage lib_database
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/** 
* Get the development tools
*/
if(defined(DB_DEVEL))
	define(DB_DEVEL,1);

#if(DB_DEVEL)
	require_once($global['approot'].'inc/lib_database/devel_tools.php');
	
/**
* Include the error container
*/
require_once($global['approot'].'inc/handler_errors.inc');

/**
* List of supported databases
*/

require_once($global['approot'].'conf/db/dbengine.list.inc');


/**
* controller
*/
// 1. Validate the configuration file
if(DB_DEVEL)
	echo "Validating the config file : ";

if(!validateconf()){
	/* @todo Handle the Errors in generic error handler */
	display_errors(true);	
}
if(DB_DEVEL)
	echo echo_done();

// 2. Include the correct database abstraction layer
require_once($global['approot'].'inc/lib_database/db_'.$conf['dbal_lib_name'].'.inc');
if(DB_DEVEL)
	echo "Included the abstaction library : ".echo_done();

// 3. make the database connection
if(DB_DEVEL)
	echo "Connection  : ";
if(! db_connect()){ 
        display_errors(true);
}
if(DB_DEVEL)
	echo echo_done();

/**
* Include the DBQuery Class
*/
require_once($global['approot'].'inc/lib_database/db_query.inc');

/**
* validate the configure file
*/
function validateconf()
{
	//Check the existance of the db library
	global $conf;
	
	//No Errors
	$return = true;

	if(!is_dir($global['approot'].'3rdparty/'.$conf['dbal_lib_name'])){
		/* @todo I18N on error messages */
		add_error("The given database abtraction library does not exists");
		$return = false;
	}
	
	/* Reconsider
    //Check the engine is supported or not
	if(!is_engine($conf['db_engine'])){
		add_error("The given Database Engine does not exists");
		$return = false;
	}
	*/
	return $return;
	
}


/**
* Returns the first field (NOTE: sql should only contain one field )
* @param string The SQL query
* @return The value returned in the query or null if the query failed.
* @note modifications from original : naming, error handling
*/
function shn_db_load_result( $sql ) {
	$cur = _shn_db_exec( $sql );
    //@todo Need Error Handling
	$ret = null;
	if ($row = _shn_db_fetch_row( $cur )) {
		$ret = $row[0];
	}
	_shn_db_free_result( $cur );
	return $ret;
}

/**
* Loads the first row of a query into an object
* @param string The SQL query
* @param object The address of variable
* @note modifications from original : naming, error handling
*/
function shn_db_load_object( $sql, &$object, $bindAll=false , $strip = true) {
	if ($object != null) {
		$hash = array();
		if( !_shn_db_load_hash( $sql, $hash ) ) {
			return false;
		}
		shn_bindhash2object( $hash, $object, null, $strip, $bindAll );
		return true;
	} else {
		$cur = _shn_db_exec( $sql );
        //@todo Need Error Handling
		if ($object = _shn_db_fetch_object( $cur )) {
			_shn_db_free_result( $cur );
			return true;
		} else {
			$object = null;
			return false;
		}
	}
}

/**
* This global function return a result row as an associative array 
*
* @param string The SQL query
* @param array An array for the result to be return in
* @return <b>True</b> is the query was successful, <b>False</b> otherwise
*/
function shn_db_load_assoc( $sql, &$hash ) {
	$cur = _shn_db_exec( $sql );
    //@todo Need Error Handling
	$hash = _shn_db_fetch_assoc( $cur );
	_shn_db_free_result( $cur );
	if ($hash == false) {
		return false;
	} else {
		return true;
	}
}

/**
* Document::db_loadHashList()
*
* { Description }
*
* @param string $index
*/
function shn_db_load_hash_list( $sql, $index='' ) {
	$cur = _shn_db_exec( $sql );
	$cur or exit( db_error() );
	$hashlist = array();
	while ($hash = db_fetch_array( $cur )) {
		$hashlist[$hash[$index ? $index : 0]] = $index ? $hash : $hash[1];
	}
	_shn_db_free_result( $cur );
	return $hashlist;
}

/**
* Document::db_loadList()
*
* { Description }
*
* @param [type] $maxrows
*/
function shn_db_load_list( $sql, $maxrows=NULL ) {
	/*GLOBAL $AppUI;
	if (!($cur = _shn_db_exec( $sql ))) {;
		$AppUI->setMsg( db_error(), UI_MSG_ERROR );
		return false;
	}*/
	$list = array();
	$cnt = 0;
	while ($hash = db_fetch_assoc( $cur )) {
		$list[] = $hash;
		if( $maxrows && $maxrows == $cnt++ ) {
			break;
		}
	}
	_shn_db_free_result( $cur );
	return $list;
}

/**
* Document::db_loadColumn()
*
* { Description }
*
* @param [type] $maxrows
*/
function shn_db_load_column( $sql, $maxrows=NULL ) {
	/*GLOBAL $AppUI;
	if (!($cur = _shn_db_exec( $sql ))) {;
		$AppUI->setMsg( db_error(), UI_MSG_ERROR );
		return false;
	}*/
	$list = array();
	$cnt = 0;
	$row_index = null;
	while ($row = _shn_db_fetch_row( $cur )) {
		if (! isset($row_index)) {
			if (isset($row[0])) {
				$row_index = 0;
			} else {
				$row_indices = array_keys($row);
				$row_index = $row_indices[0];
			}
		}
		$list[] = $row[$row_index];
		if( $maxrows && $maxrows == $cnt++ ) {
			break;
		}
	}
	_shn_db_free_result( $cur );
	return $list;
}

/* return an array of objects from a SQL SELECT query
 * class must implement the Load() factory, see examples in Webo classes
 * @note to optimize request, only select object oids in $sql
 */
function shn_db_load_object_list( $sql, $object, $maxrows = NULL ) {
	$cur = _shn_db_exec( $sql );
	if (!$cur) {
		die( "db_loadObjectList : " . db_error() );
	}
	$list = array();
	$cnt = 0;
	$row_index = null;
	while ($row = db_fetch_array( $cur )) {
		if (! isset($row_index)) {
			if (isset($row[0]))
				$row_index = 0;
			else {
				$row_indices = array_keys($row);
				$row_index = $row_indices[0];
			}
		}
		$object->load( $row[$row_index] );
		$list[] = $object;
		if( $maxrows && $maxrows == $cnt++ ) {
			break;
		}
	}
	_shn_db_free_result( $cur );
	return $list;
}


/**
* Document::db_insertArray()
*
* { Description }
*
* @param [type] $verbose
*/
function shn_db_insert_array( $table, &$hash, $verbose=false ) {
	$fmtsql = "insert into $table ( %s ) values( %s ) ";
	foreach ($hash as $k => $v) {
		if (is_array($v) or is_object($v) or $v == NULL) {
			continue;
		}
		$fields[] = $k;
		$values[] = "'" . db_escape(strip_tags( $v )) . "'";
	}
	$sql = sprintf( $fmtsql, implode( ",", $fields ) ,  implode( ",", $values ) );

	($verbose) && print "$sql<br />\n";

	if (!_shn_db_exec( $sql )) {
		return false;
	}
	$id = db_insert_id();
	return true;
}

/**
* Document::db_updateArray()
*
* { Description }
*
* @param [type] $verbose
*/
function shn_db_update_array( $table, &$hash, $keyName, $verbose=false ) {
	$fmtsql = "UPDATE $table SET %s WHERE %s";
	foreach ($hash as $k => $v) {
		if( is_array($v) or is_object($v) or $k[0] == '_' ) // internal or NA field
			continue;

		if( $k == $keyName ) { // PK not to be updated
			$where = "$keyName='" . db_escape( $v ) . "'";
			continue;
		}
		if ($v == '') {
			$val = 'NULL';
		} else {
			$val = "'" . db_escape(strip_tags( $v )) . "'";
		}
		$tmp[] = "$k=$val";
	}
	$sql = sprintf( $fmtsql, implode( ",", $tmp ) , $where );
	($verbose) && print "$sql<br />\n";
	$ret = _shn_db_exec( $sql );
	return $ret;
}

/**
* Document::db_delete()
*
* { Description }
*
*/
function shn_db_delete( $table, $keyName, $keyValue ) {
	$keyName = db_escape( $keyName );
	$keyValue = db_escape( $keyValue );
	$ret = _shn_db_exec( "DELETE FROM $table WHERE $keyName='$keyValue'" );
	return $ret;
}


/**
* Document::db_insertObject()
*
* { Description }
*
* @param [type] $keyName
* @param [type] $verbose
*/
function shn_db_insert_object( $table, &$object, $keyName = NULL, $verbose=false ) {
	$fmtsql = "INSERT INTO $table ( %s ) VALUES ( %s ) ";
	foreach (get_object_vars( $object ) as $k => $v) {
		if (is_array($v) or is_object($v) or $v == NULL) {
			continue;
		}
		if ($k[0] == '_') { // internal field
			continue;
		}
		$fields[] = $k;
		//$values[] = "'" . db_escape(htmlentities(strip_tags( $v ), ENT_COMPAT ,$locale_char_set)) . "'";
		$values[] = "'" . db_escape(strip_tags( $v )) . "'";
	}
	$sql = sprintf( $fmtsql, implode( ",", $fields ) ,  implode( ",", $values ) );
	($verbose) && print "$sql<br />\n";
	if (!_shn_db_exec( $sql )) {
		return false;
	}
	$id = db_insert_id();
	($verbose) && print "id=[$id]<br />\n";
	if ($keyName && $id)
		$object->$keyName = $id;
	return true;
}

/**
* Document::db_updateObject()
*
* { Description }
*
* @param [type] $updateNulls
*/
function shn_db_update_object( $table, &$object, $keyName, $updateNulls=true ) {
	$fmtsql = "UPDATE `$table` SET %s WHERE %s";
	foreach (get_object_vars( $object ) as $k => $v) {
		if( is_array($v) or is_object($v) or $k[0] == '_' ) { // internal or NA field
			continue;
		}
		if( $k == $keyName ) { // PK not to be updated
			$where = "$keyName='" . db_escape( $v ) . "'";
			continue;
		}
		if ($v === NULL && !$updateNulls) {
			continue;
		}
		if( $v == '' ) {
			$val = "''";
		} else {
			$val = "'" . db_escape(strip_tags( $v )). "'";
		}
		$tmp[] = "$k=$val";
	}
	if (count ($tmp)) {
		$sql = sprintf( $fmtsql, implode( ",", $tmp ) , $where );
		return _shn_db_exec( $sql );
	} else {
		return true;
	}
}

/**
* Document::db_dateConvert()
*
* { Description }
*
*/
function shn_db_date_convert( $src, &$dest, $srcFmt ) {
	$result = strtotime( $src );
	$dest = $result;
	return ( $result != 0 );
}

/**
* Document::db_datetime()
*
* { Description }
*
* @param [type] $timestamp
*/
function shn_db_datetime( $timestamp = NULL ) {
	if (!$timestamp) {
		return NULL;
	}
	if (is_object($timestamp)) {
		return $timestamp->toString( '%Y-%m-%d %H:%M:%S');
	} else {
		return strftime( '%Y-%m-%d %H:%M:%S', $timestamp );
	}
}

/**
* Document::db_dateTime2locale()
*
* { Description }
*
*/
function shn_db_datetime2locale( $dateTime, $format ) {
	if (intval( $dateTime)) {
		$date = new CDate( $dateTime );
		return $date->format( $format );
	} else {
		return null;
	}
}

/*
* copy the hash array content into the object as properties
* only existing properties of object are filled. when undefined in hash, properties wont be deleted
* @param array the input array
* @param obj byref the object to fill of any class
* @param string
* @param boolean
* @param boolean
*/
function shn_bindhash2object( $hash, &$obj, $prefix=NULL, $checkSlashes=true, $bindAll=false ) {
	is_array( $hash ) or die( "bindHashToObject : hash expected" );
	is_object( $obj ) or die( "bindHashToObject : object expected" );

	if ($bindAll) {
		foreach ($hash as $k => $v) {
			$obj->$k = ($checkSlashes && get_magic_quotes_gpc()) ? stripslashes( $hash[$k] ) : $hash[$k];
		}
	} else if ($prefix) {
		foreach (get_object_vars($obj) as $k => $v) {
			if (isset($hash[$prefix . $k ])) {
				$obj->$k = ($checkSlashes && get_magic_quotes_gpc()) ? stripslashes( $hash[$k] ) : $hash[$k];
			}
		}
	} else {
		foreach (get_object_vars($obj) as $k => $v) {
			if (isset($hash[$k])) {
				$obj->$k = ($checkSlashes && get_magic_quotes_gpc()) ? stripslashes( $hash[$k] ) : $hash[$k];
			}
		}
	}
	//echo "obj="; print_r($obj); exit;
}
?>
