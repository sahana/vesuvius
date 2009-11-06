<?php if($acl || $search_registry || $clear_cache || $audit_acl) { ?>
	<div id="submenu_v">
	<a href="?mod=vm&amp;act=adm_default"><?php echo _("VM Admin Home"); ?></a>

	<?php if($acl) { ?>
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=display_acl_situations"><?php echo _("Access Control Modifications"); ?></a>
	<?php } 
 if($search_registry) { ?>
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_update_phonetics"><?php echo _("Update Search Registry"); ?></a>
	<?php } 
 if($clear_cache) { ?>
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_clear_cache"><?php echo _("Clear Template Cache"); ?></a>
	<?php } 
 if($audit_acl) { ?>
	<a href="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl"><?php echo _("Audit ACL"); ?></a>
	<?php } ?>

	</div><br />
<?php } ?>