<?php
/**Class that front ends the PHP Mailer
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sri Ganeshan <sri@opensource.lk>
* @author     Ravindra De Silva <ravindra@opensource.lk><ravi@computer.org>
* @edit		  Mifan Careem <mifan@opensource.lk> [Converting to use global $conf variables]
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* $license	  $Id: lib_mail.inc,v 1.9 2009-08-22 17:17:22 ravithb Exp $
* @subpackage msg
*/


global $global;
require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");;

/**
 * PHPMailer extension class
 */
class InheritPhpMailer extends PHPMailer
{
    // Mifan: Converting previously used $sit global variable to $conf global array
    
    var $priority = 3;

    function InheritPhpMailer()
    {
      global $conf;
      
      
      if($conf['mod_msg_smtp_mode'] == "enabled"){
		    $this->Host = $conf['mod_msg_smtp_host'];
		    $this->Port = $conf['mod_msg_smtp_port'];
		    if($conf['mod_msg_smtp_username'] != ""){
		         $this->SMTPAuth  = true;
		         $this->Username  = $conf['mod_msg_smtp_username'];
		         $this->Password  = $conf['mod_msg_smtp_password'];
        	}
        $this->Mailer = "smtp";
        
      }
      if(!$this->From){
        	$this->From = $conf['mod_msg_smtp_sender_email'];
      }
      if(!$this->FromName){
        	$this->FromName = $conf['mod_msg_smtp_sender_name'];
      }
      if(!$this->Sender){
        	$this->Sender = $conf['mod_msg_smtp_sender_email'];
      }
      $this->Priority = $this->priority;
    }
}

/**
 * Email sending main function
 * Group sending
 */
function _shn_msg_send_group_mail($msg,$receipients)
{
	//config settings
	//require_once('mail_settings.inc');
	//shn_update_mail_configuration();
	global $conf;
	
	// instantiate the class
	$mailer = new InheritPhpMailer();
	$status=0;
	$trimd_msg=trim($msg);
	$subject=substr($trimd_msg,0,15);
	$mailer->Subject = $conf['mod_msg_mail_subject_prefix'].$subject;
	$mailer->Body = $msg;
	$status_mail=array();
	   foreach($receipients as $receipient){
			$mailer->AddAddress($receipient, '');
	        $status=$mailer->Send();
	
	        if($status){ 
	        	$status_mail[$receipient]=1;
	        }else{
		  		$status_mail[$receipient]=0;
	        }
	        $status=0;
	        $mailer->ClearAddresses();
	   }
	return $status_mail;
}

function _shn_msg_send_mail()
{
// Grab our config settings
require_once('mail_settings.inc');

// Grab the InheritPhpMailer class
//require_once('MailClass.inc');

// instantiate the class
$mailer = new InheritPhpMailer();

$receipient = $_POST['receipient'];

$subject = $_POST["subject"];

$ccreceipient = $_POST['ccreceipients'];

$bccreceipient = $_POST['bccreceipients'];

$attachment = $_POST['attachments'];

$body = $_POST['contents'];

$mailer->Subject = $subject;

$mailer->Body = $body;

$mailer->AddAddress($receipient, '');

//$mailer->AddAddress('hari1222@yahoo.com', 'hari');

$mailer->AddAttachment($attachment, ''); 

$mailer->AddCC($ccreceipient, ''); 

$mailer->AddBCC($bccreceipient,''); 

//$mailer->AddReplyTo('kushi223344@yahoo.com', 'sri'); 

if(!$mailer->Send())
{
  echo 'There was a problem sending this mail!';
}
else
{
  echo 'Mail sent!';
}
$mailer->ClearAddresses();
$mailer->ClearAttachments();
} 
