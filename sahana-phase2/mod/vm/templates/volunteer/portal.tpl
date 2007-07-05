<h1>Volunteer Management</h1>
The Volunteer Management module keeps track of projects and volunteers. From here, you can:
<ul style="margin-left: 1em;">
	<li><a href="?mod=vm&amp;act=default&amp;vm_action=display_single&amp;p_uuid={$p_uuid}">View your info page</a></li>
	{if $vol_assign}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_select_project">Assign to Project</a> - Manage volunteer assignments</li>
	{/if}

	{if $showAssigned}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_assigned">Show Assigned</a> - View all volunteers assigned to projects
	{/if}

	{if $listVolunteers}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_list_all">View All Volunteers</a> - View all registered volunteers
	{/if}

	{if $search}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_search">Search</a> - Search for a volunteer
	{/if}

	{if $add_proj}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_add">Add New Project</a> - Start a new project
	{/if}

	{if $listMyProjects}
		<li><a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list">View My Projects</a> - View all projects you are currently assigned to
	{/if}

	{if $listAllProjects}
		<li><a href="?mod=vm&amp;act=project">View All Projects</a> - View all projects being tracked</li>
	{/if}

	{if $inbox}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox">Inbox</a> - View all messages sent to you</li>
	{/if}

	{if $outbox}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox&amp;box=outbox">Outbox</a> - View all messages sent by you</li>
	{/if}

	{if $sendMessage}
		<li><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_send_message">Send Message</a> - Send a message to another volunteer</li>
	{/if}


</ul>
<h3>Projects</h3>
{if empty($projects)}
You are not assigned to any project.
{else}
<a href="?mod=vm&amp;act=project&amp;vm_action=display_my_list">Click here</a> to view your projects.
{/if}
<br /><br />

<h3>Messages</h3>
You have
{if $messages < 1} no unread messages.
{else}
<a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox">{$messages} unread message{php}echo $messages > 1? 's':'';{/php}.</a>
{/if}