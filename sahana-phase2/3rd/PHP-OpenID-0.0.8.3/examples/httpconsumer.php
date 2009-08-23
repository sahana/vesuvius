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


require_once( '../openid/consumer.php' );
require_once( 'exutil.php' );

// for backwards compatibility with older PHP versions.
if( !function_exists( 'file_get_contents' ) ) {
   function file_get_contents( $path ) {
      $buf = '';
      $fh = fopen( $path, 'r' );
      if( $fh ) {
         $buf = fread( $fh );
         fclose( $fh );
      }
      return $buf;
   }
}
if( !function_exists( 'file_put_contents' ) ) {
   function file_put_contents( $path, $data ) {
      $fh = fopen( $path, 'w' );
      if( $fh ) {
         fwrite( $fh, $data );
         fclose( $fh );
      }
   }
}


class DictionaryAssociationManager extends AbstractConsumerAssociationManager {

    function DictionaryAssociationManager( $http_client ) {
        $associator = new DiffieHelmanAssociator($http_client);
        parent::AbstractConsumerAssociationManager($associator);
        $this->association_path = '/tmp/oid_consumer_associations.txt';
    }
    
    // private. helper for maintaining state across requests.
    function _get_associations( ) {
        $buf = @file_get_contents( $this->association_path );
        return $buf ? unserialize( $buf ) : array();
    }
    
    // private. helper for maintaining state across requests.
    function _set_associations( $assoc ) {
        @file_put_contents( $this->association_path, serialize($assoc) );
    }

    function update($new_assoc, $expired) {
        // This is horribly inefficient.  Don't use this code outside
        // of toy examples.
        
        $map = null;
        
        if( $new_assoc ) {
            $map = $this->_get_associations();
            $map[] = $new_assoc;
        }

        if( $expired ) {
            foreach( $expired as $assoc1 ) {
                if( !$map ) {
                    $map = $this->_get_associations();
                }
            
                foreach( $map as $i => $assoc2 ) {
                    if( $assoc1 == $assoc2 ) {
                        unset( $map[$i] );
                        break;
                    }
                }
            }
        }

        if( $map ) {
            $this->_set_associations( $map );
        }
    }

    function get_all($server_url) {
        $map = $this->_get_associations();
        $results = array();
        foreach( $map as $assoc ) {
            if( $assoc->server_url == $server_url ) {
                $results[] = $assoc;
            }
        }

        return $results;
    }

    function invalidate($server_url, $assoc_handle) {
        $map = $this->_get_associations();
    
        foreach( $map as $i => $assoc ) {
            if( $assoc->server_url == $server_url && $assoc->handle == $assoc_handle ) {
                unset( $map[$i] );
                $this->_set_associations( $map );
                break;
            }
        }
        
    }
}


class SampleConsumer extends OpenIDConsumer {

    function SampleConsumer( $http_client, $assoc_mngr ) {
        parent::OpenIDConsumer( $http_client, $assoc_mngr );
        
        $path = '/tmp/oid_secret.txt';
        $secret = null;
        if( file_exists( $path ) ) {
            $secret = unserialize( file_get_contents( $path ) );
        }
        if( !$secret ) {
            $secret = oidUtil::random_string(20, null);
            @file_put_contents( $path, serialize( $secret ) );
        }
        
        $this->secret = $secret;
    }

    function get_assoc_mngr() {
        return $this->assoc_mngr;
    }

    function get_http_client() {
        return $this->http_client;
    }

    function verify_return_to($return_to) {
    
        // parse the input url
        $parts = parse_url($return_to);
        $host = isset( $parts['host'] ) ? $parts['host'] : '';
        $port = isset( $parts['port'] ) ? $parts['port'] : '';
        
        $host = $host . ( $port ? ':' . $port : '' );
        
        if( $host != $_SERVER['HTTP_HOST'] ) {
            return false;
        }

        $v = oidUtil::to_b64(oidUtil::hmacsha1($this->secret, $_GET['id'] . $_GET['time']));

        if( $v != $_GET['v'] ) {
            return false;
        }

        // reject really old return_to urls
        if( (int)$_GET['time'] + 60 * 60 * 6 < time()) {
            return false;
        }

        return true;
    }

    function create_return_to($base, $identity) {
        $args = array(
            'id' => $identity,
            'time' => (string)time(),
            );

        $args['v'] = oidUtil::to_b64(oidUtil::hmacsha1($this->secret, $args['id'] . $args['time']));
        return oidUtil::append_args($base, $args);
    }
};    


class ConsumerHandler extends HTTPHandler {
    var $consumer;
    var $split;
    var $dumb;
    var $self_url;

    function ConsumerHandler( $consumer, $self_url, $split, $dumb ) {
        $this->consumer = $consumer;
        $this->self_url = $self_url;
        $this->split = $split;
        $this->dumb = $dumb;
    }

    function _simplePage($msg) {
        $this->_headers();
        
        echo <<< END
<html>
<body style='background-color: #FFFFCC;'>
<p>$msg</p>
<p><a href="{$this->self_url}">home</a></p>
</body>
</html>
END
;
    }

    function _error($msg) {
        $this->_simplePage('Error: ' . $msg);
    }

    function _inputForm() {
        return <<< END
<html>
<head><title>Openid Consumer Example</title></head>
<body style='background-color: #FFFFCC;'>
<form method="GET" action="">
Your Identity URL: <input type="text" name="identity_url" size="60"/>
<br /><input type="submit" value="Log in" />
</form>

</body>
</html>
END
;
    }

    function _splitpage($server_url, $return_to, $post_data) {
        $this->_headers();
        $buf = <<< END
<html>
<body style='background-color: #FFFFCC;'>
<p>If this were a guestbook style application, it would ask you
to enter your comment now, and use the check_authorization call
to confirm that you are in fact the user you say you are.</p>
<p>This is a demo of the flow that would provide, and nothing
more.</p>
<form method="GET" action="/">
<input type="hidden" name="server_url" value="%s" />
<input type="hidden" name="return_to" value="%s" />
<input type="hidden" name="post_data" value="%s" />
<input type="submit" value="Check Authorization" />
</form>
</body>
</html>
END
;
        echo sprintf( $buf, $server_url, $return_to, $post_data );
    }

    function doValidLogin($login) {
        $this->_simplePage('Logged in as ' . $this->query['id'] );
    }

    function doInvalidLogin() {
        // raise "InvalidLogin"
        $this->_simplePage('Not logged in. Invalid.');
    }

    function doUserCancelled() {
        $this->_simplePage('Cancelled by user');
    }

    function doCheckAuthRequired($server_url, $return_to, $post_data) {
        if( $this->split ) {
            $this->_splitpage($server_url, $return_to, $post_data);
        }
        else {
            $response = $this->consumer->check_auth($server_url, $return_to, $post_data,
                                           $this->query['id']);
            $response->doAction($this);
        }
    }

    function doErrorFromServer($message) {
        // raise RuntimeError(message)
        trigger_error( $message, E_USER_ERROR );
    }

    function doUserSetupNeeded($user_setup_url) {
        // Not using checkid_immediate, so this shouldn't happen.
        //raise RuntimeError(user_setup_url)
        trigger_error( $user_setup_url, E_USER_ERROR );
    }

    function do_GET() {
        $this->query = $_GET;

        // dispatch based on query args
        if( isset($_GET['identity_url']) ) {
            // this is the entry point for a user.  do the
            // consumer's initialRequest which finds a server
            // association (unless in dumb mode) and then redirect
            // the UA to the server
            $identity_url = $_GET['identity_url'];
            // print 'making initial request'

            $ret = $this->consumer->find_identity_info($identity_url);
            if( !$ret ) {
                $error = sprintf( 'Unable to find openid.server for %s. Query was %s.', $identity_url, $_SERVER['REQUEST_URI'] );
                $this->_error( $error );
            }
            else {
                list( $consumer_id, $server_id, $server_url ) = $ret;

                $return_to = $this->consumer->create_return_to(
                    $this->self_url, $consumer_id);
                
                $trust_root = $this->self_url;

                $redirect_url = $this->consumer->handle_request(
                    $server_id, $server_url, $return_to, $trust_root);

                $this->_redirect($redirect_url);
            }
        }

        else if( isset( $_GET['openid_mode'] ) ) {
            $open_id = $_GET['id'];
            $req = new ConsumerRequest($open_id, $_GET, 'GET');
            $response = $this->consumer->handle_response($req);
            $response->doAction($this); // using visitor pattern approach
        }
        else if( isset( $_GET['post_data'] ) ) {
            // extract necessary information from current query
            $su = $_GET['server_url'];
            $rt = $_GET['return_to'];
            $pd = $_GET['post_data'];
            
            // replace query with the query from the return_to url
            $parts = parse_url( $rt );
            $this->query = null;
            parse_str( $parts['query'], $this->query );

            $response = $this->consumer->check_auth($su, $rt, $pd);
            $response->doAction($this);
        }
        else {
            $this->_headers();
            echo $this->_inputForm();
        }
    }
};
        
if( strstr( $_SERVER['REQUEST_URI'], 'httpconsumer.php' ) ) {

    // flags used to control consumer behavior.
    $dumb = false;
    $split = false;

    $http_client = HTTPClient::getHTTPClient( );
    $assoc_mngr = null;
    $consumer = null;
    
    if( $dumb ) {
        $assoc_mngr = new DumbAssociationManager( $http_client );
    }
    else {
        $assoc_mngr = new DictionaryAssociationManager( $http_client );
    }

    $consumer = new SampleConsumer($http_client, $assoc_mngr);

    // print 'Consumer Server running...'
    $handler = new ConsumerHandler( $consumer, $_SERVER['SCRIPT_URI'], $split, $dumb );
    $handler->do_GET();
}

    
