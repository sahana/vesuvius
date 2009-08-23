<?php

/*****
PHP OpenID - OpenID consumer and server library

Copyright (C) 2005 Open Source Consulting, SA. and Dan Libby

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Reciprocal linking.  The author humbly requests that if you should use 
PHP-OpenID on your website to provide an OpenID enabled service that you 
place a link to the author's website ( http://videntity.org ) somewhere 
that your users can discover it.  You are however under no obligation to 
do so.  

More info about PHP OpenID:
openid@videntity.org
http://videntity.org/openid/

More info about OpenID:
http://www.openid.net

*****/

require_once( '../openid/httpclient.php' );
require_once( '../openid/association.php' );

class SQLConsumerAssociationManager extends AbstractConsumerAssociationManager {
    // This class implements a ConsumerAssociationManager using an SQL
    // backing.  It requires php's PDO extension.
    // It hasn't yet been tested.   :-)

    // This implementation requires that the DB that it's connected to
    // have a table created by something like:
    // CREATE TABLE openid_consumer_assocs
    // (
    //    url CHAR(255),
    //    handle CHAR(255),
    //    secret CHAR(255),
    //    issued INT,
    //    lifetime INT
    // );
    
    var $qstrs = array(
    'insert into openid_consumer_assocs values(%s, %s, %s, %s, %s)',
    'select * from openid_consumer_assocs where url = %s',
    'delete from openid_consumer_assocs where url = %s and handle = %s'
    );

    function SQLConsumerAssociationManager($connection) {
        // Connection should be an open DB API 2.0 compliant
        // connection to a database with a table as described above.  The
        // paramstyle argument should be the argstyle used by the
        // connection.  At the moment, only 'qmark' and 'format' are
        // supported.  The value necessary for a particular DB is in that
        // DB module's paramstyle global.
        parent::AbstractConsumerAssociationManager(
            new DiffieHelmanAssociator(new SimpleHTTPClient()));
        $this->connection = $connection;
    }

    function update($new_assoc, $expired) {
        if( $new_assoc ) {
            $query = sprintf( $this->qstrs[0], 
                              $new_assoc->server_url,
                              $new_assoc->handle,
                              oidUtil::to_b64($new_assoc->secret),
                              $new_assoc->issued,
                              $new_assoc->lifetime);
                              
            $this->connection->beginTransaction();
                              
            $this->connection->query( $query );

            $this->connection->commit();
        }

        foreach( $expired as $assoc ) {
            $this->invalidate( $assoc->server_url, $assoc->handle );
        }
    }


    function get_all($server_url) {
        // Subclasses should return a list of ConsumerAssociation
        // objects whose server_url attribute is equal to server_url."""
        $result = array();
        
        $query = sprintf( $this->qstrs[1], $server_url );

        $this->connection->beginTransaction();

        $cur = $this->connection->query( $query );
        
        foreach ($cur as $row) {
            $result[] = new ConsumerAssociation( $row['url'],
                                                 $row['handle'],
                                                 oidUtil::from_b64($row['secret']),
                                                 $row['issued'],
                                                 $row['lifetime'] );
        }        
        
        $this->connection->commit();

        return result;
    }

    function invalidate($server_url, $assoc_handle) {
        $query = sprintf( $this->qstrs[2], $server_url, $assoc_handle );
     
        $this->connection->beginTransaction();
        
        $this->connection->query( $query );
        
        $this->connection->commit();
    }
};

function getSQLiteConsumerAssociationManager($filename) {
    // This function returns an instance of the above store using an
    // SQLite database.  It requires SQLite extension to
    // be installed to use.  The filename passed in is the filename to
    // open for the database.  If the specified file doesn't exist, it's
    // created and the necessary table is created inside of it.

    $dsn = 'sqlite:' . $filename;
    if( file_exists( $filename) ) {
        $con = new PDO( $dsn );
    }
    else {
        $con = new PDO( $dsn );
        $query = <<< END
        
        CREATE TABLE openid_consumer_assocs
        (
            url CHAR(255),
            handle CHAR(255),
            secret CHAR(255),
            issued INT,
            lifetime INT
        );
END;

        $con->beginTransaction();
        $con->query( $query );        
        $con->commit();
    }

    return new SQLConsumerAssociationManager($con);
}

// for testing.
if( strstr( $_SERVER['REQUEST_URI'], 'associations.php' ) ) {
    // $assoc_mngr = getSQLiteConsumerAssociationManager( 'memory:' );
    $assoc_mngr = getSQLiteConsumerAssociationManager( '/tmp/assoc_test.db3' );
    var_dump( $assoc_mngr );
}


