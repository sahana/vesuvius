<h2 style="text-align: center;">Report on My Projects</h2>
<br />
{php}
	shn_form_fopen('volunteer&vm_action=display_custom_report', null, array('enctype' => 'enctype="multipart/form-data"'));

		shn_form_fsopen('');
			shn_form_select($projects, 'Project: ', 'proj_id');
		shn_form_fsclose();

		shn_form_submit('Create Report');

	shn_form_fclose();
{/php}
