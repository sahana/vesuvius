{if $skills || $acl || $managers || $search_registry || $clear_cache}
	<h3>_("Administrative Functions")</h3>
	_("The following is a description of each administrative function for the VM module"):<br /><br />
	<ul>
		{if $acl}
			<li><b>_("Access Control Modifications")</b><br /> _("Modify how access to the VM module is handled")</li><br />
		{/if}

		{if $search_registry}
			<li><b>_("Update Search Registry")</b><br /> _("Since a volunteer's name may change in other places in Sahana, you may have to periodically update the search registry with current sounds-like name matching for volunteer searching")</li><br />
		{/if}

		{if $clear_cache}
			<li><b>_("Clear Template Cache")</b><br />_("Delete all PHP templates that have been cached")</li><br />
		{/if}

		{if $audit_acl}
			<li><b>_("Audit ACL")</b><br />_("Verify that all 'act' and 'vm_action' combinations in the VM code are under access control and that all VM tables/views are classified")</li><br />
		{/if}
	</ul>
{else}
	{php}
		global $global;
		require_once($global['approot'].'inc/lib_security/lib_acl.inc');
		shn_error_display_restricted_access();
	{/php}
{/if}