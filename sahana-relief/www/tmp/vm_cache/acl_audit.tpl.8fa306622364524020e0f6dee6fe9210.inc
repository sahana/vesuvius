<h3><?php echo _("ACL Audit"); ?></h3>
<br />

<?php if(empty($bad_requests) && empty($extra_requests) && empty($unclassified_tables)) { ?>
	<div class="confirmation message">
		<?php echo _("All access requests in the database and in the VM code match."); ?>
	</div>
<?php } 
 if(!empty($bad_requests)) { ?>
	<div class="warning message">
		<b style="color: #C00"><?php echo _("Warning:"); ?> </b><b><?php echo _("The following requests in the VM code are not under access control:"); ?></b>
	</div>
		<table align="center">
			<thead>
				<tr>
					<td>act</td>
					<td>vm_action</td>
					<td><?php echo _("Description"); ?></td>
					<td><?php echo _("Add"); ?></td>
				</tr>
			</thead>
			<tbody>
				<?php foreach($bad_requests as $request) { ?>
					<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
					<input type="hidden" name="request_act" value="<?php echo($request['act']); ?>" />
					<input type="hidden" name="request_vm_action" value="<?php echo($request['vm_action']); ?>" />
					<input type="hidden" name="process_action" value="add_request" />
						<tr>
							<td><?php echo($request['act']); ?></td>
							<td><?php echo($request['vm_action']); ?></td>
							<td><input type="text" name="request_desc" id="desc_<?php echo($request['act']); ?>_<?php echo($request['vm_action']); ?>" /></td>
							<td><input type="submit" value="<?php echo _("Add"); ?>" onClick="if(document.getElementById('desc_<?php echo($request['act']); ?>_<?php echo($request['vm_action']); ?>').value == '') {alert(<?php echo _("Please enter a description"); ?>); return false;}" /></td>
						</tr>
					</form>
				<?php } ?>
			</tbody>
		</table>
		<br />
	<br />
<?php } 
 if(!empty($extra_requests)) { ?>
	<div class="warning message">
		<b style="color: #C00"><?php echo _("Warning"); ?>: </b><b><?php echo _("The following requests in the database are never referenced"); ?>:</b>
	</div>
	<table align="center">
		<thead>
			<tr>
				<td>act</td>
				<td>vm_action</td>
				<td><?php echo _("Description"); ?></td>
				<td><?php echo _("Remove From Database"); ?></td>
			</tr>s
		</thead>
		<tbody>
			<?php foreach($extra_requests as $act => $request) { 
 foreach($request as $vm_action => $description) { ?>
					<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
						<input type="hidden" name="request_act" value="<?php echo($act); ?>" />
						<input type="hidden" name="request_vm_action" value="<?php echo($vm_action); ?>" />
						<input type="hidden" name="process_action" value="remove_request" />
							<tr>
								<td><?php echo($act); ?></td>
								<td><?php echo($vm_action); ?></td>
								<td><?php echo($description); ?></td>
								<td style="text-align: center"><input type="submit" value="<?php echo _("Remove"); ?>" /></td>
							</tr>
					</form>
				<?php } 
 } ?>
		</tbody>
	</table>
	<br />
<?php } 
 if(!empty($unclassified_tables)) { ?>
	<div class="warning message">
		<b style="color: #C00"><?php echo _("Warning"); ?>: </b><b><?php echo _("The following database tables/views have not been given any classification level"); ?>:</b>
	</div>
	<table align="center">
		<thead>
			<tr>
				<td><?php echo _("Table"); ?></td>
				<td><?php echo _("Classification Level"); ?></td>
				<td><?php echo _("Add"); ?></td>
			</tr>
		</thead>
		<tbody>
			<?php foreach($unclassified_tables as $table) { ?>
				<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
					<input type="hidden" name="table_to_classify" value="<?php echo($table); ?>" />
					<input type="hidden" name="process_action" value="classify_table" />
					<tr>
						<td><?php echo($table); ?></td>
						<td>
							<select name="classification_level">
								<?php foreach($classification_levels as $id => $desc) { ?>
									<option value="<?php echo($id); ?>"><?php echo($desc); ?></option>
								<?php } ?>
							</select>
						</td>
						<td><input type="submit" value="<?php echo _("Add"); ?>" /></td>
					</tr>
				</form>
			<?php } ?>
		</tbody>
	</table>
<?php } ?>