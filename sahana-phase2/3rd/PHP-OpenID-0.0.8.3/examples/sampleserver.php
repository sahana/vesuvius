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


require_once( '../openid/server.php' );
require_once( '../openid/association.php' );

define( 'addr',  isset( $_SERVER['PATH_INFO'] ) ? str_replace( $_SERVER['PATH_INFO'], '', $_SERVER['SCRIPT_URI'] ) : $_SERVER['SCRIPT_URI'] );

// define some paths to be used for maintaining state in this example server.
// May need to adjust for non-unix OS. Will attempt to create if not pre-existing.
//
// To wipe server's association and trust state, just rm -rf /tmp/openid
define( 'openid_store_base', '/tmp/openid' );

define( 'external_assoc_store_dir', openid_store_base . 'estore' );
define( 'internal_assoc_store_dir', openid_store_base . 'istore' );
define( 'trust_root_store_dir', openid_store_base . 'tstore' );

class Store extends ServerAssociationStore {
    // In python, this examples uses a simple, in-memory store that exists
    // for the life of the server process.
    
    // In php, we write the associations to a temporary file because
    // php apps are otherwise stateless. We require a directory
    // name in the constructor, and each new association is stored
    // as a file within that directory.  Typically, one should use
    // a nicer caching mechanism such as memcached, or even a database.
        
    var $store_dir;
    
    function Store( $store_dir ) {
        $this->count = 0;
        $this->assocs = array();
        $this->lifespan = 60 * 60 * 2;  // an association is valid for 2 hours
        
        $this->store_dir = $store_dir;
        
        if( !file_exists( $store_dir ) ) {
            if( (int)PHP_VERSION >= 5 ) {
               mkdir( $store_dir, 0700, true );
            }
            else {
               // can't recurse.   :(
               mkdir( $store_dir, 0700 );
            }
        }
    }

    function get($assoc_type) {
        assert( '$assoc_type == "HMAC-SHA1"' );
        // $handle = sprintf( '{%s}%d/%d',  $assoc_type, localtime(), $this->count );

        $path = tempnam( $this->store_dir, $assoc_type . '_' );
        $handle = basename( $path );
        
        $this->count += 1;
        $secret = oidUtil::random_string(20, null);
        $assoc = Association::from_expires_in($handle, $secret, $this->lifespan);

        $fh = fopen( $path, 'w' );
        if( $fh ) {
            fwrite( $fh, base64_encode( @serialize( $assoc ) ) );
            fclose( $fh );
        }

        return $assoc;
    }

    function lookup($assoc_handle, $assoc_type) {
        // This method returns the stored association for a given
        // handle and association type.  If there is no such stored
        // association, it should return null.

        $path = $this->store_dir . '/' . $assoc_handle;

        if( !file_exists( $path ) ) {
            return null;
        }
        
		return @unserialize( base64_decode( file_get_contents( $path ) ) );
    }


    function remove($assoc_handle) {
        // If the server code notices that an association it retrieves
        // has expired, it will call this method to let the store know it
        // should remove the given association.  In general, the
        // implementation should take care of that without the server
        // code getting involved.  This exists primarily to deal with
        // corner cases correctly.
        $path = $this->store_dir . $assoc_handle;
        unlink( $path );
    }
}            


class ConcreteServer extends OpenIDServer {
    function ConcreteServer() {
        if( !file_exists( openid_store_base ) ) {
            mkdir( openid_store_base, 0700 );
        }
        
        parent::OpenIDServer( new Store( internal_assoc_store_dir ), new Store( external_assoc_store_dir ), null);
        $this->counter = 0;
        $this->trust_store_dir = trust_root_store_dir;
        
        if( !file_exists( $this->trust_store_dir ) ) {
            if( (int)PHP_VERSION >= 5 ) {
               mkdir( $this->trust_store_dir, 0700, true );
            }
            else {
               // can't recurse.   :(
               mkdir( $this->trust_store_dir, 0700 );
            }
        }
        
    }

    function handle($req) {
        // This is reimplemented in the subclass so that extra tracing
        // information can be extracted.  It isn't necessary in the
        // general case.

        return parent::handle($req);
    }
    
    function gen_trust_store_path( $identity, $trust_root ) {
         return $this->trust_store_dir . '/' . 'openid_trust_' . base64_encode(md5($identity)) . '_' . base64_encode(md5($trust_root));
    }

    function is_valid($req) {
        if( addr . '/' . $req->authentication != $req->get('identity') ) {
            return false;
        }

        $path = $this->gen_trust_store_path( $req->get('identity'), $req->get('trust_root') );

        return file_exists( $path );
    }

    function add_trust($identity, $trust_root) {
    
        $path = $this->gen_trust_store_path( $identity, $trust_root );
        touch( $path );
    
    }

    function get_user_setup_url($req) {
        $args = array(
            'openid.mode' => 'checkid_setup',
            'openid.identity' => $req->get('identity'),
            'openid.trust_root' => $req->get('trust_root'),
            'openid.return_to' => $req->get('return_to'),
        );

        $assoc_handle = $req->get('assoc_handle');
        if( $assoc_handle ) {
            $args['openid.assoc_handle'] = $req->get('assoc_handle');
        }

        return oidUtil::append_args(addr . '?action=openid', $args);
    }

    function get_setup_response($req) {
        $args = array(
            'identity' => $req->get('identity'),
            'trust_root' => $req->get('trust_root'),
            'fail_to' => oidUtil::append_args($req->get('return_to'), array('openid.mode' => 'cancel') ),
            'success_to' => oidUtil::append_args(addr, $req->args),
            'action' => 'allow'
        );
        return redirect(oidUtil::append_args(addr, $args));
    }
};    


// Note: This area could use some cleanup.  I'm not a fan of executing
// code outside of classes/functions, but it was the quickest way to port
// the example.


$server = new ConcreteServer();

$identitypage = <<< END
<html>
<head>
  <title>This is an identity page</title>
  <link rel="openid.server" href="%s?action=openid">
</head>
<body style='background-color: #CCCCFF;'>
  <p>This is an identity page for %s.</p>
  <p><a href="%s">home</a></p>
</body>
</html>
END;

$mainpage = <<< END
<html>
<head>
  <title>Simple OpenID server</title>
</head>
<body style='background-color: #CCCCFF;'>
<h1>This is a simple OpenID server</h1>
<p>
  <a href="?action=login">login</a><br />
  <a href="?action=whoami">who am I?</a>
</p>
</body>
</html>
END;

$decidepage = <<< END
<html>
<head>
  <title>Allow Authorization?</title>
</head>
<body style='background-color: #CCCCFF;'>
  <h1>Allow Authorization?</h1>
  <table>
    <tr><td>Identity:</td><td>%s</td></tr>
    <tr><td>Trust Root:</td><td>%s</td></tr>
  </table>
  <form method="POST" action="%s">
    <input type="hidden" name="action" value="allow" />
    <input type="hidden" name="identity" value="%s" />
    <input type="hidden" name="trust_root" value="%s" />
    <input type="hidden" name="fail_to" value="%s" />
    <input type="hidden" name="success_to" value="%s" />
    <input type="submit" name="yes" value="yes" />
    <input type="submit" name="no" value="no" />
  </form>
</body>
</html>
END;

$loginpage = <<< END
<html>
<head>
  <title>Log In!</title>
</head>
<body style='background-color: #CCCCFF;'>
  <h1>Log In!</h1>
  <p>No password used because this is just an example.</p>
  <form method="GET" action="%s">
    <input type="hidden" name="action" value="login" />
    <input type="hidden" name="fail_to" value="%s" />
    <input type="hidden" name="success_to" value="%s" />
    <input type="text" name="user" value="" />
    <input type="submit" name="submit" value="Log In" />
    <input type="submit" name="cancel" value="Cancel" />
  </form>
</body>
</html>
END;

$whoamipage = <<< END
<html>
<head>
  <title>Who are you?</title>
</head>
<body style='background-color: #CCCCFF;'>
  <h1>Who are you?</h1>
  <p>You seem to be <a href="%s">%s<a>...</p>
  <p><a href="%s">home</a></p>
</body>
</html>
END;

$loggedinpage = <<< END
<html>
<head>
  <title>You logged in!</title>
</head>
<body style='background-color: #CCCCFF;'>
  <h1>You've successfully logged in.</h1>
  <p>You have logged in as %s</p>
  <p><a href="%s">home</a></p>
</body>
</html>
END;

$openidpage = <<< END
<html>
<head>
  <title>You've found an openid server</title>
</head>
<body style='background-color: #CCCCFF;'>
  <h1>This is an OpenID server</h1>
  <p>See <a href="http://www.openid.net/">openid.net</a>
  for more information.</p>
</body>
</html>
END;

function getQueryVar( $key ) {
    return isset( $_POST[$key] ) ? $_POST[$key] : ( isset( $_GET[$key] ) ? $_GET[$key] : null );
}

$action = getQueryVar( 'action' );

switch( $action ) {
    case 'login':
        $user = getQueryVar( 'user' );
        $cancel = getQueryVar( 'cancel' );
        $fail_to = getQueryVar( 'fail_to' );
        $success_to = getQueryVar( 'success_to' );
        
        if( $cancel ) {
            header( 'Location: ' . $fail_to );
        }
        else if( $user ) {
            setcookie('oid_user', $user);
            if( $success_to ) {
                header( 'Location: ' . $success_to );
            }
            echo sprintf( $loggedinpage, $user, addr );
        }
        else {
            echo sprintf( $loginpage, addr, $fail_to, $success_to);
        }
        
        break;

    case 'allow':
        if( $_SERVER['REQUEST_METHOD'] == 'POST' ) {

            $yes = getQueryVar('yes');
            if( $yes ) {
                $server->add_trust( getQueryVar('identity'), getQueryVar('trust_root') );
                header( 'Location: ' . getQueryVar('success_to') );
            }
            else {
                header( 'Location: ' . getQueryVar('fail_to') );
            }
        }
        else {
    
            $user = isset( $_COOKIE['oid_user'] ) ? $_COOKIE['oid_user'] : null;
            $identity = getQueryVar('identity');
            
            if( addr . '/' . $user == $identity ) {
                echo sprintf($decidepage, $identity, getQueryVar('trust_root'), addr, $identity, 
                             getQueryVar('trust_root'), getQueryVar('fail_to'), getQueryVar('success_to') );
            }
            else {
                echo sprintf( $loginpage, addr, getQueryVar('fail_to'), getQueryVar('success_to'));
            }
        }
        break;

        
    case 'openid':
        $query = array_merge( $_POST, $_GET );
        $oid_user = isset( $_COOKIE['oid_user'] ) ? $_COOKIE['oid_user'] : null;
        $req = new Request( $query, $_SERVER['REQUEST_METHOD'],  $oid_user );

        $response = $server->handle( $req );
        if( $response->code == 302 ) {
            header( 'Location: ' . $response->redirect_url );
        }
        else {
            echo $response->body;
        }
        
        break;

    case 'whoami':
        $oid_user = isset( $_COOKIE['oid_user'] ) ? $_COOKIE['oid_user'] : null;
        $identity = addr . '/' . $oid_user;
        echo sprintf( $whoamipage, $identity, $oid_user, addr );
        
        break;

        
    default:
        $path_info = isset( $_SERVER['PATH_INFO'] ) ? $_SERVER['PATH_INFO'] : '/' ;
        if( $path_info == '/' ) {
            echo $mainpage;
        }
        else {
            echo sprintf( $identitypage, addr, substr( $path_info, 1 ), addr );
        }
        
        break;
}


