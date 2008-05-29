<h2 style="text-align: center;">_("Report on My Projects")</h2>
<br />
{php}
	shn_form_fopen('volunteer&amp;vm_action=display_custom_report&amp;rpp='.VM_DEFAULT_REPORTS_RPP, null, array('enctype' => 'enctype="multipart/form-data"'));

		shn_form_fsopen('');
			shn_form_select($projects, 'Project: ', 'proj_id');
		shn_form_fsclose();

		shn_form_submit(_('Create Report'));

	shn_form_fclose();
{/php}
