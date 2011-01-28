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
 * @version 2.2.0
 */

/*
 * FIX THIS:
 *
 * To allow multiple results at the same time cleanly I need to return RESULTS objects which
 * encapsulate the active query.  Things like clear, fetch*, etc. would be associated with those
 * rather than the DB object.
 *
 * This will be a fundamental change in the way this class is used, but it will make some stuff
 * a LOT cleaner.
 */

include_once('class.abstract.independent.DB.php') ;

/**
 * Generic SQL database access management class.  The design of this class derives
 * from dm.DB and is best used for databases which provide a superset
 * of the functionality available from MySQL.  The goal of this class is two fold:
 *
 * 1. Provide a generic interface to all SQL compliant databases.
 * 2. Provide an easily portable interface to all SQL compliant databases.
 *
 * Since this class was originally conceived of and implemented for MySQL the implementation
 * of the MySQL specialization of this abstract class is the simplest.
 *
 * Features include:
 *  1. suppressing of error messages and error management
 *  2. methods to control showing of error messages
 *  3. methods to perform and manage database connections and queries
 *  4. methods to navigate through the database resuklts and queries
 *  4. Begin, Commit, and Rollback database Transactions if supported
 */

class AbstractDB extends AbstractIndependentDB
{
    /**
     * global variables
     */

    /**
     * @access private
     *
     * This variable contains structured data and is of the form:
     *
     *  host:port
     *
     * If no port is given, the "default" port for the database will be used by the specializations.
     *
     * @var string name of the host on which the database resides, defaults
     *             to 'localhost'.
     */

    var $dbhost = 'localhost';            // default database host
    var $dblogin;                         // database login name
    var $dbpass;                          // database login password
    var $dbport = '' ;                    // default port to connect to the database server.
    var $dbname;                          // database name
    var $dblink;                          // database link identifier

    /**
     * @access private
     * @var resource The query id of the last query.
     */

    var $queryid;                         // database query identifier
    var $error = array();                 // storage for error messages
    var $record = array();                // database query record identifier
    var $totalrecords;                    // the total number of records received from a select statement
    var $last_insert_id;                  // last incremented value of the primary key
    var $previd = 0;                      // previus record id. [for navigating through the db]
    var $transactions_capable = false;    // does the server support transactions?
    var $begin_work = false;              // sentinel to keep track of active transactions
    var $lastQuery ;
    var $debug = false ;
    var $_affectedRows ;                  // Number of rows affected by the last query.

    /**
     * get and set type methods for retrieving properties.
     */

    function get_dbhost()
    {
        return $this->dbhost ;
    } // end function

    function get_dblogin()
    {
        return $this->dblogin;
    } // end function

    function get_dbpass()
    {
        return $this->dbpass;

    } // end function

    /**
     * @desc Return the optional port portion of the dbhost.
     * @returns The port or the null string if there was no port specified
     * @access
     */

    function get_dbport()
    {
        return $this->dbport ;
    } // end function

    function get_dbname()
    {
        return $this->dbname;

    } // end function

    function set_dbhost($value)
    {
        if ($value === NULL)
        {
            $value = 'localhost' ;
        }
        return $this->dbhost = $value;

    } // end function

    function set_dbport($value)
    {
        if ($value === NULL)
        {
            $value = '' ;
        }
        return $this->dbport = $value;

    } // end function

    function set_dblogin($value)
    {
        return $this->dblogin = $value;

    } // end function

    function set_dbpass($value)
    {
        return $this->dbpass = $value;

    } // end function

    function set_dbname($value)
    {
        return $this->dbname = $value;

    } // end function

    function get_errors()
    {
        return $this->error;

    } // end function

    /**
     * End of the Get and Set methods
     */

    /**
     * Constructor
     *
     * @param      String $dblogin, String $dbpass, String $dbname
     * @return     void
     * @access     public
     */

    function AbstractDB($dblogin, $dbpass, $dbname, $dbhost = null)
    {
        $this->set_dblogin($dblogin);
        $this->set_dbpass($dbpass);
        $this->set_dbname($dbname);

        if ($dbhost != null)
        {
            $xxx = explode(':', $dbhost) ;
            $this->set_dbhost($xxx[0]) ;
            $this->set_dbport((array_key_exists(1, $xxx) ? $xxx[1] : '')) ;
        }
    } // end function

    /**
     * Connect to the database and change to the appropriate database.
     *
     * @param      none
     * @return     database link identifier
     * @access     public
     * @scope      public
     */

    function connect()
    {
        $this->dblink = @$this->db_connect($this->dbhost, $this->dblogin, $this->dbpass);

        if (!$this->dblink) {
            $this->return_error('Unable to connect to the database.');
        }
        else
        {
            $t = @$this->db_select($this->dbname, $this->dblink);

            if (!$t) {
                $this->return_error('Unable to change databases.');
            }
            else
            {
                $this->transactions_capable = $this->serverHasTransaction($this->dblink) ;
            }
        }
        return $this->dblink;

    } // end function

    /**
     * Disconnect from the database.
     *
     * A side effect has been introduced that clears the last result on disconnect.
     * This is to attempt to better manage memory allocation.
     *
     * @param      none
     * @return     void
     * @access     public
     * @scope      public
     */
    function disconnect()
    {
        $this->clear() ;
        $test = @$this->db_close($this->dblink);

        if (!$test) {
            $this->return_error('Unable to close the connection.');
        }

        unset($this->dblink);

    } // end function

    function escape_string($theString)
    {
        if (empty($this->dblink)) {
            // check to see if there is an open connection. If not, create one.
            $this->connect();
        }

        return $this->db_real_escape_string($theString, $this->dblink) ;
    }

    /**
     * Stores error messages
     *
     * @param      String $message
     * @return     String
     * @access     private
     * @scope      public
     */
    function return_error($message)
    {
        if ($this->debug)
        {
            return $this->error[] = $message.'<pre>'.var_export(debug_backtrace()).'</pre>'.$this->db_error().'.';
        }
        else
        {
            return $this->error[] = $message . $this->db_error() . '.';
        }
    } // end function

    /**
     * Show any errors that occurred.
     *
     * @param      boolean $theTextFlag [optional] If true, the error text is returned
     *                     as a string.
     * @return     mixed When $theTextFlag is true, return a string.
     * @access     public
     * @scope      public
     */
    function showErrors($theTextFlag = false)
    {
        if ($this->hasErrors()) {
            reset($this->error);

            $errcount = count($this->error);    //count the number of error messages

            $theErrorText = "<p>Error(s) found: <b>'$errcount'</b></p>\n";

            // print all the error messages.
            while (list($key, $val) = each($this->error)) {
                $theErrorText .= "+ $val<br>\n";
            }

            $this->resetErrors();

            if ($theTextFlag) {
                return $theErrorText ;
            }
            else {
                echo $theErrorText ;
            }
        }

    } // end function

    /**
     * Checks to see if there are any error messages that have been reported.
     *
     * @param      none
     * @return     boolean
     * @access     private
     */
    function hasErrors()
    {
        if (count($this->error) > 0) {
            return true;
        } else {
            return false;
        }

    } // end function

    /**
     * Clears all the error messages.
     *
     * @param      none
     * @return     void
     * @access     public
     */
    function resetErrors()
    {
        if ($this->hasErrors()) {
            unset($this->error);
            $this->error = array();
        }

    } // end function

    /**
     * Performs an SQL query whose argument is a constant.
     *
     * @param      String $sql
     * @return     resource query identifier
     * @access     public
     */

    function queryConstant($sql)
    {
        return $this->query($sql) ;
    }

    /**
     * Performs an SQL query.
     *
     * @param      String $sql
     * @return     resource query identifier
     * @access     public
     */

    function query(&$sql)
    {
        $this->lastQuery = $sql ;

        if (empty($this->dblink)) {
            // check to see if there is an open connection. If not, create one.
            $this->connect();
        }

        $this->queryid = @$this->db_query($sql, $this->dblink);

        if ($this->queryid)
        {
            $this->_affectedRows = @$this->db_affected_rows($this->dblink) ;
        }
        else
        {
            if ($this->begin_work)
            {
                $this->rollbackTransaction();
            }
            $this->return_error('Unable to perform the query <b>' . $sql . '</b>.');
        }

        $this->previd = 0;

        return $this->queryid;

    } // end function

    /**
     * Grabs the records as an indexed array.
     *
     * As a side effect, it keeps track of the record's position within the
     * result.
     *
     * @access     public
     * @param      resource [optional] The result from which data is to be fetched.
     * @return     mixed an array containing a DB record.
     */

    function fetchRow($theQueryId = NULL)
    {
        if (($theQueryId !== NULL) && ($theQueryId != $this->queryid))
        {
            return @$this->db_fetch_array($theQueryId) ;
        }
        else if (isset($this->queryid))
        {
            $this->previd++;
            return $this->record = @$this->db_fetch_array($this->queryid);
        }
        else
        {
            $this->return_error('No query specified.');
        }

    }

    /**
     * Grabs the records as an associative array.
     *
     * As a side effect, it keeps track of the record's position within the
     * result.
     *
     * Multiple results can be active for the span of a single object so it is allowed to
     * accept a query id from other than the current result.
     *
     * @access     public
     * @param      resource [optional] the result from which the next row is to be fetched.
     * @return     mixed an array containing a DB record.
     */

    function fetchAssoc($theQueryId = NULL)
    {
        if (($theQueryId !== NULL) && ($theQueryId != $this->queryid))
        {
            return @$this->db_fetch_assoc($theQueryId) ;
        }
        else if (isset($this->queryid))
        {
            $this->previd++;
            return $this->record = @$this->db_fetch_assoc($this->queryid);
        }
        else
        {
            $this->return_error('No query specified.');
        }

    }

    /**
     * Moves the record pointer to the first record
     *
     * @access     public
     * @param boolean $theAssocFlag True if an associative array is to be returned,
     *                false otherwise.
     * @return mixed An array containing the current DB record.
     */

    function moveFirst($theAssocFlag=false)
    {
        if (isset($this->queryid)) {
            $t = @$this->db_data_seek($this->queryid, 0);

            if ($t) {
                $this->previd = 0;
                if ($theAssocFlag) {
                  return $this->fetchAssoc();
                } else {
                  return $this->fetchRow();
                }
            } else {
                $this->return_error('Cant move to the first record.');
            }
        } else {
            $this->return_error('No query specified.');
        }

    }

    /**
     * Moves the record pointer to the last record
     *
     * @access     public
     * @param boolean $theAssocFlag True if an associative array is to be returned,
     *                false otherwise.
     * @return mixed An array containing the current DB record.
     */

    function moveLast($theAssocFlag=false)
    {
        if (isset($this->queryid)) {
            $this->previd = $this->resultCount()-1;

            $t = @$this->db_data_seek($this->queryid, $this->previd);

            if ($t) {
              if ($theAssocFlag) {
                return $this->fetchAssoc() ;
              } else {
                return $this->fetchRow();
              }
            } else {
                $this->return_error('Cant move to the last record.');
            }
        } else {
            $this->return_error('No query specified.');
        }

    }

    /**
     * Moves the record pointer to the next record
     *
     * @access     public
     * @param boolean $theAssocFlag True if an associative array is to be returned,
     *                false otherwise.
     * @return mixed An array containing the current DB record.
     */

   function moveNext($theAssocFlag=false)
    {
      if ($theAssocFlag=false) {
        return $this->fetchAssoc() ;
      } else {
        return $this->fetchRow();
      }
    }

    /**
     * Moves the record pointer to the previous record
     *
     * @access     public
     * @param boolean $theAssocFlag True if an associative array is to be returned,
     *                false otherwise.
     * @return mixed An array containing the current DB record.
     */

    function movePrev($theAssocFlag=false)
    {
        if (isset($this->queryid)) {
            if ($this->previd > 1) {
                $this->previd--;

                $t = @$this->db_data_seek($this->queryid, --$this->previd);

                if ($t) {
                  if ($theAssocFlag) {
                    return $this->fetchAssoc() ;
                  } else {
                    return $this->fetchRow();
                  }
                } else {
                    $this->return_error('Cant move to the previous record.');
                }
            } else {
                $this->return_error('BOF: First record has been reached.');
            }
        } else {
            $this->return_error('No query specified.');
        }

    } // end function


    /**
     * If the last query performed was an 'INSERT' statement, this method will
     * return the last inserted primary key number.  Many databases have a notion
     * of "sequence".  This function returns the value of the default sequence (for the case
     * of MySQL, its the last autoincrement field value) by default.  Should a
     * specifice sequence be needed, the optional name may be passed in and the current
     * value of that sequence will be returned instead.
     *
     * @param        string [optional] the name of the sequence whose current value is to be returned.
     * @return        int
     * @access        public
     * @scope        public
     * @since        version 1.0.1
     */
    function fetchLastInsertId($theSequenceName = NULL)
    {
        $this->last_insert_id = @$this->db_insert_id($this->dblink, $theSequenceName);

        if (!$this->last_insert_id)
        {
            $this->return_error(
                sprintf('Unable to get the last inserted id from %s after query: %s',
                    $this->db_specialization(),
                    $this->lastQuery));
        }

        return $this->last_insert_id;

    } // end function

    /**
     * Returns state of queryid
     *
     * @param            none
     * @return           boolean
     * @access           public
     */

    function eof()
    {
        $theResultCount = $this->resultCount() ;

        if ($theResultCount === false)
        {
            return true ;
        }

        if ($theResultCount == 0)
        {
            return true ;
        }

        return false ;
    }

    /**
     * Counts the number of rows returned from a SELECT statement.
     *
     * @param      boolean [optional] true if errors are to be captured, false otherwise.  Default
     *                     is FALSE.
     * @return     mixed False if it is not possible to calculated the number of rows in
     *                   the result, otherwise the number of rows in the result.
     * @access     public
     */

    function resultCount($showErrors=false)
    {
        if (isset($this->queryid))
        {
            $this->totalrecords = @$this->db_num_rows($this->queryid);

            return $this->totalrecords;
        }
        else
        {
            if ($showErrors)
            {
                $this->return_error('Unable to count the number of rows returned');
            }

            return false ;
        }

    }

    /**
     * Counts the number of rows affected by the last INSERT/UPDATE/DELETE statement.
     *
     * @return     integer The number of rows affected.
     * @access     public
     */

    function affectedCount()
    {
        if (isset($this->_affectedRows))
        {
            return $this->_affectedRows ;
        }
        else
        {
            $this->return_error('Unable to count the number of rows affected');

            return false ;
        }

    }

    /**
     * Checks to see if there are any records that were returned from a
     * SELECT statement. If so, returns true, otherwise false.
     *
     * @return     boolean True if there were rows in the result, false otherwise.
     * @access     public
     */
    function resultExist()
    {
        return (isset($this->queryid) && ($this->resultCount() > 0)) ;
    }

    /**
     * Checks to see if there are any records that were returned affected by a
     * INSERT/UPDATE/DELETE statement. If so, returns true, otherwise false.
     *
     * @access     public
     * @return     boolean True if there were any rows affected by the query, false otherwise.
     */

    function affectedRows()
    {
        return (isset($this->_affectedRows) && ($this->_affectedRows > 0)) ;
    }

    /**
     * Clears any records in memory associated with a result set.
     * It allows calling with no select query having occurred.
     *
     * @param      resource $result
     * @access     public
     */

    function clear($result = NULL)
    {
        if ($result !== NULL)
        {
            $t = @$this->db_free_result($result);

            if (!$t)
            {
                $this->return_error('Unable to free the results from memory');
            }
        }
        else
        {
            if (isset($this->queryid) && !empty($this->queryid))
            {
                @$this->db_free_result($this->queryid);
            }
        }

    }

    /**
     * Start a transaction.
     *
     * @access  public
     */

    function beginTransaction()
    {
        if ($this->transactions_capable) {
            $this->queryConstant('BEGIN');
            $this->begin_work = true;
        }

    } // end function

    /**
     * Perform a commit to record the changes.
     *
     * @access  public
     */

    function commitTransaction()
    {
        if ($this->transactions_capable) {
            if ($this->begin_work) {
                $this->queryConstant('COMMIT');
                $this->begin_work = false;
            }
        }
    }

    /**
     * Perform a rollback if the query fails.
     *
     * @access  public
     */

    function rollbackTransaction()
    {
        if ($this->transactions_capable) {
            if ($this->begin_work) {
                $this->queryConstant('ROLLBACK');
                $this->begin_work = false;
            }
        }

    } // end function

    /**
    * Lock A Table Item.
    *
    * @access public
    * @param mixed Table Name(s).  If an array is passed, the key is the table name and the value
    *              is the type of lock requested for that table.
    * @param string A Lock Type
    * @return mixed false if the requested lock couldn't be granted, otherwise the
    *               result of the lock query.
    */

    function lock($table, $mode="write")
    {
        $this->connect();

        $query="lock tables ";
        if (is_array($table))
        {
            foreach ($table as $key => $value)
            {
                if ($key=="read" && $key!=0)
                {
                    $query.="$value read, ";
                }
                else
                {
                    $query.="$value $mode, ";
                }
            }

            $query=substr($query,0,-2);
        }
        else
        {
            $query.="$table $mode";
        }

        $res = @$this->db_query($query, $this->dblink);

        if (!$res)
        {
            $this->return_error("$query failed.");
            return false ;
        }

        return $res;
    }

    /**
    * unlock A Table Item.
    *
    * @access public
    * @return mixed false if the unlock failed, the result of the query otherwise.
    */
    function unlock()
    {
        $this->connect();

        $res = @$this->db_query("unlock tables");
        if (!$res)
        {
            $this->return_error("unlock() failed.");
            return false;
        }

        return $res;
    }

}