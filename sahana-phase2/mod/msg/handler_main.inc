<?php
/**
* Sahana Messaging Module
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana
* @subpackage   Messaging
* @tutorial
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


global $global;
print $global['msg_jabber']->$connected;
?>
<div id="home">
<h2><?php print _("Messaging")?></h2>

<br/>
<h3>Use the New Message Option to create a New CAP message</h3>
<p>This will create an xml file containing the CAP message and store it in a 
temporary directory. You can view this file using 'View Messages' option</p>

<br />
<h3>Use the View Messages Option to view stored CAP messages</h3>
<p>Two sample messages are already added to the list. You can view them by selecting
one of them and pressing the 'view' button </p>

<br />
<h3>XMPP Messaging</h3>
<p>Comming soon to a Sahana near you ;-)</p>
</div>
