<h2 style="text-align: center;">_("Assign Volunteers")</h2>

{if empty($projects)}
<br />
<b>_("You are currently not assigned as a site manager to any projects.")</b>
{else}
	<b>_("First please select a project to assign to:") </b>
	{php}
		shn_form_fopen('project&amp;vm_action=display_assign');
			shn_form_fsopen(_('Project to assign to'));
				$extra_opts['req']=true;
				shn_form_select($projects, $label, 'proj_id', NULL, $extra_opts);
			shn_form_fsclose();

		shn_form_submit(_('Continue'));

		shn_form_fclose();
	{/php}
{/if}