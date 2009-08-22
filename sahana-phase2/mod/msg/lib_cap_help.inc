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

/**
 * Main help
 */
$help_identifire = _t("The identifier of the alert message. <br /> (1) A number or string uniquely identifying this message, assigned by the sender <br /> (2) MUST NOT include spaces, commas restricted characters (< and &)");
$help_sender = _t("Identifies the originator of this alert. Guaranteed by assigner to be unique globally; e.g., may be based on an Internet domain name");
$help_status = _t("Code Values: <br /> 'Actual' - Actionable by all targeted recipients <br /> 'Exercise'- Actionable only by designated exercise participants; exercise identifier should appear in &lt;note&gt; <br />'System' - For messages that support alert network internal functions. <br />'Test' - Technical testing only, all recipients disregard <br />'Draft' - A preliminary template or draft, not actionable in its current form.");
$help_msgType = _t("Code Values: <br /> 'Alert' - Initial information requiring attention by targeted recipients <br />'Update' - Updates and supercedes the earlier message(s) identified in &lt;references&gt;<br />'Cancel' - Cancels the earlier message(s) identified in &lt;references&gt;<br />'Ack' - Acknowledges receipt and acceptance of the message(s)) identified in &lt;references&gt;<br />'Error' indicates rejection of the message(s) identified in &lt;references&gt; explanation SHOULD appear in &lt;note&gt;");
$help_source = _t("The particular source of this alert; e.g., an operator or a specific device.");
$help_scope = _t("Code Values:<br />'Public' - For general dissemination to unrestricted audiences <br />'Restricted' - For dissemination only to users with a known operational requirement <br />'Private' - For dissemination only to specified addresses");


/**
 * Info help
 */
$help_event = _t("The text denoting the type of the subject event of the alert message");
$help_urgency = _t("(1) The 'urgency', 'severity', and 'certainty' elements collectively distinguish less emphatic from more emphatic messages.<br />(2) Code Values:<br />'Immediate' - Responsive action SHOULD be taken immediately <br />'Expected' - Responsive action SHOULD be taken soon (within next hour) <br />'Future' - Responsive action SHOULD be taken in the near future <br />'Past' - Responsive action is no longer required <br />'Unknown' - Urgency not known ");

