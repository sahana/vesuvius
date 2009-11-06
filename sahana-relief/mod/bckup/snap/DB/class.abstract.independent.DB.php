<?php
/**
 * @author Dick Munroe <munroe@csworks.com>
 * @copyright copyright @ 2006 by Dick Munroe, Cottage Software Works, Inc.
 *
 * @license http://www.csworks.com/publications/ModifiedNetBSD.html
 *
 * Copyright (c) 2006 Dick Munroe (munroe@csworks.com), Cottage Software Works, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by Dick Munroe
 *        (munroe@csworks.com) of Cottage Software Works (www.csworks.com).
 * 4. Neither the name of Cottage Software Works, Inc. nor the names of its
 *    developers may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY COTTAGE SOFTWARE WORKS, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @version 1.1.0
 *
 */

/**
 * Encapsulate all the database independent abstract interfaces.
 */

class AbstractIndependentDB
{
    /*
     * Abstract interfaces for higher level functions.
     */

    function &getQueryid()
    {
        trigger_error("getQueryid method must be overridden", E_USER_ERROR) ;
    }

    function &describeTable($theTableName)
    {
        trigger_error("describeTable method must be overridden", E_USER_ERROR) ;
    }

    function &quoteIdentifier($theIdentifier)
    {
        trigger_error("quoteIdentifier methot must be overridden", E_USER_ERROR) ;
    }

    function &showKeys($theTableName)
    {
        trigger_error("showKeys method must be overridden", E_USER_ERROR) ;
    }

    function &showTables()
    {
        trigger_error("showTables method must be overridden", E_USER_ERROR) ;
    }

    function &showCreateTable($theTableName)
    {
        trigger_error("showCreateTable method must be overridden", E_USER_ERROR) ;
    }

    function db_specialization()
    {
        trigger_error("db_specialization method must be overridden", E_USER_ERROR) ;
    }

    /**
     * Abstract functions for database access.  Assumes that all MySQL database interfaces
     * are functionally available using the actual database.
     */

    /**
     * @access protected
     * @desc database specific interface to return the number of rows affected by the last query.
     * @param mixed $dblink The internal linkage from php to the database.
     * @return integer the number of rows affected.  If the underlying database does not support
     *                 this functionality, then NULL is returned.
     */

    function db_affected_rows($dblink)
    {
        trigger_error("db_affected_rows method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to close the connection to the database.
     * @param mixed $dblink The internal linkage from php to the database.
     * @return mixed the status of the close operation.  The return must evaluate
     *               to true if the close has succeeded, false otherwise.  If the
     *               underlying database does not support this functionality, then
     *               TRUE shoule be returned.
     */

    function db_close($dblink)
    {
        trigger_error("db_close method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to establish a connection to a database.
     * @param string $dbhost The host name on which the database resides.
     * @param string $dblogin The login name to access the database.
     * @param string $dbpass The password to access the database.
     * @return mixed the status of the connect operation.  The return must evaluate
     *               to true if the connect has succeeded, false otherwise.
     */

    function db_connect($dbhost, $dblogin, $dbpass)
    {
        trigger_error("db_connect method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to move the cursor within a query.
     * @param string $queryid The query results.
     * @param string $row The row to be moved to.
     * @return mixed the status of the seek operation.  The return must evaluate
     *               to true if the seek has succeeded, false otherwise.
     */

    function db_data_seek($queryid, $row)
    {
        trigger_error("db_data_seek method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to return error information.
     * @return string the error information associated with the last
     *                operation.
     */

    function db_error()
    {
        trigger_error("db_error method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to return a row from a query as an associative array.
     * @param resource $queryid the results of a query.
     * @return mixed an associative array with 1 element for each field.
     */

    function db_fetch_assoc($queryid)
    {
        trigger_error("db_fetch_assoc method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to return a row from a query as an array (both indexed and
     *       associative.
     * @param resource $queryid the results of a query.
     * @return mixed as both an associative and indexed array with 1 element for each field.
     */

    function db_fetch_array($queryid)
    {
        trigger_error("db_fetch_array method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to free memory associated with a query.
     * @param resource $results the results of a query.
     * @return mixed the status of the free operation.  If it succeeded, the return value
     *               must evaluate to true.
     */

    function db_free_result($result)
    {
        trigger_error("db_free_result method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to return the last "unique id" inserted.
     * @param resource $dblink the connection to the database.
     * @return mixed the last inserted ID.  This operation is specific to MySQL and
     *               may not be emulatable on other databases.
     */

    function db_insert_id($dblink)
    {
        trigger_error("db_insert_id method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to return the number of rows in the last query.
     * @param resource $queryid.
     * @return mixed the number of rows in the results of the query.
     */

    function db_num_rows($queryid)
    {
        trigger_error("db_num_rows method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to perform an SQL query.
     * @param string $sql The request to be performed.
     * @param resource $dbline the link to the database.
     * @return mixed A query result.  If the query succeeded, the result
     *               of the query must evaluate to true.
     */

    function db_query($sql, $dblink)
    {
        trigger_error("db_query method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to quote a string for use in an SQL query.
     * @param string $theString the string to be quoted.
     * @param resource $dblink the link to the database.
     * @return mixed A quoted string.
     */

    function db_real_escape_string($theString, $dblink)
    {
        trigger_error("db_real_escape_string method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc database specific interface to select a database for use.
     * @param string $dbname the database to be used.
     * @param resource $dblink the link to the dbhost on which the database resided.
     * @return boolean true if the select succeeds, false otherwise.
     */

    function db_select($dbname, $dblink)
    {
        trigger_error("db_select method must be overridden", E_USER_ERROR) ;
    }

    /**
     * @access protected
     * @desc data base specific interface to determine if a server supports transactions.
     * @param resource $dblink the link to the dbhost on which the database resides.
     * @return boolean true if the server supports transactions, false otherwise.
     */

    function serverHasTransaction($dblink)
    {
        trigger_error("serverHasTransaction method must be overidden", E_USER_ERROR) ;
    }
}