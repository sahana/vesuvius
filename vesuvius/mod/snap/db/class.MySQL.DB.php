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
 * @version 1.3.0
 */

/**
 * MySQL specialization of the AbstractDB class.
 */

include_once 'class.abstract.DB.php' ;

if (!function_exists('mysql_real_escape_string'))
{
    function mysql_real_escape_string_replace_callback($c)
    {
        switch ($c[0])
        {
            case chr(0): return '\\0' ;
            case "\n": return '\\n' ;
            case "\r": return '\\r' ;
            case "\\": return '\\\\' ;
            case "'": return "\\'" ;
            case "\"": return '\\"' ;
            case chr(26): return '\\Z' ;
        }
    }

    /**
     * Versions of PHP prior to 4.3 do not implement the mysql_real_escape_string
     * interface.  In particular, Red Hat version 9.0's default PHP is
     * 4.2 so this is necessary for compatability reasons.
     *
     * @desc real escape string for versions of PHP prior to 4.3.
     * @param string the string to be quoted.
     * @param resource [optional] ignored, used only for compatibility.
     * @return string the MySQL quoted string.
     */

    function mysql_real_escape_string($theString, $theLink = NULL)
    {
        return preg_replace_callback('/[\n\r\\\\\'\"' . chr(26) . '\x00]/', "mysql_real_escape_string_replace_callback",
                                     $theString) ;
    }
}

class MySQLDB extends AbstractDB
{
    function db_specialization()
    {
        return 'MySQL' ;
    }

    /**
     * This is intended primarily as a mechanism for helping PostgreSQL handle
     * the MySQL "get_last_id" functionality.
     *
     * @access protected
     * @return reference to resource the query id of the last executed query.
     */

    function &getQueryid()
    {
        return $this->queryid ;
    }

    /**
     * @desc return the SQL query to describe the specified table.
     * @param string the name of the table.
     * @return array the result describing the table, one array element for each field in
     *         the table.  Returns FALSE if any error occurs.
     */

    function &describeTable($theTableName)
    {
        $theDescription = array() ;

        if (empty($this->dblink))
        {
            $this->connect();
        }

        if ($this->hasErrors())
        {
            return FALSE ;
        }

        $theSQL = sprintf('DESCRIBE `%s` ;', $theTableName) ;

        $theResult =
            $this->db_query(
                $theSQL,
                $this->dblink) ;

        if (!$theResult)
        {
            $this->return_error('Unable to perform the query <b>' . $theSQL . '</b>.');
            return FALSE ;
        }

        while($xxx = $this->db_fetch_array($theResult))
        {
            $theDescription[] = $xxx ;
        } ;

        $this->db_free_result($theResult) ;

        return $theDescription ;
    }

    /**
     * @desc return quoted identifier.
     * @param string identifier to be quoted.
     * @return string the quoted identifier
     */

    function &quoteIdentifier($theIdentifier)
    {
        $theIdentifier = "`" . $theIdentifier . "`" ;
        return $theIdentifier ;
    }

    /**
     * @desc return the description of the keys of the specified table.
     * @param string the name of the table.
     * @return array the result describing the table, one array element for each field in
     *         the table.  Returns FALSE if any error occurs.
     */

    function &showKeys($theTableName)
    {
        $theDescription = array() ;

        if (empty($this->dblink))
        {
            $this->connect();
        }

        if ($this->hasErrors())
        {
            return FALSE ;
        }

        $theSQL = sprintf('SHOW KEYS FROM `%s`', $theTableName) ;

        $theResult =
            $this->db_query(
                $theSQL,
                $this->dblink) ;

        if (!$theResult)
        {
            $this->return_error('Unable to perform the query <b>' . $theSQL . '</b>.');
            return FALSE ;
        }

        while($xxx = $this->db_fetch_array($theResult))
        {
            $theDescription[] = $xxx ;
        } ;

        $this->db_free_result($theResult) ;

        return $theDescription ;
    }

    /**
     * @desc return the list of tables in the current database.
     * @return array the names of the tables in the current database.
     */

    function &showTables()
    {
        $theTableNames = array() ;

        $theDBLink = $this->dblink;
        if (empty($theDBLink)) {
            $this->connect() ;
        } ;

        $theResult = $this->db_query('SHOW TABLES',$this->dblink) ;

        while ($theTableName =& $this->db_fetch_array($theResult))
        {
            $theTableNames[] = $theTableName[0] ;
        }

        $this->db_free_result($theResult) ;

        return $theTableNames ;
    }

    /**
     * @desc return the SQL query to create the specified table.
     * @param string the name of the table.
     * @return string the SQL query to create the table.
     */

    function &showCreateTable($theTableName)
    {
        $theDBLink = $this->dblink;
        if (empty($theDBLink))
        {
            $this->connect() ;
        } ;

        $theResult =
            $this->db_query( sprintf('SHOW CREATE TABLE `%s`', $theTableName), $this->dblink) ;

        $theCreateQuery = $this->db_fetch_array($theResult) ;

        $this->db_free_result($theResult) ;

        return $theCreateQuery[1] ;
    }

    /**
     * Abstract functions for database access.  Assumes that all MySQL database interfaces
     * are functionally available using the actual database.
     */

    function db_affected_rows($dblink)
    {
        return @mysql_affected_rows($dblink) ;
    }

    function db_close($dblink)
    {
        return @mysql_close($dblink) ;
    }

    function db_connect($dbhost, $dblogin, $dbpass)
    {
        return @mysql_pconnect($dbhost, $dblogin, $dbpass) ;
    }

    function db_data_seek($queryid, $row)
    {
        return @mysql_data_seek($queryid, $row) ;
    }

    function db_error()
    {
        return @mysql_error() ;
    }

    function db_fetch_array($queryid)
    {
        return mysql_fetch_array($queryid) ;
    }

    function db_fetch_assoc($queryid)
    {
        return @mysql_fetch_assoc($queryid) ;
    }

    function db_free_result($result)
    {
        return @mysql_free_result($result) ;
    }

    function db_insert_id($dblink, $theSequenceName = NULL)
    {
        return @mysql_insert_id($dblink) ;
    }

    function db_num_rows($queryid)
    {
        return @mysql_num_rows($queryid) ;
    }

    function db_query($sql, $dblink)
    {
        return @mysql_query($sql, $dblink) ;
    }

    function db_select($dbname, $dblink)
    {
        return @mysql_select_db($dbname, $dblink) ;
    }

    function db_real_escape_string($theString, $dblink)
    {
        return @mysql_real_escape_string($theString, $dblink) ;
    }

    /**
     * Checks to see whether or not the MySQL server supports transactions.
     *
     * @param      dblink, the link (if any) to the database, unused in this implementation.
     * @return     bool
     * @access     public
     */

    function serverHasTransaction($dblink)
    {
        $this->queryConstant('SHOW VARIABLES');

        if ($this->resultExist())
        {
            while ($xxx = $this->fetchRow())
            {
                if ($xxx['Variable_name'] == 'have_bdb' && $xxx['Value'] == 'YES')
                {
                    return true;
                }
                else if ($xxx['Variable_name'] == 'have_gemini' && $xxx['Value'] == 'YES')
                {
                    return true;
                }
                else if ($xxx['Variable_name'] == 'have_innodb' && $xxx['Value'] == 'YES')
                {
                    return true;
                }
            }
        }

        return false;

    } // end function

    /**
     * Constructor
     *
     * @param      String $dblogin, String $dbpass, String $dbname
     * @return     void
     * @access     public
     */

    function MySQLDB($dblogin, $dbpass, $dbname, $dbhost = null)
    {
        $this->AbstractDB($dblogin, $dbpass, $dbname, $dbhost) ;
    }
}