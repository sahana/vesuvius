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
* @author		Sriganeshan <sri@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	msg
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");
require_once($global['approot']."3rd/snoopy/Snoopy.class.php");


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
}//end of class InheritPhpMailer

/**
 * @author	Mifan
 */
function shn_send_sms($msg,$recipients)
{
	global $global;
	include_once $global['approot']."/mod/msg/lib_msg.inc";
	shn_msg_send_short_message($recipients,$msg);
}

/**
 * @deprecated
 */
function shn_send_sms_1($msg,$receipients)
{
  $sms_box=0;
  $bearer_box=0;
  $status_sms=array();
  $snoopy = new Snoopy;
  
  foreach($receipients as $to){
        $form_msg = urlencode($msg);
        $snoopy->fetchtext("http://localhost:13014/cgi-bin/sendsms?username=tester&password=foobar&to=".$to."&text=".$form_msg);
        $server_response=$snoopy->results;
        if(strcmp($server_response[0],"Sent.")){
          	$status_sms[$to]=1;
        }
        else{
	  		$status_sms[$to]=0;
        }
       $server_response="";
     } //end of loop
   return $status_sms;
}
 


function shn_check_kannel_status()
{

  $sms_box=0;
  $bearer_box=0;
  $status_sms=array();
  $snoopy = new Snoopy;
  $snoopy->fetchtext("http://localhost:13014/cgi-bin/sendsms?");
  $server_response=$snoopy->results;
  $pieces = explode(" ",$server_response);
  if(strcmp($pieces[0],"Authorization") && strcmp($pieces[1],"failed")){
    	$sms_box=1;
  }
  else{
    	$sms_box=0;
  }
  
  $snoopy->fetchtext("http://localhost:13003/");
  $server_response=$snoopy->results;
  $pieces = explode(" ",$server_response);
  if(!strcmp($pieces[0],"Unknown") && !strcmp($pieces[1],"command"))
    $bearer_box=1;
  else
    $bearer_box=0;

  if($bearer_box && $sms_box)
  {
    $kannel_status= 1;
  }
  else
  {
    $kannel_status= 0;
  }

//return $kannel_status;
return true;

}//end of function shn_check_kannel_status


// e-mail API
function _shn_msg_send_group_mail($msg,$receipients)
{
//config settings
require_once('mail_settings.inc');
shn_update_mail_configuration();

// instantiate the class
$mailer = new InheritPhpMailer();
$status=0;
$trimd_msg=trim($msg);
$subject=substr($trimd_msg,0,15);
$mailer->Subject = "[SAHANA-MSG]".$subject;
$mailer->Body = $msg;
$status_mail=array();
   foreach($receipients as $receipient)
   {
	$mailer->AddAddress($receipient, '');
        $status=$mailer->Send();

        if($status)
        { 
          $status_mail[$receipient]=1;
        }else
        {
	  $status_mail[$receipient]=0;
        }
        $status=0;
        $mailer->ClearAddresses();
        
   }
return $status_mail;
}
