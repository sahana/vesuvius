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
 */

/**
 * Definitions to use as the database type.
 */

define('dmDB_MySQL', 'MySQL') ;
define('dmDB_PostgreSQL80','PostgreSQL80') ;
define('dmDB_PostgreSQL81','PostgreSQL81') ;

/*
 * If the user doesn't specify which version of PosgreSQL is to be use, it defaults to
 * 8.1
 */

define('dmDB_PostgreSQL', dmDB_PostgreSQL81) ;

class FactoryDB
{
    /**
     * @desc Factory to return specializations for specific databases.
     * @access public
     * @param String $dblogin Login name to access the database.
     * @param String $dbpass Password to access the database.
     * @param String $dbname Name of the database being accessed.
     * @param String [optional] $dbhost Host on which the database resides, defaults
     *               to localhost.  The format of the dbhost parameter is:
     *
     *                  hostname[:port]
     *
     *               if your database server is on a non-standard port, you MUST provide
     *               both the hostname and the port, e.g.:
     *
     *                  localhost:5781
     *                  f.q.d.n:7865
     * @param String [optional] $dbtype the type of database engine to use, defaults
     *               to dmDB_MySQL
     * @return object a dm.DB object suitable for accessing the specified
     *                database.
     */

    function factory($dblogin, $dbpass, $dbname, $dbhost = null, $dbtype = dmDB_MySQL)
    {
        if ($dbtype == dmDB_MySQL)
        {
            include_once 'class.MySQL.DB.php' ;

            return new MySQLDB($dblogin, $dbpass, $dbname, $dbhost) ;
        }
        else if ($dbtype == dmDB_PostgreSQL80)
        {
            include_once 'class.PostgreSQL80.DB.php' ;

            return new PostgreSQL80DB($dblogin, $dbpass, $dbname, $dbhost) ;
        }
        else if ($dbtype == dmDB_PostgreSQL81)
        {
            include_once 'class.PostgreSQL81.DB.php' ;

            return new PostgreSQL81DB($dblogin, $dbpass, $dbname, $dbhost) ;
        }
        else
        {
            trigger_error("Unknown database type: " . $dbtype, E_USER_ERROR) ;
        }
    }

}