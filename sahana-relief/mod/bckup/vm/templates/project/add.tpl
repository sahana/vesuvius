<h2> {$action} _("Project")</h2>
{php}
shn_form_fopen('project&vm_action=process_add');
	shn_form_fsopen(_('Project Information'));
		shn_form_text(_('Name'), "name", '', array('req'=>true, 'value'=>$info['name']));
		shn_form_date(_('Start date :'), 'start_date', array('value' => $start_date));
		shn_form_date(_('End date :'), 'end_date', array('value' => $end_date));
		shn_form_textarea(_('Description'), "description", '', array('value'=>$info['description']));
		if(!isset($hidden['proj_id']))
			shn_form_select($managers,'Site Manager :', 'manager', '', array('req' => true));
	shn_form_fsclose();

	shn_form_fsopen(_('Base Location'));
		shn_location(shn_get_range(), $info['location_id']);
	shn_form_fsclose();

	shn_form_hidden($hidden);
	shn_form_submit(_('Submit'));
	shn_form_button(_('Cancel'), "onClick='history.go(-1);'");
shn_form_fclose();
{/php}