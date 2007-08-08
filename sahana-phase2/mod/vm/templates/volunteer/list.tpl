{if count($volunteers) > 0}
<table align=center>
    <thead>
        <tr>
            <td>Name</td>

{* Volunteer's picture *}
            {if $showPictures}
	            <td>Picture</td>
			{/if}

{* Volunteer's status *}
			{if $showStatus && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>Status</td>
	        {/if}

{* Volunteer's affiliation *}
			{if $showAffiliation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>Affiliation</td>
	        {/if}


{* Volunteers Position*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showPositions}
				<td>Project - Position</td>
			{/if}

{* Volunteer's availability *}
            {if $showAvailability && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>Availability<br />Start</td>
	            <td>Availability<br />End</td>
            {/if}

{* Volunteer's hours*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showHours}
				  <td>Hours</td>
			{/if}
{* Volunteer's IDs *}
            {if $showIDs && $view_auth >= VM_ACCESS_ALL}
            	<td>Identification</td>
            {/if}

{* Volunteer's location *}
            {if $showLocation && $view_auth >= VM_ACCESS_PARTIAL}
            	<td>Location</td>
           	{/if}

{* Volunteer's specialties *}
			{if $showSkills && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Specialties</td>
			{/if}

{* Assign volunteer to project *}
			{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>Assign</td>
			{/if}

{* Remove volunteer from project link *}
			{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
	       		<td>Remove From Project</td>
			{/if}

        </tr>
    </thead>







    <tbody>
    {foreach $volunteers as $p_uuid => $vol}
        <tr style="text-align: center; background-color: white; height: {$rowHeight}px;" onMouseOver="this.style.backgroundColor = '#FFA';"	onMouseOut="this.style.backgroundColor = 'white';">
            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid={$p_uuid}'>{$vol.full_name}</a></td>

{* Volunteer's picture *}
            {if $showPictures}
			<td style="margin: 0; padding: 0; text-align: center;">
				{if !empty($vol['pictureID'])}
					<img  style="margin: 0; padding: 0;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=thumb&amp;id={$vol.pictureID}" />
				{/if}
			</td>
			{/if}

{* Volunteer's status *}
        	{if $showStatus && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>
	            	{php}
	            		$num_projs = count($vol['pos_id']);
	            	{/php}
	            	{if $num_projs > 0}
	            		<b style="color: green">Assigned</b> {*({$num_projs})*}
	            	{else}
	            		<b style="color: red">Unassigned</b>
	            	{/if}
	            </td>
	        {/if}

{* Volunteer's affiliation *}
			{if $showAffiliation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>{$vol.affiliation}</td>
	        {/if}

{* Volunteers position in a Project*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showPositions}
				<td align="center">
				{if !empty($volPositions[$p_uuid])}
				<table>
					{foreach $volPositions[$p_uuid] as $position}
					<tr>
						<td align="right" style="border: none; padding-right: 0;">
					 		<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$position.proj_id}">{$position.project_name}</a>
					 	</td>
					 	<td align="left" style="border: none;">- {$position.title}</td>
					</tr>
					{/foreach}
				</table>
				{/if}
				</td>
			{/if}
{* Volunteer's availability *}
            {if $showAvailability && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>{$vol.date_start}</td>
	            <td>{$vol.date_end}</td>
            {/if}

  {* Volunteer's Hours *}
		{if $view_auth >= VM_ACCESS_PARTIAL && $showHours}
  			<td>{$hours}</td>

  			{/if}


{* Volunteer's IDs *}
	        {if $showIDs && $view_auth == VM_ACCESS_ALL}
	            <td>
		            {foreach $vol['ids'] as $name => $serial}
		            	<b>{$name}</b>: {$serial}<br />
		            {/foreach}
	            </td>
            {/if}

{* Volunteer's location *}
            {if $showLocation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>
	            	{foreach $vol['locations'] as $key => $loc}
	            		{$loc}<br />
	            	{/foreach}
	            </td>
            {/if}

{* Volunteer's specialties *}
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

{* Assign volunteer to project *}
        	{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>
				<b>Position:</b>
				<br />
				<select name="pos_id_{$p_uuid}">
				{foreach $positions as $p}
					<option value="{$p.pos_id}">{$p.title}</option>
				{/foreach}
				</select>
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

{* Remove volunteer from project link *}
        	{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
            	<td onMouseOver="this.style.color='red';"
            	    onMouseOut="this.style.color='black';"
            	    style="color: black; font-size: 30px; font-weight: bold; cursor: pointer; font-family: 'Comic Sans MS'"
            	    onClick="window.location='index.php?mod=vm&amp;act=project&amp;vm_action=process_remove_from_project&amp;p_uuid={$p_uuid}&amp;proj_id={$modifyProjId}';">
            	x</td>
			{/if}

        </tr>
    {/foreach}
    </tbody>
</table>
{else}
	{if $justAssignedVol}
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