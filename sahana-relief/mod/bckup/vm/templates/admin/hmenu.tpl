{if $acl || $search_registry || $clear_cache || $audit_acl}
	<div id="submenu_v">
	<a href="?mod=vm&amp;act=adm_default">_("VM Admin Home")</a>

	{if $acl}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=display_acl_situations">_("Access Control Modifications")</a>
	{/if}

	{if $search_registry}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_update_phonetics">_("Update Search Registry")</a>
	{/if}

	{if $clear_cache}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_clear_cache">_("Clear Template Cache")</a>
	{/if}

	{if $audit_acl}
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl">_("Audit ACL")</a>
	{/if}

	</div><br />
{/if}