{php}
shn_form_fopen('default&amp;vm_action=process_change_pass');
	shn_form_fsopen(_('Change Password'));
		shn_form_password(_('Current Password :'), 'cur_pass', '', array('req' => true));
		shn_form_password(_('New Password :'), 'pass1', '', array('req' => true));
		shn_form_password(_('Re-Type New Password :'), 'pass2', '', array('req' => true));
		shn_form_hidden(array('p_uuid'=>$p_uuid));
	shn_form_fsclose();
	shn_form_submit(_('Change Password'));
shn_form_fsclose();
{/php}