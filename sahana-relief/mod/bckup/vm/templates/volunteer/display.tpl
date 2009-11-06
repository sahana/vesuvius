{if $edit_auth || $delete_auth}
	<div id="submenu_v">
		{if $edit_auth}
			<a href = '?mod=vm&act=volunteer&vm_action=display_edit&p_uuid={$p_uuid}'>_("Edit")</a>
		{/if}
		{if $delete_auth && $p_uuid != $_SESSION['user_id']}
			<a href = '?mod=vm&act=volunteer&vm_action=display_confirm_delete&p_uuid={$p_uuid}'>_("Delete")</a>
		{/if}
	</div>
{/if}
<br>
{if !empty($pictureID)}
<center><img style="padding-bottom: 1em;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=full&amp;id={$pictureID}" /></center>
{/if} </br>
<table align="center" border="0">
	<tr>
		<br>
		<td><b>_("Name:")</b></td>
		<td>{$info.full_name}</td>
	</tr>
	<tr>
		<td><b>_("Gender:")</b></td>
		<td>{$info.gender}</td>
	</tr> </br>
	{if $view_auth == VM_ACCESS_ALL && !empty($ids)}
	<tr>
		<td><b>ID:</b></td>
		<td>
			{foreach $ids as $type => $value}
				{$id_types.$type}: {$value}<br />
			{/foreach}
		</td>
	</tr>
	{/if}
	{if !empty($locations)}
	<tr>
		<td><b>Location:</b></td>
		<td>
			{foreach $locations as $loc}
				{$loc.name}<br />
			{/foreach}
		</td>
	</tr>
	{/if}
	{if $view_auth == VM_ACCESS_ALL && !empty($dob)}
	<tr>
		<td><b>_("Date of Birth:")</b></td>
		<td>{$dob}</td>
	</tr>
	{/if}
</table>
<br />
{if !empty($info['contact'])}
	<h2>_("Contact Info")</h2>
	<table align="center" border="0">
		{foreach $info['contact'] as $type => $value}
			{if strlen($value) > 0}
			<tr>
				<td><b>{$contact_types.$type}:</b></td>
				<td>{$value}</td>
			</tr>
			{/if}
		{/foreach}
	</table>
	<br />
{/if}
<h2>_("Availability")</h2>
<table align="center" border="0">
	<tr>
		<td><b>_("Work Begin:")</b></td>
		<td>{$date_start}</td>
	</tr>
	<tr>
		<td><b>_("Work End:")</b></td>
		<td>{$date_end}</td>
	</tr>
	{if !empty($hour_start)}
		<tr>
			<td><b>_("Work Hour Begin:")</b></td>
			<td>{$hour_start}</td>
		</tr>
	{/if}
	{if !empty($hour_end)}
		<tr>
			<td><b>_("Work Hour End:")</b></td>
			<td>{$hour_end}</td>
		</tr>
	{/if}
</table>
<br />

<h2>_("Work Details")</h2>
<table align="center" border="0">
	{if !empty($occupation)}
	<tr>
		<td><b>_("Occupation:")</b></td>
		<td>{$occupation}</td>
	</tr>
	{/if}


	{if !empty($affiliation)}
	<tr>
		<td><b>_("Affiliation:")</b></td>
		<td>{$affiliation}</td>
	</tr>
	</table>
	{/if}
			{if count($projects) > 0}
	<table align= "center">
		<thead>
			<tr>
				<td> _("Project") </td>
				<td>_("Position")</td>
				<td>_("Log Time")</td>
			</tr>
		</thead>
		<tbody>

		{foreach  $VolPositions as $position}
			<tr>
				<td><a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$position.proj_id}">{$position.project_name}</a></td>
				<td>{$position.title}</td>
				<td style="text-align: center">
					{php}
						if($ac->isAuthorized(false, $ac->buildURLParams('volunteer', 'display_log_time_form', array('pos_id' => $position['pos_id'], 'p_uuid' => $p_uuid))))
						{
					{/php}
						<a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_log_time_form&amp;p_uuid={$p_uuid}&amp;pos_id={$position.pos_id}">_("Log time")</a>
					{else}
						---
					{/if}
				</td>
			</tr>
		{/foreach}

		</tbody>
	</table>
			{else}
			(none)
			{/if}


</table>
<br />
<h2>_("Skills and Work Restrictions")</h2>
<?php
$vol_skills->display();
?>
{if !empty($special_needs)}
	<tr>
	<br>
		<td><b>_("Special Needs:") </b></td>
		<td>{$special_needs}</td>
	</br>
	</tr>
{/if}

