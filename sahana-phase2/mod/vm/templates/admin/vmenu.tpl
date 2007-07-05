{if $skills || $acl || $managers || $search_registry || $clear_cache}
	<div id="submenu_v">
	<a href="?mod=vm&amp;act=adm_default">VM Admin Home</a>

	{if $skills}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=display_modify_skills">Skill Set Modifications</a>
	{/if}

	{if $acl}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=display_acl_situations">Access Control Modifications</a>
	{/if}

	{if $managers}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=display_approve_managers">Site Manager Approval</a>
	{/if}

	{if $search_registry}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_update_phonetics">Update Search Registry</a>
	{/if}

	{if $clear_cache}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_clear_cache">Clear Template Cache</a>
	{/if}

	</div><br />
{/if}