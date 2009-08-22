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
		add_error(_('Message not found.'));
	{/php}
{/if}

{if $box}
<a href="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox&amp;rpp=<?php echo VM_DEFAULT_MAILBOX_RPP; ?>">_("Back to Inbox")</a>
{else}
<a href="index.php?mod=vm&amp;act=volunteer&amp;vm_action=display_mailbox&amp;box=outbox&amp;rpp=<?php echo VM_DEFAULT_MAILBOX_RPP; ?>">_("Back to Outbox")</a>
{/if}
| <a href="index.php?mod=vm&amp;act=volunteer&amp;vm_action=process_delete_message&amp;msg_id={$message.message_id}&amp;box=<?php echo ($box ? 'inbox' : 'outbox'); &amp;rpp=<?php echo VM_DEFAULT_MAILBOX_RPP; ?>" onClick="if(!confirm('_("Are you sure you want to delete this message?")')) return false;">_("Delete this message")</a>