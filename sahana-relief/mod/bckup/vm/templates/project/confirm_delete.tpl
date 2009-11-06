<div class="form-container">
	<form>
		<fieldset>
			<legend>_("Delete Project")</legend>
			_("Are you sure you want to remove") "{$name}" _("from the system?")<br />
			<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$proj_id}">_("Cancel")</a> |
			<a href="?mod=vm&amp;act=project&amp;vm_action=process_delete&amp;proj_id={$proj_id}">_("Delete")</a>
		</fieldset>
	</form>
</div>

