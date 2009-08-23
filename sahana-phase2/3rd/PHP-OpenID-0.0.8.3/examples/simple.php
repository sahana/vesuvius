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


// Dumb mode identity verification example.
//
// This example is completely stateless, and just requires mod_php >= 4.1.0
// to run.  Stick the php openid tree somewhere beneath your docroot and go nuts. 
// Once you understand this example you'll know the basics of OpenID 
// and using the PH OpenID library.  You can then move on to more 
// robust examples, and integrating OpenID into your app.
//
// Copyright 2005, Janrain, Inc.

// This gets us everything we need to be an openid consumer.
require_once( '../openid/consumer.php' );

define('HOST', $_SERVER['SERVER_NAME']);
define('PORT', $_SERVER['SERVER_PORT']);

function my_redirect($url) {
    header( 'Location: ' . $url );
    exit; // okay, so *I* never use exit within a script, but am porting from Python.
}

function formArgstoDict() {
    // Returns a dict of the GET and POST arguments
    return array_merge( $_GET, $_POST );
}

function drawAlert($msg) {
    if( $msg ) {
        return sprintf( '<div id="alert">%s</div>', $msg );
    }
    return '';
}

$_message='';
function setAlert($m) {
    global $_message;
    $_message .= $m;
}

// Our OpenIDConsumer subclass.  See openid.consumer.OpenIDConsumer
// for more more documentation.
class SimpleConsumer extends OpenIDConsumer {
    
    function verify_return_to( $return_to ) {
    
        $parts = parse_url( $return_to );

        if (! isset($parts["port"])) $parts["port"] = ($parts["scheme"] == 'https' ? 443 : 80);

        // you should verify return_to host:port string match host and 
        // port of this server
        if( $parts['host'] != HOST || $parts['port'] != PORT ) {
            return false;
        }

        return true;
    }

};

// A handler with application specific callback logic.
class SimpleActionHandler extends ActionHandler {

    function SimpleActionHandler($query, $consumer) {
        $this->query = $query;
        $this->consumer = $consumer;
    }

    // callbacks
    function doValidLogin($login) {
        // here is where you would do what is necessary to log an openid "user"
        // user into your system.  We just print a message confirming the
        // valid login.
        setAlert( sprintf( '<b>Identity verified!</b> Thanks, ' .
                           '<a href="%s">' .
                           '%s</a>', $this->query['open_id'], $this->query['open_id'] ) );
    }

    function doInvalidLogin() {
        setAlert('Identity NOT verified!');
    }

    function doUserCancelled() {
        setAlert('Cancelled by user.');
    }

    function doCheckAuthRequired($server_url, $return_to, $post_data) {
        // do openid.mode=check_authentication call, and then change state
        $response = $this->consumer->check_auth($server_url, $return_to, $post_data,
                                                $this->getOpenID());
        $response->doAction($this);
    }

    function doErrorFromServer($message) {
        setAlert('Error from server: ' . $message);
    }

    // helpers
    function createReturnTo($base_url, $identity_url, $args=null) {
        if( !is_array( $args ) ) {
            $args = array();
        }
        $args['open_id'] = $identity_url;
        return oidUtil::append_args($base_url, $args);
    }

    function getOpenID() {
        // return the openid from the original form
        return $this->query['open_id'];
    }
};    


function dispatch() {
    // generate a dictionary of arguments
    $query = formArgstoDict();
    
    // create consumer and handler objects
    $consumer = new SimpleConsumer();
    $handler = new SimpleActionHandler($query, $consumer);

    // extract identity url from arguments.  Will be null if absent from query.
    $identity_url = isset( $query['identity_url'] ) ? $query['identity_url'] : null;

    if( $identity_url ) {
        $ret = $consumer->find_identity_info($identity_url);
        if( !$ret ) {
            setAlert(sprintf('Unable to find openid server for identity url %s', $identity_url) );
        }
        else {
            // found identity server info
            list( $identity_url, $server_id, $server_url ) = $ret;

            // build trust root - this examines the script env and builds
            // based on your running location.  In practice this may be static.
            // You will likely want it to be your entire website, not just
            // this script.
            $trust_root = isset($_SERVER['SCRIPT_URI']) ? $_SERVER['SCRIPT_URI'] : 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'];

            // build url to application for use in creating return_to
            $app_url = isset($_SERVER['SCRIPT_URI']) ? $_SERVER['SCRIPT_URI'] : 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'];

            // create return_to url from app_url
            $return_to = $handler->createReturnTo($app_url, $identity_url);

            // handle the request
            $redirect_url = $consumer->handle_request(
                $server_id, $server_url, $return_to, $trust_root);

            // redirect the user-agent to the server
            my_redirect($redirect_url);
        }
    }
    // php's url parsing converts '.' to '_'. So we check for both cases.
    else if( isset( $query['openid.mode'] ) || isset( $query['openid_mode'] ) ) {
        // got a request from the server.  build a Request object and pass
        // it off to the consumer object.  OpendIDActionHandler handles
        // the various end cases (see above).
        $openid = $handler->getOpenID();
        $req = new ConsumerRequest($openid, $query, 'GET');
        $response = $consumer->handle_response($req);

        // let our SimpleActionHandler do the work
        $response->doAction($handler);
    }
};    

// dispatch the event based on url args.
dispatch();

// Our helpful display page.
$buf = <<< END
<html>
<head>  
  <title>Simple PHP OpenID Consumer Example</title>
  <style type="text/css">
  * {font-family:verdana,sans-serif;}
  body {width:50em; margin:1em;}
  div {padding:.5em; }
  table {margin:null;padding:null;}
  #alert {border:1px solid #e7dc2b; background: #fff888;}
  #login {border:1px solid #777; background: #ddd; margin-top:1em;padding-bottom:0em;}
  </style>
</head>
<body>
  <h2>PHP Consumer Example</h3>
  <p>This example consumer uses the PHP OpenID library ( ported from <a href="http://openid.schtuff.com/">Python OpenID library</a> )  in <a href="http://www.openid.net/specs.bml#associate">dumb mode</a>.  The example asserts that you own the URL typed below; that it is your identity URL.</p>
  %s
  <div id="login">
  Verify an Identity URL
  <hr/>
    <form action="%s" method="get">     
    OpenID: <input type="text" name="identity_url" class="openid_identity" />
    <input type="submit" value="Verify" />
    </form>
  </div>

</body>
</html>
END;

echo sprintf( $buf, drawAlert($_message), $_SERVER['SCRIPT_URI'] );


