<h3>Approve Site Managers</h3><br />
{if count($managers) == 0}
<br /><center>There are no managers to approve or revoke manager approval from</center>
{else}
<table align="center">
	<thead>
		<tr>
			<td>Current Manager Status</td>
			<td>Approve</td>
			<td>Deny / Revoke</td>
			<td>Site Manager</td>
		</tr>
	</thead>
	<tbody>
		{foreach $managers as $p_uuid => $info}
			<tr align="center">
				<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_manager_approval" method="post">
					<input type="hidden" name="mgr_id" value="{$p_uuid}" />
					<td>
						{if $info['approved']}
							<b style="color: green;">Approved</b>
						{else}
							<b style="color: red;">Unpproved</b>
						{/if}
					</td>
					<td><input type="submit" name="approve" value="Approve" {php}echo $info['approved']?'disabled':''{/php}/></td>
					<td><input type="submit" name="deny" value="{php}echo $info['approved']?'Revoke':'Deny'{/php}" /></td>
					<td><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid={$p_uuid}">{$info.name}</a></td>
				</form>
			</tr>
		{/foreach}
	</tbody>
</table>
{/if}