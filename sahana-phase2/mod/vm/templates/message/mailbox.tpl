{if $box}
<center><h2>_("Inbox")</h2></center>
{else}
<center><h2>_("Outbox")</h2></center>
{/if}

{if count($messages) > 0}

<table align="center">
	<thead>
		<tr>
			<td>_("Delete")</td>
			{if $box}
			<td>_("From")</td>
			{else}
			<td>_("To")</td>
			{/if}
			<td>_("Date Sent")</td>
			<td>_("Preview")</td>
		</tr>
	</thead>
	{foreach $messages as $msg}
		<tr bgcolor="{$msg.bgcolor}">
			{php}
				$c_page = isset($_REQUEST['page']) ? $_REQUEST['page'] : 1;
				$rpp = isset($_REQUEST['rpp']) ? $_REQUEST['rpp'] : VM_DEFAULT_RPP;
			{/php}
			<td style="text-align: center;" onClick="if(!confirm('_("Are you sure you want to delete this message?")')) return false;"><a href="index.php?mod=vm&amp;act=volunteer&amp;vm_action=process_delete_message&amp;msg_id={$msg.message_id}&amp;box={$box_name}&amp;page={$c_page}&amp;rpp={$rpp}">X</a></td>
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
<center><i>_("Your") {php} echo $box? 'inbox':'outbox'; {/php} _("is empty").</i></center>

{/if}