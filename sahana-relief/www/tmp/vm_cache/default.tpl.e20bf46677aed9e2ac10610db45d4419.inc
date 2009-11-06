<?php if($skills || $acl || $managers || $search_registry || $clear_cache) { ?>
	<h3><?php echo _("Administrative Functions"); ?></h3>
	<?php echo _("The following is a description of each administrative function for the VM module"); ?>:<br /><br />
	<ul>
		<?php if($acl) { ?>
			<li><b><?php echo _("Access Control Modifications"); ?></b><br /> <?php echo _("Modify how access to the VM module is handled"); ?></li><br />
		<?php } 
 if($search_registry) { ?>
			<li><b><?php echo _("Update Search Registry"); ?></b><br /> <?php echo _("Since a volunteer's name may change in other places in Sahana, you may have to periodically update the search registry with current sounds-like name matching for volunteer searching"); ?></li><br />
		<?php } 
 if($clear_cache) { ?>
			<li><b><?php echo _("Clear Template Cache"); ?></b><br /><?php echo _("Delete all PHP templates that have been cached"); ?></li><br />
		<?php } 
 if($audit_acl) { ?>
			<li><b><?php echo _("Audit ACL"); ?></b><br /><?php echo _("Verify that all 'act' and 'vm_action' combinations in the VM code are under access control and that all VM tables/views are classified"); ?></li><br />
		<?php } ?>
	</ul>
<?php } else { 
 
		global $global;
		require_once($global['approot'].'inc/lib_security/lib_acl.inc');
		shn_error_display_restricted_access();
	 
 } ?>