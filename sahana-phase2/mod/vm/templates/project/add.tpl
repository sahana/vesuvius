<h2> {$action} Project</h2>
{php}
shn_form_fopen('project&vm_action=process_add');
	shn_form_fsopen("Project Information");
		shn_form_text("Name", "name", '', array('req'=>true, 'value'=>$info['name']));
		shn_form_date('Start date :', 'start_date', array('value' => $start_date));
		shn_form_date('End date :', 'end_date', array('value' => $end_date));
		shn_form_textarea("Description", "description", '', array('value'=>$info['description']));
		if(!isset($hidden['proj_id']))
			shn_form_select($managers,'Site Manager :', 'manager', '', array('req' => true));
	shn_form_fsclose();

	shn_form_fsopen('Base Location');
		shn_location(shn_get_range(), $info['location_id']);
	shn_form_fsclose();

	shn_form_hidden($hidden);
	shn_form_submit("Submit");
	shn_form_button("Cancel", "onClick='history.go(-1);'");
shn_form_fclose();
{/php}