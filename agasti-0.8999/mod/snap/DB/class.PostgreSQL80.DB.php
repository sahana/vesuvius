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
 * @version 1.0.1
 */

/**
 * PostgreSQL 8.0 specialization of the PostgreSQL 8.1 class.
 */

include_once 'class.PostgreSQL81.DB.php' ;

class PostgreSQL80DB extends PostgreSQL81DB
{
    function db_specialization()
    {
        return 'PostgreSQL 8.0' ;
    }

    /**
     * @desc Get the current value of the specified sequence
     *
     * This is the only difference between 8.1 and 8.0 that I've been able to find.
     *
     * @access protected
     * @param resource the database link.
     * @param string the sequence name.
     * @return integer the current value of the sequence.
     */

    function db_insert_id($dblink, $theSequenceName)
    {
        $theResult =
            $this->db_query(
                sprintf("select currval('%s') ;", $theSequenceName),
                $this->dblink) ;

        $theRow = $this->db_fetch_array($theResult) ;

        $this->db_free_result($theResult) ;

        return $theRow[0] ;
    }

    /**
     * Constructor
     *
     * @param      String $dblogin, String $dbpass, String $dbname
     * @return     void
     * @access     public
     */

    function PostgreSQL80($dblogin, $dbpass, $dbname, $dbhost = null)
    {
        $this->PostgreSQL81($dblogin, $dbpass, $dbname, $dbhost) ;
    }
}