<h2>Personal Info</h2>
{if !empty($pictureID)}
<center><img style="padding-bottom: 1em;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=full&amp;id={$pictureID}" /></center>
{/if}
<table align="center" border="0">
	<tr>
		<td><b>Name:</b></td>
		<td>{$info.full_name}</td>
	</tr>
	<tr>
		<td><b>Gender:</b></td>
		<td>{$info.gender}</td>
	</tr>
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
		<td><b>Date of Birth:</b></td>
		<td>{$dob}</td>
	</tr>
	{/if}
</table>
<br />
{if !empty($info['contact'])}
	<h2>Contact Info</h2>
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
<h2>Availability</h2>
<table align="center" border="0">
	<tr>
		<td><b>Work Begin:</b></td>
		<td>{$date_start}</td>
	</tr>
	<tr>
		<td><b>Work End:</b></td>
		<td>{$date_end}</td>
	</tr>
	{if !empty($hour_start)}
		<tr>
			<td><b>Work Hour Begin:</b></td>
			<td>{$hour_start}</td>
		</tr>
	{/if}
	{if !empty($hour_end)}
		<tr>
			<td><b>Work Hour End:</b></td>
			<td>{$hour_end}</td>
		</tr>
	{/if}
</table>
<br />

<h2>Work Details</h2>
<table align="center" border="0">
	{if !empty($occupation)}
	<tr>
		<td><b>Occupation:</b></td>
		<td>{$occupation}</td>
	</tr>
	{/if}
	{if !empty($affiliation)}
	<tr>
		<td><b>Affiliation:</b></td>
		<td>{$affiliation}</td>
	</tr>
	{/if}
	<tr>
		<td><b>Project(s):</b></td>
		<td>
			{if count($projects) > 0}
				{foreach $projects as $id => $name}
				<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$id}">{$name}</a><br />
				{/foreach}
			{else}
			(none)
			{/if}
		</td>
	</tr>
</table>
<br />
<h2>Skills</h2>
<?
$vol_skills->display();
?>
<br />
{if $edit_auth}
<a href = '?mod=vm&act=volunteer&vm_action=display_edit&p_uuid={$p_uuid}'>Edit</a>
{/if}
{if $delete_auth && $p_uuid != $_SESSION['user_id']}
<a href = '?mod=vm&act=volunteer&vm_action=display_confirm_delete&p_uuid={$p_uuid}'>Delete</a>
{/if}