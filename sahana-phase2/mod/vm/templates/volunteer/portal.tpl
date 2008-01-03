<h1 align=center>Volunteer Management</h1>
The Volunteer Management module keeps track of projects and volunteers.
<p><br/>
<br/>
</p>
<h3><?php echo _("Current features include:")?></h3>
</p>
<ul style="margin-left: 1em;">
	<li><?=_('Manage volunteer assignment')?></li>
	<li><?=_('Start and view projects')?></li>
	<li><?=_('Search volunteers')?></li>
	<li><?=_('Send and receive messages')?></li>
</ul>
<br/>
<strong>Description of Actions:</strong><br/>

<ul style="margin-left: 1em;">
	<li><a href="?mod=vm&amp;act=default&amp;vm_action=display_single&amp;p_uuid={$p_uuid}"><b>View your info page</b></a><br/>View details of your  </li>
	{if $vol_assign}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_select_project"><b>Assign to Project</b></a><br>Manage volunteer assignments</li>
	{/if}

	{if $showAssigned}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_assigned"><b>Show Assigned</b></a><br/>View all volunteers assigned to projects
	{/if}

	{if $listVolunteers}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_all"><b>View All Volunteers</b></a><br/>View all registered volunteers
	{/if}

	{if $search}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_search"><b>Search</b></a><br/>Search for a volunteer
	{/if}

	{if $add_proj}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_add"><b>Add New Project</b></a><br/>Start a new project</li>
	{/if}

	{if $listMyProjects}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list"><b>View My Projects</b></a><br/> View all projects you are currently assigned to
	{/if}

	{if $listAllProjects}
		<li><a href="?mod=vm&amp;act=project"><b>View All Projects</b></a><br/> View all projects being tracked</li>
	{/if}

	{if $inbox}
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_custom_report_select"><b>Generate report</b></a><br/>Generate customized report on volunteers and projects</li>
	{/if}

	{if $outbox}
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_add"><b>Register to VM</b></a><br>Register yourself in Volunteer Management module</li>
	{/if}

	{if $sendMessage}
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_send_message"><b>Send messages</b></a><br/>Send messages to other users</li>
	{/if}


</ul>
<h3>Current projects</h3>
{if empty($projects)}
You are not assigned to any project.
{else}
<a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list">Click here</a> to view your projects.
{/if}
<br /><br />

