<?php
shn_form_fopen('default&vm_action=process_change_pass');
	shn_form_fsopen('Change Password');
		shn_form_password('Current Password :', 'cur_pass', '', array('req' => true));
		shn_form_password('New Password :', 'pass1', '', array('req' => true));
		shn_form_password('Re-Type New Password :', 'pass2', '', array('req' => true));
		shn_form_hidden(array('p_uuid'=>$p_uuid));
	shn_form_fsclose();
	shn_form_submit("Change Password");
shn_form_fclose();
?>