<div class="form-container">
	<form>
		<fieldset>
			<legend>_("Delete Volunteer")</legend>
			_("Are you sure you want to retire") "{$name}"?<br />
			<a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid={$p_uuid}">_("Cancel")</a> |
			<a href="?mod=vm&amp;act=volunteer&amp;vm_action=process_delete&amp;p_uuid={$p_uuid}">_("Delete")</a>
		</fieldset>
	</form>
</div>

