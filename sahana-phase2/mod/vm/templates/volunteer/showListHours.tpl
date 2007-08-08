<h2 style="text-align: center;"> Pending Hours Approval </h2>
	<input type="hidden" name="p_uuid" value="{$p_uuid}" />
	<input type="hidden" name="pos_id" value="{$pos_id}" />
<tr>
	<table>
        	<td><b>Name :</b></td>
        	<td>{$full_name}</td>
        </tr>
        <tr>
        	<td><b>Project :</b></td>
        	<td>{$project_name}</td>
        </tr>
	</table>
	<table>
		{foreach $volunteers as $v}
		<tr>
        	<td>{$v.title}</td>
        	<td>{$v.project_name}</td>
        	<td>{$v.position}</td>
        	 <td><a href="#"> View Hours </a></td>
		</tr>
		{/foreach}
	</table>