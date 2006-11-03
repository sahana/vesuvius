<?

function _shn_msg_compose_mail_form($error=false){
global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc"
?>
<h2><?= _('Compose Mail')?></h2>
<?php
    if($error)
    display_errors();
?>  
<div id="formcontainer">
<?php
    shn_form_fopen("send_mail&stream=text");
?>
 	<table>
<tr><td width="100px">To: </td><td><input type="text" name="receipient" size = "50"></td></tr>
	<tr><td width="100px">Subject: </td><td><input type="text" name="subject" size = "50"></td></tr>
	<tr><td width="100px">Cc: </td><td><input type="text" name="ccreceipients" size = "50"></td></tr>
	 <tr><td width="100px">Bcc: </td><td><input type="text" name="bccreceipients" size = "50"></td></tr>


	 <tr><td width="100px">Attachments: </td><td><input type="text" name="attachments" size = "50"></td></tr>
	</table><br>
	<label>body<br>
	<textarea name ="contents" rows ="20" cols="70"></textarea>
	<input type="submit" value="Send"/>
<input type="reset" value="Clear"/>
	<?php
    //close the form
    shn_form_fclose();
}			     



