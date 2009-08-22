<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

if (!$global['msg_jabber'])
    print "<h2>Jabber not connected </h3>";
else
{


    //$JABBER->SendPresence();
    
    //$JABBER->CruiseControl(60);
    
    $global['msg_jabber']->SendPresence(NULL, NULL, "online");
    
    $global['msg_jabber']->SendMessage("sahana_test1@jabber.org", 
                         "normal",
                         NULL, 
                         array( // body, thread... whatever
                               "body" => "New Request"
                              ),
                         $payload
                        );
    
}


// EXAMPLE for an external message handler
// When running $this->CruiseControl(), the handler is called when there's an incoming
// message - if the body of the message is "go2sleep" and the sender is
// test@jabber.g-blog.net, the script will disconnect from the server and exit.

//function Handler_message_normal($message)
//{
//    global $JABBER;
//
//    $from = $JABBER->GetInfoFromMessageFrom($message);
//    $body = $JABBER->GetInfoFromMessageBody($message);
//
//    if ($body == "go2sleep" && preg_match("/^sahana/i", $from))
//    {
//        $JABBER->Disconnect();
//        exit;
//    }
//    elseif ($body)
//    {
//        print $body;
//
//        $JABBER->SendMessage($from, NULL, NULL, array("body" => "test1"));
//    }
//    else
//    {
//        $JABBER->SendMessage($from, NULL, NULL, array("body" => "I am the Elmar-bot. Give me a word or phrase, and I will return what Elmar Fudd would have said."));
//    }
//} 


