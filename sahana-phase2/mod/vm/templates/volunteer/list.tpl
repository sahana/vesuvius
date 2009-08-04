{if count($volunteers) > 0}
<table align=center>
    <thead>
        <tr>
            <td>_("Name")</td>

{* Volunteer's picture *}
            {if $showPictures}
	            <td>_("Picture")</td>
			{/if}

{* Volunteer's status *}
			{if $showStatus && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>_("Status")</td>
	        {/if}

{* Volunteer's affiliation *}
			{if $showAffiliation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>_("Affiliation")</td>
	        {/if}


{* Volunteers Position*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showPositions}
				<td>_("Project - Position")</td>
			{/if}

{* Volunteer's availability *}
            {if $showAvailability && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>_("Availability")<br />_("Start")</td>
	            <td>_("Availability")<br />_("End")</td>
            {/if}

{* Volunteer's hours*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showHours}
				  <td>_("Hours")</td>
			{/if}
{* Volunteer's IDs *}
            {if $showIDs && $view_auth >= VM_ACCESS_ALL}
            	<td>_("Identification")</td>
            {/if}

{* Volunteer's location *}
            {if $showLocation && $view_auth >= VM_ACCESS_PARTIAL}
            	<td>_("Location")</td>
           	{/if}

{* Volunteer's specialties *}
			{if $showSkills && $view_auth >= VM_ACCESS_PARTIAL}
				<td>_("Specialties")</td>
			{/if}

{* Assign volunteer to project *}
			{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>_("Assign")</td>
			{/if}

{* Remove volunteer from project link *}
			{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
	       		<td>_("Remove From Project")</td>
			{/if}

        </tr>
    </thead>







    <tbody>
    {foreach $volunteers as $vol}
    	{php}
    		$info = $vol->info;
    	{/php}
        <tr style="text-align: center; background-color: white; height: {$rowHeight}px;" onMouseOver="this.style.backgroundColor = '#FFA';"	onMouseOut="this.style.backgroundColor = 'white';">
            <td><a href='?mod=vm&act=default&vm_action=display_single&p_uuid={php}echo $vol->p_uuid;{/php}'>{$info.full_name}</a></td>

{* Volunteer's picture *}
            {if $showPictures}
            {php}
            	$pictureID = $vol->getPictureID();
            {/php}
			<td style="margin: 0; padding: 0; text-align: center;">
				{if !empty($pictureID)}
					<img  style="margin: 0; padding: 0;" src="?mod=vm&amp;act=display_image&amp;stream=image&amp;size=thumb&amp;id={$pictureID}" />
				{/if}
			</td>
			{/if}

{* Volunteer's status *}
        	{if $showStatus && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>
	            	{php}
	            		$num_projs = count($vol->proj_id);
	            	{/php}
	            	{if $num_projs > 0}
	            		<b style="color: green">_("Assigned")</b> {*({$num_projs})*}
	            	{else}
	            		<b style="color: red">_("Unassigned")</b>
	            	{/if}
	            </td>
	        {/if}

{* Volunteer's affiliation *}
			{if $showAffiliation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>{$info.affiliation_name}</td>
	        {/if}

{* Volunteers position in a Project*}
			{if $view_auth >= VM_ACCESS_PARTIAL && $showPositions}
				<td align="center">
				{php}
					$volPositions = $vol->getVolunteerAssignments();
				{/php}
				{if !empty($volPositions)}
				<table>
					{foreach $volPositions as $position}
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
	            <td>{$info.date_start}</td>
	            <td>{$info.date_end}</td>
            {/if}

  {* Volunteer's Hours *}
		{if $view_auth >= VM_ACCESS_PARTIAL && $showHours}
  			<td><?php echo $vol->getHoursByProject($modifyProjId); ?></td>

  			{/if}


{* Volunteer's IDs *}
	        {if $showIDs && $view_auth == VM_ACCESS_ALL}
	            <td>
		            {foreach $vol->info['ids'] as $name => $serial}
		            	<b>{$name}</b>: {$serial}<br />
		            {/foreach}
	            </td>
            {/if}

{* Volunteer's location *}
            {if $showLocation && $view_auth >= VM_ACCESS_PARTIAL}
	            <td>
	            	{foreach $vol->info['location_names'] as $loc}
	            		{$loc}<br />
	            	{/foreach}
	            </td>
            {/if}

{* Volunteer's specialties *}
			{if $showSkills && $view_auth >= VM_ACCESS_PARTIAL}
				<td>
					<select style="width: 100%;">
						{foreach $info['skills'] as $opt_value => $desc}
							<option value="{$opt_value}">
								{$desc}
							</option>
						{/foreach}
					</select>
	        	</td>
        	{/if}

{* Assign volunteer to project *}
        	{if $showAssignButton && $view_auth >= VM_ACCESS_PARTIAL}
				<td>
				<b>_("Position:")</b>
				<br />
				<select name="pos_id_<?php echo $vol->p_uuid; ?>">
				{foreach $positions as $p}
					<option value="{$p.pos_id}">{$p.title}</option>
				{/foreach}
				</select>
				<br />
				<input type="submit" name="assigning_vol_<?php echo $vol->p_uuid; ?>" value="_("Assign this Volunteer")" />
				</td>
        	{/if}

{* Remove volunteer from project link *}
			<?php
				global $global;
				$rpp = $global['vm_page_rpp'];
				$page = isset($_REQUEST['page']) ? $_REQUEST['page'] : 1;
			?>
        	{if $showRemove && $view_auth >= VM_ACCESS_PARTIAL}
            	<td onMouseOver="this.style.color='red';"
            	    onMouseOut="this.style.color='black';"
            	    style="color: black; font-size: 30px; font-weight: bold; cursor: pointer; font-family: 'Comic Sans MS'"
            	    onClick="window.location='index.php?mod=vm&amp;act=project&amp;vm_action=process_remove_from_project&amp;p_uuid=<?php echo $vol->p_uuid; ?>&amp;proj_id={$modifyProjId}&amp;page={$page}&amp;rpp={$rpp}';">
            	x</td>
			{/if}

        </tr>
    {/foreach}
    </tbody>
</table>
{else}
	{if $justAssignedVol}
		{php}
		_add_confirmation(_('To assign another volunteer, you must perform another search because no other volunteers match the current search criteria'));
		{/php}
	{else if $searching}
		{php}
			add_warning(_('No volunteers were found. Please refine your criteria and try again'));
			if($_REQUEST['vol_name'] != '' && !$advanced)
				add_warning(_('Alternatively, you can try the') . '<a href="index.php?mod=vm&act=volunteer&vm_action=display_search&advanced=true">Advanced Search</a>,' . _('specifying \'Loose Name Matching\''));
		{/php}
	{else}
		<center>{php}echo _('There are no volunteers found'){/php}</center>
	{/if}
{/if}
<br /><br />
