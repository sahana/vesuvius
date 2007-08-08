<h3>Approve Site Managers</h3><br />

<div style="text-align: center; font-weight: bold;">Current or Previous Applicants</div>
{if count($managers) == 0}
<br /><center>There are no managers to approve or revoke manager approval from</center>
{else}
<br />
<br />
<table align="center">
	<thead>
		<tr>
			<td>Current Status</td>
			<td>Approve</td>
			<td>Deny / Revoke</td>
			<td>Volunteer</td>
		</tr>
	</thead>
	<tbody>
		{foreach $managers as $p_uuid => $info}
			<tr align="center">
				<form action="?mod=vm&amp;act=volunteer&amp;vm_action=process_approval_modifications" method="post">
					<input type="hidden" name="vol_id" value="{$p_uuid}" />
					<td>
						{if $info['status']=='approved'}
							<b style="color: green;">Approved</b>
						{else}
							{if $info['status']=='denied'}
								<b style="color: #D00;">Denied</b>
							{else}
								<b style="color: #F80;">Unapproved</b>
							{/if}
						{/if}
					</td>
					{php}
						if($info['status']=='approved')
						{
							$approveButtonShow = 'disabled';
							$denyButtonName = 'Revoke';
						}
						else
						{
							$approveButtonShow = '';
							$denyButtonName = 'Deny';
						}

						if($info['status']=='denied')
						{
							$denyButtonName = '(Denied)';
							$denyButtonShow = 'disabled';
						}
						else
						{
							$denyButtonShow = '';
						}
					{/php}
					<td><input type="submit" name="approve" value="Approve" {$approveButtonShow} /></td>
					<td><input type="submit" name="deny" value="{$denyButtonName}" {$denyButtonShow} /></td>
					<td><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid={$p_uuid}">{$info.name}</a></td>
				</form>
			</tr>
		{/foreach}
	</tbody>
</table>
{/if}
<br />
<br />
<div style="text-align: center; font-weight: bold;">Upgrade Non-Applicants</div>
<br />
<br />
<center>
	<form action="?mod=vm&amp;act=volunteer&amp;vm_action=process_approval_upgrades" method="post">
		<select name="vol_id">
			{foreach $volunteers as $p_uuid => $name}
				<option value="{$p_uuid}">{$name}</option>
			{/foreach}
		</select>
		<input type="submit" value="Upgrade this Volunteer to Site Manager Status" />
	</form>
</center>