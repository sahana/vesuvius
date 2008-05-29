<h2 align="center">_("hours for review on") {$project_name}<h2>

<form action="" >

	<input type="hidden" name="p_uuid" value="{$p_uuid}" />
	<input type="hidden" name="pos_id" value="{$pos_id}" />

	<table>
		<tr>
			<td>_("Name")</td>
			<td>_("Project")</td>
			<td>_("Position")</td>
			<td>_("Pay Rate ")</td>
			<td>_("Start ")</td>
			<td>_("End ")</td>
		</tr>
	</table>

	<table>
		<tr>
			{foreach $shifts as $s }
	 <tr>
	 <td>{$s.full_name}</td>
	 <td>{$s.project_name}</td>
	 <td>{$s.position}</td>
	 <td>{$s.payrate}</td>
	 <td>{$s.start}</td>
	 <td>{$s.end}</td>

	 _("Approved:") <input type="radio" name="status_{$s.shift_id}" value="Approve" />

	 _("Denied:") <input type="radio" name="status_{$s.shift_id}" value="Denied" />


		</td>
      </tr>
		 {/foreach }

	</table>

</form>
