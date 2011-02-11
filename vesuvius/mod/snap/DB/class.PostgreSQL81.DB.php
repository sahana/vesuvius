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
 * @version 1.0.0
 */

/**
 * PostgreSQL 8.1 specialization of the AbstractDB class.
 */

include_once 'class.abstract.DB.php' ;

class PostgreSQL81DB extends AbstractDB
{
    /**
     * @desc Calculate the selector in the information schema given a [partially qualified] table name.
     * @param string the name of the table.
     * @return string the sql selector in the information schema for the specified table.
     */

    function &_tableSelector(&$theTableName, $theISTableName = '')
    {
        $zzz = $theISTableName . '.' ;
        if ($zzz == '.')
        {
            $zzz = '' ;
        }

        $xxx = explode('.', $theTableName) ;

        $xxx = array_reverse($xxx) ;

        $yyy = array("%stable_name = '%s'", "%stable_schema = '%s'", "%stable_catalog = '%s'") ;

        $theWhere = '' ;

        for ($i = 0 ; $i < count($xxx); $i++)
        {
            $theWhere .= ' AND ' . sprintf($yyy[$i], addcslashes($zzz, "'\\"), addcslashes($xxx[$i], "'\\")) ;
        }

        $theWhere = substr($theWhere, 5) ;

        return $theWhere ;
    }

    /**
     * @desc return the SQL query to create the specified table.
     * @param string the name of the table.
     * @return string the SQL query to create the table.
     */

    function &describeTable($theTableName)
    {
        if (empty($this->dblink))
        {
            $this->connect();
        }

        if ($this->hasErrors())
        {
            return FALSE ;
        }


        $theWhere = $this->_tableSelector($theTableName) ;

        $theSQL =
            sprintf(
                "select * from information_schema.columns where %s order by columns.ordinal_position ;",
                $theWhere) ;

        $theColumnsResult =
            $this->db_query(
                $theSQL,
                $this->dblink) ;

        if ($theColumnsResult === false)
        {
            $this->return_error("Can't execute query: $theSQL") ;
            return FALSE ;
        }

        $theTableName = explode('.', $theTableName) ;
        $theTableName = array_reverse($theTableName) ;
        $theTableName = $theTableName[0] ;

        $theColumns = array() ;

        while ($theColumn = $this->db_fetch_assoc($theColumnsResult))
        {
            $theSQL =
                sprintf(
                    "select * from information_schema.key_column_usage where key_column_usage.column_name = '%s' ;",
                    $theColumn['column_name']) ;

            $theKeyUsageResult =
                $this->db_query(
                    $theSQL,
                    $this->dblink) ;

            if ($theKeyUsageResult)
            {
                $theKey = $this->db_fetch_assoc($theKeyUsageResult) ;

                if (! $theKey)
                {
                    $theKey = array() ;
                }
            }
            else
            {
                $theKey = array() ;
            }

            $this->db_free_result($theKeyUsageResult) ;

            if ($theKey)
            {
                $theSQL =
                    sprintf(
                        "select * from information_schema.table_constraints where table_constraints.constraint_name = '%s' ;",
                        $theKey['constraint_name']) ;

                $theConstraintResult =
                    $this->db_query(
                        $theSQL,
                        $this->dblink) ;

                if ($theConstraintResult)
                {
                    $theConstraint = $this->db_fetch_assoc($theConstraintResult) ;

                    if (! $theConstraint)
                    {
                        $theConstraint = array() ;
                    }
                }
                else
                {
                    $theConstraint = array() ;
                }

                $this->db_free_result($theConstraintResult) ;
            }
            else
            {
                $theConstraint = array() ;
            }

            $xxx = array() ;
            $xxx['Field'] = $theColumn['column_name'] ;
            $xxx['Type'] = $theColumn['data_type'] ;
            if (is_numeric($theColumn['character_maximum_length']))
            {
                $xxx['Type'] .= sprintf('(%d)', $theColumn['character_maximum_length']) ;
            }
            $xxx['Null'] = $theColumn['is_nullable'] ;
            if (empty($theConstraint['constraint_type']))
            {
                $xxx['Key'] = NULL ;
            }
            else if ($theConstraint['constraint_type'] == 'PRIMARY KEY')
            {
                $xxx['Key'] = 'PRI' ;
                $theSQL =
                    sprintf(
                        "SELECT pg_get_serial_sequence('%s', '%s');",
                        $theTableName,
                        $theColumn['column_name']) ;

                $theSequenceResult =
                    $this->db_query(
                        $theSQL,
                        $this->dblink) ;

                if ($theSequenceResult)
                {
                    $theSequence = $this->db_fetch_array($theSequenceResult) ;
                    $xxx['Sequence'] = $theSequence[0] ;
                }

                $this->db_free_result($theSequenceResult) ;
            }
            else
            {
                die("Unknown Constraint Type: " . $theConstraint['constraint_type']) ;
            }
            $xxx['Default'] = $theColumn['column_default'] ;
            if (preg_match('/^nextval/', $theColumn['column_default']) == 1)
            {
                $xxx['Extra'] = 'auto_increment' ;
            }
            else
            {
                $xxx['Extra'] = NULL ;
            }

            $theColumns[] = $xxx ;
        }

        $this->db_free_result($theColumnsResult) ;

        return $theColumns ;
    }

    /**
     * @desc return quoted identifier.
     * @param string identifier to be quoted.
     * @return string the quoted identifier
     */

    function &quoteIdentifier($theIdentifier)
    {
        $theIdentifier = "\"" . $theIdentifier . "\"" ;
        return $theIdentifier ;
    }

    /**
     * @desc return the SQL query to create the specified table.
     * @param string the name of the table.
     * @return string the SQL query to create the table.
     */

    function &showKeys($theTableName)
    {
        if (empty($this->dblink))
        {
            $this->connect();
        }

        if ($this->hasErrors())
        {
            return FALSE ;
        }

        $xxx = explode('.', $theTableName) ;

        $xxx = array_reverse($xxx) ;

        $theTableName = $xxx[0] ;

        $theSQL =
            sprintf(
                "select * from pg_index where pg_index.indrelid = (select oid from pg_class where pg_class.relname = '%s') ;",
                $theTableName) ;

        $theIndexResult =
            $this->db_query(
                $theSQL,
                $this->dblink) ;

        if ($theIndexResult === FALSE)
        {
            $this->return_error("Can't execute query: $theSQL") ;
            return FALSE ;
        }

        $theKeys = array() ;

        while ($theIndex = $this->db_fetch_assoc($theIndexResult))
        {
            $theSQL =
                sprintf(
                    "select * from pg_class where pg_class.oid = %d ;",
                    $theIndex['indexrelid']) ;

            $theKeyNameResult =
                $this->db_query(
                    $theSQL,
                    $this->dblink) ;

            if ($theKeyNameResult === FALSE)
            {
                $this->return_error("Can't execute query: $theSQL") ;
                return FALSE ;
            }

            $theKeyName = $this->db_fetch_assoc($theKeyNameResult) ;

            $this->db_free_result($theKeyNameResult) ;

            $theSQL =
                sprintf(
                    "select * from pg_attribute where pg_attribute.attrelid = %d ;",
                    $theIndex['indexrelid']) ;

            $theAttributeResult =
                $this->db_query(
                    $theSQL,
                    $this->dblink) ;

            if ($theAttributeResult === FALSE)
            {
                $this->return_error("Can't execute query: $theSQL") ;
                return FALSE ;
            }

            /*
             * Sinces keys can span columns, I'm not real sure what to do.  For now, just assume
             * one key per column.
             */

            $theFieldIndex = 0 ;

            while ($theAttribute = $this->db_fetch_assoc($theAttributeResult))
            {
                $xxx = array() ;

                $xxx['Table'] = $theTableName ;
                if ($theIndex['indisunique'] == 't')
                {
                    $xxx['Non_unique'] = 0 ;

                    $theSQL =
                        sprintf(
                            "SELECT pg_get_serial_sequence('%s', '%s');",
                            $theTableName,
                            $theAttribute['attname']) ;

                    $theSequenceResult =
                        $this->db_query(
                            $theSQL,
                            $this->dblink) ;

                    if ($theSequenceResult)
                    {
                        $theSequence = $this->db_fetch_array($theSequenceResult) ;
                        $xxx['Sequence'] = $theSequence[0] ;
                    }

                    $this->db_free_result($theSequenceResult) ;
                }
                else
                {
                    $xxx['Non_unique'] = 1 ;
                }
                if ($theIndex['indisprimary'] == 't')
                {
                    $xxx['Key_name'] = 'PRIMARY' ;
                }
                else
                {
                    $xxx['Key_name'] = $theKeyName['relname'] ;
                }
                $xxx['Seq_in_index'] = $theFieldIndex ;
                $xxx['Column_name'] = $theAttribute['attname'] ;
                $xxx['Collation'] = 'A' ;       // Assume everything sorts in Ascending order.
                $xxx['Cardinality'] = NULL ;    // Assume that we don't need the number of entries for the key.
                $xxx['Sub_part'] = NULL ;       // Assume that the entire column is indexed.
                $xxx['Packed'] = NULL ;         // Assume that the column is not packed.
                if ($theAttribute['attnotnull'] == 'f')
                {
                    $xxx['Null'] = '' ;
                }
                else
                {
                    $xxx['Null'] = 'YES' ;
                }
                $xxx['Index_type'] = 'BTREE' ;  // Assum that the index is a BTREE ;
                $xxx['Comment'] = '' ;          // Assume that there is no comment.

                $theFieldIndex++ ;

                $theKeys[] = $xxx ;
            }

            $this->db_free_result($theAttributeResult) ;
        }

        $this->db_free_result($theIndexResult) ;

        return $theKeys ;
    }

    function db_specialization()
    {
        return 'PostgreSQL 8.1' ;
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
     * @desc return the SQL query to create the specified table.
     * @param string the name of the table.
     * @return string the SQL query to create the table.
     */

    function &showCreateTable($theTableName)
    {
        if (empty($this->dblink))
        {
            $this->connect();
        }

        $xxx = explode('.', $theTableName) ;

        $xxx = array_reverse($xxx) ;

        $yyy = array("table_name = '%s'", "table_schema = '%s'", "table_catalog = '%s'") ;

        $theWhere = '' ;

        for ($i = 0 ; $i < count($xxx); $i++)
        {
            $theWhere .= ' AND ' . sprintf($yyy[$i], addcslashes($xxx[$i], "'\\")) ;
        }

        $theWhere = substr($theWhere, 5) ;

        $theSQL = sprintf("select * from information_schema.columns where %s order by ordinal_position ;", $theWhere) ;

        $theColumnsResult =
            $this->db_query(
                $theSQL,
                $this->dblink) ;

        $theCreateTable = '' ;

        $theColumns = array() ;

        while ($theColumn = $this->db_fetch_assoc($theColumnsResult))
        {
            if ($theCreateTable == '')
            {
                $theCreateTable = sprintf('CREATE TABLE %s.%s', $theColumn['table_schema'], $theColumn['table_name']) ;
            }

            $xxx = sprintf('"%s" %s', $theColumn['column_name'], $theColumn['data_type']) ;

            if ($theColumn['column_default'] !== NULL)
            {
                $xxx .= sprintf(' DEFAULT %s', $theColumn['column_default']) ;
            }

            if ($theColumn['is_nullable'] == "YES")
            {
                $xxx .= ' NULL' ;
            }
            else
            {
                $xxx .= ' NOT NULL' ;
            }

            /*
             * Get all primary and unique key constraints
             */

            $theConstraintsResult =
                $this->db_query(
                    sprintf(
                        "SELECT * from information_schema.constraint_column_usage WHERE table_catalog = '%s' and table_schema = '%s' and table_name = '%s' AND column_name = '%s' ;",
                        $theColumn['table_catalog'],
                        $theColumn['table_schema'],
                        $theColumn['table_name'],
                        $theColumn['column_name']),
                    $this->dblink) ;

            while ($theConstraint = $this->db_fetch_assoc($theConstrantsResult))
            {
                /*
                 * Find out what sort of key this constraint is:
                 *
                 *  CHECK
                 *  FOREIGN KEY
                 *  PRIMARY KEY
                 *  UNIQUE
                 */

                $theTableConstraintsResult =
                    $this->db_query(
                        sprintf("SELECT * from information_schema.table_constraints WHERE constraint_catalog = '%s' AND constraint_schema = '%s' AND constraint_name = '%s' ;",
                        $theConstraint['constraint_catalog'],
                        $theConstraint['constraint_schema'],
                        $theConstraint['constraint_name']),
                    $this->dblink) ;

                while ($theTableConstraint = $this->db_fetch_assoc($theTableConstraintsResult))
                {
                    $xxx .= sprintf(' %s', $theTableConstraint['constraint_type']) ;
                }

                $this->db_free_result($theTableConstraintsResults) ;

                $theCheckConstraintsResult =
                    $this->db_query(
                        sprintf("SELECT * from information_schema.check_constraints WHERE constraint_catalog = '%s' AND constraint_schema = '%s' AND constraint_name = '%s' ;",
                        $theConstraint['constraint_catalog'],
                        $theConstraint['constraint_schema'],
                        $theConstraint['constraint_name']),
                    $this->dblink) ;

                while ($theCheckConstraint = $this->db_fetch_assoc($theCheckConstraintsResult))
                {
                    $xxx .= sprintf(' %s', $theCheckConstraint['check_clause']) ;
                }

                $this->db_free_result($theCheckConstraintsResult) ;

                /*
                 * FIX THIS:
                 *
                 * At the moment I don't handle foreign keys at all (information_schema.referential_constraints).
                 * Nor are externally specified constraints processed.
                 */
            }

            $this->db_free_result($theConstraintsResult) ;

            $theColumns[] = $xxx ;
        }

        $this->db_free_result($theColumnsResult) ;

        if (count($theColumns) == 0)
        {
            $theCreateTable = '' ;
        }
        else
        {
            $theCreateTable .= sprintf(' (%s) ;', implode(', ', $theColumns)) ;
        }

        return $theCreateTable ;
    }

    /**
     * @desc return the list of tables in the current database.
     * @return array the names of the tables in the current database.
     */

    function &showTables()
    {
        $theTableNames = array() ;

        if (empty($this->dblink))
        {
            $this->connect();
        }

        $theResult =
            $this->db_query(
                'select table_catalog, table_schema, table_name from information_schema.tables where table_schema != \'information_schema\' and table_schema not like \'pg_%\' ;',
                $this->dblink) ;

        while ($theTableName = $this->db_fetch_array($theResult))
        {
            $theTableNames[] = sprintf('%s.%s', $theTableName[1], $theTableName[2]) ;
        }

        $this->db_free_result($theResult) ;

        return $theTableNames ;
    }

    /**
     * Abstract functions for database access.  Assumes that all PostgreSQL database interfaces
     * are functionally available using the actual database.
     */

    function db_affected_rows($dblink)
    {
        // FIX THIS
        return 0 ;
        return parent::db_affected_rows($dblink) ;
    }

    function db_close($dblink)
    {
        return @pg_close($dblink) ;
    }

    function db_connect($dbhost, $dblogin, $dbpass)
    {
        $theConnect = 'dbname=\'' . addcslashes($this->get_dbname(), '\'\\') . '\'' ;
        if ($this->get_dbhost() !== NULL)
        {
            $theConnect .= ' ' . 'host=\'' . addcslashes($dbhost, '\'\\') . '\'' ;
        }
        if ($this->get_dblogin() != '')
        {
            $theConnect .= ' ' . 'user=\'' . addcslashes($dblogin, '\'\\') . '\'' ;
        }
        if ($this->get_dbpass() != '')
        {
            $theConnect .= ' ' . 'password=\'' . addcslashes($dbpass, '\'\\') . '\'' ;
        }
        if ($this->get_dbport() != '')
        {
            $theConnect .= ' ' .  'port=\'' . addcslashes($this->get_dbport(), '\'\\') . '\'' ;
        }

        return @pg_pconnect($theConnect) ;
    }

    function db_data_seek($queryid, $row)
    {
        return @pg_result_seek($queryid, $row) ;
    }

    function db_error()
    {
        return @pg_last_error($this->dblink) ;
    }

    function db_fetch_array($queryid)
    {
        return @pg_fetch_array($queryid) ;
    }

    function db_fetch_assoc($queryid)
    {
        return pg_fetch_assoc($queryid) ;
    }

    function db_free_result($result)
    {
        return @pg_free_result($result) ;
    }

    function db_insert_id($dblink, $theSequenceName = NULL)
    {
        if ($theSequenceName === NULL)
        {
            $theResult = $this->db_query('select lastval() ;', $dblink) ;
        }
        else
        {
            $theResult = $this->db_query(sprintf("select currval('%s') ;", $theSequenceName), $dblink) ;
        }

        $theRow = $this->db_fetch_array($theResult) ;

        $this->db_free_result($theResult) ;

        return $theRow[0] ;
    }

    function db_num_rows($queryid)
    {
        return @pg_num_rows($queryid) ;
    }

    function db_query($sql, $dblink)
    {
        return @pg_query($dblink, $sql) ;
    }

    function db_select($dbname, $dblink)
    {
        /*
         * Unlike MySQL, PostgreSQL connects to a host/database pair and you can't switch
         * databases in mid stream.  This is a hard incompatibility that I may be able to
         * wash away by issuing a new connect to the database server if the dbname passed in
         * isn't the same as the current one.  For now, just go with the connection that you
         * already have.
         *
         * This function is normally only called by the abstract DB connect function though
         * so there shouldn't be any problem with this.
         */

        return is_resource($dblink) ;
    }

    function db_real_escape_string($theString, $dblink)
    {
        return @pg_escape_string($theString) ;
    }

    function serverHasTransaction($dblink)
    {
        return true ;
    }

    /**
     * Constructor
     *
     * @param      String $dblogin, String $dbpass, String $dbname
     * @return     void
     * @access     public
     */

    function PostgreSQL81($dblogin, $dbpass, $dbname, $dbhost = null)
    {
        $this->AbstractDB($dblogin, $dbpass, $dbname, $dbhost) ;
    }
}