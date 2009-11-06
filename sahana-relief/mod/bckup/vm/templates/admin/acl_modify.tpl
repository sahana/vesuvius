<script type="text/javascript">
/*
 * A function to get rid of a row in the classification table
 *
 * @param node 	- a reference to the node (a table cell) that is being clicked on to remove the data
 * @return void
 */

function remove_classification_row(node)
{
	var num_rows = 0;
	var table_body = node.parentNode.parentNode;
	for(var i = 0; i < table_body.childNodes.length; i++)
	{
		if(table_body.childNodes[i].tagName == 'TR')
			num_rows++;
	}

	table_body.removeChild(node.parentNode);
	if(num_rows == 1)
	{
		document.getElementById('no_tables_message').style.display = 'block';
		document.getElementById('overall_table_crud_list').style.display = 'none';
	}
}

</script>

<h3>_("Access Control")</h3>

<form action="?mod=vm&amp;act=adm_default&amp;vm_action=process_acl_modifications" method="post">
	<input type="hidden" name="acl_act" value="{$act}" />
	<input type="hidden" name="acl_vm_action" value="{$vm_action}" />
	<b>Modifying access control constraints for access request '<i>{$request_description}</i>'</b><br /><br />

	<h4>Data Classification Constraints</h4>
	<center>
		<b id="no_tables_message"
			{if !empty($request_constraints['tables'])}
				style="display: none";
			{/if}
		>(none)</b>

	<table id="overall_table_crud_list"
	{if empty($request_constraints['tables'])}
		style="display: none;"
	{/if}>
		<thead>
			<tr>
				<td>_("Table Name")</td>
				<td>_("Create")</td>
				<td>_("Read")</td>
				<td>_("Update")</td>
				<td>_("Delete")</td>
				<td>_("Remove From List")</td>
			</tr>
		</thead>
		<tbody id="table_crud_list">
		{foreach $request_constraints['tables'] as $table_name => $crud}
			<tr id="table_{$table_name}_crud">
				<td>{$table_name}</td>
				<td><input type="checkbox" name="table_{$table_name}_req_c" value="on" {php}if(substr_count($crud, 'c') > 0) echo 'checked';{/php} /></td>
				<td><input type="checkbox" name="table_{$table_name}_req_r" value="on" {php}if(substr_count($crud, 'r') > 0) echo 'checked';{/php} /></td>
				<td><input type="checkbox" name="table_{$table_name}_req_u" value="on" {php}if(substr_count($crud, 'u') > 0) echo 'checked';{/php} /></td>
				<td><input type="checkbox" name="table_{$table_name}_req_d" value="on" {php}if(substr_count($crud, 'd') > 0) echo 'checked';{/php} /></td>
				<td style="cursor: pointer; color: black; font-size: 18px; font-family: 'Comic Sans MS'; text-align: center;"
				    onMouseOver="this.style.color = 'red';" onMouseOut="this.style.color = 'black';"
				    onClick="remove_classification_row(this);">x</td>
			</tr>
		{/foreach}
		</tbody>
	</table>
	<br /><br />
	<select id="table_to_add">
		{foreach $tables as $table}
			<option value="{$table}">{$table}</option>
		{/foreach}
	</select>
	<input type="button" value="Add to List" onClick="

	var table_list = document.getElementById('table_to_add');
	var table_name = table_list.options[table_list.selectedIndex].value;
	var table_crud = document.getElementById('table_crud_list');

	//check to see if the table is already in the list and return if so

	for(var i = 0; i < table_crud.childNodes.length; i++)
	{
		if(table_crud.childNodes[i].id == ('table_' + table_name + '_crud'))
			return;
	}

	//add the row to the table

	var row = document.createElement('tr');
	row.setAttribute('id', 'table_' + table_name + '_crud');
	var cell = document.createElement('td');
	cell.appendChild(document.createTextNode(table_name));
	row.appendChild(cell);

	var box;
	cell = document.createElement('td');
	box = document.createElement('input');
	box.setAttribute('type', 'checkbox');
	box.setAttribute('name', 'table_' + table_name + '_req_c');
	box.setAttribute('value', 'on');
	cell.appendChild(box);
	row.appendChild(cell);

	cell = document.createElement('td');
	box = document.createElement('input');
	box.setAttribute('type', 'checkbox');
	box.setAttribute('name', 'table_' + table_name + '_req_r');
	box.setAttribute('value', 'on');
	cell.appendChild(box);
	row.appendChild(cell);

	cell = document.createElement('td');
	box = document.createElement('input');
	box.setAttribute('type', 'checkbox');
	box.setAttribute('name', 'table_' + table_name + '_req_u');
	box.setAttribute('value', 'on');
	cell.appendChild(box);
	row.appendChild(cell);

	cell = document.createElement('td');
	box = document.createElement('input');
	box.setAttribute('type', 'checkbox');
	box.setAttribute('name', 'table_' + table_name + '_req_d');
	box.setAttribute('value', 'on');
	cell.appendChild(box);
	row.appendChild(cell);

	cell = document.createElement('td');
	cell.appendChild(document.createTextNode('x'));

	cell.style.cursor = 'pointer';
	cell.style.color = 'black';
	cell.style.fontSize = '18px';
	cell.style.fontFamily = 'Comic Sans MS';
	cell.style.textAlign = 'center';
	row.appendChild(cell);

	try
	{
		cell.addEventListener('mouseover', function(e) {e.target.style.color = 'red';}, false);
	}
	catch(err)
	{
		cell.attachEvent('onmouseover', function(e) {e.srcElement.style.color = 'red';});
	}

	try
	{
		cell.addEventListener('mouseout', function(e) {e.target.style.color = 'black';}, false);
	}
	catch(err)
	{
		cell.attachEvent('onmouseout', function(e) {e.srcElement.style.color = 'black';});
	}

	try
	{
		cell.addEventListener('click', function(e) {remove_classification_row(e.target);}, false);
	}
	catch(err)
	{
		cell.attachEvent('onclick', function(e) {remove_classification_row(e.srcElement);});
	}

	table_crud.appendChild(row);

	//make the overall table visible in case it's not already visible

	document.getElementById('overall_table_crud_list').style.display = 'block';

	//get rid of the '(none)' if it's not yet gone

	document.getElementById('no_tables_message').style.display = 'none';

	" />
	</center>
	<br /><br />
	<h4>_("Special Constraints")</h4>
	{foreach $possible_constraints as $code => $desc}
		{php}
			$matches = array();
			preg_match("/^\s*(\w+)(.*)/", $desc, $matches);
		{/php}
		<input type="checkbox" value="_("on")" name="constraint_{$code}_req"

		{if in_array($code, $request_constraints['extra'])}
		checked
		{/if}

		/>
		{if strcasecmp($matches[1], 'require') == 0}
			<b style="color: #900">
		{else if strcasecmp($matches[1], 'override') == 0}
			<b style="color: #090">
		{else}
			<b style="color: #00C">
		{/if}
		{$matches.1}</b>{$matches.2}
		<br /><br />
	{/foreach}

	<br /><br />
	<center>
		<input type="submit" value="_("Save Changes")" />
		<input type="button" value="_("Cancel Changes")" onClick="window.location='index.php?mod=vm&act=adm_default&vm_action=display_acl_situations';" />
	</center>
</form>