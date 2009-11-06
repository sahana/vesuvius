<h2 style="text-align: center;">{$info.name}</h2>

{if $showVolunteersAssigned && ($edit_auth || $delete_auth || $assign_auth)}
	<div id="submenu_v">
	{if $edit_auth}
		<a href='?mod=vm&act=project&vm_action=display_edit&proj_id={$proj_id}'>_("Edit")</a>
	{/if}
	{if $delete_auth}
		<a href="?mod=vm&amp;act=project&vm_action=display_confirm_delete&proj_id={$proj_id}">_("Delete")</a>
	{/if}
	{if $assign_auth}
		<a href="?mod=vm&amp;act=project&vm_action=display_assign&proj_id={$proj_id}">_("Assign Volunteers")</a>
	{/if}
		<a href="?mod=vm&amp;act=project&amp;vm_action=display_single&amp;proj_id={$proj_id}">_("Refresh")</a>
	</div>
{/if}

<table align=center>
    <tbody>
        <tr>
        	<td><b>_("Project Name :")</b></td>
        	{if !$showVolunteersAssigned}
        	<td><a href='index.php?mod=vm&act=project&vm_action=display_single&proj_id={$proj_id}'>{$info.name}</a></td>
        	{else}
        	<td>{$info.name}</td>
        	{/if}
        </tr>
        <tr>
        	<td><b>_("Start Date :")</b></td>
        	<td>{$start_date}</td>
        </tr>
        <tr>
        	<td><b>_("End Date :")</b></td>
        	<td>{$end_date}</td>
        </tr>
        <tr>
        	<td><b>_("Location :")</b></td>
        	<td>{$location}</td>
        </tr>
        <tr>
        	<td><b>_("Volunteers assigned :")</b></td>
        	<td>{$numVolunteers}</td>
        </tr>
    </tbody>
 </table>
<br />
<br />

{if count($positions) > 0}
<table align=center>
    <h3 style="text-align: center;">_("Positions")</h3>
    <tbody>
    	<tr>
			<th colspan="3"></th>
			<th colspan="2">_("# Volunteers")</th>
			<th></th>
    	</tr>
		<tr>
        	<th>_("Title")</th>
        	<th>_("Description")</th>
        	{if $assign_auth}
        		<th>_("Pay Rate")</th>
        	{/if}
        	<th style="padding-right: 1em; text-align: center;">_("Target")</th>
        	<th>_("Assigned")</th>
        	{if $add_pos_auth || $delete_pos_auth}
            <th>_("Actions")</th>
        	{/if}
        </tr>
		{foreach $positions as $p}
        <tr>
        	<td>{$p.title}</td>
        	<td>{$p.description}</td>

			{if $assign_auth}
        		<td align="center">
        		{if !empty($p['payrate'])}
        			${$p.payrate}
        		{else}-{/if}
        		</td>
        	{/if}
        	<td align="center">
        		<b>
	        	{if $p['numSlots'] > 0}
	        		{$p.numSlots}
	        	{else}-{/if}
        		</b>
        	</td>

   			<td align="center">
   			<b>

   			{if $p['numVolunteers'] <= 0}
   				<span style="color: red">{$p.numVolunteers}</span>
   			{else if $p['numVolunteers'] >= $p['numSlots'] }
   				<span style="color: green">{$p.numVolunteers}</span>
   			{else}
   				<span style="color: orange">{$p.numVolunteers}</span>
   			{/if}
   			</b>
   			</td>
        	{if $add_pos_auth || $delete_pos_auth}
        	<td>
	        	{if $add_pos_auth}
					[<a href="?mod=vm&amp;act=project&amp;vm_action=add_position&amp;proj_id={$proj_id}&amp;pos_id={$p.pos_id}">_("edit")</a>]
				{/if}
				{if $delete_pos_auth}
					[<a href="#" onClick="if(confirm('Are you sure you want to remove this position?')) window.location = 'index.php?mod=vm&amp;act=project&amp;vm_action=remove_position&amp;proj_id={$proj_id}&amp;pos_id={$p.pos_id}';">_("remove")</a>]
				{/if}
			</td>
			{/if}
		</tr>
		{/foreach}
    </tbody>

 </table>

{if $add_pos_auth}
	<center>
		[<a href="?mod=vm&act=project&vm_action=add_position&proj_id={$proj_id}">_("Add a position")</a>]
	</center>
{/if}
{else}

<center>
	<h3 style="text-align: center;">_("Positions")</h3>
		_("There are no positions assigned to") {$info.name}.
		{if $add_pos_auth }
			[<a href="?mod=vm&act=project&vm_action=add_position&proj_id={$proj_id}">_("Add a position")</a>]
		{/if}
	</center>

{/if}
<br />

{if $showVolunteersAssigned}
<h3>_("Description")</h3>
{$info.description}
<br /><br />

<!--
Projects now have positions
<h3>_("Specialties needed")</h3>
<br />
<?php
//$skills->display();
?>

<br />
<br />
-->

<div align="center">
	{if $numVolunteers > 0}
		_("Volunteers working on") {$info.name}:
	{else}
		_("No volunteers are currently assigned to") {$info.name}.
	{/if}
</div>
{/if}
<br />
