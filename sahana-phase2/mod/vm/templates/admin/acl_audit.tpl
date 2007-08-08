<h3>ACL Audit</h3>
<br />

{if empty($bad_requests) && empty($extra_requests) && empty($unclassified_tables)}
	<div class="confirmation message">
		All access requests in the database and in the VM code match.
	</div>
{/if}

{if !empty($bad_requests)}
	<div class="warning message">
		<b style="color: #C00">Warning: </b><b>The following requests in the VM code are not under access control:</b>
	</div>
		<table align="center">
			<thead>
				<tr>
					<td>act</td>
					<td>vm_action</td>
					<td>Description</td>
					<td>Add</td>
				</tr>
			</thead>
			<tbody>
				{foreach $bad_requests as $request}
					<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
					<input type="hidden" name="request_act" value="{$request.act}" />
					<input type="hidden" name="request_vm_action" value="{$request.vm_action}" />
					<input type="hidden" name="process_action" value="add_request" />
						<tr>
							<td>{$request.act}</td>
							<td>{$request.vm_action}</td>
							<td><input type="text" name="request_desc" id="desc_{$request.act}_{$request.vm_action}" /></td>
							<td><input type="submit" value="Add" onClick="if(document.getElementById('desc_{$request.act}_{$request.vm_action}').value == '') {alert('Please enter a description'); return false;}" /></td>
						</tr>
					</form>
				{/foreach}
			</tbody>
		</table>
		<br />
	<br />
{/if}

{if !empty($extra_requests)}
	<div class="warning message">
		<b style="color: #C00">Warning: </b><b>The following requests in the database are never referenced:</b>
	</div>
	<table align="center">
		<thead>
			<tr>
				<td>act</td>
				<td>vm_action</td>
				<td>Description</td>
				<td>Remove From Database</td>
			</tr>
		</thead>
		<tbody>
			{foreach $extra_requests as $act => $request}
				{foreach $request as $vm_action => $description}
					<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
						<input type="hidden" name="request_act" value="{$act}" />
						<input type="hidden" name="request_vm_action" value="{$vm_action}" />
						<input type="hidden" name="process_action" value="remove_request" />
							<tr>
								<td>{$act}</td>
								<td>{$vm_action}</td>
								<td>{$description}</td>
								<td style="text-align: center"><input type="submit" value="Remove" /></td>
							</tr>
					</form>
				{/foreach}
			{/foreach}
		</tbody>
	</table>
	<br />
{/if}

{if !empty($unclassified_tables)}
	<div class="warning message">
		<b style="color: #C00">Warning: </b><b>The following database tables/views have not been given any classification level:</b>
	</div>
	<table align="center">
		<thead>
			<tr>
				<td>Table</td>
				<td>Classification Level</td>
				<td>Add</td>
			</tr>
		</thead>
		<tbody>
			{foreach $unclassified_tables as $table}
				<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_audit_acl" method="post">
					<input type="hidden" name="table_to_classify" value="{$table}" />
					<input type="hidden" name="process_action" value="classify_table" />
					<tr>
						<td>{$table}</td>
						<td>
							<select name="classification_level">
								{foreach $classification_levels as $id => $desc}
									<option value="{$id}">{$desc}</option>
								{/foreach}
							</select>
						</td>
						<td><input type="submit" value="Add" /></td>
					</tr>
				</form>
			{/foreach}
		</tbody>
	</table>
{/if}