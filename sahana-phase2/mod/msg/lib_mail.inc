<?php

global $global;
require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");;

class InheritPhpMailer extends PHPMailer
{
    var $priority = 3;

  
    function InheritPhpMailer()
    {
      global $sit; 
      
      // Comes from config.php $sit array
      
      if($sit['smtp_mode'] == "enabled")
      {
        $this->Host = $sit['smtp_host'];
        $this->Port = $sit['smtp_port'];
        if($sit['smtp_username'] != "")
        {
         $this->SMTPAuth  = true;
         $this->Username  = $sit['smtp_username'];
         $this->Password  = $sit['smtp_password'];
        }
        $this->Mailer = "smtp";
        
      }
      if(!$this->From)
      {
        $this->From = $sit['from_email'];
      }
      if(!$this->FromName)
      {
        $this->FromName = $sit['from_name'];
      }
      if(!$this->Sender)
      {
        $this->Sender = $sit['from_email'];
      }
      $this->Priority = $this->priority;
    }
}

function _shn_msg_send_mail()
{
// Grab our config settings
require_once('mail_info.inc');

// Grab the InheritPhpMailer class
//require_once('MailClass.inc');

// instantiate the class
$mailer = new InheritPhpMailer();

$receipient = $_POST['receipient'];

$subject = $_POST["subject"];

$ccreceipient = $_POST['ccreceipients'];

$bccreceipient = $_POST['bccreceipients'];

$attachment = $_POST['attachments'];
//var_dump($_POST);
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
}?> 
