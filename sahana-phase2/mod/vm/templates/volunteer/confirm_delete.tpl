<div class="form-container">
	<form>
		<fieldset>
			<legend>Delete Volunteer</legend>
			Are you sure you want to remove "{$name}" from the system?<br />
			<a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid={$p_uuid}">Cancel</a> |
			<a href="?mod=vm&amp;act=volunteer&amp;vm_action=process_delete&amp;p_uuid={$p_uuid}">Delete</a>
		</fieldset>
	</form>
</div>

