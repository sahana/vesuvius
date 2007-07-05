<h2 style="text-align: center;">Project Details</h2>

<table align=center>
    <tbody>
        <tr>
        	<td><b>Project Name :</b></td>
        	{if !$showVolunteersAssigned}
        	<td><a href='index.php?mod=vm&act=project&vm_action=display_single&proj_id={$proj_id}'>{$info.name}</a></td>
        	{else}
        	<td>{$info.name}</td>
        	{/if}
        </tr>
        <tr>
        	<td><b>Start Date :</b></td>
        	<td>{$start_date}</td>
        </tr>
        <tr>
        	<td><b>End Date :</b></td>
        	<td>{$end_date}</td>
        </tr>
        <tr>
        	<td><b>Location :</b></td>
        	<td>{$location}</td>
        </tr>
        <tr>
        	<td><b>Site Manager :</b></td>
        	<td><a href="?mod=vm&amp;act=volunteer&amp;vm_action=display_single&amp;p_uuid={$mgr_id}">{$mgr_name}</a> </td>
        </tr>
        <tr>
        	<td><b>Volunteers assigned :</b></td>
        	<td>{$numVolunteers}</td>
        </tr>

    </tbody>
</table>
<br />
{if $showVolunteersAssigned}
<h3>Description</h3>
{$info.description}
<br /><br />

<h3>Specialties needed</h3>
<br />
<?
$skills->display();
?>

<br />
{if $edit_auth}
<a href='?mod=vm&act=project&vm_action=display_edit&proj_id={$proj_id}'>Edit</a>
{/if}
{if $delete_auth}
<a href="?mod=vm&amp;act=project&vm_action=display_confirm_delete&proj_id={$proj_id}">Delete</a>
{/if}
<br /><br />

<div align="center">
	{if $numVolunteers > 0}
		Volunteers working on {$info.name}:
	{else}
		No volunteers are currently assigned to {$info.name}.
	{/if}
</div>
{/if}
<br />
