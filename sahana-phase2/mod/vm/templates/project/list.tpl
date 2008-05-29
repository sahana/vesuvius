{if count($projects) > 0}
<table align=center>
    <thead>
        <tr>
            <td>_("Name")</td>
            <td>_("Description")</td>
        </tr>
    </thead>
    <tbody>
    {foreach $projects as $id => $info}
        <tr>
            <td><a href='?mod=vm&act=project&vm_action=display_single&proj_id={$id}'>{$info.name}</a></td>
			<td>{$info.description}</td>
        </tr>
    {/foreach}
    </tbody>
</table>
{else}
<center>(_("no projects"))</center>
{/if}
<br />