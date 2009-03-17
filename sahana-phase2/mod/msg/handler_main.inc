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
* @author	Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	sahana
* @subpackage	rms
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

global $global;
print $global['msg_jabber']->$connected;
?>

<h1 align="center"><?php echo  _t("Messaging Home")?> </h1>
<div id="home">
    <div>
    <p><?php echo  (_t("Messaging module is the main communicative root of the Sahana system. It is used to send SMS, e-mail alerts and/or messages to various groups and individuals before, after and during a disaster. It also provides a convenient way of grouping mobile phone numbers and e-mail addresses.")) ?></p></div>
    <br></br>
    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
      
    <ul>
        <li><a href="index.php?mod=msg&act=customized_messaging"><b><?php echo  (_t("Messages:"))?></b></a><br><?php echo  (_t("SMS and e-mail alerts/messages could be sent to any groups or individuals. This feature currently works only on Linux platform."))?></li>
        <li><a href="index.php?mod=msg&act=add_group"><b><?php echo  (_t("Manage Groups:"))?></b></a><br><?php echo  (_t("Each end user is provided the facility to create, customize and maintain various groups of SMS and e-mail contacts"))?></li>
        <li><a href="index.php?mod=msg&act=cap_new"><b><?php echo  (_t("CAP:"))?></b></a>
<br><a href="index.php?mod=msg&act=cap_new"><?php echo  (_t("New Alert"))?></a><?php echo  (_t(" option enables end-user to create a new CAP message. This will create an XML file containing the CAP message and store it in a temporary directory. You can view this file using 'View Messages' option."))?>
<br><a href="index.php?mod=msg&act=cap_view"><?php echo (_t("View Alert"))?></a><?php echo  (_t(" option enables end-user to view stored CAP messages. Two sample messages are already added to the list. You can view them by selecting one of them and pressing the 'View' button"))?></li>
    </ul>
<?php




    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('rss_alert',_t('CAP Alerts'));
?>
</div>


<!--<div id="home">
<h2><?//php print _t("Messaging")?></h2>

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
