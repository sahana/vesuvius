{if $skills || $acl || $managers || $search_registry || $clear_cache}
	<h3>Administrative Functions</h3>
	The following is a description of each administrative function for the VM module:<br /><br />
	<ul>
		{if $skills}
		<li><b>Skills Set Modifications</b><br /> Add or remove skills a volunteer or project can request</li><br />
		{/if}

		{if $acl}
		<li><b>Access Control Modifications</b><br /> Modify how access to the VM module is handled</li><br />
		{/if}

		{if $managers}
		<li><b>Site Manager Approval</b><br /> Give a site manager approval to fulfill site management duties</li><br />
		{/if}

		{if $search_registry}
		<li><b>Update Search Registry</b><br /> Since a volunteer's name may change in other places in Sahana, you may have to periodically update
	the search registry with current sounds-like name matching for volunteer searching</li><br />
		{/if}

		{if $clear_cache}
		<li><b>Clear Template Cache</b><br />Delete all PHP templates that have been cached</li><br />
		{/if}
	</ul>
{else}
	{php}
		global $global;
		require_once($global['approot'].'inc/lib_security/lib_acl.inc');
		shn_error_display_restricted_access();
	{/php}
{/if}