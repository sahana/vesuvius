{if !empty($message)}
	{if $box}
	<b>From: </b> {$message.from} <br />
	{/if}
	<b>To: </b> {$message.to}
	<br />
	<b>Sent: </b> {$message.time}
	<br /> <br />
	<h3>Message: </h3> {$message.message}
	<br /> <br />
{else}
	{php}
		add_error('Message not found.');
	{/php}
{/if}

{if $box}
<a href="index.php?mod=vm&act=volunteer&vm_action=display_mailbox">Back to Inbox</a>
{else}
<a href="index.php?mod=vm&act=volunteer&vm_action=display_mailbox&box=outbox">Back to Outbox</a>
{/if}
| <a href="#" onClick="if(confirm('Are you sure you want to delete this message?')) window.location = 'index.php?mod=vm&act=volunteer&vm_action=process_delete_message&msg_id={$message.message_id}&box=inbox';">Delete this message</a>