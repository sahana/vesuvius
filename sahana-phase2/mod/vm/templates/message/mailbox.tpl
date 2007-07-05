{if $box}
<center><h2>Inbox</h2></center>
{else}
<center><h2>Outbox</h2></center>
{/if}

{if count($messages) > 0}

<table align="center">
	<thead>
		<tr>
			<td>Delete</td>
			{if $box}
			<td>From</td>
			{else}
			<td>To</td>
			{/if}
			<td>Date Sent</td>
			<td>Preview</td>
		</tr>
	</thead>
	{foreach $messages as $msg}
		<tr bgcolor="{$msg.bgcolor}">
			<td style="text-align: center; cursor: pointer; font-weight: bold;" onMouseOver="this.style.color='red'" onMouseOut="this.style.color='black'" onClick="if(confirm('Are you sure you want to delete this message?')) window.location = 'index.php?mod=vm&act=volunteer&vm_action=process_delete_message&msg_id={$msg.message_id}&box={$box_name}';">X</td>
			{if $box}
			<td>{$msg.from}</td>
			{else}
			<td>{$msg.to}</td>
			{/if}
			<td>{$msg.time}</td>
			<td>
				{if $box}
				<a href="index.php?mod=vm&act=volunteer&vm_action=display_message&msg_id={$msg.message_id}&box=inbox">{$msg.message}</a>
				{else}
				<a href="index.php?mod=vm&act=volunteer&vm_action=display_message&msg_id={$msg.message_id}&box=outbox">{$msg.message}</a>
				{/if}
			</td>
		</tr>
	{/foreach}

</table>

{else}
<center><i>Your {php} echo $box? 'inbox':'outbox' {/php} is empty.</i></center>

{/if}