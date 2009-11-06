<h1 align=center>_("Volunteer Management")</h1>
<p>_("The Volunteer Management module keeps track of projects and volunteers.")</p>
<h3>_("Volunteer Portal")</h3><br/>
<ul style="margin-left: 1em;">
	<li><a href="?mod=vm&amp;act=default&amp;vm_action=display_single&amp;p_uuid={$p_uuid}"><b>_("My information page")</b></a><br/>_("Personal information and time logging.")  </li>
	{if $vol_assign}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_select_project"><b>_("Assign to Project")</b></a><br>_("Manage volunteer assignments")</li>
	{/if}

	{if $showAssigned}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_assigned"><b>_("Show Assigned")</b></a><br/>_("View all volunteers assigned to projects")
	{/if}

	{if $listVolunteers}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_all"><b>_("View All Volunteers")</b></a><br/>_("View all registered volunteers")
	{/if}

	{if $search}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_search"><b>_("Search")</b></a><br/>_("Search for a volunteer")
	{/if}

	{if $add_proj}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_add"><b>_("Add New Project")</b></a><br/>_("Start a new project")</li>
	{/if}

	{if $listMyProjects}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list"><b>_("View My Projects")</b></a><br/>_("View all projects you are currently assigned to")
	{/if}

	{if $listAllProjects}
		<li><a href="?mod=vm&amp;act=project"><b>_("View All Projects")</b></a><br/>_("View all projects being tracked")</li>
	{/if}

	{if $inbox}
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_custom_report_select"><b>_("Generate report")</b></a><br/>_("Generate customized report on volunteers and projects")</li>
	{/if}

	{if $outbox}
		<li><a href="?mod=vm&amp;act=volunteer&vm_action=display_add"><b>_("Register to VM")</b></a><br />_("Register yourself in Volunteer Management module")</li>
	{/if}

	{if $sendMessage}
		<li>
			<a href="?mod=vm&amp;act=volunteer&vm_action=display_send_message"><b>_("Send messages")</b></a>
			<br />
			_("Send messages to other users")
		</li>
	{/if}


</ul>
<h3>_("Current projects")</h3>
<p>
{if empty($projects)}
	_("You are not assigned to any project.")
{else}
<a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list">_("Click here")</a> _("to view your projects").
{/if}
</p>
<h3>_("Current features include:")</h3>
</p>
<ul style="margin-left: 1em;">
	<li>_("Manage volunteer assignment")</li>
	<li>_("Start and view projects")</li>
	<li>_("Search volunteers")</li>
	<li>_("Send and receive messages")</li>
</ul>

<SMALL>_("Version") 1.4, _("Last Modified") 05/25/2008 01:40 EST </SMALL>
<br /><br />

