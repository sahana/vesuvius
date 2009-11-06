<div class="form-container">
	<form>
		<fieldset>
			<legend><?php echo _("Delete Project"); ?></legend>
			<?php echo _("Are you sure you want to remove"); ?> "<?php echo($name); ?>" <?php echo _("from the system?"); ?><br />
			<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id=<?php echo($proj_id); ?>"><?php echo _("Cancel"); ?></a> |
			<a href="?mod=vm&amp;act=project&amp;vm_action=process_delete&amp;proj_id=<?php echo($proj_id); ?>"><?php echo _("Delete"); ?></a>
		</fieldset>
	</form>
</div>

