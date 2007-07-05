{if count($volunteers) > 0}
<table align=center>
    <thead>
        <tr>
            <td>Name</td>
            {if $listPictures}
	            <td>Picture</td>
			{/if}
			{if $showTask && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Assigned Task</td>
			{/if}
			{if $view_auth >= VM_ACCESS_PARTIAL}
	            <td>Status</td>
	            <td>Affiliation</td>
            {/if}
            {if $showAvailability && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>Availability<br />Start</td>
	            <td>Availability<br />End</td>
            {/if}
            {if $showIDs && $view_auth >= VM_ACCESS_ALL}
            	<td>Identification</td>
            {/if}
            {if $view_auth >= VM_ACCESS_PARTIAL}
            	<td>Location</td>
           	{/if}
			{if $showSkills && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Specialties</td>
			{/if}
			{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Assign</td>
			{/if}
			{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
	       		<td>Remove From Project</td>
			{/if}
			{if $showEditTask && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Edit Assigned Task</td>
			{/if}
        </tr>
    </thead>
    <tbody>
    {foreach $volunteers as $p_uuid => $vol}
        <tr style="text-align: center; background-color: white; height: {php}echo VM_IMAGE_THUMB_HEIGHT; {/php}px;" onMouseOver="this.style.backgroundColor = '#FFA';" onMouseOut="this.style.backgroundColor = 'white';">
            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid={$p_uuid}'>{$vol.full_name}</a></td>
            {if $listPictures}
			<td style="margin: 0; padding: 0; text-align: center;">
				{if !empty($vol['pictureID'])}
					<img  style="margin: 0; padding: 0;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=thumb&amp;id={$vol.pictureID}" />
				{/if}
			</td>
			{/if}
			{if $showTask && $view_auth >= VM_ACCESS_PARTIAL}
        		<td>{php} echo $vol['projs'][$proj_id]; {/php}</td>
        	{/if}
        	{if $view_auth >= VM_ACCESS_PARTIAL}
             <td>
             	{php}
             		$num_projs = count($vol['projs']);
             	{/php}
             	{if $num_projs == 0}
             		<b style="color: red">Unassigned</b>
             	{else}
             		<b style="color: green">Assigned</b> ({$num_projs})
             	{/if}
             </td>
             <td>{$vol.affiliation}</td>
             {/if}
	             {if $showAvailability && $view_auth >= VM_ACCESS_PARTIAL}
		             <td>{$vol.date_start}</td>
		             <td>{$vol.date_end}</td>
	             {/if}
	         {if $showIDs && $view_auth >= VM_ACCESS_ALL}
             <td>
	             {foreach $vol['ids'] as $name => $serial}
	             	<b>{$name}</b>: {$serial}<br />
	             {/foreach}
             </td>
             {/if}
             {if $view_auth >= VM_ACCESS_PARTIAL}
             <td>
             	{foreach $vol['locations'] as $key => $loc}
             		{$loc}<br />
             	{/foreach}
             </td>
             {/if}
			{if $showSkills && $view_auth >= VM_ACCESS_PARTIAL}
			<td>
				<select style="width: 100%;">
					{foreach $vol['skills'] as $opt_value => $desc}
						<option value="{$opt_value}">
							{php}
								echo preg_replace('/'.VM_SKILLS_DELIMETER.'/', ' '.VM_SKILLS_DELIMETER.' ', $desc);
							{/php}
						</option>
					{/foreach}
				</select>
        	</td>
        	{/if}
        	{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>
				<b>Task to assign:</b> <span class='req'>*req</span>
				<br />
				<input type="text" name="{$p_uuid}_task" />
				<br />
				<input type="button" value="Assign this Volunteer" id="{$p_uuid}_assign" onClick="

				var old_id = document.getElementById('p_uuid');
				var parent = old_id.parentNode;
				var form_node = document.getElementById('assign_form');

				var new_id = document.createElement('input');
				new_id.setAttribute('type', 'hidden');
				new_id.setAttribute('value', '{$p_uuid}');
				new_id.setAttribute('name', 'p_uuid');
				new_id.setAttribute('id', 'p_uuid');

				parent.removeChild(old_id);
				form_node.appendChild(new_id);
				form_node.submit();

				" />
				</td>
        	{/if}
        	{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
            	<td onMouseOver="this.style.color='red';"
            	    onMouseOut="this.style.color='black';"
            	    style="color: black; font-size: 30px; font-weight: bold; cursor: pointer; font-family: 'Comic Sans MS'"
            	    onClick="window.location='index.php?mod=vm&amp;act=project&amp;vm_action=process_remove_from_project&amp;p_uuid={$p_uuid}&amp;proj_id={$proj_id}';">
            	x</td>
			{/if}
			{if $showEditTask && $view_auth >= VM_ACCESS_PARTIAL}
				<td onMouseOver="this.style.color='green';"
            	    onMouseOut="this.style.color='black';"
            	    style="color: black; font-size: 30px; font-weight: bold; cursor: pointer; font-family: 'Comic Sans MS'"
            	    onClick="window.location='index.php?mod=vm&amp;act=project&amp;vm_action=display_edit_task&amp;p_uuid={$p_uuid}&amp;proj_id={$proj_id}';">
            	*</td>
			{/if}
        </tr>
    {/foreach}
    </tbody>
</table>
{else}
	{if $just_assigned_vol}
		{php}
			add_confirmation('To assign another volunteer, you must perform another search because no other volunteers match the current search criteria');
		{/php}
	{else if $searching}
		{php}
			add_warning('No volunteers were found. Please refine your criteria and try again');
			if($_REQUEST['vol_name'] != '' && !$advanced)
				add_warning('Alternatively, you can try the <a href="index.php?mod=vm&act=volunteer&vm_action=display_search&advanced=true">Advanced Search</a>, specifying \'Loose Name Matching\'');
		{/php}
	{else}
		<center>(none)</center>
	{/if}
{/if}
<br /><br />