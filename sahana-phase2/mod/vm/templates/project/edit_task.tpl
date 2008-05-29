{php}
	shn_form_fopen("project&amp;vm_action=process_edit_task&amp;p_uuid=$p_uuid&amp;proj_id=$proj_id");
		shn_form_fsopen(_('Modify Task'));
			shn_form_text(_('Task'), "task", '', array('req'=>true, 'value'=>$current_task));
		shn_form_fsclose();
		shn_form_submit(_('Update'));
	shn_form_fclose();
{/php}
