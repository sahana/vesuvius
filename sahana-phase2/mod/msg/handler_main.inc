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


global $global;
print $global['msg_jabber']->$connected;
?>


<h1 align="center"><?= _("Messaging Home")?> </h1>
<div id="home">
    <div>
    <p><?= (_("Messaging module is the main communicative root of the sahana system. It is used to send sms,E-mail alerts and/or messages to various groups and individuals before, after and during a disaster. It also provides a convenient way of grouping mobile phone numbers and E-mail addresses.")) ?></p></div>
    <br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
      
    <ul>
        <li><a href="index.php?mod=msg&act=customized_messaging"><b><?= (_("Messages:"))?></b></a><br><?= (_("sms and E-mail alerts/messages could be sent to any groups or individuals. This feature currently works only on Linux platform."))?></li>
        <li><a href="index.php?mod=msg&act=add_group"><b><?= (_("Manage Groups:"))?></b></a><br><?= (_("Each end user is provided the facility to create,customize and maintain various groups of sms and E-mail contacts"))?></li>
        <li><a href="index.php?mod=msg&act=cap_new"><b><?= (_("CAP:"))?></b></a><br><?= (_(" New Alert Option enables end-user to create a New CAP message This will create an xml file containing the CAP message and store it in a temporary directory. You can view this file using 'View Messages' option."))?><br><?=(_("View Alert Option enables end-user to view stored CAP messages Two sample messages are already added to the list. You can view them by selecting
one of them and pressing the 'view' button"))?></li>
        
    </ul>
    
</div>


<!--<div id="home">
<h2><?//php print _("Messaging")?></h2>

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
</div>-->
